
#include "libft_memory.h"
#include "libft_string.h"



char	*ft_strinsert(char const *dest, char const *src, t_size offset)
{
	char	*result;
	t_size	len_dst;
	t_size	len_src;
	t_size	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (dest == NULL || src == NULL)
		return (NULL);
#endif
	len_dst = ft_strlen(dest);
	len_src = ft_strlen(src);
	if (!(result = (char *)ft_memalloc(len_dst + len_src + 1)))
		return (NULL);
	i = (t_size)-1;
	while (++i < offset)
		result[i] = dest[i];
	--i;
	while (++i < len_src)
		result[i] = src[i - offset];
	--i;
	while (++i < len_dst)
		result[i] = dest[i - len_src];
	result[i] = '\0';
	return (result);
}
