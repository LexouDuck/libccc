
#include "libccc.h"
#include "libccc/bool.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



static t_char const*	g_str_bool_uppercase[2] = { "FALSE", "TRUE" };
static t_char const*	g_str_bool_lowercase[2] = { "false", "true" };
//static t_char const*	g_str_bool_mixedcase[2] = { "False", "True" };



t_char const*	Bool_String(t_bool value, t_bool uppercase)
{
	t_char const* const*	lookup;

	lookup = (uppercase ? g_str_bool_uppercase : g_str_bool_lowercase);
	return (lookup[value]);
}



t_size	Bool_Print(t_char* dest, t_bool value, t_bool uppercase)
{
	t_char const* const*	lookup;
	t_size	length;

	HANDLE_ERROR(NULLPOINTER, (dest == NULL), return (0);)
	length = value ? sizeof("TRUE") : sizeof("FALSE");
	lookup = (uppercase ? g_str_bool_uppercase : g_str_bool_lowercase);
	String_Copy_N(dest, lookup[value], length);
	return (length);
}



t_char*	Bool_ToString(t_bool value, t_bool uppercase)
{
	t_char const* const*	lookup;

	lookup = (uppercase ? g_str_bool_uppercase : g_str_bool_lowercase);
	return (String_Duplicate(lookup[value]));
}
