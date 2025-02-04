// Copyright 2025 Geson-anko
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <inputtino/input.hpp>

namespace py = pybind11;

// Define a custom exception for inputtino errors
class InputtinoError : public std::runtime_error {
 public:
  explicit InputtinoError(const std::string& msg) : std::runtime_error(msg) {}
};

// Helper function to convert Result to Python-friendly return values
template <typename T>
T unwrap_result(const inputtino::Result<T>& result) {
  if (!result) {
    throw InputtinoError(result.getErrorMessage());
  }
  return std::move(*result);
}

PYBIND11_MODULE(_core, m) {
  m.doc() = "pybind inputtino module!";

  // Register our custom exception
  py::register_exception<InputtinoError>(m, "InputtinoError");

  // DeviceDefinition remains unchanged
  py::class_<inputtino::DeviceDefinition>(m, "DeviceDefinition")
      .def(py::init<>())
      .def_readwrite("name", &inputtino::DeviceDefinition::name)
      .def_readwrite("vendor_id", &inputtino::DeviceDefinition::vendor_id)
      .def_readwrite("product_id", &inputtino::DeviceDefinition::product_id)
      .def_readwrite("version", &inputtino::DeviceDefinition::version)
      .def_readwrite("device_phys", &inputtino::DeviceDefinition::device_phys)
      .def_readwrite("device_uniq", &inputtino::DeviceDefinition::device_uniq);

  // VirtualDevice remains unchanged
  py::class_<inputtino::VirtualDevice>(m, "VirtualDevice")
      .def("get_nodes", &inputtino::VirtualDevice::get_nodes);

  // Mouse with proper Result handling and nested enum
  auto mouse =
      py::class_<inputtino::Mouse, inputtino::VirtualDevice>(m, "Mouse")
          .def_static(
              "create",
              [](const inputtino::DeviceDefinition& def) {
                auto result = inputtino::Mouse::create(def);
                return unwrap_result(result);
              },
              py::arg("device") =
                  inputtino::DeviceDefinition{
                      .name = "Wolf mouse virtual device",
                      .vendor_id = 0xAB00,
                      .product_id = 0xAB01,
                      .version = 0xAB00})
          .def("move", &inputtino::Mouse::move)
          .def("move_abs", &inputtino::Mouse::move_abs)
          .def("press", &inputtino::Mouse::press)
          .def("release", &inputtino::Mouse::release)
          .def("vertical_scroll", &inputtino::Mouse::vertical_scroll)
          .def("horizontal_scroll", &inputtino::Mouse::horizontal_scroll);

  // Define MouseButton as a nested enum
  py::enum_<inputtino::Mouse::MOUSE_BUTTON>(mouse, "Button")
      .value("LEFT", inputtino::Mouse::MOUSE_BUTTON::LEFT)
      .value("MIDDLE", inputtino::Mouse::MOUSE_BUTTON::MIDDLE)
      .value("RIGHT", inputtino::Mouse::MOUSE_BUTTON::RIGHT)
      .value("SIDE", inputtino::Mouse::MOUSE_BUTTON::SIDE)
      .value("EXTRA", inputtino::Mouse::MOUSE_BUTTON::EXTRA);

  // Keyboard with Result handling
  py::class_<inputtino::Keyboard, inputtino::VirtualDevice>(m, "Keyboard")
      .def_static(
          "create",
          [](const inputtino::DeviceDefinition& def, int millis_repress_key) {
            auto result = inputtino::Keyboard::create(def, millis_repress_key);
            return unwrap_result(result);
          },
          py::arg("device") =
              inputtino::DeviceDefinition{.name = "Wolf (virtual) keyboard",
                                          .vendor_id = 0xAB00,
                                          .product_id = 0xAB05,
                                          .version = 0xAB00},
          py::arg("millis_repress_key") = 50)
      .def("press", &inputtino::Keyboard::press)
      .def("release", &inputtino::Keyboard::release);

  // Trackpad with Result handling
  py::class_<inputtino::Trackpad, inputtino::VirtualDevice>(m, "Trackpad")
      .def_static(
          "create",
          [](const inputtino::DeviceDefinition& def) {
            auto result = inputtino::Trackpad::create(def);
            return unwrap_result(result);
          },
          py::arg("device") =
              inputtino::DeviceDefinition{.name = "Wolf (virtual) touchpad",
                                          .vendor_id = 0xAB00,
                                          .product_id = 0xAB02,
                                          .version = 0xAB00})
      .def("place_finger", &inputtino::Trackpad::place_finger)
      .def("release_finger", &inputtino::Trackpad::release_finger)
      .def("set_left_btn", &inputtino::Trackpad::set_left_btn);

  // Joypad base class with nested enums
  auto joypad =
      py::class_<inputtino::Joypad, inputtino::VirtualDevice>(m, "Joypad")
          .def("set_pressed_buttons", &inputtino::Joypad::set_pressed_buttons)
          .def("set_triggers", &inputtino::Joypad::set_triggers)
          .def("set_stick", &inputtino::Joypad::set_stick);

  // Define ControllerButton as a nested enum
  py::enum_<inputtino::Joypad::CONTROLLER_BTN>(joypad, "Button")
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

  // Define StickPosition as a nested enum
  py::enum_<inputtino::Joypad::STICK_POSITION>(joypad, "StickPosition")
      .value("RS", inputtino::Joypad::STICK_POSITION::RS)
      .value("LS", inputtino::Joypad::STICK_POSITION::LS);

  // PS5Joypad with Result handling and nested enums
  auto ps5_joypad =
      py::class_<inputtino::PS5Joypad, inputtino::Joypad>(m, "PS5Joypad")
          .def_static(
              "create",
              [](const inputtino::DeviceDefinition& def) {
                auto result = inputtino::PS5Joypad::create(def);
                return unwrap_result(result);
              },
              py::arg("device") =
                  inputtino::DeviceDefinition{
                      .name = "Wolf DualSense (virtual) pad",
                      .vendor_id = 0x054C,
                      .product_id = 0x0CE6,
                      .version = 0x8111})
          .def("get_mac_address", &inputtino::PS5Joypad::get_mac_address)
          .def("get_sys_nodes", &inputtino::PS5Joypad::get_sys_nodes)
          .def("place_finger", &inputtino::PS5Joypad::place_finger)
          .def("release_finger", &inputtino::PS5Joypad::release_finger)
          .def("set_motion", &inputtino::PS5Joypad::set_motion)
          .def("set_battery", &inputtino::PS5Joypad::set_battery)
          .def("set_on_rumble", &inputtino::PS5Joypad::set_on_rumble)
          .def("set_on_led", &inputtino::PS5Joypad::set_on_led);

  // Define PS5 specific enums as nested types
  py::enum_<inputtino::PS5Joypad::MOTION_TYPE>(ps5_joypad, "MotionType")
      .value("ACCELERATION", inputtino::PS5Joypad::MOTION_TYPE::ACCELERATION)
      .value("GYROSCOPE", inputtino::PS5Joypad::MOTION_TYPE::GYROSCOPE);

  py::enum_<inputtino::PS5Joypad::BATTERY_STATE>(ps5_joypad, "BatteryState")
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
