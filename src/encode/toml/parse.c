
#include <errno.h>

#include <libccc.h>
#include <libccc/char.h>
#include <libccc/memory.h>
#include <libccc/string.h>
#include <libccc/sys/io.h>
#include <libccc/encode/toml.h>



typedef struct toml_parse
{
	s_toml*		result;		//!< the result TOML
	t_char const*	content;	//!< the string to parse
	t_size		length;		//!< the length of the string to parse
	t_bool		strict;		//!< if TRUE, strict parsing mode is on (rigourously follows the spec)
	t_size		offset;		//!< current parsing offset
	t_uint		depth;		//!< current section nesting level
	t_size		line;		//!< current line number
}			s_toml_parse;



static
void	TOML_Parse_SkipWhitespace(s_toml_parse *p, t_bool skip_comments)
{
	while (p->content[p->offset])
	{
		if (p->content[p->offset] == '\n')
			++(p->line);
		else if (skip_comments && (
			(p->content[p->offset] == '#') ||
			(p->content[p->offset] == ';')))
		{
			while (p->content[p->offset] && p->content[p->offset] != '\n')
			{
				++(p->offset);
			}
			++(p->line);
		}
		else if (!Char_IsSpace(p->content[p->offset]))
			break;
		++(p->offset);
	}
}
/*
static t_char*	TOML_Parse_ApplySetting(s_parser *p)
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

static t_char*	TOML_Parse_ReadSetting(s_parser *p)
{
	t_char*	file;

	file = p->file;
	p->label = (p->file + p->offset);
	while (file[p->offset] && !(Char_IsSpace(file[p->offset]) ||
		file[p->offset] == '=' ||
		file[p->offset] == '#' ||
		file[p->offset] == ';'))
		++(p->offset);
	p->label_length = (file + p->offset) - p->label;
	if (file[p->offset] != '=')
		TOML_Parse_SkipWhitespace(p);
	if (file[p->offset] != '=')
		return (TOML_Parse_Error('=', " symbol but instead found ", file[p->offset]));
	++(p->offset);
	TOML_Parse_SkipWhitespace(p);
	if (!file[p->offset])
		return ("Unexpected end of file encountered before value.");
	p->value = (file + p->offset);
	while (file[p->offset] && !Char_IsSpace(file[p->offset]))
		++(p->offset);
	p->value_length = (file + p->offset) - p->value;
	++(p->offset);
	return (TOML_Parse_ApplySetting(p));
}

void		TOML_Parse(t_fd fd, s_config* config, s_logger const* logger)
{
	s_parser	parser;
	t_char*		error;

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
*/

static
t_bool	TOML_Parse_Key(s_toml_parse* p)
{

}



static
t_bool	TOML_Parse_Value(s_toml_parse* p)
{

}



static
t_bool	TOML_Parse_Section(s_toml_parse* p)
{
	while (p->content[p->offset] && p->content[p->offset] != ']')
	{

		p->offset += 1;
	}
}



s_toml*	TOML_Parse(t_char const* toml)
{
	s_toml_parse p = { 0 };

	p.content = toml;
//	p.result = ;
	TOML_Parse_SkipWhitespace(&p, TRUE);
	while (p.content[p.offset])
	{
		if (p.content[p.offset] == '[')
		{
			if (TOML_Parse_Section(&p))
				goto failure;
		}
		else
		{
			if (TOML_Parse_Key(&p))
				goto failure;
			TOML_Parse_SkipWhitespace(&p, TRUE);
			if (p.content[p.offset] == '=')
				p.offset += 1;
			else
				goto failure;
			TOML_Parse_SkipWhitespace(&p, TRUE);
			if (TOML_Parse_Value(&p))
				goto failure;
		}
		TOML_Parse_SkipWhitespace(&p, TRUE);
		++p.offset;
	}

success:
	return (p.result);

failure:
	return (NULL);
}
