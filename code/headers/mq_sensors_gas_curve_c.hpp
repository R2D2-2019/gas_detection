#pragma once
#include <array>
#include <gas_enums.hpp>

namespace r2d2::gas_detection {

    /**
     * Class mq_sensors_gas_curve_c provides the ability to create gas_curves
     * for the mq_sensor.
     */
    class mq_sensors_gas_curve_c {
    private:
        gas_type gas_id;

        /** Each gas has its own logarithmic curve.
         * Meaning a value of 100 is represented as 2.
         * 
         * The first 2 values are the logarithmic x and y starting points of the curve,
         * the 3rd value is the logarithmic slope increment.
         **/
        std::array<float, 3> gas_curve = {};

    public:
        /**
         * Multiple constructors to create an object with the gas id and gas
         * curve
         **/
        mq_sensors_gas_curve_c(const gas_type &gas_id,
                               const std::array<float, 3> &gas_curve);

        /**
         * This constructor sets the gas curve values according to the gas_id.
         * 0 is LPG, 1 is co, and 2 is smoke 3 is alcohol.
         *
         * These mesures are done as following: For example LPG
         * two points from LPG curve are taken point1:(200,1.6)
         * point2(10000,0.26) take log of each point (lg200,
         * lg 1.6)=(2.3,0.20)  (lg10000,lg0.26)=(4,-0.58)
         * find the slope using these points.
         * take point1 as reference data format:{ x, y,
         * slope};
         **/
        mq_sensors_gas_curve_c(const gas_type &gas_id);

        /**
         * This functions sets the gas_id for a specific gas curve.
         */
        void set_gas_id(const gas_type &gas_id_new);

        /**
         * This functions sets the gas_curve values for a specific gas curve.
         */
        void set_gas_curve(const std::array<float, 3> &gas_curve_new);

        /**
         * This functions returns the gas_id.
         */
        gas_type get_gas_id();

        /**
         * This functions returns the specific value(specified by the index) of
         * a gas_curve.
         */
        float get_gas_curve(const int &index);
    };

} // namespace r2d2::gas_detection
