
#include <libccc/sys/io.h>
#include <libccc/encode/json.h>
#include <libccc/encode/toml.h>


t_utf8*	json_complex_min =
"{"
	"\"Attributes\":"
	"{"
		"\"SEX_ATTRIBUTE\":"		"[{\"Values\":[{\"CHARACTER\":\"M\"}]}],"
		"\"AGE_ATTRIBUTE\":"		"[{\"Values\":[{\"INTEGER\":\"82\"}]}],"
		"\"SPOUSE_ATTRIBUTE\":"		"[{\"Values\":[{\"BOOLEAN\":\"FALSE\"}]}],"
		"\"HEIGHT_ATTRIBUTE\":"		"[{\"Values\":[{\"FLOAT\":\"176.5\"}]}],"
		"\"OCCUPATION_ATTRIBUTE\":"	"[{\"Values\":[{\"STRING\":\"actor\"}]}],"
		"\"LABEL_ATTRIBUTE\":"		"[{\"Values\":[{\"TEXT\":\"Яцк Ничолсон\"}]}],"
		"\"BIRTHDAY_ATTRIBUTE\":"	"[{\"Values\":[{\"TIME\":\"-1031788800\"}]}],"
		"\"DOCUMENT_ATTRIBUTE\":"	"[{\"Values\":[{\"WEB\":\"urn:isbn:0393350967\"}]}],"
		"\"WEIGHT_ATTRIBUTE\":"
		"["
			"{\"Values\":[\"72\"],"
			"\"Properties\":[[\"listed\",\"\",\"\"]]},"
			"{\"Values\":[\"160\"],"
			"\"Properties\":[[\"reported\",\"\",\"\"],[\"pounds\",\"lbs\",\"352\"]]}"
		"],"
		"\"LOCATION_ATTRIBUTE\":"	"[{\"Values\":[{\"TEXT\":\"Los Angeles\"},{\"TEXT\":\"Aspen\"},{\"TEXT\":\"Malibu\"}]}],"
		"\"CHILD_ATTRIBUTE\":"
		"["
			"{\"Values\":[{\"TEXT\":\"Jennifer\"}],\"Properties\":[[\"Born\",\"\",\"1963\"],[\"Mother\",\"\",\"Sandra Knight\"]]},"
			"{\"Values\":[{\"TEXT\":\"Caleb\"}],\"Properties\":[[\"Born\",\"\",\"1970\"],[\"Paternity\",\"open question 2\",\"not established\"],[\"Mother\",\"\",\"Susan Anspach\"]]},"
			"{\"Values\":[{\"TEXT\":\"Honey\"}]},"
			"{\"Values\":[{\"TEXT\":\"Lorraine\"}]},"
			"{\"Values\":[{\"TEXT\":\"Raymond\"}],\"Properties\":[[\"Born\",\"youngest\",\"1992\"],[\"Mother\",\"\",\"Rebecca Broussard\"]]}"
		"]"
	"},"
	"\"Properties\":[[\"known for\",\"most popular role\",\"The Shining\"],[\"fan of\",\"famous fan\",\"Los Angeles Lakers\"],[\"fan of\",\"\",\"Bob Dylan\"],[\"also known for\",\"best performance\",\"Chinatown\"]],"
	"\"Values\":[\"actor\",\"player\",\"filmmaker\"]"
"}";

int main()
{
/*
	t_fd fd = IO_Open("../Castlevania/config1.toml", OPEN_READONLY, 0);
	if (fd < 0)
		return (ERROR);
	t_char* file = NULL;
	t_size filesize = IO_Read_File(fd, (void**)&file, 0);
	if (filesize == 0 || file == NULL)
		return (ERROR);
*/
	s_toml* object = JSON_FromString(json_complex_min);
	if (object == NULL)
		return (ERROR);
	t_char* output = TOML_ToString(object);
	if (output == NULL)
		return (ERROR);
	IO_Output_Line(output);
	return (OK);
}
