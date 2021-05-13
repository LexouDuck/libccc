
#include "libccc/stringarray.h"



t_char**	StringArray_Append(t_char** *a_dest, t_char const** src)
{
	t_char**	tmp;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, a_dest)
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, src)
	tmp = StringArray_Join((t_char const**)*a_dest, src);
	StringArray_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



t_char**	StringArray_Prepend(t_char const** src, t_char** *a_dest)
{
	t_char**	tmp;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, a_dest)
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, src)
	tmp = StringArray_Join(src, (t_char const**)*a_dest);
	StringArray_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



t_char**	StringArray_Insert_InPlace(t_char** *a_dest, t_char const** src, t_u32 index)
{
	t_char**	tmp;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, a_dest)
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, src)
	tmp = StringArray_Sub((t_char const**)*a_dest, 0, index);
	StringArray_Append(&tmp, src);
	StringArray_Append(&tmp, (t_char const**)(*a_dest) + index);
	StringArray_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}
