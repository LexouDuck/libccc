
#include "libccc/bool.h"
#include "libccc/char.h"

#include LIBCONFIG_HANDLE_INCLUDE



inline
t_ascii	ASCII_ToUppercase(t_ascii c)
{
	return (('a' <= c && c <= 'z') ? (c - ('a' - 'A')) : c);
}



inline
t_ascii	ASCII_ToLowercase(t_ascii c)
{
	return (('A' <= c && c <= 'Z') ? (c + ('a' - 'A')) : c);
}
