
/*
**	Functions used from <stdlib.h>:
**	-	void	read(int fd, char* buffer, size_t n);
*/
#include <unistd.h>

#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/array/stringarray.h"
#include "libccc/sys/io.h"


static t_io_error	IO_Read_File_Error(int result, char* *a_file)
{
	if (result < 0)
	{
		if (*a_file)
		{
			Memory_Free(*a_file);
			*a_file = NULL;
		}
		return (errno);
	}
	else return (OK);
}

t_io_error	IO_Read_File(t_fd const fd, char* *a_file, t_size max)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_file == NULL)
		return (ERROR);
#endif
	int		result;
	char	buffer[IO_BUFFER_SIZE + 1] = {0};
	char*	file = NULL;
	t_size	length;

	file = String_New(0);
	if (file == NULL)
		return (ERROR);
	if (max == 0)
		max = (t_size)-1;
	buffer[IO_BUFFER_SIZE] = '\0';
	length = 0;
	while ((result = read(fd, buffer, IO_BUFFER_SIZE)) > 0 &&
		(length += result) < max)
	{
		if (result < IO_BUFFER_SIZE)
		{
			buffer[result] = '\0';
		}
		String_Append(&file, buffer);
		if (file == NULL)
			return (ERROR);
	}
	*a_file = file;
	return (IO_Read_File_Error(result, a_file));
}



t_io_error	IO_Read_Lines(t_fd const fd, char** *a_strarr)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_strarr == NULL)
		return (ERROR);
#endif
	char*	file	= NULL; 
	char**	result	= NULL;
	t_bool	status	= OK;

	status = IO_Read_File(fd, &file, 0);
	if (status)
	{
		String_Delete(&file);
		return (status);
	}
	result = String_Split_String(file, "\n");
	String_Delete(&file);
	*a_strarr = result;
	return (OK);
}
