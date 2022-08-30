#include "app.h"
#include "auto_transporter.h"

void main_task(intptr_t unused) {
    static bool is_initialized = false;
    if(! is_initialized) {
        is_initialized = true;
        auto_transporter_config();
    }
    auto_transporter_transport();
    ext_tsk();
}
