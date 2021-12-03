
#include "libccc/math/int.h"

#include LIBCONFIG_ERROR_INCLUDE



// `one` starts at the highest power of four greater than or equal to `x`

#define DEFINEFUNC_UINT_ROOT2(BITS) \
t_u##BITS	U##BITS##_Root2(t_u##BITS x)		\
{												\
    t_u##BITS result = 0;						\
    t_u##BITS one = (t_u##BITS)1 << (BITS - 2);	\
												\
    while (one > x)								\
    {											\
        one >>= 2;								\
    }											\
    while (one != 0)							\
    {											\
        if (x >= result + one)					\
        {										\
            x = x - (result + one);				\
            result = result + 2 * one;			\
        }										\
        result >>= 1;							\
        one >>= 2;								\
    }											\
    return (result);							\
}

#define DEFINEFUNC_SINT_ROOT2(BITS) \
t_s##BITS	S##BITS##_Root2(t_s##BITS x)		\
{												\
    t_s##BITS result = 0;						\
    t_s##BITS one = (t_s##BITS)1 << (BITS - 2);	\
												\
	HANDLE_ERROR(MATHDOMAIN, (x < 0), return (S##BITS##_ERROR);)\
    while (one > x)								\
    {											\
        one >>= 2;								\
    }											\
    while (one != 0)							\
    {											\
        if (x >= result + one)					\
        {										\
            x = x - (result + one);				\
            result = result + 2 * one;			\
        }										\
        result >>= 1;							\
        one >>= 2;								\
    }											\
    return (result);							\
}



DEFINEFUNC_UINT_ROOT2(8)
DEFINEFUNC_SINT_ROOT2(8)
DEFINEFUNC_UINT_ROOT2(16)
DEFINEFUNC_SINT_ROOT2(16)
DEFINEFUNC_UINT_ROOT2(32)
DEFINEFUNC_SINT_ROOT2(32)
DEFINEFUNC_UINT_ROOT2(64)
DEFINEFUNC_SINT_ROOT2(64)
#if LIBCONFIG_USE_128BIT
DEFINEFUNC_UINT_ROOT2(128)
DEFINEFUNC_SINT_ROOT2(128)
#endif
