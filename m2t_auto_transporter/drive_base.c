#include "drive_base.h"



static motor_port_t drive_base_left_motor_port = EV3_PORT_A;
static motor_port_t drive_base_right_motor_port = EV3_PORT_C;
static int drive_base_power = 40;

// This class has an explicitly defined 'config' method.

void drive_base_config(void) {
    ev3_motor_config(drive_base_left_motor_port, LARGE_MOTOR);
    ev3_motor_config(drive_base_right_motor_port, LARGE_MOTOR);
}
void drive_base_forward(void) {
    ev3_motor_set_power(drive_base_left_motor_port, drive_base_power);
    ev3_motor_set_power(drive_base_right_motor_port, drive_base_power);
}
void drive_base_back(void) {
    ev3_motor_set_power(drive_base_left_motor_port, -drive_base_power);
    ev3_motor_set_power(drive_base_right_motor_port, -drive_base_power);
}
void drive_base_stop(void) {
    ev3_motor_stop(drive_base_left_motor_port, true);
    ev3_motor_stop(drive_base_right_motor_port, true);
}
void drive_base_turn_left(void) {
    ev3_motor_set_power(drive_base_left_motor_port, 0);
    ev3_motor_set_power(drive_base_right_motor_port, drive_base_power);
}
void drive_base_turn_right(void) {
    ev3_motor_set_power(drive_base_left_motor_port, drive_base_power);
    ev3_motor_set_power(drive_base_right_motor_port, 0);
}

