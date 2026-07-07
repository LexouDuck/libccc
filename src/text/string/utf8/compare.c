
#include "libccc/char.h"
#include "libccc/text/string/ascii.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
_INLINE()
t_sint	StringUTF8_Compare(t_utf8 const* str1, t_utf8 const* str2)
{
	return (strcmp(str1, str2));
}
#else
t_sint	StringUTF8_Compare(t_utf8 const* str1, t_utf8 const* str2)
{
	t_utf32 c1;
	t_utf32 c2;
	t_size	i;

	if (str1 == str2)
		return (0);
	if CCCERROR((str1 == NULL), ERROR_NULLPOINTER, NULL)	return ((str1 - str2));
	if CCCERROR((str2 == NULL), ERROR_NULLPOINTER, NULL)	return ((str1 - str2));
	i = 0;
	while (str1[i] && str2[i])
	{
		c1 = CharUTF32_FromUTF8(str1 + i);
		c2 = CharUTF32_FromUTF8(str2 + i);
		if (c1 != c2)
			return ((t_sint)c1 - (t_sint)c2);
		++i;
	}
	return ((t_sint)str1[i] - (t_sint)str2[i]);
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
_INLINE()
t_sint	StringUTF8_Compare_N(t_utf8 const* str1, t_utf8 const* str2, t_size n)
{
	return (strncmp(str1, str2, n));
}
#else
t_sint	StringUTF8_Compare_N(t_utf8 const* str1, t_utf8 const* str2, t_size n)
{
	t_utf32 c1;
	t_utf32 c2;
	t_size	i;

	if (str1 == str2)
		return (0);
	if CCCERROR((str1 == NULL), ERROR_NULLPOINTER, NULL)	return ((str1 - str2));
	if CCCERROR((str2 == NULL), ERROR_NULLPOINTER, NULL)	return ((str1 - str2));
	if (n == 0)
		return (0);
	i = 0;
	while (str1[i] && str2[i])
	{
		c1 = CharUTF32_FromUTF8(str1 + i);
		c2 = CharUTF32_FromUTF8(str2 + i);
		if (c1 != c2)
			return ((t_sint)c1 - (t_sint)c2);
		++i;
		if (i == n)
			return (0);
	}
	return ((t_sint)str1[i] - (t_sint)str2[i]);
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
_INLINE()
t_sint	StringUTF8_Compare_IgnoreCase(t_utf8 const* str1, t_utf8 const* str2)
{
	return (strcasecmp(str1, str2));
}
#else
t_sint	StringUTF8_Compare_IgnoreCase(t_utf8 const* str1, t_utf8 const* str2)
{
	t_utf32 c1;
	t_utf32 c2;
	t_size	i;

	if (str1 == str2)
		return (0);
	if CCCERROR((str1 == NULL), ERROR_NULLPOINTER, NULL)	return ((str1 - str2));
	if CCCERROR((str2 == NULL), ERROR_NULLPOINTER, NULL)	return ((str1 - str2));
	i = 0;
	while (str1[i] && str2[i])
	{
		c1 = CharUTF32_FromUTF8(str1 + i);
		c2 = CharUTF32_FromUTF8(str2 + i);
		if (c1 != c2 &&
			!(CharUTF32_ToLower(c1) == CharUTF32_ToLower(c2)) &&
			!(CharUTF32_ToUpper(c1) == CharUTF32_ToUpper(c2)))
			return ((t_sint)c1 - (t_sint)c2);
		++i;
	}
	return ((t_sint)str1[i] - (t_sint)str2[i]);
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
_INLINE()
t_sint	StringUTF8_Compare_N_IgnoreCase(t_utf8 const* str1, t_utf8 const* str2, t_size n)
{
	return (strncasecmp(str1, str2, n));
}
#else
t_sint	StringUTF8_Compare_N_IgnoreCase(t_utf8 const* str1, t_utf8 const* str2, t_size n)
{
	t_utf32 c1;
	t_utf32 c2;
	t_size	i;

	if (str1 == str2)
		return (0);
	if CCCERROR((str1 == NULL), ERROR_NULLPOINTER, NULL)	return ((str1 - str2));
	if CCCERROR((str2 == NULL), ERROR_NULLPOINTER, NULL)	return ((str1 - str2));
	if (n == 0)
		return (0);
	i = 0;
	while (str1[i] && str2[i])
	{
		c1 = CharUTF32_FromUTF8(str1 + i);
		c2 = CharUTF32_FromUTF8(str2 + i);
		if (c1 != c2 &&
			!(CharUTF32_ToLower(c1) == CharUTF32_ToLower(c2)) &&
			!(CharUTF32_ToUpper(c1) == CharUTF32_ToUpper(c2)))
			return ((t_sint)c1 - (t_sint)c2);
		++i;
		if (i == n)
			return (0);
	}
	return ((t_sint)str1[i] - (t_sint)str2[i]);
}
#endif
