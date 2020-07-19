

#include "glue_mod.h"

#include "glue_dbg.h"

typedef duk_ret_t(*GLUE_MOD_INIT_FUNC)(duk_context*);

typedef enum {
    GLUE_IMPL_UNDEFINED,
    GLUE_IMPL_NATIVE,
    GLUE_IMPL_SCRIPT
} GLUE_MOD_IMPL;

struct duk_c_module {
    bool isValid() const {
        return impl_t != GLUE_IMPL_UNDEFINED;
    }

    bool isNative() const {
        return impl_t == GLUE_IMPL_NATIVE;
    }
    
    bool isScript() const {
        return impl_t == GLUE_IMPL_SCRIPT;
    }

    const char *name;
    GLUE_MOD_INIT_FUNC init_func;
    GLUE_MOD_IMPL impl_t;
};



static const struct duk_c_module c_module_list[] = {
    { "js_mod",     dukopen_js_module,     GLUE_IMPL_SCRIPT },
    { "native_mod", dukopen_native_module, GLUE_IMPL_NATIVE },
    { "",           nullptr,               GLUE_IMPL_UNDEFINED },
};

static const int c_module_count = (sizeof(c_module_list) / sizeof(c_module_list[0]));


const duk_c_module & glue_mod_idx_by_name(const char* name) {

    for (int i = 0; i < c_module_count; i++) {
        if (strcmp(c_module_list[i].name, name) == 0) {
            return c_module_list[i];
        }
    }
    return c_module_list[c_module_count];
}

duk_ret_t my_native_constructor(duk_context *ctx) {
    return 0;
}

/* Module table:
* - module.exports: initial exports table (may be replaced by user)
* - module.id is non-writable and non-configurable, as the CommonJS
*   spec suggests this if possible
* - module.filename: not set, defaults to resolved ID if not explicitly
*   set by modSearch() (note capitalization, not .fileName, matches Node.js)
* - module.name: not set, defaults to last component of resolved ID if
*   not explicitly set by modSearch()
*/

/* 
 *   Nargs was given as 4 and we get the following stack arguments:
 *   index 0: id       - Relative IDs are converted to absolute IDs and there are no unresolved
 *   index 1: require  - Function for loading further modules
 *   index 2: exports  - object to export symbols during module search.
                         Writing to exports within the module search function is usually only needed when
                         loading native (Duktape/C) modules.
 *   index 3: module   - object which provides additional information about the module being loaded
*/
bool GlueMod::search_load(duk_context* ctx) {

    DukDbg d(ctx);
    duk_ret_t rc = 0;

    const char *glue_mode_id = duk_get_string(ctx, 0);

    const duk_c_module &glue_module = glue_mod_idx_by_name(glue_mode_id);

    if (glue_module.isValid()) {
        glue_module.init_func(ctx);

       if (glue_module.isNative()) {
           // POPULATE exports
d.d();
           duk_enum(ctx, -1, 0);

d.d();
           while (duk_next(ctx, -1, 1)) {

d.d();
               duk_put_prop(ctx, 2);
d.d();
           }

d.d();
           duk_pop_2(ctx);
d.d();
           return 0;
       }



        if (glue_module.isScript()) {
            return 1;
        }
    }

    return duk_generic_error(ctx, "Could not find module '%s'", glue_mode_id);
}
