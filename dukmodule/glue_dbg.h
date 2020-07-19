
#if !defined(GLUE_DBG_20200710_H)
#define      GLUE_DBG_20200710_H

#include "duktape.h"

class DukDbg {
public:
    DukDbg(duk_context * ctx)
        :_ctx(ctx)
    {}

    void d(); // dump stack
    void e(); // enum
    void g(); // dump global object

private:
    duk_context * _ctx;
};


#endif
