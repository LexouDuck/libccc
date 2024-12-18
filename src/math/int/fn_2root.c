
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE


#define DEFINEFUNC_UINT_ROOT2(BITS) \
t_u##BITS	U##BITS##_Root2(t_u##BITS x) \
{ \
    t_u##BITS result = 0; \
    t_u##BITS one = (t_u##BITS)1 << (BITS - 2); \
/* `one` starts at the highest power of four greater than or equal to `x` */ \
    while (one > x) \
    { \
        one >>= 2; \
    } \
    while (one != 0) \
    { \
        if (x >= result + one) \
        { \
            x = x - (result + one); \
            result = result + 2 * one; \
        } \
        result >>= 1; \
        one >>= 2; \
    } \
    return (result); \
} \

DEFINEFUNC_UINT_ROOT2(8)
DEFINEFUNC_UINT_ROOT2(16)
DEFINEFUNC_UINT_ROOT2(32)
DEFINEFUNC_UINT_ROOT2(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_ROOT2(128)
#endif



#define DEFINEFUNC_SINT_ROOT2(BITS) \
t_s##BITS	S##BITS##_Root2(t_s##BITS x) \
{ \
    t_s##BITS result = 0; \
    t_s##BITS one = (t_s##BITS)1 << (BITS - 2); \
/* `one` starts at the highest power of four greater than or equal to `x` */ \
	if CCCERROR((x < 0), ERROR_MATHDOMAIN, NULL)\
        return (S##BITS##_ERROR);               \
    while (one > x) \
    { \
        one >>= 2; \
    } \
    while (one != 0) \
    { \
        if (x >= result + one) \
        { \
            x = x - (result + one); \
            result = result + 2 * one; \
        } \
        result >>= 1; \
        one >>= 2; \
    } \
    return (result); \
} \

DEFINEFUNC_SINT_ROOT2(8)
DEFINEFUNC_SINT_ROOT2(16)
DEFINEFUNC_SINT_ROOT2(32)
DEFINEFUNC_SINT_ROOT2(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_ROOT2(128)
#endif
