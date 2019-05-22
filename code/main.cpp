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

    r2d2::gas_detection::mq_sensors_gas_curve_c lpg(static_cast<int>(r2d2::gas_detection::gas_type::LPG));
    r2d2::gas_detection::mq_sensors_gas_curve_c co(static_cast<int>(r2d2::gas_detection::gas_type::CO));
    r2d2::gas_detection::mq_sensors_gas_curve_c smoke(static_cast<int>(r2d2::gas_detection::gas_type::SMOKE));

    constexpr int gasses_amount = 3;
    
    std::array<r2d2::gas_detection::mq_sensors_gas_curve_c, gasses_amount> mq_2_gasses = {co, lpg, smoke};

    r2d2::gas_detection::mq_sensor_c<gasses_amount> mq_2(mq_pin, mq_2_gasses);

    hwlib::cout << "start heating" << '\n';
    //hwlib::wait_ms(20'000); // the module needs to heat up!
    hwlib::cout << "done heating" << '\n';

    //hwlib::cout << "calibrate result: " << static_cast<int>(mq_2.calibrate(10, 500)) << '\n';
    mq_2.set_sample_interval_time(10, 500);
    mq_2.calibrate();
    mq_2.set_sample_interval_time(1, 20);
    for(;;){
        hwlib::cout << mq_2.get() << '\n';
        hwlib::cout << "raw value: " << mq_pin.read() << '\n';
    }
}