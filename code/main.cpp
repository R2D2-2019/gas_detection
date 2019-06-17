#include <comm.hpp>
#include <hwlib.hpp>
#include <gas_sensors_c.hpp>

template <typename T, std::size_t N>
hwlib::ostream &operator<<(hwlib::ostream &out, const std::array<T, N> &rhs) {
    for (auto &object : rhs) {
        out << object << '\n';
    }
    return out;
}

int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
    // The pin to read the analogue value of mq_sensor.
    auto mq_pin = hwlib::target::pin_adc(hwlib::target::ad_pins::a0);

    r2d2::comm_c comm1;

    // Define the amount of gasses and sensors here.
    constexpr int sensors_amount = 1;
    constexpr int gasses_amount = 3;

    // Creating objects that contain the gas curve used by mq sensors.
    r2d2::gas_detection::mq_sensors_gas_curve_c lpg(
        static_cast<int>(r2d2::gas_detection::gas_type::LPG));
    r2d2::gas_detection::mq_sensors_gas_curve_c co(
        static_cast<int>(r2d2::gas_detection::gas_type::CO));
    r2d2::gas_detection::mq_sensors_gas_curve_c smoke(
        static_cast<int>(r2d2::gas_detection::gas_type::SMOKE));

    // Creating structs that store the ID and value.
    r2d2::gas_detection::gas_s gas_s_lpg = {
        static_cast<int>(r2d2::gas_detection::gas_type::LPG), 0};
    r2d2::gas_detection::gas_s gas_s_co = {
        static_cast<int>(r2d2::gas_detection::gas_type::CO), 0};
    r2d2::gas_detection::gas_s gas_s_smoke = {
        static_cast<int>(r2d2::gas_detection::gas_type::SMOKE), 0};

    // Create MQ-2 sensor object with corresponding gas curves.
    std::array<r2d2::gas_detection::mq_sensors_gas_curve_c, gasses_amount>
        mq_2_gas_curves = {lpg, co, smoke};

    // Create array with gas structs with variable amount.
    std::array<r2d2::gas_detection::gas_s, gasses_amount> gasses_s = {
        gas_s_lpg, gas_s_co, gas_s_smoke};

    // Create container with gas structs.
    r2d2::gas_detection::gas_container_c<gasses_amount> container_gasses(
        gasses_s);

    // Create mq_sensor object with mq gas curves.
    r2d2::gas_detection::mq_sensor_c<gasses_amount> mq_2(mq_pin,
                                                         mq_2_gas_curves);

    // Create an array with all gas sensor pointers.
    std::array<r2d2::gas_detection::gas_sensor_interface_c<gasses_amount> *,
               sensors_amount>
        gas_sensors_ptrs = {&mq_2};

    // Create an object which has the pointers of gas sensors, container of gas
    // structs, and able to send all information over the CAN bus.
    r2d2::gas_detection::module_c<sensors_amount, gasses_amount> gas_sensors(
        comm1, gas_sensors_ptrs, container_gasses);

    hwlib::cout << "start heating" << '\n';
    hwlib::wait_ms(20'000); // the module needs to heat up!
    hwlib::cout << "done heating" << '\n';

    // Setting interval and sample time for calibration.
    mq_2.set_sample_interval_time(10, 500);
    mq_2.calibrate();

    // Setting interval and sample time for getting results.
    mq_2.set_sample_interval_time(1, 20);

    for (;;) {
        gas_sensors.process();
    }
}