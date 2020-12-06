
#include "libft_memory.h"
#include "libft_string.h"
#include "libft_stringarray.h"



char	**ft_strarrsub(char const **strarr, t_u32 start, t_u32 n)
{
	char		**result;
	t_u32		length;
	t_u32		i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (strarr == NULL)
		return (NULL);
#endif
	length = ft_strarrlen(strarr);
	if (start > length || start + n > length)
		return (NULL);
	if (!(result = ft_strarrnew(n)))
		return (NULL);
	i = 0;
	while (i < n)
	{
		if (!(result[i] = ft_strdup(strarr[start + i])))
		{
			ft_strarrdel(&result);
			return (NULL);
		}
		++i;
	}
	result[i] = NULL;
	return (result);
}
