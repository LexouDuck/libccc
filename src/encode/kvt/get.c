
#ifndef __NOSTD__
	#include <stdarg.h>
#else
	typedef __builtin_va_list va_list;
	#define va_start(v,l)	__builtin_va_start(v,l)
	#define va_end(v)		__builtin_va_end(v)
	#define va_arg(v,l)		__builtin_va_arg(v,l)
	#define va_copy(d,s)	__builtin_va_copy(d,s)
#endif

#include "libccc.h"
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/sys/io.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_ERROR_INCLUDE



#define PARSINGERROR_KVTPATH	"\n"C_RED"ACCESSOR PATH PARSE ERROR"C_RESET": "



#define PARSE_KVTPATH_WHITESPACE(EXPECTED, ERRORMESSAGE) \
	while (str[i] && Char_IsSpace(str[i]))	{ ++i; }				\
	HANDLE_ERROR_SF(PARSE, (str[i] == '\0'),						\
		return (NULL);,												\
		PARSINGERROR_KVTPATH										\
			"Unexpected end of accessor string, "					\
			"expected %s "ERRORMESSAGE".\n",						\
			EXPECTED)												\

#define PARSE_KVTPATH_MATCH_CHAR(CHAR, ERRORMESSAGE) \
	HANDLE_ERROR_SF(PARSE, (str[i] != CHAR),						\
		return (NULL);,												\
		PARSINGERROR_KVTPATH										\
			"Expected char '%c'/0x%4.4X "ERRORMESSAGE", "			\
			"but instead found: '%c'/0x%4.4X\n",					\
			(CHAR ? CHAR : '\a'),		CHAR,						\
			(str[i] ? str[i] : '\a'),	str[i])						\
	else ++i;														\

#define PARSE_KVTPATH_MATCH_STRING(STRING, ERRORMESSAGE) \
	HANDLE_ERROR_SF(PARSE,											\
		String_Compare_N(str + i, STRING, String_Length(STRING)),	\
		return (NULL);,												\
		PARSINGERROR_KVTPATH										\
			"Expected \"%s\" "ERRORMESSAGE", "						\
			"but instead found: '%.16s'\n",							\
			STRING, str)											\
	else ++i;														\



_FORMAT(printf, 2, 3)
s_kvt*	KVT_Get(s_kvt const* object, t_char const* format_path, ...)
{
	va_list args;
	t_char*	path;
	t_char*	str;
	t_char*	accessor;
	s_kvt*	result = NULL;
	t_size	length;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (object == NULL),      return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (format_path == NULL), return (NULL);)
	va_start(args, format_path);
	path = String_Format_VA(format_path, args);
	va_end(args);
	HANDLE_ERROR(ALLOCFAILURE, (path == NULL), return (NULL);)
	result = (s_kvt*)object;
	str = path;
	i = 0;
	while (str[i])
	{
		PARSE_KVTPATH_WHITESPACE("'['", "to begin accessor path string")
		PARSE_KVTPATH_MATCH_CHAR( '[',  "to begin accessor path string")
		PARSE_KVTPATH_WHITESPACE("number or string value", "accessor path string")
		if (str[i] == '-' ||
			str[i] == '+' ||
			Char_IsDigit(str[i]))
		{	// number accessor
			length = 0;
			if (str[i] == '-' || str[i] == '+')
				length++;
			while (Char_IsDigit(str[i + length]))
			{
				++length;
			}
			accessor = String_Sub(str, i, length);
			i += length;
			t_s64 index = S64_FromString(accessor);
			result = KVT_GetArrayItem(result, index);
			HANDLE_ERROR_SF(NOTFOUND, (result == NULL), return (NULL);,
				" in array for index "SF_S64, index)
		}
		else if (str[i] == '\"')
		{	// string accessor
			PARSE_KVTPATH_MATCH_CHAR('"', "to begin string accessor path string")
			length = 0;
			while (str[i + length] != '\"')
			{
				HANDLE_ERROR_SF(PARSE, (str[i + length] == '\0'), return (NULL);, PARSINGERROR_KVTPATH
					"Unexpected end of accessor string, expected a closing double-quote '\"' t_char")
				++length;
			}
			accessor = String_Sub(str, i, length);
			i += length;
			PARSE_KVTPATH_MATCH_CHAR('"', "to end string accessor path string")
			result = KVT_GetObjectItem(result, accessor); // TODO find a smart way to handle this problem
			HANDLE_ERROR_SF(NOTFOUND, (result == NULL), return (NULL);,
				": \"%s\"", accessor)
		}
		else
		{
			HANDLE_ERROR_SF(PARSE, (TRUE), return (NULL);, PARSINGERROR_KVTPATH
				"Expected number or double-quoted string within brackets, but instead found: '%s'\n", str)
		}
		String_Delete(&accessor);
		PARSE_KVTPATH_WHITESPACE("']'", "to end accessor path string")
		PARSE_KVTPATH_MATCH_CHAR( ']',  "to end accessor path string")
	}
	return (result);
}



