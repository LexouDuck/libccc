
#include <libccc.h>
#include <libccc/memory.h>
#include <libccc/int.h>
#include <libccc/string.h>
#include <libccc/sys/io.h>
#include <libccc/sys/ansi.h>

#include "ppp.h"



int	ppp_verbatim(char const* lex_str, int lex_token)
{
	t_char* verbatim = c_strdup(lex_str);
	yylval.v_str = verbatim;
	ppp_syntaxlist_add(&(s_syntaxlist)
	{
		.lexed = lex_token,
		.source_space = ppp.whitespace,
		.source_space_length = (ppp.whitespace == NULL) ? 0 : c_strlen(ppp.whitespace),
		.source_token = verbatim,
		.source_token_length =       (verbatim == NULL) ? 0 : c_strlen(verbatim),
		.output = NULL,
	});
	ppp.whitespace = NULL;
//	IO_Output_String(verbatim); // TODO construct a buffer and write once at the end
	return (lex_token);
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
	ppp.current_line = yylineno;
	ppp.whitespace = c_strdup(lex_str);
}



t_uint	ppp_syntaxlist_length(void)
{
	if (ppp.syntax_list == NULL)
		return (0);
	t_uint i = 0;
	while (!(ppp.syntax_list[i].lexed == '\0' && ppp.syntax_list[i].source_token == NULL))
	{
		++i;
	}
	return (i);
}

void	ppp_syntaxlist_add(s_syntaxlist const* item)
{
	t_uint	length = ppp_syntaxlist_length();
	ppp.syntax_list = (ppp.syntax_list == NULL) ?
		c_memalloc(                   (length + 2) * sizeof(s_syntaxlist)) :
		c_memrealloc(ppp.syntax_list, (length + 2) * sizeof(s_syntaxlist));
	ppp.syntax_list[length] = *item;
	ppp.syntax_list[length + 1] = SYNTAXLIST_TERMINATOR;
}
