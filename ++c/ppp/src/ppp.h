
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
	t_char* name;
	t_char* type;
	t_char* value;
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



//! This struct stores all internal state for ppp
typedef struct ppp
{
	t_char const*	current_file; //!< name of the file being parsed
	t_uint	current_line;	//!< the current line number being parsed from the `current_file`
	t_uint	display_line;	//!< the current line number to display (taking in account any `#line` preproc statements)

	t_bool	debug;		//!< if TRUE, debug mode is active
	t_bool	verbose;	//!< if TRUE, verbose mode is active

	t_uint	errors;		//!< total amount of errors so far
	t_uint	warnings;	//!< total amount of warnings so far

	t_uint    symbolcount; //!< total amount of symbols defined
	s_symbol* symboltable; //!< the full symbol table
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

int		ppp_c_line(char const* lex_str, int lex_token);
int		ppp_c_define(char const* lex_str, int lex_token);
int		ppp_c_include(char const* lex_str, int lex_token);

// symbol table handling

//! Converts a string array to a symbol_field array
s_symbol_field*	ppp_symbolfieldsfromstrarr(char** strarr);

//! Get the string representation of a symbol-kind enum item
char const*	ppp_symbolkind(e_symbolkind kind);

void		ppp_symboltable_create(s_symbol const* symbol);
void		ppp_symboltable_delete(e_symbolkind kind, char const* name);
s_symbol*	ppp_symboltable_find  (e_symbolkind kind, char const* name);



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
