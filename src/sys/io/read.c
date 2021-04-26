#include <stdio.h>
/*
**	Functions used from <stdlib.h>:
**	-	void	read(int fd, char* buffer, size_t n);
*/
#include <unistd.h>
#include <errno.h>

#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"
#include "libccc/sys/io.h"



t_sintmax	IO_Read_File(t_fd const fd, char** a_file, t_size max)
{
	LIBCONFIG_HANDLE_NULLPOINTER(a_file, ERROR)
	char	buffer[IO_BUFFER_SIZE + 1] = {0};
	t_sintmax	result;
	char*	file = NULL;
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



t_sintmax	IO_Read_Lines(t_fd const fd, char** *a_strarr)
{
	LIBCONFIG_HANDLE_NULLPOINTER(a_strarr, ERROR)
	char*	file	= NULL; 
	char**	result	= NULL;
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
