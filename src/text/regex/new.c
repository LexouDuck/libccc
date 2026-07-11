/*============================================================================*\
||                                            ______________________________  ||
||  src/text/regex/new.c                     |    __    __  ___      _____  | ||
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
#include "libccc/text/string/utf8.h"
#include "libccc/text/format.h"

#include "regex_private.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	The recursive-descent parser state
*/
typedef struct rxparser
{
	t_utf8 const*	pat;	//!< the pattern string being parsed
	t_size			len;	//!< the length (in bytes) of the pattern string
	t_size			pos;	//!< the current parsing position (in bytes)
	t_regex_options	flags;	//!< the currently active option flags (global options + inline `(?imsxU)` flags)
	t_uint			groups;	//!< the amount of capture groups parsed so far
	t_utf8**		names;	//!< the array of group names parsed so far (`NULL` items for unnamed groups)
	s_rxnode*		allocs;	//!< the head of the linked-list of every allocated node
	char const*		errmsg;	//!< the error message, if a syntax error was found (`NULL` otherwise)
	t_size			errpos;	//!< the position (in bytes) at which the syntax error was found
}	s_rxparser;



static s_rxnode*	RX_Parse_Alternation(s_rxparser* p);



static
void	RX_Parse_Error(s_rxparser* p, char const* message)
{
	if (p->errmsg == NULL)
	{
		p->errmsg = message;
		p->errpos = p->pos;
	}
}

static
s_rxnode*	RX_Parse_NewNode(s_rxparser* p, e_rxnode_kind kind)
{
	s_rxnode*	result;

	result = (s_rxnode*)Memory_New(sizeof(s_rxnode));
	if (result == NULL)
	{
		RX_Parse_Error(p, "memory allocation failure");
		return (NULL);
	}
	result->kind = kind;
	result->icase = ((p->flags & REGEX_OPTION_IGNORECASE) != 0);
	result->allocs = p->allocs;
	p->allocs = result;
	return (result);
}

//! Frees every node in the given `allocs` linked-list (as well as any allocated node contents)
void	RX_DeleteAST(s_rxnode* allocs)
{
	s_rxnode*	node;
	s_rxnode*	next;

	node = allocs;
	while (node)
	{
		next = node->allocs;
		if (node->kind == RXNODE_CLASS && node->u.cclass.ranges)
			Memory_Free(node->u.cclass.ranges);
		if (node->kind == RXNODE_ALT && node->u.alt.branches)
			Memory_Free(node->u.alt.branches);
		Memory_Free(node);
		node = next;
	}
}



static
t_bool	RX_Parse_IsAtEnd(s_rxparser const* p)
{
	return (p->pos >= p->len);
}

//! Returns the byte at the current parsing position (or `'\0'` if at the end), without advancing
static
t_utf8	RX_Parse_Peek(s_rxparser const* p)
{
	if (p->pos >= p->len)
		return ('\0');
	return (p->pat[p->pos]);
}

//! Returns the byte at the current parsing position + `offset`, without advancing
static
t_utf8	RX_Parse_PeekAt(s_rxparser const* p, t_size offset)
{
	if (p->pos + offset >= p->len)
		return ('\0');
	return (p->pat[p->pos + offset]);
}

//! If the byte at the current position is `c`, advances past it and returns `TRUE`
static
t_bool	RX_Parse_Accept(s_rxparser* p, t_utf8 c)
{
	if (RX_Parse_Peek(p) == c)
	{
		p->pos += 1;
		return (TRUE);
	}
	return (FALSE);
}

//! Decodes and consumes one full UTF-8 character at the current position
static
t_utf32	RX_Parse_NextChar(s_rxparser* p)
{
	t_utf32	c;
	t_size	length;

	c = RX_Decode(p->pat, p->len, p->pos, &length);
	p->pos += length;
	return (c);
}



static
t_bool	RX_Parse_IsHexDigit(t_utf8 c, t_u32* digit)
{
	if (c >= '0' && c <= '9')	{ *digit = (c - '0');      return (TRUE); }
	if (c >= 'a' && c <= 'f')	{ *digit = (c - 'a' + 10); return (TRUE); }
	if (c >= 'A' && c <= 'F')	{ *digit = (c - 'A' + 10); return (TRUE); }
	return (FALSE);
}

//! Parses exactly `amount` hexadecimal digits (or, if `amount` is 0: any number of them, until a `}` char)
static
t_bool	RX_Parse_HexNumber(s_rxparser* p, t_uint amount, t_utf32* dest)
{
	t_utf32	result;
	t_u32	digit;
	t_uint	i;

	result = 0;
	i = 0;
	while (amount == 0 || i < amount)
	{
		if (amount == 0 && RX_Parse_Peek(p) == '}')
			break;
		if (!RX_Parse_IsHexDigit(RX_Parse_Peek(p), &digit))
		{
			RX_Parse_Error(p, "invalid hexadecimal digit in escape sequence");
			return (FALSE);
		}
		if (result > 0x0FFFFFFF)
		{
			RX_Parse_Error(p, "hexadecimal character code is too large");
			return (FALSE);
		}
		result = (result << 4) | digit;
		p->pos += 1;
		i += 1;
	}
	if (amount == 0 && i == 0)
	{
		RX_Parse_Error(p, "empty hexadecimal escape sequence: \\x{}");
		return (FALSE);
	}
	*dest = result;
	return (TRUE);
}



//! One entry of the unicode-property/POSIX-class name table
typedef struct rxpropname
{
	char const*	name;
	t_u32		prop;
}	s_rxpropname;

