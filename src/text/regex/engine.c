/*============================================================================*\
||                                            ______________________________  ||
||  src/text/regex/engine.c                  |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#include "libccc/memory.h"
#include "libccc/text/regex.h"
#include "libccc/text/char/unicode.h"

#include "regex_private.h"

#include LIBCONFIG_ERROR_INCLUDE



/*============================================================================*\
||                          UTF-8 decoding utilities                          ||
\*============================================================================*/

t_utf8*	RX_StrNDup(t_utf8 const* str, t_size n)
{
	t_utf8*	result;

	result = (t_utf8*)Memory_Allocate(n + 1);
	if (result == NULL)
		return (NULL);
	Memory_Copy(result, str, n);
	result[n] = '\0';
	return (result);
}

t_utf8*	RX_StrDup(t_utf8 const* str)
{
	t_size	length;

	length = 0;
	while (str[length])
		length += 1;
	return (RX_StrNDup(str, length));
}



t_utf32	RX_Decode(t_utf8 const* str, t_size length, t_size pos, t_size* dest_length)
{
	t_u8	b;
	t_utf32	c;
	t_size	seq;
	t_size	i;

	if (pos >= length)
	{
		*dest_length = 0;
		return (0);
	}
	b = (t_u8)str[pos];
	if (b < 0x80)
	{
		*dest_length = 1;
		return (b);
	}
	if ((b & 0xE0) == 0xC0)	{ seq = 2;	c = (b & 0x1F); }
	else if ((b & 0xF0) == 0xE0)	{ seq = 3;	c = (b & 0x0F); }
	else if ((b & 0xF8) == 0xF0)	{ seq = 4;	c = (b & 0x07); }
	else
	{	// invalid lead byte: decode it as a single raw byte
		*dest_length = 1;
		return (b);
	}
	if (pos + seq > length)
	{	// truncated sequence: decode the lead as a single raw byte
		*dest_length = 1;
		return (b);
	}
	for (i = 1; i < seq; ++i)
	{
		if (((t_u8)str[pos + i] & 0xC0) != 0x80)
		{	// invalid continuation byte: decode the lead as a single raw byte
			*dest_length = 1;
			return (b);
		}
		c = (c << 6) | ((t_u8)str[pos + i] & 0x3F);
	}
	*dest_length = seq;
	return (c);
}

t_utf32	RX_DecodePrev(t_utf8 const* str, t_size pos, t_size* dest_length)
{
	t_size	start;
	t_size	length;
	t_utf32	c;

	if (pos == 0)
	{
		*dest_length = 0;
		return (0);
	}
	start = pos - 1;
	while (start > 0 && ((t_u8)str[start] & 0xC0) == 0x80 && (pos - start) < 4)
		start -= 1;
	c = RX_Decode(str, pos, start, &length);
	if (start + length != pos)
	{	// the bytes before `pos` do not form a valid sequence ending at `pos`: decode a single raw byte
		*dest_length = 1;
		return ((t_u8)str[pos - 1]);
	}
	*dest_length = length;
	return (c);
}



/*============================================================================*\
||                       Character property utilities                         ||
\*============================================================================*/

t_bool	RX_IsWordChar(t_utf32 c)
{
	return (CharUTF32_IsAlphaNumeric(c) || c == '_');
}

