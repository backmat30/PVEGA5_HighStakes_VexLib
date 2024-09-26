#ifndef __E_CONTROLLER_DIGITAL_HPP__
#define __E_CONTROLLER_DIGITAL_HPP__
namespace pvegas {
namespace op_control {
enum class EControllerDigital {
  BUTTON_A,
  BUTTON_B,
  BUTTON_X,
  BUTTON_Y,
  DPAD_DOWN,
  DPAD_LEFT,
  DPAD_UP,
  DPAD_RIGHT,
  TRIGGER_LEFT_TOP,
  TRIGGER_LEFT_BOTTOM,
  TRIGGER_RIGHT_TOP,
  TRIGGER_RIGHT_BOTTOM,
  NONE
};
} // namespace io
} // namespace pvegas
#endif