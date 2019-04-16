#include <mq_sensor.hpp>

int main(void) {
  // to do remove floats (possible fix is factor 1000 everything)


  // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
    auto mq_pin = hwlib::target::pin_adc(hwlib::target::ad_pins::a0);
    int ro = 5; //found in datasheet
    float ro_clean_air_factor = 9.83; // see datasheet air line

    std::array<float, 3> gas_lpg = {2.30, 0.48, -0.37}; // somewhere in the datasheet, log table
    mq_sensor_c mq_2(mq_pin, ro, ro_clean_air_factor, gas_lpg);
    
    hwlib::cout << "start heating" << '\n';
    hwlib::wait_ms(20'000); // the module needs to heat up!
    hwlib::cout << "done heating" << '\n';

    hwlib::cout << "calibrate result: " << static_cast<int>(mq_2.calibrate(10, 500)) << '\n';
    hwlib::cout << "read result: " << static_cast<int>(mq_2.read(50, 500)) << '\n';

    
}