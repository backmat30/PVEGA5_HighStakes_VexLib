#include "pvegas/profiles/DefaultProfile.hpp"

namespace pvegas{
    namespace profiles{
        std::string DefaultProfile::getName(){
            return PROFILE_NAME;
        }

        int DefaultProfile::getControlMode(op_control::EControlType control_type) const{
            int mode{};
            if(CONTROL_MODE_MAP.count(control_type) > 0){
                mode = CONTROL_MODE_MAP.at(control_type);
            }
            return mode;
        }

        void DefaultProfile::setControlMode(op_control::EControlType control_type, int control_mode){
            CONTROL_MODE_MAP[control_type] = control_mode;
        }

        op_control::EControllerAnalog DefaultProfile::getAnalogControlMapping(op_control::EControl control) const{
            op_control::EControllerAnalog analogMapping{op_control::EControllerAnalog::NONE};
            if(ANALOG_CONTROL_MAP.count(control) > 0){
                analogMapping = ANALOG_CONTROL_MAP.at(control);
            }
            return analogMapping;
        }

        op_control::EControllerDigital DefaultProfile::getDigitalControlMapping(op_control::EControl control) const{
            op_control::EControllerDigital digitalMapping{op_control::EControllerDigital::NONE};
            if(DIGITAL_CONTROL_MAP.count(control) > 0){
                digitalMapping = DIGITAL_CONTROL_MAP.at(control);
            }
            return digitalMapping;
        }
    }
}