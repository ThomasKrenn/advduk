

/*
link collection

https://github.com/svaarala/duktape/blob/master/doc/c-module-convention.rst
https://stackoverflow.com/questions/43700716/load-native-c-modules-in-duktape-2-1-0-to
https://wiki.duktape.org/howtomodules

*/


#include "dukmodapp.h"




#include "dukmod_js.h"
#include "dukmod_native.h"

#include <stdlib.h>


/*
// call with two ints
static duk_ret_t dummy_add_two(duk_context *ctx) {

    duk_idx_t  nStackVal = duk_get_top(ctx);

    int arg1 = duk_require_int(ctx, -2);
    int arg2 = duk_require_int(ctx, -1);
    duk_pop_2(ctx);

    duk_push_int(ctx, arg1 + arg2);

    return 1;
}
*/






using TestFunc = int(*) (int, char*[]);

struct tag_cmdTable {
    const char *   cmd;
    TestFunc func;
};

tag_cmdTable cmdTable[] = {
    "[dukmod_js]",      &dukmod_js_main,
    "[dukmod_native]",  &dukmod_native_main,
    nullptr,nullptr
};


TestFunc getTstFunc(const char* cmdName) {
    for (int i = 0; cmdTable[i].cmd != nullptr; ++i) {
        if (strcmp(cmdName, cmdTable[i].cmd) == 0) {
            return cmdTable[i].func;
        }
    }
    return nullptr;
}

void usage(const char* prg) {
    printf("Usage: dukmodapp.exe [command]\nCommands:\n");
    for (int i = 0; cmdTable[i].cmd != nullptr; ++i) {
        printf("  '%s'\n", cmdTable[i].cmd);
    }
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    TestFunc func = getTstFunc(argv[1]);
    if (func) {
        int rc = func(argc, argv);
        return rc;
    }

    usage(argv[0]);

    return EXIT_FAILURE;
}



