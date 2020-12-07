
#include "libft_memory.h"
#include "libft_string.h"



inline void	ft_strdel(char **a_str)
{
#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (a_str == NULL)
		return ;
#endif
	if (*a_str)
	{
		ft_memfree(*a_str);
		*a_str = NULL;
	}
}
