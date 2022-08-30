#include "carrier.h"



static sensor_port_t carrier_sensor_port = EV3_PORT_2;

// This class has an explicitly defined 'config' method.

void carrier_config(void) {
    ev3_sensor_config(carrier_sensor_port, TOUCH_SENSOR);
}
bool carrier_cargo_is_loaded(void) {
    return ev3_touch_sensor_is_pressed(carrier_sensor_port);
}

