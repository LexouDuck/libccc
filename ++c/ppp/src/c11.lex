/*
**	ANSI C grammar, Lex specification
**	(This Lex file is accompanied by a matching Yacc file.)
**	In 1985, Jeff Lee published his Yacc grammar based on a draft version of the ANSI C standard, along with a supporting Lex specification.
**	Tom Stockfisch reposted those files to net.sources in 1987;
**	as mentioned in the answer to question 17.25 of the comp.lang.c FAQ,
**	they used to be available from ftp.uu.net as usenet/net.sources/ansi.c.grammar.Z.
**
**	The version you see here has been updated based on the 2011 ISO C standard.
**	(The previous version's Lex and Yacc files for ANSI C9X still exist as archived copies.)
**
**	It is assumed that translation phases 1..5 have already been completed, including preprocessing and _Pragma processing.
**	The Lex rule for string literals will perform concatenation (translation phase 6).
**	Transliteration of universal character names (\uHHHH or \UHHHHHHHH) must have been done by either the preprocessor,
**	or a replacement for the input() macro used by Lex (or the YY_INPUT function used by Flex) to read characters.
**	Although comments should have been changed to space characters during translation phase 3, there are Lex rules for them anyway.
**
**	I want to keep this version as close to the current C Standard grammar as possible; please let me know if you discover discrepancies.
**	(There is an FAQ for this grammar that you might want to read first.)
**
**	jutta@pobox.com, 2012
**
**	Last edit: 2012-12-19 DAGwyn@aol.com
*/

/*
	Note: The following %-parameters are the minimum sizes needed for real Lex.
	%e	number of parsed tree nodes
	%p	number of positions
	%n	number of states
	%k	number of packed character classes
	%a	number of transitions
	%o	size of output array
	%e	1019
	%p	2807
	%n	371
	%k	284
	%a	1213
	%o	1117
*/



