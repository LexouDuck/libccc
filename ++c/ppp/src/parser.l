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

%{

#include "ppp.h"

extern void yyerror(const char *);  /* prints grammar violation message */

%}

%option yylineno



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
preprocessor  (\n[ \t]*#[ \t]*)
whitespace    [ \t\v\n\f]

%%

 /* comments */
"/*"((.*)?)*"*/"     { ppp_comment_block(yytext); }
"/*"((.*)?)*         { ppp_error("unterminated comment block"); }
"//"((.*)?)*"\n"     { ppp_comment_line(yytext); }
"//"((.*)?)*         { ppp_error("unterminated comment line: no newline at end of file"); }

 /* C preprocessor */
{preprocessor}"if"		{ return ppp_verbatim(yytext, PP_IF); }
{preprocessor}"elif"	{ return ppp_verbatim(yytext, PP_ELIF); }
{preprocessor}"else"	{ return ppp_verbatim(yytext, PP_ELSE); }
{preprocessor}"endif"	{ return ppp_verbatim(yytext, PP_ENDIF); }
{preprocessor}"ifdef"	{ return ppp_verbatim(yytext, PP_IFDEF); }
{preprocessor}"ifndef"	{ return ppp_verbatim(yytext, PP_IFNDEF); }
{preprocessor}"line"	{ return ppp_verbatim(yytext, PP_LINE); }
{preprocessor}"define"	{ return ppp_verbatim(yytext, PP_DEFINE); }
{preprocessor}"include"	{ return ppp_verbatim(yytext, PP_INCLUDE); }
{preprocessor}"error"	{ return ppp_verbatim(yytext, PP_ERROR); }
{preprocessor}"warning"	{ return ppp_verbatim(yytext, PP_WARNING); }
{preprocessor}"pragma"	{ return ppp_verbatim(yytext, PP_PRAGMA); }

 /* C keywords */
"if"					{ return ppp_verbatim(yytext, IF); }
"else"					{ return ppp_verbatim(yytext, ELSE); }
"while"					{ return ppp_verbatim(yytext, WHILE); }
"for"					{ return ppp_verbatim(yytext, FOR); }
"do"					{ return ppp_verbatim(yytext, DO); }
"break"					{ return ppp_verbatim(yytext, BREAK); }
"continue"				{ return ppp_verbatim(yytext, CONTINUE); }
"goto"					{ return ppp_verbatim(yytext, GOTO); }
"switch"				{ return ppp_verbatim(yytext, SWITCH); }
"case"					{ return ppp_verbatim(yytext, CASE); }
"default"				{ return ppp_verbatim(yytext, DEFAULT); }
"return"				{ return ppp_verbatim(yytext, RETURN); }
 /* C keywords: storage class specifiers */
"auto"					{ return ppp_verbatim(yytext, AUTO); }
"register"				{ return ppp_verbatim(yytext, REGISTER); }
"static"				{ return ppp_verbatim(yytext, STATIC); }
"extern"				{ return ppp_verbatim(yytext, EXTERN); }
"inline"				{ return ppp_verbatim(yytext, INLINE); }
 /* C keywords: type qualifiers */
"signed"				{ return ppp_verbatim(yytext, SIGNED); }
"unsigned"				{ return ppp_verbatim(yytext, UNSIGNED); }
"const"					{ return ppp_verbatim(yytext, CONST); }
"restrict"				{ return ppp_verbatim(yytext, RESTRICT); }
"volatile"				{ return ppp_verbatim(yytext, VOLATILE); }
 /* C keywords: type definitions */
"typedef"				{ return ppp_verbatim(yytext, TYPEDEF); }
"struct"				{ return ppp_verbatim(yytext, STRUCT); }
"union"					{ return ppp_verbatim(yytext, UNION); }
"enum"					{ return ppp_verbatim(yytext, ENUM); }
 /* C primitive types */
"void"					{ return ppp_verbatim(yytext, VOID); }
"char"					{ return ppp_verbatim(yytext, CHAR); }
"short"					{ return ppp_verbatim(yytext, SHORT); }
"int"					{ return ppp_verbatim(yytext, INT); }
"long"					{ return ppp_verbatim(yytext, LONG); }
"float"					{ return ppp_verbatim(yytext, FLOAT); }
"double"				{ return ppp_verbatim(yytext, DOUBLE); }
 /* C builtin operators */
"sizeof"				{ return ppp_verbatim(yytext, SIZEOF); }
 /* C99/C11 */
"_Alignas"              { return ppp_verbatim(yytext, ALIGNAS); }
"_Alignof"              { return ppp_verbatim(yytext, ALIGNOF); }
"_Atomic"               { return ppp_verbatim(yytext, ATOMIC); }
"_Bool"                 { return ppp_verbatim(yytext, BOOL); }
"_Complex"              { return ppp_verbatim(yytext, COMPLEX); }
"_Generic"              { return ppp_verbatim(yytext, GENERIC); }
"_Imaginary"            { return ppp_verbatim(yytext, IMAGINARY); }
"_Noreturn"             { return ppp_verbatim(yytext, NORETURN); }
"_Static_assert"        { return ppp_verbatim(yytext, STATIC_ASSERT); }
"_Thread_local"         { return ppp_verbatim(yytext, THREAD_LOCAL); }

{char_alpha}{char_token}*		{ return ppp_symbol(yytext); }

{prefix_hex}{digit_hex}+{suffix_int}?									{ return ppp_verbatim(yytext, LITERAL_INT); }
{digit_nonzero}{digit}*{suffix_int}?									{ return ppp_verbatim(yytext, LITERAL_INT); }
"0"{digit_octal}*{suffix_int}?											{ return ppp_verbatim(yytext, LITERAL_INT); }

{prefix_char}?"'"([^'\\\n]|{str_escape})+"'"							{ return ppp_verbatim(yytext, LITERAL_CHAR); }

{digit}+{floatexp}{suffix_float}?										{ return ppp_verbatim(yytext, LITERAL_FLOAT); }
{digit}*"."{digit}+{floatexp}?{suffix_float}?							{ return ppp_verbatim(yytext, LITERAL_FLOAT); }
{digit}+"."{floatexp}?{suffix_float}?									{ return ppp_verbatim(yytext, LITERAL_FLOAT); }
{prefix_hex}{digit_hex}+{floatexp_hex}{suffix_float}?					{ return ppp_verbatim(yytext, LITERAL_FLOAT); }
{prefix_hex}{digit_hex}*"."{digit_hex}+{floatexp_hex}{suffix_float}?	{ return ppp_verbatim(yytext, LITERAL_FLOAT); }
{prefix_hex}{digit_hex}+"."{floatexp_hex}{suffix_float}?				{ return ppp_verbatim(yytext, LITERAL_FLOAT); }

({prefix_string}?\"([^"\\\n]|{str_escape})*\"{whitespace}*)+			{ return ppp_verbatim(yytext, LITERAL_STRING); }

(<([^>\\\n]|{str_escape})*>)											{ return ppp_verbatim(yytext, PP_STRING); }
 /* [ \t]+[^\n]*														{ return (PP); } */

"..."				{ return ppp_verbatim(yytext, ELLIPSIS); }

">>="				{ return ppp_verbatim(yytext, OP_ASSIGN_BITRIGHT); }
"<<="				{ return ppp_verbatim(yytext, OP_ASSIGN_BITLEFT); }
"+="				{ return ppp_verbatim(yytext, OP_ASSIGN_ADD); }
"-="				{ return ppp_verbatim(yytext, OP_ASSIGN_SUB); }
"*="				{ return ppp_verbatim(yytext, OP_ASSIGN_MUL); }
"/="				{ return ppp_verbatim(yytext, OP_ASSIGN_DIV); }
"%="				{ return ppp_verbatim(yytext, OP_ASSIGN_MOD); }
"&="				{ return ppp_verbatim(yytext, OP_ASSIGN_BITAND); }
"^="				{ return ppp_verbatim(yytext, OP_ASSIGN_BITXOR); }
"|="				{ return ppp_verbatim(yytext, OP_ASSIGN_BITOR); }
">>"				{ return ppp_verbatim(yytext, OP_BITRIGHT); }
"<<"				{ return ppp_verbatim(yytext, OP_BITLEFT); }
"++"				{ return ppp_verbatim(yytext, OP_INC); }
"--"				{ return ppp_verbatim(yytext, OP_DEC); }
"->"				{ return ppp_verbatim(yytext, OP_PTR); }
"&&"				{ return ppp_verbatim(yytext, OP_AND); }
"||"				{ return ppp_verbatim(yytext, OP_OR); }
"<="				{ return ppp_verbatim(yytext, OP_LTE); }
">="				{ return ppp_verbatim(yytext, OP_GTE); }
"=="				{ return ppp_verbatim(yytext, OP_EQ); }
"!="				{ return ppp_verbatim(yytext, OP_NEQ); }
";"					{ return ppp_verbatim(yytext, ';'); }
("{"|"<%")			{ return ppp_verbatim(yytext, '{'); }
("}"|"%>")			{ return ppp_verbatim(yytext, '}'); }
","					{ return ppp_verbatim(yytext, ','); }
":"					{ return ppp_verbatim(yytext, ':'); }
"="					{ return ppp_verbatim(yytext, '='); }
"("					{ return ppp_verbatim(yytext, '('); }
")"					{ return ppp_verbatim(yytext, ')'); }
("["|"<:")			{ return ppp_verbatim(yytext, '['); }
("]"|":>")			{ return ppp_verbatim(yytext, ']'); }
"."					{ return ppp_verbatim(yytext, '.'); }
"&"					{ return ppp_verbatim(yytext, '&'); }
"!"					{ return ppp_verbatim(yytext, '!'); }
"~"					{ return ppp_verbatim(yytext, '~'); }
"-"					{ return ppp_verbatim(yytext, '-'); }
"+"					{ return ppp_verbatim(yytext, '+'); }
"*"					{ return ppp_verbatim(yytext, '*'); }
"/"					{ return ppp_verbatim(yytext, '/'); }
"%"					{ return ppp_verbatim(yytext, '%'); }
"<"					{ return ppp_verbatim(yytext, '<'); }
">"					{ return ppp_verbatim(yytext, '>'); }
"^"					{ return ppp_verbatim(yytext, '^'); }
"|"					{ return ppp_verbatim(yytext, '|'); }
"?"					{ return ppp_verbatim(yytext, '?'); }

"\n"				{ return ppp_verbatim(yytext, '\n'); }
{whitespace}+		{ ppp_whitespace(yytext); }
.					{ ppp_error("syntax error, unexpected character: '%s'", yytext); }

%%

int yywrap(void)        /* called at end of input */
{
	return ppp_exit(); /* terminate now */
}
