
#include <stdarg.h>

#include "libccc.h"
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/sys/io.h"
#include "libccc/encode/common.h"



#define PARSE_KVTPATH_WHITESPACE(EXPECTED, ERRORMESSAGE) \
	while (str[i] && Char_IsSpace(str[i]))	{ ++i; }				\
	if (str[i] == '\0')												\
	{																\
		IO_Output_Format(C_RED"KVT PATH PARSE ERROR:"C_RESET		\
			"Unexpected end of accessor string, "					\
			"expected %s "ERRORMESSAGE".\n",						\
			EXPECTED);												\
		return (result);											\
	}																\

#define PARSE_KVTPATH_MATCH_CHAR(CHAR, ERRORMESSAGE) \
	if (str[i] != CHAR)												\
	{																\
		IO_Output_Format(C_RED"KVT PATH PARSE ERROR:"C_RESET		\
			"Expected t_char '%c' "ERRORMESSAGE", "					\
			"but instead found: '%c'\n",							\
			CHAR, str[i]);											\
		return (result);											\
	}																\
	else ++i;														\

#define PARSE_KVTPATH_MATCH_STRING(STRING, ERRORMESSAGE) \
	if (String_Compare_N(str + i, STRING, String_Length(STRING)))	\
	{																\
		IO_Output_Format(C_RED"KVT PATH PARSE ERROR:"C_RESET		\
			"Expected \"%s\" "ERRORMESSAGE", "						\
			"but instead found: '%.16s'\n",							\
			STRING, str);											\
		return (result);											\
	}																\
	else ++i;														\

_FORMAT(printf, 2, 3)
s_kvt*	KVT_Get(s_kvt const* object, t_char const* format_path, ...)
{
	va_list args;
	t_char*	path;
	t_char*	str;
	s_kvt*	result = NULL;
	t_size	length;
	t_char*	accessor;

	if (object == NULL || format_path == NULL)
		return (NULL);
	va_start(args, format_path);
	path = String_Format_VA(format_path, args);
	va_end(args);
	if (path == NULL)
		return (NULL);
	result = (s_kvt*)object;
	str = path;
	for (t_size i = 0; str[i]; ++i)
	{
		PARSE_KVTPATH_WHITESPACE("'['", "to begin accessor")
		PARSE_KVTPATH_MATCH_CHAR( '[',  "to begin accessor")
		PARSE_KVTPATH_WHITESPACE("number or string value", "accessor")
		if (Char_IsDigit(str[i]))
		{	// number accessor
			length = 1;
			while (Char_IsDigit(str[i + length]))
			{
				++length;
			}
			accessor = String_Sub(str, i, length);
			t_u64 index = U64_FromString(accessor);
			result = KVT_GetArrayItem(result, index);
		}
		else if (str[i] == '\"')
		{	// string accessor
			PARSE_KVTPATH_MATCH_CHAR('"', "to begin string accessor")
			length = 1;
			while (str[i + length] != '\"')
			{
				if (str[i + length] == '\0')
				{
					IO_Output_Line("Unexpected end of accessor string, expected a closing double-quote '\"' t_char");
					return (result);
				}
				++length;
			}
			PARSE_KVTPATH_MATCH_CHAR('"', "to end string accessor")
			accessor = String_Sub(str, i, length);
			result = KVT_GetObjectItem(result, accessor);
		}
		else
		{
			IO_Output_Format(C_RED"KVT PATH PARSE ERROR"C_RESET": "
				"Expected number or double-quoted string within brackets, but instead found: '%s'\n", str);
			return (result);
		}
		String_Delete(&accessor);
		PARSE_KVTPATH_WHITESPACE("']'", "to end accessor")
		PARSE_KVTPATH_MATCH_CHAR( ']',  "to end accessor")
	}
	return (result);
}



t_bool	KVT_GetValue_Boolean(s_kvt const* const item) 
{
	if (!KVT_IsBoolean(item)) 
		return ((t_bool)FALSE);
	return (item->value.number);
}

t_s64	KVT_GetValue_Integer(s_kvt const* const item) 
{
	if (!KVT_IsInteger(item)) 
		return ((t_s64)0);
	return (item->value.number);
}

t_f64	KVT_GetValue_Float(s_kvt const* const item) 
{
	if (!KVT_IsFloat(item)) 
		return ((t_f64)NAN);
	return (item->value.number);
}

t_char*	KVT_GetValue_String(s_kvt const* const item) 
{
	if (!KVT_IsString(item)) 
		return (NULL);
	return (item->value.string);
}



s_kvt*	KVT_GetArrayItem(s_kvt const* array, t_sint index)
{
	s_kvt* current_child;

	if (index < 0)
		return (NULL);
	if (array == NULL)
		return (NULL);
	current_child = array->value.child;
	while ((current_child != NULL) && (index > 0))
	{
		index--;
		current_child = current_child->next;
	}
	return (current_child);
}



static s_kvt* get_object_item(s_kvt const* const object, t_char const* const name, const t_bool case_sensitive)
{
	s_kvt* current_element = NULL;

	if ((object == NULL) || (name == NULL))
		return (NULL);

	current_element = object->value.child;
	if (case_sensitive)
	{
		while ((current_element != NULL) && (current_element->key != NULL) && (String_Compare(name, current_element->key) != 0))
		{
			current_element = current_element->next;
		}
	}
	else
	{
		while ((current_element != NULL) && (String_Compare_IgnoreCase(name, current_element->key) != 0))
		{
			current_element = current_element->next;
		}
	}
	if ((current_element == NULL) || (current_element->key == NULL))
		return (NULL);
	return (current_element);
}

s_kvt*	KVT_GetObjectItem(s_kvt const* const object, t_char const* const key)
{
	return (get_object_item(object, key, FALSE));
}

s_kvt*	KVT_GetObjectItem_CaseSensitive(s_kvt const* const object, t_char const* const key)
{
	return (get_object_item(object, key, TRUE));
}

t_bool	KVT_HasObjectItem(s_kvt const* object, t_char const* key)
{
	return (KVT_GetObjectItem(object, key) ? 1 : 0);
}
