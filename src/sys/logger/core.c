
#include <stdarg.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>

#include "libccc.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/array/stringarray.h"
#include "libccc/sys/time.h"
#include "libccc/sys/io.h"
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
	if (verbose_only && !logger.mode_verbose)
		return (OK);
	if (!logger.dest[LOGGER_DEST_STDOUT] &&
		!logger.dest[LOGGER_DEST_STDERR] &&
		!logger.dest[LOGGER_DEST_FILE])
		return (OK);

	char	error_str[BUFFERSIZE] = {0};

	if (use_errno)
	{
#ifdef __MINGW32__
		int error = WSAGetLastError();
		DWORD len = FormatMessageA(FORMAT_MESSAGE_ARGUMENT_ARRAY | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, error, 0, error_str, BUFFERSIZE, NULL);
		if (len)
			error_str[len] = '\0';
		else
			sprintf(error_str, "Error: %d", error);
#else
		strerror_r(errno, error_str, BUFFERSIZE);
#endif
	}

	char*	time_now_utc 	= Log_GetUnixDateTime(Time_Now());
	char*	full_format_str = NULL;
	char*	log_msg			= NULL;
	size_t	length = String_Length(time_now_utc);
	if (length > 0 && time_now_utc[length - 1] == '\n')
		time_now_utc[length - 1] = '\0';

	if (use_errno)
		full_format_str = String_Build("%s | %s%s%s"LOG_TIMESTAMP_INDENT"-> %s%s",
			time_now_utc,
			prefix,
			format_str,
			format_str[0] != '\0' && format_str[String_Length(format_str) - 1] == '\n' ? "" : "\n",
			error_str,
			error_str[0] != '\0' && error_str[String_Length(error_str) - 1] == '\n' ? "" : "\n");
	else
		full_format_str = String_Build("%s | %s%s%s",
			time_now_utc,
			prefix,
			format_str,
			format_str[String_Length(format_str) - 1] == '\n' ? "" : "\n");

	// NB: a va_list (in this case, 'args') can only be called ONCE, or else segfault
	if ((log_msg = String_Build_VA(full_format_str, args)) == NULL)
		Log_FatalError(logger, "Could not construct log message");
	else
	{
		if (logger.dest_stdout && logger.dest_stderr)
		{
			vLog_Write(logger,
				(is_error ? STDERR : STDOUT),
				(is_error ? "stderr" : "stdout"),
				log_msg);
		}
		else
		{
			if (logger.dest_stdout)
				vLog_Write(logger, STDOUT, "stdout", log_msg);
			if (logger.dest_stderr)
				vLog_Write(logger, STDERR, "stderr", log_msg);
		}
		if (logger.dest_file)
			vLog_Write(logger, logger.file_fd, "log file", log_msg);
	}

	String_Delete(&time_now_utc);
	String_Delete(&full_format_str);
	String_Delete(&log_msg);

	return (OK);
}
