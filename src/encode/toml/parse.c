
#include <errno.h>

#include <libccc.h>
#include <libccc/char.h>
#include <libccc/memory.h>
#include <libccc/string.h>
#include <libccc/sys/io.h>

#include "src/config.h"
#include "src/logger.h"



static char*	TOML_Parse_Error(char expected, char* description, char instead)
{
	char*	result;
	t_size	length;
	t_size	i;

	length = String_Length(description);
	if (!(result = Memory_New((64 + length) * sizeof(char))))
		return (NULL);
	i = 0;
	String_Copy(result, "Expected \'");
	i += 10;
	result[i++] = expected;
	String_Copy(result + i, "\' (");
	i += 3;
	String_Copy(result + i, description);
	i += length;
	String_Copy(result + i, "), but instead found: \'");
	i += 21;
	result[i] = instead;
	return (result);
}

static void	TOML_Parse_SkipWhitespace(s_parser *p)
{
	char*	file;

	file = p->file;
	while (file[p->index] && (Char_IsSpace(file[p->index]) ||
		file[p->index] == '#' ||
		file[p->index] == ';'))
	{
		if (file[p->index] == '\n')
			++(p->line);
		else if (
			file[p->index] == '#' ||
			file[p->index] == ';')
		{
			while (file[p->index] && file[p->index] != '\n')
				++(p->index);
			++(p->line);
		}
		++(p->index);
	}
}

static char*	TOML_Parse_ApplySetting(s_parser *p)
{
	t_s32	index;
	t_s32	i;

	if (*(p->label + p->label_length))
		*(p->label + p->label_length) = '\0';
	i = -1;
	index = -1;
	while (++i < ENUMLENGTH_CONFIG)
		if (p->config[i].label && String_Equals(p->label, p->config[i].label))
			index = i;
	if (index == -1)
	{
		Log_Error(p->logger, 0, "Error while reading INI file, at line %zu\n"LOG_TIMESTAMP_INDENT"Unable to resolve label: %s", p->line, p->label);
		return (NULL);
	}
	if (*(p->value + p->value_length))
		*(p->value + p->value_length) = '\0';
	if (!(p->config[index].value = String_Duplicate(p->value)))
		return ("Could not create config value string");
	return (NULL);
}

static char*	TOML_Parse_ReadSetting(s_parser *p)
{
	char*	file;

	file = p->file;
	p->label = (p->file + p->index);
	while (file[p->index] && !(Char_IsSpace(file[p->index]) ||
		file[p->index] == '=' ||
		file[p->index] == '#' ||
		file[p->index] == ';'))
		++(p->index);
	p->label_length = (file + p->index) - p->label;
	if (file[p->index] != '=')
		TOML_Parse_SkipWhitespace(p);
	if (file[p->index] != '=')
		return (TOML_Parse_Error('=', " symbol but instead found ", file[p->index]));
	++(p->index);
	TOML_Parse_SkipWhitespace(p);
	if (!file[p->index])
		return ("Unexpected end of file encountered before value.");
	p->value = (file + p->index);
	while (file[p->index] && !Char_IsSpace(file[p->index]))
		++(p->index);
	p->value_length = (file + p->index) - p->value;
	++(p->index);
	return (TOML_Parse_ApplySetting(p));
}

void		TOML_Parse(t_fd fd, s_config* config, s_logger const* logger)
{
	s_parser	parser;
	char*		error;

	parser.config = config;
	parser.file = NULL;
	if (IO_Read_File(fd, &parser.file, CONFIG_FILEBUFFER) < 0)
	{
		Log_Error_IO(logger, errno, "Couldn't read config INI file.");
		return;
	}
	parser.index = 0;
	parser.line = 1;
	TOML_Parse_SkipWhitespace(&parser);
	while (parser.file[parser.index])
	{
		if ((error = TOML_Parse_ReadSetting(&parser)))
		{
			Log_Error(logger, 0, "Error while reading INI file, at line %zu\n"LOG_TIMESTAMP_INDENT"%s",
				parser.line, error);
			String_Delete(&error);
		}
		TOML_Parse_SkipWhitespace(&parser);
	}
	String_Delete(&parser.file);
}
