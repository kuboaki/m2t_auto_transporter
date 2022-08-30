#ifndef AUTO_TRANSPORTER_H_
#define AUTO_TRANSPORTER_H_

#include <ev3api.h>
#include <stdbool.h>

#include "util.h"
#include "line_tracer.h"
#include "wall_detector.h"
#include "bumper.h"
#include "carrier.h"

extern void auto_transporter_config(void);
extern void auto_transporter_transport(void);

#endif // AUTO_TRANSPORTER_H_
