// Copyright 2025 Geson-anko
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <inputtino/input.hpp>

namespace py = pybind11;

PYBIND11_MODULE(_core, m) {
  m.doc() = "pybind inputtino module!";

  // DeviceDefinition
  py::class_<inputtino::DeviceDefinition>(m, "DeviceDefinition")
      .def(py::init<>())
      .def_readwrite("name", &inputtino::DeviceDefinition::name)
      .def_readwrite("vendor_id", &inputtino::DeviceDefinition::vendor_id)
      .def_readwrite("product_id", &inputtino::DeviceDefinition::product_id)
      .def_readwrite("version", &inputtino::DeviceDefinition::version)
      .def_readwrite("device_phys", &inputtino::DeviceDefinition::device_phys)
      .def_readwrite("device_uniq", &inputtino::DeviceDefinition::device_uniq);

  // VirtualDevice
  py::class_<inputtino::VirtualDevice>(m, "VirtualDevice")
      .def("get_nodes", &inputtino::VirtualDevice::get_nodes);

  // Mouse
  py::class_<inputtino::Mouse, inputtino::VirtualDevice>(m, "Mouse")
      .def_static("create", &inputtino::Mouse::create)
      .def("move", &inputtino::Mouse::move)
      .def("move_abs", &inputtino::Mouse::move_abs)
      .def("press", &inputtino::Mouse::press)
      .def("release", &inputtino::Mouse::release)
      .def("vertical_scroll", &inputtino::Mouse::vertical_scroll)
      .def("horizontal_scroll", &inputtino::Mouse::horizontal_scroll);

  py::enum_<inputtino::Mouse::MOUSE_BUTTON>(m, "MouseButton")
      .value("LEFT", inputtino::Mouse::MOUSE_BUTTON::LEFT)
      .value("MIDDLE", inputtino::Mouse::MOUSE_BUTTON::MIDDLE)
      .value("RIGHT", inputtino::Mouse::MOUSE_BUTTON::RIGHT)
      .value("SIDE", inputtino::Mouse::MOUSE_BUTTON::SIDE)
      .value("EXTRA", inputtino::Mouse::MOUSE_BUTTON::EXTRA);

  // Keyboard
  py::class_<inputtino::Keyboard, inputtino::VirtualDevice>(m, "Keyboard")
      .def_static("create", &inputtino::Keyboard::create)
      .def("press", &inputtino::Keyboard::press)
      .def("release", &inputtino::Keyboard::release);

  // Trackpad
  py::class_<inputtino::Trackpad, inputtino::VirtualDevice>(m, "Trackpad")
      .def_static("create", &inputtino::Trackpad::create)
      .def("place_finger", &inputtino::Trackpad::place_finger)
      .def("release_finger", &inputtino::Trackpad::release_finger)
      .def("set_left_btn", &inputtino::Trackpad::set_left_btn);

  // Joypad base class
  py::class_<inputtino::Joypad, inputtino::VirtualDevice>(m, "Joypad")
      .def("set_pressed_buttons", &inputtino::Joypad::set_pressed_buttons)
      .def("set_triggers", &inputtino::Joypad::set_triggers)
      .def("set_stick", &inputtino::Joypad::set_stick);

  py::enum_<inputtino::Joypad::CONTROLLER_BTN>(m, "ControllerButton")
      .value("DPAD_UP", inputtino::Joypad::CONTROLLER_BTN::DPAD_UP)
      .value("DPAD_DOWN", inputtino::Joypad::CONTROLLER_BTN::DPAD_DOWN)
      .value("DPAD_LEFT", inputtino::Joypad::CONTROLLER_BTN::DPAD_LEFT)
      .value("DPAD_RIGHT", inputtino::Joypad::CONTROLLER_BTN::DPAD_RIGHT)
      .value("START", inputtino::Joypad::CONTROLLER_BTN::START)
      .value("BACK", inputtino::Joypad::CONTROLLER_BTN::BACK)
      .value("HOME", inputtino::Joypad::CONTROLLER_BTN::HOME)
      .value("LEFT_STICK", inputtino::Joypad::CONTROLLER_BTN::LEFT_STICK)
      .value("RIGHT_STICK", inputtino::Joypad::CONTROLLER_BTN::RIGHT_STICK)
      .value("LEFT_BUTTON", inputtino::Joypad::CONTROLLER_BTN::LEFT_BUTTON)
      .value("RIGHT_BUTTON", inputtino::Joypad::CONTROLLER_BTN::RIGHT_BUTTON)
      .value("A", inputtino::Joypad::CONTROLLER_BTN::A)
      .value("B", inputtino::Joypad::CONTROLLER_BTN::B)
      .value("X", inputtino::Joypad::CONTROLLER_BTN::X)
      .value("Y", inputtino::Joypad::CONTROLLER_BTN::Y);

  py::enum_<inputtino::Joypad::STICK_POSITION>(m, "StickPosition")
      .value("RS", inputtino::Joypad::STICK_POSITION::RS)
      .value("LS", inputtino::Joypad::STICK_POSITION::LS);

  // PS5 Joypad
  py::class_<inputtino::PS5Joypad, inputtino::Joypad>(m, "PS5Joypad")
      .def_static("create", &inputtino::PS5Joypad::create)
      .def("get_mac_address", &inputtino::PS5Joypad::get_mac_address)
      .def("get_sys_nodes", &inputtino::PS5Joypad::get_sys_nodes)
      .def("place_finger", &inputtino::PS5Joypad::place_finger)
      .def("release_finger", &inputtino::PS5Joypad::release_finger)
      .def("set_motion", &inputtino::PS5Joypad::set_motion)
      .def("set_battery", &inputtino::PS5Joypad::set_battery)
      .def("set_on_rumble", &inputtino::PS5Joypad::set_on_rumble)
      .def("set_on_led", &inputtino::PS5Joypad::set_on_led);

  py::enum_<inputtino::PS5Joypad::MOTION_TYPE>(m, "PS5MotionType")
      .value("ACCELERATION", inputtino::PS5Joypad::MOTION_TYPE::ACCELERATION)
      .value("GYROSCOPE", inputtino::PS5Joypad::MOTION_TYPE::GYROSCOPE);

  py::enum_<inputtino::PS5Joypad::BATTERY_STATE>(m, "PS5BatteryState")
      .value("BATTERY_DISCHARGING",
             inputtino::PS5Joypad::BATTERY_STATE::BATTERY_DISCHARGING)
      .value("BATTERY_CHARGING",
             inputtino::PS5Joypad::BATTERY_STATE::BATTERY_CHARGHING)
      .value("BATTERY_FULL", inputtino::PS5Joypad::BATTERY_STATE::BATTERY_FULL)
      .value("VOLTAGE_OR_TEMPERATURE_OUT_OF_RANGE",
             inputtino::PS5Joypad::BATTERY_STATE::
                 VOLTAGE_OR_TEMPERATURE_OUT_OF_RANGE)
      .value("TEMPERATURE_ERROR",
             inputtino::PS5Joypad::BATTERY_STATE::TEMPERATURE_ERROR)
      .value("CHARGING_ERROR",
             inputtino::PS5Joypad::BATTERY_STATE::CHARGHING_ERROR);
}
