
#include "libccc.h"

#ifndef __NOSTD__
	#if (!defined(__GNUC__) && defined(__MSVC__))
	#include "libccc/compatibility/msvc/unistd.h"
	#else
	#include <unistd.h>
	#endif
#else
	typedef unsigned long	size_t;
	char*	strerror(int error);
	int		write(int fd, void const* buffer, size_t n);
#endif
#ifndef __NOSTD__
	#include <errno.h>
#else
	#ifndef	errno
	extern	int*	errno(void);
	#define errno	(*errno())
	#endif
#endif
#ifndef __NOSTD__
	#include <stdarg.h>
#else
	typedef __builtin_va_list va_list;
	#define va_start(v,l)	__builtin_va_start(v,l)
	#define va_end(v)		__builtin_va_end(v)
	#define va_arg(v,l)		__builtin_va_arg(v,l)
	#define va_copy(d,s)	__builtin_va_copy(d,s)
#endif

#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"
#include "libccc/sys/time.h"
#include "libccc/sys/io.h"
#include "libccc/sys/logger.h"

#include LIBCONFIG_ERROR_INCLUDE



e_cccerror	Log_Fatal(s_logger const* logger, t_char const* str)
{
//	if CCCERROR((logger == NULL), ERROR_NULLPOINTER, NULL)
//		return (ERROR_NULLPOINTER);

// only using write()
	t_char const* prefix;
	int 	result = 0;
	t_bool	is_sh;
	t_fd	fd = (logger ? logger->fd : STDOUT);
	is_sh = IO_IsTerminal(fd);
	prefix = (is_sh ? "libccc: "ANSI_COLOR_FG_RED"fatal"ANSI_RESET": " : "libccc: fatal: ");
	result = write(fd, prefix, String_Length(prefix));
	if (str)
	{
		result = write(fd, str, String_Length(str));
	}
	result = write(fd, "\n", (sizeof("\n") - sizeof("")));

// printf/dprintf method (less compatible)
/*
	if (logger == NULL)
	{
		result = printf(
			ANSI_COLOR_FG_RED"Fatal Error"ANSI_RESET": %s\n\t-> %s\n",
			(str ? str : ""), message);
		return (ERROR_NULLPOINTER);
	}
	if (logger->path && IO_IsTerminal(logger->fd))
	{
		result = dprintf(logger->fd,
			ANSI_COLOR_FG_RED"Fatal Error"ANSI_RESET": %s\n\t-> %s\n",
			(str ? str : ""), message);
	}
	else
	{
		result = dprintf(logger->fd,
			"Fatal Error: %s\n\t-> %s\n",
			(str ? str : ""), message);
	}
*/
//	if CCCERROR((result == 0), ERROR_SYSTEM, NULL)
//		return (ERROR_PRINT);
	if (result <= 0)
		return (ERROR_PRINT);
	return (ERROR_NONE);
}



t_char*	Logger_GetTimestamp(t_time utc)
{
	static const t_size max = 24;
	t_char*	result;
	s_date	date;

	date = Time_ToDate_UTC(utc);
	result = String_New(max);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	Date_ToString_N(result, max, &date, LOG_TIMESTAMP_FORMAT);
	return (result);
}



//! Functions to help debug the logger
t_char*	Logger_GetSettings(s_logger const* logger)
{
	t_char*		result = NULL;
	t_char const*	logformat = NULL;

	if CCCERROR((logger == NULL), ERROR_NULLPOINTER, "logger struct given is NULL")
		return (NULL);
	switch (logger->format)
	{
		case LOGFORMAT_ANSI: logformat = LOGFORMAT_STRING_ANSI; break;
		case LOGFORMAT_TEXT: logformat = LOGFORMAT_STRING_TEXT; break;
		case LOGFORMAT_JSON: logformat = LOGFORMAT_STRING_JSON; break;
		case LOGFORMAT_XML:  logformat = LOGFORMAT_STRING_XML ; break;
		default: break;
	}
	result = String_Format(
		"\nLogger settings:"
		"\n\t- Silence normal logs and warnings: %s"
		"\n\t- Silence error logs: %s"
		"\n\t- Show TimeStamp: %s"
		"\n\t- Verbose mode: %s"
		"\n\t- Obfuscated mode: %s"
		"\n\t- Append mode: %s"
		"\n\t- Format mode: %s"
		"\n\t- Logging to fd: %d"
		"\n\t- Logging to file: \"%s\"",
		(logger->silence_logs   ? "ON" : "OFF"),
		(logger->silence_errors ? "ON" : "OFF"),
		(logger->timestamp      ? "ON" : "OFF"),
		(logger->verbose        ? "ON" : "OFF"),
		(logger->obfuscated     ? "ON" : "OFF"),
		(logger->append         ? "ON" : "OFF"),
		logformat,
		logger->fd,
		logger->path
	);
	return (result);
}



e_cccerror	Logger_LogSettings(s_logger const* logger)
{
	e_cccerror result;
	t_char*	tmp;

	if CCCERROR((logger == NULL), ERROR_NULLPOINTER, "logger given is NULL")
		return (ERROR_NULLPOINTER);
	tmp = Logger_GetSettings(logger);
	result = Log_Message(logger, "%s", tmp);
	String_Delete(&tmp);
	return (result);
}
