
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
	ppp_syntaxtree_addnode(&(s_ast)
	{
		.token = lex_token,
		.text = verbatim,
		.block = NULL,
	});
	IO_Output_String(verbatim); // TODO construct a buffer and write once at the end
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
	ppp_verbatim(lex_str, 0);
}



void	ppp_c_line(t_uint lineno, char const* filename)
{
	// TODO: if (ppp_flags.no_lines == FALSE)
	ppp.display_file = filename;
	ppp.display_line = lineno;
}

void	ppp_c_define(char const* name, char const** args, char const* content)
{
	s_symbol symbol = (s_symbol)
	{
		.kind = SYMBOLKIND_MACRO,
		.name = c_strdup(name),
		.fields = ppp_symbolfieldsfromstrarr(c_strarrdup(args)),
		.value = c_strdup(content),
	};
	ppp_symboltable_create(&symbol);
	// TODO custom input buffer switching logic ?
}

void	ppp_c_include(char const* filename)
{
	ppp_message("includes file: %s", filename);
	// TODO custom input buffer switching logic
}



t_uint	ppp_syntaxtree_length(void)
{
	t_uint i = 0;
	while (
		ppp.syntax_tree[i].text != NULL ||
		ppp.syntax_tree[i].token != '\0')
	{
		++i;
	}
	return (i);
}

void	ppp_syntaxtree_addnode(s_ast const* node)
{
	t_uint	length = ppp_syntaxtree_length();
	ppp.syntax_tree = c_realloc(ppp.syntax_tree, (length + 1) * sizeof(s_ast));
	ppp.syntax_tree[length] = *node;
}
