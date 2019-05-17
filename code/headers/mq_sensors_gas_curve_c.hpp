#pragma once
#include <array>

namespace r2d2::gas_detection{
/**
 * Class mq_sensors_gas_curve_c provides the ability to create gas_curves for the mq_sensor.
 * Each gas has its own logarithmic curve.
 * The first 2 values are points on the curve, the 3rd value is the slope increment.
 * @return
 */
    class mq_sensors_gas_curve_c{
        private:
            int gas_id;
            std::array<float, 3> gas_curve = {};
        public:
            mq_sensors_gas_curve_c(const int & gas_id, const std::array<float, 3> &gas_curve);
            mq_sensors_gas_curve_c();
            /**
            * This functions sets the gas_id for a specific gas curve.
            * @return
            */
            void set_gas_id(const int & gas_id_new);
            /**
            * This functions sets the gas_curve values for a specific gas curve.
            * @return
            */
            void set_gas_curve(const std::array<float, 3> & gas_curve_new);
            /**
            * This functions returns the gas_id.
            * @return
            */
            int get_gas_id();
            /**
            * This functions returns the specific value(specified by the index) of a gas_curve.
            * @return
            */
            float get_gas_curve(const int & index);
    };

    
} // namespace r2d2::gas_detection{
