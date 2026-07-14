
#include "libccc/memory.h"
#include "libccc/text/string/ascii.h"
#include "libccc/text/stringarray/ascii.h"

#include LIBCONFIG_ERROR_INCLUDE



t_bool	StringArrayASCII_Equals(
	t_char const* const* strarr1,
	t_char const* const* strarr2)
{
	t_uint	length1;
	t_uint	length2;

	if (strarr1 == strarr2)
		return (TRUE);
	if CCCERROR((strarr1 == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
	if CCCERROR((strarr2 == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
	length1 = StringArrayASCII_Length(strarr1);
	length2 = StringArrayASCII_Length(strarr2);
	if (length1 != length2)
		return (FALSE);
	for (t_uint i = 0; i < length1; ++i)
	{
		if (!StringASCII_Equals(strarr1[i], strarr2[i]))
			return (FALSE);
	}
	return (TRUE);
}


t_bool	StringArrayASCII_Equals_N(
	t_char const* const* strarr1,
	t_char const* const* strarr2,
	t_uint n)
{
	t_uint	length1;
	t_uint	length2;

	if (strarr1 == strarr2)
		return (TRUE);
	if CCCERROR((strarr1 == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
	if CCCERROR((strarr2 == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
	length1 = StringArrayASCII_Length(strarr1);
	length2 = StringArrayASCII_Length(strarr2);
	if (length1 != length2 && (length1 < n || length2 < n))
		return (FALSE);
	for (t_uint i = 0; (i < n) && (i < length1) && (i < length2); ++i)
	{
		if (!StringASCII_Equals(strarr1[i], strarr2[i]))
			return (FALSE);
	}
	return (TRUE);
}