//! Checks whether the given codepoint `c` has the single character property `prop`
static
t_bool	RX_HasProp1(t_utf32 c, t_u32 prop)
{
	switch (prop)
	{
		case RXPROP_ALPHA:	return (CharUTF32_IsLetter(c));
		case RXPROP_UPPER:	return (CharUTF32_IsUppercase(c));
		case RXPROP_LOWER:	return (CharUTF32_IsLowercase(c));
		case RXPROP_DIGIT:	return (CharUTF32_IsDigit_Decimal(c));
		case RXPROP_XDIGIT:	return (CharUTF32_IsDigit_Hexadecimal(c));
		case RXPROP_ALNUM:	return (CharUTF32_IsAlphaNumeric(c));
		case RXPROP_WORD:	return (RX_IsWordChar(c));
		case RXPROP_SPACE:	return (CharUTF32_IsWhiteSpace(c));
		case RXPROP_HSPACE:	return (c == ' ' || c == '\t' || c == 0xA0 || c == 0x1680 ||
			(c >= 0x2000 && c <= 0x200A) || c == 0x202F || c == 0x205F || c == 0x3000);
		case RXPROP_VSPACE:	return (c == '\n' || c == 0x0B || c == '\f' || c == '\r' ||
			c == 0x85 || c == 0x2028 || c == 0x2029);
		case RXPROP_PUNCT:	return (CharUTF32_IsPunctuation(c));
		case RXPROP_PRINT:	return (CharUTF32_IsPrintable(c));
		case RXPROP_GRAPH:	return (CharUTF32_IsPrintable(c) && c != ' ' && !CharUTF32_IsWhiteSpace(c));
		case RXPROP_CNTRL:	return (c < 0x20 || c == 0x7F);
		case RXPROP_BLANK:	return (c == ' ' || c == '\t');
		case RXPROP_ASCII:	return (c <= 0x7F);
		default:	return (FALSE);
	}
}

t_bool	RX_HasProps(t_utf32 c, t_u32 props)
{
	t_u32	bit;

	for (bit = 1; bit != 0 && bit <= props; bit <<= 1)
	{
		if ((props & bit) && RX_HasProp1(c, bit))
			return (TRUE);
	}
	return (FALSE);
}

//! Checks whether the given codepoint `c` LACKS any one of the properties in the `nprops` bitmask
static
t_bool	RX_LacksProps(t_utf32 c, t_u32 nprops)
{
	t_u32	bit;

	for (bit = 1; bit != 0 && bit <= nprops; bit <<= 1)
	{
		if ((nprops & bit) && !RX_HasProp1(c, bit))
			return (TRUE);
	}
	return (FALSE);
}

//! Checks whether the given codepoint `c` is described by the given class node's contents (before negation)
static
t_bool	RX_MatchClassInner(s_rxnode const* node, t_utf32 c)
{
	t_uint	i;

	for (i = 0; i < node->u.cclass.ranges_amount; ++i)
	{
		if (c >= node->u.cclass.ranges[i].min &&
			c <= node->u.cclass.ranges[i].max)
			return (TRUE);
	}
	if (node->u.cclass.props && RX_HasProps(c, node->u.cclass.props))
		return (TRUE);
	if (node->u.cclass.nprops && RX_LacksProps(c, node->u.cclass.nprops))
		return (TRUE);
	return (FALSE);
}

t_bool	RX_MatchClass(s_rxnode const* node, t_utf32 c)
{
	t_bool	matched;
	t_utf32	other;

	matched = RX_MatchClassInner(node, c);
	if (!matched && node->icase)
	{
		other = CharUTF32_ToLowercase(c);
		if (other != c)
			matched = RX_MatchClassInner(node, other);
		if (!matched)
		{
			other = CharUTF32_ToUppercase(c);
			if (other != c)
				matched = RX_MatchClassInner(node, other);
		}
	}
	if (node->u.cclass.negate)
		return (!matched);
	return (matched);
}



/*============================================================================*\
||                       The backtracking match routine                       ||
\*============================================================================*/

//! The state of one match attempt
typedef struct rxmatcher
{
	t_utf8 const*		str;	//!< the string being matched against
	t_size				len;	//!< the length (in bytes) of `str`
	t_size				start;	//!< the position at which the current match attempt started (for `\G`)
	t_uint				groups;	//!< the amount of capture groups in the pattern
	s_regex_capture*	caps;	//!< the current capture group regions (array of `groups + 1` items)
	t_size				steps;	//!< the total amount of matcher "steps" taken so far (guards against catastrophic backtracking)
	t_uint				depth;	//!< the current recursion depth (guards against C stack overflow)
	t_bool				aborted;//!< set to `TRUE` if a resource limit was exceeded (aborts the whole match attempt)
}	s_rxmatcher;

