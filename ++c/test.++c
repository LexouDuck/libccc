
// this is a small independent file (not part of the libccc test suite)

#include <libccc_string.h>
#include <libccc_list.h>
#include <libccc_io.h>

#include <stdio.h>



#define COUNT 8
int main()
{
	static char* lines[COUNT] =
	{
		"Yo my boi",
		"What's up dog",
		"Not much, you ?",
		"...",
		"Yo spit it out",
		"What's the deal ?",
		"You got the dope ?",
		"I ask the questions.",
	};

	// s_array
	{
		s_array* str_array = &(s_array)
		{
			.item_count = COUNT,
			.item_size = sizeof(char*),
			.items = lines,
		};
		foreach (char*, str, s_array, str_array)
		{
			IO_Output_Format("i:%zu,ptr:%p,\tstr:%p -> \"%s\"\n", str_i, str_ptr, str, str);
		}
	}

	// s_list
	{
		s_list* str_list = NULL;
		for (int i = 0; i < COUNT; ++i)
		{
			List_Append(&str_list, List_New(lines[i], lines[i] ? String_Length(lines[i]) : 0));
		}
		foreach (char*, str, s_list, str_list)
		{
			IO_Output_Format("i:%zu,lst:%p, size: %llu,\tstr:%p -> \"%s\"\n", str_i, str_lst, str_lst->item_size, str, str);
		}
	}
	return (OK);
}
