/*============================================================================*\
||                                            ______________________________  ||
||  libccc/text/regex.h                      |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_TEXT_REGEX_H
#define __LIBCCC_TEXT_REGEX_H
/*!@group{libccc_text_regex,20,libccc/text/regex.h}
**
**	This header defines types and functions for regular expression matching/replacing.
**
**	The regex engine implemented here is a backtracking engine, whose syntax/feature-set
**	is heavily inspired by the all-encompassing [Oniguruma](https://github.com/kkos/oniguruma)
**	regex engine (which itself encompasses the features of several regex dialects: PCRE, ruby, etc).
**	The strings handled by these functions are UTF-8 strings (`t_utf8 const*`) - note that,
**	since any ASCII string is by definition also a valid UTF-8 string, these regex functions
**	can be used on ASCII strings without any conversion needed.
**
**	Here is an overview of the supported regular expression syntax:
**
**	- **Characters/escapes**: `\t`, `\n`, `\r`, `\f`, `\v`, `\a`, `\e`, `\0`,
**		`\xFF`, `\x{FFFFFFFF}`, `\uFFFF`, `\cX` (control char), `\Q...\E` (verbatim quoting)
**	- **Character types**: `.` (any char), `\d`/`\D` (digit), `\w`/`\W` (word char),
**		`\s`/`\S` (whitespace), `\h`/`\H` (horizontal whitespace), `\v`/`\V` (vertical whitespace),
**		`\R` (any newline sequence, ie: `\r\n`, `\r`, or `\n`),
**		`\p{PROPERTY}`/`\P{PROPERTY}` (unicode character property, eg: `\p{L}`, `\p{Lu}`, `\p{Nd}`, etc)
**	- **Character classes**: `[abc]`, `[^abc]`, `[a-z]`, with support for escapes/types within,
**		and POSIX bracket classes: `[:alpha:]`, `[:digit:]`, `[:space:]`, `[:^alpha:]`, etc
**	- **Anchors**: `^` (line start), `$` (line end), `\A` (string start), `\z` (string end),
**		`\Z` (string end, ignoring any final newline), `\b`/`\B` (word boundary), `\G` (match start)
**	- **Quantifiers**: `?`, `*`, `+`, `{n}`, `{n,}`, `{n,m}` - each of which can be made
**		lazy/reluctant with a `?` suffix, or possessive (never backtracks) with a `+` suffix
**	- **Alternation**: `foo|bar`
**	- **Groups**: `(...)` (capturing), `(?:...)` (non-capturing), `(?>...)` (atomic),
**		`(?<name>...)`/`(?'name'...)`/`(?P<name>...)` (named capturing), `(?#...)` (comment),
**		`(?imxsU)`/`(?-imxsU)`/`(?imxsU:...)` (inline option flags)
**	- **Look-around**: `(?=...)` (lookahead), `(?!...)` (negative lookahead),
**		`(?<=...)` (lookbehind), `(?<!...)` (negative lookbehind) - lookbehind may be variable-length
**	- **Backreferences**: `\1` through `\99`, `\k<name>`, `\k'name'`
**
**	- http://www.greenend.org.uk/rjk/tech/regexp.html#matchmulti
**	- https://www.regular-expressions.info/modifiers.html
**	- https://github.com/kkos/oniguruma/blob/master/doc/RE
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc.h"

HEADER_CPP

#ifndef __LIBCCC_TEXT_REGEX_T
#define __LIBCCC_TEXT_REGEX_T

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//!@doc Option flags, to alter the behavior of regular expression compiling/matching
/*!
**	These option bitflag values can be combined together with the `|` bitwise-or operator.
**	Most of these options can also be set/unset locally within a pattern,
**	by using inline option groups, for example: `(?i)`, `(?-i)`, or `(?im:...)`
*/
//!@{

//! The type used to store a set of regular expression option bitflags
typedef t_u32	t_regex_options;
TYPEDEF_ALIAS(	t_regex_options, REGEX_OPTIONS, PRIMITIVE)

