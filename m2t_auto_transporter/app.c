#include "app.h"
#include "auto_transporter.h"

void main_task(intptr_t unused) {
    init_f("m2t_auto_transporter");
    static bool is_initialized = false;
    if(! is_initialized) {
        is_initialized = true;
        auto_transporter_config();
    }
    auto_transporter_transport();
    ext_tsk();
}
