
#if !defined(DUKMOD_NATIVE_20200719_H)
#define      DUKMOD_NATIVE_20200719_H

#include "glue_ctx.h"

/* Init function name is dukopen_<modname>. */
duk_ret_t dukopen_native_module(duk_context *ctx);

int dukmod_native_main(int argc, char *argv[]);


#endif

