#pragma once
#include <array>

namespace r2d2::gas {
    class gas_sensor_interface_c{
    private:

    public:
        gas_sensor_interface_c(){}
        virtual std::array<int, 5> get();       //temporary, return type will be changed soon. 
        virtual void calibrate();
          
    };


}