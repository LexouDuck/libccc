
#include "libccc/memory.h"
#include "libccc/monad/array.h"



void	CONCAT(Array_T,_Remove)(s_array_T* array, T item)
{
	t_sint	index = CONCAT(Array_T,_IndexOf)(array, item);
	if (index == ERROR)
		return;
	CONCAT(Array_T,_RemoveAt)(array, index);
}



void	CONCAT(Array_T,_Remove_F)(s_array_T* array, T item, void (*delete)(T))
{
	t_sint	index = CONCAT(Array_T,_IndexOf)(array, item);
	if (index == ERROR)
		return;
	CONCAT(Array_T,_RemoveAt_F)(array, index, delete);
}
