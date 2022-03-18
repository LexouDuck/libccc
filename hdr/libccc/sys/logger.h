/*============================================================================*\
||                                            ______________________________  ||
||  libccc/sys/logger.h                      |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_SYS_LOGGER_H
#define __LIBCCC_SYS_LOGGER_H
/*!@group{libccc_sys_logger,23,libccc/sys/logger.h}
**
**	This header defines a simple yet useful set of functions to do program logging
*/

/*
** ************************************************************************** *|
**                                 Includes                                   *|
** ************************************************************************** *|
*/

#ifndef __NOSTD__
	#include <stdarg.h>
#else
	typedef __builtin_va_list va_list;
#endif

#include "libccc_config.h"
#include "libccc_define.h"

#include "libccc/sys/io.h"
#include "libccc/sys/time.h"
#include "libccc/sys/error.h"

HEADER_CPP

#ifndef __LIBCCC_SYS_LOGGER_T
#define __LIBCCC_SYS_LOGGER_T

/* ************************************************************************** */
/*                                 Definitions                                */
/* ************************************************************************** */

//!	This enum describes the different text formattings available for the libccc logger
typedef enum logformat
{
	LOGFORMAT_ANSI = 0, //!< Prints in a format that is friendly for terminals (ANSI colors)
	LOGFORMAT_TEXT = 1, //!< Prints in a format that is friendly for raw text (same as above, but without ANSI color codes)
	LOGFORMAT_JSON = 2, //!< Prints in a format that can be easily parsed by a JSON parser
	LOGFORMAT_XML  = 3, //!< Prints in a format that can be easily parsed by an XML parser
}	e_logformat;
//!@doc String literal macros for each item of the #e_logformat enumeration
//!@{
#define LOGFORMAT_STRING_ANSI		"ANSI"
#define LOGFORMAT_STRING_TEXT		"TEXT"
#define LOGFORMAT_STRING_JSON		"JSON"
#define LOGFORMAT_STRING_XML		"XML"
//!@}



//! This struct stores all the settings and internal state needed for a basic logging system
typedef struct logger
{
//	t_bool		in_use;			//!< If `TRUE`, logger should be considered locked (ie: already in use by some process)
	t_bool		silence_logs;	//!< If `TRUE`, then this logger will suppress "message", "success" and "warning" logs
	t_bool		silence_errors;	//!< If `TRUE`, then this logger will suppress "failure" and "error" logs
	t_bool		verbose;		//!< If `TRUE`, then this logger will display "verbose" message logs (see Log_Verbose())
	t_bool		timestamp;		//!< If `TRUE`, the logger prints a timestamp at the beginning of each log line
	t_bool		obfuscated;		//!< If `TRUE`, indicates that the logging messages should hide sensitive info, like passwords for instance
	t_bool		append;			//!< If `TRUE`, logger will append text to the file if it already exists, rather than overwrite/clear it
	e_logformat	format;			//!< Specifies the kind logging format for the text output
	t_fd		fd;				//!< The file descriptor to which this logger outputs
	t_char*		path;			//!< The file path (relative or absolute) for this logger output logfile
}	s_logger;

//! A null-terminated pointer array of instantiated, active, read-only logger structs.
typedef s_logger const* const*	t_logptrarr;



//! The null/default value for a #s_logger struct (all fields set to zero)
#define	NULL_LOGGER 			((s_logger const){ 0 })

//! The default settings for a #s_logger struct meant to output text to #STDOUT
#define DEFAULT_LOGGER_STDOUT	((s_logger const)\
{\
	/*.in_use = FALSE,*/\
	.silence_logs   = FALSE,\
	.silence_errors = TRUE,\
	.timestamp      = FALSE,\
	.verbose        = FALSE,\
	.obfuscated     = FALSE,\
	.append         = FALSE,\
	.format = LOGFORMAT_ANSI,\
	.fd = STDOUT,\
	.path = NULL,\
})
//! The default settings for a #s_logger struct meant to output text to #STDERR
#define DEFAULT_LOGGER_STDERR	((s_logger const)\
{\
	/*.in_use = FALSE,*/\
	.silence_logs   = TRUE,\
	.silence_errors = FALSE,\
	.timestamp      = FALSE,\
	.verbose        = FALSE,\
	.obfuscated     = FALSE,\
	.append         = FALSE,\
	.format = LOGFORMAT_ANSI,\
	.fd = STDERR,\
	.path = NULL,\
})


