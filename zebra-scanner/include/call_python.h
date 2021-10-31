#pragma once
#include <pybind11/pybind11.h>

namespace py = pybind11;

template<class C>
py::object call_python(py::object& fn, C& arg1, const bool ensure_gil = true)
{
	if (ensure_gil)
		py::gil_scoped_acquire acquire;

	return fn(arg1);
}
