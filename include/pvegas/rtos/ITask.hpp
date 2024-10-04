#ifndef __I_TASK_HPP__
#define __I_TASK_HPP__

namespace pvegas {
namespace rtos {
class ITask {
 public:
  virtual ~ITask() = 0;

  // starts a task using the provided function and given parameters
  virtual void start(int (*function)(void *), void *params) = 0;

  // pauses other tasks until this task is done
  virtual void join() = 0;
};
}  // namespace rtos
}  // namespace pvegas
#endif