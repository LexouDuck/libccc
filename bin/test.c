#include "libccc_string.h"
#include "libccc_list.h"
#include "libccc_io.h"

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
	s_list* strlist = NULL;
	s_list* elem;
	for (int i = 0; i < COUNT; ++i)
	{
		elem = List_New(lines[i], lines[i] ? String_Length(lines[i]) : 0);
		List_Append(&strlist, elem);
	}
	foreach (char*, str, s_list, strlist)
	{
		IO_Output_Format("lst:%p,\tsize: %llu,\tstr:%p -> \"%s\"\n", _lst, _lst->item_size, str, str);
	}
}
