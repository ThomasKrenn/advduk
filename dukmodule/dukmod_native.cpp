
#include "dukmod_native.h"

#include "glue_dbg.h"

typedef enum tag_OCA_COLORS {
    OCA_UNDEFINED = 0,
    OCA_BLUE,
    OCA_RED,
    OCA_PINK_MAGENTA,
    OCA_GREEN,
    OCA_TURQUOISE_CYAN,
    OCA_YELLOW,
    OCA_WHITE,
    OCA_BLACK,
    OCA_DARK_BLUE,
    OCA_ORANGE,
    OCA_PURPLE,
    OCA_DARK_GREEN,
    OCA_DARK_TURQUOISE,
    OCA_MUSTARD,
    OCA_GRAY,
    OCA_BROWN
} OCA_COLORS;


struct OCA_COLOR {
    const char *color_name;
    const int color_val;
};

#define KEY(a) {#a, a}

static const struct OCA_COLOR oca_key_consts[] = {
    KEY(OCA_UNDEFINED),
    KEY(OCA_BLUE),
    KEY(OCA_RED),
    KEY(OCA_PINK_MAGENTA),
    KEY(OCA_GREEN),
    KEY(OCA_TURQUOISE_CYAN),
    KEY(OCA_YELLOW),
    KEY(OCA_WHITE),
    KEY(OCA_BLACK),
    KEY(OCA_DARK_BLUE),
    KEY(OCA_ORANGE),
    KEY(OCA_PURPLE),
    KEY(OCA_DARK_GREEN),
    KEY(OCA_DARK_TURQUOISE),
    KEY(OCA_MUSTARD),
    KEY(OCA_GRAY),
    KEY(OCA_BROWN)
};



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
    printf("my_func_1( %d)\n", argc);
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
    { "A", my_func_1, 0 /*nargs*/ },
    { "B", my_func_2, DUK_VARARGS /*nargs*/ },
    { NULL, NULL, 0 }
};

/* push a the object to export on the stack */
duk_ret_t dukopen_native_module(duk_context *ctx) {

    duk_bool_t rc;

    DukDbg d(ctx);

d.d();

     duk_idx_t idx = duk_push_object(ctx);

d.d();
     duk_put_function_list(ctx, idx, my_module_funcs);

//d.d();
//
//    for (unsigned int i = 0; i < sizeof(oca_key_consts) / sizeof(struct OCA_COLOR); i++) {
//        duk_push_int(ctx, i);
//        duk_put_prop_string(ctx, idx, oca_key_consts[i].color_name);
//    }
//
d.d();
return 1;

}


int dukmod_native_main(int argc, char *argv[]) {

    GlueCtx ctx;

    const char* native_mod = R"( 
      print('-- native module  --'); 
      var mymod = require('native_mod');
      
      print('### accessing native module code and properties ###');
      print('typeof mymod: ',typeof mymod);
      print('typeof mymod.module: ',typeof mymod.module);
      print(Object.getOwnPropertyNames(mymod));

      print(mymod.A());
      print('OCA_GREEN id =', mymod.OCA_GREEN);

    )";

    std::string src(native_mod);

    ctx.eval(src);

    return EXIT_SUCCESS;
}