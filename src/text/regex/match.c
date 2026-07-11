/*============================================================================*\
||                                            ______________________________  ||
||  src/text/regex/match.c                   |    __    __  ___      _____  | ||
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
#include "libccc/text/format.h"

#include "regex_private.h"

#include LIBCONFIG_ERROR_INCLUDE



t_bool	Regex_Match(s_regex const* regex, t_utf8 const* str, t_size offset, s_regex_match* dest_match)
{
	t_size	length;

	if CCCERROR((regex == NULL), ERROR_NULLPOINTER, "regex given is NULL")
		return (FALSE);
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to match given is NULL")
		return (FALSE);
	length = StringUTF8_Length(str);
	if CCCERROR((offset > length), ERROR_INDEX2LARGE,
		"offset given (" SF_SIZE ") is beyond the end of the string (length: " SF_SIZE ")", offset, length)
		return (FALSE);
	return (RX_Run(regex, str, length, offset, TRUE, FALSE, dest_match));
}

t_bool	Regex_Search(s_regex const* regex, t_utf8 const* str, t_size offset, s_regex_match* dest_match)
{
	t_size	length;
	t_bool	anchored;

	if CCCERROR((regex == NULL), ERROR_NULLPOINTER, "regex given is NULL")
		return (FALSE);
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to search given is NULL")
		return (FALSE);
	length = StringUTF8_Length(str);
	if CCCERROR((offset > length), ERROR_INDEX2LARGE,
		"offset given (" SF_SIZE ") is beyond the end of the string (length: " SF_SIZE ")", offset, length)
		return (FALSE);
	anchored = ((regex->options & REGEX_OPTION_ANCHORED) != 0);
	return (RX_Run(regex, str, length, offset, anchored, FALSE, dest_match));
}

t_bool	Regex_Matches(s_regex const* regex, t_utf8 const* str)
{
	return (Regex_Search(regex, str, 0, NULL));
}

t_bool	Regex_MatchEntire(s_regex const* regex, t_utf8 const* str)
{
	t_size	length;

	if CCCERROR((regex == NULL), ERROR_NULLPOINTER, "regex given is NULL")
		return (FALSE);
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to match given is NULL")
		return (FALSE);
	length = StringUTF8_Length(str);
	return (RX_Run(regex, str, length, 0, TRUE, TRUE, NULL));
}

s_regex_match*	Regex_SearchAll(s_regex const* regex, t_utf8 const* str, t_uint* dest_amount)
{
	s_regex_match*	result;
	s_regex_match*	tmp;
	s_regex_match	match;
	t_uint	amount;
	t_size	length;
	t_size	offset;
	t_size	charlen;

	if (dest_amount)
		*dest_amount = 0;
	if CCCERROR((regex == NULL), ERROR_NULLPOINTER, "regex given is NULL")
		return (NULL);
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to search given is NULL")
		return (NULL);
	length = StringUTF8_Length(str);
	result = NULL;
	amount = 0;
	offset = 0;
	while (offset <= length)
	{
		if (!RX_Run(regex, str, length, offset, FALSE, FALSE, &match))
			break;
		tmp = (s_regex_match*)Memory_Reallocate(result, (amount + 1) * sizeof(s_regex_match));
		if CCCERROR((tmp == NULL), ERROR_ALLOCFAILURE, NULL)
		{
			RegexMatch_Delete(&match);
			while (amount--)
				RegexMatch_Delete(&result[amount]);
			Memory_Free(result);
			return (NULL);
		}
		result = tmp;
		result[amount] = match;
		amount += 1;
		if (match.length == 0)
		{	// zero-width match: advance by one character, to avoid an infinite loop
			if (match.index >= length)
				break;
			RX_Decode(str, length, match.index, &charlen);
			offset = match.index + (charlen == 0 ? 1 : charlen);
		}
		else
			offset = match.index + match.length;
	}
	if (dest_amount)
		*dest_amount = amount;
	return (result);
}

void	RegexMatch_Delete(s_regex_match* match)
{
	if CCCERROR((match == NULL), ERROR_NULLPOINTER, "match given is NULL")
		return;
	if (match->captures)
		Memory_Free(match->captures);
	match->captures = NULL;
	match->captures_amount = 0;
	match->index = 0;
	match->length = 0;
}

t_utf8*	RegexMatch_GetCapture(s_regex_match const* match, t_uint index, t_utf8 const* str)
{
	s_regex_capture	capture;

	if CCCERROR((match == NULL), ERROR_NULLPOINTER, "match given is NULL")
		return (NULL);
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if CCCERROR((index >= match->captures_amount), ERROR_INDEX2LARGE,
		"capture group index given (%u) is too large (the match only has %u groups)",
		index, match->captures_amount)
		return (NULL);
	capture = match->captures[index];
	if (capture.index == REGEX_NOMATCH)
		return (NULL);
	return (RX_StrNDup(str + capture.index, capture.length));
}
