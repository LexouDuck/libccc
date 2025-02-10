
#ifndef LIBCCCTEST_PRINT_H_
#define LIBCCCTEST_PRINT_H_

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include <stdbool.h>
#ifndef __cplusplus
#ifndef bool
#define bool	_Bool
#endif
#endif

#include "test_catch.h"
#include "test_timer.h"



/*============================================================================*\
||                                   Defines                                  ||
\*============================================================================*/

/*
**	Output color string codes for tty terminal/shell.
*/
#ifndef __COLORS__
#define __COLORS__
#define ANSI_COLOR_FG_RED		"\x1b[31m"
#define ANSI_COLOR_FG_GREEN		"\x1b[32m"
#define ANSI_COLOR_FG_YELLOW	"\x1b[33m"
#define ANSI_COLOR_FG_BLUE		"\x1b[34m"
#define ANSI_COLOR_FG_MAGENTA	"\x1b[35m"
#define ANSI_COLOR_FG_CYAN		"\x1b[36m"
#define ANSI_RESET		"\x1b[0m"
#endif



/*============================================================================*\
||                              Utility Functions                             ||
\*============================================================================*/

void	print_error(char const* format_error, ...);
void	print_percent(double percent);
void	print_totals(int amount, int failed, int warnings, char const* category);
void	print_usage(char const* program_name);
void	print_suite_title(char const* suite_name);
void	print_title(void);
void	print_endian_warning(void);
void	print_nonstd(void);



#endif
