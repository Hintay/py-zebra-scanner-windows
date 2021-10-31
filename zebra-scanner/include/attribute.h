#pragma once
#include <string>
#include <pybind11/pybind11.h>

#include "common_defs.h"

class Scanner;
namespace py = pybind11;

class Attribute
{
public:
	explicit Attribute(
		Scanner* s,
		int id,
		wchar_t data_type,
		const wchar_t* permission,
		const wchar_t* value
	);

	int SetValue(const py::object& v);
	int StoreValue(const py::object& v);
	py::object CastStringToObject(const wchar_t* value_str, wchar_t data_type) const;

	int id_;
	wchar_t data_type_;
	std::wstring permission_;
	py::object value_;

private:
	int ExecuteSetOrStoreAttribute(OPCODE command, const py::object& v);
	void CastValueToString(const py::object& v, std::wstring& value_as_string) const;
	Scanner* scanner_;
};
