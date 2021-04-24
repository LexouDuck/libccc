
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/encode/json.h"



t_sint	JSON_GetArrayLength(s_json const* array)
{
	s_json* child = NULL;
	t_size size = 0;

	if (array == NULL)
		return (0);
	child = array->child;
	while (child != NULL)
	{
		size++;
		child = child->next;
	}
	// FIXME: Can overflow here. Cannot be fixed without breaking the API
	return (t_sint)size;
}
