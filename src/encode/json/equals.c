
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/encode/json.h"



t_bool	JSON_Equals(s_json const* const a, s_json const* const b, const t_bool case_sensitive)
{
	if ((a == NULL) || (b == NULL) || ((a->type & JSON_TYPE_MASK) != (b->type & JSON_TYPE_MASK)) || JSON_IsInvalid(a))
		return (FALSE);

	// check if type is valid
	switch (a->type & JSON_TYPE_MASK)
	{
		case JSON_TYPE_FALSE:
		case JSON_TYPE_TRUE:
		case JSON_TYPE_NULL:
		case JSON_TYPE_NUMBER:
		case JSON_TYPE_STRING:
		case JSON_TYPE_RAW:
		case JSON_TYPE_ARRAY:
		case JSON_TYPE_OBJECT:
			break;

		default:
			return (FALSE);
	}

	// identical objects are equal
	if (a == b)
		return (TRUE);

	switch (a->type & JSON_TYPE_MASK)
	{
		// in these cases and equal type is enough
		case JSON_TYPE_FALSE:
		case JSON_TYPE_TRUE:
		case JSON_TYPE_NULL:
			return (TRUE);

		case JSON_TYPE_NUMBER:
			if (F64_Equals(a->value_number, b->value_number))
				return (TRUE);
			return (FALSE);

		case JSON_TYPE_STRING:
		case JSON_TYPE_RAW:
			if ((a->value_string == NULL) || (b->value_string == NULL))
				return (FALSE);
			if (String_Compare(a->value_string, b->value_string) == 0)
				return (TRUE);
			return (FALSE);

		case JSON_TYPE_ARRAY:
		{
			s_json* a_element = a->child;
			s_json* b_element = b->child;

			for (; (a_element != NULL) && (b_element != NULL);)
			{
				if (!JSON_Equals(a_element, b_element, case_sensitive))
					return (FALSE);

				a_element = a_element->next;
				b_element = b_element->next;
			}

			// one of the arrays is longer than the other
			if (a_element != b_element)
				return (FALSE);
			return (TRUE);
		}

		case JSON_TYPE_OBJECT:
		{
			s_json* a_element = NULL;
			s_json* b_element = NULL;

			foreach (s_json*, a_element, s_json, a)
			{
				// TODO This has O(n^2) runtime, which is horrible!
				b_element = case_sensitive ?
					JSON_GetObjectItem_CaseSensitive(b, a_element->key) :
					JSON_GetObjectItem(b, a_element->key);
				if (b_element == NULL)
					return (FALSE);

				if (!JSON_Equals(a_element, b_element, case_sensitive))
					return (FALSE);
			}

			// Doing this twice, once on a and b to prevent TRUE comparison if a subset of b
			// TODO: Do this the proper way, this is just a fix for now */
			foreach (s_json*, b_element, s_json, b)
			{
				a_element = case_sensitive ?
					JSON_GetObjectItem_CaseSensitive(a, b_element->key) :
					JSON_GetObjectItem(a, b_element->key);
				if (a_element == NULL)
					return (FALSE);

				if (!JSON_Equals(b_element, a_element, case_sensitive))
					return (FALSE);
			}
			return (TRUE);
		}

		default:
			return (FALSE);
	}
}