//! The different kinds of matcher continuation frames
typedef enum rxcont_kind
{
	RXCONT_DONE,		//!< the bottom-most sentinel: the whole pattern has matched (records the end position)
	RXCONT_CHAIN,		//!< resume matching a chain of nodes
	RXCONT_REPEAT,		//!< resume the logic of a repeat node (after one repetition of its child has matched)
	RXCONT_GROUPCLOSE,	//!< record the captured region of a capture group (restoring it if further matching fails)
}	e_rxcont_kind;

//! A matcher continuation frame (these live on the C call stack, linked from innermost to outermost)
typedef struct rxcont
{
	e_rxcont_kind			kind;
	struct rxcont const*	prev;	//!< the enclosing (outer) continuation frame
	union
	{
		struct	//!< for `RXCONT_DONE`
		{
			t_size*	dest_end;		//!< the variable in which to record the end position of the match
			t_size	require_end;	//!< if `has_require`, the exact position at which the match must end
			t_bool	has_require;	//!< if `TRUE`, the match only succeeds if it ends exactly at `require_end`
		}	done;
		struct	//!< for `RXCONT_CHAIN`
		{
			s_rxnode const*	node;	//!< the node chain to resume matching
		}	chain;
		struct	//!< for `RXCONT_REPEAT`
		{
			s_rxnode const*	rep;	//!< the repeat node whose logic should be resumed
			t_u32			count;	//!< the amount of repetitions matched so far
			t_size			lastpos;//!< the position at which the previous repetition started (for the empty-loop guard)
		}	repeat;
		struct	//!< for `RXCONT_GROUPCLOSE`
		{
			t_uint	index;	//!< the index of the capture group being closed
			t_size	start;	//!< the position at which the capture group's region started
		}	gclose;
	}	u;
}	s_rxcont;



static t_bool	RX_MatchNode(s_rxmatcher* m, s_rxnode const* node, t_size pos, s_rxcont const* k);
static t_bool	RX_MatchRepeat(s_rxmatcher* m, s_rxnode const* rep, t_u32 count, t_size pos, t_size lastpos, s_rxcont const* k);



//! Attempts to match a single-character node (`RXNODE_LITERAL`/`ANY`/`CLASS`/`LINEBREAK`) at `pos`, advancing `*dest_pos` past it
static
t_bool	RX_MatchOne(s_rxmatcher* m, s_rxnode const* node, t_size pos, t_size* dest_pos)
{
	t_utf32	c;
	t_size	length;

	if (pos >= m->len)
		return (FALSE);
	c = RX_Decode(m->str, m->len, pos, &length);
	switch (node->kind)
	{
		case RXNODE_LITERAL:
		{
			if (c != node->u.literal.c)
			{
				if (!node->icase)
					return (FALSE);
				if (CharUTF32_ToLowercase(c) != CharUTF32_ToLowercase(node->u.literal.c))
					return (FALSE);
			}
			break;
		}
		case RXNODE_ANY:
		{
			if (!node->u.any.dotall && c == '\n')
				return (FALSE);
			break;
		}
		case RXNODE_CLASS:
		{
			if (!RX_MatchClass(node, c))
				return (FALSE);
			break;
		}
		case RXNODE_LINEBREAK:
		{
			if (c == '\r')
			{	// `\r\n` counts as a single line-break sequence
				if (pos + 1 < m->len && m->str[pos + 1] == '\n')
					length = 2;
				break;
			}
			if (!(c == '\n' || c == 0x0B || c == '\f' || c == 0x85 || c == 0x2028 || c == 0x2029))
				return (FALSE);
			break;
		}
		default:	return (FALSE);
	}
	*dest_pos = pos + length;
	return (TRUE);
}