static s_rxpropname const	rx_propnames[] =
{
	{ "l"          , RXPROP_ALPHA  },
	{ "letter"     , RXPROP_ALPHA  },
	{ "alpha"      , RXPROP_ALPHA  },
	{ "lu"         , RXPROP_UPPER  },
	{ "upper"      , RXPROP_UPPER  },
	{ "uppercase"  , RXPROP_UPPER  },
	{ "ll"         , RXPROP_LOWER  },
	{ "lower"      , RXPROP_LOWER  },
	{ "lowercase"  , RXPROP_LOWER  },
	{ "n"          , RXPROP_DIGIT  },
	{ "nd"         , RXPROP_DIGIT  },
	{ "digit"      , RXPROP_DIGIT  },
	{ "xdigit"     , RXPROP_XDIGIT },
	{ "alnum"      , RXPROP_ALNUM  },
	{ "word"       , RXPROP_WORD   },
	{ "w"          , RXPROP_WORD   },
	{ "z"          , RXPROP_SPACE  },
	{ "zs"         , RXPROP_SPACE  },
	{ "space"      , RXPROP_SPACE  },
	{ "white_space", RXPROP_SPACE  },
	{ "whitespace" , RXPROP_SPACE  },
	{ "p"          , RXPROP_PUNCT  },
	{ "punct"      , RXPROP_PUNCT  },
	{ "punctuation", RXPROP_PUNCT  },
	{ "print"      , RXPROP_PRINT  },
	{ "graph"      , RXPROP_GRAPH  },
	{ "cntrl"      , RXPROP_CNTRL  },
	{ "control"    , RXPROP_CNTRL  },
	{ "blank"      , RXPROP_BLANK  },
	{ "ascii"      , RXPROP_ASCII  },
	{ NULL         , 0             },
};

//! Looks up the given (case-insensitive) property `name` of byte-length `length`, in the table above
static
t_u32	RX_Parse_GetPropertyByName(t_utf8 const* name, t_size length)
{
	t_uint	i;
	t_size	j;
	t_utf8	c;

	for (i = 0; rx_propnames[i].name; ++i)
	{
		for (j = 0; j < length; ++j)
		{
			c = name[j];
			if (c >= 'A' && c <= 'Z')
				c += ('a' - 'A');
			if (rx_propnames[i].name[j] == '\0' || rx_propnames[i].name[j] != c)
				break;
		}
		if (j == length && rx_propnames[i].name[j] == '\0')
			return (rx_propnames[i].prop);
	}
	return (0);
}

//! Parses a `\p{NAME}` or `\P{NAME}` unicode property escape (the `\p`/`\P` has already been consumed)
static
t_bool	RX_Parse_Property(s_rxparser* p, t_bool negated, t_u32* dest_prop, t_bool* dest_negated)
{
	t_size	start;
	t_u32	prop;

	if (!RX_Parse_Accept(p, '{'))
	{
		RX_Parse_Error(p, "expected `{` after `\\p` unicode property escape");
		return (FALSE);
	}
	if (RX_Parse_Accept(p, '^'))
		negated = !negated;
	start = p->pos;
	while (!RX_Parse_IsAtEnd(p) && RX_Parse_Peek(p) != '}')
		p->pos += 1;
	if (!RX_Parse_Accept(p, '}'))
	{
		RX_Parse_Error(p, "unterminated `\\p{...}` unicode property escape");
		return (FALSE);
	}
	prop = RX_Parse_GetPropertyByName(p->pat + start, p->pos - 1 - start);
	if (prop == 0)
	{
		p->pos = start;
		RX_Parse_Error(p, "unknown unicode property name in `\\p{...}` escape");
		return (FALSE);
	}
	*dest_prop = prop;
	*dest_negated = negated;
	return (TRUE);
}



//! The result kind of parsing one escape sequence
typedef enum rxescape_kind
{
	RXESCAPE_ERROR,		//!< a syntax error occurred
	RXESCAPE_CHAR,		//!< the escape yields a single literal character
	RXESCAPE_PROPERTY,	//!< the escape yields a character property (`\d`, `\w`, `\p{...}`, etc)
}	e_rxescape_kind;

