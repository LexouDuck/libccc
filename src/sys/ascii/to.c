
#include "libccc/bool.h"
#include "libccc/char.h"



inline
t_ascii	ASCII_ToUppercase(t_ascii c)
{
	return (('a' <= c && c <= 'z') ? (c - ('A' - 'a')) : c);
}



inline
t_ascii	ASCII_ToLowercase(t_ascii c)
{
	return (('A' <= c && c <= 'Z') ? (c + ('A' - 'a')) : c);
}
