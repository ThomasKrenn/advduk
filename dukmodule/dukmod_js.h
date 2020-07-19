
#if !defined(DUKMOD_JS_20200718_H)
#define      DUKMOD_JS_20200718_H

#include "glue_ctx.h"

int dukmod_js_main(int argc, char *argv[]);
duk_ret_t dukopen_js_module(duk_context * ctx);

#endif
