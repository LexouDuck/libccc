
/*
**	Functions used from <stdlib.h>:
**	-	void	read(int fd, char* buffer, size_t n);
*/
#include <unistd.h>

#include "libft_memory.h"
#include "libft_string.h"
#include "libft_stringarray.h"
#include "libft_io.h"


static t_bool	ft_readfile_error(int result, char* *a_file)
{
	if (result < 0)
	{
		if (*a_file)
		{
			ft_memfree(*a_file);
			*a_file = NULL;
		}
		return (ERROR);
	}
	else
		return (OK);
}




#include <stdio.h>

t_bool		ft_readfile(t_fd const fd, char* *a_file, t_size max)
{
	int		result;
	char	buffer[BUFF_SIZE + 1] = {0};
	char*	file = NULL;
	t_size	length;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (a_file == NULL)
		return (ERROR);
#endif
	if (!(file = ft_strnew(0)))
		return (ERROR);
	if (max == 0)
		max = (t_size)-1;
	buffer[BUFF_SIZE] = '\0';
	length = 0;
	while ((result = read(fd, buffer, BUFF_SIZE)) > 0 &&
		(length += result) < max)
	{
printf("result %d, buffer = [[%s]]\n\n", result, buffer);
		if (result < BUFF_SIZE)
		{
			buffer[result] = '\0';
		}
		ft_strappend(&file, buffer);
	}
	*a_file = file;
printf("FULL FILE\n\n[[[%s]]]\nEND_FILE\n\n\n", file);
	return (ft_readfile_error(result, a_file));
}



t_bool		ft_readlines(t_fd const fd, char** *a_strarr)
{
	char*	file	= NULL; 
	char**	result	= NULL;
	t_bool	status	= OK;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (a_strarr == NULL)
		return (ERROR);
#endif
	status = ft_readfile(fd, &file, 0);
	if (status)
	{
		ft_strdel(&file);
		return (status);
	}
	result = ft_strsplit_str(file, "\n");
	String_Delete(&file);
	*a_strarr = result;
	return (OK);
}
