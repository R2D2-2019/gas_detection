#include <gas_sensors_c.hpp>

void r2d2::gas::gas_sensors_c::process() {
     while (comm.has_data()){
               auto frame = comm.get_data();

               //process frame
            }
            return;
}