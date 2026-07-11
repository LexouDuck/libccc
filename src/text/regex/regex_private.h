/*============================================================================*\
||                                            ______________________________  ||
||  src/text/regex/regex_private.h           |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_TEXT_REGEX_PRIVATE_H
#define __LIBCCC_TEXT_REGEX_PRIVATE_H

/*
**	This header is private to the regex engine implementation:
**	it defines the internal "compiled pattern" representation (an AST of `s_rxnode`),
**	which is what is stored in the public `s_regex` struct's opaque `.compiled` field.
*/

#include "libccc.h"
#include "libccc/text/regex.h"

/*============================================================================*\
||                              Engine limits                                 ||
\*============================================================================*/

//! The maximum amount of "steps" the backtracking matcher may take for a single match attempt (guards against catastrophic backtracking)
#define RX_LIMIT_STEPS	(1 << 24)
//! The maximum recursion depth of the backtracking matcher (guards against C stack overflow)
#define RX_LIMIT_DEPTH	(20000)
//! The value used for the `max` field of a repeat node, to signify "no upper bound" (ie: `*`, `+`, `{n,}`)
#define RX_INFINITY		((t_u32)-1)

/*============================================================================*\
||                        Character property bitflags                         ||
\*============================================================================*/

/*
**	These property bitflags are used within character class nodes, to represent
**	character "types" (`\d`, `\w`, POSIX classes, `\p{...}` unicode properties, etc).
**	A class node has two such bitmasks: `props` (character must have the property),
**	and `nprops` (character must NOT have the property, eg: for a `\D` within a class).
*/
#define RXPROP_ALPHA	(1 << 0)	//!< `\p{L}`, `[:alpha:]` : any unicode letter
#define RXPROP_UPPER	(1 << 1)	//!< `\p{Lu}`, `[:upper:]`: any uppercase letter
#define RXPROP_LOWER	(1 << 2)	//!< `\p{Ll}`, `[:lower:]`: any lowercase letter
#define RXPROP_DIGIT	(1 << 3)	//!< `\d`, `\p{Nd}`, `[:digit:]`: any decimal digit
#define RXPROP_XDIGIT	(1 << 4)	//!< `[:xdigit:]`: any hexadecimal digit
#define RXPROP_ALNUM	(1 << 5)	//!< `[:alnum:]`: any letter or decimal digit
#define RXPROP_WORD		(1 << 6)	//!< `\w`, `[:word:]`: any letter, decimal digit, or underscore
#define RXPROP_SPACE	(1 << 7)	//!< `\s`, `\p{Z}`, `[:space:]`: any whitespace character
#define RXPROP_HSPACE	(1 << 8)	//!< `\h`: any horizontal whitespace character (space, tab, etc)
#define RXPROP_VSPACE	(1 << 9)	//!< `\v` (in some contexts), `[:vspace:]`: any vertical whitespace character (newline, etc)
#define RXPROP_PUNCT	(1 << 10)	//!< `\p{P}`, `[:punct:]`: any punctuation character
#define RXPROP_PRINT	(1 << 11)	//!< `[:print:]`: any printable character
#define RXPROP_GRAPH	(1 << 12)	//!< `[:graph:]`: any printable character, excluding whitespace
#define RXPROP_CNTRL	(1 << 13)	//!< `[:cntrl:]`: any control character
#define RXPROP_BLANK	(1 << 14)	//!< `[:blank:]`: a space or a tab character
#define RXPROP_ASCII	(1 << 15)	//!< `\p{ASCII}`, `[:ascii:]`: any character in the ASCII range (0x00 to 0x7F)

/*============================================================================*\
||                              AST node types                                ||
\*============================================================================*/

