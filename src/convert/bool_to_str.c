
#include "libft_memory.h"
#include "libft_convert.h"



char*	Convert_Bool_To_String(t_bool number, t_bool uppercase)
{
	char*	result;

	if (number)
	{
		if (!(result = (char*)Memory_Alloc(5)))
			return (NULL);
		result[0] = uppercase ? 'T' : 't';
		result[1] = uppercase ? 'R' : 'r';
		result[2] = uppercase ? 'U' : 'u';
		result[3] = uppercase ? 'E' : 'e';
		result[4] = '\0';
	}
	else
	{
		if (!(result = (char*)Memory_Alloc(6)))
			return (NULL);
		result[0] = uppercase ? 'F' : 'f';
		result[1] = uppercase ? 'A' : 'a';
		result[2] = uppercase ? 'L' : 'l';
		result[3] = uppercase ? 'S' : 's';
		result[4] = uppercase ? 'E' : 'e';
		result[5] = '\0';
	}
	return (result);
}
