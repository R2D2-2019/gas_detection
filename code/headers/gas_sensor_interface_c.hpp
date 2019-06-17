#pragma once
#include <array>
#include <gas_s.hpp>

namespace r2d2::gas_detection {

    /**
     * Class gas_sensor_interface_c provides an interface of all the gas
     * sensors.
     */
    template <int AmountOfGasses>
    class gas_sensor_interface_c {
    public:
        gas_sensor_interface_c() {
        }

        /**
         *  This function gets the return value from the gas sensor.
         *  This can be either a PPM value or a ml/L.
         *
         * @internal
         * @return
         */
        virtual std::array<r2d2::gas_detection::gas_s, AmountOfGasses>
        get() = 0;

        /**
         * This function calibrates the sensor.
         */
        virtual void calibrate() = 0;
    };

} // namespace r2d2::gas_detection