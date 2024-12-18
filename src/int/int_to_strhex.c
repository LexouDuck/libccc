
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_TOSTRHEX(BITS) \
t_char*	U##BITS##_ToString_Hex(t_u##BITS number, t_bool prefix) \
{ \
	t_char*	result; \
	t_u8	digits[BITS / 4]; \
	t_u8	i; \
	t_u##BITS	n; \
	n = number; \
	i = 0; \
	while (n > 0) \
	{ \
		digits[i++] = n % 16; \
		n /= 16; \
	} \
	if (i == 0) \
		digits[i++] = 0; \
	result = (t_char*)Memory_Allocate((prefix ? 2 : 0) + i + 1); \
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL) \
		return (NULL); \
	n = 0; \
	if (prefix) \
	{ \
		result[n++] = '0'; \
		result[n++] = 'x'; \
	} \
	while (i--) \
	{ \
		result[n++] = digits[i] + (digits[i] < 10 ? '0' : 'A' - 10); \
	} \
	result[n] = '\0'; \
	return (result); \
} \

DEFINEFUNC_UINT_TOSTRHEX(8)
DEFINEFUNC_UINT_TOSTRHEX(16)
DEFINEFUNC_UINT_TOSTRHEX(32)
DEFINEFUNC_UINT_TOSTRHEX(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_TOSTRHEX(128)
#endif



#define DEFINEFUNC_SINT_TOSTRHEX(BITS) \
t_char*	S##BITS##_ToString_Hex(t_s##BITS number, t_bool prefix) \
{ \
	t_char*	result; \
	t_u8	digits[BITS / 4]; \
	t_u8	i; \
	t_u##BITS	n; \
	if (number < 0) \
		n = -number; \
	else n = number; \
	i = 0; \
	while (n > 0) \
	{ \
		digits[i++] = n % 16; \
		n /= 16; \
	} \
	result = (t_char*)Memory_Allocate((prefix ? 2 : 0) + i + 1); \
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL) \
		return (NULL); \
	n = 0; \
	if (number < 0) \
		result[n++] = '-'; \
	if (number == 0) \
		result[n++] = '0'; \
	if (prefix) \
	{ \
		result[n++] = '0'; \
		result[n++] = 'x'; \
	} \
	while (i--) \
	{ \
		result[n++] = digits[i] + (digits[i] < 10 ? '0' : 'A' - 10); \
	} \
	result[n] = '\0'; \
	return (result); \
} \

DEFINEFUNC_SINT_TOSTRHEX(8)
DEFINEFUNC_SINT_TOSTRHEX(16)
DEFINEFUNC_SINT_TOSTRHEX(32)
DEFINEFUNC_SINT_TOSTRHEX(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_TOSTRHEX(128)
#endif