//! Parses one escape sequence which is valid both inside and outside of a `[...]` class (the `\` has already been consumed)
static
e_rxescape_kind	RX_Parse_Escape(s_rxparser* p, t_bool in_class, t_utf32* dest_char, t_u32* dest_prop, t_bool* dest_negated)
{
	t_utf8	c;

	*dest_negated = FALSE;
	if (RX_Parse_IsAtEnd(p))
	{
		RX_Parse_Error(p, "pattern may not end with a trailing `\\` backslash");
		return (RXESCAPE_ERROR);
	}
	c = RX_Parse_Peek(p);
	switch (c)
	{
		case 'n':	p->pos += 1;	*dest_char = '\n';	return (RXESCAPE_CHAR);
		case 'r':	p->pos += 1;	*dest_char = '\r';	return (RXESCAPE_CHAR);
		case 't':	p->pos += 1;	*dest_char = '\t';	return (RXESCAPE_CHAR);
		case 'f':	p->pos += 1;	*dest_char = '\f';	return (RXESCAPE_CHAR);
		case 'a':	p->pos += 1;	*dest_char = '\a';	return (RXESCAPE_CHAR);
		case 'e':	p->pos += 1;	*dest_char = 0x1B;	return (RXESCAPE_CHAR);
		case '0':	p->pos += 1;	*dest_char = 0x00;	return (RXESCAPE_CHAR);
		case 'x':
		{
			p->pos += 1;
			if (RX_Parse_Accept(p, '{'))
			{
				if (!RX_Parse_HexNumber(p, 0, dest_char))
					return (RXESCAPE_ERROR);
				if (!RX_Parse_Accept(p, '}'))
				{
					RX_Parse_Error(p, "unterminated `\\x{...}` escape sequence");
					return (RXESCAPE_ERROR);
				}
				return (RXESCAPE_CHAR);
			}
			if (!RX_Parse_HexNumber(p, 2, dest_char))
				return (RXESCAPE_ERROR);
			return (RXESCAPE_CHAR);
		}
		case 'u':
		{
			p->pos += 1;
			if (!RX_Parse_HexNumber(p, 4, dest_char))
				return (RXESCAPE_ERROR);
			return (RXESCAPE_CHAR);
		}
		case 'c':
		{
			p->pos += 1;
			if (RX_Parse_IsAtEnd(p))
			{
				RX_Parse_Error(p, "expected a character after `\\c` control-char escape");
				return (RXESCAPE_ERROR);
			}
			c = RX_Parse_Peek(p);
			p->pos += 1;
			if (c >= 'a' && c <= 'z')
				c -= ('a' - 'A');
			*dest_char = (c ^ 0x40);
			return (RXESCAPE_CHAR);
		}
		case 'd':	p->pos += 1;	*dest_prop = RXPROP_DIGIT;	return (RXESCAPE_PROPERTY);
		case 'D':	p->pos += 1;	*dest_prop = RXPROP_DIGIT;	*dest_negated = TRUE;	return (RXESCAPE_PROPERTY);
		case 'w':	p->pos += 1;	*dest_prop = RXPROP_WORD;	return (RXESCAPE_PROPERTY);
		case 'W':	p->pos += 1;	*dest_prop = RXPROP_WORD;	*dest_negated = TRUE;	return (RXESCAPE_PROPERTY);
		case 's':	p->pos += 1;	*dest_prop = RXPROP_SPACE;	return (RXESCAPE_PROPERTY);
		case 'S':	p->pos += 1;	*dest_prop = RXPROP_SPACE;	*dest_negated = TRUE;	return (RXESCAPE_PROPERTY);
		case 'h':	p->pos += 1;	*dest_prop = RXPROP_HSPACE;	return (RXESCAPE_PROPERTY);
		case 'H':	p->pos += 1;	*dest_prop = RXPROP_HSPACE;	*dest_negated = TRUE;	return (RXESCAPE_PROPERTY);
		case 'v':	p->pos += 1;	*dest_prop = RXPROP_VSPACE;	return (RXESCAPE_PROPERTY);
		case 'V':	p->pos += 1;	*dest_prop = RXPROP_VSPACE;	*dest_negated = TRUE;	return (RXESCAPE_PROPERTY);
		case 'p':	p->pos += 1;	return (RX_Parse_Property(p, FALSE, dest_prop, dest_negated) ? RXESCAPE_PROPERTY : RXESCAPE_ERROR);
		case 'P':	p->pos += 1;	return (RX_Parse_Property(p, TRUE,  dest_prop, dest_negated) ? RXESCAPE_PROPERTY : RXESCAPE_ERROR);
		case 'b':
		{
			if (in_class) // within a class, `\b` is the backspace character
			{
				p->pos += 1;
				*dest_char = 0x08;
				return (RXESCAPE_CHAR);
			}
			RX_Parse_Error(p, "unexpected escape sequence");
			return (RXESCAPE_ERROR);
		}
		default:
		{
			if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
			{
				RX_Parse_Error(p, "unknown escape sequence");
				return (RXESCAPE_ERROR);
			}
			// any escaped punctuation character simply matches that character literally
			*dest_char = RX_Parse_NextChar(p);
			return (RXESCAPE_CHAR);
		}
	}
}



//! Appends one codepoint range to the given class node's `ranges` array
static
t_bool	RX_Parse_Class_AddRange(s_rxparser* p, s_rxnode* node, t_utf32 min, t_utf32 max)
{
	s_rxrange*	ranges;
	t_uint		amount;

	amount = node->u.cclass.ranges_amount;
	ranges = (s_rxrange*)Memory_Reallocate(node->u.cclass.ranges, (amount + 1) * sizeof(s_rxrange));
	if (ranges == NULL)
	{
		RX_Parse_Error(p, "memory allocation failure");
		return (FALSE);
	}
	ranges[amount].min = min;
	ranges[amount].max = max;
	node->u.cclass.ranges = ranges;
	node->u.cclass.ranges_amount = amount + 1;
	return (TRUE);
}

//! Parses a POSIX bracket class `[:name:]` or `[:^name:]` (the leading `[:` has NOT yet been consumed)
static
t_bool	RX_Parse_Class_Posix(s_rxparser* p, s_rxnode* node)
{
	t_size	start;
	t_bool	negated;
	t_u32	prop;

	p->pos += 2; // consume the `[:`
	negated = RX_Parse_Accept(p, '^');
	start = p->pos;
	while (!RX_Parse_IsAtEnd(p) && RX_Parse_Peek(p) != ':')
		p->pos += 1;
	prop = RX_Parse_GetPropertyByName(p->pat + start, p->pos - start);
	if (!RX_Parse_Accept(p, ':') || !RX_Parse_Accept(p, ']'))
	{
		RX_Parse_Error(p, "unterminated POSIX bracket class (expected `:]`)");
		return (FALSE);
	}
	if (prop == 0)
	{
		p->pos = start;
		RX_Parse_Error(p, "unknown POSIX bracket class name");
		return (FALSE);
	}
	if (negated)
		node->u.cclass.nprops |= prop;
	else
		node->u.cclass.props |= prop;
	return (TRUE);
}

