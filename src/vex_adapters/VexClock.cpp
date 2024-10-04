#include "vex_adapters/VexClock.hpp"

namespace vex_adapters
{
    VexClock::VexClock(VexClock &other) {}

    std::unique_ptr<pvegas::rtos::IClock> VexClock::clone()
    {
        return std::unique_ptr<pvegas::rtos::IClock>(new VexClock(*this));
    }

    uint32_t VexClock::getTime() { return vex::timer::system(); };
}