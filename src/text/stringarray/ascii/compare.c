
#include "libccc/memory.h"
#include "libccc/text/string/ascii.h"
#include "libccc/text/stringarray/ascii.h"

#include LIBCONFIG_ERROR_INCLUDE



t_sint	StringArrayASCII_Compare(t_char const* const* strarr1, t_char const* const* strarr2,
	t_sint (*compare)(t_char const* ptr1, t_char const* ptr2))
{
	t_sint	result;
	t_uint	length1;
	t_uint	length2;

	if CCCERROR((compare == NULL), ERROR_NULLPOINTER, "compare() function given is NULL")
		return (0);
	if (strarr1 == strarr2)
		return (0);
	if CCCERROR((strarr1 == NULL), ERROR_NULLPOINTER, NULL) return ((strarr1 - strarr2));
	if CCCERROR((strarr2 == NULL), ERROR_NULLPOINTER, NULL) return ((strarr1 - strarr2));
	length1 = StringArrayASCII_Length(strarr1);
	length2 = StringArrayASCII_Length(strarr2);
	if (length1 == length2 && strarr1 == strarr2)
		return (0);
	for (t_uint i = 0; (i < length1) && (i < length2); ++i)
	{
		result = compare(strarr1[i], strarr2[i]);
		if (result)
			return (result);
	}
	return (0);
}



t_sint	StringArrayASCII_Compare_N(t_char const* const* strarr1, t_char const* const* strarr2,
	t_sint (*compare)(t_char const* ptr1, t_char const* ptr2), t_uint n)
{
	t_sint	result;
	t_uint	length1;
	t_uint	length2;

	if CCCERROR((compare == NULL), ERROR_NULLPOINTER, "compare() function given is NULL")
		return (0);
	if (strarr1 == strarr2)
		return (0);
	if CCCERROR((strarr1 == NULL), ERROR_NULLPOINTER, NULL) return ((strarr1 - strarr2));
	if CCCERROR((strarr2 == NULL), ERROR_NULLPOINTER, NULL) return ((strarr1 - strarr2));
	length1 = StringArrayASCII_Length(strarr1);
	length2 = StringArrayASCII_Length(strarr2);
	if (length1 == length2 && strarr1 == strarr2)
		return (0);
	for (t_uint i = 0; (i < n) && (i < length1) && (i < length2); ++i)
	{
		result = compare(strarr1[i], strarr2[i]);
		if (result)
			return (result);
	}
	return (0);
}
