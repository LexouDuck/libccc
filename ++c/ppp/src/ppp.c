
#include <libccc.h>
#include <libccc/memory.h>
#include <libccc/string.h>
#include <libccc/sys/io.h>
#include <libccc/sys/ansi.h>

#include "ppp.h"



s_ppp ppp;



#define DEFINEFUNC_PPP_SYMBOLTABLE_GET(KIND) \
s_symbol_##KIND* ppp_getsymbol_##KIND(char const* name) \
{ \
	for (t_uint i = 0; i < ppp.symbolcount_##KIND; ++i) \
	{ \
		if (String_Equals(name, ppp.symboltable_##KIND[i].name)) \
		{ \
			return (&ppp.symboltable_##KIND[i]); \
		} \
	} \
	return (NULL); \
} \

#define DEFINEFUNC_PPP_SYMBOLTABLE_ADD(KIND) \
void ppp_addsymbol_##KIND(s_symbol_##KIND symbol) \
{ \
	ppp.symbolcount_##KIND++; \
	if (ppp.symboltable_##KIND == NULL) \
	{ \
		ppp.symboltable_##KIND = Memory_Allocate(ppp.symbolcount_##KIND * sizeof(s_symbol_##KIND)); \
		ppp.symboltable_##KIND[0] = symbol; \
	} \
	else \
	{ \
		ppp.symboltable_##KIND = Memory_Reallocate(ppp.symboltable_##KIND, \
			ppp.symbolcount_##KIND * sizeof(s_symbol_##KIND)); \
	} \
} \

#define DEFINEFUNC_PPP_SYMBOLTABLE_DEL(KIND) \
void ppp_removesymbol_##KIND(char const* name) \
{ \
	if (ppp.symboltable_##KIND == NULL) \
	{ \
		ppp_error("symbol table '"#KIND"' is empty, but attempted to remove symbol '%s'", name); \
		return; \
	} \
	else \
	{ \
		s_symbol_##KIND* symbol = ppp_getsymbol_##KIND(name); \
		if (symbol == NULL) \
		{ \
			ppp_error("symbol table '"#KIND"', could not find symbol to remove '%s'", name); \
			return; \
		} \
		ppp.symboltable_##KIND = Memory_Reallocate(ppp.symboltable_##KIND, \
			ppp.symbolcount_##KIND * sizeof(s_symbol_##KIND)); \
	} \
	ppp.symbolcount_##KIND--; \
} \

#undef	SYMBOL
#define SYMBOL(KIND, SYMBOLINFO) \
	DEFINEFUNC_PPP_SYMBOLTABLE_ADD(KIND) \
	DEFINEFUNC_PPP_SYMBOLTABLE_GET(KIND) \
	DEFINEFUNC_PPP_SYMBOLTABLE_DEL(KIND) \

#include "ppp.symboltypes.c"
#undef	SYMBOL



#define DEFINEFUNC_PPP_LOGGING(KIND, FORMAT, EXTRA) \
void	ppp_##KIND(char const* format, ...)				\
{														\
	int		result = 0;									\
	t_char* message = NULL;								\
	va_list args;										\
														\
	EXTRA												\
	if (format == NULL) return;							\
	va_start(args, format);								\
	message = String_Format_VA(format, args);			\
	va_end(args);										\
	if (message == NULL) return;						\
	result = IO_Write_Format(STDERR, FORMAT,			\
		yylineno,										\
		message);										\
	String_Delete(&message);							\
	if (result < 0) return;								\
	return;												\
}														\

DEFINEFUNC_PPP_LOGGING(error  , "ppp: line %i: "C_RED   "error"  C_RESET": %s\n", ppp.errors   += 1;)
DEFINEFUNC_PPP_LOGGING(warning, "ppp: line %i: "C_YELLOW"warning"C_RESET": %s\n", ppp.warnings += 1;)
DEFINEFUNC_PPP_LOGGING(message, "ppp: line %i: "C_RESET "message"C_RESET": %s\n", )



int ppp_init(void)
{
	// TODO flag settings ?
	return (OK);
}

int ppp_exit(void)
{
	if (ppp.errors > 0)
	{
		IO_Write_Format(STDERR, "ppp: exited with %u errors total\n", ppp.errors);
		return (ERROR);
	}
	return (OK);
}



int	ppp_verbatim(char const* str, int lex)
{
	IO_Output_String(str); // TODO construct a buffer and write once at the end
	return (lex);
}



void	ppp_comment_block(char const* str)
{
	//if (ppp_flags.no_comments == FALSE)
	ppp_verbatim(str, 0);
}

void	ppp_comment_line(char const* str)
{
	//if (ppp_flags.no_comments == FALSE)
	ppp_verbatim(str, 0);
}

void	ppp_whitespace(char const* str)
{
	//if (ppp_flags.minified == FALSE)
	ppp_verbatim(str, 0);
}



int		ppp_symbol(char const* str)
{
	if (ppp_getsymbol_macro  (str))	return (MACRO_NAME);
	if (ppp_getsymbol_enum   (str))	return (LITERAL_ENUM);
	if (ppp_getsymbol_type   (str))	return (TYPEDEF_NAME);
	if (ppp_getsymbol_typedef(str))	return (TYPEDEF_NAME);
	if (ppp_getsymbol_func   (str))	return (IDENTIFIER);
	if (ppp_getsymbol_global (str))	return (IDENTIFIER);
	if (ppp_getsymbol_local  (str))	return (IDENTIFIER);
	ppp_error("unknown symbol: %s", str);
	return (IDENTIFIER);
}



int		ppp_c_line(char const* str, int lex)
{
	//if (ppp_flags.no_lines == FALSE)
	ppp_verbatim(str, 0);
	return (lex);
}

int		ppp_c_define(char const* str, int lex)
{
	// TODO custom parsing logic
	ppp_verbatim(str, 0);
	return (lex);
}

int		ppp_c_include(char const* str, int lex)
{
	// TODO custom parsing logic
	ppp_verbatim(str, 0);
	return (lex);

}



int	main(int argc, char** argv)
{
	if (argc <= 1)
	{
		ppp_error("not enough arguments");
		return (EXIT_FAILURE);
	}
	for (int i = 1; i < argc; ++i)
	{
		if (argv[i][0] == '-')
		{
			// TODO logic to handle argument flags
		}
		else
		{
			ppp_message("parsing file '%s'", argv[i]);
			ppp_init();
			// Open a file handle to a particular file:
			FILE *file = fopen(argv[i], "r");
			// Make sure it is valid:
			if (!file)
			{
				ppp_error("input file '%s' could not be opened for reading", argv[i]);
				return (EXIT_FAILURE);
			}
			// Set Flex to read from it instead of defaulting to STDIN:
			yyin = file;
			// begin lex/yacc on input file
			yyparse();
		}
	}
}
