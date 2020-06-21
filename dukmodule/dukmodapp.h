
#if !defined(MYDUKAPP_202006_H)
#define      MYDUKAPP_202006_H

#include "duk_config.h"

class DukDbg {
public:
    DukDbg(duk_context * ctx)
        :_ctx(ctx)
    {}

    void d();
    void e();

private:
    duk_context * _ctx;
};

#endif


