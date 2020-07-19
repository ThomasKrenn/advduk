

#include "glue_ctx.h"

#include "glue_mod.h"
#include "glue_dbg.h"

#include "dukmod_js.h"
#include "dukmod_native.h"

#include <cassert>

/* Nargs was given as 4 and we get the following stack arguments:
*   index 0: id       - Relative IDs are converted to absolute IDs and there are no unresolved
*   index 1: require  - Function for loading further modules
*   index 2: exports  - object to export symbols during module search.
                        Writing to exports within the module search function is usually only needed when
                        loading native (Duktape/C) modules.
*   index 3: module   - object which provides additional information about the module being loaded
*/

duk_ret_t GlueCtx::mod_search(duk_context * ctx) {

    int argc = duk_get_top(ctx);
    assert(argc == 4);

    duk_ret_t rc = GlueMod::search_load(ctx);
 
    return rc;
}


// DUK_COMPILE_EVAL | DUK_COMPILE_NOSOURCE | DUK_COMPILE_STRLEN | DUK_COMPILE_NOFILENAME
void GlueCtx::eval(std::string & src) {


    duk_push_string(_ctx, src.data());

    duk_push_string(_ctx, "eval");

    duk_int_t rc;

    rc = duk_pcompile(_ctx, DUK_COMPILE_EVAL);  // [ ... source filename ] -> [ function ]
    if (rc == DUK_EXEC_SUCCESS) {
        // success
    }
    else {
        printf("error duk_pcompile: %s\n", duk_safe_to_string(_ctx, -1));
    }

    // Call target function func with nargs arguments (not counting the function itself).
    rc = duk_pcall(_ctx, 0);
    if (rc == DUK_EXEC_SUCCESS) {
        // success
    }
    else {

        // throw error
        printf("error duk_pcall: %s\n", duk_safe_to_string(_ctx, -1));
        duk_pop(_ctx);

    }
}

