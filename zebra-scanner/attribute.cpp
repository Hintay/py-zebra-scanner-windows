#include <atlcomcli.h>
#include "attribute.h"
#include "scanner.h"

using namespace std;

Attribute::Attribute(
	Scanner* s, const int id, const wchar_t data_type,
	const wchar_t* permission, const wchar_t* value
) : id_(id), data_type_(data_type), permission_(permission), scanner_(s)
{
	value_ = CastStringToObject(value, data_type);
}

int Attribute::SetValue(const py::object& v)
{
	return ExecuteSetOrStoreAttribute(OPCODE::RSM_ATTR_SET, v);
}

int Attribute::StoreValue(const py::object& v)
{
	return ExecuteSetOrStoreAttribute(OPCODE::RSM_ATTR_STORE, v);
}

py::object Attribute::CastStringToObject(const wchar_t* value_str, const wchar_t data_type) const
{
	py::gil_scoped_acquire acquire;
	// Information about data types is taken from zebra-scanner-4.4.1-8/Native/CsClient/src/CsDecodeIncomming.cpp
	switch (data_type)
	{
	case L'F': // Flag? A boolean
		return py::cast(wcscmp(L"True", value_str) == 0);

	case L'B': // uint8_t
	case L'W': // uint16_t
	case L'D': // uint32_t
		return py::cast(std::stoul(value_str));

	case L'I': // int16_t
	case L'L': // int32_t
		return py::cast(std::stol(value_str));

	default: // String or single character
		return py::cast(value_str);
	}
}

int Attribute::ExecuteSetOrStoreAttribute(const OPCODE command, const py::object& v)
{
	std::wstring value_as_string;
	CastValueToString(v, value_as_string);

	// If the attribute IDs correspond to non-actionable attributes, then add
	// them as a valid data type.
	std::wstring data_type;
	if (id_ != 6000 && id_ != 6001 && id_ != 6003)
		data_type = data_type_;

	const std::wstring in_xml = L"<inArgs><scannerID>" + to_wstring(scanner_->scanner_id_) +
		L"</scannerID><cmdArgs><arg-xml><attrib_list><attribute>" +
		L"<id>" + to_wstring(id_) + L"</id>" +
		L"<datatype>" + data_type + L"</datatype>" +
		L"<value>" + value_as_string + L"</value>" +
		L"</attribute></attrib_list></arg-xml></cmdArgs></inArgs>";

	BSTR out_xml;
	long status;
	scanner_->ExecCommand(command, &CComBSTR(in_xml.c_str()), &out_xml, &status);
	if (status == STATUS_SUCCESS)
		value_ = v; // Update local copy of the new value
	return status;
}

void Attribute::CastValueToString(const py::object& v, std::wstring& value_as_string) const
{
	switch (data_type_) {
	case L'F': // Boolean (F for flag?)
		value_as_string = v.cast<bool>() ? L"True" : L"False";
		break;

	case L'B': // uint8_t
	case L'W': // uint16_t
	case L'D': // uint32_t
		value_as_string = std::to_wstring(v.cast<uint32_t>());
		break;

	case L'I': // int16_t
	case L'L': // int32_t
		value_as_string = std::to_wstring(v.cast<int32_t>());
		break;

	default: // A string
		value_as_string = v.cast<std::wstring>();
		break;
	}
}
