

#include "glue_dbg.h"



// debug helper
void DukDbg::d() {
    duk_push_context_dump(_ctx);
    printf("--> %s\n\n", duk_to_string(_ctx, -1));
    duk_pop(_ctx);
}

void DukDbg::e() {
    duk_enum(_ctx, -1, DUK_ENUM_INCLUDE_NONENUMERABLE);

    while (duk_next(_ctx, -1 /*enum_idx*/, 0 /*get_value*/)) {
        /* [ ... enum key ] */
        printf("-> key %s\n", duk_get_string(_ctx, -1));
        duk_pop(_ctx);  /* pop_key */
    }
}

void DukDbg::g() {
    duk_push_global_object(_ctx);
    d();
    duk_pop(_ctx);
}
