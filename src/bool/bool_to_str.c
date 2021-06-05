
#include "libccc/char.h"
#include "libccc/bool.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char*	Bool_ToString(t_bool value, t_bool uppercase)
{
	t_char*	result;

	result = (t_char*)Memory_Allocate(value ? 5 : 6);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	if (value)
	{
		result[0] = uppercase ? 'T' : 't';
		result[1] = uppercase ? 'R' : 'r';
		result[2] = uppercase ? 'U' : 'u';
		result[3] = uppercase ? 'E' : 'e';
		result[4] = '\0';
	}
	else
	{
		result[0] = uppercase ? 'F' : 'f';
		result[1] = uppercase ? 'A' : 'a';
		result[2] = uppercase ? 'L' : 'l';
		result[3] = uppercase ? 'S' : 's';
		result[4] = uppercase ? 'E' : 'e';
		result[5] = '\0';
	}
	return (result);
}
