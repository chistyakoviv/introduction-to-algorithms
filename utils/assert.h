#include <assert.h>

#define ASSERT(expr, msg) \
    if (!(expr)) \
    { \
        __assert_fail(msg, \
            __FILE__, __LINE__, __ASSERT_FUNCTION); \
    }
