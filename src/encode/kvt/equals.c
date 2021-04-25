
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/encode/common.h"



t_bool	KVT_Equals(s_kvt const* const a, s_kvt const* const b, const t_bool case_sensitive)
{
	if ((a == NULL) || (b == NULL) || ((a->type & KVT_TYPE_MASK) != (b->type & KVT_TYPE_MASK)) || KVT_IsInvalid(a))
		return (FALSE);

	// check if type is valid
	switch (a->type & KVT_TYPE_MASK)
	{
		case KVT_TYPE_FALSE:
		case KVT_TYPE_TRUE:
		case KVT_TYPE_NULL:
		case KVT_TYPE_NUMBER:
		case KVT_TYPE_STRING:
		case KVT_TYPE_RAW:
		case KVT_TYPE_ARRAY:
		case KVT_TYPE_OBJECT:
			break;

		default:
			return (FALSE);
	}

	// identical objects are equal
	if (a == b)
		return (TRUE);

	switch (a->type & KVT_TYPE_MASK)
	{
		// in these cases and equal type is enough
		case KVT_TYPE_FALSE:
		case KVT_TYPE_TRUE:
		case KVT_TYPE_NULL:
			return (TRUE);

		case KVT_TYPE_NUMBER:
			if (F64_Equals(a->value_number, b->value_number))
				return (TRUE);
			return (FALSE);

		case KVT_TYPE_STRING:
		case KVT_TYPE_RAW:
			if ((a->value_string == NULL) || (b->value_string == NULL))
				return (FALSE);
			if (String_Compare(a->value_string, b->value_string) == 0)
				return (TRUE);
			return (FALSE);

		case KVT_TYPE_ARRAY:
		{
			s_kvt* a_element = a->child;
			s_kvt* b_element = b->child;

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

		case KVT_TYPE_OBJECT:
		{
			s_kvt* a_element = NULL;
			s_kvt* b_element = NULL;

			foreach (s_kvt*, a_element, s_kvt, a)
			{
				// TODO This has O(n^2) runtime, which is horrible!
				b_element = case_sensitive ?
					KVT_GetObjectItem_CaseSensitive(b, a_element->key) :
					KVT_GetObjectItem(b, a_element->key);
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
					KVT_GetObjectItem(a, b_element->key);
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
