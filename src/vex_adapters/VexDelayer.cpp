#include "vex_adapters/VexDelayer.hpp"

namespace vex_adapters {
VexDelayer::VexDelayer(VexDelayer& other) {}

std::unique_ptr<pvegas::rtos::IDelayer> VexDelayer::clone(){
    return std::unique_ptr<pvegas::rtos::IDelayer>(new VexDelayer(*this));
}

void VexDelayer::delay(uint32_t millis){
    vex::this_thread::sleep_for(millis);
}

void VexDelayer::delayUntil(uint32_t time){
    vex::this_thread::sleep_until(time);
}
}  // namespace vex_adapters