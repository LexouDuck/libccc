// this is a small independent file (not part of the libccc test suite)

#include <stdio.h>

#include <libccc.h>
#include <libccc/string.h>
#include <libccc/sys/io.h>

#define T		char*
#define TYPE	_str
#include <libccc/monad/array.h>
#include <libccc/monad/list.h>
#include <libccc/monad/dict.h>
#include <libccc/monad/tree.h>
#include <libccc/monad/object.h>
/*
#define T		t_sint
#define TYPE	_sint
#include <libccc/monad/array.h>
#include <libccc/monad/list.h>
#include <libccc/monad/dict.h>
#include <libccc/monad/tree.h>
#include <libccc/monad/object.h>
*/



#define COUNT 10
int main()
{
	static char* lines[COUNT] =
	{
		"Yo, my boi!",
		"What's up, dog?",
		"Not much, you ?",
		"...",
		"Yo, spit it out.",
		"What's the deal ?",
		"You got the dope ?",
		"I ask the questions.",
		"He's got a gun!",
		"FREEZE! HANDS IN THE AIR!",
	};
	t_size i;

	IO_Output_String("\n- s_array:\n");
	{
		s_array_str* str_array = &(s_array_str)
		{
			.length = COUNT,
			.items = lines,
		};
		i = 0;
		foreach (char*, str, s_array, str_array)
		{
			IO_Output_Format("i:%zu,\titer:%zu,\tstr:%p -> \"%s\"\n", i++, str_i, str, str);
		}
	}

	IO_Output_String("\n- s_list:\n");
	{
		s_list_str* str_list = List_New(COUNT,
			"Yo, my boi!",
			"What's up, dog?",
			"Not much, you ?",
			"...",
			"Yo, spit it out.",
			"What's the deal ?",
			"You got the dope ?",
			"I ask the questions.",
			"He's got a gun!",
			"FREEZE! HANDS IN THE AIR!"
		);
		foreach (char*, str, s_list, str_list)
		{
			IO_Output_Format("i:%zu,\titer:%p,\tstr:%p -> \"%s\"\n", i++, str_i, str, str);
		}
	}
	return (OK);
}
