/*============================================================================*/
/*                                            ______________________________  */
/*  ppp_symbol.h                             |   _____    _____    _____    | */
/*                                           |  |  , \ \ |  , \ \ |  , \ \  | */
/*  https://github.com/LexouDuck/libccc.git  |  |  '_/_/ |  '_/_/ |  '_/_/  | */
/*                                           |  |  | |   |  | |   |  | |    | */
/* Comprehensive|Cross-platform|Customizable |  |__|_|   |__|_|   |__|_|    | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __PPP_SYMBOL_H
#define __PPP_SYMBOL_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include <libccc.h>



/*
** ************************************************************************** *|
**                                  Definitions                               *|
** ************************************************************************** *|
*/

//! Defines the different kinds of symbols stored in the symboltable
typedef enum symbolkind
{
	SYMBOLKIND_NONE = 0,
	SYMBOLKIND_USER,
	SYMBOLKIND_TYPE,
	SYMBOLKIND_ENUM,
	SYMBOLKIND_UNION,
	SYMBOLKIND_STRUCT,
	SYMBOLKIND_MACRO,
	ENUMLENGTH_SYMBOLKIND
}	e_symbolkind;

//! One field/argument of a symbol
typedef struct symbol_field
{
	t_char*	name;
	t_char*	type;
	t_char*	value;
}	s_symbol_field;

//! Stores all info concerning one symbol in the symbol table
typedef struct symbol
{
	e_symbolkind	kind;
	t_char*			name;
	t_char*			type;
	t_char*			value;
	t_uint			fields_amount;
	s_symbol_field*	fields;
}	s_symbol;



/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

//! add a new symbol field to the given s_symbol struct
void			ppp_symbol_addfield(s_symbol* symbol, s_symbol_field* field);
//! Converts a string array to a symbol_field array
s_symbol_field*	ppp_symbolfieldsfromstrarr(t_char** strarr);

//! Get the string representation of a symbol-kind enum item
t_char const*	ppp_symbolkind(e_symbolkind kind);

void			ppp_symboltable_create(s_symbol const* symbol);
void			ppp_symboltable_delete(e_symbolkind kind, t_char const* name);
s_symbol*		ppp_symboltable_find  (e_symbolkind kind, t_char const* name);



#endif
