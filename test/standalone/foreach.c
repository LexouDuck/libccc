// this is a small independent file (not part of the libccc test suite)

#include <libccc.h>
#include <libccc/string.h>
#include <libccc/sys/io.h>


#define T_TYPE	char*
#define T_NAME	str
#define T_NULL	NULL
#define T_EQUALS(A, B)	(String_Equals((A), (B)))
#include <libccc/generic/array.c>

#define T_TYPE	char*
#define T_NAME	str
#define T_NULL	NULL
#define T_EQUALS(A, B)	(String_Equals((A), (B)))
#include <libccc/generic/list.c>

#define T_TYPE	char*
#define T_NAME	str
#define T_NULL	NULL
#define T_EQUALS(A, B)	(String_Equals((A), (B)))
#include <libccc/generic/dict.c>

#define T_TYPE	char*
#define T_NAME	str
#define T_NULL	NULL
#define T_EQUALS(A, B)	(String_Equals((A), (B)))
#include <libccc/generic/tree.c>

#define T_TYPE	char*
#define T_NAME	str
#define T_NULL	NULL
#define T_EQUALS(A, B)	(String_Equals((A), (B)))
#include <libccc/generic/set.c>

#define T_TYPE	char*
#define T_NAME	str
#define T_NULL	NULL
#define T_EQUALS(A, B)	(String_Equals((A), (B)))
#include <libccc/generic/convert.c>

//#include <libccc/generic/object.c>

#define T_TYPE	int
#define T_NAME	int
#define T_NULL	0
#include <libccc/generic/array.c>

#define T_TYPE	s_array_int*
#define T_NAME	array_int
#define T_NULL	&(s_array_int){ .length = 0, .items = NULL }
#define T_EQUALS(A, B)	(Array_Equals_int((A), (B)))
#include <libccc/generic/array.c>

#define T_TYPE	int
#define T_NAME	int
#define T_NULL	0
#include <libccc/generic/list.c>

#define T_TYPE	s_list_int*
#define T_NAME	list_int
#define T_NULL	&(s_list_int){ 0 }
#define T_EQUALS(A, B)	(List_Equals_int((A), (B)))
#include <libccc/generic/list.c>

#define T_TYPE	int
#define T_NAME	int
#define T_NULL	0
#include <libccc/generic/dict.c>

#define T_TYPE	int
#define T_NAME	int
#define T_NULL	0
#include <libccc/generic/tree.c>

#define T_TYPE	int
#define T_NAME	int
#define T_NULL	0
#include <libccc/generic/set.c>

#define T_TYPE	int
#define T_NAME	int
#define T_NULL	0
#include <libccc/generic/convert.c>

//#include <libccc/generic/object.c>



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
			Array_Create(int)(3, 0, 1, 10),
			Array_Create(int)(3, 42, 69, 420),
			Array_Create(int)(3, 42, 69, 420),
			Array_Create(int)(6, 42, 69, 420, 0, 1, 10));
//		Array_RemoveAt(array_int)(tmp, 1);
		i = 0;
		foreach (s_array(int)*, int_array, s_array, tmp)
		{
			j = 0;
			foreach (int, integer, s_array, int_array)
			{
				IO_Output_Format("\t""i:%u,\t""j:%u,\t""iter:%u,\t""int: %i\n",
					i, j, integer_i, integer);
				++j;
			}
			++i;
		}
		Array_Delete_F(array_int)(&tmp, Array_Delete(int));
	}
#endif
#if 1
	IO_Output_String("\n- s_list<s_list<int>>:\n");
	{
		s_list(list_int)* tmp = List_Create(list_int)(4,
			List_Create(int)(3, 0, 1, 10),
			List_Create(int)(3, 42, 69, 420),
			List_Create(int)(3, 42, 69, 420),
			List_Create(int)(6, 42, 69, 420, 0, 1, 10));
//		List_RemoveAt(list_int)(tmp, 1);
		i = 0;
		foreach (s_list(int)*, int_list, s_list, tmp)
		{
			j = 0;
			foreach (int, integer, s_list, int_list)
			{
				IO_Output_Format("\t""i:%u,\t""j:%u,\t""iter:%p,\t""int: %i\n",
					i, j, (void*)integer_i, integer);
				++j;
			}
			++i;
		}
		List_Delete_F(list_int)(&tmp, List_Delete(int));
	}
