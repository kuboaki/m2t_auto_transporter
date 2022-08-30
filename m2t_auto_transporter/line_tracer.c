#include "line_tracer.h"

typedef enum _line_tracer_state_t {
    LTST_PSEUDO_END_STATE,
    LTST_STOPPING,
    LTST_ON_LINE,
    LTST_OUT_OF_LINE,
    LTST_START
} line_tracer_state_t;

static line_tracer_state_t lt_state;

static const char* line_tracer_state_names[] = {
    "LTST_PSEUDO_END_STATE",
    "LTST_STOPPING",
    "LTST_ON_LINE",
    "LTST_OUT_OF_LINE",
    "LTST_START"
};

static bool line_tracer_running = false;

void line_tracer_config(void) {
    msg_f("line_tracer_config", 1);
    line_monitor_config();
    drive_base_config();

    lt_state = LTST_STOPPING;
    drive_base_stop();  // initial entry action
    msg_f(line_tracer_state_names[lt_state], 1);
}

void line_tracer_run(void) {
    line_tracer_running = true;
    line_tracer_runner();
}
void line_tracer_stop(void) {
    line_tracer_running = false;
    line_tracer_runner();
}

void line_tracer_runner(void) {
    switch(lt_state){
    case LTST_STOPPING:
        if(line_tracer_running){
            lt_state = LTST_START;
            msg_f(line_tracer_state_names[lt_state], 1);
        }
        break;
    case LTST_ON_LINE:
        drive_base_turn_left();  // do action
        if(! line_monitor_is_online()){
            lt_state = LTST_OUT_OF_LINE;
            msg_f(line_tracer_state_names[lt_state], 1);
        }
        if(! line_tracer_running){
            lt_state = LTST_STOPPING;
            msg_f(line_tracer_state_names[lt_state], 1);
            drive_base_stop();  // entry action
        }
        break;
    case LTST_OUT_OF_LINE:
        drive_base_turn_right();  // do action
        if(line_monitor_is_online()){
            lt_state = LTST_ON_LINE;
            msg_f(line_tracer_state_names[lt_state], 1);
        }
        if(! line_tracer_running){
            lt_state = LTST_STOPPING;
            msg_f(line_tracer_state_names[lt_state], 1);
            drive_base_stop();  // entry action
        }
        break;
    case LTST_START:
        if(line_monitor_is_online()){
            lt_state = LTST_ON_LINE;
            msg_f(line_tracer_state_names[lt_state], 1);
        }
        if(! line_monitor_is_online()){
            lt_state = LTST_OUT_OF_LINE;
            msg_f(line_tracer_state_names[lt_state], 1);
        }
        break;
    case LTST_PSEUDO_END_STATE:
    default:
        break;
    }
}
