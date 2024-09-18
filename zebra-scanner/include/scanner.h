#pragma once
#include <atlbase.h>

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <pybind11/pybind11.h>

#include "common_defs.h"

#import <_CoreScanner.tlb> no_namespace named_guids

class Attribute;
namespace py = pybind11;

class Scanner final
{
public:
	explicit Scanner(CComQIPtr<ICoreScanner> scanner_interface): scanner_interface_(scanner_interface) {}
	~Scanner()
	{
		py::gil_scoped_acquire acquire;
		on_barcode_.clear();
	}

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

	void OnBarcodeDecorator(const py::object& obj);
	void OnBarcode(py::object& obj);

	void TrimProperties();
	std::vector<py::object> on_barcode_;

protected:
	CComQIPtr<ICoreScanner> scanner_interface_;
};
