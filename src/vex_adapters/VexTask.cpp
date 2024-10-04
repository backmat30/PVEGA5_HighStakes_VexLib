#include "vex_adapters/VexTask.hpp"

namespace vex_adapters {
void VexTask::start(int (*function)(void *), void *params) {
  task = std::unique_ptr<vex::thread>(new vex::thread(function, params));
}

void VexTask::join() {
  if (task) {
    task->join();
  }
}
}  // namespace vex_adapters