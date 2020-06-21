
#include "mydukmod.h"

#include "dukmodapp.h"

#include <duktape.h>

#include <stdio.h>

/*
 *  Duktape/C functions providing module functionality.
 */

static duk_ret_t myobject_constructor(duk_context *ctx) {

    int argc = duk_get_top(ctx);
    printf("myobject_constructor( %d)\n", argc);
    return 0;
}

static duk_ret_t myobject_print_first(duk_context *ctx) {

    int argc = duk_get_top(ctx);
    printf("myobject_print_first( %d)\n", argc);
    return 0;
}

static duk_ret_t myobject_print_second(duk_context *ctx) {

    int argc = duk_get_top(ctx);
    printf("myobject_print_second( %d)\n", argc);
    return 0;
}


static duk_ret_t my_func_1(duk_context *ctx) {

    int argc = duk_get_top(ctx);
    printf("my_func_1( %d)\n",argc);
    duk_push_string(ctx, "a");
    return 1;
}

static duk_ret_t my_func_2(duk_context *ctx) {
    
    int argc = duk_get_top(ctx);
    printf("my_func_2( args %d )\n", argc);
    duk_push_string(ctx, "b");
    return 1;
}

static const duk_function_list_entry my_module_funcs[] = {
    { "_a", my_func_1, 0 /*nargs*/ },
    { "_b", my_func_2, DUK_VARARGS /*nargs*/ },
    { NULL, NULL, 0 }
};

static const duk_number_list_entry my_module_consts[] = {
    { "FLAG_FOO", (double)(1 << 0) },
    { NULL , 0.0 }
};

duk_ret_t dukopen_native_module(duk_context *ctx) {

    DukDbg d(ctx);

d.d();

/* Initialize module in whatever way is most appropriate.
* Called as a Duktape/C function.
*
* Push the module result (e.g. an object with exported symbols or
* a function) on top of the value stack and return 1 to indicate
* there's a return value.  Temporary values can be left below
* the return value like in normal Duktape/C functions.
*/


   duk_push_object(ctx);  /* module result */

//d.d();

//   duk_put_function_list(ctx, -1, my_module_funcs);

d.d();

   duk_push_c_function(ctx, my_func_1, 0);

d.d();

   duk_put_prop_string(ctx, -2, "A");

d.d();

   duk_push_c_function(ctx, my_func_2, 0);

d.d();

   duk_put_prop_string(ctx, -2, "B");

d.d();

d.e();


   duk_put_prop_string(ctx, -1, "exports");

d.d();

//     /* Return value is the module object.  It's up to the caller to decide
//     * how to use the value, e.g. write to global object.  The value can also
//     * be e.g. a function/constructor instead of an object.
//     */
// 
//     /* It's up to the caller to decide how to use the value  ----  Why is it up to the caller ? */
  return 1;  /* return module value */

}


duk_ret_t dukopen_js_module(duk_context * ctx) {

    const char* js_src = R"( 
    var _a = function(p) {
        return 'a';
    }

    var _b = function() {
        return 'b';
    }

    exports.A = _a;
    exports.B = _b;

    )";
    size_t len = strlen(js_src);

    duk_push_lstring(ctx, js_src, len);
    return 1;
}

