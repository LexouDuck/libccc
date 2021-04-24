
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/encode/json.h"



s_json*	JSON_CreateNull(void)
{
	s_json* item = JSON_New_Item();
	if (item)
	{
		item->type = JSON_TYPE_NULL;
	}
	return (item);
}

s_json*	JSON_CreateTrue(void)
{
	s_json* item = JSON_New_Item();
	if (item)
	{
		item->type = JSON_TYPE_TRUE;
	}
	return (item);
}

s_json*	JSON_CreateFalse(void)
{
	s_json* item = JSON_New_Item();
	if (item)
	{
		item->type = JSON_TYPE_FALSE;
	}
	return (item);
}

s_json*	JSON_CreateBool(t_bool boolean)
{
	s_json* item = JSON_New_Item();
	if (item)
	{
		item->type = boolean ? JSON_TYPE_TRUE : JSON_TYPE_FALSE;
	}
	return (item);
}

s_json*	JSON_CreateNumber(t_f64 num)
{
	s_json* item = JSON_New_Item();
	if (item)
	{
		item->type = JSON_TYPE_NUMBER;
		item->value_number = num;
	}
	return (item);
}

s_json*	JSON_CreateString(t_char const* string)
{
	s_json* item = JSON_New_Item();
	if (item)
	{
		item->type = JSON_TYPE_STRING;
		item->value_string = (t_char*)String_Duplicate((t_char const*)string);
		if (!item->value_string)
		{
			JSON_Delete(item);
			return (NULL);
		}
	}
	return (item);
}

s_json*	JSON_CreateStringReference(t_char const* string)
{
	s_json* item = JSON_New_Item();
	if (item != NULL)
	{
		item->type = JSON_TYPE_STRING | JSON_TYPE_ISREFERENCE;
		item->value_string = (t_char*)string;
	}
	return (item);
}

s_json*	JSON_CreateObjectReference(s_json const* child)
{
	s_json* item = JSON_New_Item();
	if (item != NULL)
	{
		item->type = JSON_TYPE_OBJECT | JSON_TYPE_ISREFERENCE;
		item->child = (s_json*)child;
	}
	return (item);
}

s_json*	JSON_CreateArrayReference(s_json const* child)
{
	s_json* item = JSON_New_Item();
	if (item != NULL)
	{
		item->type = JSON_TYPE_ARRAY | JSON_TYPE_ISREFERENCE;
		item->child = (s_json*)child;
	}
	return (item);
}

s_json*	JSON_CreateRaw(t_char const* raw)
{
	s_json* item = JSON_New_Item();
	if (item)
	{
		item->type = JSON_TYPE_RAW;
		item->value_string = (t_char*)String_Duplicate((t_char const*)raw);
		if (!item->value_string)
		{
			JSON_Delete(item);
			return (NULL);
		}
	}
	return (item);
}

s_json*	JSON_CreateArray(void)
{
	s_json* item = JSON_New_Item();
	if (item)
	{
		item->type=JSON_TYPE_ARRAY;
	}
	return (item);
}

s_json*	JSON_CreateObject(void)
{
	s_json* item = JSON_New_Item();
	if (item)
	{
		item->type = JSON_TYPE_OBJECT;
	}
	return (item);
}

// Create Arrays:
s_json*	JSON_CreateIntArray(const t_sint *numbers, t_sint count)
{
	t_size i = 0;
	s_json* n = NULL;
	s_json* p = NULL;
	s_json* a = NULL;

	if ((count < 0) || (numbers == NULL))
		return (NULL);

	a = JSON_CreateArray();

	for (i = 0; a && (i < (t_size)count); i++)
	{
		n = JSON_CreateNumber(numbers[i]);
		if (!n)
		{
			JSON_Delete(a);
			return (NULL);
		}
		if (!i)
		{
			a->child = n;
		}
		else
		{
			p->next = n;
			n->prev = p;
		}
		p = n;
	}

	if (a && a->child)
	{
		a->child->prev = n;
	}
	return (a);
}

s_json*	JSON_CreateFloatArray(const t_f32 *numbers, t_sint count)
{
	t_size i = 0;
	s_json* n = NULL;
	s_json* p = NULL;
	s_json* a = NULL;

	if ((count < 0) || (numbers == NULL))
		return (NULL);

	a = JSON_CreateArray();

	for (i = 0; a && (i < (t_size)count); i++)
	{
		n = JSON_CreateNumber((t_f64)numbers[i]);
		if (!n)
		{
			JSON_Delete(a);
			return (NULL);
		}
		if (!i)
		{
			a->child = n;
		}
		else
		{
			p->next = n;
			n->prev = p;
		}
		p = n;
	}

	if (a && a->child)
	{
		a->child->prev = n;
	}
	return (a);
}

s_json*	JSON_CreateDoubleArray(const t_f64 *numbers, t_sint count)
{
	t_size i = 0;
	s_json* n = NULL;
	s_json* p = NULL;
	s_json* a = NULL;

	if ((count < 0) || (numbers == NULL))
		return (NULL);

	a = JSON_CreateArray();

	for (i = 0; a && (i < (t_size)count); i++)
	{
		n = JSON_CreateNumber(numbers[i]);
		if (!n)
		{
			JSON_Delete(a);
			return (NULL);
		}
		if (!i)
		{
			a->child = n;
		}
		else
		{
			p->next = n;
			n->prev = p;
		}
		p = n;
	}

	if (a && a->child)
	{
		a->child->prev = n;
	}
	return (a);
}

s_json*	JSON_CreateStringArray(t_char const* const *strings, t_sint count)
{
	t_size i = 0;
	s_json* n = NULL;
	s_json* p = NULL;
	s_json* a = NULL;

	if ((count < 0) || (strings == NULL))
		return (NULL);

	a = JSON_CreateArray();

	for (i = 0; a && (i < (t_size)count); i++)
	{
		n = JSON_CreateString(strings[i]);
		if (!n)
		{
			JSON_Delete(a);
			return (NULL);
		}
		if (!i)
		{
			a->child = n;
		}
		else
		{
			p->next = n;
			n->prev = p;
		}
		p = n;
	}

	if (a && a->child)
	{
		a->child->prev = n;
	}
	
	return (a);
}
