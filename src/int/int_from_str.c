
#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/char.h"
#include "libccc/pointer.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_FROMSTR(BITS) \
t_u##BITS	U##BITS##_FromString(t_char const* str)									\
{																					\
	t_char const* s = String_Find_Char(str, '0');									\
	if (s && s[0] && s[0] == '0')													\
		switch (s[1])																\
		{																			\
			case 'x': return (U##BITS##_FromString_Hex(s));							\
			case 'o': return (U##BITS##_FromString_Oct(s));							\
			case 'b': return (U##BITS##_FromString_Bin(s));							\
		}																			\
	return (U##BITS##_FromString_Dec(str));											\
}																					\

DEFINEFUNC_UINT_FROMSTR(8)
DEFINEFUNC_UINT_FROMSTR(16)
DEFINEFUNC_UINT_FROMSTR(32)
DEFINEFUNC_UINT_FROMSTR(64)
#ifdef __int128
DEFINEFUNC_UINT_FROMSTR(128)
#endif



#define DEFINEFUNC_SINT_FROMSTR(BITS) \
t_s##BITS	S##BITS##_FromString(t_char const* str)									\
{																					\
	t_char const* s = String_Find_Char(str, '0');									\
	if (s && s[0] && s[0] == '0')													\
		switch (s[1])																\
		{																			\
			case 'x': return (S##BITS##_FromString_Hex(s));							\
			case 'o': return (S##BITS##_FromString_Oct(s));							\
			case 'b': return (S##BITS##_FromString_Bin(s));							\
		}																			\
	return (S##BITS##_FromString_Dec(str));											\
}																					\

DEFINEFUNC_SINT_FROMSTR(8)
DEFINEFUNC_SINT_FROMSTR(16)
DEFINEFUNC_SINT_FROMSTR(32)
DEFINEFUNC_SINT_FROMSTR(64)
#ifdef __int128
DEFINEFUNC_SINT_FROMSTR(128)
#endif