//! Checks whether the zero-width assertion of the given anchor node holds at `pos`
static
t_bool	RX_MatchAnchor(s_rxmatcher* m, s_rxnode const* node, t_size pos)
{
	t_bool	word_prev;
	t_bool	word_next;
	t_size	length;

	switch (node->u.anchor.kind)
	{
		case RXANCHOR_STR_START:	return (pos == 0);
		case RXANCHOR_STR_END:		return (pos == m->len);
		case RXANCHOR_STR_END_NL:	return (pos == m->len || (m->str[pos] == '\n' && pos + 1 == m->len));
		case RXANCHOR_LINE_START:	return (pos == 0 || m->str[pos - 1] == '\n');
		case RXANCHOR_LINE_END:		return (pos == m->len || m->str[pos] == '\n');
		case RXANCHOR_MATCH_START:	return (pos == m->start);
		case RXANCHOR_WORD_BOUND:
		case RXANCHOR_NOTWORD_BOUND:
		{
			word_prev = (pos > 0      && RX_IsWordChar(RX_DecodePrev(m->str, pos, &length)));
			word_next = (pos < m->len && RX_IsWordChar(RX_Decode(m->str, m->len, pos, &length)));
			if (node->u.anchor.kind == RXANCHOR_WORD_BOUND)
				return (word_prev != word_next);
			return (word_prev == word_next);
		}
	}
	return (FALSE);
}



//! Duplicates the current capture group state (for negative look-arounds)
static
s_regex_capture*	RX_SaveCaps(s_rxmatcher* m)
{
	s_regex_capture*	result;

	result = (s_regex_capture*)Memory_Duplicate(m->caps, (m->groups + 1) * sizeof(s_regex_capture));
	if (result == NULL)
		m->aborted = TRUE;
	return (result);
}

//! Restores a previously saved capture group state
static
void	RX_RestoreCaps(s_rxmatcher* m, s_regex_capture const* saved)
{
	Memory_Copy(m->caps, saved, (m->groups + 1) * sizeof(s_regex_capture));
}

//! Runs an independent sub-match of the given `chain` starting at `pos` (used for look-arounds/atomic groups)
static
t_bool	RX_SubRun(s_rxmatcher* m, s_rxnode const* chain, t_size pos, t_size require_end, t_bool has_require, t_size* dest_end)
{
	s_rxcont	done;

	done.kind = RXCONT_DONE;
	done.prev = NULL;
	done.u.done.dest_end = dest_end;
	done.u.done.require_end = require_end;
	done.u.done.has_require = has_require;
	return (RX_MatchNode(m, chain, pos, &done));
}



