#pragma once

namespace r2d2::gas_detection{
    struct gas_s{
        int gas_id;
        int value;      //can be either PPM or ml/L

        friend hwlib::ostream &operator<< (hwlib::ostream &out, const gas_s &g){
            return out << "gas_id: " << g.gas_id << " value: " << g.value;
        }
    };

}