//! The different kinds of nodes which can make up a compiled regular expression AST
typedef enum rxnode_kind
{
	RXNODE_LITERAL,	//!< matches one particular character
	RXNODE_ANY,		//!< matches any character: `.`
	RXNODE_CLASS,	//!< matches a character class: `[...]`, `\d`, `\w`, `\p{...}`, etc
	RXNODE_LINEBREAK,//!< matches any newline sequence: `\R` (ie: `\r\n`, `\r`, or `\n`)
	RXNODE_ANCHOR,	//!< matches a zero-width position assertion: `^`, `$`, `\A`, `\b`, etc
	RXNODE_GROUP,	//!< a (possibly capturing, possibly atomic) group: `(...)`, `(?:...)`, `(?>...)`
	RXNODE_LOOK,	//!< a look-around assertion: `(?=...)`, `(?!...)`, `(?<=...)`, `(?<!...)`
	RXNODE_BACKREF,	//!< a backreference to a previous capture group: `\1`, `\k<name>`
	RXNODE_ALT,		//!< an alternation between two or more branches: `...|...`
	RXNODE_REPEAT,	//!< a quantified/repeated sub-expression: `?`, `*`, `+`, `{n,m}`
}	e_rxnode_kind;

//! The different kinds of zero-width position assertions (for `RXNODE_ANCHOR` nodes)
typedef enum rxanchor_kind
{
	RXANCHOR_STR_START,		//!< `\A` (or `^`, when not in multiline mode): matches only at the very start of the string
	RXANCHOR_STR_END,		//!< `\z`: matches only at the very end of the string
	RXANCHOR_STR_END_NL,	//!< `\Z` (or `$`, when not in multiline mode): matches at the very end of the string, or just before a string-final newline
	RXANCHOR_LINE_START,	//!< `^` (in multiline mode): matches at the start of the string, or just after any newline
	RXANCHOR_LINE_END,		//!< `$` (in multiline mode): matches at the end of the string, or just before any newline
	RXANCHOR_WORD_BOUND,	//!< `\b`: matches at any position between a "word" character and a non-"word" character
	RXANCHOR_NOTWORD_BOUND,	//!< `\B`: matches at any position which is not a word boundary
	RXANCHOR_MATCH_START,	//!< `\G`: matches only at the position where the current match attempt started
}	e_rxanchor_kind;

//! A single (inclusive) range of unicode codepoints, within a character class node
typedef struct rxrange
{
	t_utf32	min;	//!< the smallest codepoint of this range (inclusive)
	t_utf32	max;	//!< the largest codepoint of this range (inclusive)
}	s_rxrange;

//! A single node of a compiled regular expression AST
typedef struct rxnode
{
	e_rxnode_kind	kind;		//!< which kind of node this is (determines which member of the union `u` is used)
	t_bool			icase;		//!< if `TRUE`, this node matches case-insensitively (resolved at compile-time, from global/inline `i` flags)
	struct rxnode*	next;		//!< the next node in the current sequence/chain (`NULL` if this is the last node of the chain)
	struct rxnode*	allocs;		//!< [internal] linked-list of every allocated node (used to free the whole AST easily)
	union
	{
		struct	//!< for `RXNODE_LITERAL`
		{
			t_utf32	c;			//!< the character to match
		}	literal;
		struct	//!< for `RXNODE_ANY`
		{
			t_bool	dotall;		//!< if `TRUE`, also matches newline characters (resolved at compile-time, from `s` flags)
		}	any;
		struct	//!< for `RXNODE_CLASS`
		{
			t_bool		negate;			//!< if `TRUE`, the class matches any character which is NOT described by it: `[^...]`
			t_u32		props;			//!< bitmask of `RXPROP_*` character properties which match
			t_u32		nprops;			//!< bitmask of `RXPROP_*` character properties whose complement matches (eg: `\D`, `\W`)
			t_uint		ranges_amount;	//!< the amount of items in the `ranges` array
			s_rxrange*	ranges;			//!< the array of codepoint ranges which match (single chars are stored as a range of 1)
		}	cclass;
		struct	//!< for `RXNODE_ANCHOR`
		{
			e_rxanchor_kind	kind;	//!< which kind of position assertion this is
		}	anchor;
		struct	//!< for `RXNODE_GROUP`
		{
			t_uint			capture;	//!< the 1-based index of this capture group (or `0`, if this group is non-capturing)
			t_bool			atomic;		//!< if `TRUE`, this is an atomic group `(?>...)`: once matched, it is never backtracked into
			struct rxnode*	child;		//!< the chain of nodes contained within the group
		}	group;
		struct	//!< for `RXNODE_LOOK`
		{
			t_bool			behind;		//!< if `TRUE`, this is a lookbehind (otherwise, a lookahead)
			t_bool			negative;	//!< if `TRUE`, this is a negative look-around: `(?!...)`, `(?<!...)`
			struct rxnode*	child;		//!< the chain of nodes contained within the look-around
			t_u32			width_min;	//!< the minimum possible width (in characters) of the child pattern (used for lookbehind)
			t_u32			width_max;	//!< the maximum possible width (in characters) of the child pattern (`RX_INFINITY` if unbounded)
		}	look;
		struct	//!< for `RXNODE_BACKREF`
		{
			t_uint	index;	//!< the 1-based index of the capture group which this node refers back to
		}	backref;
		struct	//!< for `RXNODE_ALT`
		{
			t_uint			amount;		//!< the amount of branches in this alternation
			struct rxnode**	branches;	//!< the array of branch node chains
		}	alt;
		struct	//!< for `RXNODE_REPEAT`
		{
			t_u32			min;		//!< the minimum amount of repetitions
			t_u32			max;		//!< the maximum amount of repetitions (`RX_INFINITY` if unbounded)
			t_bool			lazy;		//!< if `TRUE`, this quantifier is lazy/reluctant (matches as few repetitions as possible)
			t_bool			possessive;	//!< if `TRUE`, this quantifier is possessive (matches as many repetitions as possible, and never backtracks)
			struct rxnode*	child;		//!< the chain of nodes being repeated
		}	repeat;
	}	u;
}	s_rxnode;

