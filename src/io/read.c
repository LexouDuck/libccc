
/*
**	Functions used from <stdlib.h>:
**	-	void	read(int fd, char* buffer, size_t n);
*/
#include <unistd.h>

#include "libccc_memory.h"
#include "libccc_string.h"
#include "libccc_stringarray.h"
#include "libccc_io.h"


static t_bool	c_readfile_error(int result, char* *a_file)
{
	if (result < 0)
	{
		if (*a_file)
		{
			c_memfree(*a_file);
			*a_file = NULL;
		}
		return (ERROR);
	}
	else
		return (OK);
}

t_bool		c_readfile(t_fd const fd, char* *a_file, t_size max)
{
	int		result;
	char	buffer[BUFF_SIZE + 1] = {0};
	char*	file = NULL;
	t_size	length;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_file == NULL)
		return (ERROR);
#endif
	if (!(file = c_strnew(0)))
		return (ERROR);
	if (max == 0)
		max = (t_size)-1;
	buffer[BUFF_SIZE] = '\0';
	length = 0;
	while ((result = read(fd, buffer, BUFF_SIZE)) > 0 &&
		(length += result) < max)
	{
		if (result < BUFF_SIZE)
		{
			buffer[result] = '\0';
		}
		c_strappend(&file, buffer);
	}
	*a_file = file;
	return (c_readfile_error(result, a_file));
}



t_bool		c_readlines(t_fd const fd, char** *a_strarr)
{
	char*	file	= NULL; 
	char**	result	= NULL;
	t_bool	status	= OK;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_strarr == NULL)
		return (ERROR);
#endif
	status = c_readfile(fd, &file, 0);
	if (status)
	{
		c_strdel(&file);
		return (status);
	}
	result = c_strsplit_str(file, "\n");
	String_Delete(&file);
	*a_strarr = result;
	return (OK);
}
