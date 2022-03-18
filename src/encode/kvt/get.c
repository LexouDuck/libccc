
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
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/sys/io.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_ERROR_INCLUDE



#define PARSINGERROR_KVTPATH_MESSAGE \
	"\n""could not parse KVT_Get() accessor path string: "

#define PARSINGERROR_KVTPATH(CONDITION, ...) \
	HANDLE_ERROR_SF(PARSE, CONDITION, goto failure;,	\
		PARSINGERROR_KVTPATH_MESSAGE __VA_ARGS__		\
	)													\



#define PARSE_KVTPATH_WHITESPACE() \
	while (str[i] && Char_IsSpace(str[i]))	{ ++i; }				\

#define PARSE_KVTPATH_MATCH_CHAR(CHAR, ERRORMESSAGE) \
	PARSINGERROR_KVTPATH((str[i] != CHAR),							\
	else ++i;														\

#define PARSE_KVTPATH_MATCH_STRING(STRING, ERRORMESSAGE) \
	PARSINGERROR_KVTPATH(											\
		String_Compare_N(str + i, STRING, String_Length(STRING)),	\
		"Expected \"%s\" "ERRORMESSAGE", "							\
		"but instead found: '%.16s'\n",								\
		STRING, str)												\
	else ++i;														\



static
t_bool	KVT_Get_IsBareKeyChar(t_utf32 c)
{
	return (c == '-' || c == '_' || Char_IsAlphaNumeric(c));
}

s_kvt*	KVT_Get(s_kvt const* object, t_char const* format_path, ...)
{
	va_list args;
	t_char*	str = NULL;
	t_char*	key = NULL;
	s_kvt*	result = NULL;
	t_bool	bracket;
	t_size	length;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (object == NULL),      return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (format_path == NULL), return (NULL);)
	va_start(args, format_path);
	str = String_Format_VA(format_path, args);
	va_end(args);
	HANDLE_ERROR(ALLOCFAILURE, (str == NULL), return (NULL);)
	result = (s_kvt*)object;
	i = 0;
	PARSE_KVTPATH_WHITESPACE()
	if (str[i] == '\0') // empty accessor string
		return (result);
	while (str[i])
	{
		if (str[i] == '[')
		{
			bracket = TRUE;
			++i;
		}
		else
		{
			bracket = FALSE;
			if (str[i] == '.')
				++i;
		}

		PARSE_KVTPATH_WHITESPACE()
		PARSINGERROR_KVTPATH((str[i] == '\0'),
			"Unexpected end of accessor string: \"%s\"", str)
		if (str[i] == '-' ||
			str[i] == '+' ||
			Char_IsDigit(str[i]))
		{	// array accessor: integer
			length = 0;
			if (str[i] == '-' || str[i] == '+')
				length++;
			while (Char_IsDigit(str[i + length]))
			{
				++length;
			}
			key = String_Sub(str, i, length);
			HANDLE_ERROR(ALLOCFAILURE, (key == NULL), goto failure;)
			i += length;
			t_s64 index = S64_FromString(key);
			result = KVT_GetArrayItem(result, index);
			HANDLE_ERROR_SF(NOTFOUND, (result == NULL), goto failure;,
				"no item in array at index "SF_S64, index)
		}
		else if (KVT_Get_IsBareKeyChar(str[i]))
		{	// object accessor: bare key
			length = 0;
			while (KVT_Get_IsBareKeyChar(str[i + length]))
			{
				++length;
			}
			key = String_Sub(str, i, length);
			HANDLE_ERROR(ALLOCFAILURE, (key == NULL), goto failure;)
			i += length;
			result = KVT_GetObjectItem(result, key); // TODO find a smart way to handle this problem
			HANDLE_ERROR_SF(KEYNOTFOUND, (result == NULL), goto failure;,
				"no key in object matching \"%s\"", key)
		}
		else if (str[i] == '\"')
		{	// object accessor: quoted key
			++i;
			length = 0;
			while (str[i + length] != '\"')
			{
				PARSINGERROR_KVTPATH((str[i + length] == '\0'),
					"Unexpected end of accessor string, expected a closing double-quote '\"' t_char")
				++length;
			}
			key = String_Sub(str, i, length);
			HANDLE_ERROR(ALLOCFAILURE, (key == NULL), goto failure;)
			i += length;
			++i;
			result = KVT_GetObjectItem(result, key); // TODO find a smart way to handle this problem
			HANDLE_ERROR_SF(KEYNOTFOUND, (result == NULL), goto failure;,
				"no key in object matching \"%s\"", key)
		}
		else
		{
			PARSINGERROR_KVTPATH((TRUE),
				"Expected number or double-quoted string within brackets, but instead found: '%s'\n", str + i)
		}

		if (key)
			String_Delete(&key);
		PARSE_KVTPATH_WHITESPACE()

		if (str[i] == ']')
		{
			PARSINGERROR_KVTPATH((bracket == FALSE),
				"Unexpected closing bracket encountered: \"%s\"", str + i)
			else ++i;
		}
		else
		{
			PARSINGERROR_KVTPATH((bracket == TRUE),
				"Expected closing bracket ']' char, instead found: \"%s\"", str + i)
		}
/*
		PARSINGERROR_KVTPATH((TRUE),
			"Expected separator accessor path string, "
			"but instead found: '%c'/0x%4.4X\n",
			(str[i] ? str[i] : '\a'),	str[i])
		PARSE_KVTPATH_WHITESPACE()
*/
	}
	if (str) { String_Delete(&str); }
	if (key) { String_Delete(&key); }
	return (result);

failure:
	if (str) { String_Delete(&str); }
	if (key) { String_Delete(&key); }
	return (NULL);
}



