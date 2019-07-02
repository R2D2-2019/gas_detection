#include <array>
#include <gas_enums.hpp>
#include <mq_sensors_gas_curve_c.hpp>

namespace r2d2::gas_detection {
    mq_sensors_gas_curve_c::mq_sensors_gas_curve_c(
        const gas_type &gas_id, const std::array<float, 3> &gas_curve)
        : gas_id(gas_id), gas_curve(gas_curve) {
    }

    mq_sensors_gas_curve_c::mq_sensors_gas_curve_c(const gas_type &gas_id)
        : gas_id(gas_id) {
        gas_type gas = static_cast<gas_type>(gas_id);
        switch (gas) {
        case r2d2::gas_detection::gas_type::LPG:
            gas_curve = {2.3, 0.21, -0.47};
            break;
        case r2d2::gas_detection::gas_type::CO:
            gas_curve = {2.3, 0.72, -0.34};
            break;
        case r2d2::gas_detection::gas_type::SMOKE:
            gas_curve = {2.3, 0.53, -0.44};
            break;
        case r2d2::gas_detection::gas_type::ALCOHOL:
            gas_curve = {5.0, 0.4, -1.413};
            break;
        }
    }

    void mq_sensors_gas_curve_c::set_gas_id(const gas_type &gas_id_new) {
        gas_id = gas_id_new;
    };

    void mq_sensors_gas_curve_c::set_gas_curve(
        const std::array<float, 3> &gas_curve_new) {
        gas_curve = gas_curve_new;
    }

    gas_type mq_sensors_gas_curve_c::get_gas_id() {
        return gas_id;
    }

    float mq_sensors_gas_curve_c::get_gas_curve(const int &index) {
        return gas_curve[index];
    }
} // namespace r2d2::gas_detection
