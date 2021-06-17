
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_ADD(BITS) \
inline t_u##BITS	U##BITS##_Add(t_u##BITS a, t_u##BITS b)	\
{															\
	HANDLE_ERROR(RESULTRANGE, (a > U##BITS##_MAX - b),		\
		LIBCONFIG_ERROR_HANDLEOVERFLOW(U##BITS##_MAX))		\
	return (a + b);											\
}
#define DEFINEFUNC_SINT_ADD(BITS) \
inline t_s##BITS	S##BITS##_Add(t_s##BITS a, t_s##BITS b)	\
{															\
	if (a && b && SIGN(a) == SIGN(b))						\
	{														\
		HANDLE_ERROR(RESULTRANGE, (a > S##BITS##_MAX - b),	\
			LIBCONFIG_ERROR_HANDLEOVERFLOW(S##BITS##_MAX))	\
		HANDLE_ERROR(RESULTRANGE, (a < S##BITS##_MIN - b),	\
			LIBCONFIG_ERROR_HANDLEOVERFLOW(S##BITS##_MIN))	\
	}														\
	return (a + b);											\
}
/*
(+) + (+) = [0, +2N] => (a > MAX - b)
(+) + (-) = [-N, +N]
(-) + (+) = [-N, +N]
(-) + (-) = [-2N, 0] => (a < MIN - b)
*/



#define DEFINEFUNC_UINT_SUB(BITS) \
inline t_u##BITS	U##BITS##_Sub(t_u##BITS a, t_u##BITS b)	\
{															\
	HANDLE_ERROR(RESULTRANGE, (a < b),						\
		LIBCONFIG_ERROR_HANDLEOVERFLOW(0))					\
	return (a - b);											\
}
#define DEFINEFUNC_SINT_SUB(BITS) \
inline t_s##BITS	S##BITS##_Sub(t_s##BITS a, t_s##BITS b)	\
{															\
	if (a && b && SIGN(a) != SIGN(b))						\
	{														\
		HANDLE_ERROR(RESULTRANGE, (a > S##BITS##_MAX + b),	\
			LIBCONFIG_ERROR_HANDLEOVERFLOW(S##BITS##_MAX))	\
		HANDLE_ERROR(RESULTRANGE, (a < S##BITS##_MIN + b),	\
			LIBCONFIG_ERROR_HANDLEOVERFLOW(S##BITS##_MIN))	\
	}														\
	return (a - b);											\
}
/*
(+) - (+) = [-N, +N]
(+) - (-) = [0, +2N] => (a > MAX + b)
(-) - (+) = [-2N, 0] => (a < MIN + b)
(-) - (-) = [-N, +N]
*/



// TODO fix this and test
#define DEFINEFUNC_UINT_MUL(BITS) \
inline t_u##BITS	U##BITS##_Mul(t_u##BITS a, t_u##BITS b)		\
{																\
	HANDLE_ERROR(RESULTRANGE,									\
		(Memory_GetMSB(a) + Memory_GetMSB(b) >= BITS),			\
		LIBCONFIG_ERROR_HANDLEOVERFLOW(U##BITS##_MAX))			\
	return (a * b);												\
}
#define DEFINEFUNC_SINT_MUL(BITS) \
inline t_s##BITS	S##BITS##_Mul(t_s##BITS a, t_s##BITS b)		\
{																\
	HANDLE_ERROR(RESULTRANGE,									\
		(Memory_GetMSB(ABS(a)) + Memory_GetMSB(ABS(b)) >= BITS),\
		LIBCONFIG_ERROR_HANDLEOVERFLOW(SIGN(a) == SIGN(b) ? S##BITS##_MAX : S##BITS##_MIN))\
	return (a * b);												\
}
/*
(+) * (+) = [0, +N²] => ()
(+) * (-) = [-N², 0] => ()
(-) * (+) = [-N², 0] => ()
(-) * (-) = [0, +N²] => ()
*/



// TODO fix this and test
#define DEFINEFUNC_UINT_DIV(BITS) \
inline t_u##BITS	U##BITS##_Div(t_u##BITS a, t_u##BITS b)			\
{																	\
	HANDLE_ERROR(MATHDOMAIN, (b == 0), return (U##BITS##_ERROR);)	\
	return (a / b);													\
}
#define DEFINEFUNC_SINT_DIV(BITS) \
inline t_s##BITS	S##BITS##_Div(t_s##BITS a, t_s##BITS b)			\
{																	\
	HANDLE_ERROR(MATHDOMAIN, (b == 0), return (S##BITS##_ERROR);)	\
	return (a / b);													\
}
/*
(+) / (+) = [0, +N]
(+) / (-) = [-N, 0]
(-) / (+) = [-N, 0]
(-) / (-) = [0, +N]
*/



// TODO fix this and test
#define DEFINEFUNC_UINT_MOD(BITS) \
inline t_u##BITS	U##BITS##_Mod(t_u##BITS a, t_u##BITS b)			\
{																	\
	HANDLE_ERROR(MATHDOMAIN, (b == 0), return (U##BITS##_ERROR);)	\
	return (a % b);													\
}
#define DEFINEFUNC_SINT_MOD(BITS) \
inline t_s##BITS	S##BITS##_Mod(t_s##BITS a, t_s##BITS b)			\
{																	\
	HANDLE_ERROR(MATHDOMAIN, (b == 0), return (S##BITS##_ERROR);)	\
	return (a % b);													\
}
/*
(+) % (+) = [0, +N]
(+) % (-) = [-N, 0]
(-) % (+) = [-N, 0]
(-) % (-) = [0, +N]
*/



DEFINEFUNC_UINT_ADD(8)
DEFINEFUNC_SINT_ADD(8)
DEFINEFUNC_UINT_SUB(8)
DEFINEFUNC_SINT_SUB(8)
DEFINEFUNC_UINT_MUL(8)
DEFINEFUNC_SINT_MUL(8)
DEFINEFUNC_UINT_DIV(8)
DEFINEFUNC_SINT_DIV(8)
DEFINEFUNC_UINT_MOD(8)
DEFINEFUNC_SINT_MOD(8)

DEFINEFUNC_UINT_ADD(16)
DEFINEFUNC_SINT_ADD(16)
DEFINEFUNC_UINT_SUB(16)
DEFINEFUNC_SINT_SUB(16)
DEFINEFUNC_UINT_MUL(16)
DEFINEFUNC_SINT_MUL(16)
DEFINEFUNC_UINT_DIV(16)
DEFINEFUNC_SINT_DIV(16)
DEFINEFUNC_UINT_MOD(16)
DEFINEFUNC_SINT_MOD(16)

DEFINEFUNC_UINT_ADD(32)
DEFINEFUNC_SINT_ADD(32)
DEFINEFUNC_UINT_SUB(32)
DEFINEFUNC_SINT_SUB(32)
DEFINEFUNC_UINT_MUL(32)
DEFINEFUNC_SINT_MUL(32)
DEFINEFUNC_UINT_DIV(32)
DEFINEFUNC_SINT_DIV(32)
DEFINEFUNC_UINT_MOD(32)
DEFINEFUNC_SINT_MOD(32)

DEFINEFUNC_UINT_ADD(64)
DEFINEFUNC_SINT_ADD(64)
DEFINEFUNC_UINT_SUB(64)
DEFINEFUNC_SINT_SUB(64)
DEFINEFUNC_UINT_MUL(64)
DEFINEFUNC_SINT_MUL(64)
DEFINEFUNC_UINT_DIV(64)
DEFINEFUNC_SINT_DIV(64)
DEFINEFUNC_UINT_MOD(64)
DEFINEFUNC_SINT_MOD(64)

#ifdef __int128
DEFINEFUNC_UINT_ADD(128)
DEFINEFUNC_SINT_ADD(128)
DEFINEFUNC_UINT_SUB(128)
DEFINEFUNC_SINT_SUB(128)
DEFINEFUNC_UINT_MUL(128)
DEFINEFUNC_SINT_MUL(128)
DEFINEFUNC_UINT_DIV(128)
DEFINEFUNC_SINT_DIV(128)
DEFINEFUNC_UINT_MOD(128)
DEFINEFUNC_SINT_MOD(128)
#endif
