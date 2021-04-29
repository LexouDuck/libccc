/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/sys/ansi.h                        |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_SYS_ANSI_H
#define __LIBCCC_SYS_ANSI_H
/*!@group{libccc_sys_ansi}
** @{
**	This header defines some useful ANSI text macros.
**
**	@isostd{https://en.cppreference.com/w/c/ansi}
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! ANSI text output display macros
/*!
**	These are some useful string literals for commandline output colors.
**	Can be used with any of the 'IO_Output_*' and 'IO_Write_*' functions.
**
**	(Learn more here)[https://misc.flogisoft.com/bash/tip_colors_and_formatting]
*/
//! @{
#define ANSI(X)		"\x1B["X"m"

// TODO refactor  these macros to instead have an 'ANSI_' prefix

#define IO_RESET			ANSI("0")	//!< The string sequence to reset the terminal text output to its default color

#define IO_TEXT_BOLD		ANSI("1")	//!< Display terminal output text in bold
#define IO_TEXT_DIM			ANSI("2")	//!< Display terminal output text with dimmer, darker colors
#define IO_TEXT_3			ANSI("3")	//!< ???
#define IO_TEXT_UNDERLINE	ANSI("4")	//!< Display terminal output text with an underline
#define IO_TEXT_BLINK		ANSI("5")	//!< Display terminal output text which blinks every second (only in tty and xterm)
#define IO_TEXT_6			ANSI("6")	//!< ???
#define IO_TEXT_INVERTED	ANSI("7")	//!< Display terminal output text with the background/foreground colors reversed
#define IO_TEXT_HIDDEN		ANSI("8")	//!< Write, but do not display, the terminal output text (useful for passwords)
#define IO_TEXT_9			ANSI("9")	//!< ???

#define IO_TEXT_RESET_BOLD		ANSI("21")	//!< Undoes the effects of #IO_TEXT_BOLD
#define IO_TEXT_RESET_DIM		ANSI("22")	//!< Undoes the effects of #IO_TEXT_DIM
#define IO_TEXT_RESET_3			ANSI("23")	//!< Undoes the effects of #IO_TEXT_3
#define IO_TEXT_RESET_UNDERLINE	ANSI("24")	//!< Undoes the effects of #IO_TEXT_UNDERLINE
#define IO_TEXT_RESET_BLINK		ANSI("25")	//!< Undoes the effects of #IO_TEXT_BLINK
#define IO_TEXT_RESET_6			ANSI("26")	//!< Undoes the effects of #IO_TEXT_6
#define IO_TEXT_RESET_INVERTED	ANSI("27")	//!< Undoes the effects of #IO_TEXT_INVERTED
#define IO_TEXT_RESET_HIDDEN	ANSI("28")	//!< Undoes the effects of #IO_TEXT_HIDDEN
#define IO_TEXT_RESET_9			ANSI("29")	//!< Undoes the effects of #IO_TEXT_9

#define IO_COLOR_FG_BLACK			ANSI("30")	//!< The string sequence to color the terminal text output black
#define IO_COLOR_FG_GRAY_DARK		ANSI("90")	//!< The string sequence to color the terminal text output dark gray
#define IO_COLOR_FG_RED				ANSI("31")	//!< The string sequence to color the terminal text output red
#define IO_COLOR_FG_RED_LIGHT		ANSI("91")	//!< The string sequence to color the terminal text output light red
#define IO_COLOR_FG_GREEN			ANSI("32")	//!< The string sequence to color the terminal text output green
#define IO_COLOR_FG_GREEN_LIGHT		ANSI("92")	//!< The string sequence to color the terminal text output light green
#define IO_COLOR_FG_YELLOW			ANSI("33")	//!< The string sequence to color the terminal text output yellow
#define IO_COLOR_FG_YELLOW_LIGHT	ANSI("93")	//!< The string sequence to color the terminal text output light yellow
#define IO_COLOR_FG_BLUE			ANSI("34")	//!< The string sequence to color the terminal text output blue
#define IO_COLOR_FG_BLUE_LIGHT		ANSI("94")	//!< The string sequence to color the terminal text output light blue
#define IO_COLOR_FG_MAGENTA			ANSI("35")	//!< The string sequence to color the terminal text output magenta
#define IO_COLOR_FG_MAGENTA_LIGHT	ANSI("95")	//!< The string sequence to color the terminal text output light magenta
#define IO_COLOR_FG_CYAN			ANSI("36")	//!< The string sequence to color the terminal text output cyan
#define IO_COLOR_FG_CYAN_LIGHT		ANSI("96")	//!< The string sequence to color the terminal text output light cyan
#define IO_COLOR_FG_GRAY_LIGHT		ANSI("37")	//!< The string sequence to color the terminal text output light gray
#define IO_COLOR_FG_WHITE			ANSI("97")	//!< The string sequence to color the terminal text output white

