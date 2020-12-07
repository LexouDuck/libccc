
#include "libft_memory.h"
#include "libft_convert.h"



char	*ft_size_to_str(t_size number)
{
	char	*result;
	t_u8	digits[MAXDIGIT_64BIT];
	t_u8	i;
	t_size	n;

	n = number;
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 10;
		n /= 10;
	}
	if (i == 0)
		digits[i++] = 0;
	if (!(result = (char *)ft_memalloc(i + 1)))
		return (NULL);
	n = 0;
	while (i--)
		result[n++] = '0' + digits[i];
	result[n] = '\0';
	return (result);
}
