/*============================================================================*\
||                                            ______________________________  ||
||  libccc/sys/ansi.h                        |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_SYS_ANSI_H
#define __LIBCCC_SYS_ANSI_H
/*!@group{libccc_sys_ansi,21,libccc/sys/ansi.h}
**
**	This header defines some useful ANSI text macros.
**
**	@see
**	- https://en.wikipedia.org/wiki/ANSI_escape_code
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc_define.h"

HEADER_CPP

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

#define ANSI_ESC(SEQUENCE, NUMBER)	"\x1B[" #NUMBER "" SEQUENCE "" //!< A helper macro used to construct common ANSI commandline escape codes.

// ANSI cursor functions

#define ANSI_CURSOR_SAVE()                "\x1B 7"                   //!< A special ANSI escape code to save the current position of the cursor (DEC).
#define ANSI_CURSOR_LOAD()                "\x1B 8"                   //!< A special ANSI escape code to restore the cursor to its last saved position (DEC).
#define ANSI_CURSOR_MOVE(LINE, COLUMN)    "\x1B["#LINE";"#COLUMN"H"  //!< A special ANSI escape code to move the cursor to the specified position.
#define ANSI_CURSOR_MOVE_UP(LINES)        ANSI_ESC("A", LINES)       //!< A special ANSI escape code to move the cursor up # lines.
#define ANSI_CURSOR_MOVE_DOWN(LINES)      ANSI_ESC("B", LINES)       //!< A special ANSI escape code to move the cursor down # lines.
#define ANSI_CURSOR_MOVE_RIGHT(LINES)     ANSI_ESC("C", LINES)       //!< A special ANSI escape code to move the cursor right # columns.
#define ANSI_CURSOR_MOVE_LEFT(LINES)      ANSI_ESC("D", LINES)       //!< A special ANSI escape code to move the cursor left # columns.
#define ANSI_CURSOR_NEXTLINE(LINES)       ANSI_ESC("E", LINES)       //!< A special ANSI escape code to put the cursor at the beginning of the next line, # lines down.
#define ANSI_CURSOR_PREVLINE(LINES)       ANSI_ESC("F", LINES)       //!< A special ANSI escape code to put the cursor at the beginning of the previous line, # lines up.

// ANSI erase functions

#define ANSI_ERASE_SCREEN_AFTER           ANSI_ESC("J", 0)     //!< A special ANSI escape code to erase from cursor until end of screen.
#define ANSI_ERASE_SCREEN_BEFORE          ANSI_ESC("J", 1)     //!< A special ANSI escape code to erase from cursor to beginning of screen.
#define ANSI_ERASE_SCREEN                 ANSI_ESC("J", 2)     //!< A special ANSI escape code to erase the entire screen.
#define ANSI_ERASE_SAVED                  ANSI_ESC("J", 3)     //!< A special ANSI escape code to erase all saved lines.
#define ANSI_ERASE_LINE_AFTER             ANSI_ESC("K", 0)     //!< A special ANSI escape code to erase from cursor to end of line.
#define ANSI_ERASE_LINE_BEFORE            ANSI_ESC("K", 1)     //!< A special ANSI escape code to erase start of line to the cursor.
#define ANSI_ERASE_LINE                   ANSI_ESC("K", 2)     //!< A special ANSI escape code to erase the entire line.

// ANSI color & style functions

//! ANSI text output display escape code macros
/*!
**	These are some useful string literals for commandline output colors.
**	Can be used with any of the 'IO_Output_*' and 'IO_Write_*' functions.
**
**	(Learn more here)[https://misc.flogisoft.com/bash/tip_colors_and_formatting]
*/
//! @{
#define ANSI_STYLE(CODE)	"\x1B["#CODE"m"

#define ANSI_RESET             ANSI_STYLE(0)	//!< The string sequence to reset the terminal text output to its default color