//! Parses a `[...]` character class (the leading `[` has already been consumed), returning a `RXNODE_CLASS` node
static
s_rxnode*	RX_Parse_Class(s_rxparser* p)
{
	s_rxnode*		node;
	t_utf32			c;
	t_utf32			range_max;
	t_u32			prop;
	t_bool			negated;
	t_bool			first;
	e_rxescape_kind	escape;

	node = RX_Parse_NewNode(p, RXNODE_CLASS);
	if (node == NULL)
		return (NULL);
	node->u.cclass.negate = RX_Parse_Accept(p, '^');
	first = TRUE;
	while (TRUE)
	{
		if (RX_Parse_IsAtEnd(p))
		{
			RX_Parse_Error(p, "unterminated `[...]` character class (expected `]`)");
			return (NULL);
		}
		if (RX_Parse_Peek(p) == ']' && !first)
		{
			p->pos += 1;
			break;
		}
		first = FALSE;
		if (RX_Parse_Peek(p) == '[' && RX_Parse_PeekAt(p, 1) == ':')
		{
			if (!RX_Parse_Class_Posix(p, node))
				return (NULL);
			continue;
		}
		if (RX_Parse_Accept(p, '\\'))
		{
			escape = RX_Parse_Escape(p, TRUE, &c, &prop, &negated);
			if (escape == RXESCAPE_ERROR)
				return (NULL);
			if (escape == RXESCAPE_PROPERTY)
			{
				if (negated)
					node->u.cclass.nprops |= prop;
				else
					node->u.cclass.props |= prop;
				continue;
			}
		}
		else
		{
			c = RX_Parse_NextChar(p);
		}
		// check for a range: `a-z`
		if (RX_Parse_Peek(p) == '-' && RX_Parse_PeekAt(p, 1) != ']' && !(p->pos + 1 >= p->len))
		{
			p->pos += 1; // consume the `-`
			if (RX_Parse_Accept(p, '\\'))
			{
				escape = RX_Parse_Escape(p, TRUE, &range_max, &prop, &negated);
				if (escape == RXESCAPE_ERROR)
					return (NULL);
				if (escape == RXESCAPE_PROPERTY)
				{
					RX_Parse_Error(p, "cannot use a character-type escape as a range endpoint in a class");
					return (NULL);
				}
			}
			else
			{
				range_max = RX_Parse_NextChar(p);
			}
			if (range_max < c)
			{
				RX_Parse_Error(p, "invalid range in character class (endpoints are reversed)");
				return (NULL);
			}
			if (!RX_Parse_Class_AddRange(p, node, c, range_max))
				return (NULL);
		}
		else
		{
			if (!RX_Parse_Class_AddRange(p, node, c, c))
				return (NULL);
		}
	}
	return (node);
}



//! Creates a single-property class node (used for `\d`, `\w`, `\s`, `\p{...}`, etc, outside of a class)
static
s_rxnode*	RX_Parse_NewPropertyNode(s_rxparser* p, t_u32 prop, t_bool negated)
{
	s_rxnode*	node;

	node = RX_Parse_NewNode(p, RXNODE_CLASS);
	if (node == NULL)
		return (NULL);
	if (negated)
		node->u.cclass.negate = TRUE;
	node->u.cclass.props = prop;
	return (node);
}

//! Creates a single-character literal node
static
s_rxnode*	RX_Parse_NewLiteralNode(s_rxparser* p, t_utf32 c)
{
	s_rxnode*	node;

	node = RX_Parse_NewNode(p, RXNODE_LITERAL);
	if (node == NULL)
		return (NULL);
	node->u.literal.c = c;
	return (node);
}

//! Creates a zero-width anchor node
static
s_rxnode*	RX_Parse_NewAnchorNode(s_rxparser* p, e_rxanchor_kind kind)
{
	s_rxnode*	node;

	node = RX_Parse_NewNode(p, RXNODE_ANCHOR);
	if (node == NULL)
		return (NULL);
	node->u.anchor.kind = kind;
	return (node);
}



//! Computes the minimum/maximum possible width (in characters) of the given node chain (saturating at #RX_INFINITY)
static
void	RX_Parse_GetWidth(s_rxnode const* chain, t_u32* dest_min, t_u32* dest_max)
{
	s_rxnode const*	node;
	t_u32	total_min = 0;
	t_u32	total_max = 0;
	t_u32	min;
	t_u32	max;
	t_uint	i;

	for (node = chain; node; node = node->next)
	{
		min = 0;
		max = 0;
		switch (node->kind)
		{
			case RXNODE_LITERAL:
			case RXNODE_ANY:
			case RXNODE_CLASS:		min = 1;	max = 1;	break;
			case RXNODE_LINEBREAK:	min = 1;	max = 2;	break;
			case RXNODE_ANCHOR:
			case RXNODE_LOOK:		break;
			case RXNODE_BACKREF:	min = 0;	max = RX_INFINITY;	break;
			case RXNODE_GROUP:		RX_Parse_GetWidth(node->u.group.child, &min, &max);	break;
			case RXNODE_ALT:
			{
				min = RX_INFINITY;
				max = 0;
				for (i = 0; i < node->u.alt.amount; ++i)
				{
					t_u32	branch_min;
					t_u32	branch_max;
					RX_Parse_GetWidth(node->u.alt.branches[i], &branch_min, &branch_max);
					if (branch_min < min)	min = branch_min;
					if (branch_max > max)	max = branch_max;
				}
				if (node->u.alt.amount == 0)
					min = 0;
				break;
			}
			case RXNODE_REPEAT:
			{
				t_u32	child_min;
				t_u32	child_max;
				RX_Parse_GetWidth(node->u.repeat.child, &child_min, &child_max);
				if (child_min != 0 && node->u.repeat.min > RX_INFINITY / child_min)
					min = RX_INFINITY;
				else
					min = child_min * node->u.repeat.min;
				if (child_max == 0 || node->u.repeat.max == 0)
					max = 0;
				else if (node->u.repeat.max == RX_INFINITY || child_max == RX_INFINITY ||
					node->u.repeat.max > RX_INFINITY / child_max)
					max = RX_INFINITY;
				else
					max = child_max * node->u.repeat.max;
				break;
			}
		}
		total_min = (min == RX_INFINITY || total_min > RX_INFINITY - min) ? RX_INFINITY : (total_min + min);
		total_max = (max == RX_INFINITY || total_max > RX_INFINITY - max) ? RX_INFINITY : (total_max + max);
	}
	*dest_min = total_min;
	*dest_max = total_max;
}



