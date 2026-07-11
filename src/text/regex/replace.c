/*============================================================================*\
||                                            ______________________________  ||
||  src/text/regex/replace.c                 |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#include "libccc/memory.h"
#include "libccc/text/regex.h"
#include "libccc/text/string/utf8.h"

#include "regex_private.h"

#include LIBCONFIG_ERROR_INCLUDE



//! A simple growing string buffer, used to construct the replacement result
typedef struct rxbuffer
{
	t_utf8*	data;
	t_size	length;
	t_size	capacity;
}	s_rxbuffer;

static
t_bool	RX_Buffer_Append(s_rxbuffer* buffer, t_utf8 const* str, t_size n)
{
	t_utf8*	tmp;
	t_size	capacity;

	if (n == 0)
		return (TRUE);
	if (buffer->length + n + 1 > buffer->capacity)
	{
		capacity = (buffer->capacity == 0 ? 64 : buffer->capacity);
		while (buffer->length + n + 1 > capacity)
			capacity *= 2;
		tmp = (t_utf8*)Memory_Reallocate(buffer->data, capacity);
		if (tmp == NULL)
			return (FALSE);
		buffer->data = tmp;
		buffer->capacity = capacity;
	}
	Memory_Copy(buffer->data + buffer->length, str, n);
	buffer->length += n;
	buffer->data[buffer->length] = '\0';
	return (TRUE);
}

//! Appends the region captured by group `index` of the given `match` (does nothing if that group did not match)
static
t_bool	RX_Buffer_AppendCapture(s_rxbuffer* buffer, s_regex_match const* match, t_utf8 const* str, t_uint index)
{
	s_regex_capture	capture;

	if (index >= match->captures_amount)
		return (TRUE); // a reference to a non-existent group is substituted with nothing
	capture = match->captures[index];
	if (capture.index == REGEX_NOMATCH)
		return (TRUE); // a group which did not participate in the match is substituted with nothing
	return (RX_Buffer_Append(buffer, str + capture.index, capture.length));
}

//! Appends the given `replacement` string, expanding any `$N`/`\N`/`${name}`/`$<name>`/`$$` substitution sequences
static
t_bool	RX_Buffer_AppendReplacement(s_rxbuffer* buffer, s_regex const* regex, s_regex_match const* match, t_utf8 const* str, t_utf8 const* replacement)
{
	t_size	i;
	t_size	start;
	t_uint	index;
	t_utf8	c;
	t_utf8	terminator;
	t_sint	named;

	i = 0;
	while (replacement[i])
	{
		c = replacement[i];
		if (c != '$' && c != '\\')
		{
			if (!RX_Buffer_Append(buffer, replacement + i, 1))
				return (FALSE);
			i += 1;
			continue;
		}
		i += 1;
		if (replacement[i] == '\0')
			return (RX_Buffer_Append(buffer, &c, 1)); // a trailing `$` or `\` is appended literally
		if (replacement[i] == c)
		{	// `$$` gives a literal `$`, and `\\` gives a literal `\`
			if (!RX_Buffer_Append(buffer, &c, 1))
				return (FALSE);
			i += 1;
			continue;
		}
		if (replacement[i] >= '0' && replacement[i] <= '9')
		{	// `$N` or `\N` numbered group substitution
			index = (replacement[i] - '0');
			i += 1;
			if (replacement[i] >= '0' && replacement[i] <= '9' &&
				(index * 10 + (replacement[i] - '0')) < match->captures_amount)
			{
				index = index * 10 + (replacement[i] - '0');
				i += 1;
			}
			if (!RX_Buffer_AppendCapture(buffer, match, str, index))
				return (FALSE);
			continue;
		}
		if (c == '$' && (replacement[i] == '{' || replacement[i] == '<'))
		{	// `${name}` or `$<name>` named group substitution
			terminator = (replacement[i] == '{' ? '}' : '>');
			i += 1;
			start = i;
			while (replacement[i] && replacement[i] != terminator)
				i += 1;
			if (replacement[i] == terminator && i > start)
			{
				t_utf8*	name = RX_StrNDup(replacement + start, i - start);
				if (name == NULL)
					return (FALSE);
				named = Regex_GetGroupIndex(regex, name);
				Memory_Free(name);
				i += 1;
				if (named > 0 && !RX_Buffer_AppendCapture(buffer, match, str, (t_uint)named))
					return (FALSE);
				continue;
			}
			// malformed `${...` sequence: append it literally
			i = start - 2;
			if (!RX_Buffer_Append(buffer, replacement + i, 2))
				return (FALSE);
			i += 2;
			continue;
		}
		// any other `$x` or `\x` sequence is appended literally (both characters)
		if (!RX_Buffer_Append(buffer, &c, 1))
			return (FALSE);
	}
	return (TRUE);
}



static
t_utf8*	RX_Replace(s_regex const* regex, t_utf8 const* str, t_utf8 const* replacement, t_bool all)
{
	s_rxbuffer		buffer = {0};
	s_regex_match	match;
	t_size	length;
	t_size	offset;
	t_size	charlen;
	t_bool	ok;

	length = StringUTF8_Length(str);
	offset = 0;
	while (offset <= length)
	{
		if (!RX_Run(regex, str, length, offset, FALSE, FALSE, &match))
			break;
		ok = RX_Buffer_Append(&buffer, str + offset, match.index - offset);
		ok = ok && RX_Buffer_AppendReplacement(&buffer, regex, &match, str, replacement);
		if (match.length == 0)
		{	// zero-width match: also append the following character, and advance past it
			if (match.index < length)
			{
				RX_Decode(str, length, match.index, &charlen);
				if (charlen == 0)
					charlen = 1;
				ok = ok && RX_Buffer_Append(&buffer, str + match.index, charlen);
				offset = match.index + charlen;
			}
			else
				offset = length + 1;
		}
		else
			offset = match.index + match.length;
		RegexMatch_Delete(&match);
		if CCCERROR((!ok), ERROR_ALLOCFAILURE, NULL)
		{
			if (buffer.data)
				Memory_Free(buffer.data);
			return (NULL);
		}
		if (!all)
			break;
	}
	if (offset <= length)
	{
		if CCCERROR((!RX_Buffer_Append(&buffer, str + offset, length - offset)), ERROR_ALLOCFAILURE, NULL)
		{
			if (buffer.data)
				Memory_Free(buffer.data);
			return (NULL);
		}
	}
	if (buffer.data == NULL)
		return (RX_StrDup(""));
	return (buffer.data);
}

t_utf8*	Regex_Replace(s_regex const* regex, t_utf8 const* str, t_utf8 const* replacement)
{
	if CCCERROR((regex == NULL), ERROR_NULLPOINTER, "regex given is NULL")
		return (NULL);
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if CCCERROR((replacement == NULL), ERROR_NULLPOINTER, "replacement string given is NULL")
		return (NULL);
	return (RX_Replace(regex, str, replacement, FALSE));
}

t_utf8*	Regex_ReplaceAll(s_regex const* regex, t_utf8 const* str, t_utf8 const* replacement)
{
	if CCCERROR((regex == NULL), ERROR_NULLPOINTER, "regex given is NULL")
		return (NULL);
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if CCCERROR((replacement == NULL), ERROR_NULLPOINTER, "replacement string given is NULL")
		return (NULL);
	return (RX_Replace(regex, str, replacement, TRUE));
}
