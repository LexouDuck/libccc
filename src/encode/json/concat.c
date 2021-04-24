
#include "libccc.h"
#include "libccc/encode/json.h"



s_json*	JSON_Concat(s_json const* a, s_json const* b)
{
	s_json*	result;
	s_json*	concat;

	result = JSON_Duplicate(a, TRUE);
	concat = JSON_Duplicate(b, TRUE);
	if (!JSON_AddToArray_Item(result, concat))
	{
		JSON_Delete(result);
		JSON_Delete(concat);
		return (NULL);
	}
	return (result);
}
