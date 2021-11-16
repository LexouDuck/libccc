
#ifndef __PPP_H
#define __PPP_H

#include <stdlib.h>
#include <stdio.h>

#include <libccc.h>

#include "y.tab.h"



// Declare stuff from lex that yacc needs to know about:
extern int yylex();
extern int yyparse();
extern void yyerror(char const * s);
extern FILE *yyin;
extern int yylineno;



#undef	SYMBOL
#define SYMBOL(KIND, SYMBOLINFO) \
typedef struct symbol_##KIND								\
{															\
	SYMBOLINFO												\
}															\
s_symbol_##KIND;											\
s_symbol_##KIND*	ppp_getsymbol_##KIND(char const* name);	\
void	ppp_addsymbol_##KIND(s_symbol_##KIND symbol);		\
void	ppp_removesymbol_##KIND(char const* name);			\

#include "ppp.symboltypes.c"
#undef	SYMBOL



//! this struct stores all internal state for ppp
typedef struct ppp
{
	t_uint	errors;		//!< total amount of errors so far
	t_uint	warnings;	//!< total amount of warnings so far

#undef	SYMBOL
#define SYMBOL(KIND, SYMBOLINFO) \
	t_uint           symbolcount_##KIND;	\
	s_symbol_##KIND* symboltable_##KIND;	\

#include "ppp.symboltypes.c"
#undef	SYMBOL
}
s_ppp;

//! This global var holds all internal state
extern s_ppp ppp;



int		ppp_init(void);
int		ppp_exit(void);

_FORMAT(printf, 1, 2)	void	ppp_error  (char const* message, ...);
_FORMAT(printf, 1, 2)	void	ppp_warning(char const* message, ...);
_FORMAT(printf, 1, 2)	void	ppp_message(char const* message, ...);



void	ppp_comment_block(char const* str);
void	ppp_comment_line(char const* str);
void	ppp_whitespace(char const* str);

int		ppp_verbatim(char const* str, int lex);

int		ppp_symbol(char const* str);

int		ppp_c_line(char const* str, int lex);
int		ppp_c_define(char const* str, int lex);
int		ppp_c_include(char const* str, int lex);



#endif
