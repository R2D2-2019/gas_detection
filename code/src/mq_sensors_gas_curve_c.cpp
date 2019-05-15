#include <mq_sensor.hpp>
#include <array>

using namespace r2d2::gas_detection;

mq_sensors_gas_curve_c::mq_sensors_gas_curve_c(const int & gas_id, const std::array<float, 3> &gas_curve):
    gas_id (gas_id),
    gas_curve (gas_curve)
{}

mq_sensors_gas_curve_c::mq_sensors_gas_curve_c() = default;

void mq_sensors_gas_curve_c::set_gas_id(const int & gas_id_new){
    gas_id = gas_id_new;
};

void mq_sensors_gas_curve_c::set_gas_curve(const std::array<float, 3> & gas_curve_new){
    gas_curve = gas_curve_new;
}