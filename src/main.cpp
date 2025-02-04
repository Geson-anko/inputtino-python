// Copyright 2025 Geson-anko
#include <pybind11/pybind11.h>

#include <inputtino/input.hpp>

std::string hello_from_bin() { return "Hello from inputtino-python!"; }

namespace py = pybind11;

PYBIND11_MODULE(_core, m) {
  m.doc() = "pybind11 hello module";

  m.def("hello_from_bin", &hello_from_bin, R"pbdoc(
      A function that returns a Hello string.
  )pbdoc");
}