digit_octal   [0-7]
digit         [0-9]
digit_nonzero [1-9]
digit_hex     [0-9a-fA-F]
char_alpha    [a-zA-Z_]
char_token    [a-zA-Z0-9_]
prefix_hex    (0[xX])
floatexp      ([Ee][+-]?{digit}+)
floatexp_hex  ([Pp][+-]?{digit}+)
suffix_float  (f|F|l|L)
suffix_int    (((u|U)(l|L|ll|LL)?)|((l|L|ll|LL)(u|U)?))
prefix_char   (u|U|L)
prefix_string (u8|u|U|L)
str_escape    (\\(['"\?\\abfnrtv]|[0-7]{1,3}|x[a-fA-F0-9]+))
whitespace    [ \t\v\n\f]

%{
#include <stdio.h>
#include "y.tab.h"

extern void yyerror(const char *);  /* prints grammar violation message */

extern int	c_sym_type(const char *);  /* returns type from symbol table */
#define c_sym_type(identifier) IDENTIFIER /* with no symbol table, fake it */

static void	c_comment(void);
static int	c_check_type(void);
%}

%%

 /* comments */
"/*"                    { c_comment(); }
"//".*                  { /* consume '//'-comment */ }

 /* C keywords */
"if"					{ return (IF); }
"else"					{ return (ELSE); }
"while"					{ return (WHILE); }
"for"					{ return (FOR); }
"do"					{ return (DO); }
"break"					{ return (BREAK); }
"continue"				{ return (CONTINUE); }
"goto"					{ return (GOTO); }
"switch"				{ return (SWITCH); }
"case"					{ return (CASE); }
"default"				{ return (DEFAULT); }
"return"				{ return (RETURN); }
 /* C keywords for decl options */
"inline"				{ return (INLINE); }
"static"				{ return (STATIC); }
"extern"				{ return (EXTERN); }
"volatile"				{ return (VOLATILE); }
 /* C keywords for type definition */
"typedef"				{ return (TYPEDEF); }
"struct"				{ return (STRUCT); }
"union"					{ return (UNION); }
"enum"					{ return (ENUM); }
 /* C primitive types */
"void"					{ return (VOID); }
"char"					{ return (CHAR); }
"short"					{ return (SHORT); }
"int"					{ return (INT); }
"long"					{ return (LONG); }
"float"					{ return (FLOAT); }
"double"				{ return (DOUBLE); }
 /* C type qualifiers */
"signed"				{ return (SIGNED); }
"unsigned"				{ return (UNSIGNED); }
"const"					{ return (CONST); }
"restrict"				{ return (RESTRICT); }
"auto"					{ return (AUTO); }
"register"				{ return (REGISTER); }
 /* C builtin operators */
"sizeof"				{ return (SIZEOF); }
 /* C99/C11 */
"_Alignas"              { return (ALIGNAS); }
"_Alignof"              { return (ALIGNOF); }
"_Atomic"               { return (ATOMIC); }
"_Bool"                 { return (BOOL); }
"_Complex"              { return (COMPLEX); }
"_Generic"              { return (GENERIC); }
"_Imaginary"            { return (IMAGINARY); }
"_Noreturn"             { return (NORETURN); }
"_Static_assert"        { return (STATIC_ASSERT); }
"_Thread_local"         { return (THREAD_LOCAL); }
"__func__"              { return (FUNC_NAME); }

{char_alpha}{char_token}*					{ return c_check_type(); }

{prefix_hex}{digit_hex}+{suffix_int}?				{ return (LITERAL_INT); }
{digit_nonzero}{digit}*{suffix_int}?				{ return (LITERAL_INT); }
"0"{digit_octal}*{suffix_int}?						{ return (LITERAL_INT); }

{prefix_char}?"'"([^'\\\n]|{str_escape})+"'"		{ return (LITERAL_CHAR); }

{digit}+{floatexp}{suffix_float}?										{ return (LITERAL_FLOAT); }
{digit}*"."{digit}+{floatexp}?{suffix_float}?							{ return (LITERAL_FLOAT); }
{digit}+"."{floatexp}?{suffix_float}?									{ return (LITERAL_FLOAT); }
{prefix_hex}{digit_hex}+{floatexp_hex}{suffix_float}?					{ return (LITERAL_FLOAT); }
{prefix_hex}{digit_hex}*"."{digit_hex}+{floatexp_hex}{suffix_float}?	{ return (LITERAL_FLOAT); }
{prefix_hex}{digit_hex}+"."{floatexp_hex}{suffix_float}?				{ return (LITERAL_FLOAT); }

({prefix_string}?\"([^"\\\n]|{str_escape})*\"{whitespace}*)+	{ return (LITERAL_STRING); }

"..."				{ return (ELLIPSIS); }

">>="				{ return (OP_ASSIGN_BITRIGHT); }
"<<="				{ return (OP_ASSIGN_BITLEFT); }
"+="				{ return (OP_ASSIGN_ADD); }
"-="				{ return (OP_ASSIGN_SUB); }
"*="				{ return (OP_ASSIGN_MUL); }
"/="				{ return (OP_ASSIGN_DIV); }
"%="				{ return (OP_ASSIGN_MOD); }
"&="				{ return (OP_ASSIGN_BITAND); }
"^="				{ return (OP_ASSIGN_BITXOR); }
"|="				{ return (OP_ASSIGN_BITOR); }
">>"				{ return (OP_RIGHT); }
"<<"				{ return (OP_LEFT); }
"++"				{ return (OP_INC); }
"--"				{ return (OP_DEC); }
"->"				{ return (OP_PTR); }
"&&"				{ return (OP_AND); }
"||"				{ return (OP_OR); }
"<="				{ return (OP_LTE); }
">="				{ return (OP_GTE); }
"=="				{ return (OP_EQ); }
"!="				{ return (OP_NEQ); }
";"					{ return (';'); }
("{"|"<%")			{ return ('{'); }
("}"|"%>")			{ return ('}'); }
","					{ return (','); }
":"					{ return (':'); }
"="					{ return ('='); }
"("					{ return ('('); }
")"					{ return (')'); }
("["|"<:")			{ return ('['); }
("]"|":>")			{ return (']'); }
"."					{ return ('.'); }
"&"					{ return ('&'); }
"!"					{ return ('!'); }
"~"					{ return ('~'); }
"-"					{ return ('-'); }
"+"					{ return ('+'); }
"*"					{ return ('*'); }
"/"					{ return ('/'); }
"%"					{ return ('%'); }
"<"					{ return ('<'); }
">"					{ return ('>'); }
"^"					{ return ('^'); }
"|"					{ return ('|'); }
"?"					{ return ('?'); }

{whitespace}+		{ /* whitespace separates tokens */ }
.					{ /* discard bad characters */ }

%%

int yywrap(void)        /* called at end of input */
{
	return 1;           /* terminate now */
}

static void c_comment(void)
{
	int c;

	while ((c = input()) != 0)
	{
		if (c == '*')
		{
			while ((c = input()) == '*')
			{}
			if (c == '/')
				return;
			if (c == 0)
				break;
		}
	}
	yyerror("unterminated comment");
}

static int c_check_type(void)
{
	switch (c_sym_type(yytext))
	{
	case TYPEDEF_NAME:                /* previously defined */
		return TYPEDEF_NAME;
	case ENUMERATION_CONSTANT:        /* previously defined */
		return ENUMERATION_CONSTANT;
	default:                          /* includes undefined */
		return IDENTIFIER;
	}
}
