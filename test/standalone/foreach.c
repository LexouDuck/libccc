// this is a small independent file (not part of the libccc test suite)

#include <libccc.h>
#include <libccc/string.h>
#include <libccc/sys/io.h>


#define T_TYPE	char*
#define T_NAME	str
#define T_NULL	NULL
#define T_EQUALS(A, B)	(String_Equals((A), (B)))
#include <libccc/monad/array.c>

#define T_TYPE	char*
#define T_NAME	str
#define T_NULL	NULL
#define T_EQUALS(A, B)	(String_Equals((A), (B)))
#include <libccc/monad/list.c>

//#include <libccc/monad/dict.c>
//#include <libccc/monad/tree.c>
//#include <libccc/monad/object.c>

#define T_TYPE	int
#define T_NAME	int
#define T_NULL	0
#include <libccc/monad/array.c>

#define T_TYPE	s_array(int)
#define T_NAME	array_int
#define T_NULL	(s_array(int)){ .length = 0, .items = NULL }
#define T_EQUALS(A, B)	(Array_Equals(int)(&(A), &(B)))
#include <libccc/monad/array.c>

#define T_TYPE	int
#define T_NAME	int
#define T_NULL	0
#include <libccc/monad/list.c>

#define T_TYPE	s_list(int)
#define T_NAME	list_int
#define T_NULL	(s_list(int)){ 0 }
#define T_EQUALS(A, B)	(List_Equals(int)(&(A), &(B)))
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
		s_array(str)* tmp = Array_Create(str)(COUNT,
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
		Array_Delete(str)(&tmp);
	}
	IO_Output_String("\n- s_list<char*>:\n");
	{
		s_list(str)* tmp = List_Create(str)(COUNT,
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
		List_Delete(str)(&tmp);
	}


#if 1
	IO_Output_String("\n- s_array<s_array<int>>:\n");
	{
		s_array(array_int)* tmp = Array_Create(array_int)(4,
			Array_Create(int)(3,	0, 1, 10),
			Array_Create(int)(3,	42, 69, 420),
			Array_Create(int)(3,	42, 69, 420),
			Array_Create(int)(6,	42, 69, 420, 0, 1, 10));
		Array_RemoveAt(array_int)(tmp, 1);
		i = 0;
		foreach (s_array(int), int_array, s_array, tmp)
		{
			//IO_Output_Format("i:%u,\titer:%u,\t""length: %u\n", i++, int_array_i, int_array.length);
			j = 0;
			foreach (int, integer, s_array, &int_array)
			{
				IO_Output_Format("\t""i:%u,\t""j:%u,\t""iter:%u,\t""int: %i\n",
					i++, j++, integer_i, integer);
			}
		}
		Array_Delete_F(array_int)(&tmp, Array_Delete_int);
	}
#endif
#if 1
	IO_Output_String("\n- s_list<s_list<int>>:\n");
	{
		s_list(list_int)* tmp = List_Create(list_int)(4,
			List_Create(int)(3, 	0, 1, 10),
			List_Create(int)(3, 	42, 69, 420),
			List_Create(int)(3, 	42, 69, 420),
			List_Create(int)(6, 	42, 69, 420, 0, 1, 10));
		List_RemoveAt(list_int)(tmp, 1);
		i = 0;
		foreach (s_list(int), int_list, s_list, tmp)
		{
			j = 0;
			foreach (int, integer, s_list, &int_list)
			{
				IO_Output_Format("\t""i:%u,\t""j:%u,\t""iter:%p,\t""int: %i\n",
					i++, j++, (void*)integer_i, integer);
			}
		}
		List_Delete_F(list_int)(&tmp, List_Delete_int);
	}
#endif
	return (OK);
}
