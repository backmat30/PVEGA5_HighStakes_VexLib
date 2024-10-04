#ifndef __VEX_DELAYER_HPP__
#define __VEX_DELAYER_HPP__

#include "vex_thread.h"
#include "pvegas/rtos/IDelayer.hpp"
#include <memory>

namespace vex_adapters {
class VexDelayer : public pvegas::rtos::IDelayer {
 private:
  // copy constructor for cloning
  VexDelayer(VexDelayer& other);

 public:
  // clone this delayer
  std::unique_ptr<pvegas::rtos::IDelayer> clone() override;

  // delay the task for given milliseconds
  void delay(uint32_t millis) override;

  // delay until the system time reaches the specified time
  void delayUntil(uint32_t time) override;
};
}  // namespace vex_adapters
#endif