#ifndef __I_MENU_HPP__
#define __I_MENU_HPP__

#include "pvegas/SystemConfig.hpp"
#include "pvegas/configs/IConfig.hpp"
#include "pvegas/profiles/IProfile.hpp"
namespace pvegas{
    namespace menu{
        class IMenu{
            public:
            virtual ~IMenu() = default;

            virtual void display() = 0;

            virtual bool isStarted() = 0;

            virtual SystemConfig getSystemConfig(bool read_only = false) = 0;

            virtual void addConfig(std::unique_ptr<configs::IConfig>& config) = 0;

            virtual void addProfile(std::unique_ptr<profiles::IProfile>& profile) = 0;
        };
    }
}
#endif