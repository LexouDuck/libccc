
#include "libft_memory.h"



inline void	ft_memdel(void **ptr)
{
#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (ptr == NULL)
		return ;
#endif
	if (*ptr)
	{
		ft_memfree(*ptr);
		*ptr = NULL;
	}
}
