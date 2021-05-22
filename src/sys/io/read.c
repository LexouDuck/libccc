
#include "libccc/pointer.h"

#ifndef __NOSTD__
	#include <unistd.h>
#else
	int	read(int fd, char* buffer, size_t n);
#endif


#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"
#include "libccc/sys/io.h"



t_sintmax	IO_Read_File(t_fd const fd, t_char** a_file, t_size max)
{
	HANDLE_ERROR(NULLPOINTER, (a_file == NULL), return (ERROR);)
	char	buffer[IO_BUFFER_SIZE + 1] = {0};
	t_sintmax	result;
	t_char*	file = NULL;
	t_size	length;

	file = String_New(0);
	if (file == NULL)
	{
		*a_file = NULL;
		return (ERROR);
	}
	if (max == 0)
		max = (t_size)-1;
	buffer[IO_BUFFER_SIZE] = '\0';
	length = 0;
	while ((result = read(fd, buffer, IO_BUFFER_SIZE)) > 0 && (length += result) < max)
	{
		if (result < IO_BUFFER_SIZE)
		{
			buffer[result] = '\0';
		}
		Memory_Append((void**)&file, length - result, buffer, result);
		if (file == NULL)
		{
			*a_file = NULL;
			return (ERROR);
		}
	}
	*a_file = file;
	if (result < 0)
	{
		if (*a_file)
		{	// free the (likely to be incorrect) buffer
			Memory_Free(*a_file);
			*a_file = NULL;
		}
		return (result);
	}
	return (length);
}



t_sintmax	IO_Read_Lines(t_fd const fd, t_char** *a_strarr)
{
	HANDLE_ERROR(NULLPOINTER, (a_strarr == NULL), return (ERROR);)
	t_char*	file	= NULL; 
	t_char**	result	= NULL;
	t_sintmax	status	= OK;

	status = IO_Read_File(fd, &file, 0);
	if (status < 0)
	{
		String_Delete(&file);
		return (status);
	}
	result = String_Split_String(file, "\n");
	String_Delete(&file);
	*a_strarr = result;
	return (OK);
}
