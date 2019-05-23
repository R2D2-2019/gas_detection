#pragma once
#include <base_module.hpp>
#include <gas_sensor_interface_c.hpp>
#include <gas_container_c.hpp>
#include <gas_s.hpp>
#include <mq_sensor.hpp>

namespace r2d2::gas_detection {

    /**
     * Class gas_sensors_c listens to the CAN bus and sends gas data whenever requested. 
     * This class also makes sure the gas container stays up to date. 
     */
    template <int AmountOfSensors, int AmountOfGasses>
    class gas_sensors_c : public base_module_c{
    private:
        std::array<gas_sensor_interface_base_c*, AmountOfSensors> sensors;
        gas_container_c<AmountOfGasses> container;

    public:
        gas_sensors_c(base_comm_c &comm,std::array<gas_sensor_interface_base_c*, AmountOfSensors> & sensors, gas_container_c<AmountOfGasses> & container)
            : base_module_c(comm),
              container(container)
                
        {
            comm.listen_for_frames(
                {r2d2::frame_type::ALL} // should become only gas requests. 
            );
        }

        void process() override{
            while (comm.has_data()){
                auto frame = comm.get_data();
                
                //process frame: return the asked values
            }

            /**
            * TODO: doxy
            * @return
            */
            for (gas_sensor_interface_base_c* sensor : sensors){
                //std::array<r2d2::gas_detection::gas_s, AmountOfGasses> sensor_data = sensor->gas_sensor_interface_c<AmountOfGasses>::get();
                std::array<r2d2::gas_detection::gas_s, AmountOfGasses> sensor_data = sensor->gas_sensor_interface_c<AmountOfGasses>::get();
                for (r2d2::gas_detection::gas_s gas : sensor_data){
                    container.set(gas.gas_id, gas.value);
                }
            }
        }   
    };
}