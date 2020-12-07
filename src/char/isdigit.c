
#include "libft_char.h"



inline t_bool	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

inline t_bool	ft_ishexdigit(int c)
{
	return (('0' <= c && c <= '9') ||
			('A' <= c && c <= 'F') ||
			('a' <= c && c <= 'f'));
}

inline t_bool	ft_isalnum(int c)
{
	return (('A' <= c && c <= 'Z') ||
			('a' <= c && c <= 'z') ||
			('0' <= c && c <= '9'));
}
