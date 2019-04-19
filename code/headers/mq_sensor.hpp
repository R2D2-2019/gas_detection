#pragma once
#include <cmath>
#include <hwlib.hpp>


struct gas{
  int gas_id, value;

  friend hwlib::ostream & operator<< (hwlib::ostream &out, const gas &g){
    return out << "gas_id: " << g.gas_id << " value: " << g.value;
  }

};

struct mq_sensors_gas_curve{
  int gas_id;
  std::array<float, 3> gas_curve = {};

};


template<int gasses_amount>
class mq_sensor_c{

private:
  hwlib::target::pin_adc & adc_pin;
  int rl; //load resistor
  int ro = 0;
  float ro_clean_air_factor;
  std::array<mq_sensors_gas_curve, gasses_amount> gas_curves;
  std::array<gas, gasses_amount> gasses;
  int resistance_calculation(int raw_adc);

public:
  mq_sensor_c<gasses_amount>(hwlib::target::pin_adc & adc_pin, int rl, float ro_clean_air_factor, std::array<mq_sensors_gas_curve, gasses_amount> curve);
  int calibrate(int sample_times, int interval_wait_ms);
  std::array<gas, gasses_amount> read(int sample_time, int interval_wait_ms);

};

template<int gasses_amount>
mq_sensor_c<gasses_amount>::mq_sensor_c(hwlib::target::pin_adc & adc_pin, int rl, float ro_clean_air_factor, std::array<mq_sensors_gas_curve, gasses_amount> gas_curves):
  adc_pin(adc_pin),
  rl(rl),
  ro_clean_air_factor(ro_clean_air_factor),
  gas_curves(gas_curves)
{
  for(size_t i = 0; i < gas_curves.size(); i++){
    gasses[i].gas_id = gas_curves[i].gas_id;
  }
 }

template<int gasses_amount>
int mq_sensor_c<gasses_amount>::calibrate(int sample_times, int interval_wait_ms){
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

template<int gasses_amount>
int mq_sensor_c<gasses_amount>::resistance_calculation(int raw_adc){
  return rl*(4095-raw_adc)/raw_adc;
};

template<int gasses_amount>
std::array<gas, gasses_amount> mq_sensor_c<gasses_amount>::read(int sample_times, int interval_wait_ms){
  int rs = 0;
  for(int i = 0; i < sample_times; i++)
  {
    int test = resistance_calculation(adc_pin.read());
    rs += test;
    hwlib::wait_ms(interval_wait_ms);
  }

  for(size_t i = 0; i < gas_curves.size(); i++){
    gasses[i].value = static_cast<int>(pow(10, (((log((rs/sample_times)/ro) - gas_curves[i].gas_curve[1]) / gas_curves[i].gas_curve[2]) + gas_curves[i].gas_curve[0])));
  }
  
  return gasses;
}
