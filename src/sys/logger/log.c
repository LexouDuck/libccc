
#include <stdarg.h>

#include "libccc/sys/io.h"
#include "libccc/sys/logger.h"



t_io_error	Log(s_logger const* logger,
	t_bool verbose_only,
	t_bool is_error,
	t_bool use_errno,
	char const* format_str, ...)
{
	t_io_error	result;
	va_list		args;

	va_start(args, format_str);
	result = Log_VA(logger,
		verbose_only, is_error, use_errno,
		"", NULL,
		format_str, args);
	va_end(args);
	return (result);
}



t_io_error	Log_Error(s_logger const* logger, char const* format_str, ...)
{
	t_io_error	result;
	va_list		args;

	va_start(args, format_str);
	result = Log_VA(logger,
		FALSE, TRUE, FALSE,
		"Error", C_RED,
		format_str, args);
	va_end(args);
	return (result);
}

t_io_error	Log_Error_IO(s_logger const* logger, char const* format_str, ...)
{
	t_io_error	result;
	va_list		args;

	va_start(args, format_str);
	result = Log_VA(logger,
		FALSE, TRUE, TRUE,
		"IO Error", C_RED,
		format_str, args);
	va_end(args);
	return (result);
}

// To be called when there is an important warning to show to the user
t_io_error	Log_Warning(s_logger const* logger, char const* format_str, ...)
{
	t_io_error	result;
	va_list		args;

	va_start(args, format_str);
	result = Log_VA(logger,
		FALSE, FALSE, FALSE,
		"Warning", C_YELLOW,
		format_str, args);
	va_end(args);
	return (result);
}

// To be called when there is an successful operation (or result) to notify the user of
t_io_error	Log_Success(s_logger const* logger, char const* format_str, ...)
{
	t_io_error	result;
	va_list		args;

	va_start(args, format_str);
	result = Log_VA(logger,
		FALSE, FALSE, FALSE,
		"Success", C_GREEN,
		format_str, args);
	va_end(args);
	return (result);
}

// To be called when there is user-useful data to be logged (operation successful with value X returned, etc)
t_io_error	Log_Message(s_logger const* logger, char const* format_str, ...)
{
	t_io_error	result;
	va_list		args;

	va_start(args, format_str);
	result = Log_VA(logger,
		FALSE, FALSE, FALSE,
		"", NULL,
		format_str, args);
	va_end(args);
	return (result);
}

// To be called when there is "verbose" data to be logged
t_io_error	Log_Message_Verbose(s_logger const* logger, char const* format_str, ...)
{
	t_io_error	result;
	va_list		args;

	va_start(args, format_str);
	result = Log_VA(logger,
		TRUE, FALSE, FALSE,
		"", NULL,
		format_str, args);
	va_end(args);
	return (result);
}
