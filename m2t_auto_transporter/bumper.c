#include "bumper.h"



static sensor_port_t bumper_sensor_port = EV3_PORT_1;

// This class has an explicitly defined 'config' method.

void bumper_config(void) {
    ev3_sensor_config(bumper_sensor_port, TOUCH_SENSOR);
}
bool bumper_is_pushed(void) {
    return ev3_touch_sensor_is_pressed(bumper_sensor_port);
}

