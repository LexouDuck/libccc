
#include "libft_memory.h"



inline void	*ft_ptrarrnew(t_size n)
{
	void	**result;

	if (!(result = (void**)ft_memnew(sizeof(void**) * (n + 1))))
		return (NULL);
	return (result);
}
