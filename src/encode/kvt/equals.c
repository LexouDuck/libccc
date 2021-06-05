
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_ERROR_INCLUDE



t_bool	KVT_Equals(s_kvt const* a, s_kvt const* b, t_bool case_sensitive)
{
	if (a == b)
		return (TRUE);
	else if (a == NULL)	return (FALSE);
	else if (b == NULL)	return (FALSE);
	if ((a->type & DYNAMICTYPE_MASK) != (b->type & DYNAMICTYPE_MASK))
		return (FALSE);
	HANDLE_ERROR(INVALIDARGS, (KVT_IsInvalid(a)), return (FALSE);)
	HANDLE_ERROR(INVALIDARGS, (KVT_IsInvalid(b)), return (FALSE);)
	// check if type is valid
	switch (a->type & DYNAMICTYPE_MASK)
	{
		case DYNAMICTYPE_NULL:
		case DYNAMICTYPE_BOOLEAN:
		case DYNAMICTYPE_INTEGER:
		case DYNAMICTYPE_FLOAT:
		case DYNAMICTYPE_STRING:
		case DYNAMICTYPE_RAW:
		case DYNAMICTYPE_ARRAY:
		case DYNAMICTYPE_OBJECT:
			break;
		default:
			return (FALSE);
	}
	switch (a->type & DYNAMICTYPE_MASK)
	{
		case DYNAMICTYPE_NULL:    return (TRUE);
		case DYNAMICTYPE_BOOLEAN: return (a->value.boolean == b->value.boolean);
		case DYNAMICTYPE_INTEGER: return (a->value.number == b->value.number);
		case DYNAMICTYPE_FLOAT:   return (F64_Equals(a->value.number, b->value.number));
		case DYNAMICTYPE_STRING:  return (String_Equals(a->value.string, b->value.string));
		case DYNAMICTYPE_RAW:     return (String_Equals(a->value.string, b->value.string));
		case DYNAMICTYPE_ARRAY:
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
		case DYNAMICTYPE_OBJECT:
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
