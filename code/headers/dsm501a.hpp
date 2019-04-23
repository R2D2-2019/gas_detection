#pragma once
#include <hwlib.hpp>

class dsm501a_c{
    private:
        /**
        * @brief 
        * Data output pin
        */
        hwlib::target::pin_in & pin_in;  // digital pin_in
        /**
        * @brief 
        * Sampletime (30 seconds as default)
        */
        int sampletime_ms; //miliseconds
        /**
        * @brief 
        * Interval while measuring (important for RTOS)
        */
        int waitingtime_ms; //miliseconds
    public:

        /**
        * @brief 
        * Constructor dsm501a_c
        * @param    pin_in: GPIO number
        * @param    sampletime: measuring time, default 30000 miliseconds
        * @param    waitingtime: Interval while measuring in milliseconds (important for RTOS, default 50 milliseconds)
        */
        dsm501a_c(hwlib::target::pin_in & pin_in, int sampletime = 30000, int waitingtime = 50):
            pin_in(pin_in),
            sampletime_ms(sampletime),
            waitingtime_ms(waitingtime)
        {}
        /**
        * @brief 
        * Reads the gasvolume, returns a value in ug/m3
        * @details
        * Reads the gasvolume for 30 seconds, returns an integer value in ug/m3
        */
        int read();
        /**
        * @brief 
        * Empty function, inherits from (future) superclass
        */
        void calibrate(){}
};