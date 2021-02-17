/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/logger.h                          |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_LOGGER_H
#define __LIBCCC_LOGGER_H
/*! @file libccc/logger.h
**	This header defines a simple yet useful set of functions to do program logging
**	@addtogroup libccc/logger
**	@{
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

typedef struct	s_logfile_
{
	t_fd		fd;		//!< The file descriptor for this logger output logfile
	char*		path;	//!< The file path (relative or absolute) for this logger output logfile
	t_bool		append;	//!< If TRUE, logger will append text to the file if it already exists, rather than overwrite/clear it
}				s_logfile;
#define NULL_LOGFILE	((s_logfile){ .fd = 0, .path = NULL, .append = FALSE })


//! The maximum amount of files a logger can log to simultaneously
#define LOGFILES_MAX	16
//! This struct stores all the settings and internal state needed for a basic logging system
typedef struct	s_logger_
{
	t_bool		show_timestamp;		//!< If TRUE, the logger prints a timestamp at the beginning of each log line
	t_bool		mode_verbose;		//!< If TRUE, additional logging messages will be displayed
	t_bool		mode_obfuscated;	//!< If TRUE, indicates that the logging messages should hide sensitive info, like passwords for instance
	t_bool		dest_stdout;		//!< If TRUE, the logger outputs to the terminal standard output stream
	t_bool		dest_stderr;		//!< If TRUE, the logger outputs to the terminal standard error stream
	s_logfile	dest_files[LOGFILES_MAX];	//!< Each of these, if TRUE, will make to logger output to the specified dest
}				s_logger;
#define	NULL_LOGGER ((s_logger){ .show_timestamp = FALSE, .mode_verbose = FALSE, .mode_obfuscated = FALSE, .dest_stdout = FALSE, .dest_stderr = FALSE, .dest_files = {0} })



/*!
**	The format with which to display timestamps at the beginning of log lines.
*/
#define LOG_TIMESTAMP_FORMAT	FORMAT_DATE_UNIX" "FORMAT_TIME_UNIX" | "

/*!
** The string to display at the beginning of each new line when outputting text that is multiline
** As such, the amount of spaces here is equivalent to the size of a console log timestamp
*/
#define LOG_TIMESTAMP_INDENT	"                    | "



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
	t_bool		is_error,
	t_bool 		use_errno,
	char const*	prefix,
	char const*	prefix_color,
	char const*	format_str,
	va_list		args);
#define c_log_va	Log_VA



//! Used to log a fundamental error where even the logger itself doesn't work: calls the STD C perror() function
t_io_error				Log_Fatal(s_logger const* logger, char const* str);
#define c_log_fatal		Log_Fatal
#define Log_FatalError	Log_Fatal


//! Logging (perror-style) to both stderr and logfile (if applicable)
_FORMAT(printf, 2, 3)
t_io_error				Log_Error_IO(s_logger const* logger, char const* format_str, ...);
#define c_log_error_io	Log_Error_IO
#define Log_SystemError	Log_Error_IO

//! Logging perror-style to both stderr and logfile (if applicable)
_FORMAT(printf, 2, 3)
t_io_error				Log_Error(s_logger const* logger, char const* format_str, ...);
#define c_log_error		Log_Error

//! To be called when there is an important warning to show to the user
_FORMAT(printf, 2, 3)
t_io_error				Log_Warning(s_logger const* logger, char const* format_str, ...);
#define c_log_warning	Log_Warning

//! To be called when there is an successful operation (or result) to notify the user of
_FORMAT(printf, 2, 3)
t_io_error				Log_Success(s_logger const* logger, char const* format_str, ...);
#define c_log_success	Log_Success

//! Logging printf-style of message to both stdout and logfile (if applicable)
_FORMAT(printf, 2, 3)
t_io_error				Log_Message(s_logger const* logger, char const* format_str, ...);
#define c_log_message	Log_Message

//! Logging printf-style of verbose message to both stdout and logfile (if applicable)
_FORMAT(printf, 2, 3)
t_io_error				Log_Message_Verbose(s_logger const* logger, char const* format_str, ...);
#define c_log_verbose	Log_Message_Verbose
#define Log_Verbose		Log_Message_Verbose



/*! @} */
HEADER_END
#endif
