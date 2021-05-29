
#include "libccc/string.h"

#include LIBCONFIG_HANDLE_INCLUDE



void	String_Iterate(t_char* str, void (*f)(t_char* c))
{
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (f == NULL), return;)
	i = 0;
	while (str[i])
	{
		f(&(str[i]));
		++i;
	}
}



void	String_Iterate_I(t_char* str, void (*f)(t_char* c, t_size index))
{
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (f == NULL), return;)
	i = 0;
	while (str[i])
	{
		f(&(str[i]), i);
		++i;
	}
}
