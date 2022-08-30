#ifndef WALL_DETECTOR_H_
#define WALL_DETECTOR_H_

#include <ev3api.h>
#include <stdbool.h>

#include "util.h"

extern void wall_detector_config(void);
extern void wall_detector_config(void);
extern bool wall_detector_is_detected(void);

#endif // WALL_DETECTOR_H_
