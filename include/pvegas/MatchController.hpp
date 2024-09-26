#ifndef __MATCHCONTROLLER_HPP__
#define __MATCHCONTROLLER_HPP__

// includes
#include "control/ControlSystem.hpp"
#include "menu/IMenu.hpp"
#include "pvegas/io/IController.hpp"
#include "pvegas/robot/Robot.hpp"
#include "pvegas/rtos/IClock.hpp"
#include "pvegas/rtos/IDelayer.hpp"
#include "pvegas/OpControlManager.hpp"
#include <memory>

namespace pvegas {
class MatchController {
private:
  static constexpr uint32_t MENU_DELAY{10};

  std::unique_ptr<menu::IMenu> m_menu{};

  std::shared_ptr<rtos::IClock> m_clock{};

  std::unique_ptr<rtos::IDelayer> m_delayer{};

  OpControlManager op_control_manager{m_clock, m_delayer};

  std::shared_ptr<control::ControlSystem> control_system{};

  std::shared_ptr<io::IController> controller{};

  std::shared_ptr<robot::Robot> robot{};

public:
  MatchController(std::unique_ptr<menu::IMenu> &new_menu,
                  std::shared_ptr<rtos::IClock> &clock,
                  std::unique_ptr<rtos::IDelayer> &delayer);

  void init(bool fast_init);

  void disabled();

  void competitionInit();

  void autonomous();

  void operatorControl();
};
} // namespace pvegas
#endif