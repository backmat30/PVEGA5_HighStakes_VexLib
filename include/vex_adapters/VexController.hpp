#ifndef __VEX_CONTROLLER_HPP__
#define __VEX_CONTROLLER_HPP__

#include <map>
#include <memory>
#include <vector>

#include "pvegas/io/IController.hpp"
#include "vex_controller.h"
#include "vex_thread.h"
#include "vex_timer.h"

namespace vex_adapters {
class VexController : public pvegas::io::IController {
 private:
  // delay for the task loop
  static constexpr uint8_t TASK_DELAY{10};

  // rate the rumble refreshes at
  static constexpr uint8_t RUMBLE_REFRESH_RATE{50};

  // max rumble pattern length
  static constexpr uint8_t MAX_RUMBLE_LENGTH{8};

  // conversion from vex controller output to a percentage
  static constexpr double ANALOG_CONVERSION{1.0 / 127};

  // repeatedly refresh the controller
  static void taskLoop(void *params);

  // controller being wrapped
  std::unique_ptr<vex::controller> m_controller{};

  // maps custom analog button enumerations to vex analog button enumerations
  std::map<pvegas::op_control::EControllerAnalog, vex::controller::axis>
      analog_map{};

  // maps custom digital button enumerations to vex digital button enumerations
  std::map<pvegas::op_control::EControllerDigital, vex::controller::button>
      digital_map{};

  // maps custom digital button enumerations to whether they are being pressed
  std::map<pvegas::op_control::EControllerDigital, bool> buttonPressedMap{
      {pvegas::op_control::EControllerDigital::BUTTON_A, false},
      {pvegas::op_control::EControllerDigital::BUTTON_B, false},
      {pvegas::op_control::EControllerDigital::BUTTON_X, false},
      {pvegas::op_control::EControllerDigital::BUTTON_Y, false},
      {pvegas::op_control::EControllerDigital::DPAD_DOWN, false},
      {pvegas::op_control::EControllerDigital::DPAD_LEFT, false},
      {pvegas::op_control::EControllerDigital::DPAD_UP, false},
      {pvegas::op_control::EControllerDigital::DPAD_RIGHT, false},
      {pvegas::op_control::EControllerDigital::TRIGGER_LEFT_TOP, false},
      {pvegas::op_control::EControllerDigital::TRIGGER_LEFT_BOTTOM, false},
      {pvegas::op_control::EControllerDigital::TRIGGER_RIGHT_TOP, false},
      {pvegas::op_control::EControllerDigital::TRIGGER_RIGHT_BOTTOM, false}};

  std::vector<pvegas::op_control::EControllerDigital> digital_pressed{};
      // mutex object
      vex::mutex mutex{};

  // current rumble pattern
  char rumble_pattern[MAX_RUMBLE_LENGTH]{};

  // boolean to show if there is a new rumble pattern defined
  bool new_rumble_pattern{};

  // stores the time that the rumble was last changed
  uint32_t last_rumble_refresh{};

  void updateRumble();

  void taskUpdate();

 public:
  // creates a new VexController using a vex controller
  VexController(std::unique_ptr<vex::controller> &controller);

  // initialize the controller
  void init() override;

  // runs the controller
  void run() override;

  // gets the value of an analog input
  double getAnalog(pvegas::op_control::EControllerAnalog channel) override;

  // returns true if the specified button is pressed
  bool getDigital(pvegas::op_control::EControllerDigital channel) override;

  // returns true of the specified button changes from not pressed to pressed
  bool getNewDigital(pvegas::op_control::EControllerDigital channel) override;

  // rumbles the controller
  void rumble(std::string pattern) override;
};
}  // namespace vex_adapters
#endif