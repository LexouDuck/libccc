
#include "libft_memory.h"
#include "libft_list.h"



s_list*		List_New(void* item, t_size item_size)
{
	s_list* result;

	if (!(result = (s_list*)Memory_Alloc(sizeof(s_list))))
		return (NULL);
//	result->prev = NULL;
	result->next = NULL;
	result->item_size = (item ? item_size : 0);
	result->item = item;
	return (result);
}
