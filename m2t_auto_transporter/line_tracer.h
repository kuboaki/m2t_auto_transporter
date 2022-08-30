#ifndef LINE_TRACER_H_
#define LINE_TRACER_H_

#include <ev3api.h>
#include <stdbool.h>

#include "util.h"
#include "line_monitor.h"
#include "drive_base.h"

extern void line_tracer_config(void);
extern void line_tracer_runner(void);
extern void line_tracer_run(void);
extern void line_tracer_stop(void);

#endif // LINE_TRACER_H_