//! ANSI Color code (255-map, not supported on certain old terminals)
/*!
**	@param	CODE	should be a string, containing number between 0 and 255
**	@see
**	- IO_GetColor()
*/
#define IO_COLOR_FG(CODE)	ANSI("38;5;"CODE"")

//!< The string sequence to color the terminal text output with the default color for this terminal
#define IO_COLOR_FG_DEFAULT	ANSI("39")

#define IO_COLOR_BG_BLACK			ANSI("40")	//!< The string sequence to color the terminal text background/highlight black
#define IO_COLOR_BG_RED				ANSI("41")	//!< The string sequence to color the terminal text background/highlight red
#define IO_COLOR_BG_GREEN			ANSI("42")	//!< The string sequence to color the terminal text background/highlight green
#define IO_COLOR_BG_YELLOW			ANSI("43")	//!< The string sequence to color the terminal text background/highlight yellow
#define IO_COLOR_BG_BLUE			ANSI("44")	//!< The string sequence to color the terminal text background/highlight blue
#define IO_COLOR_BG_MAGENTA			ANSI("45")	//!< The string sequence to color the terminal text background/highlight magenta
#define IO_COLOR_BG_CYAN			ANSI("46")	//!< The string sequence to color the terminal text background/highlight cyan
#define IO_COLOR_BG_GRAY_LIGHT		ANSI("47")	//!< The string sequence to color the terminal text background/highlight light gray
#define IO_COLOR_BG_GRAY_DARK		ANSI("100")	//!< The string sequence to color the terminal text background/highlight dark gray
#define IO_COLOR_BG_RED_LIGHT		ANSI("101")	//!< The string sequence to color the terminal text background/highlight light red
#define IO_COLOR_BG_GREEN_LIGHT		ANSI("102")	//!< The string sequence to color the terminal text background/highlight light green
#define IO_COLOR_BG_YELLOW_LIGHT	ANSI("103")	//!< The string sequence to color the terminal text background/highlight light yellow
#define IO_COLOR_BG_BLUE_LIGHT		ANSI("104")	//!< The string sequence to color the terminal text background/highlight light blue
#define IO_COLOR_BG_MAGENTA_LIGHT	ANSI("105")	//!< The string sequence to color the terminal text background/highlight light magenta
#define IO_COLOR_BG_CYAN_LIGHT		ANSI("106")	//!< The string sequence to color the terminal text background/highlight light cyan
#define IO_COLOR_BG_WHITE			ANSI("107")	//!< The string sequence to color the terminal text background/highlight white

//! ANSI Color code (255-map, not supported on certain old terminals)
/*!
**	@param	CODE	should be a string, containing number between 0 and 255
**	@see IO_GetColor()
*/
#define IO_COLOR_BG(CODE)	ANSI("48;5;"CODE"")

//!< The string sequence to color the terminal text background with the default color for this terminal
#define IO_COLOR_BG_DEFAULT	ANSI("49")

//! @}

#ifndef __COLORS__
#define __COLORS__
#define C_RED		ANSI("31")	//!< The string sequence to color the terminal text output red
#define C_GREEN		ANSI("32")	//!< The string sequence to color the terminal text output green
#define C_YELLOW	ANSI("33")	//!< The string sequence to color the terminal text output yellow
#define C_BLUE		ANSI("34")	//!< The string sequence to color the terminal text output blue
#define C_MAGENTA	ANSI("35")	//!< The string sequence to color the terminal text output magenta
#define C_CYAN		ANSI("36")	//!< The string sequence to color the terminal text output cyan
#define C_RESET		ANSI("0")	//!< The string sequence to reset the terminal text output to its default color
#endif



/*! @} */
HEADER_END
#endif
