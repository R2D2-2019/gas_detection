#include <hwlib.hpp>
#include <cmath>

class mq_sensor_c{
private:
  hwlib::target::pin_adc & adc_pin;
  int rl; //load resistor
  int ro;
  float ro_clean_air_factor;
  std::array<float, 3> curve;
  
  float resistance_calculation(int raw_adc);

public:
  mq_sensor_c(hwlib::target::pin_adc & adc_pin, int rl, float ro_clean_air_factor, std::array<float, 3> curve);
  float calibrate(int sample_times, int interval_wait_ms);
  float read(int sample_time, int interval_wait_ms);

};

mq_sensor_c::mq_sensor_c(hwlib::target::pin_adc & adc_pin, int rl, float ro_clean_air_factor, std::array<float, 3> curve):
adc_pin(adc_pin),
rl(rl),
ro_clean_air_factor(ro_clean_air_factor),
curve(curve)
{}


float mq_sensor_c::calibrate(int sample_times, int interval_wait_ms){
  float val = 0;
  for(int i = 0; i < sample_times; i++){
    val += resistance_calculation(adc_pin.read());
    hwlib::wait_ms(interval_wait_ms);
  }
  val = val/sample_times;
  val = val/ro_clean_air_factor;
  ro = val;
  return val;

};

float mq_sensor_c::resistance_calculation(int raw_adc){
  // example
  // 10*(4095 - 437) / 437 = 83.7
  return static_cast<float>(rl*(4095-raw_adc)/raw_adc); // 4095 == max adc
};

// return rs
float mq_sensor_c::read(int sample_times, int interval_wait_ms){
  float rs = 0;
  for(int i = 0; i < sample_times; i++)
  {
    auto test = resistance_calculation(adc_pin.read());
    rs += test;
    hwlib::wait_ms(interval_wait_ms);
  }

  rs = rs/sample_times;
  float rs_ro = rs/ro;

  return (pow(10, (((log(rs_ro) - curve[1]) / curve[2]) + curve[0])));
}




int main(void) {
  // to do remove floats (possible fix is factor 1000 everything)


  // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
    auto mq_pin = hwlib::target::pin_adc(hwlib::target::ad_pins::a0);
    int ro = 5; //10k ohm? on board can't measure it
    float ro_clean_air_factor = 9.83; // see datasheet air line?

    std::array<float, 3> gas_lpg = {2.30,0.21,-0.47}; // somewhere in the datasheet?
    mq_sensor_c mq_2(mq_pin, ro, ro_clean_air_factor, gas_lpg);
    
    hwlib::cout << "start heating" << '\n';
    hwlib::wait_ms(20'000); // the module needs to heat up!
    hwlib::cout << "done heating" << '\n';

    hwlib::cout << "calibrate result: " << static_cast<int>(mq_2.calibrate(10, 500) * 1000) << '\n';
    hwlib::cout << "read result: " << static_cast<int>(mq_2.read(50, 500) * 1000) << '\n';

    
}