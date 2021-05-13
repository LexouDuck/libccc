
#include "libccc/sys/unicode.h"



// TODO UTF handling
t_bool	UTF32_IsLetter(t_utf32 c)
{
	return (('A' <= c && c <= 'Z') ||
			('a' <= c && c <= 'z'));
}



// TODO UTF handling
t_bool	UTF32_IsUppercase(t_utf32 c)
{
	return ('A' <= c && c <= 'Z');
}



// TODO UTF handling
t_bool	UTF32_IsLowercase(t_utf32 c)
{
	return ('a' <= c && c <= 'z');
}



// TODO UTF handling
t_bool	UTF32_IsAlphaNumeric(t_utf32 c)
{
	return (('A' <= c && c <= 'Z') ||
			('a' <= c && c <= 'z') ||
			('0' <= c && c <= '9'));
}
