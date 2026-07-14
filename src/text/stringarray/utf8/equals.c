
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_bool	StringArrayUTF8_Equals(
	t_utf8 const* const* strarr1,
	t_utf8 const* const* strarr2)
{
	t_uint	length1;
	t_uint	length2;
	t_uint	i;

	if (strarr1 == strarr2)
		return (TRUE);
	if CCCERROR((strarr1 == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
	if CCCERROR((strarr2 == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
	length1 = StringArrayUTF8_Length(strarr1);
	length2 = StringArrayUTF8_Length(strarr2);
	if (length1 != length2)
		return (FALSE);
	for (i = 0; i < length1; ++i)
	{
		if (!StringUTF8_Equals(strarr1[i], strarr2[i]))
			return (FALSE);
	}
	return (TRUE);
}



t_bool	StringArrayUTF8_Equals_N(
	t_utf8 const* const* strarr1,
	t_utf8 const* const* strarr2,
	t_uint n)
{
	t_uint	length1;
	t_uint	length2;
	t_uint	i;

	if (strarr1 == strarr2)
		return (TRUE);
	if CCCERROR((strarr1 == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
	if CCCERROR((strarr2 == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
	length1 = StringArrayUTF8_Length(strarr1);
	length2 = StringArrayUTF8_Length(strarr2);
	if (length1 != length2 && (length1 < n || length2 < n))
		return (FALSE);
	for (i = 0; (i < n) && (i < length1) && (i < length2); ++i)
	{
		if (!StringUTF8_Equals(strarr1[i], strarr2[i]))
			return (FALSE);
	}
	return (TRUE);
}