#define ANSI_STYLE_BOLD        ANSI_STYLE(1)	//!< Display terminal output text in bold
#define ANSI_STYLE_DIM         ANSI_STYLE(2)	//!< Display terminal output text with dimmer, darker colors
#define ANSI_STYLE_ITALIC      ANSI_STYLE(3)	//!< Display terminal output text in italic
#define ANSI_STYLE_UNDERLINE   ANSI_STYLE(4)	//!< Display terminal output text with an underline
#define ANSI_STYLE_BLINK       ANSI_STYLE(5)	//!< Display terminal output text which blinks every second (only in tty and xterm)
#define ANSI_STYLE_UNKNOWN     ANSI_STYLE(6)	//!< ???
#define ANSI_STYLE_INVERTED    ANSI_STYLE(7)	//!< Display terminal output text with the background/foreground colors reversed
#define ANSI_STYLE_HIDDEN      ANSI_STYLE(8)	//!< Write, but do not display, the terminal output text (useful for passwords)
#define ANSI_STYLE_OVERLINE    ANSI_STYLE(9)	//!< Display terminal output text with an overline (a.k.a strikethrough)

#define ANSI_RESET_BOLD        ANSI_STYLE(21)	//!< Undoes the effects of #ANSI_RESET_BOLD
#define ANSI_RESET_DIM         ANSI_STYLE(22)	//!< Undoes the effects of #ANSI_RESET_DIM
#define ANSI_RESET_ITALIC      ANSI_STYLE(23)	//!< Undoes the effects of #ANSI_RESET_ITALIC
#define ANSI_RESET_UNDERLINE   ANSI_STYLE(24)	//!< Undoes the effects of #ANSI_RESET_UNDERLINE
#define ANSI_RESET_BLINK       ANSI_STYLE(25)	//!< Undoes the effects of #ANSI_RESET_BLINK
#define ANSI_RESET_UKNOWN      ANSI_STYLE(26)	//!< Undoes the effects of #ANSI_RESET_UKNOWN
#define ANSI_RESET_INVERTED    ANSI_STYLE(27)	//!< Undoes the effects of #ANSI_RESET_INVERTED
#define ANSI_RESET_HIDDEN      ANSI_STYLE(28)	//!< Undoes the effects of #ANSI_RESET_HIDDEN
#define ANSI_RESET_OVERLINE    ANSI_STYLE(29)	//!< Undoes the effects of #ANSI_RESET_OVERLINE

//! ANSI Color code (255-map, not supported on certain old terminals)
/*!
**	@param	CODE	should be a string, containing number between 0 and 255
**	@see
**	- IO_GetColor()
*/
#define ANSI_COLOR_FG(CODE)	        ANSI_STYLE("38;5;"#CODE)

#define ANSI_COLOR_FG_BLACK         ANSI_STYLE(30)	//!< The string sequence to color the terminal text output black
#define ANSI_COLOR_FG_RED           ANSI_STYLE(31)	//!< The string sequence to color the terminal text output red
#define ANSI_COLOR_FG_GREEN         ANSI_STYLE(32)	//!< The string sequence to color the terminal text output green
#define ANSI_COLOR_FG_YELLOW        ANSI_STYLE(33)	//!< The string sequence to color the terminal text output yellow
#define ANSI_COLOR_FG_BLUE          ANSI_STYLE(34)	//!< The string sequence to color the terminal text output blue
#define ANSI_COLOR_FG_MAGENTA       ANSI_STYLE(35)	//!< The string sequence to color the terminal text output magenta
#define ANSI_COLOR_FG_CYAN          ANSI_STYLE(36)	//!< The string sequence to color the terminal text output cyan
#define ANSI_COLOR_FG_GRAY_LIGHT    ANSI_STYLE(37)	//!< The string sequence to color the terminal text output light gray
#define ANSI_COLOR_FG_GRAY_DARK     ANSI_STYLE(90)	//!< The string sequence to color the terminal text output dark gray
#define ANSI_COLOR_FG_RED_LIGHT     ANSI_STYLE(91)	//!< The string sequence to color the terminal text output light red
#define ANSI_COLOR_FG_GREEN_LIGHT   ANSI_STYLE(92)	//!< The string sequence to color the terminal text output light green
#define ANSI_COLOR_FG_YELLOW_LIGHT  ANSI_STYLE(93)	//!< The string sequence to color the terminal text output light yellow
#define ANSI_COLOR_FG_BLUE_LIGHT    ANSI_STYLE(94)	//!< The string sequence to color the terminal text output light blue
#define ANSI_COLOR_FG_MAGENTA_LIGHT ANSI_STYLE(95)	//!< The string sequence to color the terminal text output light magenta
#define ANSI_COLOR_FG_CYAN_LIGHT    ANSI_STYLE(96)	//!< The string sequence to color the terminal text output light cyan
#define ANSI_COLOR_FG_WHITE         ANSI_STYLE(97)	//!< The string sequence to color the terminal text output white

