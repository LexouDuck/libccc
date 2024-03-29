
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/encode/json.h"

#include LIBCONFIG_ERROR_INCLUDE



static void skip_oneline_comment(t_utf8** input)
{
	*input += STRING_LENGTH("//");

	for (; (*input)[0] != '\0'; ++(*input))
	{
		if ((*input)[0] == '\n')
		{
			*input += STRING_LENGTH("\n");
			return;
		}
	}
}

static void skip_multiline_comment(t_utf8** input)
{
	*input += STRING_LENGTH("/*");

	for (; (*input)[0] != '\0'; ++(*input))
	{
		if (((*input)[0] == '*') && ((*input)[1] == '/'))
		{
			*input += STRING_LENGTH("*/");
			return;
		}
	}
}

static void minify_string(t_utf8** input, t_utf8** output)
{
	(*output)[0] = (*input)[0];
	*input += STRING_LENGTH("\"");
	*output += STRING_LENGTH("\"");

	for (; (*input)[0] != '\0'; (void)++(*input), ++(*output))
	{
		(*output)[0] = (*input)[0];

		if ((*input)[0] == '\"')
		{
			(*output)[0] = '\"';
			*input += STRING_LENGTH("\"");
			*output += STRING_LENGTH("\"");
			return;
		}
		else if (((*input)[0] == '\\') && ((*input)[1] == '\"'))
		{
			(*output)[1] = (*input)[1];
			*input += STRING_LENGTH("\"");
			*output += STRING_LENGTH("\"");
		}
	}
}

void	JSON_Minify(t_utf8* json)
{
	t_utf8* into = json;

	if (json == NULL)
		return;

	while (json[0] != '\0')
	{
		switch (json[0])
		{
			case ' ':
			case '\t':
			case '\r':
			case '\n':
				json++;
				break;

			case '/':
				if (json[1] == '/')
				{
					skip_oneline_comment(&json);
				}
				else if (json[1] == '*')
				{
					skip_multiline_comment(&json);
				}
				else
				{
					json++;
				}
				break;

			case '\"':
				minify_string(&json, (t_utf8**)&into);
				break;

			default:
				into[0] = json[0];
				json++;
				into++;
		}
	}

	// and null-terminate.
	*into = '\0';
}