#endif

#if 1
	IO_Output_String("\n- s_dict<char*>:\n");
	{
		s_dict(str)* tmp = Dict_Create(str)(4,
			"first",  "Omae",
			"second", " wa ",
			"third",  "mou ",
			"fourth", "shindeiru.");
		i = 0;
		foreach (s_keyval(str), keyval, s_dict, tmp)
		{
			IO_Output_Format("\t""i:%u,\t""iter:%u,\t""key:\"%s\" -> value:\"%s\"\n",
				i++, keyval_i, keyval.key, keyval.value);
		}
		Dict_Delete(str)(&tmp);
	}
#endif
#if 1
	IO_Output_String("\n- s_dict<int>:\n");
	{
		s_dict(int)* tmp = Dict_Create(int)(3,
			"one",   1,
			"two",   2,
			"three", 3);
		i = 0;
		foreach (s_keyval(int), keyval, s_dict, tmp)
		{
			IO_Output_Format("\t""i:%u,\t""iter:%u,\t""key:\"%s\" -> value:%i (hash:%llX)\n",
				i++, keyval_i, keyval.key, keyval.value, (unsigned long long)keyval.hash);
		}
		Dict_Delete(int)(&tmp);
	}
#endif

#if 1
	IO_Output_String("\n- s_tree<char*>:\n");
	{
		s_tree(str)* tmp = Tree_Create(str)("Omae", 2, " wa ", "mou ");
		Tree_Append(str)(Tree_Get(str)(tmp, 1), Tree_Item(str)("shindeiru."));
		i = 0;
		foreach (s_tree(str)*, node, s_tree, tmp) // NOTE: iterates the DIRECT sub-nodes of the given node
		{
			IO_Output_Format("\t""i:%u,\t""iter:%u,\t""node:%p -> value:\"%s\" (%u sub-nodes)\n",
				i++, (t_uint)node_i, (void*)node, node->value, (t_uint)node->node_count);
		}
		Tree_Delete(str)(&tmp);
	}
#endif
#if 1
	IO_Output_String("\n- s_tree<s_tree<int>> (nested foreach):\n");
	{
		s_tree(int)* tmp = Tree_Create(int)(1, 2, 10, 20);
		Tree_Append(int)(Tree_Get(int)(tmp, 0), Tree_Item(int)(100));
		Tree_Append(int)(Tree_Get(int)(tmp, 0), Tree_Item(int)(101));
		i = 0;
		foreach (s_tree(int)*, node, s_tree, tmp)
		{
			IO_Output_Format("\t""i:%u,\t""value:%i (%u sub-nodes)\n",
				i, node->value, (t_uint)node->node_count);
			j = 0;
			foreach (s_tree(int)*, subnode, s_tree, node)
			{
				IO_Output_Format("\t\t""i:%u,\t""j:%u,\t""value:%i\n",
					i, j++, subnode->value);
			}
			++i;
		}
		Tree_Delete(int)(&tmp);
	}
#endif

#if 1
	IO_Output_String("\n- s_set<char*> (values are unique):\n");
	{
		s_set(str)* tmp = Set_Create(str)(6, "Omae", " wa ", "mou ", "Omae", "shindeiru.", "mou ");
		i = 0;
		foreach (char*, str, s_set, tmp) // NOTE: the 6 given values only produce 4 items (duplicates are ignored)
		{
			IO_Output_Format("\t""i:%u,\t""iter:%u,\t""str:\"%s\"\n", i++, str_i, str);
		}
		Set_Delete(str)(&tmp);
	}