#define REGEX_OPTION_NONE		(0)			//!< The default options (no option flags set)
#define REGEX_OPTION_IGNORECASE	(1 << 0)	//!< `(?i)`: case-insensitive matching (eg: `a` will match both `a` and `A`)
#define REGEX_OPTION_MULTILINE	(1 << 1)	//!< `(?m)`: the `^` and `$` anchors also match at line-breaks, not just at the start/end of the string
#define REGEX_OPTION_DOTALL		(1 << 2)	//!< `(?s)`: the `.` wildcard also matches newline characters (also known as "single-line mode")
#define REGEX_OPTION_EXTENDED	(1 << 3)	//!< `(?x)`: "free-spacing mode": whitespace in the pattern is ignored, and `#` starts a comment which spans to the end of the line
#define REGEX_OPTION_UNGREEDY	(1 << 4)	//!< `(?U)`: inverts the "greediness" of quantifiers: `*` becomes lazy, and `*?` becomes greedy, etc
#define REGEX_OPTION_ANCHORED	(1 << 5)	//!< the pattern is forced to only match at the very start of the searched region (as if it began with `\G`)
#define REGEX_OPTION_NOCAPTURE	(1 << 6)	//!< plain `(...)` groups do not capture (only named groups like `(?<name>...)` will capture)
//!@}

//! The value stored in an #s_regex_capture group's `.index` field, when that group did not take part in the match
#define REGEX_NOMATCH	((t_size)-1)



//!@doc A structure to store the region of the searched string which was captured by one capture group
/*!
**	@nonstd
**
**	Both fields of this struct are expressed in bytes (not in UTF-8 symbols/graphemes),
**	such that the captured region of a string `str` is: `str[index]` to `str[index + length - 1]`.
*/
//!@{
typedef struct regex_capture
{
	t_size	index;	//!< The index (in bytes) of the start of the captured region, or #REGEX_NOMATCH if this group did not match
	t_size	length;	//!< The length (in bytes) of the captured region
}	s_regex_capture;
TYPEDEF_ALIAS(s_regex_capture, REGEX_CAPTURE, STRUCT)
//!@}

//!@doc A structure to store the result of a (successful) regular expression match
/*!
**	@nonstd
**
**	The `captures` array always holds `captures_amount` items: the item at index `0`
**	is the region of the whole match, and each item `n` (starting at `1`) is the region
**	captured by the pattern's `n`th capture group (or `{ REGEX_NOMATCH, 0 }`, if that
**	particular group did not take part in the match).
**	The `captures` array buffer is allocated by whichever matching function filled this
**	struct, and should be freed by calling RegexMatch_Delete() when no longer needed.
*/
//!@{
typedef struct regex_match
{
	t_size				index;				//!< The index (in bytes) of the start of the whole match (equal to `captures[0].index`)
	t_size				length;				//!< The length (in bytes) of the whole match (equal to `captures[0].length`)
	t_uint				captures_amount;	//!< The amount of items in the `captures` array (this is always the pattern's group amount + 1)
	s_regex_capture*	captures;			//!< The array of captured regions (item `0` is the whole match, item `n` is capture group `n`)
}	s_regex_match;
TYPEDEF_ALIAS(s_regex_match, REGEX_MATCH, STRUCT)
//!@}

//!@doc The main aggregate type used to store a compiled regular expression
/*!
**	@nonstd
**
**	This struct is created by calling Regex_New(), and freed by calling Regex_Delete().
**	Its fields should generally be considered read-only: in particular, the `compiled`
**	field holds the engine's internal representation of the pattern, and is opaque.
*/
//!@{
typedef struct regex
{
	t_utf8*			pattern;	//!< The source pattern string which was compiled (allocated copy)
	t_regex_options	options;	//!< The global option flags which were given when compiling
	t_uint			groups;		//!< The total amount of capture groups in the pattern (not counting the whole-match "group 0")
	t_utf8**		names;		//!< The array of capture group names: `names[n - 1]` is the name of group `n` (`NULL` if that group is unnamed)
	void*			compiled;	//!< [opaque] The engine's internal compiled representation of the pattern
}	s_regex;
TYPEDEF_ALIAS(s_regex, REGEX, STRUCT)
//!@}

#endif
#ifndef __LIBCCC_TEXT_REGEX_F
#define __LIBCCC_TEXT_REGEX_F

/*============================================================================*\
||                             Compiling functions                            ||
\*============================================================================*/

//!@doc Compiles the given regular expression `pattern` string, with the given `options` flags
/*!
**	@nonstd
**
**	@param	pattern	The regular expression pattern to compile (must be a valid UTF-8 string)
**	@param	options	The global option flags to compile with (a set of `REGEX_OPTION_*` bitflags)
**	@returns
**	A newly allocated compiled regular expression struct,
**	or `NULL` if an error occurred (ie: if the given `pattern` has invalid syntax).
*/
//!@{
s_regex*				Regex_New(t_utf8 const* pattern, t_regex_options options);
#define c_regnew		Regex_New
#define Regex_Compile	Regex_New
//!@}

//!@doc Deletes the given compiled regular expression `*a_regex` (freeing all its allocated contents)
/*!
**	@nonstd
**
**	@param	a_regex	The address of the compiled regex to delete (will be set to `NULL`)
*/
//!@{
void					Regex_Delete(s_regex* *a_regex);
#define c_regdel		Regex_Delete
//!@}

