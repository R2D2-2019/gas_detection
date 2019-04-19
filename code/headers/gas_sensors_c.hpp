#pragma once
#include <base_module.hpp>
#include <gas_sensor_interface_c.hpp>

namespace r2d2::gas_detection {

    /**
     * Class gas_sensors_c listens to the CAN bus and sends gas data whenever requested. 
     * This class also makes sure the gas container stays up to date. 
     */
    template <int AmountOfSensors>
    class gas_sensors_c : public base_module_c{
    private:
    std::array<gas_sensor_interface_base_c*, AmountOfSensors> sensors;

    public:
        gas_sensors_c(base_comm_c &comm)
        : base_module_c(comm)        
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
   
            //update gas container
            return;
        }   
    };
}