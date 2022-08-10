/*============================================================================*/
/*                                            ______________________________  */
/*  ppp_syntax.h                             |   _____    _____    _____    | */
/*                                           |  |  , \ \ |  , \ \ |  , \ \  | */
/*  https://github.com/LexouDuck/libccc.git  |  |  '_/_/ |  '_/_/ |  '_/_/  | */
/*                                           |  |  | |   |  | |   |  | |    | */
/* Comprehensive|Cross-platform|Customizable |  |__|_|   |__|_|   |__|_|    | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __PPP_SYNTAX_H
#define __PPP_SYNTAX_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include <libccc.h>

#include "ppp_symbol.h"

/*
** ************************************************************************** *|
**                                  Definitions                               *|
** ************************************************************************** *|
*/

//! Lexed token integer, as defined by lex/yacc (flex/bison)
typedef int	t_lex;



//! Node in the abstract syntax list which represents the parsed source code
typedef struct syntaxlist
{
//	struct syntaxlist*	next;	//!< the next item in the list
//	struct syntaxlist*	prev;	//!< the previous item in the list
	t_lex		lexed;					//!< The lex/yacc token integer (`0` for non-tokenized substrings)
	t_char*		source_space;			//!< Any preceding whitespace, as written in source code
	t_size		source_space_length;	//!< The length of the `.source_space` string
	t_char*		source_token;			//!< The verbatim input text, as written in source code
	t_size		source_token_length;	//!< The length of the `.source_token` string
	t_char*		output;					//!< The transpiled output C code (or NULL if `.output` is identical to `.source`)
}	s_syntaxlist;
//! An AST node with all fields set to zero: acts as a terminator for an array of AST nodes
#define SYNTAXLIST_TERMINATOR	(s_syntaxlist)\
{\
	.lexed = 0,\
	.source_space = NULL,\
	.source_space_length = 0,\
	.source_token = NULL,\
	.source_token_length = 0,\
	.output = NULL,\
}

#if 0

//! Top-level node in the abstract syntax tree which represents the source code
typedef struct syntaxtree_declaration
{
	s_syntaxlist*		lex;	//!< reference to the corresponding syntaxlist item
	e_statementkind		type;	//!< the kind of statement
	s_syntaxtree_node*	code;	//!< contents of this code statement
	s_syntaxtree_node*	block;	//!< contents of the inner code block
}	s_syntaxtree_declaration;



//! The different types of statements in a function definition
typedef enum statement
{
	STATEMENT_NONE = 0,
	STATEMENT_PREPROCESSOR,
	STATEMENT_DECLARATION,
	STATEMENT_AFFECTATION,
	STATEMENT_CONTROLFLOW,
	ENUMLENGTH_STATEMENT
}	e_statement;

//! Top-level node in the abstract syntax tree which represents the source code
typedef struct syntaxtree_statement
{
	s_syntaxlist*		lex;	//!< reference to the corresponding syntaxlist item
	e_statement			kind;	//!< the kind of statement
	s_syntaxtree_node*	code;	//!< contents of this code statement
	s_syntaxtree_node*	block;	//!< contents of the inner code block
}	s_syntaxtree_statement;

#endif

/*
** ************************************************************************** *|
**                                  Functions                                 *|
** ************************************************************************** *|
*/

// syntax events

void		ppp_c_line(t_uint lineno, char const* filename);
s_symbol	ppp_c_define(char const* name, char const** args, char const* content);
void		ppp_c_include(char const* filename);



// syntax tree handling

t_uint		ppp_syntaxlist_length(void);
void		ppp_syntaxlist_add(s_syntaxlist const* item);



// syntax tree handling

// TODO

#endif
