#include "vex_adapters/VexClock.hpp"

namespace vex_adapters
{
    VexClock::VexClock(VexClock& other) : m_timer{new vex::timer}
    {
        *m_timer.get() = other.m_timer.get()->value();
    }
    std::unique_ptr<pvegas::rtos::IClock> VexClock::clone()
    {
        return std::unique_ptr<pvegas::rtos::IClock>(new VexClock(*this));
    }

    uint32_t VexClock::getTime() { return m_timer->time(); };
}