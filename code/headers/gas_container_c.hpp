#pragma once
#include <gas_s.hpp>
#include <array>
namespace r2d2::gas_detection {
    /**
     * Class gas_container_c is a containers for all the gas values 
     */
    template<int AmountOfGasses>
    class gas_container_c{
    private:
        std::array<gas_s, AmountOfGasses> gasses;
    public:
        gas_container_c(){}

        /**
         * This function returns the value of a certain gas. To use this function, give the ID from a gas (which should be found on the wiki).
         * The function then returns the value of the gas. This value can be either PPM or ml/L (which of the 2 is also found on the wiki).
         */
        int get(int gas_id){
            for (const gas_s &gas : gasses){
                if(gas.gas_id == gas_id){
                    return gas.value;
                }
            }
        }

        /**
         * This function is used to set values in the container. 
         */
        void set (int gas_id, int value){
            for (const gas_s &gas : gasses){
                if (gas.gas_id == gas_id){
                    gas.value = value;
                    return true; // confirmed. 
                }
            }
            return false; //gas not in array. (We need to make sure all gasses are already in the array from the start. This needs another look, but works for now)
        }
    };
    
}