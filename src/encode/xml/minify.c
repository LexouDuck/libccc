
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/encode/xml.h"

#include LIBCONFIG_ERROR_INCLUDE



#define XML_ISWHITESPACE(C) \
	((C) == ' ' || (C) == '\t' || (C) == '\r' || (C) == '\n')



//! Skips over an XML comment (`<!-- ... -->`), copying nothing to the output
static
void	skip_comment(t_utf8** input)
{
	*input += STRING_LENGTH("<!--");
	for (; (*input)[0] != '\0'; ++(*input))
	{
		if ((*input)[0] == '-' &&
			(*input)[1] == '-' &&
			(*input)[2] == '>')
		{
			*input += STRING_LENGTH("-->");
			return;
		}
	}
}

//! Copies a `<![CDATA[ ... ]]>` section verbatim to the output
static
void	minify_cdata(t_utf8** input, t_utf8** output)
{
	for (t_size i = 0; i < STRING_LENGTH("<![CDATA["); ++i)
	{
		(*output)[0] = (*input)[0];
		++(*input), ++(*output);
	}
	for (; (*input)[0] != '\0'; (void)++(*input), ++(*output))
	{
		(*output)[0] = (*input)[0];
		if ((*input)[0] == ']' &&
			(*input)[1] == ']' &&
			(*input)[2] == '>')
		{
			(*output)[1] = (*input)[1];
			(*output)[2] = (*input)[2];
			*input += STRING_LENGTH("]]>");
			*output += STRING_LENGTH("]]>");
			return;
		}
	}
}

//! Copies a tag (`< ... >`) verbatim to the output (quoted attribute values may contain '>' chars)
static
void	minify_tag(t_utf8** input, t_utf8** output)
{
	t_utf8	quote = '\0';

	for (; (*input)[0] != '\0'; (void)++(*input), ++(*output))
	{
		(*output)[0] = (*input)[0];
		if (quote != '\0')
		{
			if ((*input)[0] == quote)
				quote = '\0';
			continue;
		}
		if ((*input)[0] == '"' || (*input)[0] == '\'')
		{
			quote = (*input)[0];
			continue;
		}
		if ((*input)[0] == '>')
		{
			++(*input), ++(*output);
			return;
		}
	}
}



void	XML_Minify(t_utf8* xml)
{
	t_utf8*	into = xml;
	t_utf8*	text;

	if CCCERROR((xml == NULL), ERROR_NULLPOINTER, NULL)
		return;
	while (xml[0] != '\0')
	{
		if (xml[0] == '<')
		{
			if (String_Equals_N(xml, "<!--", STRING_LENGTH("<!--")))
			{	// comments are removed entirely
				skip_comment(&xml);
				continue;
			}
			if (String_Equals_N(xml, "<![CDATA[", STRING_LENGTH("<![CDATA[")))
			{	// CDATA sections are preserved verbatim
				minify_cdata(&xml, &into);
				continue;
			}
			// any other tag/markup is preserved verbatim
			minify_tag(&xml, &into);
			continue;
		}
		// text content: only remove it if it is composed of whitespace chars entirely
		text = xml;
		while (text[0] != '\0' && text[0] != '<' && XML_ISWHITESPACE(text[0]))
			++text;
		if (text[0] == '\0' || text[0] == '<')
		{	// whitespace-only text: skip it (copy nothing)
			xml = text;
			continue;
		}
		// significant text: copy it verbatim, until the next tag
		while (xml[0] != '\0' && xml[0] != '<')
		{
			into[0] = xml[0];
			++xml, ++into;
		}
	}
	into[0] = '\0';
}
