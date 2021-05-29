
#include "libccc/sys/unicode.h"

#include LIBCONFIG_HANDLE_INCLUDE



// TODO UTF handling
t_bool	UTF32_IsDigit(t_utf32 c)
{
	return ('0' <= c && c <= '9');
}



// TODO UTF handling
t_bool	UTF32_IsDigit_Hex(t_utf32 c)
{
	return (('0' <= c && c <= '9') ||
			('A' <= c && c <= 'F') ||
			('a' <= c && c <= 'f'));
}



// TODO UTF handling
t_bool	UTF32_IsDigit_Oct(t_utf32 c)
{
	return (('0' <= c && c <= '7'));
}



// TODO UTF handling
t_bool	UTF32_IsDigit_Bin(t_utf32 c)
{
	return (c == '0' || c == '1');
}
