
#include <libccc.h>
#include <libccc/memory.h>
#include <libccc/string.h>
#include <libccc/sys/io.h>
#include <libccc/sys/ansi.h>

#include "ppp.h"



s_symbol_field*	ppp_symbolfieldsfromstrarr(char** strarr)
{
	t_uint	length = c_strarrlen((char const**)strarr);
	s_symbol_field* result = (s_symbol_field*)c_malloc(length * sizeof(s_symbol_field));
	for (t_uint i = 0; i < length; ++i)
	{
		result[i] = (s_symbol_field)
		{
			.name = c_strdup(strarr[i]),
			.type = NULL,
			.value = NULL,
		};
	}
	return result;
}



void ppp_symboltable_create(s_symbol const* symbol)
{
	ppp_message("New %s symbol: '%s'", ppp_symbolkind(symbol->kind), symbol->name);
	t_size size = ppp.symbolcount * sizeof(s_symbol);
	ppp.symbolcount++;
	if (ppp.symboltable == NULL)
	{
		ppp.symboltable = Memory_New(size + sizeof(s_symbol));
		ppp.symboltable[0] = *symbol;
	}
	else
	{
		s_symbol* old = ppp.symboltable;
		s_symbol* new = Memory_New(size + sizeof(s_symbol));
		Memory_Copy(new, old, size);
		Memory_Delete((void**)&old);
		ppp.symboltable = new;
	}
}

void ppp_symboltable_delete(e_symbolkind kind, char const* name)
{
	ppp_message("Removing %s symbol: '%s'", ppp_symbolkind(kind), name);
	t_size size = ppp.symbolcount * sizeof(s_symbol);
	ppp.symbolcount--;
	if (ppp.symboltable == NULL)
	{
		ppp_failure("attempted to remove symbol '%s', but %s symbol table is empty.", name, ppp_symbolkind(kind));
		return;
	}
	else
	{
		s_symbol* symbol = ppp_symboltable_find(kind, name);
		if (symbol == NULL)
		{
			ppp_failure("could not find symbol '%s' to remove from %s symbol table.", name, ppp_symbolkind(kind));
			return;
		}
		t_uint index = (symbol - ppp.symboltable);
		s_symbol* old = ppp.symboltable;
		s_symbol* new = Memory_New(size + sizeof(s_symbol));
		Memory_Copy(new, old, index);
		Memory_Copy(new, old + index + 1, size - index - 1);
		Memory_Delete((void**)&old);
		ppp.symboltable = new;
	}
}

s_symbol* ppp_symboltable_find(e_symbolkind kind, char const* name)
{
	for (t_uint i = 0; i < ppp.symbolcount; ++i)
	{
		if (kind == SYMBOLKIND_NONE ||
			kind == ppp.symboltable[i].kind)
		{
			if (String_Equals(name, ppp.symboltable[i].name))
				return (&ppp.symboltable[i]);
		}
	}
	return (NULL);
}
