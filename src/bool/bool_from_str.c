
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



t_bool	Bool_FromString(t_char const* str)
{
	t_bool	result = FALSE;
	Bool_Parse(&result, str);
	return (result);
}

t_size	Bool_Parse(t_bool *dest, t_char const* str)
{
	t_size	length = 0;
	t_size	i = 0;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), PARSE_RETURN(BOOL_ERROR))
	while (str[i] && Char_IsSpace(str[i]))
	{
		++i;
		++length;
	}
	while (str[length])
	{
		++length;
	}
	if (Char_IsDigit(str[i]) && SInt_FromString(str + i))
		PARSE_RETURN(TRUE)
	if (String_Equals_N_IgnoreCase(str + i, STRING_0, LENGTH_0) &&
		(length - i <= LENGTH_0 || !Char_IsAlphaNumeric(str[i + LENGTH_0])))
	{
		i += LENGTH_0;
		PARSE_RETURN(FALSE)
	}
	if (String_Equals_N_IgnoreCase(str + i, STRING_1, LENGTH_1) &&
		(length - i <= LENGTH_1 || !Char_IsAlphaNumeric(str[i + LENGTH_1])))
	{
		i += LENGTH_1;
		PARSE_RETURN(TRUE)
	}
	HANDLE_ERROR_SF(PARSE, (TRUE), PARSE_RETURN(BOOL_ERROR),
		"expected boolean string (\"true\" or \"false\", case-insensitive, or a number), instead got \"%s\"", str)
}