//! The engine's internal compiled representation of a regular expression (stored in `s_regex.compiled`)
typedef struct rxcompiled
{
	s_rxnode*	root;	//!< the root node chain of the compiled AST
	s_rxnode*	allocs;	//!< the head of the linked-list of every allocated node (linked via each node's `.allocs` field)
}	s_rxcompiled;

/*============================================================================*\
||                     Internal shared utility functions                      ||
\*============================================================================*/

//! Frees every node in the given `allocs` linked-list (as well as any allocated node contents)
void	RX_DeleteAST(s_rxnode* allocs);
//! Returns a newly allocated copy of the given string (equivalent to strdup)
t_utf8*	RX_StrDup(t_utf8 const* str);
//! Returns a newly allocated, NUL-terminated copy of the first `n` bytes of the given string
t_utf8*	RX_StrNDup(t_utf8 const* str, t_size n);
//! Decodes the UTF-8 character at `str[pos]`, writing its byte-length to `*dest_length` (invalid sequences are decoded as a single raw byte)
t_utf32	RX_Decode(t_utf8 const* str, t_size length, t_size pos, t_size* dest_length);
//! Decodes the UTF-8 character which precedes `str[pos]`, writing its byte-length to `*dest_length`
t_utf32	RX_DecodePrev(t_utf8 const* str, t_size pos, t_size* dest_length);
//! Checks whether the given codepoint `c` has all the character properties given in the `props` bitmask
t_bool	RX_HasProps(t_utf32 c, t_u32 props);
//! Checks whether the given codepoint `c` is a "word" character (letter, digit, or underscore)
t_bool	RX_IsWordChar(t_utf32 c);
//! Checks whether the given codepoint `c` matches the given character class node (must be of kind `RXNODE_CLASS`)
t_bool	RX_MatchClass(s_rxnode const* node, t_utf32 c);
//! The core matching routine: searches/matches `regex` within `str` (of byte-length `len`)
/*!
**	@param	regex		The compiled regular expression to match with
**	@param	str			The string to match against
**	@param	len			The length (in bytes) of `str`
**	@param	offset		The byte position at which matching starts
**	@param	anchored	If `TRUE`, only attempt to match at exactly `offset`; otherwise, search forward from `offset`
**	@param	entire		If `TRUE`, the match is required to span until the very end of the string
**	@param	dest_match	(optional) if not `NULL`, is filled with the resulting match info (allocates its `.captures` array)
**	@returns `TRUE` if a match was found, otherwise `FALSE`
*/
t_bool	RX_Run(s_regex const* regex, t_utf8 const* str, t_size len, t_size offset, t_bool anchored, t_bool entire, s_regex_match* dest_match);

#endif
