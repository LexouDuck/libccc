
#include <stdio.h>



#include "libccc/string.h"
#include "libccc/sys/io.h"
#include "libccc/encode/common.h"
#include "libccc/encode/json.h"
#include "libccc/encode/toml.h"



int main(int argc, char** argv)
{
	t_char* json = IO_Read_Filepath_Text("./test/_kvt_test.json");
	s_kvt* item = JSON_FromString(json);
/*
	s_entity temp_entity = NULL_ENTITY;
	status = Avial_Create_Entity_KWARGS(&worker, &temp_entity,
		auth,
		.name="Test Store Memory",
		.klass=CLASS_AVESTERRA,
		.subklass=SUBCLASS_ENTITY,
		.context=CONTEXT_AVESTERRA,
		.outlet=ADAPTER_OBJECT
	);
	if (status) { return (status); }

	status = Avial_Store_Entity(&worker, temp_entity, auth, value, NULL);
	if (status) { return (status); }
*/
	t_char* str = JSON_ToString(item);
	IO_Output_Line(str);
	String_Delete(&str);
	String_Delete(&json);
	return (OK);
}
