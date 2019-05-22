#pragma once

namespace r2d2::gas_detection {
    /**
     * Enum class to define which gas has what ID. These ID's are always matched with the gas type.
     * If more gasses are used(for example more MQ sensors), add them here.
     */
    enum class gas_type : uint8_t {
        LPG,
        CO,
        SMOKE
    };    
    
} // namespace r2d2::gas_detection 