/*!
**	The format string to use to display timestamps at the beginning of log lines.
*/
#define LOG_TIMESTAMP_FORMAT	SF_DATE_UNIX" "SF_TIME_UNIX

/*!
** The string to display at the beginning of each new line when outputting text that is multiline
** As such, the amount of spaces here is equivalent to the size of a console log timestamp
*/
#define LOG_TIMESTAMP_INDENT	"                   "
//! Separator string used between timestamp and message (if applicable)
#define LOG_TIMESTAMP_SEPARATOR	" | "

//! Indentation string used for LOGFORMAT_JSON
#define LOG_JSON_INDENT			"        "



#endif
#ifndef __LIBCCC_SYS_LOGGER_F
#define __LIBCCC_SYS_LOGGER_F

/* ************************************************************************** */
/*                            Logger Body Macros                              */
/* ************************************************************************** */

#define LOGONE_FUNCTION_CONTENT(SKIP, ERRORINT, ERRORMSG, PREFIX, PREFIX_COLOR) \
	e_cccerror	result = OK;					\
	va_list		args;							\
	if (SKIP)	return (result);				\
	va_start(args, format_str);					\
	result = Log_VA(logger,						\
		ERRORINT,								\
		PREFIX,									\
		PREFIX_COLOR,							\
		ERRORMSG,								\
		format_str, args);						\
	va_end(args);								\
	return (result);							\

#define LOGALL_FUNCTION_CONTENT(SKIP, ERRORINT, ERRORMSG, PREFIX, PREFIX_COLOR) \
	e_cccerror	result = OK;					\
	va_list		args;							\
	for (t_u32 i = 0; loggers[i]; ++i)			\
	{											\
		s_logger const* logger = loggers[i];	\
		if (SKIP)	continue;					\
		va_start(args, format_str);				\
		result = Log_VA(logger,					\
			ERRORINT,							\
			PREFIX,								\
			PREFIX_COLOR,						\
			ERRORMSG,							\
			format_str, args);					\
		va_end(args);							\
	}											\
	return (result);							\



/* ************************************************************************** */
/*                            Function Definitions                            */
/* ************************************************************************** */

/*
**	utils/logger.c
*/

//!@doc Create a new logger. If logfile_path is required, but NULL, a default macro is used
//!@{
void						Logger_Init(s_logger *a_logger);
#define c_loginit			Logger_Init
#define InitializeLogger	Logger_Init //!< DEPRECATED
//!@}

//!@doc Cleanly release logger (close file descriptors, free internal memory)
//!@{
void						Logger_Exit(s_logger *a_logger);
#define c_logexit			Logger_Exit
#define FinalizeLogger		Logger_Exit //!< DEPRECATED
//!@}

//!@doc Free all memory in logger, but do not release sockets; useful when a duplicated memory instance exists
//!@{
void						Logger_DeleteMemory(s_logger *a_logger);
#define c_logdelmem			Logger_DeleteMemory
#define DeleteMemory_Logger	Logger_DeleteMemory //!< DEPRECATED
//!@}

//!@doc Util function to help debug the logger
//!@{
t_char*						Logger_GetSettings(s_logger const* logger);
#define c_log_getsettings	Logger_GetSettings
//!@}

//!@doc Util function to help debug the logger
//!@{
e_cccerror					Logger_LogSettings(s_logger const* logger);
#define c_log_logsettings	Logger_LogSettings
//!@}



//!@doc Returns a UNIX-format string representation of the given 'utc' date/time number
//!@{
t_char*						Logger_GetTimestamp(t_time utc);
#define c_logtime			Logger_GetTimestamp
//!@}



