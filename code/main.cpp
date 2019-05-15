#include <gas_sensors_c.hpp>
#include "hwlib.hpp"

template<typename T, std::size_t N>
hwlib::ostream & operator<< (hwlib::ostream & out, const std::array<T, N> & rhs)
{
    for(auto & object : rhs){
        out << object << '\n';
    }
    return out;
}

int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
    auto mq_pin = hwlib::target::pin_adc(hwlib::target::ad_pins::a0);

    int rl = 10; //found in datasheet
    float ro_clean_air_factor = 9.83; // see datasheet air line

    constexpr int co_gas_id = 1;
    std::array<float, 3> gas_co_curve = {2.30, 0.72, -0.34}; //log table for co gas, reference to datasheet
    r2d2::gas_detection::mq_sensors_gas_curve_c co(co_gas_id, gas_co_curve);

    constexpr int lpg_gas_id = 0;
    std::array<float, 3> gas_lpg_curve = {2.3, 0.21,-0.47}; //log table for LPG gas, reference to datasheet
    r2d2::gas_detection::mq_sensors_gas_curve_c lpg(lpg_gas_id, gas_lpg_curve);

    constexpr int smoke_gas_id = 2;
    std::array<float, 3> gas_smoke_curve = {2.3, 0.53, -0.44}; //log table for smoke
    r2d2::gas_detection::mq_sensors_gas_curve_c smoke(smoke_gas_id, gas_smoke_curve);

    constexpr int gasses_amount = 3;
    
    std::array<r2d2::gas_detection::mq_sensors_gas_curve_c, gasses_amount> mq_2_gasses = {co, lpg, smoke};

    r2d2::gas_detection::mq_sensor_c<gasses_amount> mq_2(mq_pin, rl, ro_clean_air_factor, mq_2_gasses);

    
    hwlib::cout << "start heating" << '\n';
    //hwlib::wait_ms(20'000); // the module needs to heat up!
    hwlib::cout << "done heating" << '\n';

    hwlib::cout << "calibrate result: " << static_cast<int>(mq_2.calibrate(10, 500)) << '\n';
    for(;;){
        hwlib::cout << mq_2.get(1, 20) << '\n';
        //hwlib::cout << "get result: " << mq_pin.read() << '\n';
    }
}