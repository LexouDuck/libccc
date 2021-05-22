
#include "libccc/pointer.h"

#ifndef __NOSTD__
	#include <unistd.h>
#else
	int	read(int fd, char* buffer, size_t n);
#endif
#ifndef __NOSTD__
	#include <stdio.h>
#else
	void	perror(char const* str);
#endif

#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/monad/array.h"
#include "libccc/sys/io.h"

#include LIBCONFIG_HANDLE_INCLUDE



static
int		gnl_read(t_fd const fd, t_char** a_newline)
{
	static t_size	buf_pos = 0;
	static char		buffer[IO_BUFFER_SIZE + 1] = {0};
	int				status = 0;
	int				offset = 0;
	t_char*			temp = NULL;
	t_bool			end_of_buffer = FALSE;
	t_bool			done_new_line = FALSE;

	if (!(*a_newline = String_New(0)))
		return (GNL_ERROR);
	while (!done_new_line)
	{
		if (buf_pos == IO_BUFFER_SIZE)
			end_of_buffer = TRUE;
		if (end_of_buffer)
		{
			buf_pos = 0;
			end_of_buffer = FALSE;
			Memory_Clear(buffer, IO_BUFFER_SIZE);
			status = read(fd, buffer, IO_BUFFER_SIZE);
			if (status < 0)
			{
				perror("getnextline: couldn't read file");
				return (GNL_ERROR);
			}
			if (status == 0)
				return (GNL_END);
		}
		temp = String_Find_Char(buffer + buf_pos, '\n');
		if (temp == NULL)
		{
			String_Append(a_newline, buffer + buf_pos);
			end_of_buffer = TRUE;
		}
		else
		{
			offset = temp - (buffer + buf_pos);
			temp = String_Duplicate_N(buffer + buf_pos, offset);
			String_Append(a_newline, temp);
			String_Delete(&temp);
			buf_pos += offset + 1;
			return (GNL_LINE);
		}
	}
	return (status);
}



int		IO_Read_NextLine(t_fd const fd, t_char** a_line)
{
	t_char*			new_line = NULL;
	int				status = GNL_ERROR;

	if (a_line == NULL || fd < 0)
		return (GNL_ERROR);
	new_line = NULL;
	status = gnl_read(fd, &new_line);
	if (status < 0)
	{
		String_Delete(&new_line);
		return (GNL_ERROR);
	}
	*a_line = new_line;
	return (status);
}
