
#include "libft_char.h"



inline t_bool	ft_isprint(int c)
{
	return (0x20 <= c && c <= 0x7E);
}

inline t_bool	ft_isascii(int c)
{
	return (0x00 <= c && c <= 0x7F);
}

inline t_bool	ft_isspace(int c)
{
	return ((c == ' ') || ('\t' <= c && c <= '\r'));
}

inline t_bool	ft_ispunct(int c)
{
	return (('!' <= c && c <= '/') ||
			(':' <= c && c <= '@') ||
			('[' <= c && c <= '`') ||
			('{' <= c && c <= '~'));
}
