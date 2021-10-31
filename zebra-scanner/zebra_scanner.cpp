#include "zebra_scanner.h"

#include <sstream>
#include <atlsafe.h>
#include <locale>
#include <fmt/core.h>
#include <fmt/xchar.h>

#include "scanner.h"
#include "attribute.h"
#include "barcode.h"
#include "call_python.h"

# ifdef _HAS_CXX17
#include <magic_enum.hpp>
# endif

using namespace std;

template<class C>
wchar_t* repr_wchar(C& object, ssize_t* size = nullptr)
{
	return PyUnicode_AsWideCharString(py::repr(object).ptr(), size);
}

PYBIND11_MODULE(zebra_scanner, m)
{
	using namespace py;

	// Initialize COM
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	class_<CoreScanner>(m, "CoreScanner", "Zebra CoreScanner Driver Instance")
		.def(py::init<>())
		.def("open", &CoreScanner::Open, "Opens a CoreScanner instance. This must be the first command called before invoking any other command.")
		.def("close", &CoreScanner::Close, "Closes the application instance through the CoreScanner service.")
		.def("on_scanner_added", &CoreScanner::OnScannerAddedDecorator, "Triggered when a new scanner is added. The parameter is the new scanner.")
		.def("on_scanner_removed", &CoreScanner::OnScannerRemovedDecorator, "Triggered when a scanner is removed. The parameter is the removed scanner.")
		.def("fetch_scanners", &CoreScanner::FetchScanners, "Fetch all scanners that are connected. This command should be invoked after the Open command.")
		.def_readonly("scanners", &CoreScanner::scanners_, "Scanners list")
		.def("__repr__",
			[](const CoreScanner& a) {
				if (!a.is_open_)
					return string("<CoreScanner Closed>");
				return fmt::format("<CoreScanner Opened(scanners={})>", static_cast<string>(repr(cast(a.scanners_))));
			})
	;

	class_<Scanner, std::shared_ptr<Scanner>> (m, "Scanner", "Zebra Scanner Instance")
		.def("on_barcode", &Scanner::OnBarcodeDecorator, "Triggered when there is a barcode scanned. The parameter is the barcode.")
		.def("pull_trigger", &Scanner::PullTrigger, "Pull the trigger of the scanner.")
		.def("release_trigger", &Scanner::ReleaseTrigger, "Release the trigger of the scanner.")
		.def("fetch_attributes", py::overload_cast<>(&Scanner::FetchAttributes), "Fetch all the attributes of the scanner.")
		.def("fetch_attributes", py::overload_cast<int>(&Scanner::FetchAttributes), "Fetch the value of attribute of the scanner.")
		.def("fetch_attributes", py::overload_cast<const std::vector<int>&>(&Scanner::FetchAttributes), "Fetch the values of attribute(s) of the scanner.")
		.def("fetch_attributes", py::overload_cast<const std::wstring&>(&Scanner::FetchAttributes), "Fetch the values of attribute(s) of the scanner.")
		.def_readonly("attributes", &Scanner::attributes_)
		.def_readonly("type", &Scanner::type_)
		.def_readonly("scannerID", &Scanner::scanner_id_)
		.def_readonly("serialnumber", &Scanner::serial_number_)
		.def_readonly("GUID", &Scanner::guid_)
		.def_readonly("PID", &Scanner::pid_)
		.def_readonly("VID", &Scanner::vid_)
		.def_readonly("modelnumber", &Scanner::model_number_)
		.def_readonly("DoM", &Scanner::dom_)
		.def_readonly("firmware", &Scanner::firmware_)
		.def("__repr__",
			[](const Scanner& a) {
				return fmt::format(
					L"Scanner(type='{}', scannerID={}, serialnumber='{}', GUID='{}', PID='{}', modelnumber='{}', DoM='{}', firmware='{}')",
					a.type_, a.scanner_id_, a.serial_number_, a.guid_, a.pid_, a.vid_, a.model_number_, a.dom_, a.firmware_
				);
			});

	class_<Attribute, std::shared_ptr<Attribute>>(m, "Attribute", "Attribute Instance of Specified Scanner")
		.def("set_value", &Attribute::SetValue, "Set the value of attribute of the scanner. Attribute set using this command are lost after the next power down.")
		.def("store_value", &Attribute::StoreValue, "Store the value of attribute of the scanner. Attribute store using this command are persistent over power down and power up cycles.")
		.def_readonly("id", &Attribute::id_)
		.def_readonly("permission", &Attribute::permission_)
		.def_readonly("datatype", &Attribute::data_type_)
		.def_readonly("value", &Attribute::value_)
		.def("__repr__",
			[](const Attribute& a) {
				return fmt::format(
					L"Attribute(id={}, permission='{}', datatype='{}', value={})",
					a.id_, a.permission_, a.data_type_, repr_wchar(a.value_));
			});

	class_<Barcode> barcode_m(m, "Barcode");

# ifdef _HAS_CXX17
	py::enum_<BarcodeType> barcode_type(barcode_m, "Type");
	auto types = magic_enum::enum_entries<BarcodeType>();
	for(const auto& entire: types)
		barcode_type.value(std::string(entire.second).c_str(), entire.first);
	barcode_type.export_values();
# endif

	barcode_m.def("get_symbology", &Barcode::GetSymbology, "Get symbology type by ID.")
		.def_readonly("code", &Barcode::code_)
		.def_readonly("type", &Barcode::type_)
		.def_property_readonly("symbology",  [](const Barcode& a) { return Barcode::GetSymbology(a.type_); })
		.def("__repr__",
			[](const Barcode& a) {
				return fmt::format(
					L"Barcode(code='{}', type='{}', symbology='{}')",
					a.code_, a.type_, Barcode::GetSymbology(a.type_));
			});
}

