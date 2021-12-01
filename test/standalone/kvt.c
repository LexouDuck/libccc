
#include <stdio.h>



#include "libccc/math/math.h"
#include "libccc/string.h"
#include "libccc/sys/io.h"
#include "libccc/encode/common.h"
#include "libccc/encode/json.h"
#include "libccc/encode/toml.h"

#ifndef FILEPATH
#define FILEPATH	"./test/standalone/kvt_test.toml"
#endif

#define AMOUNT	1
#define MAXCHARS	40

int main()//(int argc, char** argv)
{
	t_char* file = IO_Read_Filepath_Text(FILEPATH);
	if (file == NULL)	{ IO_Output_Line("FILE ERROR");	return (ERROR); }
	for (t_uint i = 0; i < AMOUNT; ++i)
	{
		s_kvt* kvt = TOML_FromString(file);
		if (kvt == NULL)	{ IO_Output_Line("PARSE ERROR");	return (ERROR); }
		t_char* str = TOML_ToString(kvt);
		if (str == NULL)	{ IO_Output_Line("PRINT ERROR");	return (ERROR); }
		IO_Output_Line((AMOUNT == 1) ? str :
			String_Format(SF_UINT":\t%.30s", i, str));
		KVT_Delete(kvt);
		String_Delete(&str);
	}
	String_Delete(&file);
	return (OK);
}
