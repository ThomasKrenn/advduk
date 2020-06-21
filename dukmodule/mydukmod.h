
#if !defined(MYDUKMOD_202006_H)
#define      MYDUKMOD_202006_H


#include "duk_config.h"

/* Init function name is dukopen_<modname>. */
duk_ret_t dukopen_native_module(duk_context *ctx);

duk_ret_t dukopen_js_module(duk_context * ctx);


#endif
