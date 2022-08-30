#include "line_monitor.h"




static sensor_port_t line_monitor_sensor_port = EV3_PORT_3;
static int line_monitor_threshold = 50;

// This class has an explicitly defined 'config' method.

void line_monitor_config(void) {
    ev3_sensor_config(line_monitor_sensor_port, COLOR_SENSOR);
}
bool line_monitor_is_online(void) {
    return ev3_color_sensor_get_reflect(line_monitor_sensor_port) <  line_monitor_threshold;
}