/* ************************************************************************** */
/*                             Logging Definitions                            */
/* ************************************************************************** */

//!@doc Output a printf-like string as a logging message
/*!
**	@param	logger	The `s_logger` struct which holds the state/settings for logging
**	@param	error_code		(optional) The error code number (is only used for certain `e_logformat` settings)
**	@param	prefix			(optional) The message prefix (is output immediately before the `format` string)
**	@param	prefix_color	(optional) The ANSI color escape sequence (only used if `logger->logformat == LOGFORMAT_ANSI`)
**	@param	suffix			(optional) The secondary log message (is output a second line, after the `format` string)
**	@param	format	The format string for the body of the log message (similar to `printf()`)
**	@param	args	The variadic arguments list for the log message `format` string (similar to `printf()`)
*/
//!@{

_FORMAT(printf, 3, 4)
e_cccerror 	Log(s_logger const* logger,
	t_char const*	suffix,
	t_char const*	format, ...);
#define c_io_log		Log

_FORMAT(printf, 6, 7)
e_cccerror 	Log_Custom(s_logger const* logger,
	int				error_code,
	t_char const*	prefix,
	t_char const*	prefix_color,
	t_char const*	suffix,
	t_char const*	format, ...);
#define c_io_log_custom	Log_Custom

e_cccerror	Log_VA(s_logger const* logger,
	int				error_code,
	t_char const*	prefix,
	t_char const*	prefix_color,
	t_char const*	suffix,
	t_char const*	format, va_list args);
#define c_io_log_va		Log_VA

//!@}



//!@doc Used to log a fundamental error where even the logger itself doesn't work: calls the STD C perror() function
//!@{
e_cccerror				Log_Fatal(s_logger const* logger, t_char const* str);
#define c_log_fatal		Log_Fatal
#define Log_FatalError	Log_Fatal
//!@}



//! Text prefix used when logging a "failure" message
#ifndef LOGPREFIX_ERROR
#define LOGPREFIX_ERROR	"error"
#endif

//!@doc Log an error message (with a secondary `message` string) - use this to notify the user of a failure/problem
//!@{
_FORMAT(printf, 3, 4)
e_cccerror					Log_Error(s_logger const* logger, t_char const* message, t_char const* format_str, ...);
#define c_log_error			Log_Error
//!@doc Like Log_Error(), but this takes an array of loggers, and logs to each of their destinations
_FORMAT(printf, 3, 4)
e_cccerror					LogAll_Error(t_logptrarr const loggers, t_char const* message, t_char const* format_str, ...);
#define c_logall_error		LogAll_Error
//!@}

//!@doc Log an error message (with `perror()`/`strerror()` string) - use this to notify the user of a failure/problem
//!@{
_FORMAT(printf, 3, 4)
e_cccerror					Log_Error_STD(s_logger const* logger, t_errno error, t_char const* format_str, ...);
#define c_log_error_std		Log_Error_STD
#define Log_SystemError		Log_Error_STD
//!@doc Like Log_Error_STD(), but this takes an array of loggers, and logs to each of their destinations
_FORMAT(printf, 3, 4)
e_cccerror					LogAll_Error_STD(t_logptrarr const loggers, t_errno error, t_char const* format_str, ...);
#define c_logall_error_std	LogAll_Error_STD
#define LogAll_SystemError	LogAll_Error_STD
//!@}

//!@doc Log an error message (with libccc error message string) - use this to notify the user of a failure/problem
//!@{
_FORMAT(printf, 3, 4)
e_cccerror					Log_Error_CCC(s_logger const* logger, e_cccerror error, t_char const* format_str, ...);
#define c_log_error_ccc		Log_Error_CCC
#define Log_CCCError		Log_Error_CCC
//!@doc Like Log_Error_CCC(), but this takes an array of loggers, and logs to each of their destinations
_FORMAT(printf, 3, 4)
e_cccerror					LogAll_Error_CCC(t_logptrarr const loggers, e_cccerror error, t_char const* format_str, ...);
#define c_logall_error_ccc	LogAll_Error_CCC
#define LogAll_CCCError		LogAll_Error_CCC
//!@}



