#pragma once
#include "mq_sensors_gas_curve_c.hpp"
#include <array>
#include <cmath>

namespace r2d2::gas_detection {
    /**
     * Class mq_sensor_c provides the functionality to use all mq type sensors.
     */

    template <int AmountOfGasses>
    class mq_sensor_c : public gas_sensor_interface_c<AmountOfGasses> {
    private:
        /**
         * TODO: doxy rl
         * TODO: doxy ro
         * TODO: doxy ro_clean_air_factor
         * @return
         */
        hwlib::target::pin_adc &adc_pin;
        int rl = 10; // found in datasheet
        int ro = 0;
        int sample_time;
        int interval_time;
        float ro_clean_air_factor = 9.83; // see datasheet air line;
        std::array<mq_sensors_gas_curve_c, AmountOfGasses> gas_curves;
        std::array<gas_s, AmountOfGasses> gasses;

        /**
         * TODO: doxy
         * @return
         */
        int resistance_calculation(int raw_adc);

    public:
        mq_sensor_c<AmountOfGasses>(
            hwlib::target::pin_adc &adc_pin,
            std::array<mq_sensors_gas_curve_c, AmountOfGasses> curve);

        /**
         * The mq sensors need to be calibrated in fresh air, this function
         * provides this functionality.
         * @return
         */

        void calibrate();
        /**
         * Gets the gas values and returns them in an array of gas_s.
         * @return
         */
        std::array<gas_s, AmountOfGasses> get() override;

        void set_sample_interval_time(int new_sample_time,
                                      int new_interval_time);
    };

    template <int AmountOfGasses>
    mq_sensor_c<AmountOfGasses>::mq_sensor_c(
        hwlib::target::pin_adc &adc_pin,
        std::array<mq_sensors_gas_curve_c, AmountOfGasses> gas_curves)
        : adc_pin(adc_pin), gas_curves(gas_curves) {
        for (size_t i = 0; i < gas_curves.size(); i++) {
            gasses[i].gas_id = gas_curves[i].get_gas_id();
        }
    }

    template <int AmountOfGasses>
    void mq_sensor_c<AmountOfGasses>::calibrate() {
        int val = 0;
        for (int i = 0; i < sample_time; i++) {
            val += resistance_calculation(adc_pin.read());
            hwlib::wait_ms(interval_time);
        }
        val = (val / sample_time) / ro_clean_air_factor;
        ro = val;
    };

    template <int AmountOfGasses>
    int mq_sensor_c<AmountOfGasses>::resistance_calculation(int raw_adc) {
        return rl * (4095 - raw_adc) / raw_adc;
    };

    template <int AmountOfGasses>
    std::array<gas_s, AmountOfGasses> mq_sensor_c<AmountOfGasses>::get() {
        int rs = 0;
        for (int i = 0; i < sample_time; i++) {
            int read_value = resistance_calculation(adc_pin.read());
            rs += read_value;
            hwlib::wait_ms(interval_time);
        }

        for (size_t i = 0; i < gas_curves.size(); i++) {
            gasses[i].value =
                static_cast<int>(pow(10, (((log((rs / sample_time) / ro) -
                                            gas_curves[i].get_gas_curve(1)) /
                                           gas_curves[i].get_gas_curve(2)) +
                                          gas_curves[i].get_gas_curve(0))));
        }

        return gasses;
    }

    template <int AmountOfGasses>
    void mq_sensor_c<AmountOfGasses>::set_sample_interval_time(
        int new_sample_time, int new_interval_time) {
        sample_time = new_sample_time;
        interval_time = new_interval_time;
    }

} // namespace r2d2::gas_detection