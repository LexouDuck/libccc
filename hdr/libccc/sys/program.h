/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/sys/program.h                     |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_SYS_PROGRAM_H
#define __LIBCCC_SYS_PROGRAM_H
/*!@group{libccc_sys_program}
** @{
**	This header defines all the functions for OS-level input/output, read/write.
**
**	@isostd{C,https://en.cppreference.com/w/c/program}
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#ifndef __NOSTD__
	#include <stdlib.h>
#else
	#define EXIT_SUCCESS	(OK)
	#define EXIT_FAILURE	(ERROR)
#endif

#include "libccc.h"

HEADER_CPP

#ifndef __LIBCCC_SYS_PROGRAM_T
#define __LIBCCC_SYS_PROGRAM_T

/*
** ************************************************************************** *|
**                                  Definitions                               *|
** ************************************************************************** *|
*/



#endif
#ifndef __LIBCCC_SYS_PROGRAM_F
#define __LIBCCC_SYS_PROGRAM_F

/*
** ************************************************************************** *|
**                           Common Program Utilities                         *|
** ************************************************************************** *|
*/

//! TODO wrapper function for abort()
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/program/abort}
*/
_NORETURN()
void				Program_Abort(void);
#define c_abort		Program_Abort //!< @alias{Program_Abort}



//! TODO wrapper function for exit()
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/program/exit}
*/
_NORETURN()
void				Program_Exit(int exit_code);
#define c_exit		Program_Exit //!< @alias{Program_Exit}



//! TODO wrapper function for atexit()
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/program/atexit}
*/
e_cccerror			Program_OnExit(void (*f)(void));
#define c_atexit	Program_OnExit //!< @alias{Program_OnExit}
#define c_on_exit	Program_OnExit //!< @alias{Program_OnExit}



//! TODO wrapper function for quick_exit()		@isostd{C11,https://en.cppreference.com/w/c/program/quick_exit}
//! TODO wrapper function for at_quick_exit()	@isostd{C11,https://en.cppreference.com/w/c/program/at_quick_exit}



//! TODO wrapper function for system()
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/program/system}
*/
int					Program_Run(t_char const* command);
#define c_system	Program_Run



//! TODO wrapper function for getenv()
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/program/getenv} TODO make it safe with a strdup()
*/
t_char*				Program_GetEnv(t_char const* name);
#define c_getenv	Program_GetEnv

//! TODO wrapper function for setenv()
/*!
**	@isostd{POSIX,https://linux.die.net/man/3/setenv}
*/
int					Program_SetEnv(t_char const* name, t_char const* value, t_bool overwrite);
#define c_setenv	Program_SetEnv



//! TODO wrapper function for getcwd()
/*!
**	@isostd{POSIX,https://linux.die.net/man/3/getcwd}
*/
t_char*				Program_GetCWD(void);
#define c_getcwd	Program_GetCWD



#endif

/*! @} */
HEADER_END
#endif