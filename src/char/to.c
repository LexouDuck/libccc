
#include "libccc_char.h"



inline char		c_tolower(char c)
{
	return (('A' <= c && c <= 'Z') ?
		(c - 'A' + 'a') : c);
}

inline char		c_toupper(char c)
{
	return (('a' <= c && c <= 'z') ?
		(c - 'a' + 'A') : c);
}