//! Registers a new capture group, appending its `name` (which may be `NULL`) to the parser's names array
static
t_uint	RX_Parse_AddGroup(s_rxparser* p, t_utf8* name)
{
	t_utf8**	names;

	names = (t_utf8**)Memory_Reallocate(p->names, (p->groups + 1) * sizeof(t_utf8*));
	if (names == NULL)
	{
		RX_Parse_Error(p, "memory allocation failure");
		if (name)
			Memory_Free(name);
		return (0);
	}
	names[p->groups] = name;
	p->names = names;
	p->groups += 1;
	return (p->groups);
}

//! Parses a group name, delimited by the given `terminator` character (eg: `name>` or `name'`)
static
t_utf8*	RX_Parse_GroupName(s_rxparser* p, t_utf8 terminator)
{
	t_size	start;
	t_utf8	c;
	t_utf8*	result;

	start = p->pos;
	while (!RX_Parse_IsAtEnd(p) && RX_Parse_Peek(p) != terminator)
	{
		c = RX_Parse_Peek(p);
		if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
			(c >= '0' && c <= '9') || c == '_' || (t_u8)c >= 0x80))
		{
			RX_Parse_Error(p, "invalid character in capture group name");
			return (NULL);
		}
		p->pos += 1;
	}
	if (p->pos == start)
	{
		RX_Parse_Error(p, "capture group name may not be empty");
		return (NULL);
	}
	if (!RX_Parse_Accept(p, terminator))
	{
		RX_Parse_Error(p, "unterminated capture group name");
		return (NULL);
	}
	result = RX_StrNDup(p->pat + start, p->pos - 1 - start);
	if (result == NULL)
		RX_Parse_Error(p, "memory allocation failure");
	return (result);
}

//! Parses the inline option flag characters of a `(?imsxU-imsxU...` group
static
t_bool	RX_Parse_OptionFlags(s_rxparser* p)
{
	t_bool	remove;
	t_u32	flag;
	t_utf8	c;

	remove = FALSE;
	while (TRUE)
	{
		c = RX_Parse_Peek(p);
		if (c == ':' || c == ')')
			return (TRUE);
		flag = 0;
		switch (c)
		{
			case '-':	remove = TRUE;	p->pos += 1;	continue;
			case 'i':	flag = REGEX_OPTION_IGNORECASE;	break;
			case 'm':	flag = REGEX_OPTION_MULTILINE;	break;
			case 's':	flag = REGEX_OPTION_DOTALL;		break;
			case 'x':	flag = REGEX_OPTION_EXTENDED;	break;
			case 'U':	flag = REGEX_OPTION_UNGREEDY;	break;
			default:
			{
				RX_Parse_Error(p, "invalid inline option flag character (expected any of `imsxU`)");
				return (FALSE);
			}
		}
		if (remove)
			p->flags &= ~flag;
		else
			p->flags |= flag;
		p->pos += 1;
	}
}

