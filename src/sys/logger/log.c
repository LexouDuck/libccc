
#include <stdarg.h>

#include "libccc/sys/io.h"
#include "libccc/sys/logger.h"



t_io_error	LogAll(s_logptr_array loggers,
	t_bool verbose_only,
	t_bool is_error,
	t_bool use_errno,
	char const* format_str, ...)
{
	t_io_error	result;
	va_list		args;

	for (t_u32 i = 0; i < loggers.length; ++i)
	{
		va_start(args, format_str);
		result = Log_VA(loggers.logptrs[i],
			verbose_only, is_error, use_errno,
			"", NULL,
			format_str, args);
		va_end(args);
	}
	return (result);
}



t_io_error	LogAll_Error(s_logptr_array loggers, int error_code, char const* format_str, ...)
{
	t_io_error	result;
	va_list		args;

	for (t_u32 i = 0; i < loggers.length; ++i)
	{
		va_start(args, format_str);
		result = Log_VA(loggers.logptrs[i],
			FALSE, FALSE, error_code,
			"Error", C_RED,
			format_str, args);
		va_end(args);
	}
	return (result);
}

t_io_error	LogAll_Error_IO(s_logptr_array loggers, int error_code, char const* format_str, ...)
{
	t_io_error	result;
	va_list		args;

	for (t_u32 i = 0; i < loggers.length; ++i)
	{
		va_start(args, format_str);
		result = Log_VA(loggers.logptrs[i],
			FALSE, TRUE, error_code,
			"IO Error", C_RED,
			format_str, args);
		va_end(args);
	}
	return (result);
}

// To be called when there is an important warning to show to the user
t_io_error	LogAll_Warning(s_logptr_array loggers, char const* format_str, ...)
{
	t_io_error	result;
	va_list		args;

	for (t_u32 i = 0; i < loggers.length; ++i)
	{
		va_start(args, format_str);
		result = Log_VA(loggers.logptrs[i],
			FALSE, FALSE, 0,
			"Warning", C_YELLOW,
			format_str, args);
		va_end(args);
	}
	return (result);
}

// To be called when there is an successful operation (or result) to notify the user of
t_io_error	LogAll_Success(s_logptr_array loggers, char const* format_str, ...)
{
	t_io_error	result;
	va_list		args;

	for (t_u32 i = 0; i < loggers.length; ++i)
	{
		va_start(args, format_str);
		result = Log_VA(loggers.logptrs[i],
			FALSE, FALSE, 0,
			"Success", C_GREEN,
			format_str, args);
		va_end(args);
	}
	return (result);
}

// To be called when there is user-useful data to be logged (operation successful with value X returned, etc)
t_io_error	LogAll_Message(s_logptr_array loggers, char const* format_str, ...)
{
	t_io_error	result;
	va_list		args;

	for (t_u32 i = 0; i < loggers.length; ++i)
	{
		va_start(args, format_str);
		result = Log_VA(loggers.logptrs[i],
			FALSE, FALSE, 0,
			"", NULL,
			format_str, args);
		va_end(args);
	}
	return (result);
}

// To be called when there is "verbose" data to be logged
t_io_error	LogAll_Message_Verbose(s_logptr_array loggers, char const* format_str, ...)
{
	t_io_error	result;
	va_list		args;

	for (t_u32 i = 0; i < loggers.length; ++i)
	{
		va_start(args, format_str);
		result = Log_VA(loggers.logptrs[i],
			TRUE, FALSE, 0,
			"", NULL,
			format_str, args);
		va_end(args);
	}
	return (result);
}
