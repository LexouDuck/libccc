
#include "libccc.h"
#include "libccc/pointer.h"

#ifndef __NOSTD__
	#if (!defined(__GNUC__) && defined(__MSVC__))
	#include "libccc/compatibility/msvc/unistd.h"
	#else
	#include <unistd.h>
	#endif
#else
	int	read(int fd, char* buffer, size_t n);
#endif


#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"
#include "libccc/sys/io.h"

#include LIBCONFIG_ERROR_INCLUDE



t_sintmax	IO_Read_File(t_fd const fd, void* *a_file, t_size max)
{
	char		buffer[IO_BUFFER_SIZE + 1] = {0};
	t_sintmax	result;
	t_u8*		file = NULL;
	t_size		length;

	if CCCERROR((a_file == NULL), ERROR_NULLPOINTER, "destination address given is NULL")
		return (ERROR);
	file = (t_u8*)Memory_New(0);
	if CCCERROR((file == NULL), ERROR_ALLOCFAILURE, NULL)
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
		if CCCERROR((file == NULL), ERROR_ALLOCFAILURE, NULL)
		{
			*a_file = NULL;
			return (ERROR);
		}
	}
	*(t_u8* *)a_file = file;
	if CCCERROR((result < 0), ERROR_SYSTEM, 
		"error occurred while reading from fd#%i", fd)
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
	if CCCERROR((a_strarr == NULL), ERROR_NULLPOINTER, NULL) return (ERROR);
	t_char*		file	= NULL; 
	t_char**	result	= NULL;
	t_sintmax	status	= OK;

	status = IO_Read_File(fd, (void* *)&file, 0);
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

t_sintmax	IO_Read_Filepath(t_char const* filepath, void* *a_file)
{
	t_fd		fd = 0;
	t_sintmax	status = 0;

	fd = IO_Open(filepath, O_RDONLY, 0);
	if (fd < 0)
	{
		return (ERROR);
	}
	status = IO_Read_File(fd, a_file, 0);
	IO_Close(fd);

	return (status);
}

char*		IO_Read_Filepath_Text(t_char const* filepath)
{
	char*	result	= NULL;
	IO_Read_Filepath(filepath, (void* *)&result);
	return (result);
}
