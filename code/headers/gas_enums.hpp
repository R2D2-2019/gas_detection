#pragma once

namespace r2d2::gas_detection {
    /**
     * Enum to define which gas has what ID. These ID's are always matched with
     * the gas type. If more gasses are used(for example more MQ sensors), add
     * them here.
     */
    enum class gas_type { LPG = 0, CO = 1, SMOKE = 2, ALCOHOL = 3 };

} // namespace r2d2::gas_detection
