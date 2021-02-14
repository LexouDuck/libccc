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

#include "libccc_config.h"
#include "libccc_define.h"

#include "libccc/sys/io.h"
#include "libccc/sys/time.h"

HEADER_CPP

/* ************************************************************************** */
/*                                 Definitions                                */
/* ************************************************************************** */

//! The arbitrary data buffer size used to write the log output to file
#define BUFFERSIZE	4096 // 4 Kb

//! The name of the text file to write logger output to
#define LOGFILE_NAME	DEFAULT_LOGFILE_NAME



/*!
**	The format with which to display timestamps at the beginning of log lines.
*/
#define LOG_TIMESTAMP_FORMAT	FORMAT_DATE_UNIX" "FORMAT_TIME_UNIX" | "

/*!
** The string to display at the beginning of each new line when outputting text that is multiline
** As such, the amount of spaces here is equivalent to the size of a console log timestamp
*/
#define LOG_TIMESTAMP_INDENT	"                    | "



typedef struct	s_logfile_
{
	t_fd		fd;		//!< The file descriptor for this logger output logfile
	char const*	path;	//!< The file path (relative or absolute) for this logger output logfile
	t_bool		append;	//!< If TRUE, logger will append text to the file if it already exists, rather than overwrite/clear it
}				s_logfile;

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



/* ************************************************************************** */
/*                            Function Definitions                            */
/* ************************************************************************** */

/*
**	utils/logger.c
*/

//! Create a new logger. If logfile_path is required, but NULL, a default macro is used
void						Log_Init(s_logger* logger);
#define c_log_init			Log_Init
#define InitializeLogger	Log_Init

//! Cleanly release logger (close file descriptors, etc)
void						Log_Exit(s_logger* logger);
#define c_log_exit			Log_Exit
#define FinalizeLogger		Log_Exit



int		vLog(s_logger const* logger,
	t_bool 			verbose_only,
	t_bool			is_error,
	t_bool 			use_errno,
	char const*		prefix,
	char const*		prefix_color,
	char const*		format_str,
	va_list			args);
#define c_vlog	vLog

//! Send a printf-like string to logfile
void 		Log(s_logger const* logger,
	t_bool is_verbose_only,
	t_bool is_error,
	t_bool use_errno_perror,
	char const* format_str, ...);
#define c_log	Log



//! Logging perror-style to both stderr and logfile (if applicable)
void					Log_Error(s_logger const logger, t_bool errno, char const* format_str, ...);
#define c_log_error		Log_Error

//! To be called when there is an important warning to show to the user
void					Log_Warning(s_logger const logger, char const* format_str, ...);
#define c_log_warning	Log_Warning

//! To be called when there is an successful operation (or result) to notify the user of
void					Log_Success(s_logger const logger, char const* format_str, ...);
#define c_log_success	Log_Success

//! Logging printf-style of message to both stdout and logfile (if applicable)
void					Log_Message(s_logger const logger, char const* format_str, ...);
#define c_log_message	Log_Message

//! Logging printf-style of verbose message to both stdout and logfile (if applicable)
void					Log_Verbose(s_logger const logger, char const* format_str, ...);
#define c_log_verbose	Log_Verbose



//! Util function to help debug the logger
char*						Log_GetLoggerSettings(s_logger const* logger);
#define c_log_getsettings	Log_GetLoggerSettings

//! Util function to help debug the logger
void						Log_LoggerSettings(s_logger const* logger);
#define c_log_settings		Log_LoggerSettings



//! Used to log a fundamental error where even the logger itself doesn't work: calls the STD C perror() function
void		Log_FatalError(s_logger const* logger, char const* str);
//! Returns a UNIX-format string representation  of the given 'utc' date/time number
char*		Log_GetUnixDateTime(t_time utc);



/*! @} */
HEADER_END
#endif
