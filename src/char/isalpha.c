
#include "libccc/char.h"



inline
t_bool	Char_IsLetter(t_utf32 c)
{
	return (('A' <= c && c <= 'Z') ||
			('a' <= c && c <= 'z'));
}



inline
t_bool	Char_IsUppercase(t_utf32 c)
{
	return ('A' <= c && c <= 'Z');
}



inline
t_bool	Char_IsLowercase(t_utf32 c)
{
	return ('a' <= c && c <= 'z');
}