//! The inner match routine (see RX_MatchNode() below, which wraps this with a recursion depth guard)
static
t_bool	RX_MatchNode_(s_rxmatcher* m, s_rxnode const* node, t_size pos, s_rxcont const* k)
{
	while (TRUE)
	{
		if (++m->steps > RX_LIMIT_STEPS)
		{
			m->aborted = TRUE;
			return (FALSE);
		}
		if (node == NULL)
		{	// the end of the current node chain was reached: pop the innermost continuation frame
			if (k == NULL)
				return (TRUE);
			switch (k->kind)
			{
				case RXCONT_DONE:
				{
					if (k->u.done.has_require && pos != k->u.done.require_end)
						return (FALSE);
					if (k->u.done.dest_end)
						*(k->u.done.dest_end) = pos;
					return (TRUE);
				}
				case RXCONT_CHAIN:
				{
					node = k->u.chain.node;
					k = k->prev;
					continue;
				}
				case RXCONT_REPEAT:
				{
					return (RX_MatchRepeat(m,
						k->u.repeat.rep,
						k->u.repeat.count,
						pos,
						k->u.repeat.lastpos,
						k->prev));
				}
				case RXCONT_GROUPCLOSE:
				{
					s_regex_capture	old;
					t_uint	index = k->u.gclose.index;
					t_bool	result;

					old = m->caps[index];
					m->caps[index].index = k->u.gclose.start;
					m->caps[index].length = pos - k->u.gclose.start;
					result = RX_MatchNode(m, NULL, pos, k->prev);
					if (!result)
						m->caps[index] = old;
					return (result);
				}
			}
			return (FALSE);
		}
		switch (node->kind)
		{
			case RXNODE_LITERAL:
			case RXNODE_ANY:
			case RXNODE_CLASS:
			case RXNODE_LINEBREAK:
			{
				if (!RX_MatchOne(m, node, pos, &pos))
					return (FALSE);
				node = node->next;
				continue;
			}
			case RXNODE_ANCHOR:
			{
				if (!RX_MatchAnchor(m, node, pos))
					return (FALSE);
				node = node->next;
				continue;
			}
			case RXNODE_GROUP:
			{
				if (node->u.group.atomic)
				{	// atomic group: find the first sub-match, then never backtrack into it
					t_size	end;

					if (!RX_SubRun(m, node->u.group.child, pos, 0, FALSE, &end))
						return (FALSE);
					pos = end;
					node = node->next;
					continue;
				}
				{
					s_rxcont	kchain;
					s_rxcont	kclose;

					kchain.kind = RXCONT_CHAIN;
					kchain.prev = k;
					kchain.u.chain.node = node->next;
					if (node->u.group.capture == 0)
						return (RX_MatchNode(m, node->u.group.child, pos, &kchain));
					kclose.kind = RXCONT_GROUPCLOSE;
					kclose.prev = &kchain;
					kclose.u.gclose.index = node->u.group.capture;
					kclose.u.gclose.start = pos;
					return (RX_MatchNode(m, node->u.group.child, pos, &kclose));
				}
			}
			case RXNODE_LOOK:
			{
				s_regex_capture*	saved = NULL;
				t_bool	ok;
				t_size	end;

				if (node->u.look.negative)
				{
					saved = RX_SaveCaps(m);
					if (saved == NULL)
						return (FALSE);
				}
				if (!node->u.look.behind)
				{	// lookahead
					ok = RX_SubRun(m, node->u.look.child, pos, 0, FALSE, &end);
				}
				else
				{	// lookbehind: try candidate start positions, requiring the sub-match to end exactly at `pos`
					t_size	min_bytes;
					t_size	max_bytes;
					t_size	q;

					ok = FALSE;
					min_bytes = node->u.look.width_min;
					if (node->u.look.width_max == RX_INFINITY ||
						(t_size)node->u.look.width_max > pos / 4)
						max_bytes = pos;
					else
						max_bytes = (t_size)node->u.look.width_max * 4;
					if (node->u.look.width_min != RX_INFINITY && min_bytes <= pos)
					{
						q = pos - min_bytes;
						while (TRUE)
						{
							if (q == 0 || ((t_u8)m->str[q] & 0xC0) != 0x80)
							{	// only try positions which lie on a character boundary
								if (RX_SubRun(m, node->u.look.child, q, pos, TRUE, &end))
								{
									ok = TRUE;
									break;
								}
								if (m->aborted)
								{
									if (saved)
										Memory_Free(saved);
									return (FALSE);
								}
							}
							if (q == 0 || pos - q >= max_bytes)
								break;
							q -= 1;
						}
					}
				}
				if (m->aborted)
				{
					if (saved)
						Memory_Free(saved);
					return (FALSE);
				}
				if (node->u.look.negative)
				{
					if (ok)
						RX_RestoreCaps(m, saved);
					Memory_Free(saved);
					if (ok)
						return (FALSE);
				}
				else if (!ok)
					return (FALSE);
				node = node->next;
				continue;
			}
			case RXNODE_BACKREF:
			{
				s_regex_capture	cap;

				if (node->u.backref.index > m->groups)
					return (FALSE);
				cap = m->caps[node->u.backref.index];
				if (cap.index == REGEX_NOMATCH)
					return (FALSE);
				if (!node->icase)
				{
					t_size	i;

					if (pos + cap.length > m->len)
						return (FALSE);
					for (i = 0; i < cap.length; ++i)
					{
						if (m->str[pos + i] != m->str[cap.index + i])
							return (FALSE);
					}
					pos += cap.length;
				}
				else
				{	// case-insensitive backreference: compare character by character
					t_size	q = cap.index;
					t_size	q_end = cap.index + cap.length;
					t_utf32	c1;
					t_utf32	c2;
					t_size	l1;
					t_size	l2;

					while (q < q_end)
					{
						if (pos >= m->len)
							return (FALSE);
						c1 = RX_Decode(m->str, q_end, q, &l1);
						c2 = RX_Decode(m->str, m->len, pos, &l2);
						if (c1 != c2 &&
							CharUTF32_ToLowercase(c1) != CharUTF32_ToLowercase(c2))
							return (FALSE);
						q += l1;
						pos += l2;
					}
				}
				node = node->next;
				continue;
			}
			case RXNODE_ALT:
			{
				s_rxcont	kchain;
				t_uint		i;

				kchain.kind = RXCONT_CHAIN;
				kchain.prev = k;
				kchain.u.chain.node = node->next;
				for (i = 0; i < node->u.alt.amount; ++i)
				{
					if (RX_MatchNode(m, node->u.alt.branches[i], pos, &kchain))
						return (TRUE);
					if (m->aborted)
						return (FALSE);
				}
				return (FALSE);
			}
			case RXNODE_REPEAT:
			{
				return (RX_MatchRepeat(m, node, 0, pos, (t_size)-1, k));
			}
		}
		return (FALSE);
	}
}