static
t_char const*	KVT_GetTypeName(t_dynamic type)
{
	type &= DYNAMICTYPE_MASK;
	if (Memory_CountBits(type) != 1)
		return ("INVALID");
	else if (type & DYNAMICTYPE_BOOLEAN)	return ("BOOLEAN");
	else if (type & DYNAMICTYPE_INTEGER)	return ("INTEGER");
	else if (type & DYNAMICTYPE_FLOAT)		return ("FLOAT");
	else if (type & DYNAMICTYPE_STRING)		return ("STRING");
	else if (type & DYNAMICTYPE_ARRAY)		return ("ARRAY");
	else if (type & DYNAMICTYPE_OBJECT)		return ("OBJECT");
	else if (type & DYNAMICTYPE_RAW)		return ("RAW");
	else return ("INVALID");
}



t_bool	KVT_GetValue_Boolean(s_kvt const* item) 
{
	HANDLE_ERROR(NULLPOINTER, (item == NULL),			return ((t_bool)FALSE);)
	HANDLE_ERROR_SF(WRONGTYPE, (!KVT_IsBoolean(item)),	return ((t_bool)FALSE);,
		"attempted to read value as boolean for key \"%s\", but type is %s", item->key, KVT_GetTypeName(item->type))
	return (item->value.boolean);
}

t_s64	KVT_GetValue_Integer(s_kvt const* item) 
{
	HANDLE_ERROR(NULLPOINTER, (item == NULL),			return ((t_s64)0);)
	HANDLE_ERROR_SF(WRONGTYPE, (!KVT_IsInteger(item)),	return ((t_s64)0);,
		"attempted to read value as integer for key \"%s\", but type is %s", item->key, KVT_GetTypeName(item->type))
	return (item->value.integer);
}

t_f64	KVT_GetValue_Float(s_kvt const* item) 
{
	HANDLE_ERROR(NULLPOINTER, (item == NULL),			return ((t_f64)NAN);)
	HANDLE_ERROR_SF(WRONGTYPE, (!KVT_IsFloat(item)),	return ((t_f64)NAN);,
		"attempted to read value as float for key \"%s\", but type is %s", item->key, KVT_GetTypeName(item->type))
	return (item->value.number);
}

t_char*	KVT_GetValue_String(s_kvt const* item) 
{
	HANDLE_ERROR(NULLPOINTER, (item == NULL),			return (NULL);)
	HANDLE_ERROR_SF(WRONGTYPE, (!KVT_IsString(item)),	return (NULL);,
		"attempted to read value as string for key \"%s\", but type is %s", item->key, KVT_GetTypeName(item->type))
	return (item->value.string);
}



s_kvt*	KVT_GetArrayItem(s_kvt const* array, t_sint index)
{
	s_kvt* item;
	t_sint i;

	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (NULL);)
	HANDLE_ERROR_SF(WRONGTYPE, (!KVT_IsArray(array) && !KVT_IsObject(array)), return (NULL);,
		"attempted to read value as array for key \"%s\", but type is %s", array->key, KVT_GetTypeName(array->type))
	item = array->value.child;
	HANDLE_ERROR_SF(NOTFOUND, (item == NULL),
		return (NULL);,
		"no item in array at index %i", index)
	i = index;
	if (i == 0)
		return (item);
	else if (i > 0)
	{	// positive index
		while (item && (i > 0))
		{
			i--;
			item = item->next;
		}
	}
	else if (i < 0)
	{	// negative index
		while (item && (i < 0))
		{
			i++;
			item = item->prev;
		}
	}
	HANDLE_ERROR_SF(NOTFOUND, (item == NULL),
		return (NULL);,
		"no item in array at index %i", index)
	return (item);
}



static
s_kvt* KVT_GetObjectItem_(s_kvt const* object, t_char const* key, t_bool case_sensitive, t_bool error)
{
	s_kvt* item = NULL;

	HANDLE_ERROR(NULLPOINTER, (object == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (key == NULL), return (NULL);)
	HANDLE_ERROR_SF(WRONGTYPE, (!KVT_IsArray(object) && !KVT_IsObject(object)), return (NULL);,
		"attempted to read value as object for key \"%s\", but type is %s", object->key, KVT_GetTypeName(object->type))
	item = object->value.child;
	while (item)
	{
		if (item->key && (case_sensitive ?
			String_Equals(key, item->key) :
			String_Equals_IgnoreCase(key, item->key)))
			return (item);
		item = item->next;
	}
	HANDLE_ERROR_SF(KEYNOTFOUND, (error),
		return (NULL);,
		"no key in object matching \"%s\"", key)
	return (NULL);
}

s_kvt*	KVT_GetObjectItem_IgnoreCase(s_kvt const* object, t_char const* key)
{
	return (KVT_GetObjectItem_(object, key, FALSE, FALSE));
}

s_kvt*	KVT_GetObjectItem_CaseSensitive(s_kvt const* object, t_char const* key)
{
	return (KVT_GetObjectItem_(object, key, TRUE, FALSE));
}

t_bool	KVT_HasObjectItem_IgnoreCase(s_kvt const* object, t_char const* key)
{
	return (KVT_GetObjectItem_(object, key, FALSE, TRUE) ? TRUE : FALSE);
}

t_bool	KVT_HasObjectItem_CaseSensitive(s_kvt const* object, t_char const* key)
{
	return (KVT_GetObjectItem_(object, key, TRUE, TRUE) ? TRUE : FALSE);
}