//! The string sequence to color the terminal text output with the default color for this terminal
#define ANSI_COLOR_FG_DEFAULT       ANSI_STYLE(39)

//! ANSI Color code (255-map, not supported on certain old terminals)
/*!
**	@param	CODE	should be a string, containing number between 0 and 255
**	@see IO_GetColor()
*/
#define ANSI_COLOR_BG(CODE)	        ANSI_STYLE("48;5;"#CODE)

#define ANSI_COLOR_BG_BLACK         ANSI_STYLE(40)	//!< The string sequence to color the terminal text background/highlight black
#define ANSI_COLOR_BG_RED           ANSI_STYLE(41)	//!< The string sequence to color the terminal text background/highlight red
#define ANSI_COLOR_BG_GREEN         ANSI_STYLE(42)	//!< The string sequence to color the terminal text background/highlight green
#define ANSI_COLOR_BG_YELLOW        ANSI_STYLE(43)	//!< The string sequence to color the terminal text background/highlight yellow
#define ANSI_COLOR_BG_BLUE          ANSI_STYLE(44)	//!< The string sequence to color the terminal text background/highlight blue
#define ANSI_COLOR_BG_MAGENTA       ANSI_STYLE(45)	//!< The string sequence to color the terminal text background/highlight magenta
#define ANSI_COLOR_BG_CYAN          ANSI_STYLE(46)	//!< The string sequence to color the terminal text background/highlight cyan
#define ANSI_COLOR_BG_GRAY_LIGHT    ANSI_STYLE(47)	//!< The string sequence to color the terminal text background/highlight light gray
#define ANSI_COLOR_BG_GRAY_DARK     ANSI_STYLE(100)	//!< The string sequence to color the terminal text background/highlight dark gray
#define ANSI_COLOR_BG_RED_LIGHT     ANSI_STYLE(101)	//!< The string sequence to color the terminal text background/highlight light red
#define ANSI_COLOR_BG_GREEN_LIGHT   ANSI_STYLE(102)	//!< The string sequence to color the terminal text background/highlight light green
#define ANSI_COLOR_BG_YELLOW_LIGHT  ANSI_STYLE(103)	//!< The string sequence to color the terminal text background/highlight light yellow
#define ANSI_COLOR_BG_BLUE_LIGHT    ANSI_STYLE(104)	//!< The string sequence to color the terminal text background/highlight light blue
#define ANSI_COLOR_BG_MAGENTA_LIGHT ANSI_STYLE(105)	//!< The string sequence to color the terminal text background/highlight light magenta
#define ANSI_COLOR_BG_CYAN_LIGHT    ANSI_STYLE(106)	//!< The string sequence to color the terminal text background/highlight light cyan
#define ANSI_COLOR_BG_WHITE         ANSI_STYLE(107)	//!< The string sequence to color the terminal text background/highlight white

//! The string sequence to color the terminal text background with the default color for this terminal
#define ANSI_COLOR_BG_DEFAULT       ANSI_STYLE(49)

//! @}

#ifndef __COLORS__
#define __COLORS__
#define ANSI_RESET		ANSI_STYLE(0)	//!< The string sequence to reset the terminal text output to its default color
#define ANSI_COLOR_FG_RED		ANSI_STYLE(31)	//!< The string sequence to color the terminal text output red
#define ANSI_COLOR_FG_GREEN		ANSI_STYLE(32)	//!< The string sequence to color the terminal text output green
#define ANSI_COLOR_FG_YELLOW	ANSI_STYLE(33)	//!< The string sequence to color the terminal text output yellow
#define ANSI_COLOR_FG_BLUE		ANSI_STYLE(34)	//!< The string sequence to color the terminal text output blue
#define ANSI_COLOR_FG_MAGENTA	ANSI_STYLE(35)	//!< The string sequence to color the terminal text output magenta
#define ANSI_COLOR_FG_CYAN		ANSI_STYLE(36)	//!< The string sequence to color the terminal text output cyan
#endif



/*! @endgroup */
HEADER_END
#endif
