#pragma once
#include <cmath>
#include <hwlib.hpp>

namespace r2d2::mq_sensor{
    
    struct gas_s{
        int gas_id, value;
        friend hwlib::ostream &operator<< (hwlib::ostream &out, const gas_s &g){
            return out << "gas_id: " << g.gas_id << " value: " << g.value;
        }
    };

    struct mq_sensors_gas_curve_s{
        int gas_id;
        std::array<float, 3> gas_curve = {};
    };


    /**
     * Class mq_sensor_c provides the functionality to use all mq type sensors.
     */

    template<int AmountOfGasses>
    class mq_sensor_c{
    private:
        hwlib::target::pin_adc & adc_pin;
        int rl;
        int ro = 0;
        float ro_clean_air_factor;
        std::array<mq_sensors_gas_curve_s, AmountOfGasses> gas_curves;
        std::array<gas_s, AmountOfGasses> gasses;

        int resistance_calculation(int raw_adc);

    public: 
        mq_sensor_c<AmountOfGasses>(hwlib::target::pin_adc & adc_pin, int rl, float ro_clean_air_factor, std::array<mq_sensors_gas_curve_s, AmountOfGasses> curve);
        
        /**
         * The mq sensors need to be calibrated in fresh air, this function provides this functionality.
         */
        int calibrate(int sample_times, int interval_wait_ms);
        /**
         * Gets the gas values and returns them in an array of gas_s.
         * There is a fairly complecated calculation required for this,
         * information about this can be found on the wiki
         * @return
         */
        std::array<gas_s, AmountOfGasses> get(int sample_time, int interval_wait_ms);
    };

    template<int AmountOfGasses>
    mq_sensor_c<AmountOfGasses>::mq_sensor_c(hwlib::target::pin_adc & adc_pin, int rl, float ro_clean_air_factor, std::array<mq_sensors_gas_curve_s, AmountOfGasses> gas_curves)
    : adc_pin(adc_pin),
        rl(rl),
        ro_clean_air_factor(ro_clean_air_factor),
        gas_curves(gas_curves) {
        for (size_t i = 0; i < gas_curves.size(); i++) {
            gasses[i].gas_id = gas_curves[i].gas_id;
        }
    }

    template<int AmountOfGasses>
    int mq_sensor_c<AmountOfGasses>::calibrate(int sample_times, int interval_wait_ms){
        int val = 0;
        for (int i = 0; i < sample_times; i++) {
        val += resistance_calculation(adc_pin.read());
        hwlib::wait_ms(interval_wait_ms);
        }
        val = (val/sample_times) / ro_clean_air_factor;
        ro = val;
        return val;

    };

    template<int AmountOfGasses>
    int mq_sensor_c<AmountOfGasses>::resistance_calculation(int raw_adc){
        return rl * (4095 - raw_adc) / raw_adc;
    };

    template<int AmountOfGasses>
    std::array<gas_s, AmountOfGasses> mq_sensor_c<AmountOfGasses>::get(int sample_times, int interval_wait_ms){
        int rs = 0;
        for (int i = 0; i < sample_times; i++) {
            int read_value = resistance_calculation(adc_pin.read());
            rs += read_value;
            hwlib::wait_ms(interval_wait_ms);
        }

        for (size_t i = 0; i < gas_curves.size(); i++) {
            gasses[i].value = static_cast<int>(pow(10, (((log((rs / sample_times) / ro) - gas_curves[i].gas_curve[1]) / gas_curves[i].gas_curve[2]) + gas_curves[i].gas_curve[0])));
        }
    
    return gasses;
    }
} //namespace r2d2::mq_sensor