/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/sys/logger.h                      |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_SYS_LOGGER_H
#define __LIBCCC_SYS_LOGGER_H
/*!@group{libccc_sys_logger}
** @{
**	This header defines a simple yet useful set of functions to do program logging
**
**	@file
*/

/*
** ************************************************************************** *|
**                                 Includes                                   *|
** ************************************************************************** *|
*/

#include <stdarg.h>

#include "libccc_config.h"
#include "libccc_define.h"

#include "libccc/sys/io.h"
#include "libccc/sys/time.h"

HEADER_CPP

/* ************************************************************************** */
/*                                 Definitions                                */
/* ************************************************************************** */

//!	This enum specifies a specific text formatting wrapper
typedef enum	e_logformat_
{
	LOGFORMAT_ANSI = 0, //! Prints in a format that is friendly for terminals (ANSI colors)
	LOGFORMAT_TEXT = 1, //! Prints in a format that is friendly for raw text (same as above, but without ANSI color codes)
	LOGFORMAT_JSON = 2, //! Prints in a format that can be easily parsed by a JSON parser
	LOGFORMAT_XML  = 3, //! Prints in a format that can be easily parsed by an XML parser
}				e_logformat;
#define LOGFORMAT_STRING_ANSI		"ANSI"
#define LOGFORMAT_STRING_TEXT		"TEXT"
#define LOGFORMAT_STRING_JSON		"JSON"
#define LOGFORMAT_STRING_XML		"XML"

//! This struct stores all the settings and internal state needed for a basic logging system
typedef struct	s_logger_
{
//	t_bool		in_use;			//!< If TRUE, logger should be considered locked (in use by a given process)
	t_bool		silence_logs;	//!< If TRUE, successful and warning logging with this logger will be ignored
	t_bool		silence_errors;	//!< If TRUE, error logging with this logger will be ignored
	t_bool		timestamp;		//!< If TRUE, the logger prints a timestamp at the beginning of each log line
	t_bool		verbose;		//!< If TRUE, additional logging messages will be displayed
	t_bool		obfuscated;		//!< If TRUE, indicates that the logging messages should hide sensitive info, like passwords for instance
	t_bool		append;			//!< If TRUE, logger will append text to the file if it already exists, rather than overwrite/clear it
	e_logformat	format;			//!< Specifies the overall loggingformat
	t_fd		fd;				//!< The file descriptor to which this logger outputs
	char*		path;			//!< The file path (relative or absolute) for this logger output logfile
}				s_logger;
#define	NULL_LOGGER 			((s_logger const){ 0 })

#define DEFAULT_LOGGER_STDOUT	((s_logger const){ /*.in_use = FALSE,*/ .silence_logs = FALSE, .silence_errors = TRUE,  .timestamp = TRUE,  .verbose = FALSE,  .obfuscated = FALSE, .append = FALSE, .format = LOGFORMAT_ANSI, .fd = STDOUT, .path = NULL })
#define DEFAULT_LOGGER_STDERR	((s_logger const){ /*.in_use = FALSE,*/ .silence_logs = TRUE,  .silence_errors = FALSE, .timestamp = TRUE,  .verbose = FALSE,  .obfuscated = FALSE, .append = FALSE, .format = LOGFORMAT_ANSI, .fd = STDERR, .path = NULL })

//! A null-terminated pointer array of instantiated, active, read-only logger structs. Internals should be set through the internals of a void**. 
typedef s_logger const* const*	t_logptrarr;


/*!
**	The format with which to display timestamps at the beginning of log lines.
*/
#define LOG_TIMESTAMP_FORMAT	FORMAT_DATE_UNIX" "FORMAT_TIME_UNIX" | "

/*!
** The string to display at the beginning of each new line when outputting text that is multiline
** As such, the amount of spaces here is equivalent to the size of a console log timestamp
*/
#define LOG_TIMESTAMP_INDENT	"                    | "
#define LOG_JSON_INDENT			"        "



/* ************************************************************************** */
/*                            Logger Body Macros                              */
/* ************************************************************************** */

#define LOGONE_FUNCTION_CONTENT(VERBOSE_ONLY, IS_ERROR, USE_ERRNO, PREFIX, PREFIX_COLOR) \
	t_io_error	result = OK;					\
	va_list		args;							\
												\
	va_start(args, format_str);					\
	result = Log_VA(logger,						\
		VERBOSE_ONLY, IS_ERROR, USE_ERRNO,		\
		PREFIX, PREFIX_COLOR,					\
		format_str, args);						\
	va_end(args);								\
	return (result);							\