static
t_bool	RX_MatchNode(s_rxmatcher* m, s_rxnode const* node, t_size pos, s_rxcont const* k)
{
	t_bool	result;

	if (m->aborted)
		return (FALSE);
	if (m->depth >= RX_LIMIT_DEPTH)
	{
		m->aborted = TRUE;
		return (FALSE);
	}
	m->depth += 1;
	result = RX_MatchNode_(m, node, pos, k);
	m->depth -= 1;
	return (result);
}



//! Checks whether the given repeat node's child is a single one-character node (enabling the fast iterative repeat path)
static
t_bool	RX_IsSimpleRepeat(s_rxnode const* rep)
{
	s_rxnode const*	child;

	child = rep->u.repeat.child;
	if (child == NULL || child->next != NULL)
		return (FALSE);
	return (child->kind == RXNODE_LITERAL
		||  child->kind == RXNODE_ANY
		||  child->kind == RXNODE_CLASS);
}

//! The fast iterative repeat path: for repeats of a single one-character node, avoids recursing once per repetition
static
t_bool	RX_MatchRepeatSimple(s_rxmatcher* m, s_rxnode const* rep, t_size pos, s_rxcont const* k)
{
	s_rxnode const*	child = rep->u.repeat.child;
	t_u32	min = rep->u.repeat.min;
	t_u32	max = rep->u.repeat.max;
	t_u32	count;
	t_size	length;

	if (!rep->u.repeat.lazy)
	{	// greedy: consume as many repetitions as possible, then give them back one at a time
		count = 0;
		while (count < max && RX_MatchOne(m, child, pos, &pos))
			count += 1;
		if (count < min)
			return (FALSE);
		while (TRUE)
		{
			if (RX_MatchNode(m, rep->next, pos, k))
				return (TRUE);
			if (m->aborted || count == min)
				return (FALSE);
			RX_DecodePrev(m->str, pos, &length);
			if (length == 0)
				return (FALSE);
			pos -= length;
			count -= 1;
		}
	}
	else
	{	// lazy: consume as few repetitions as possible, adding one at a time
		count = 0;
		while (count < min)
		{
			if (!RX_MatchOne(m, child, pos, &pos))
				return (FALSE);
			count += 1;
		}
		while (TRUE)
		{
			if (RX_MatchNode(m, rep->next, pos, k))
				return (TRUE);
			if (m->aborted || count >= max)
				return (FALSE);
			if (!RX_MatchOne(m, child, pos, &pos))
				return (FALSE);
			count += 1;
		}
	}
}

