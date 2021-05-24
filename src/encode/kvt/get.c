
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

#include LIBCONFIG_HANDLE_INCLUDE



#define PARSE_KVTPATH_WHITESPACE(EXPECTED, ERRORMESSAGE) \
	while (str[i] && Char_IsSpace(str[i]))	{ ++i; }				\
	HANDLE_ERROR_MESSAGE(PARSE, (str[i] == '\0'),					\
		return (result);, PARSINGERROR_KVTPATH						\
			"Unexpected end of accessor string, "					\
			"expected %s "ERRORMESSAGE".\n",						\
			EXPECTED)												\

#define PARSE_KVTPATH_MATCH_CHAR(CHAR, ERRORMESSAGE) \
	HANDLE_ERROR_MESSAGE(PARSE, (str[i] != CHAR),					\
		return (result);, PARSINGERROR_KVTPATH						\
			"Expected char '%c' "ERRORMESSAGE", "					\
			"but instead found: '%c'\n",							\
			(CHAR ? CHAR : '\a'),									\
			(str[i] ? str[i] : '\a'))								\
	else ++i;														\

#define PARSE_KVTPATH_MATCH_STRING(STRING, ERRORMESSAGE) \
	HANDLE_ERROR_MESSAGE(PARSE,										\
		String_Compare_N(str + i, STRING, String_Length(STRING)),	\
		return (result);, PARSINGERROR_KVTPATH						\
			"Expected \"%s\" "ERRORMESSAGE", "						\
			"but instead found: '%.16s'\n",							\
			STRING, str)											\
	else ++i;														\



#define PARSINGERROR_KVTPATH	C_RED"ACCESSOR PATH PARSE ERROR"C_RESET": "



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
			i += length;
			t_u64 index = U64_FromString(accessor);
			result = KVT_GetArrayItem(result, index);
		}
		else if (str[i] == '\"')
		{	// string accessor
			PARSE_KVTPATH_MATCH_CHAR('"', "to begin string accessor")
			length = 0;
			while (str[i + length] != '\"')
			{
				HANDLE_ERROR_MESSAGE(PARSE, (str[i + length] == '\0'), return (result);, PARSINGERROR_KVTPATH
					"Unexpected end of accessor string, expected a closing double-quote '\"' t_char")
				++length;
			}
			accessor = String_Sub(str, i, length);
			i += length;
			PARSE_KVTPATH_MATCH_CHAR('"', "to end string accessor")
			result = KVT_GetObjectItem(result, accessor); // TODO find a smart way to handle this problem
		}
		else
		{
			HANDLE_ERROR_MESSAGE(PARSE, (TRUE), return (result);, PARSINGERROR_KVTPATH
				"Expected number or double-quoted string within brackets, but instead found: '%s'\n", str)
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



s_kvt*	KVT_GetArrayItem(s_kvt const* array, t_uint index)
{
	s_kvt* current_child;

	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (NULL);)
	current_child = array->value.child;
	while ((current_child != NULL) && (index > 0))
	{
		index--;
		current_child = current_child->next;
	}
	return (current_child);
}



static
s_kvt* get_object_item(s_kvt const* object, t_char const* name, t_bool case_sensitive)
{
	s_kvt* current_element = NULL;

	HANDLE_ERROR(NULLPOINTER, (object == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (name   == NULL), return (NULL);)
	current_element = object->value.child;
	if (case_sensitive)
	{
		while ((current_element != NULL) &&
			(current_element->key != NULL) &&
			String_Compare(name, current_element->key))
		{
			current_element = current_element->next;
		}
	}
	else
	{
		while ((current_element != NULL) &&
			String_Compare_IgnoreCase(name, current_element->key))
		{
			current_element = current_element->next;
		}
	}
	HANDLE_ERROR(KEYNOTFOUND,
		(current_element == NULL || current_element->key == NULL),
		return (NULL);)
	return (current_element);
}

s_kvt*	KVT_GetObjectItem_IgnoreCase(s_kvt const* object, t_char const* key)
{
	return (get_object_item(object, key, FALSE));
}

s_kvt*	KVT_GetObjectItem_CaseSensitive(s_kvt const* object, t_char const* key)
{
	return (get_object_item(object, key, TRUE));
}

t_bool	KVT_HasObjectItem_IgnoreCase(s_kvt const* object, t_char const* key)
{
	return (KVT_GetObjectItem_IgnoreCase(object, key) ? 1 : 0);
}

t_bool	KVT_HasObjectItem_CaseSensitive(s_kvt const* object, t_char const* key)
{
	return (KVT_GetObjectItem_CaseSensitive(object, key) ? 1 : 0);
}
