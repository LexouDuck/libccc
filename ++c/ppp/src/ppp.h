/*============================================================================*/
/*                                            ______________________________  */
/*  ppp.h                                    |   _____    _____    _____    | */
/*                                           |  |  , \ \ |  , \ \ |  , \ \  | */
/*  https://github.com/LexouDuck/libccc.git  |  |  '_/_/ |  '_/_/ |  '_/_/  | */
/*                                           |  |  | |   |  | |   |  | |    | */
/* Comprehensive|Cross-platform|Customizable |  |__|_|   |__|_|   |__|_|    | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __PPP_H
#define __PPP_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <libccc.h>
#include <libccc/memory.h>
#include <libccc/string.h>
#include <libccc/stringarray.h>
#include <libccc/pointerarray.h>

#include "ppp_syntax.h"



//! Lexed token integer, as defined by lex/yacc (flex/bison)
typedef int	t_lex;



//! This struct stores all internal state for ppp
typedef struct ppp
{
	t_char const*	current_file; //!< name of the file being parsed
	t_char const*	display_file; //!< name of the file to display (taking in account any `#line` preproc statements)
	t_uint	current_line;	//!< the current line number being parsed from the `current_file`
	t_uint	display_line;	//!< the current line number to display (taking in account any `#line` preproc statements)

	t_bool	debug;		//!< if TRUE, debug mode is active
	t_bool	verbose;	//!< if TRUE, verbose mode is active

	t_uint	errors;		//!< total amount of errors so far
	t_uint	warnings;	//!< total amount of warnings so far

	t_uint		symbolcount; //!< total amount of symbols defined
	s_symbol*	symboltable; //!< the full symbol table
	s_ast*		syntax_tree; //!< the full source code, in AST format
}	s_ppp;

//! This global var holds all internal state
extern s_ppp ppp;



// logging

int		ppp_init(void);
int		ppp_exit(void);

_FORMAT(printf, 1, 2)	void	ppp_error  (char const* message, ...);
_FORMAT(printf, 1, 2)	void	ppp_failure(char const* message, ...);
_FORMAT(printf, 1, 2)	void	ppp_warning(char const* message, ...);
_FORMAT(printf, 1, 2)	void	ppp_message(char const* message, ...);
_FORMAT(printf, 1, 2)	void	ppp_verbose(char const* message, ...);
_FORMAT(printf, 1, 2)	void	ppp_debug  (char const* message, ...);

// parsing

void	ppp_comment_block(char const* lex_str);
void	ppp_comment_line(char const* lex_str);
void	ppp_whitespace(char const* lex_str);

int		ppp_verbatim(char const* lex_str, int lex_token);

//! Get the lex/yacc token integer from a lexed string
int		ppp_token(char const* lex_str);

// events

int			ppp_c_line(t_uint lineno, char const* filename);
s_symbol	ppp_c_define(char const* name, char const** args, char const* content);
void		ppp_c_include(char const* filename);



#include "y.tab.h"



//! define lex/yacc function to lex one single token
extern int yylex();
//! define lex/yacc function to parse one file
extern int yyparse();
//! define lex/yacc function callback for lex/yacc parsing syntax errors 
extern void yyerror(char const * s);
//! define lex/yacc input file handle
extern FILE *yyin;
//! define lex/yacc file line number
extern int yylineno;
//! enable yacc debug info
extern int yydebug;
//! use string type in yacc file by default
//#define YYSTYPE 	char const*



#endif