//! Text prefix used when logging a "failure" message
#ifndef LOGPREFIX_FAILURE
#define LOGPREFIX_FAILURE	"failure"
#endif

//!@doc Log a "failure" message - use this to notify the user of a failure/problem
//!@{
_FORMAT(printf, 2, 3)
e_cccerror					Log_Failure(s_logger const* logger, t_char const* format_str, ...);
#define c_log_fail			Log_Failure
//!@}
//!@doc Like Log_Failure(), but this takes an array of loggers, and logs to each of their destinations
//!@{
_FORMAT(printf, 2, 3)
e_cccerror					LogAll_Failure(t_logptrarr const loggers, t_char const* format_str, ...);
#define c_logall_fail		LogAll_Failure
//!@}

//! Text prefix used when logging a "warning" message
#ifndef LOGPREFIX_WARNING
#define LOGPREFIX_WARNING	"warning"
#endif

//!@doc Log a "warning" message - use this to notify the user of a minor/potential problem
//!@{
_FORMAT(printf, 2, 3)
e_cccerror					Log_Warning(s_logger const* logger, t_char const* format_str, ...);
#define c_log_warning		Log_Warning
//!@}
//!@doc Like Log_Warning(), but this takes an array of loggers, and logs to each of their destinations
//!@{
_FORMAT(printf, 2, 3)
e_cccerror					LogAll_Warning(t_logptrarr const loggers, t_char const* format_str, ...);
#define c_logall_warning	LogAll_Warning
//!@}

//! Text prefix used when logging a "success" message
#ifndef LOGPREFIX_SUCCESS
#define LOGPREFIX_SUCCESS	"success"
#endif

//!@doc Log a "success" message - use this to notify the user of a successful operation (or result)
//!@{
_FORMAT(printf, 2, 3)
e_cccerror					Log_Success(s_logger const* logger, t_char const* format_str, ...);
#define c_log_success		Log_Success
//!@}
//!@doc Like Log_Success(), but this takes an array of loggers, and logs to each of their destinations
//!@{
_FORMAT(printf, 2, 3)
e_cccerror					LogAll_Success(t_logptrarr const loggers, t_char const* format_str, ...);
#define c_logall_success	LogAll_Success
//!@}

//! Text prefix used when logging a "message" message
#ifndef LOGPREFIX_MESSAGE
#define LOGPREFIX_MESSAGE	"message"
#endif

//!@doc Log a normal message
//!@{
_FORMAT(printf, 2, 3)
e_cccerror					Log_Message(s_logger const* logger, t_char const* format_str, ...);
#define c_log_message		Log_Message
//!@}
//!@doc Like Log_Message(), but this takes an array of loggers, and logs to each of their destinations
//!@{
_FORMAT(printf, 2, 3)
e_cccerror					LogAll_Message(t_logptrarr const loggers, t_char const* format_str, ...);
#define c_logall_message	LogAll_Message
//!@}

//! Text prefix used when logging a "verbose" message
#ifndef LOGPREFIX_VERBOSE
#define LOGPREFIX_VERBOSE	"verbose"
#endif

//!@doc Logging printf-style of verbose message to both stdout and logfile (if applicable)
//!@{
_FORMAT(printf, 2, 3)
e_cccerror					Log_Verbose(s_logger const* logger, t_char const* format_str, ...);
#define c_log_verbose		Log_Verbose
#define Log_Verbose			Log_Verbose
//!@doc Like Log_Verbose(), but this takes an array of loggers, and logs to each of their destinations
//!@}
_FORMAT(printf, 2, 3)
//!@{
e_cccerror					LogAll_Verbose(t_logptrarr const loggers, t_char const* format_str, ...);
#define c_logall_verbose	LogAll_Verbose
#define LogAll_Verbose		LogAll_Verbose
//!@}



#endif

/*! @endgroup */
HEADER_END
#endif
