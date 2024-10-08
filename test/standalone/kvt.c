
#include <stdio.h>



#include "libccc/math.h"
#include "libccc/string.h"
#include "libccc/sys/io.h"
#include "libccc/encode/common.h"
#include "libccc/encode/json.h"
#include "libccc/encode/toml.h"

#ifndef FILEPATH
#define FILEPATH	"./test/standalone/kvt_test.json"
#endif
/*
#ifndef FILE
#define FILE 
#endif
*/
#define AMOUNT	1
#define MAXCHARS	40

int main()//(int argc, char** argv)
{
	t_char* file;
#ifdef FILE
	file = String_Duplicate(FILE);
#else
	file =
		IO_Read_Filepath_Text(FILEPATH)
//		#include "../"FILEPATH
	;
#endif
	if (file == NULL) { IO_Output_Line(ANSI_COLOR_FG_RED"FILE ERROR"ANSI_RESET);	return (ERROR); }
	for (t_uint i = 0; i < AMOUNT; ++i)
	{
		s_kvt* kvt;
		t_char* str;
		kvt = JSON_FromString(file);
		if (kvt == NULL) { IO_Output_Line(ANSI_COLOR_FG_RED"PARSE ERROR"ANSI_RESET);	return (ERROR); }
		str = JSON_ToString(kvt);
		if (str == NULL) { IO_Output_Line(ANSI_COLOR_FG_RED"PRINT ERROR"ANSI_RESET);	return (ERROR); }
		t_char* output = String_Format(SF_UINT":\t%.30s", i, str);
		IO_Output_Line((AMOUNT == 1) ? str : output);
		KVT_Delete(kvt);
		String_Delete(&str);
		String_Delete(&output);
	}
	String_Delete(&file);
	return (OK);
}
