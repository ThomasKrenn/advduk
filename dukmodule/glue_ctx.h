
#if !defined(GLUE_CTX_20200718_H)
#define      GLUE_CTX_20200718_H

#include "duktape.h"

#include "duk_module_duktape.h"
#include "duk_print_alert.h"

#include <string>





class GlueCtx {
public:
    GlueCtx()
        :_ctx(nullptr)
    {
        init();
    }

    ~GlueCtx() {
        if (_ctx) {
            duk_destroy_heap(_ctx);
        }
    }


    // DUK_COMPILE_EVAL | DUK_COMPILE_NOSOURCE | DUK_COMPILE_STRLEN | DUK_COMPILE_NOFILENAME
    void eval(std::string & src);

protected:
    void init() {
        _ctx = duk_create_heap_default();

        // add 'print' support
        duk_uint_t flags = 0;
        duk_print_alert_init(_ctx, flags);

        // add 'require' support
        duk_module_duktape_init(_ctx);


        // module search function
        duk_get_global_string(_ctx, "Duktape");
        duk_push_c_function(_ctx, &GlueCtx::mod_search, 4);
        duk_put_prop_string(_ctx, -2, "modSearch");
        duk_pop(_ctx);

    }

    static duk_ret_t GlueCtx::mod_search(duk_context * ctx);

private:
    duk_context * _ctx;
};

#endif

