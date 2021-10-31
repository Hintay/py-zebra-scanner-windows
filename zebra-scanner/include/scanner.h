#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <pybind11/pybind11.h>

#include "common_defs.h"
#include "_CoreScanner_h.h"

class Attribute;
namespace py = pybind11;

class Scanner final
{
public:
	explicit Scanner(ICoreScanner* scanner_interface): scanner_interface_(scanner_interface) {}

	std::wstring type_;
	int scanner_id_ = -1;
	std::wstring serial_number_;
	std::wstring guid_;
	std::wstring pid_;
	std::wstring vid_;
	std::wstring model_number_;
	std::wstring dom_;
	std::wstring firmware_;
	std::map<int, std::shared_ptr<Attribute>> attributes_;

	HRESULT ExecCommand(
		/* [in] */ OPCODE op_code,
		/* [in] */ BSTR* in_xml,
		/* [out] */ BSTR* out_xml,
		/* [out] */ LONG* status) const;
	HRESULT ExecCommand(
		/* [in] */ OPCODE op_code,
		/* [out] */ BSTR* out_xml,
		/* [out] */ LONG* status) const;

	void PullTrigger() const;
	void ReleaseTrigger() const;
	std::vector<std::shared_ptr<Attribute>> FetchAttributes();
	std::vector<std::shared_ptr<Attribute>> FetchAttributes(int);
	std::vector<std::shared_ptr<Attribute>> FetchAttributes(const std::vector<int>&);
	std::vector<std::shared_ptr<Attribute>> FetchAttributes(const std::wstring&);

	void Scanner::TrimProperties();

	void OnBarcodeDecorator(const py::object& obj);
	void OnBarcode(py::object& obj);
	std::vector<py::object> on_barcode_;
private:
	ICoreScanner* scanner_interface_;
};
