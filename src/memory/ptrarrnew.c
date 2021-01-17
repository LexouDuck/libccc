
#include "libccc_memory.h"



inline void	*c_ptrarrnew(t_size n)
{
	void	**result;

	if (!(result = (void**)c_memnew(sizeof(void**) * (n + 1))))
		return (NULL);
	return (result);
}
