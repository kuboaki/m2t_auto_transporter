#include "wall_detector.h"




static sensor_port_t wall_detector_sensor_port = EV3_PORT_4;
static int wall_detector_threshold = 8;

// This class has an explicitly defined 'config' method.

void wall_detector_config(void) {
    ev3_sensor_config(wall_detector_sensor_port, ULTRASONIC_SENSOR);
}
bool wall_detector_is_detected(void) {
    static int16_t val_old = 0;
    static uint32_t detected = 0;
    static uint32_t detected_old = 0;
    
    int16_t val = ev3_ultrasonic_sensor_get_distance(wall_detector_sensor_port);
    if( val < wall_detector_threshold ) {
        detected = (detected << 1) | 1;
    } else {
        detected = (detected << 1) | 0;
    }
    if( val_old != val ) {
        fmt_f("dist=%d", val, 4);
    }
    if( detected_old != detected ) {
        fmt_f("detected=%04X", detected, 5);
    }
    val_old = val;
    detected_old = detected;
    return detected;
}