//!@doc Gets the total amount of capture groups contained in the given compiled `regex`
/*!
**	@nonstd
**
**	@param	regex	The compiled regular expression to inspect
**	@returns
**	The total amount of capture groups in the pattern (not counting the whole-match "group 0")
*/
//!@{
t_uint					Regex_GetGroupAmount(s_regex const* regex);
#define c_reggroups		Regex_GetGroupAmount
//!@}

//!@doc Gets the name of the capture group with the given `index`, in the given compiled `regex`
/*!
**	@nonstd
**
**	@param	regex	The compiled regular expression to inspect
**	@param	index	The index of the capture group whose name should be returned (the first group is `1`)
**	@returns
**	The name of the capture group with the given `index`,
**	or `NULL` if that group has no name, or if no group with such an `index` exists.
*/
//!@{
t_utf8 const*			Regex_GetGroupName(s_regex const* regex, t_uint index);
#define c_reggroupname	Regex_GetGroupName
//!@}

//!@doc Gets the index of the capture group with the given `name`, in the given compiled `regex`
/*!
**	@nonstd
**
**	@param	regex	The compiled regular expression to inspect
**	@param	name	The name of the capture group whose index should be returned
**	@returns
**	The index of the capture group with the given `name` (the first group is `1`),
**	or `ERROR` (`-1`) if no group with such a `name` exists.
*/
//!@{
t_sint					Regex_GetGroupIndex(s_regex const* regex, t_utf8 const* name);
#define c_reggroupindex	Regex_GetGroupIndex
//!@}



/*============================================================================*\
||                              Matching functions                            ||
\*============================================================================*/

//!@doc Attempts to match the given `regex` against `str`, anchored at the given byte `offset`
/*!
**	@nonstd
**
**	Unlike Regex_Search(), this function only attempts to match at the exact given `offset`
**	position (ie: the resulting match, if any, will always begin exactly at `str + offset`).
**
**	@param	regex		The compiled regular expression to match with
**	@param	str			The string to match against
**	@param	offset		The index (in bytes) of `str` at which the match attempt is anchored
**	@param	dest_match	(optional) if not `NULL`, is filled with the resulting match info
**							(in which case, RegexMatch_Delete() should later be called on it)
**	@returns
**	`TRUE` if the pattern matched at the given `offset` position, otherwise `FALSE`.
*/
//!@{
t_bool					Regex_Match(s_regex const* regex, t_utf8 const* str, t_size offset, s_regex_match* dest_match);
#define c_regmatch		Regex_Match
//!@}

//!@doc Searches for the first match of the given `regex` within `str`, at or after the given byte `offset`
/*!
**	@nonstd
**
**	@param	regex		The compiled regular expression to search with
**	@param	str			The string to search within
**	@param	offset		The index (in bytes) of `str` at which the search begins
**	@param	dest_match	(optional) if not `NULL`, is filled with the resulting match info
**							(in which case, RegexMatch_Delete() should later be called on it)
**	@returns
**	`TRUE` if a match was found anywhere at/after the given `offset` position, otherwise `FALSE`.
*/
//!@{
t_bool					Regex_Search(s_regex const* regex, t_utf8 const* str, t_size offset, s_regex_match* dest_match);
#define c_regsearch		Regex_Search
//!@}

//!@doc Checks whether the given `regex` matches anywhere within the given `str`
/*!
**	@nonstd
**
**	@param	regex	The compiled regular expression to search with
**	@param	str		The string to search within
**	@returns
**	`TRUE` if the pattern matches anywhere within `str`, otherwise `FALSE`.
*/
//!@{
t_bool					Regex_Matches(s_regex const* regex, t_utf8 const* str);
#define c_regmatches	Regex_Matches
//!@}

//!@doc Checks whether the given `regex` matches the entirety of the given `str`
/*!
**	@nonstd
**
**	@param	regex	The compiled regular expression to match with
**	@param	str		The string to match against
**	@returns
**	`TRUE` if the pattern matches the whole of `str` (from its very start to its very end),
**	otherwise `FALSE`.
*/
//!@{
t_bool					Regex_MatchEntire(s_regex const* regex, t_utf8 const* str);
#define c_regmatchall	Regex_MatchEntire
//!@}

