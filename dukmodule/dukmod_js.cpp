

#include "dukmod_js.h"

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


int dukmod_js_main(int argc, char *argv[]) {

    GlueCtx ctx;

    const char* js_mod = R"( 
      print('-- js module --'); 
      var mymod = require('js_mod');
      print(typeof mymod);
      print(Object.getOwnPropertyNames(mymod));

      print(mymod.A());
      print(mymod.id);

    )";

    std::string src(js_mod);

    ctx.eval(src);

    return EXIT_SUCCESS;
}

