#include "vex_adapters/VexController.hpp"

namespace vex_adapters {

void VexController::taskLoop(void *params) {
  // define the controller from the params
  VexController *controller{static_cast<VexController *>(params)};

  // update the controller on loop
  while (true) {
    controller->taskUpdate();
    vex::this_thread::sleep_for(TASK_DELAY);
  }
}

void VexController::updateRumble() {
  // get current system timer
  uint32_t time{vex::timer::system()};

  // checks if a new rumble request has been made
  // checks if there has been enough time since last update
  if (new_rumble_pattern && time - last_rumble_refresh >= RUMBLE_REFRESH_RATE) {
    // validate the controller and rumble it
    if (m_controller) {
      m_controller->rumble(rumble_pattern);
    }

    // reset new rumble pattern flag and the time of last refresh
    new_rumble_pattern = false;
    last_rumble_refresh = time;
  }
}

void VexController::taskUpdate() {
  // blocks other processes while the controller updates
  mutex.lock();
  // update rumble
  updateRumble();
  // update list of pressed buttons
  for (uint8_t i{0}; i < digital_pressed.size(); i++) {
    // if the button is no longer pressed, remove it from the vector and
    // decrement i
    if (!digital_map.at(digital_pressed.at(i)).pressing()) {
      digital_pressed.erase(digital_pressed.begin() + i);
      i--;
    }
  }
  mutex.unlock();
}

VexController::VexController(std::unique_ptr<vex::controller> &controller)
    : m_controller{std::move(controller)},
      analog_map{{pvegas::op_control::EControllerAnalog::JOYSTICK_LEFT_X,
                  m_controller->Axis4},
                 {pvegas::op_control::EControllerAnalog::JOYSTICK_LEFT_Y,
                  m_controller->Axis3},
                 {pvegas::op_control::EControllerAnalog::JOYSTICK_RIGHT_X,
                  m_controller->Axis1},
                 {pvegas::op_control::EControllerAnalog::JOYSTICK_RIGHT_Y,
                  m_controller->Axis2}},
      digital_map{{pvegas::op_control::EControllerDigital::BUTTON_A,
                   m_controller->ButtonA},
                  {pvegas::op_control::EControllerDigital::BUTTON_B,
                   m_controller->ButtonB},
                  {pvegas::op_control::EControllerDigital::BUTTON_X,
                   m_controller->ButtonX},
                  {pvegas::op_control::EControllerDigital::BUTTON_Y,
                   m_controller->ButtonY},
                  {pvegas::op_control::EControllerDigital::DPAD_DOWN,
                   m_controller->ButtonDown},
                  {pvegas::op_control::EControllerDigital::DPAD_LEFT,
                   m_controller->ButtonLeft},
                  {pvegas::op_control::EControllerDigital::DPAD_UP,
                   m_controller->ButtonUp},
                  {pvegas::op_control::EControllerDigital::DPAD_RIGHT,
                   m_controller->ButtonRight},
                  {pvegas::op_control::EControllerDigital::TRIGGER_LEFT_TOP,
                   m_controller->ButtonL1},
                  {pvegas::op_control::EControllerDigital::TRIGGER_LEFT_BOTTOM,
                   m_controller->ButtonL2},
                  {pvegas::op_control::EControllerDigital::TRIGGER_RIGHT_TOP,
                   m_controller->ButtonR1},
                  {pvegas::op_control::EControllerDigital::TRIGGER_RIGHT_BOTTOM,
                   m_controller->ButtonR2}} {}

void VexController::init() {}

void VexController::run() {
  // starts a new background thread that runs the task loop for this controller
  vex::thread controller_task{&VexController::taskLoop, this};
}

double VexController::getAnalog(pvegas::op_control::EControllerAnalog channel) {
  double value{};

  // if the channel exists in the map and the controller exists, take the value
  if (analog_map.count(channel) > 0) {
    if (m_controller) {
      value = analog_map.at(channel).value();
    }
  }

  return value;
}

bool VexController::getDigital(pvegas::op_control::EControllerDigital channel) {
  bool value{};

  // if the channel exists in the map and the controller exists, take the value
  if (digital_map.count(channel) > 0) {
    if (m_controller) {
      value = digital_map.at(channel).pressing();
    }
  }

  return value;
}

bool VexController::getNewDigital(
    pvegas::op_control::EControllerDigital channel) {
  bool value{};
  // if the channel exists in the map and the controller exists, check for a new
  // press
  if (digital_map.count(channel) > 0) {
    if (m_controller) {
      // defaults value to the state of the button
      value = digital_map.at(channel).pressing();
      // checks if the channel is already pressed, if so, override value to
      // false
      for (pvegas::op_control::EControllerDigital button : digital_pressed) {
        if (button == channel) {
          value = false;
        }
      }
    }
  }
  // if value is true, there is a new press for channel, so add the channel to
  // the list of pressed buttons
  if (value) {
    digital_pressed.push_back(channel);
  }
  return value;
}

void VexController::rumble(std::string pattern){
    // takes the mutex
    mutex.lock();
    //copies the rumble pattern
    for(uint8_t i{0}; i < MAX_RUMBLE_LENGTH; ++i){
        rumble_pattern[i] = pattern[i];
    }
    //changes the new rumble flag
    new_rumble_pattern = true;
    // gives back the mutex
    mutex.unlock();
}
}  // namespace vex_adapters