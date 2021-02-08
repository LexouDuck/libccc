
#include "libccc/char.h"



inline t_char		Char_ToUppercase(t_char c)
{
	return (('a' <= c && c <= 'z') ?
		(c - 'a' + 'A') : c);
}



inline t_char		Char_ToLowercase(t_char c)
{
	return (('A' <= c && c <= 'Z') ?
		(c - 'A' + 'a') : c);
}
