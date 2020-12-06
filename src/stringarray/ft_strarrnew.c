
#include "libft_memory.h"
#include "libft_stringarray.h"



inline char	**ft_strarrnew(t_u32 length)
{
	return ((char**)ft_memnew(sizeof(char*) * (length + 1)));
}
