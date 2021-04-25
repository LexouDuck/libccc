
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/encode/common.h"



s_kvt*	KVT_CreateNull(void)
{
	s_kvt* item = KVT_New_Item();
	if (item)
	{
		item->type = KVT_TYPE_NULL;
	}
	return (item);
}

s_kvt*	KVT_CreateTrue(void)
{
	s_kvt* item = KVT_New_Item();
	if (item)
	{
		item->type = KVT_TYPE_TRUE;
	}
	return (item);
}

s_kvt*	KVT_CreateFalse(void)
{
	s_kvt* item = KVT_New_Item();
	if (item)
	{
		item->type = KVT_TYPE_FALSE;
	}
	return (item);
}

s_kvt*	KVT_CreateBool(t_bool boolean)
{
	s_kvt* item = KVT_New_Item();
	if (item)
	{
		item->type = boolean ? KVT_TYPE_TRUE : KVT_TYPE_FALSE;
	}
	return (item);
}

s_kvt*	KVT_CreateNumber(t_f64 num)
{
	s_kvt* item = KVT_New_Item();
	if (item)
	{
		item->type = KVT_TYPE_NUMBER;
		item->value_number = num;
	}
	return (item);
}

s_kvt*	KVT_CreateString(t_char const* string)
{
	s_kvt* item = KVT_New_Item();
	if (item)
	{
		item->type = KVT_TYPE_STRING;
		item->value_string = (t_char*)String_Duplicate((t_char const*)string);
		if (!item->value_string)
		{
			KVT_Delete(item);
			return (NULL);
		}
	}
	return (item);
}

s_kvt*	KVT_CreateStringReference(t_char const* string)
{
	s_kvt* item = KVT_New_Item();
	if (item != NULL)
	{
		item->type = KVT_TYPE_STRING | KVT_TYPE_ISREFERENCE;
		item->value_string = (t_char*)string;
	}
	return (item);
}

s_kvt*	KVT_CreateObjectReference(s_kvt const* child)
{
	s_kvt* item = KVT_New_Item();
	if (item != NULL)
	{
		item->type = KVT_TYPE_OBJECT | KVT_TYPE_ISREFERENCE;
		item->child = (s_kvt*)child;
	}
	return (item);
}

s_kvt*	KVT_CreateArrayReference(s_kvt const* child)
{
	s_kvt* item = KVT_New_Item();
	if (item != NULL)
	{
		item->type = KVT_TYPE_ARRAY | KVT_TYPE_ISREFERENCE;
		item->child = (s_kvt*)child;
	}
	return (item);
}

s_kvt*	KVT_CreateRaw(t_char const* raw)
{
	s_kvt* item = KVT_New_Item();
	if (item)
	{
		item->type = KVT_TYPE_RAW;
		item->value_string = (t_char*)String_Duplicate((t_char const*)raw);
		if (!item->value_string)
		{
			KVT_Delete(item);
			return (NULL);
		}
	}
	return (item);
}

s_kvt*	KVT_CreateArray(void)
{
	s_kvt* item = KVT_New_Item();
	if (item)
	{
		item->type=KVT_TYPE_ARRAY;
	}
	return (item);
}

s_kvt*	KVT_CreateObject(void)
{
	s_kvt* item = KVT_New_Item();
	if (item)
	{
		item->type = KVT_TYPE_OBJECT;
	}
	return (item);
}

// Create Arrays:
s_kvt*	KVT_CreateIntArray(const t_sint *numbers, t_sint count)
{
	t_size i = 0;
	s_kvt* n = NULL;
	s_kvt* p = NULL;
	s_kvt* a = NULL;

	if ((count < 0) || (numbers == NULL))
		return (NULL);

	a = KVT_CreateArray();

	for (i = 0; a && (i < (t_size)count); i++)
	{
		n = KVT_CreateNumber(numbers[i]);
		if (!n)
		{
			KVT_Delete(a);
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

s_kvt*	KVT_CreateFloatArray(const t_f32 *numbers, t_sint count)
{
	t_size i = 0;
	s_kvt* n = NULL;
	s_kvt* p = NULL;
	s_kvt* a = NULL;

	if ((count < 0) || (numbers == NULL))
		return (NULL);

	a = KVT_CreateArray();

	for (i = 0; a && (i < (t_size)count); i++)
	{
		n = KVT_CreateNumber((t_f64)numbers[i]);
		if (!n)
		{
			KVT_Delete(a);
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

s_kvt*	KVT_CreateDoubleArray(const t_f64 *numbers, t_sint count)
{
	t_size i = 0;
	s_kvt* n = NULL;
	s_kvt* p = NULL;
	s_kvt* a = NULL;

	if ((count < 0) || (numbers == NULL))
		return (NULL);

	a = KVT_CreateArray();

	for (i = 0; a && (i < (t_size)count); i++)
	{
		n = KVT_CreateNumber(numbers[i]);
		if (!n)
		{
			KVT_Delete(a);
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

s_kvt*	KVT_CreateStringArray(t_char const* const *strings, t_sint count)
{
	t_size i = 0;
	s_kvt* n = NULL;
	s_kvt* p = NULL;
	s_kvt* a = NULL;

	if ((count < 0) || (strings == NULL))
		return (NULL);

	a = KVT_CreateArray();

	for (i = 0; a && (i < (t_size)count); i++)
	{
		n = KVT_CreateString(strings[i]);
		if (!n)
		{
			KVT_Delete(a);
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
