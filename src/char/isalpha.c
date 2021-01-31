
#include "libccc/char.h"



inline t_bool	c_isalpha(int c)
{
	return (('A' <= c && c <= 'Z') ||
			('a' <= c && c <= 'z'));
}

inline t_bool	c_isupper(int c)
{
	return ('A' <= c && c <= 'Z');
}

inline t_bool	c_islower(int c)
{
	return ('a' <= c && c <= 'z');
}
