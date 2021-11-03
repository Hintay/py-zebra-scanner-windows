#include "scanner.h"
#include "attribute.h"
#include "call_python.h"
#include "pugixml.hpp"

using namespace std;

namespace str_tool
{
	inline void ltrim(std::wstring& s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](const int ch) {
			return !std::isspace(ch);
			}));
	}

	inline void rtrim(std::wstring& s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), [](const int ch) {
			return !std::isspace(ch);
			}).base(), s.end());
	}

	inline void trim(std::wstring& s) {
		ltrim(s);
		rtrim(s);
	}
}


vector<shared_ptr<Attribute>> Scanner::FetchAttributes()
{
	long status;
	BSTR out_xml;
	ExecCommand(OPCODE::RSM_ATTR_GETALL, &out_xml, &status);

	pugi::xml_document out_args;
	out_args.load_buffer_inplace(&out_xml[0], SysStringByteLen(out_xml));
	std::wstring attribute_list;

	pugi::xml_node attr = out_args.child(L"outArgs").child(L"arg-xml").child(L"response").child(L"attrib_list").child(L"attribute");
	if(attr)
		attribute_list += attr.child_value();

	for(attr = attr.next_sibling(L"attribute"); attr; attr = attr.next_sibling(L"attribute"))
	{
		attribute_list += ',';
		attribute_list += attr.child_value();
	}

	return FetchAttributes(attribute_list);
}

vector<shared_ptr<Attribute>> Scanner::FetchAttributes(const int attribute_id)
{
	return FetchAttributes(to_wstring(attribute_id));
}

vector<shared_ptr<Attribute>> Scanner::FetchAttributes(const std::vector<int>& attribute_ids)
{
	std::wstring attribute_list;
	auto ids_begin = attribute_ids.begin();
	const auto ids_end = attribute_ids.end();

	if (ids_begin != ids_end)
		attribute_list += to_wstring(*ids_begin++);

	while (ids_begin != ids_end)
		attribute_list += L',' + to_wstring(*ids_begin++);

	return FetchAttributes(attribute_list);
}

vector<shared_ptr<Attribute>> Scanner::FetchAttributes(const std::wstring& attribute_ids) {
	const std::wstring in_xml = L"<inArgs><scannerID>" + to_wstring(scanner_id_) +
		L"</scannerID><cmdArgs><arg-xml><attrib_list>" +
		attribute_ids + L"</attrib_list></arg-xml></cmdArgs></inArgs>";

	long status;
	BSTR out_xml;
	ExecCommand(OPCODE::RSM_ATTR_GET, &CComBSTR(in_xml.c_str()), &out_xml, &status);

	pugi::xml_document out_args;
	out_args.load_buffer_inplace(&out_xml[0], SysStringByteLen(out_xml));

	std::vector<std::shared_ptr<Attribute>> attributes;
	for (pugi::xml_node attr = out_args.child(L"outArgs").child(L"arg-xml").child(L"response").child(L"attrib_list").child(L"attribute");
		attr;
		attr = attr.next_sibling(L"attribute"))
	{
		auto a = std::make_shared<Attribute>(
			this, std::stoi(attr.child_value(L"id")),
			attr.child_value(L"datatype")[0],
			attr.child_value(L"permission"),
			attr.child_value(L"value"));
		attributes_[a->id_] = a;
		attributes.push_back(a);
	}
	return attributes;
}

void Scanner::TrimProperties()
{
	str_tool::trim(serial_number_);
	str_tool::trim(model_number_);
	str_tool::trim(firmware_);
}

void Scanner::OnBarcodeDecorator(const py::object& obj) {
	on_barcode_.push_back(obj);
}

void Scanner::OnBarcode(py::object& obj) {
	py::gil_scoped_acquire acquire;
	for (auto fn : on_barcode_)
	{
		call_python(fn, obj, false);
	}
}

HRESULT Scanner::ExecCommand(OPCODE op_code, BSTR* in_xml, BSTR* out_xml, LONG* status) const
{
	return scanner_interface_->ExecCommand(static_cast<LONG>(op_code), in_xml, out_xml, status);
}

HRESULT Scanner::ExecCommand(OPCODE op_code, BSTR* out_xml, LONG* status) const
{
	const wstring in_xml = L"<inArgs><scannerID>" + to_wstring(scanner_id_) + L"</scannerID></inArgs>";
	return scanner_interface_->ExecCommand(static_cast<LONG>(op_code), &CComBSTR(in_xml.c_str()), out_xml, status);
}

void Scanner::PullTrigger() const
{
	long status;
	BSTR out_xml;
	ExecCommand(OPCODE::DEVICE_PULL_TRIGGER, &out_xml, &status);
}

void Scanner::ReleaseTrigger() const
{
	long status;
	BSTR out_xml;
	ExecCommand(OPCODE::DEVICE_RELEASE_TRIGGER, &out_xml, &status);
}
