/*============================================================================*\
||                                            ______________________________  ||
||  src/text/regex/split.c                   |    __    __  ___      _____  | ||
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



//! Frees the given (NULL-terminated) stringarray and all the strings within it
static
void	RX_Split_DeleteParts(t_utf8** parts)
{
	t_uint	i;

	if (parts == NULL)
		return;
	for (i = 0; parts[i]; ++i)
		Memory_Free(parts[i]);
	Memory_Free(parts);
}

//! Appends one part (a duplicate of `n` bytes of `str`) to the given growing stringarray
static
t_utf8**	RX_Split_AddPart(t_utf8** parts, t_uint* amount, t_utf8 const* str, t_size n)
{
	t_utf8**	tmp;

	if (n == 0)
		return (parts); // like String_Split(): empty parts are not included in the result
	tmp = (t_utf8**)Memory_Reallocate(parts, (*amount + 2) * sizeof(t_utf8*));
	if (tmp == NULL)
		return (NULL);
	parts = tmp;
	parts[*amount] = RX_StrNDup(str, n);
	if (parts[*amount] == NULL)
		return (NULL);
	*amount += 1;
	parts[*amount] = NULL;
	return (parts);
}

t_utf8**	Regex_Split(s_regex const* regex, t_utf8 const* str)
{
	t_utf8**		result;
	t_utf8**		tmp;
	s_regex_match	match;
	t_uint	amount;
	t_size	length;
	t_size	offset;
	t_size	part_start;
	t_size	charlen;

	if CCCERROR((regex == NULL), ERROR_NULLPOINTER, "regex given is NULL")
		return (NULL);
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to split given is NULL")
		return (NULL);
	length = StringUTF8_Length(str);
	result = (t_utf8**)Memory_New(1 * sizeof(t_utf8*));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	result[0] = NULL;
	amount = 0;
	offset = 0;
	part_start = 0;
	while (offset <= length)
	{
		if (!RX_Run(regex, str, length, offset, FALSE, FALSE, &match))
			break;
		if (match.length == 0)
		{	// zero-width match: not a useful delimiter, simply advance by one character
			RegexMatch_Delete(&match);
			if (offset >= length)
				break;
			RX_Decode(str, length, offset, &charlen);
			offset += (charlen == 0 ? 1 : charlen);
			continue;
		}
		{
			t_size	m_index = match.index;
			t_size	m_length = match.length;

			tmp = RX_Split_AddPart(result, &amount, str + part_start, m_index - part_start);
			RegexMatch_Delete(&match);
			if CCCERROR((tmp == NULL), ERROR_ALLOCFAILURE, NULL)
			{
				RX_Split_DeleteParts(result);
				return (NULL);
			}
			result = tmp;
			offset = m_index + m_length;
			part_start = offset;
		}
	}
	tmp = RX_Split_AddPart(result, &amount, str + part_start, length - part_start);
	if CCCERROR((tmp == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		RX_Split_DeleteParts(result);
		return (NULL);
	}
	return (tmp);
}
