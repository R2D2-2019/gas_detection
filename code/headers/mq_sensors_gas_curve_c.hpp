#pragma once
#include <array>

namespace r2d2::gas_detection{

    class mq_sensors_gas_curve_c{
        private:
            int gas_id;
            std::array<float, 3> gas_curve = {};
        public:
            mq_sensors_gas_curve_c(const int & gas_id, const std::array<float, 3> &gas_curve);
            mq_sensors_gas_curve_c();

            void set_gas_id(const int & gas_id_new);
            void set_gas_curve(const std::array<float, 3> & gas_curve_new);
            int get_gas_id();
            float get_gas_curve(const int & index);
    };

    
} // namespace r2d2::gas_detection{