//! Parses a `(...)` group of any kind (the leading `(` has already been consumed)
static
s_rxnode*	RX_Parse_Group(s_rxparser* p)
{
	s_rxnode*		node;
	t_utf8*			name;
	t_regex_options	saved_flags;
	t_bool			is_look = FALSE;
	t_bool			look_behind = FALSE;
	t_bool			look_negative = FALSE;
	t_bool			atomic = FALSE;
	t_uint			capture = 0;

	saved_flags = p->flags;
	name = NULL;
	if (RX_Parse_Accept(p, '?'))
	{
		if (RX_Parse_Accept(p, ':'))
			{}
		else if (RX_Parse_Accept(p, '>'))
			atomic = TRUE;
		else if (RX_Parse_Accept(p, '='))
			{ is_look = TRUE; }
		else if (RX_Parse_Accept(p, '!'))
			{ is_look = TRUE; look_negative = TRUE; }
		else if (RX_Parse_Accept(p, '#'))
		{	// comment group: skip everything until the closing `)`
			while (!RX_Parse_IsAtEnd(p) && RX_Parse_Peek(p) != ')')
				p->pos += 1;
			if (!RX_Parse_Accept(p, ')'))
			{
				RX_Parse_Error(p, "unterminated `(?#...)` comment group");
				return (NULL);
			}
			return (RX_Parse_NewNode(p, RXNODE_GROUP)); // an empty non-capturing group: zero-width, always matches
		}
		else if (RX_Parse_Peek(p) == '<' &&
			(RX_Parse_PeekAt(p, 1) == '=' || RX_Parse_PeekAt(p, 1) == '!'))
		{
			p->pos += 1;
			is_look = TRUE;
			look_behind = TRUE;
			look_negative = (RX_Parse_Peek(p) == '!');
			p->pos += 1;
		}
		else if (RX_Parse_Accept(p, '<'))
		{
			name = RX_Parse_GroupName(p, '>');
			if (name == NULL)
				return (NULL);
			capture = RX_Parse_AddGroup(p, name);
			if (capture == 0)
				return (NULL);
		}
		else if (RX_Parse_Accept(p, '\''))
		{
			name = RX_Parse_GroupName(p, '\'');
			if (name == NULL)
				return (NULL);
			capture = RX_Parse_AddGroup(p, name);
			if (capture == 0)
				return (NULL);
		}
		else if (RX_Parse_Peek(p) == 'P' && RX_Parse_PeekAt(p, 1) == '<')
		{
			p->pos += 2;
			name = RX_Parse_GroupName(p, '>');
			if (name == NULL)
				return (NULL);
			capture = RX_Parse_AddGroup(p, name);
			if (capture == 0)
				return (NULL);
		}
		else
		{	// inline option flags: `(?imsxU)` or `(?imsxU:...)`
			if (!RX_Parse_OptionFlags(p))
				return (NULL);
			if (RX_Parse_Accept(p, ')'))
			{	// a plain `(?flags)` group: alters the flags for the rest of the enclosing group
				// return a zero-width node which always matches (an empty non-capturing group)
				node = RX_Parse_NewNode(p, RXNODE_GROUP);
				return (node);
			}
			if (!RX_Parse_Accept(p, ':'))
			{
				RX_Parse_Error(p, "expected `:` or `)` after inline option flags");
				return (NULL);
			}
		}
	}
	else
	{	// plain `(...)` group
		if ((p->flags & REGEX_OPTION_NOCAPTURE) == 0)
		{
			capture = RX_Parse_AddGroup(p, NULL);
			if (capture == 0)
				return (NULL);
		}
	}
	if (is_look)
	{
		node = RX_Parse_NewNode(p, RXNODE_LOOK);
		if (node == NULL)
			return (NULL);
		node->u.look.behind = look_behind;
		node->u.look.negative = look_negative;
		node->u.look.child = RX_Parse_Alternation(p);
		if (p->errmsg)
			return (NULL);
		RX_Parse_GetWidth(node->u.look.child, &node->u.look.width_min, &node->u.look.width_max);
	}
	else
	{
		node = RX_Parse_NewNode(p, RXNODE_GROUP);
		if (node == NULL)
			return (NULL);
		node->u.group.capture = capture;
		node->u.group.atomic = atomic;
		node->u.group.child = RX_Parse_Alternation(p);
		if (p->errmsg)
			return (NULL);
	}
	if (!RX_Parse_Accept(p, ')'))
	{
		RX_Parse_Error(p, "unterminated group (expected `)`)");
		return (NULL);
	}
	p->flags = saved_flags;
	return (node);
}



//! Parses a `\k<name>` or `\k'name'` named backreference (the `\k` has already been consumed)
static
s_rxnode*	RX_Parse_NamedBackref(s_rxparser* p)
{
	s_rxnode*	node;
	t_utf8*		name;
	t_utf8		terminator;
	t_uint		i;

	if (RX_Parse_Accept(p, '<'))
		terminator = '>';
	else if (RX_Parse_Accept(p, '\''))
		terminator = '\'';
	else
	{
		RX_Parse_Error(p, "expected `<` or `'` after `\\k` named backreference");
		return (NULL);
	}
	name = RX_Parse_GroupName(p, terminator);
	if (name == NULL)
		return (NULL);
	for (i = 0; i < p->groups; ++i)
	{
		if (p->names[i] && StringUTF8_Equals(p->names[i], name))
			break;
	}
	Memory_Free(name);
	if (i == p->groups)
	{
		RX_Parse_Error(p, "named backreference refers to an unknown capture group");
		return (NULL);
	}
	node = RX_Parse_NewNode(p, RXNODE_BACKREF);
	if (node == NULL)
		return (NULL);
	node->u.backref.index = (i + 1);
	return (node);
}

