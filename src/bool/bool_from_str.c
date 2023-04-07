
#include "libccc.h"
#include "libccc/bool.h"
#include "libccc/char.h"
#include "libccc/int.h"

#include LIBCONFIG_ERROR_INCLUDE



#define BOOL_ERROR	FALSE

#define STRING_0	"FALSE"
#define LENGTH_0	(sizeof(STRING_0) - sizeof(""))

#define STRING_1	"TRUE"
#define LENGTH_1	(sizeof(STRING_1) - sizeof(""))



t_size	Bool_Parse(t_bool *dest, t_size n, t_char const* str)
{
	t_bool	result;
	t_size	length = 0;
	t_size	i = 0;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination buffer is NULL")
		goto failure;
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to parse is NULL")
		goto failure;
	while (i < n && str[i] && Char_IsSpace(str[i]))
	{
		++i;
		++length;
	}
	while (str[length])
	{
		++length;
	}
	if (Char_IsDigit(str[i]) && SInt_FromString(str + i))
	{
		result = TRUE;
		goto success;
	}
	if (String_Equals_N_IgnoreCase(str + i, STRING_0, LENGTH_0) &&
		(length - i <= LENGTH_0 || !Char_IsAlphaNumeric(str[i + LENGTH_0])))
	{
		i += LENGTH_0;
		result = FALSE;
		goto success;
	}
	if (String_Equals_N_IgnoreCase(str + i, STRING_1, LENGTH_1) &&
		(length - i <= LENGTH_1 || !Char_IsAlphaNumeric(str[i + LENGTH_1])))
	{
		i += LENGTH_1;
		result = TRUE;
		goto success;
	}
	CCCERROR(TRUE, ERROR_PARSE, 
		"expected boolean string (\"TRUE\" or \"FALSE\", case-insensitive, or a number), instead got \"%s\"", str);
		goto failure;

success:
	if (dest)	*dest = result;
	return (i);
failure:
	if (dest)	*dest = BOOL_ERROR;
	return (i);
}



inline
t_bool	Bool_FromString(t_char const* str)
{
	t_bool	result = FALSE;
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to parse given is NULL")
		return (BOOL_ERROR);
	Bool_Parse(&result, String_Length(str), str);
	return (result);
}
