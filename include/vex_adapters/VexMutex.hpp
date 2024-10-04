#ifndef __VEX_MUTEX_HPP__
#define __VEX_MUTEX_HPP__

#include "pvegas/rtos/IMutex.hpp"
#include "vex_thread.h"

namespace vex_adapters {
class VexMutex : public pvegas::rtos::IMutex {
    private:
    // the mutex being wrapped
    vex::mutex mutex{};

    public:
    // takes the mutex
    void take() override;

    // gives back the mutex
    void give() override;
};
}  // namespace vex_adapters
#endif