t_bool	KVT_GetValue_Boolean(s_kvt const* item) 
{
	if (!KVT_IsBoolean(item)) 
		return ((t_bool)FALSE);
	return (item->value.number);
}

t_s64	KVT_GetValue_Integer(s_kvt const* item) 
{
	if (!KVT_IsInteger(item)) 
		return ((t_s64)0);
	return (item->value.number);
}

t_f64	KVT_GetValue_Float(s_kvt const* item) 
{
	if (!KVT_IsFloat(item)) 
		return ((t_f64)NAN);
	return (item->value.number);
}

t_char*	KVT_GetValue_String(s_kvt const* item) 
{
	if (!KVT_IsString(item)) 
		return (NULL);
	return (item->value.string);
}



s_kvt*	KVT_GetArrayItem(s_kvt const* array, t_sint index)
{
	s_kvt* item;

	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (NULL);)
	HANDLE_ERROR(WRONGTYPE, (!KVT_IsArray(array) && !KVT_IsObject(array)), return (NULL);)
	item = array->value.child;
	if (index == 0)
		return (item);
	else if (index > 0)
	{	// positive index
		while (item && (index > 0))
		{
			index--;
			item = item->next;
		}
	}
	else if (index < 0)
	{	// negative index
		while (item && (index < 0))
		{
			index++;
			item = item->prev;
		}
	}
	return (item);
}



static
s_kvt* KVT_GetObjectItem_(s_kvt const* object, t_char const* key, t_bool case_sensitive)
{
	s_kvt* current_element = NULL;

	HANDLE_ERROR(NULLPOINTER, (object == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (key   == NULL), return (NULL);)
	current_element = object->value.child;
	if (case_sensitive)
	{
		while ((current_element != NULL) &&
			(current_element->key != NULL) &&
			String_Compare(key, current_element->key))
		{
			current_element = current_element->next;
		}
	}
	else
	{
		while ((current_element != NULL) &&
			String_Compare_IgnoreCase(key, current_element->key))
		{
			current_element = current_element->next;
		}
	}
	HANDLE_ERROR_SF(KEYNOTFOUND,
		(current_element == NULL || current_element->key == NULL),
		return (NULL);,
		": \"%s\"", key)
	return (current_element);
}

s_kvt*	KVT_GetObjectItem_IgnoreCase(s_kvt const* object, t_char const* key)
{
	return (KVT_GetObjectItem_(object, key, FALSE));
}

s_kvt*	KVT_GetObjectItem_CaseSensitive(s_kvt const* object, t_char const* key)
{
	return (KVT_GetObjectItem_(object, key, TRUE));
}

t_bool	KVT_HasObjectItem_IgnoreCase(s_kvt const* object, t_char const* key)
{
	return (KVT_GetObjectItem_IgnoreCase(object, key) ? 1 : 0);
}

t_bool	KVT_HasObjectItem_CaseSensitive(s_kvt const* object, t_char const* key)
{
	return (KVT_GetObjectItem_CaseSensitive(object, key) ? 1 : 0);
}
