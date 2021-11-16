
#include <libccc.h>
#include <libccc/sys/io.h>
#include <libccc/sys/ansi.h>

#include "ppp.h"



extern int	c_sym_type(const char *);  /* returns type from symbol table */
#define c_sym_type(identifier) IDENTIFIER /* with no symbol table, fake it */



void	ppp_error(char const* message)
{
	IO_Write_Format(STDERR, "ppp -> %i:%i: "C_RED"error"C_RESET": %s\n",
		yylloc.first_line,
		yylloc.first_column,
		message);
}

void	ppp_verbatim(char const* str)
{
	IO_Output_String(str);
}



void	ppp_comment_block(char const* str)
{
	ppp_error("unterminated comment");
}

void	ppp_comment_line(char const* str)
{
	ppp_error("line comments not supported yet lol");
}



int		ppp_symbol(char const* str)
{
	switch (c_sym_type(str))
	{
		case TYPEDEF_NAME:         printf("\n""found type %s",  str); return TYPEDEF_NAME;         /* previously defined */
		case ENUMERATION_CONSTANT: printf("\n""found enum %s",  str); return ENUMERATION_CONSTANT; /* previously defined */
		default:                   printf("\n""found thing %s", str); return IDENTIFIER;           /* includes undefined */
	}
}



int	main(int argc, char** argv)
{
	if (argc <= 1)
	{
		ppp_error("not enough arguments");
		return (EXIT_FAILURE);
	}
	for (int i = 0; i < argc; ++i)
	{
		IO_Output_Format("- found arg");
	}
}