static
t_bool	RX_MatchRepeat(s_rxmatcher* m, s_rxnode const* rep, t_u32 count, t_size pos, t_size lastpos, s_rxcont const* k)
{
	t_u32	min = rep->u.repeat.min;
	t_u32	max = rep->u.repeat.max;

	if (m->aborted)
		return (FALSE);
	if (rep->u.repeat.possessive)
	{	// possessive: match each repetition atomically, and never backtrack
		t_size	end;

		while (count < max)
		{
			if (!RX_SubRun(m, rep->u.repeat.child, pos, 0, FALSE, &end))
				break;
			if (m->aborted)
				return (FALSE);
			if (end == pos)
				break; // the repetition matched nothing: stop, to avoid an infinite loop
			pos = end;
			count += 1;
		}
		if (m->aborted || count < min)
			return (FALSE);
		return (RX_MatchNode(m, rep->next, pos, k));
	}
	if (count == 0 && RX_IsSimpleRepeat(rep))
		return (RX_MatchRepeatSimple(m, rep, pos, k));
	if (!rep->u.repeat.lazy)
	{	// greedy: try one more repetition first, then try to continue past the repeat
		if (count < max && !(count > 0 && pos == lastpos))
		{
			s_rxcont	krep;

			krep.kind = RXCONT_REPEAT;
			krep.prev = k;
			krep.u.repeat.rep = rep;
			krep.u.repeat.count = count + 1;
			krep.u.repeat.lastpos = pos;
			if (RX_MatchNode(m, rep->u.repeat.child, pos, &krep))
				return (TRUE);
			if (m->aborted)
				return (FALSE);
		}
		if (count >= min)
			return (RX_MatchNode(m, rep->next, pos, k));
		return (FALSE);
	}
	else
	{	// lazy: try to continue past the repeat first, then try one more repetition
		if (count >= min)
		{
			if (RX_MatchNode(m, rep->next, pos, k))
				return (TRUE);
			if (m->aborted)
				return (FALSE);
		}
		if (count < max && !(count > 0 && pos == lastpos))
		{
			s_rxcont	krep;

			krep.kind = RXCONT_REPEAT;
			krep.prev = k;
			krep.u.repeat.rep = rep;
			krep.u.repeat.count = count + 1;
			krep.u.repeat.lastpos = pos;
			return (RX_MatchNode(m, rep->u.repeat.child, pos, &krep));
		}
		return (FALSE);
	}
}



t_bool	RX_Run(s_regex const* regex, t_utf8 const* str, t_size len, t_size offset, t_bool anchored, t_bool entire, s_regex_match* dest_match)
{
	s_rxcompiled const*	compiled;
	s_rxmatcher			m;
	t_size	start;
	t_size	end;
	t_size	length;
	t_uint	i;

	compiled = (s_rxcompiled const*)regex->compiled;
	if (compiled == NULL || offset > len)
		return (FALSE);
	m.str = str;
	m.len = len;
	m.groups = regex->groups;
	m.steps = 0;
	m.depth = 0;
	m.aborted = FALSE;
	m.caps = (s_regex_capture*)Memory_New((m.groups + 1) * sizeof(s_regex_capture));
	if CCCERROR((m.caps == NULL), ERROR_ALLOCFAILURE, NULL)
		return (FALSE);
	start = offset;
	while (TRUE)
	{
		for (i = 0; i <= m.groups; ++i)
		{
			m.caps[i].index = REGEX_NOMATCH;
			m.caps[i].length = 0;
		}
		m.start = start;
		end = start;
		{
			s_rxcont	done;

			done.kind = RXCONT_DONE;
			done.prev = NULL;
			done.u.done.dest_end = &end;
			done.u.done.require_end = len;
			done.u.done.has_require = entire;
			if (RX_MatchNode(&m, compiled->root, start, &done))
			{
				m.caps[0].index = start;
				m.caps[0].length = end - start;
				if (dest_match)
				{
					dest_match->index = start;
					dest_match->length = end - start;
					dest_match->captures_amount = m.groups + 1;
					dest_match->captures = m.caps;
				}
				else
					Memory_Free(m.caps);
				return (TRUE);
			}
		}
		if (m.aborted || anchored || start >= len)
			break;
		RX_Decode(str, len, start, &length);
		start += (length == 0 ? 1 : length);
	}
	Memory_Free(m.caps);
	return (FALSE);
}
