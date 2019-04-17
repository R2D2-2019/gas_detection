#include <hwlib.hpp>
#include <dsm501a.hpp>

int main(void) {
  // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
    
    hwlib::target::pin_in pin_in = hwlib::target::pin_in( hwlib::target::pins::d8);
    dsm501a_c dsm501a = dsm501a_c(pin_in);
    while(1){
      dsm501a.read();
    }
    
}