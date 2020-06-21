
/*
https://wiki.duktape.org/howtomodules
*/

#include "dukmodapp.h"

#include "mydukmod.h"


#include "duktape.h"

#include "duk_module_duktape.h"
#include "duk_print_alert.h"

#include <stdlib.h>
#include <string>

// call with two ints
static duk_ret_t dummy_add_two(duk_context *ctx) {

    duk_idx_t  nStackVal = duk_get_top(ctx);

    int arg1 = duk_require_int(ctx, -2);
    int arg2 = duk_require_int(ctx, -1);
    duk_pop_2(ctx);

    duk_push_int(ctx, arg1 + arg2);

    return 1;
}

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
    void eval(std::string & src) {
        duk_eval_string(_ctx,src.data());
    }

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

    static duk_ret_t GlueCtx::mod_search(duk_context * ctx) {
        DukDbg d(ctx);
        duk_ret_t rc = 0;
            /* Nargs was given as 4 and we get the following stack arguments:
            *   index 0: id       - Relative IDs are converted to absolute IDs and there are no unresolved
            *   index 1: require  - Function for loading further modules
            *   index 2: exports  - object to export symbols during module search. Writing to exports within the module search function is usually only needed when loading native (Duktape/C) modules.
            *   index 3: module   - object which provides additional information about the module being loaded
            */

            int argc = duk_get_top(ctx);

            switch (argc) {
            case 4: {
                /* module */
                rc = DUK_ERR_NONE;
                duk_remove(ctx, -1);
            }
            case 3: {
                /* exports */
                rc = DUK_ERR_NONE;
                duk_remove(ctx, -1);
            }
            case 2: {
                /* require */
                rc = DUK_ERR_NONE;
                duk_remove(ctx, -1);
            }
            case 1: {
                /* id */
                // require string
                if (duk_check_type(ctx, -1, DUK_TYPE_STRING)) {
                    const char* mymod_id = duk_require_string(ctx, -1);
                    printf("--> require('%s');\n", mymod_id);

                    d.d();
                    duk_remove(ctx, -1);
                    d.d();

                    /* Normally we'd look at 'id' to decide what module to load, ignore
                    * in this example.
                    */

                    if (strcmp(mymod_id,"js_mod") == 0) {
                        rc = dukopen_js_module(ctx);
                    }
                    else {
                        rc = dukopen_native_module(ctx);
                    }

                }

            }
        }
        return rc;
    }

private:
    duk_context * _ctx;
};

/* 
link collection

https://github.com/svaarala/duktape/blob/master/doc/c-module-convention.rst
https://stackoverflow.com/questions/43700716/load-native-c-modules-in-duktape-2-1-0-to
https://wiki.duktape.org/howtomodules

*/

int main(int argc, char *argv[]) {

    GlueCtx glue;
    
    const char* js_mod = R"( 
      print('-- js --'); 
      var mymod = require('js_mod');
      print(typeof mymod);
      print(Object.getOwnPropertyNames(mymod));

      print(mymod.A()); // working

    )";
    const char* native_mod = R"( 
      print('-- js --'); 
      var mymod = require('native_mod');
      print(typeof mymod);
      print(Object.getOwnPropertyNames(mymod));

      print(mymod.A()); // not working

    )";

    bool jsmod = false;
    const char* ourMod;
    if (jsmod) {
        ourMod = js_mod;
    }
    else {
        ourMod = native_mod;
    }

    std::string src(ourMod);
    
    glue.eval(src);

    return EXIT_SUCCESS;
}

