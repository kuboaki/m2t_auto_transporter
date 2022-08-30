#ifndef DRIVE_BASE_H_
#define DRIVE_BASE_H_

#include <ev3api.h>
#include <stdbool.h>

#include "util.h"

extern void drive_base_config(void);
extern void drive_base_config(void);
extern void drive_base_forward(void);
extern void drive_base_back(void);
extern void drive_base_stop(void);
extern void drive_base_turn_left(void);
extern void drive_base_turn_right(void);

#endif // DRIVE_BASE_H_
