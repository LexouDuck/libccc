
#include <libccc.h>
#include <libccc/memory.h>
#include <libccc/string.h>
#include <libccc/sys/io.h>
#include <libccc/sys/ansi.h>

#include "ppp.h"



s_ppp ppp;



int	ppp_verbatim(char const* lex_str, int lex_token)
{
	yylval.v_str = c_strdup(lex_str);
	IO_Output_String(lex_str); // TODO construct a buffer and write once at the end
	return (lex_token);
}



void	ppp_comment_block(char const* lex_str)
{
	//if (ppp_flags.no_comments == FALSE)
	ppp_verbatim(lex_str, 0);
}

void	ppp_comment_line(char const* lex_str)
{
	//if (ppp_flags.no_comments == FALSE)
	ppp_verbatim(lex_str, 0);
}

void	ppp_whitespace(char const* lex_str)
{
	//if (ppp_flags.minified == FALSE)
	ppp_verbatim(lex_str, 0);
}



int		ppp_token(char const* lex_str)
{
	ppp_verbatim(lex_str, 0);
	s_symbol* symbol = ppp_symboltable_find(SYMBOLKIND_NONE, lex_str);
	if (symbol == NULL)
	{
		ppp_message("Parsed unknown symbol: '%s'", lex_str);
		return (IDENTIFIER);
	}
	switch (symbol->kind)
	{
		case SYMBOLKIND_USER:	return (IDENTIFIER);
		case SYMBOLKIND_TYPE:	return (NAME_TYPEDEF);
		case SYMBOLKIND_STRUCT:	return (NAME_STRUCT);
		case SYMBOLKIND_UNION:	return (NAME_UNION);
		case SYMBOLKIND_ENUM:	return (NAME_ENUM);
		case SYMBOLKIND_MACRO:	return (NAME_MACRO);
		case SYMBOLKIND_NONE:	return (IDENTIFIER);
		default:
		{
			ppp_message("Parsed unknown symbol: '%s'", lex_str);
			return (IDENTIFIER);
		}
	}
}



int		ppp_c_line(char const* lex_str, int lex_token)
{
	//if (ppp_flags.no_lines == FALSE)
	ppp_verbatim(lex_str, 0);
	return (lex_token);
}

int		ppp_c_define(char const* lex_str, int lex_token)
{
	// TODO custom parsing logic
	ppp_verbatim(lex_str, 0);
	return (lex_token);
}

int		ppp_c_include(char const* lex_str, int lex_token)
{
	// TODO custom parsing logic
	ppp_verbatim(lex_str, 0);
	return (lex_token);

}



// populate symbol table with standard builtin symbols
int ppp_init(void)
{
	// ANSI
	ppp_symboltable_create(&(s_symbol){ .kind=SYMBOLKIND_MACRO, .name="__cplusplus" });
	ppp_symboltable_create(&(s_symbol){ .kind=SYMBOLKIND_MACRO, .name="__OBJC__" });
	ppp_symboltable_create(&(s_symbol){ .kind=SYMBOLKIND_MACRO, .name="__DATE__" });
	ppp_symboltable_create(&(s_symbol){ .kind=SYMBOLKIND_MACRO, .name="__TIME__" });
	ppp_symboltable_create(&(s_symbol){ .kind=SYMBOLKIND_MACRO, .name="__FILE__" });
	ppp_symboltable_create(&(s_symbol){ .kind=SYMBOLKIND_MACRO, .name="__LINE__" });
	ppp_symboltable_create(&(s_symbol){ .kind=SYMBOLKIND_MACRO, .name="__STDC__" });
	ppp_symboltable_create(&(s_symbol){ .kind=SYMBOLKIND_MACRO, .name="__STDC_VERSION__" });
	// GNUC
	ppp_symboltable_create(&(s_symbol){ .kind=SYMBOLKIND_MACRO, .name="__GNUC__" });
	ppp_symboltable_create(&(s_symbol){ .kind=SYMBOLKIND_MACRO, .name="__COUNTER__" });
	ppp_symboltable_create(&(s_symbol){ .kind=SYMBOLKIND_MACRO, .name="__BASE_FILE__" });
	ppp_symboltable_create(&(s_symbol){ .kind=SYMBOLKIND_MACRO, .name="__INCLUDE_LEVEL__" });
	ppp_symboltable_create(&(s_symbol){ .kind=SYMBOLKIND_MACRO, .name="__BYTE_ORDER__" });
	ppp_symboltable_create(&(s_symbol){ .kind=SYMBOLKIND_MACRO, .name="__ORDER_LITTLE_ENDIAN__" });
	ppp_symboltable_create(&(s_symbol){ .kind=SYMBOLKIND_MACRO, .name="__ORDER_BIG_ENDIAN__" });
	ppp_symboltable_create(&(s_symbol){ .kind=SYMBOLKIND_MACRO, .name="__ORDER_PDP_ENDIAN__" });
	ppp_symboltable_create(&(s_symbol){ .kind=SYMBOLKIND_MACRO, .name="__FLOAT_WORD_ORDER__" });
	// C99/C++
	ppp_symboltable_create(&(s_symbol){ .kind=SYMBOLKIND_USER, .name="__func__" });
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
			// TODO robust logic to handle argument flags
			if (String_Equals(argv[i], "-d") ||
				String_Equals(argv[i], "--debug"))
				ppp.debug = TRUE;
			if (String_Equals(argv[i], "-v") ||
				String_Equals(argv[i], "--verbose"))
				ppp.verbose = TRUE;
		}
		else
		{
			ppp_init();
			ppp.current_file = argv[i];
			ppp_message("beginning to parse file: %s", ppp.current_file);
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
			// begin lex/yacc parsing on input file
			yyparse();
			if (fclose(file))
			{
				ppp_error("input file '%s' could not be closed properly", argv[i]);
				return (EXIT_FAILURE);
			}
		}
	}
	ppp_exit();
}
