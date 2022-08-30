#include "auto_transporter.h"

typedef enum _auto_transporter_state_t {
    ATST_PSEUDO_END_STATE,
    ATST_WAIT_FOR_LOADING,
    ATST_TRANSPORTING,
    ATST_WAIT_FOR_UNLOADING,
    ATST_WAIT_FOR_START,
    ATST_WAIT_FOR_RETURN,
    ATST_WAIT_FOR_PASSING_STATION,
    ATST_ARRIVED,
    ATST_RUNNING_TOWARD_GARAGE
} auto_transporter_state_t;

static auto_transporter_state_t at_state;

    ATST_WAIT_FOR_LOADING,
    ATST_TRANSPORTING,
    ATST_WAIT_FOR_UNLOADING,
    ATST_WAIT_FOR_START,
    ATST_WAIT_FOR_RETURN,
    ATST_WAIT_FOR_PASSING_STATION,
    ATST_ARRIVED,
    ATST_RUNNING_TOWARD_GARAGE,

static const char* auto_transporter_state_names[] = {
    "ATST_PSEUDO_END_STATE",
    "ATST_WAIT_FOR_LOADING",
    "ATST_TRANSPORTING",
    "ATST_WAIT_FOR_UNLOADING",
    "ATST_WAIT_FOR_START",
    "ATST_WAIT_FOR_RETURN",
    "ATST_WAIT_FOR_PASSING_STATION",
    "ATST_ARRIVED",
    "ATST_RUNNING_TOWARD_GARAGE"
};


void auto_transporter_config(void) {
    msg_f("auto_transporter_config", 1);
    line_tracer_config();
    wall_detector_config();
    bumper_config();
    carrier_config();

    at_state = ATST_WAIT_FOR_LOADING;
}


void auto_transporter_transport(void) {
    switch(at_state){
    case ATST_WAIT_FOR_LOADING:
        if(carrier_cargo_is_loaded()){
            at_state = ATST_WAIT_FOR_START;
            msg_f(auto_transporter_state_names[at_state], 1);
        }
        break;
    case ATST_TRANSPORTING:
        line_tracer_run();  // do action
        if(wall_detector_is_detected()){
            line_tracer_stop();    //  exit action;
            at_state = ATST_WAIT_FOR_UNLOADING;
            msg_f(auto_transporter_state_names[at_state], 1);
        }
        break;
    case ATST_WAIT_FOR_UNLOADING:
        if(! carrier_cargo_is_loaded()){
            at_state = ATST_WAIT_FOR_RETURN;
            msg_f(auto_transporter_state_names[at_state], 1);
        }
        break;
    case ATST_WAIT_FOR_START:
        if(bumper_is_pushed()){
            at_state = ATST_TRANSPORTING;
            msg_f(auto_transporter_state_names[at_state], 1);
        }
        if(! carrier_cargo_is_loaded()){
            at_state = ATST_WAIT_FOR_LOADING;
            msg_f(auto_transporter_state_names[at_state], 1);
        }
        break;
    case ATST_WAIT_FOR_RETURN:
        if(bumper_is_pushed()){
            at_state = ATST_WAIT_FOR_PASSING_STATION;
            msg_f(auto_transporter_state_names[at_state], 1);
        }
        break;
    case ATST_WAIT_FOR_PASSING_STATION:
        line_tracer_run();  // do action
        if(! wall_detector_is_detected()){
            at_state = ATST_RUNNING_TOWARD_GARAGE;
            msg_f(auto_transporter_state_names[at_state], 1);
        }
        break;
    case ATST_ARRIVED:
        if(true){
            at_state = ATST_PSEUDO_END_STATE;
        }
        break;
    case ATST_RUNNING_TOWARD_GARAGE:
        line_tracer_run();  // do action
        if(wall_detector_is_detected()){
            line_tracer_stop();    //  exit action;
            at_state = ATST_ARRIVED;
            msg_f(auto_transporter_state_names[at_state], 1);
        }
        break;
    case ATST_PSEUDO_END_STATE:
    default:
        break;
    }
}
