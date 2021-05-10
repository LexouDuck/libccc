
#include "libccc/sys/ascii.h"



inline
t_bool	ASCII_IsDigit(t_ascii c)
{
	return ('0' <= c && c <= '9');
}



inline
t_bool	ASCII_IsDigit_Hex(t_ascii c)
{
	return (('0' <= c && c <= '9') ||
			('A' <= c && c <= 'F') ||
			('a' <= c && c <= 'f'));
}



inline
t_bool	ASCII_IsDigit_Oct(t_ascii c)
{
	return (('0' <= c && c <= '7'));
}



inline
t_bool	ASCII_IsDigit_Bin(t_ascii c)
{
	return (c == '0' || c == '1');
}
