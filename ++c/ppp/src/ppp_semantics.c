
#include <libccc.h>
#include <libccc/memory.h>
#include <libccc/int.h>
#include <libccc/string.h>
#include <libccc/sys/io.h>
#include <libccc/sys/ansi.h>

#include "ppp.h"



void	ppp_c_line(t_uint lineno, char const* filename)
{
	// TODO: if (ppp_flags.no_lines == FALSE)
	if (lineno == 0)
	{
		ppp.display_file = ppp.current_file;
		ppp.display_line = ppp.current_line;
	}
	else
	{
		ppp.display_file = filename;
		ppp.display_line = lineno;
	}
}

s_symbol	ppp_c_define(char const* name, char const** args, char const* content)
{
	s_symbol symbol = (s_symbol)
	{
		.kind = SYMBOLKIND_MACRO,
		.name   = (name == NULL) ? NULL : c_strdup(name),
		.fields = (args == NULL) ? NULL : ppp_symbolfieldsfromstrarr(c_strarrdup(args)),
		.value  = (content == NULL) ? NULL : c_strdup(content),
	};
	ppp_symboltable_create(&symbol);
	// TODO custom input buffer switching logic ?
	return (symbol);
}

void	ppp_c_include(char const* filename)
{
	ppp_message("includes file: %s", filename);
	// TODO custom input buffer switching logic
}