#endif
#if 1
	IO_Output_String("\n- s_set<int> (union/intersection):\n");
	{
		s_set(int)* evens = Set_Create(int)(3, 2, 4, 6);
		s_set(int)* small = Set_Create(int)(3, 1, 2, 3);
		s_set(int)* both = Set_Union(int)(evens, small);
		s_set(int)* common = Set_Intersect(int)(evens, small);
		i = 0;
		foreach (int, integer, s_set, both)
		{
			IO_Output_Format("\t""i:%u,\t""int:%i\n", i++, integer);
		}
		IO_Output_Format("\t""union length: %u (2 appears once), intersection contains 2: %s\n",
			Set_Length(int)(both),
			(Set_Contains(int)(common, 2) ? "TRUE" : "FALSE"));
		Set_Delete(int)(&common);
		Set_Delete(int)(&both);
		Set_Delete(int)(&small);
		Set_Delete(int)(&evens);
	}
#endif

#if 1
	IO_Output_String("\n- Array_ToList<char*> / List_ToArray<char*> (round-trip):\n");
	{
		s_array(str)* array = Array_Create(str)(3, "Omae", "wa", "shindeiru.");
		s_list(str)*  list = Array_ToList(str)(array);
		s_array(str)* back = List_ToArray(str)(list);
		i = 0;
		foreach (char*, str, s_list, list)
		{
			IO_Output_Format("\t""i:%u,\t""str:\"%s\"\n", i++, str);
		}
		IO_Output_Format("\t""round-trip equals: %s\n",
			(Array_Equals(str)(array, back) ? "TRUE" : "FALSE"));
		Array_Delete(str)(&back);
		List_Delete(str)(&list);
		Array_Delete(str)(&array);
	}
#endif
#if 1
	IO_Output_String("\n- Array_ToSet<char*> (deduplicates) / Set_ToArray<char*>:\n");
	{
		s_array(str)* array = Array_Create(str)(6, "Omae", " wa ", "mou ", "Omae", "shindeiru.", "mou ");
		s_set(str)*   uniq = Array_ToSet(str)(array);
		s_array(str)* back = Set_ToArray(str)(uniq);
		i = 0;
		foreach (char*, str, s_set, uniq)
		{
			IO_Output_Format("\t""i:%u,\t""str:\"%s\"\n", i++, str);
		}
		IO_Output_Format("\t""array length: %u -> set length: %u (duplicates removed), back to array length: %u\n",
			array->length, Set_Length(str)(uniq), back->length);
		Array_Delete(str)(&back);
		Set_Delete(str)(&uniq);
		Array_Delete(str)(&array);
	}
#endif
#if 1
	IO_Output_String("\n- List_ToSet<int> (deduplicates) / Set_ToList<int> (round-trip):\n");
	{
		s_list(int)* list = List_Create(int)(6, 4, 8, 15, 4, 23, 8);
		s_set(int)*  uniq = List_ToSet(int)(list);
		s_list(int)* back = Set_ToList(int)(uniq);
		s_set(int)*  uniq2 = List_ToSet(int)(back);
		i = 0;
		foreach (int, integer, s_list, back)
		{
			IO_Output_Format("\t""i:%u,\t""int:%i\n", i++, integer);
		}
		IO_Output_Format("\t""list length: %u -> set length: %u (duplicates removed), round-trip set equals: %s\n",
			List_Length(int)(list), Set_Length(int)(uniq),
			(Set_Equals(int)(uniq, uniq2) ? "TRUE" : "FALSE"));
		Set_Delete(int)(&uniq2);
		List_Delete(int)(&back);
		Set_Delete(int)(&uniq);
		List_Delete(int)(&list);
	}
#endif

#if 1
	IO_Output_String("\n- List_ToArray<int> / Array_ToList<int> (round-trip):\n");
	{
		s_list(int)*  list = List_Create(int)(4, 42, 69, 420, 1337);
		s_array(int)* array = List_ToArray(int)(list);
		s_list(int)*  back = Array_ToList(int)(array);
		i = 0;
		foreach (int, integer, s_array, array)
		{
			IO_Output_Format("\t""i:%u,\t""int:%i\n", i++, integer);
		}
		IO_Output_Format("\t""round-trip equals: %s\n",
			(List_Equals(int)(list, back) ? "TRUE" : "FALSE"));
		List_Delete(int)(&back);
		Array_Delete(int)(&array);
		List_Delete(int)(&list);
	}
#endif
	return (OK);
}
