
#include <stdarg.h>

#include "libccc/sys/io.h"
#include "libccc/sys/logger.h"



void 		Log(s_logger const logger,
	t_bool verbose_only,
	t_bool is_error,
	t_bool use_errno,
	char const* format_str, ...)
{
	va_list		args;

	va_start(args, format_str);
	vLog(logger, verbose_only, is_error, use_errno,
		"", NULL,
		format_str, args);
	va_end(args);
}



void		Log_Error(s_logger const logger, t_bool errno, char const* format_str, ...)
{
	va_list		args;

	va_start(args, format_str);
	vLog(logger, FALSE, TRUE, errno,
		"Error: ", C_RED,
		format_str, args);
	va_end(args);
}

// To be called when there is an important warning to show to the user
void		Log_Warning(s_logger const logger, char const* format_str, ...)
{
	va_list		args;

	va_start(args, format_str);
	vLog(logger, FALSE, FALSE, FALSE,
		"Warning: ", C_YELLOW,
		format_str, args);
	va_end(args);
}

// To be called when there is an successful operation (or result) to notify the user of
void		Log_Success(s_logger const logger, char const* format_str, ...)
{
	va_list		args;

	va_start(args, format_str);
	vLog(logger, FALSE, FALSE, FALSE,
		"Success: ", C_GREEN,
		format_str, args);
	va_end(args);
}

// To be called when there is user-useful data to be logged (operation successful with value X returned, etc)
void		Log_Message(s_logger const logger, char const* format_str, ...)
{
	va_list		args;

	va_start(args, format_str);
	vLog(logger, FALSE, FALSE, FALSE,
		"", NULL,
		format_str, args);
	va_end(args);
}

// To be called when there is "verbose" data to be logged
void		Log_Verbose(s_logger const logger, char const* format_str, ...)
{
	va_list		args;

	va_start(args, format_str);
	vLog(logger, TRUE, FALSE, FALSE,
		"", NULL,
		format_str, args);
	va_end(args);
}
