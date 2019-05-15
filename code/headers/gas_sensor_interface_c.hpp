#pragma once
#include <array>
#include <gas_s.hpp>

namespace r2d2::gas_detection {

    /**
     * Class gas_sensor_interface_base_c is needed to create an array of gas_sensor_interface_c instances. 
     * We cant do this directly because gas_sensor_interface_c is an templated class.
     */
    class gas_sensor_interface_base_c {
        virtual void calibrate();

    };

    /**
     * Class gas_sensor_interface_c provides an interface of all the gas sensors. 
     *  
     */
    template<int AmountOfGasses>
    class gas_sensor_interface_c : public gas_sensor_interface_base_c {
    public:
        gas_sensor_interface_c(){}

        /**
         *  This funtion gets the return value from the gas sensor.
         *  This can be either a PPM value or a ml/L.
         * 
         * @internal
         * @return
         */
        virtual std::array<r2d2::gas_detection::gas_s, AmountOfGasses> get(); 

        /**
         * This function calibrates the sensor.
         */
        virtual void calibrate(); 
          
    };

}