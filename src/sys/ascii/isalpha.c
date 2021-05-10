
#include "libccc/sys/ascii.h"



inline
t_bool	ASCII_IsLetter(t_ascii c)
{
	return (('A' <= c && c <= 'Z') ||
			('a' <= c && c <= 'z'));
}



inline
t_bool	ASCII_IsUppercase(t_ascii c)
{
	return ('A' <= c && c <= 'Z');
}



inline
t_bool	ASCII_IsLowercase(t_ascii c)
{
	return ('a' <= c && c <= 'z');
}



inline
t_bool	ASCII_IsAlphaNumeric(t_ascii c)
{
	return (('A' <= c && c <= 'Z') ||
			('a' <= c && c <= 'z') ||
			('0' <= c && c <= '9'));
}
