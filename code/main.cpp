#include <mq_sensor.hpp>


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
    std::array<float, 3> co_gas_curve = {2.30, 0.72, -0.34}; //log table for co gas, reference to datasheet
    mq_sensors_gas_curve_s co;
    co.gas_id = co_gas_id;
    co.gas_curve = co_gas_curve;

    constexpr int lpg_gas_id = 0;
    std::array<float, 3> gas_lpg = {2.30, 0.72, -0.34}; //log table for LPG gas, reference to datasheet
    mq_sensors_gas_curve_s lpg;
    lpg.gas_id = lpg_gas_id;
    lpg.gas_curve = gas_lpg;

    constexpr int smoke_gas_id = 2;
    std::array<float, 3> gas_smoke = {2.3, 0.53, -0.44}; //log table for smoke
    mq_sensors_gas_curve_s smoke;
    smoke.gas_id = smoke_gas_id;
    smoke.gas_curve = gas_smoke;

    constexpr int gasses_amount = 3;
    
    std::array<mq_sensors_gas_curve_s, gasses_amount> mq_2_gasses = {co, lpg, smoke};

    mq_sensor_c<gasses_amount> mq_2(mq_pin, rl, ro_clean_air_factor, mq_2_gasses);

    
    hwlib::cout << "start heating" << '\n';
    //hwlib::wait_ms(20'000); // the module needs to heat up!
    hwlib::cout << "done heating" << '\n';

    hwlib::cout << "calibrate result: " << static_cast<int>(mq_2.calibrate(10, 500)) << '\n';
    for(;;){
        hwlib::cout << mq_2.get(1, 20) << '\n';
        //hwlib::cout << "get result: " << mq_pin.read() << '\n';
    }
}