CoreScanner::CoreScanner()
{
	PyEval_InitThreads();

	// Create the CoreScanner COM object
	const HRESULT hr = CoCreateInstance(CLSID_CCoreScanner, nullptr, CLSCTX_ALL, IID_ICoreScanner, reinterpret_cast<void**>(&scanner_interface_));
	if FAILED(hr)
		throw runtime_error("Failed to create CoreScanner COM object.");

	if (scanner_interface_)
	{
		// Create an instance of the sink object to sink Core Scanner Events
		scanner_event_sink_ = new EventSink(this);
		scanner_event_sink_unknown_ = scanner_event_sink_->GetIDispatch(FALSE);
		// Advice or make a connection
		AfxConnectionAdvise(scanner_interface_, DIID__ICoreScannerEvents, scanner_event_sink_unknown_, FALSE, &dw_cookie_);
	}
}

CoreScanner::~CoreScanner()
{
	if (is_open_)
	{
		try
		{
			Close();
		}
		catch (...) {}
	}
	DestroyInstance();
}

void CoreScanner::DestroyInstance()
{
	/*** If ever the CoreScanner Service becomes unresponsive when the application is
	closed, a STATUS_ACCESS_VIOLATION is raised on this thread which is handled
	by a Win32 exception handler. - VRQW74
	***/
	_try
	{
		if (scanner_interface_)
		{
			if (dw_cookie_ != 0 && scanner_event_sink_)
			{
				AfxConnectionUnadvise(scanner_interface_, DIID__ICoreScannerEvents, scanner_event_sink_unknown_,
				                      FALSE, dw_cookie_);
				delete scanner_event_sink_;
				scanner_event_sink_ = nullptr;
				dw_cookie_ = 0;
			}
			scanner_interface_->Release();
			scanner_interface_ = nullptr;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
	}
}

void CoreScanner::Open()
{
	long status = 1;

	CComSafeArray<SHORT> types(1);
	types[0] = SCANNER_TYPES_ALL;

	const HRESULT hr = scanner_interface_->Open(0, types, 1, &status);
	if(FAILED(hr) || status != STATUS_SUCCESS)
		throw runtime_error(fmt::format("Failed to open CoreScanner object. Returned status: {}", status));

	RegisterEvents();
	FetchScanners();
	is_open_ = true;
}

void CoreScanner::Close()
{
	for (const auto& scanner_pair : scanners_)
	{
		auto scanner = scanner_pair.second;
		OnScannerRemoved(scanner);
	}

	long status;
	scanner_interface_->Close(0, &status);
	is_open_ = false;
}

void CoreScanner::RegisterEvents() const
{
	long status = 1;
	BSTR in_xml = CComBSTR(L"<inArgs><cmdArgs><arg-int>6</arg-int><arg-int>1,2,4,8,16,32</arg-int></cmdArgs></inArgs>");
	BSTR out_xml;
	const HRESULT hr = scanner_interface_->ExecCommand(static_cast<LONG>(OPCODE::REGISTER_FOR_EVENTS), &in_xml, &out_xml, &status);
	if (FAILED(hr) || status != STATUS_SUCCESS)
		throw runtime_error(fmt::format("Failed to register events. Returned status: {}", status));
}

void CoreScanner::OnScannerAddedDecorator(py::object& obj)
{
	py::gil_scoped_acquire acquire;
	on_scanner_added_.emplace_back(obj);
	for (const auto& scanner_pair: scanners_)
	{
		auto scanner = scanner_pair.second;
		py::object o = py::cast(scanner);
		call_python(obj, o, false);
	}
}

void CoreScanner::OnScannerRemovedDecorator(py::object& obj)
{
	on_scanner_removed_.emplace_back(obj);
}

void CoreScanner::OnScannerAdded(std::shared_ptr<Scanner>& scanner) {
	py::gil_scoped_acquire acquire;
	for (auto& callback: on_scanner_added_) {
		auto o = py::cast(scanner);
		call_python(callback, o, false);
	}
}

void CoreScanner::OnScannerRemoved(std::shared_ptr<Scanner>& scanner)
{
	py::gil_scoped_acquire acquire;
	for (auto& callback : on_scanner_removed_) {
		auto o = py::cast(scanner);
		call_python(callback, o, false);
	}
}

void CoreScanner::FetchScanners()
{
	long status = 1;
	BSTR out_xml = nullptr;
	short scanners_count = 0;
	CComSafeArray<int> scanner_id_list(MAX_NUM_DEVICES);

	const HRESULT hr = scanner_interface_->GetScanners(&scanners_count, scanner_id_list, &out_xml, &status);
	if (FAILED(hr) || status != STATUS_SUCCESS)
		throw runtime_error(fmt::format("Failed to get scanners list. Returned status: {}", status));

	pugi::xml_document scanners;
	scanners.load_buffer_inplace(&out_xml[0], SysStringByteLen(out_xml));
	for (pugi::xml_node scanner = scanners.child(L"scanners").child(L"scanner"); scanner; scanner = scanner.next_sibling(L"scanner")) {
		ParseScannerFromXml(scanner);
	}
}

void CoreScanner::ParseScannerFromXml(const pugi::xml_node& scanner) {
	const int scanner_id = stoi(scanner.child_value(L"scannerID"));

	auto s = std::make_shared<Scanner>(scanner_interface_);
	s->type_ = scanner.attribute(L"type").value();
	s->scanner_id_ = scanner_id;
	s->serial_number_ = scanner.child_value(L"serialnumber");
	s->guid_ = scanner.child_value(L"GUID");
	s->pid_ = scanner.child_value(L"PID");
	s->vid_ = scanner.child_value(L"VID");
	s->model_number_ = scanner.child_value(L"modelnumber");
	s->firmware_ = scanner.child_value(L"firmware");
	s->dom_ = scanner.child_value(L"DoM");
	s->TrimProperties();

	scanners_[scanner_id] = s;

	// Wait for some kind of response from the scanner
	// so that we know we can access the scanner
	// in our on_scanner_added callback
	s->FetchAttributes(L"0");
	OnScannerAdded(s);
}

void CoreScanner::OnImageEvent(LPBYTE media_buffer, LONG buffer_size)
{
}

void CoreScanner::OnVideoEvent(LPBYTE media_buffer, LONG buffer_size)
{
}

void CoreScanner::OnBarcodeEvent(SHORT event_type, BSTR scan_data)
{
	pugi::xml_document out_args;
	out_args.load_buffer_inplace(&scan_data[0], SysStringByteLen(scan_data));
	const pugi::xml_node args = out_args.child(L"outArgs");
	const int scanner_id = stoi(args.child_value(L"scannerID"));

	const auto scanner_map = scanners_.find(scanner_id);
	if (scanner_map == scanners_.end())
	{
		FetchScanners();
		return;
	}

	const auto scanner = scanner_map->second;
	wchar_t temp_data[3] = { 0 };
	for (pugi::xml_node scan_data_node = args.child(L"arg-xml").child(L"scandata");
		scan_data_node;
		scan_data_node = scan_data_node.next_sibling(L"scandata")) {

		wstring data = scan_data_node.child_value(L"datalabel");
		wstring result;
		for (auto i = data.cbegin(); i != data.cend(); ++i) {
			if (*i == L'0' && *(++i) == L'x')
			{
				temp_data[0] = *++i;
				temp_data[1] = *++i;
				const auto converted = static_cast<wchar_t>(wcstoul(temp_data, nullptr, 16));
				result.append(1, converted);
			}
		}

		Barcode barcode(
			result, 
			std::stoi(scan_data_node.child_value(L"datatype"))
		);

		py::gil_scoped_acquire acquire;
		py::object barcode_obj = py::cast(barcode);
		scanner->OnBarcode(barcode_obj);
	}
}

void CoreScanner::OnPNPEvent(SHORT event_type, BSTR pnp_xml)
{
	pugi::xml_document out_args;
	out_args.load_buffer_inplace(&pnp_xml[0], SysStringByteLen(pnp_xml));
	for (pugi::xml_node scanner = out_args.child(L"outArgs").child(L"arg-xml").child(L"scanners").child(L"scanner");
		scanner;
		scanner = scanner.next_sibling(L"scanner"))
	{
		int scanner_id = stoi(scanner.child_value(L"scannerID"));
		if (event_type == SCANNER_ATTACHED)
		{
			auto s = std::make_shared<Scanner>(scanner_interface_);
			s->type_ = scanner.attribute(L"type").value();
			s->scanner_id_ = scanner_id;
			s->serial_number_ = scanner.child_value(L"serialnumber");
			s->guid_ = scanner.child_value(L"GUID");
			s->model_number_ = scanner.child_value(L"modelnumber");

			auto rsm_attrs = s->FetchAttributes(L"535,20004");
			s->firmware_ = rsm_attrs[0]->value_.cast<wstring>();
			s->dom_ = rsm_attrs[0]->value_.cast<wstring>();

			s->TrimProperties();
			scanners_[scanner_id] = s;
			OnScannerAdded(s);
		}
		else if (event_type == SCANNER_DETACHED)
		{
			auto s = scanners_[scanner_id];
			// For BT Scanners.
			if (wcsncmp(scanner.child_value(L"pnp"), L"0", 1) == 0)
				continue;
			OnScannerRemoved(s);
			scanners_.erase(scanner_id);
		}
	}
}

void CoreScanner::OnCommandResponseEvent(SHORT status, BSTR scan_cmd_response)
{
}

void CoreScanner::OnScanRMDEvent(SHORT event_type, BSTR event_data)
{
}

void CoreScanner::OnIOEvent(SHORT type, UCHAR data)
{
}

void CoreScanner::OnScannerNotificationEvent(SHORT notification_type, BSTR p_scanner_data)
{
}

void CoreScanner::OnBinaryDataEvent(LPBYTE binary_buffer, LONG buffer_size, SHORT data_format, BSTR* scanner_data)
{
}

void CoreScanner::OnParameterBarcodeEvent(LPBYTE barcode_buffer, LONG buffer_size)
{
}
