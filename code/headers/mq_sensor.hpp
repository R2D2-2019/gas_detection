#pragma once
#include <cmath>
#include <hwlib.hpp>

template<int number_of_gasses>
class mq_sensor_c{
private:
  hwlib::target::pin_adc & adc_pin;
  int rl; //load resistor
  int ro;
  float ro_clean_air_factor;
  number_of_gasses, std::array<float, 3> gas_curves;
  
  int resistance_calculation(int raw_adc);

public:
  mq_sensor_c(hwlib::target::pin_adc & adc_pin, int rl, float ro_clean_air_factor, std::array<float, 3> curve);
  int calibrate(int sample_times, int interval_wait_ms);
  int read(int sample_time, int interval_wait_ms);

};