#define LOGALL_FUNCTION_CONTENT(VERBOSE_ONLY, IS_ERROR, USE_ERRNO, PREFIX, PREFIX_COLOR) \
	t_io_error	result = OK;					\
	va_list		args;							\
												\
	for (t_u32 i = 0; loggers[i]; ++i)			\
	{											\
		va_start(args, format_str);				\
		result = Log_VA(loggers[i],				\
		VERBOSE_ONLY, IS_ERROR, USE_ERRNO,		\
		PREFIX, PREFIX_COLOR,					\
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

//! Create a new logger. If logfile_path is required, but NULL, a default macro is used
void						Logger_Init(s_logger *a_logger);
#define c_log_init			Logger_Init
#define InitializeLogger	Logger_Init

//! Cleanly release logger (close file descriptors, etc)
void						Logger_Exit(s_logger *a_logger);
#define c_log_exit			Logger_Exit
#define FinalizeLogger		Logger_Exit

//! Free all memory in logger, but do not release sockets; useful when a duplicated memory instance exists
void						Logger_DeleteMemory(s_logger *a_logger);
#define c_log_delmemory		Logger_DeleteMemory
#define DeleteMemory_Logger	Logger_DeleteMemory

//! Util function to help debug the logger
char*						Logger_GetSettings(s_logger const* logger);
#define c_log_getsettings	Logger_GetSettings

//! Util function to help debug the logger
t_io_error					Logger_LogSettings(s_logger const* logger);
#define c_log_logsettings	Logger_LogSettings



//! Returns a UNIX-format string representation of the given 'utc' date/time number
char*		Logger_GetTimestamp(t_time utc);



/* ************************************************************************** */
/*                             Logging Definitions                            */
/* ************************************************************************** */

//! Send a printf-like string to logfile
_FORMAT(printf, 5, 6)
t_io_error 	Log(s_logger const* logger,
	t_bool is_verbose_only,
	t_bool is_error,
	t_bool use_errno_perror,
	char const* format_str, ...);
#define c_log_		Log

t_io_error	Log_VA(s_logger const* logger,
	t_bool 		verbose_only,
	t_bool 		use_errno,
	int			is_error,
	char const*	prefix,
	char const*	prefix_color,
	char const*	format_str,
	va_list		args);
#define c_log_va	Log_VA



//! Used to log a fundamental error where even the logger itself doesn't work: calls the STD C perror() function
t_io_error				Log_Fatal	(s_logger const* logger, char const* str);
#define c_log_fatal		Log_Fatal
#define Log_FatalError	Log_Fatal



//! Logging (perror-style) to both stderr and logfile (if applicable)
_FORMAT(printf, 3, 4)
t_io_error					LogAll_Error_IO			(t_logptrarr const loggers, int error_code, char const* format_str, ...);
#define c_logall_error_io	LogAll_Error_IO
#define LogAll_SystemError	LogAll_Error_IO

//! Logging perror-style to both stderr and logfile (if applicable)
_FORMAT(printf, 3, 4)
t_io_error					LogAll_Error			(t_logptrarr const loggers, int error_code, char const* format_str, ...);
#define c_logall_error		LogAll_Error

//! To be called when there is an important warning to show to the user
_FORMAT(printf, 2, 3)
t_io_error					LogAll_Warning			(t_logptrarr const loggers,                 char const* format_str, ...);
#define c_logall_warning	LogAll_Warning

//! To be called when there is an successful operation (or result) of which to notify the user
_FORMAT(printf, 2, 3)
t_io_error					LogAll_Success			(t_logptrarr const loggers,                 char const* format_str, ...);
#define c_logall_success	LogAll_Success

//! Logging printf-style of message to both stdout and logfile (if applicable)
_FORMAT(printf, 2, 3)
t_io_error					LogAll_Message			(t_logptrarr const loggers,                 char const* format_str, ...);
#define c_logall_message	LogAll_Message

//! Logging printf-style of verbose message to both stdout and logfile (if applicable)
_FORMAT(printf, 2, 3)
t_io_error					LogAll_Message_Verbose	(t_logptrarr const loggers,                 char const* format_str, ...);
#define c_logall_verbose	LogAll_Message_Verbose
#define LogAll_Verbose		LogAll_Message_Verbose



//! Logging (perror-style) to both stderr and logfile (if applicable)
_FORMAT(printf, 3, 4)
t_io_error					Log_Error_IO			(s_logger const* logger, int error_code, char const* format_str, ...);
#define c_log_error_io	Log_Error_IO
#define Log_SystemError	Log_Error_IO

//! Logging perror-style to both stderr and logfile (if applicable)
_FORMAT(printf, 3, 4)
t_io_error					Log_Error				(s_logger const* logger, int error_code, char const* format_str, ...);
#define c_log_error		Log_Error

//! To be called when there is an important warning to show to the user
_FORMAT(printf, 2, 3)
t_io_error					Log_Warning				(s_logger const* logger,                 char const* format_str, ...);
#define c_log_warning	Log_Warning

//! To be called when there is an successful operation (or result) of which to notify the user
_FORMAT(printf, 2, 3)
t_io_error					Log_Success				(s_logger const* logger,                 char const* format_str, ...);
#define c_log_success	Log_Success

//! Logging printf-style of message to both stdout and logfile (if applicable)
_FORMAT(printf, 2, 3)
t_io_error					Log_Message				(s_logger const* logger,                 char const* format_str, ...);
#define c_log_message	Log_Message

//! Logging printf-style of verbose message to both stdout and logfile (if applicable)
_FORMAT(printf, 2, 3)
t_io_error					Log_Message_Verbose		(s_logger const* logger,                 char const* format_str, ...);
#define c_log_verbose	Log_Message_Verbose
#define Log_Verbose		Log_Message_Verbose



/*! @} */
HEADER_END
#endif
