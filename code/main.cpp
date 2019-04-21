#include "hwlib.hpp"
#include <gas_sensors_c.hpp>

template<typename T, std::size_t N>
hwlib::ostream &operator<< (hwlib::ostream &out, const std::array<T, N> &rhs)
{
    for(auto &object : rhs){
      out << object << '\n';
    }
    return out;
}

int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
    for (;;){
        hwlib::cout << "this works via arduino";
        hwlib::wait_ms(1000);
    }
}