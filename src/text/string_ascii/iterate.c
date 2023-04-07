
#include "libccc/text/string_ascii.h"

#include LIBCONFIG_ERROR_INCLUDE



void	String_Iterate(t_ascii* str, void (*f)(t_ascii* c))
{
	t_size	i;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return;
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return;
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

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return;
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return;
	i = 0;
	while (str[i])
	{
		f(&(str[i]), i);
		++i;
	}
}
