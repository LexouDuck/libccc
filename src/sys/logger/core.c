
#include <stdarg.h>

#include "libccc.h"
#include "libccc/string.h"
#include "libccc/sys/io.h"
#include "libccc/sys/time.h"
#include "libccc/sys/logger.h"



static inline void vLog_Write(s_logger const* logger, t_fd fd, char const* output, char const* log_msg)
{
	int status = IO_Write_String(fd, log_msg);
	if (status < 0)
	{
		char* tmp = String_Join("Could not write log message to ", output);
		Log_FatalError(logger, tmp);
		String_Delete(&tmp);
	}
}



int	vLog(s_logger const* logger,
	t_bool 			verbose_only,
	t_bool			is_error,
	t_bool 			use_errno,
	char const*		prefix,
	char const*		prefix_color,
	char const*		format_str,
	va_list			args)
{
	if (verbose_only && !logger->mode_verbose)
		return (OK);

	char*	error_str;
	if (use_errno)
	{
		error_str = IO_GetError(errno);
	}
	char*	full_format_str = NULL;
	char*	log_msg			= NULL;
	char*	timestamp = logger->show_timestamp ? Log_GetUnixDateTime(Time_Now()) : NULL;
/*
	size_t	length = String_Length(time_now_utc);
	if (length > 0 && time_now_utc[length - 1] == '\n')
		time_now_utc[length - 1] = '\0';
*/
	if (use_errno)
	{
		full_format_str = String_Format("%s%s%s%s%s%s%s-> %s%s",
			timestamp ? timestamp : "",
			prefix_color ? prefix_color : "",
			prefix,
			prefix_color ? C_RESET : "",
			format_str,
			format_str[0] != '\0' && format_str[String_Length(format_str) - 1] == '\n' ? "" : "\n",
			timestamp ? LOG_TIMESTAMP_INDENT : " ",
			error_str,
			error_str[0] != '\0' && error_str[String_Length(error_str) - 1] == '\n' ? "" : "\n");
	}
	else
	{
		full_format_str = String_Format("%s%s%s%s%s%s",
			timestamp ? timestamp : "",
			prefix_color ? prefix_color : "",
			prefix,
			prefix_color ? C_RESET : "",
			format_str,
			format_str[String_Length(format_str) - 1] == '\n' ? "" : "\n");
	}

	// NB: a va_list (in this case, 'args') can only be called ONCE, or else segfault
	log_msg = String_Format_VA(full_format_str, args);
	if (log_msg == NULL)
		Log_FatalError(logger, "Could not construct log message");
	else
	{
		if (logger->dest_stdout && logger->dest_stderr)
		{
			vLog_Write(logger,
				(is_error ? STDERR : STDOUT),
				(is_error ? "stderr" : "stdout"),
				log_msg);
		}
		else
		{
			if (logger->dest_stdout)
				vLog_Write(logger, STDOUT, "stdout", log_msg);
			if (logger->dest_stderr)
				vLog_Write(logger, STDERR, "stderr", log_msg);
		}
		for (t_uint i = 0; i < LOGFILES_MAX; ++i)
		{
			if (logger->dest_files[i].path)
			{
				vLog_Write(logger,
					logger->dest_files[i].fd,
					logger->dest_files[i].path,
					log_msg);
			}
		}
	}

	String_Delete(&timestamp);
	String_Delete(&full_format_str);
	String_Delete(&log_msg);

	return (OK);
}
