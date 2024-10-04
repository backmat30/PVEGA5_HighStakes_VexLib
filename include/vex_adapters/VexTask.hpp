#ifndef __VEX_TASK_HPP__
#define __VEX_TASK_HPP__

#include <memory>

#include "pvegas/rtos/ITask.hpp"
#include "vex_thread.h"

namespace vex_adapters {
class VexTask : public pvegas::rtos::ITask {
 private:
  // the task being wrapped
  std::unique_ptr<vex::thread> task{};

 public:
  // start the task with the given function and parameters
  void start(int (*function)(void *), void *params) override;

  // wait for the task to finish to continue
  void join() override;
};
}  // namespace vex_adapters
#endif