#include "pvegas/robot/subsystems/drivetrain/DirectDriveBuilder.hpp"
#include <memory>

namespace pvegas {
namespace robot {
namespace subsystems {
namespace drivetrain {
DirectDriveBuilder *DirectDriveBuilder::withLeftMotor(
    std::unique_ptr<io::IMotor> &motor) {
  m_left_motors.addMotor(motor);
  return this;
}

DirectDriveBuilder *DirectDriveBuilder::withRightMotor(
    std::unique_ptr<io::IMotor> &motor) {
  m_right_motors.addMotor(motor);
  return this;
}

DirectDriveBuilder *
DirectDriveBuilder::withVelocityToVoltage(double velocity_to_voltage) {
  m_velocity_to_voltage = velocity_to_voltage;
  return this;
}
DirectDriveBuilder *DirectDriveBuilder::withWheelRadius(double wheel_radius) {
  m_wheel_radius = wheel_radius;
  return this;
}

DirectDriveBuilder *DirectDriveBuilder::withDriveRadius(double drive_radius) {
  m_drive_radius = drive_radius;
  return this;
}

std::unique_ptr<IDrivetrain> DirectDriveBuilder::build() {
  std::unique_ptr<DirectDrive> drivetrain{std::make_unique<DirectDrive>()};
  drivetrain->setLeftMotors(m_left_motors);
  drivetrain->setRightMotors(m_right_motors);
  drivetrain->setVelocityToVoltage(m_velocity_to_voltage);
  drivetrain->setWheelRadius(m_wheel_radius);
  drivetrain->setDriveRadius(m_drive_radius);
  return drivetrain;
}
} // namespace drivetrain
} // namespace subsystems
} // namespace robot
} // namespace pvegas