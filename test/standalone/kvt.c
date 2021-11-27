
#include <stdio.h>



#include "libccc/string.h"
#include "libccc/sys/io.h"
#include "libccc/encode/common.h"
#include "libccc/encode/json.h"
#include "libccc/encode/toml.h"

#define AMOUNT 1000

int main()//(int argc, char** argv)
{
	t_char* json = IO_Read_Filepath_Text("./test/_kvt_test.json");
	for (t_uint i = 0; i < AMOUNT; ++i)
	{
		s_kvt* kvt = JSON_FromString(json);
		t_char* str = JSON_ToString(kvt);
		IO_Output_Line((AMOUNT == 1) ? str : UInt_ToString(i));
		KVT_Delete(kvt);
		String_Delete(&str);
	}
	String_Delete(&json);
	return (OK);
}

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
