#pragma once
#include <base_module.hpp>

namespace r2d2::gas {
    class gas_sensors_c : public base_module_c{
    private:

    public:
        gas_sensors_c(base_comm_c &comm):
        base_module_c(comm)        
        {
            comm.listen_for_frames(
                {r2d2::frame_type::ALL}
                //array of frames
            );
        }

        void process() override;
          
    };
}