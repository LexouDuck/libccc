
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/encode/common.h"



t_bool	KVT_Equals(s_kvt const* const a, s_kvt const* const b, const t_bool case_sensitive)
{
	if ((a == NULL) || (b == NULL) ||
		((a->type & DYNAMIC_TYPE_MASK) != (b->type & DYNAMIC_TYPE_MASK)) ||
		KVT_IsInvalid(a))
		return (FALSE);
	// check if type is valid
	switch (a->type & DYNAMIC_TYPE_MASK)
	{
		case DYNAMIC_TYPE_NULL:
		case DYNAMIC_TYPE_BOOLEAN:
		case DYNAMIC_TYPE_INTEGER:
		case DYNAMIC_TYPE_FLOAT:
		case DYNAMIC_TYPE_STRING:
		case DYNAMIC_TYPE_RAW:
		case DYNAMIC_TYPE_ARRAY:
		case DYNAMIC_TYPE_OBJECT:
			break;
		default:
			return (FALSE);
	}
	// objects with identical pointers are necessarily equal
	if (a == b)
		return (TRUE);
	switch (a->type & DYNAMIC_TYPE_MASK)
	{
		case DYNAMIC_TYPE_NULL: 	return (TRUE);
		case DYNAMIC_TYPE_BOOLEAN:	return (a->value.boolean == b->value.boolean);
		case DYNAMIC_TYPE_INTEGER:	return (a->value.number == b->value.number);
		case DYNAMIC_TYPE_FLOAT:	return (F64_Equals(a->value.number, b->value.number));
		case DYNAMIC_TYPE_STRING:	return (String_Equals(a->value.string, b->value.string));
		case DYNAMIC_TYPE_RAW:		return (String_Equals(a->value.string, b->value.string));
		case DYNAMIC_TYPE_ARRAY:
		{
			s_kvt* a_element = a->value.child;
			s_kvt* b_element = b->value.child;
			for (; (a_element != NULL) && (b_element != NULL);)
			{
				if (!KVT_Equals(a_element, b_element, case_sensitive))
					return (FALSE);

				a_element = a_element->next;
				b_element = b_element->next;
			}
			// one of the arrays is longer than the other
			if (a_element != b_element)
				return (FALSE);
			return (TRUE);
		}
		case DYNAMIC_TYPE_OBJECT:
		{
			s_kvt* a_element = NULL;
			s_kvt* b_element = NULL;
			foreach (s_kvt*, a_element, s_kvt, a)
			{
				// TODO This has O(n^2) runtime, which is horrible!
				b_element = case_sensitive ?
					KVT_GetObjectItem_CaseSensitive(b, a_element->key) :
					KVT_GetObjectItem_IgnoreCase(b, a_element->key);
				if (b_element == NULL)
					return (FALSE);

				if (!KVT_Equals(a_element, b_element, case_sensitive))
					return (FALSE);
			}
			// Doing this twice, once on a and b to prevent TRUE comparison if a subset of b
			// TODO: Do this the proper way, this is just a fix for now */
			foreach (s_kvt*, b_element, s_kvt, b)
			{
				a_element = case_sensitive ?
					KVT_GetObjectItem_CaseSensitive(a, b_element->key) :
					KVT_GetObjectItem_IgnoreCase(a, b_element->key);
				if (a_element == NULL)
					return (FALSE);

				if (!KVT_Equals(b_element, a_element, case_sensitive))
					return (FALSE);
			}
			return (TRUE);
		}

		default:
			return (FALSE);
	}
}
