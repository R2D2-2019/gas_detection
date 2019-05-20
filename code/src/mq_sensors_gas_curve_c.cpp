#include "mq_sensors_gas_curve_c.hpp"
#include <array>

namespace r2d2::gas_detection{
    mq_sensors_gas_curve_c::mq_sensors_gas_curve_c(const int & gas_id, const std::array<float, 3> &gas_curve)
        : gas_id (gas_id), gas_curve (gas_curve)
    {}

    mq_sensors_gas_curve_c::mq_sensors_gas_curve_c(const int & gas_id)
    : gas_id(gas_id)
    {
        if(gas_id == GasType::lpg){
            gas_curve = {2.3, 0.21,-0.47};
        }else if(gas_id == GasType::co){
            gas_curve = {2.30, 0.72, -0.34};
        }else if(gas_id == GasType::smoke){
            gas_curve = {2.3, 0.53, -0.44};
        }
    }

    void mq_sensors_gas_curve_c::set_gas_id(const int & gas_id_new){
        gas_id = gas_id_new;
    };

    void mq_sensors_gas_curve_c::set_gas_curve(const std::array<float, 3> & gas_curve_new){
        gas_curve = gas_curve_new;
    }

    int mq_sensors_gas_curve_c::get_gas_id(){
        return gas_id;
    }

    float mq_sensors_gas_curve_c::get_gas_curve(const int & index){
        return gas_curve[index];
    }
}