//! Parses one "atom" of the pattern (a single matchable element, before any quantifier)
static
s_rxnode*	RX_Parse_Atom(s_rxparser* p)
{
	s_rxnode*		node;
	t_utf32			c;
	t_u32			prop;
	t_bool			negated;
	e_rxescape_kind	escape;
	t_bool			multiline;

	multiline = ((p->flags & REGEX_OPTION_MULTILINE) != 0);
	if (RX_Parse_Accept(p, '('))
		return (RX_Parse_Group(p));
	if (RX_Parse_Accept(p, '['))
		return (RX_Parse_Class(p));
	if (RX_Parse_Accept(p, '^'))
		return (RX_Parse_NewAnchorNode(p, multiline ? RXANCHOR_LINE_START : RXANCHOR_STR_START));
	if (RX_Parse_Accept(p, '$'))
		return (RX_Parse_NewAnchorNode(p, multiline ? RXANCHOR_LINE_END : RXANCHOR_STR_END_NL));
	if (RX_Parse_Accept(p, '.'))
	{
		node = RX_Parse_NewNode(p, RXNODE_ANY);
		if (node == NULL)
			return (NULL);
		node->u.any.dotall = ((p->flags & REGEX_OPTION_DOTALL) != 0);
		return (node);
	}
	if (RX_Parse_Accept(p, '\\'))
	{
		c = RX_Parse_Peek(p);
		switch (c)
		{
			case 'A':	p->pos += 1;	return (RX_Parse_NewAnchorNode(p, RXANCHOR_STR_START));
			case 'z':	p->pos += 1;	return (RX_Parse_NewAnchorNode(p, RXANCHOR_STR_END));
			case 'Z':	p->pos += 1;	return (RX_Parse_NewAnchorNode(p, RXANCHOR_STR_END_NL));
			case 'b':	p->pos += 1;	return (RX_Parse_NewAnchorNode(p, RXANCHOR_WORD_BOUND));
			case 'B':	p->pos += 1;	return (RX_Parse_NewAnchorNode(p, RXANCHOR_NOTWORD_BOUND));
			case 'G':	p->pos += 1;	return (RX_Parse_NewAnchorNode(p, RXANCHOR_MATCH_START));
			case 'R':	p->pos += 1;	return (RX_Parse_NewNode(p, RXNODE_LINEBREAK));
			case 'k':	p->pos += 1;	return (RX_Parse_NamedBackref(p));
			default:	break;
		}
		if (c >= '1' && c <= '9')
		{	// numbered backreference
			t_uint	index = 0;
			while (RX_Parse_Peek(p) >= '0' && RX_Parse_Peek(p) <= '9' && index < 100)
			{
				index = index * 10 + (RX_Parse_Peek(p) - '0');
				p->pos += 1;
			}
			if (index > p->groups)
			{
				RX_Parse_Error(p, "backreference refers to a capture group which does not (yet) exist");
				return (NULL);
			}
			node = RX_Parse_NewNode(p, RXNODE_BACKREF);
			if (node == NULL)
				return (NULL);
			node->u.backref.index = index;
			return (node);
		}
		escape = RX_Parse_Escape(p, FALSE, &c, &prop, &negated);
		if (escape == RXESCAPE_ERROR)
			return (NULL);
		if (escape == RXESCAPE_PROPERTY)
			return (RX_Parse_NewPropertyNode(p, prop, negated));
		return (RX_Parse_NewLiteralNode(p, c));
	}
	c = RX_Parse_NextChar(p);
	return (RX_Parse_NewLiteralNode(p, c));
}



//! Parses an optional quantifier suffix (`?`, `*`, `+`, `{n,m}`), wrapping the given `atom` in a repeat node if one is present
static
s_rxnode*	RX_Parse_Quantifier(s_rxparser* p, s_rxnode* atom)
{
	s_rxnode*	node;
	t_u32		min;
	t_u32		max;
	t_utf8		c;

	c = RX_Parse_Peek(p);
	if (c == '?')		{ min = 0;	max = 1;           }
	else if (c == '*')	{ min = 0;	max = RX_INFINITY; }
	else if (c == '+')	{ min = 1;	max = RX_INFINITY; }
	else if (c == '{')
	{	// parse `{n}`, `{n,}` or `{n,m}` - if malformed, the `{` is simply treated as a literal char
		t_size	saved = p->pos;
		t_bool	valid = FALSE;
		p->pos += 1;
		min = 0;
		max = RX_INFINITY;
		if (RX_Parse_Peek(p) >= '0' && RX_Parse_Peek(p) <= '9')
		{
			while (RX_Parse_Peek(p) >= '0' && RX_Parse_Peek(p) <= '9')
			{
				min = min * 10 + (RX_Parse_Peek(p) - '0');
				if (min > 100000)	min = 100000;
				p->pos += 1;
			}
			if (RX_Parse_Accept(p, '}'))
			{
				max = min;
				valid = TRUE;
			}
			else if (RX_Parse_Accept(p, ','))
			{
				if (RX_Parse_Accept(p, '}'))
					valid = TRUE;
				else if (RX_Parse_Peek(p) >= '0' && RX_Parse_Peek(p) <= '9')
				{
					max = 0;
					while (RX_Parse_Peek(p) >= '0' && RX_Parse_Peek(p) <= '9')
					{
						max = max * 10 + (RX_Parse_Peek(p) - '0');
						if (max > 100000)	max = 100000;
						p->pos += 1;
					}
					if (RX_Parse_Accept(p, '}'))
						valid = TRUE;
				}
			}
		}
		if (!valid)
		{
			p->pos = saved;
			return (atom);
		}
		if (max < min)
		{
			p->pos = saved;
			RX_Parse_Error(p, "invalid `{n,m}` quantifier (the maximum is smaller than the minimum)");
			return (NULL);
		}
		p->pos -= 1; // step back onto the `}`, so the shared logic below can advance past it
		c = '}';
	}
	else
	{
		return (atom);
	}
	p->pos += 1; // consume the quantifier character
	node = RX_Parse_NewNode(p, RXNODE_REPEAT);
	if (node == NULL)
		return (NULL);
	node->u.repeat.min = min;
	node->u.repeat.max = max;
	node->u.repeat.child = atom;
	if (RX_Parse_Accept(p, '?'))
		node->u.repeat.lazy = TRUE;
	else if (RX_Parse_Accept(p, '+'))
		node->u.repeat.possessive = TRUE;
	if ((p->flags & REGEX_OPTION_UNGREEDY) && !node->u.repeat.possessive)
		node->u.repeat.lazy = !node->u.repeat.lazy;
	return (node);
}



//! In extended/free-spacing mode: skips any whitespace, and any `#` comments (which span to the end of the line)
static
void	RX_Parse_SkipExtendedWhitespace(s_rxparser* p)
{
	t_utf8	c;

	if ((p->flags & REGEX_OPTION_EXTENDED) == 0)
		return;
	while (!RX_Parse_IsAtEnd(p))
	{
		c = RX_Parse_Peek(p);
		if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == 0x0B)
			p->pos += 1;
		else if (c == '#')
		{
			while (!RX_Parse_IsAtEnd(p) && RX_Parse_Peek(p) != '\n')
				p->pos += 1;
		}
		else
			break;
	}
}

