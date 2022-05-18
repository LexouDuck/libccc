
#include "libccc/text/stringascii.h"

#include LIBCONFIG_ERROR_INCLUDE



void	String_Iterate(t_ascii* str, void (*f)(t_ascii* c))
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



void	String_Iterate_I(t_ascii* str, void (*f)(t_ascii* c, t_size index))
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
