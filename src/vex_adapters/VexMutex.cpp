#include "vex_adapters/VexMutex.hpp"

namespace vex_adapters{
    void VexMutex::take() {
        mutex.lock();
    }

    void VexMutex::give() {
        mutex.unlock();
    }
}