//! Parses a sequence of quantified atoms (one branch of an alternation)
static
s_rxnode*	RX_Parse_Sequence(s_rxparser* p)
{
	s_rxnode*	head;
	s_rxnode*	tail;
	s_rxnode*	atom;
	t_utf32		c;

	head = NULL;
	tail = NULL;
	while (TRUE)
	{
		RX_Parse_SkipExtendedWhitespace(p);
		if (RX_Parse_IsAtEnd(p) || RX_Parse_Peek(p) == '|' || RX_Parse_Peek(p) == ')')
			break;
		if (RX_Parse_Peek(p) == '\\' && RX_Parse_PeekAt(p, 1) == 'Q')
		{	// verbatim-quoted span: `\Q...\E`
			p->pos += 2;
			while (!RX_Parse_IsAtEnd(p))
			{
				if (RX_Parse_Peek(p) == '\\' && RX_Parse_PeekAt(p, 1) == 'E')
				{
					p->pos += 2;
					break;
				}
				c = RX_Parse_NextChar(p);
				atom = RX_Parse_NewLiteralNode(p, c);
				if (atom == NULL)
					return (NULL);
				if (tail)	tail->next = atom;
				else		head = atom;
				tail = atom;
			}
			continue;
		}
		if (RX_Parse_Peek(p) == '*' || RX_Parse_Peek(p) == '+' || RX_Parse_Peek(p) == '?')
		{
			RX_Parse_Error(p, "quantifier has nothing to repeat");
			return (NULL);
		}
		atom = RX_Parse_Atom(p);
		if (atom == NULL)
			return (NULL);
		RX_Parse_SkipExtendedWhitespace(p);
		atom = RX_Parse_Quantifier(p, atom);
		if (atom == NULL)
			return (NULL);
		if (tail)	tail->next = atom;
		else		head = atom;
		tail = atom;
	}
	return (head);
}

//! Parses a full alternation: one or more sequences, separated by `|` characters
static
s_rxnode*	RX_Parse_Alternation(s_rxparser* p)
{
	s_rxnode*	node;
	s_rxnode*	branch;
	s_rxnode**	branches;
	t_uint		amount;

	branch = RX_Parse_Sequence(p);
	if (p->errmsg)
		return (NULL);
	if (!RX_Parse_Accept(p, '|'))
		return (branch);
	node = RX_Parse_NewNode(p, RXNODE_ALT);
	if (node == NULL)
		return (NULL);
	branches = (s_rxnode**)Memory_New(2 * sizeof(s_rxnode*));
	if (branches == NULL)
	{
		RX_Parse_Error(p, "memory allocation failure");
		return (NULL);
	}
	branches[0] = branch;
	amount = 1;
	while (TRUE)
	{
		branch = RX_Parse_Sequence(p);
		if (p->errmsg)
		{
			node->u.alt.branches = branches;
			node->u.alt.amount = amount;
			return (NULL);
		}
		branches[amount] = branch;
		amount += 1;
		if (!RX_Parse_Accept(p, '|'))
			break;
		branches = (s_rxnode**)Memory_Reallocate(branches, (amount + 1) * sizeof(s_rxnode*));
		if (branches == NULL)
		{
			RX_Parse_Error(p, "memory allocation failure");
			node->u.alt.amount = 0;
			return (NULL);
		}
	}
	node->u.alt.branches = branches;
	node->u.alt.amount = amount;
	return (node);
}



s_regex*	Regex_New(t_utf8 const* pattern, t_regex_options options)
{
	s_regex*		result;
	s_rxcompiled*	compiled;
	s_rxparser		p = {0};
	s_rxnode*		root;
	t_uint			i;

	if CCCERROR((pattern == NULL), ERROR_NULLPOINTER, "regex pattern given is NULL")
		return (NULL);
	if CCCERROR((!CharUTF8_IsStringValid(pattern, NULL, NULL)), ERROR_ILLEGALBYTES,
		"regex pattern given is not a valid UTF-8 string")
		return (NULL);
	p.pat = pattern;
	p.len = StringUTF8_Length(pattern);
	p.flags = options;
	root = RX_Parse_Alternation(&p);
	if (p.errmsg == NULL && !RX_Parse_IsAtEnd(&p))
		RX_Parse_Error(&p, "unmatched closing parenthesis `)`");
	if (p.errmsg)
	{
		RX_DeleteAST(p.allocs);
		for (i = 0; i < p.groups; ++i)
		{
			if (p.names[i])
				Memory_Free(p.names[i]);
		}
		if (p.names)
			Memory_Free(p.names);
		if CCCERROR(TRUE, ERROR_PARSE,
			"invalid regex pattern, syntax error at position " SF_SIZE ": %s",
			p.errpos, p.errmsg)
			return (NULL);
		return (NULL);
	}
	result = (s_regex*)Memory_New(sizeof(s_regex));
	compiled = (s_rxcompiled*)Memory_New(sizeof(s_rxcompiled));
	if (result == NULL || compiled == NULL)
	{
		if (result)		Memory_Free(result);
		if (compiled)	Memory_Free(compiled);
		RX_DeleteAST(p.allocs);
		if CCCERROR(TRUE, ERROR_ALLOCFAILURE, NULL)
			return (NULL);
		return (NULL);
	}
	compiled->root = root;
	compiled->allocs = p.allocs;
	result->pattern = RX_StrDup(pattern);
	result->options = options;
	result->groups = p.groups;
	result->names = p.names;
	result->compiled = compiled;
	return (result);
}
