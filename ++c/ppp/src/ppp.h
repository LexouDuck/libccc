
#ifndef __PPP_H
#define __PPP_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <libccc.h>
#include <libccc/memory.h>
#include <libccc/string.h>
#include <libccc/stringarray.h>

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



#undef	SYMBOLKIND
#define SYMBOLKIND(KIND, SYMBOLINFO) \
typedef struct symbol_##KIND								\
{															\
	SYMBOLINFO												\
}															\
s_symbol_##KIND;											\
s_symbol_##KIND*	ppp_getsymbol_##KIND(char const* name);	\
void	ppp_addsymbol_##KIND(s_symbol_##KIND symbol);		\
void	ppp_removesymbol_##KIND(char const* name);			\

#include "ppp_symbolkind.c"
#undef	SYMBOLKIND



//! this macro is simply used to remove boilerplate in yacc code
#define ppp_addsymbol(KIND, ...) \
		ppp_addsymbol_##KIND((s_symbol_##KIND)__VA_ARGS__)

//! this macro is simply used to remove boilerplate in yacc code
#define ppp_removesymbol(KIND, NAME) \
		ppp_removesymbol_##KIND(NAME)



//! this struct stores all internal state for ppp
typedef struct ppp
{
	t_char const*	current_file; //!< name of the file being parsed

	t_uint	errors;		//!< total amount of errors so far
	t_uint	warnings;	//!< total amount of warnings so far

#undef	SYMBOLKIND
#define SYMBOLKIND(KIND, SYMBOLINFO) \
	t_uint           symbolcount_##KIND;	\
	s_symbol_##KIND* symboltable_##KIND;	\

#include "ppp_symbolkind.c"
#undef	SYMBOLKIND
}
s_ppp;

//! This global var holds all internal state
extern s_ppp ppp;



int		ppp_init(void);
int		ppp_exit(void);

_FORMAT(printf, 1, 2)	void	ppp_error  (char const* message, ...);
_FORMAT(printf, 1, 2)	void	ppp_failure(char const* message, ...);
_FORMAT(printf, 1, 2)	void	ppp_warning(char const* message, ...);
_FORMAT(printf, 1, 2)	void	ppp_message(char const* message, ...);



void	ppp_comment_block(char const* lex_str);
void	ppp_comment_line(char const* lex_str);
void	ppp_whitespace(char const* lex_str);

int		ppp_verbatim(char const* lex_str, int lex_token);

int		ppp_symbol(char const* lex_str);

int		ppp_c_line(char const* lex_str, int lex_token);
int		ppp_c_define(char const* lex_str, int lex_token);
int		ppp_c_include(char const* lex_str, int lex_token);



#endif
