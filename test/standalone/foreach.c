// this is a small independent file (not part of the libccc test suite)

#include <libccc.h>
#include <libccc/string.h>
#include <libccc/sys/io.h>

#include <libccc/monad/list.c>
#define T			char*
#define T_NAME		_str
#include <libccc/monad/array.c>
#define T			char*
#define T_NAME		_str
#include <libccc/monad/list.c>

//#include <libccc/monad/dict.c>
//#include <libccc/monad/tree.c>
//#include <libccc/monad/object.c>

#define T			int
#define T_NAME		_int
#define T_DEFAULT	0
#include <libccc/monad/array.c>
#define T				s_array_int
#define T_NAME			_array_int
#define T_DEFAULT		(s_array_int){ .length = 0, .items = NULL }
#define T_EQUALS(A, B)	(Array_Equals_int(&(A), &(B)))
#include <libccc/monad/array.c>

#define T			int
#define T_NAME		_int
#define T_DEFAULT	0
#include <libccc/monad/list.c>
#define T				s_list_int
#define T_NAME			_list_int
#define T_DEFAULT		(s_list_int){ 0 }
#define T_EQUALS(A, B)	(List_Equals_int(&(A), &(B)))
#include <libccc/monad/list.c>

//#include <libccc/monad/dict.c>
//#include <libccc/monad/tree.c>
//#include <libccc/monad/object.c>



#define COUNT 10
int main(int argc, char** argv)
{
	t_uint i;
	t_uint j;

	if (argc < 1 || argv == NULL)
		return (ERROR);

	IO_Output_String("\n- s_array<char*>:\n");
	{
		s_array_str* tmp = Array_Create_str(COUNT,
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
		foreach (char*, str, s_array, tmp)
		{
			IO_Output_Format("\t""i:%u,\t""iter:%u,\t""str:%p -> \"%s\"\n",
				i++, str_i, (void*)str, str);
		}
		Array_Delete_str(&tmp);
	}
	IO_Output_String("\n- s_list<char*>:\n");
	{
		s_list_str* tmp = List_Create_str(COUNT,
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
		foreach (char*, str, s_list, tmp)
		{
			IO_Output_Format("\t""i:%u,\t""iter:%p,\t""str:%p -> \"%s\"\n",
				i++, (void*)str_i, (void*)str, str);
		}
		List_Delete_str(&tmp);
	}


#if 1
	IO_Output_String("\n- s_array<s_array<int>>:\n");
	{
		s_array_array_int* tmp = Array_Create_array_int(4,
			Array_Create_int(3,	0, 1, 10),
			Array_Create_int(3,	42, 69, 420),
			Array_Create_int(3,	42, 69, 420),
			Array_Create_int(6,	42, 69, 420, 0, 1, 10));
		Array_RemoveAt_array_int(tmp, 1);
		i = 0;
		foreach (s_array_int, int_array, s_array, tmp)
		{
			//IO_Output_Format("i:%u,\titer:%u,\t""length: %u\n", i++, int_array_i, int_array.length);
			j = 0;
			foreach (int, integer, s_array, &int_array)
			{
				IO_Output_Format("\t""i:%u,\t""j:%u,\t""iter:%u,\t""int: %i\n",
					i++, j++, integer_i, integer);
			}
		}
		Array_Delete_F_array_int(&tmp, Array_Delete_int);
	}
#endif
#if 1
	IO_Output_String("\n- s_list<s_list<int>>:\n");
	{
		s_list_list_int* tmp = List_Create_list_int(4,
			List_Create_int(3, 	0, 1, 10),
			List_Create_int(3, 	42, 69, 420),
			List_Create_int(3, 	42, 69, 420),
			List_Create_int(6, 	42, 69, 420, 0, 1, 10));
		List_RemoveAt_list_int(tmp, 1);
		i = 0;
		foreach (s_list_int, int_list, s_list, tmp)
		{
			j = 0;
			foreach (int, integer, s_list, &int_list)
			{
				IO_Output_Format("\t""i:%u,\t""j:%u,\t""iter:%p,\t""int: %i\n",
					i++, j++, (void*)integer_i, integer);
			}
		}
		List_Delete_F_list_int(&tmp, List_Delete_int);
	}
#endif
	return (OK);
}
