
#include "libft_char.h"



inline char		ft_tolower(char c)
{
	return (('A' <= c && c <= 'Z') ?
		(c - 'A' + 'a') : c);
}

inline char		ft_toupper(char c)
{
	return (('a' <= c && c <= 'z') ?
		(c - 'a' + 'A') : c);
}