//!@doc Finds every (non-overlapping) match of the given `regex` within `str`
/*!
**	@nonstd
**
**	@param	regex		The compiled regular expression to search with
**	@param	str			The string to search within
**	@param	dest_amount	(optional) if not `NULL`, is set to the amount of matches found
**	@returns
**	A newly allocated array of match info structs (one for each match found, in order),
**	or `NULL` if no match was found, or if an error occurred.
**	The result should later be freed by calling RegexMatch_Delete() on each item of the
**	array, and then freeing the array buffer itself.
*/
//!@{
s_regex_match*			Regex_SearchAll(s_regex const* regex, t_utf8 const* str, t_uint* dest_amount);
#define c_regsearchall	Regex_SearchAll
//!@}

//!@doc Deletes the contents of the given `match` struct (freeing its allocated `captures` array)
/*!
**	@nonstd
**
**	Note that this function does not free the given `match` struct pointer itself
**	(since match structs are typically stack-allocated by the caller):
**	it only frees the allocated `.captures` array within, and zeroes out the struct.
**
**	@param	match	The match struct whose contents should be deleted
*/
//!@{
void					RegexMatch_Delete(s_regex_match* match);
#define c_regmatchdel	RegexMatch_Delete
//!@}

//!@doc Gets a newly allocated copy of the region of `str` which was captured by the given capture group
/*!
**	@nonstd
**
**	@param	match	The match struct to read from (as filled by Regex_Match(), Regex_Search(), etc)
**	@param	index	The index of the capture group to get (`0` for the whole match, `1` for the first group, etc)
**	@param	str		The string which was searched (ie: the same string that produced this `match`)
**	@returns
**	A newly allocated string which duplicates the region captured by the given group,
**	or `NULL` if that group did not take part in the match (or if any error occurred).
*/
//!@{
t_utf8*					RegexMatch_GetCapture(s_regex_match const* match, t_uint index, t_utf8 const* str);
#define c_regcapture	RegexMatch_GetCapture
//!@}



/*============================================================================*\
||                              Replacing functions                           ||
\*============================================================================*/

//!@doc Replaces the first match of `regex` within `str`, with the given `replacement` string
/*!
**	@nonstd
**
**	The `replacement` string may contain special substitution sequences:
**	- `$0` or `\0`: is substituted with the whole match
**	- `$N` or `\N` (where `N` is a number from `1` to `99`): is substituted with the text captured by group `N`
**	- `${name}` or `$<name>`: is substituted with the text captured by the group named `name`
**	- `$$`: is substituted with a literal `$` character (likewise, `\\` gives a literal `\`)
**
**	@param	regex		The compiled regular expression to search with
**	@param	str			The string to search within
**	@param	replacement	The replacement string (with `$N` substitution sequences, see above)
**	@returns
**	A newly allocated string, in which the first match of `regex` has been replaced
**	(if no match was found, the result is simply a full copy of `str`),
**	or `NULL` if an error occurred.
*/
//!@{
t_utf8*					Regex_Replace(s_regex const* regex, t_utf8 const* str, t_utf8 const* replacement);
#define c_regreplace	Regex_Replace
//!@}

//!@doc Replaces every (non-overlapping) match of `regex` within `str`, with the given `replacement` string
/*!
**	@nonstd
**
**	The `replacement` string may contain special substitution sequences (see Regex_Replace()).
**
**	@param	regex		The compiled regular expression to search with
**	@param	str			The string to search within
**	@param	replacement	The replacement string (with `$N` substitution sequences)
**	@returns
**	A newly allocated string, in which every match of `regex` has been replaced
**	(if no match was found, the result is simply a full copy of `str`),
**	or `NULL` if an error occurred.
*/
//!@{
t_utf8*					Regex_ReplaceAll(s_regex const* regex, t_utf8 const* str, t_utf8 const* replacement);
#define c_regreplaceall	Regex_ReplaceAll
//!@}



/*============================================================================*\
||                              Splitting functions                           ||
\*============================================================================*/

//!@doc Splits the given `str` into several parts, using matches of `regex` as the delimiter
/*!
**	@nonstd
**
**	Note that, much like the String_Split() functions, empty parts are not included in
**	the result (ie: several consecutive delimiter matches are treated as one, and any
**	delimiter matches at the very start/end of `str` are simply skipped over).
**
**	@param	regex	The compiled regular expression to use as delimiter
**	@param	str		The string to split into parts
**	@returns
**	A newly allocated `NULL`-terminated array of newly allocated strings (ie: a stringarray,
**	which can be freed with StringArray_Delete()), holding each of the parts of `str`,
**	or `NULL` if an error occurred.
*/
//!@{
t_utf8**				Regex_Split(s_regex const* regex, t_utf8 const* str);
#define c_regsplit		Regex_Split
//!@}

#endif

/*! @endgroup */
HEADER_END
#endif
