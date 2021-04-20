// this is a small independent file (not part of the libccc test suite)

#include <stdio.h>

#include <libccc.h>
#include <libccc/string.h>
#include <libccc/sys/io.h>

#define T			char*
#define T_NAME		_str
#define T_DEFAULT	NULL

#include <libccc/monad/array.c>
#include <libccc/monad/list.c>
//#include <libccc/monad/dict.c>
//#include <libccc/monad/tree.c>
//#include <libccc/monad/object.c>


#undef T
#undef T_NAME
#undef T_DEFAULT
#define T			int
#define T_NAME		_int
#define T_DEFAULT	0

#include <libccc/monad/array.c>


#undef T
#undef T_NAME
#undef T_DEFAULT
#define T			s_array_int
#define T_NAME		_array_int
#define T_DEFAULT	(s_array_int){ .length = 0, .items = NULL }

#include <libccc/monad/array.c>



#define COUNT 10
int main()
{
	t_uint i;

	IO_Output_String("\n- s_array<char*>:\n");
	{
		s_array_str str_array = Array_str_New(COUNT,
			"Yo, my boi!",
			"What's up, dog?",
			"Not much, you ?",
			"...",
			"Yo, spit it out.",
			"What's the deal ?",
			"You got the dope ?",
			"I ask the questions.",
			"He's got a gun!",
			"FREEZE! HANDS IN THE AIR!");
		i = 0;
		foreach (char*, str, s_array, &str_array)
		{
			IO_Output_Format("i:%u,\titer:%u,\tstr:%p -> \"%s\"\n", i++, str_i, str, str);
		}
	}
/*
	IO_Output_String("\n- s_list<char*>:\n");
	{
		s_list_str* str_list = List_str_New(COUNT,
			"Yo, my boi!",
			"What's up, dog?",
			"Not much, you ?",
			"...",
			"Yo, spit it out.",
			"What's the deal ?",
			"You got the dope ?",
			"I ask the questions.",
			"He's got a gun!",
			"FREEZE! HANDS IN THE AIR!");
		i = 0;
		foreach (char*, str, s_list, str_list)
		{
			IO_Output_Format("i:%u,\titer:%p,\tstr:%p -> \"%s\"\n", i++, str_i, str, str);
		}
	}
*/
	IO_Output_String("\n- s_array<int>:\n");
	{
		s_array_int int_array = Array_int_New(6,
			42,
			69,
			420,
			0,
			1,
			10);
		i = 0;
		foreach (int, integer, s_array, &int_array)
		{
			IO_Output_Format("i:%u,\titer:%u,\tint: %i\n", i++, integer_i, integer);
		}
	}
	IO_Output_String("\n- s_array<int>:\n");
	{
		s_array_array_int int_array_array = Array_array_int_New(3,
			Array_int_New(3,	0, 1, 10),
			Array_int_New(3,	42, 69, 420),
			Array_int_New(6,	42, 69, 420, 0, 1, 10));
		i = 0;
		foreach (s_array_int, int_array, s_array, &int_array_array)
		{
			foreach (int, integer, s_array, &int_array)
			{
				IO_Output_Format("i:%u,\titer:%u,\tint: %i\n", i++, integer_i, integer);
			}
		}
	}
	return (OK);
}
