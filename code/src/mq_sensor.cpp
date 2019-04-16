#include <mq_sensor.hpp>


mq_sensor_c::mq_sensor_c(hwlib::target::pin_adc & adc_pin, int rl, float ro_clean_air_factor, std::array<float, 3> curve):
adc_pin(adc_pin),
rl(rl),
ro_clean_air_factor(ro_clean_air_factor),
curve(curve)
{}


int mq_sensor_c::calibrate(int sample_times, int interval_wait_ms){
  int val = 0;
  for(int i = 0; i < sample_times; i++){
    val += resistance_calculation(adc_pin.read());
    hwlib::wait_ms(interval_wait_ms);
  }
  val = val/sample_times;
  val = val/ro_clean_air_factor;
  ro = val;
  return val;

};

int mq_sensor_c::resistance_calculation(int raw_adc){
  return rl*(4095-raw_adc)/raw_adc; 
};

// return rs
int mq_sensor_c::read(int sample_times, int interval_wait_ms){
  int rs = 0;
  for(int i = 0; i < sample_times; i++)
  {
    int test = resistance_calculation(adc_pin.read());
    rs += test;
    hwlib::wait_ms(interval_wait_ms);
  }
  return static_cast<int>(pow(10, (((log((rs/sample_times)/ro) - curve[1]) / curve[2]) + curve[0])));
}