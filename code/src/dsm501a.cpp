#include <dsm501a.hpp>

int dsm501a_c::read(){
    uint_fast64_t start_time = hwlib::now_us();	
    int duration_low_ms = 0;
    while (start_time + (sampletime_ms*1000) > hwlib::now_us() ){
        if (pin_in.read() == 0){
            duration_low_ms += waitingtime_ms;
        }
         hwlib::wait_ms(waitingtime_ms);
    }
    // floats are not accepted, so the real value has to be divided by 100
    int lowratio_round2 = ((duration_low_ms*100.0)/sampletime_ms)*100;
    
    // floats are not accepted, so the real value has to be divided by 100
    int concentration_mgm3_round2 = ((0.001915 * (lowratio_round2/100.0 * lowratio_round2/100.0)) + (0.09522 * lowratio_round2/100.0) - 0.04884)*100;   // https://forum.mysensors.org/topic/9497/dust-sensor-samyoung-dsm501a/7
    hwlib::cout << "duration_low_ms: " << duration_low_ms << " lowratio: " << lowratio_round2 << "    concentration_mgm3: " << concentration_mgm3_round2 << "\n";
    start_time = hwlib::now_us();
    duration_low_ms = 0;
    return concentration_mgm3_round2;
}