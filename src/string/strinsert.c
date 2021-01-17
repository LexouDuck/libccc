
#include "libccc_memory.h"
#include "libccc_string.h"



char	*c_strinsert(char const *dest, char const *src, t_size offset)
{
	char	*result;
	t_size	len_dst;
	t_size	len_src;
	t_size	i;

#if LIBCCCCONFIG_HANDLE_NULLPOINTERS
	if (dest == NULL || src == NULL)
		return (NULL);
#endif
	len_dst = c_strlen(dest);
	len_src = c_strlen(src);
	if (!(result = (char *)c_memalloc(len_dst + len_src + 1)))
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
