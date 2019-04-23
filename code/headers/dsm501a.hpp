#pragma once
#include <hwlib.hpp>

class dsm501a_c{
    private:
        hwlib::target::pin_in & pin_in;  // digital pin_in
        int sampletime_ms; //miliseconds
        int waitingtime_ms; //miliseconds
    public:
        dsm501a_c(hwlib::target::pin_in & pin_in):
            pin_in(pin_in),
            sampletime_ms(30000),
            waitingtime_ms(50)
        {}

        int read();
        void calibrate(){}
};