#ifndef __VEX_CLOCK_HPP__
#define __VEX_CLOCK_HPP__

#include "pvegas/rtos/IClock.hpp"
#include "vex_timer.h"

#include <memory>
#include <cstdint>

namespace vex_adapters{
    class VexClock : public pvegas::rtos::IClock{
        private:
        // timer being wrapped
        std::unique_ptr<vex::timer> m_timer{};
        public:
        // copy constructor
        VexClock(VexClock& other);

        // clones the clock object
        std::unique_ptr<pvegas::rtos::IClock> clone() override;

        // gets the current system time
        uint32_t getTime() override;
    };
}
#endif