#pragma once
#include <gas_enums.hpp>
#include <hwlib.hpp>

namespace r2d2::gas_detection {

    /**
     * This is a container which has the gas_id(which corresponds which gas it
     * is) and the value of gas in parts per million.
     */
    struct gas_s {
        gas_type gas_id;
        int value;

        /**
         * An operator which outputs the gas_id and the value in parts per
         * million.
         */
        friend hwlib::ostream &operator<<(hwlib::ostream &out, const gas_s &g) {
            return out << "gas_id: " << static_cast<int>(g.gas_id)
                       << " value: " << g.value;
        }
    };

} // namespace r2d2::gas_detection
