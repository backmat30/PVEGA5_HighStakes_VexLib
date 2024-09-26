#ifndef __ROBOT_HPP__
#define __ROBOT_HPP__
#include "subsystems/ASubsystem.hpp"
#include <memory>
#include <string>
#include <vector>
namespace pvegas {
namespace robot {
class Robot {
private:
  std::vector<std::unique_ptr<ASubsystem>> subsystems{};

public:
  void addSubsystem(std::unique_ptr<ASubsystem> &subsystem);

  bool removeSubsystem(std::string subsystem);

  void init();

  void run();

  void sendCommand(std::string subsystem_name, std::string command_name, ...);

  void *getState(std::string subsystem_name, std::string state_name);
};
} // namespace robot
} // namespace pvegas
#endif