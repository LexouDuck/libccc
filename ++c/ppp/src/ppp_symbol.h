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
	SYMBOLKIND_USER,	//!< variable or function
	SYMBOLKIND_TYPE,	//!< typedef
	SYMBOLKIND_ENUM,	//!< enum type
	SYMBOLKIND_UNION,	//!< union type
	SYMBOLKIND_STRUCT,	//!< struct type
	SYMBOLKIND_MACRO,	//!< macro #define
	ENUMLENGTH_SYMBOLKIND
}	e_symbolkind;

//! One field/subfield/argument of a symbol
typedef struct symbol_field
{
	t_char*	name;	//!< The name of this symbol field
	t_char*	type;	//!< The type associated with this symbol field
	t_char*	value;	//!< The initially-assigned value for this symbol field
}	s_symbol_field;

//! Stores all info concerning one symbol in the symbol table
typedef struct symbol
{
	e_symbolkind	kind;	//!< The type of symbol
	t_uint			scope;	//!< The scoping depth of this symbol (`0` means global)
	t_char*			name;	//!< The name of this symbol
	t_char*			type;	//!< The type associated with this symbol
	t_char*			value;	//!< The initially-assigned value for this symbol
	t_uint			fields_amount; //!< The amount of items in the `.fields` array
	s_symbol_field*	fields;	//!< The subfields of this symbol (e.g. function arguments, struct members, etc)
}	s_symbol;



/*
** ************************************************************************** *|
**                                  Functions                                 *|
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
