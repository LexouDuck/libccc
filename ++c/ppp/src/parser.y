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
	Note: There are two shift/reduce conflicts, correctly resolved by default:
		IF '(' expression ')' statement _ ELSE statement
	and
		ATOMIC _ '(' type_name ')'
	where "_" has been used to flag the points of ambiguity.
*/

%{

#include "ppp.h"

int yydebug = 1;

%}

%error-verbose

%locations

%token	PP PP_SPACE PP_NEWLINE /* basic macro infrastructure */
%token	PP_CONTENT PP_STRING /* raw macro contents */
%token	PP_IF PP_ELIF PP_ELSE PP_ENDIF
%token	PP_IFDEF PP_IFNDEF
%token	PP_UNDEF PP_DEFINE
%token	PP_ERROR PP_WARNING
%token	PP_INCLUDE
%token	PP_PRAGMA
%token	PP_LINE

%token	IDENTIFIER /* new, as-of-yet-unknown symbol */
%token	LITERAL_INT LITERAL_FLOAT
%token	LITERAL_CHAR LITERAL_STRING
%token	LITERAL_ENUM
%token	NAME_MACRO
%token	NAME_TYPEDEF
%token	NAME_STRUCT
%token	NAME_UNION
%token	NAME_ENUM

%token	IF ELSE
%token	WHILE DO FOR
%token	RETURN GOTO CONTINUE BREAK
%token	SWITCH CASE DEFAULT

%token	SIZEOF
%token	ALIGNOF
%token	OP_PTR
%token	OP_INC OP_DEC
%token	OP_BITLEFT OP_BITRIGHT
%token	OP_AND OP_OR
%token	OP_LT OP_GT OP_LTE OP_GTE OP_EQ OP_NEQ
%token	OP_ASSIGN_MUL OP_ASSIGN_DIV OP_ASSIGN_MOD OP_ASSIGN_ADD OP_ASSIGN_SUB
%token	OP_ASSIGN_BITLEFT OP_ASSIGN_BITRIGHT
%token	OP_ASSIGN_BITAND OP_ASSIGN_BITXOR OP_ASSIGN_BITOR

%token	TYPEDEF
%token	EXTERN STATIC AUTO REGISTER INLINE
%token	CONST RESTRICT VOLATILE
%token	SIGNED UNSIGNED
%token	VOID BOOL CHAR SHORT INT LONG FLOAT DOUBLE
%token	COMPLEX IMAGINARY 
%token	STRUCT UNION ENUM
%token	ELLIPSIS

%token	ATOMIC
%token	ALIGNAS
%token	NORETURN
%token	THREAD_LOCAL
%token	GENERIC
%token	STATIC_ASSERT



/* Yacc's YYSTYPE Union
	The yacc parser maintains a stack (array) of token values while it is parsing.
	This union defines all the possible values that tokens may have.
	Yacc creates a typedef named `YYSTYPE` for this union.
	All token types (see %type declarations below) are taken from the field names of this union.
	The global variable `yylval` which lex uses to return token values is declared as a `YYSTYPE` union.
*/
%union
{
	int		v_int;
	float	v_float;
	char*	v_str;
	char**	v_strarr;
};

%type<v_str> PP_SPACE
%type<v_str> PP_NEWLINE
%type<v_str> PP_CONTENT
%type<v_str> PP_STRING
%type<v_str> LITERAL_INT
%type<v_str> LITERAL_FLOAT
%type<v_str> LITERAL_CHAR
%type<v_str> LITERAL_STRING
%type<v_str> LITERAL_ENUM
%type<v_str> IDENTIFIER
%type<v_str> NAME_MACRO
%type<v_str> NAME_TYPEDEF
%type<v_str> NAME_STRUCT
%type<v_str> NAME_UNION
%type<v_str> NAME_ENUM

%type<v_str> preprocessor_content
%nterm<v_strarr> preprocessor_define_args

%type <v_str> declaration_specifiers
%type <v_str> declarator_list



%start translation_unit

%%



/* C preprocessor */

preprocessor_content
	: PP_CONTENT
	| LITERAL_INT
	| LITERAL_FLOAT
	| LITERAL_CHAR
	| LITERAL_STRING
	| LITERAL_ENUM
	;

preprocessor
	: PP preprocessor_conditional  '\n'
	| PP preprocessor_undefine     '\n'
	| PP preprocessor_define       '\n'
	| PP preprocessor_include      '\n'
	| PP preprocessor_line         '\n'
	;

preprocessor_conditional
	: PP_IF   preprocessor_content  {}
	| PP_ELIF preprocessor_content  {}
	| PP_ELSE                       {}
	| PP_ENDIF                      {}
	| PP_IFDEF  PP_SPACE IDENTIFIER {}
	| PP_IFNDEF PP_SPACE IDENTIFIER {}
	;

preprocessor_undefine
	: PP_UNDEF PP_SPACE IDENTIFIER  { ppp_removesymbol(macro, $3); }
	;

preprocessor_define
	: PP_DEFINE PP_SPACE IDENTIFIER                                                        { ppp_addsymbol(macro, { .name=c_strdup($3), });                                                         ppp_warning("DEBUG { .name=\"%s\", }",                            c_strdup($3)); }
	| PP_DEFINE PP_SPACE IDENTIFIER PP_SPACE                                               { ppp_addsymbol(macro, { .name=c_strdup($3), });                                                         ppp_warning("DEBUG { .name=\"%s\", } SPACE",                      c_strdup($3)); }
	| PP_DEFINE PP_SPACE IDENTIFIER PP_SPACE preprocessor_content                          { ppp_addsymbol(macro, { .name=c_strdup($3), .text=c_strdup($5) });                                      ppp_warning("DEBUG { .name=\"%s\", .text=\"%s\" }",               c_strdup($3), c_strdup($5)); }
	| PP_DEFINE PP_SPACE IDENTIFIER '(' preprocessor_define_args ')'                       { ppp_addsymbol(macro, { .name=c_strdup($3), .args=c_strarrdup((char const**)$5) });                     ppp_warning("DEBUG { .name=\"%s\", .args=\"%s\" }",               c_strdup($3), c_strarrdup((char const**)$5)); }
	| PP_DEFINE PP_SPACE IDENTIFIER '(' preprocessor_define_args ')' preprocessor_content  { ppp_addsymbol(macro, { .name=c_strdup($3), .args=c_strarrdup((char const**)$5), .text=c_strdup($7) }); ppp_warning("DEBUG { .name=\"%s\", .args=\"%s\", .text=\"%s\" }", c_strdup($3), c_strarrdup((char const**)$5), c_strdup($7)); }
	;

preprocessor_define_args
	: IDENTIFIER                                { ppp_message("parameter list begin: %s", $1); $$ = c_strarrcreate(1, c_strdup($1)); }
	| preprocessor_define_args ',' IDENTIFIER   { ppp_message("parameter list next:: %s", $3); $$ = c_strarrappend(&($1), (char const*[2]){ c_strdup($3), NULL }); }
	;

preprocessor_include
	: PP_INCLUDE PP_STRING                { ppp_message("includes file: %s", ($2)); /* TODO */ }
	| PP_INCLUDE LITERAL_STRING           { ppp_message("includes file: %s", ($2)); /* TODO */ }
	| PP_INCLUDE PP_SPACE PP_STRING       { ppp_message("includes file: %s", ($3)); /* TODO */ }
	| PP_INCLUDE PP_SPACE LITERAL_STRING  { ppp_message("includes file: %s", ($3)); /* TODO */ }
	;

preprocessor_line
	: PP_LINE                                           {}
	| PP_LINE PP_SPACE                                  {}
	| PP_LINE PP_SPACE constant                         {}
	| PP_LINE PP_SPACE constant PP_SPACE PP_STRING      {}
	| PP_LINE PP_SPACE constant PP_SPACE LITERAL_STRING {}
	;



/* C language */

constant
	: LITERAL_INT
	| LITERAL_CHAR
	| LITERAL_FLOAT
	| LITERAL_ENUM	/* after it has been defined as such */
	;

string
	: LITERAL_STRING
	;

expression_primary
	: IDENTIFIER
	| constant
	| string
	| '(' expression ')'
	| generic_selection
	;

expression_postfix
	: expression_primary
	| expression_postfix '[' expression ']'
	| expression_postfix '(' ')'
	| expression_postfix '(' argument_expression_list ')'
	| expression_postfix '.' IDENTIFIER
	| expression_postfix OP_PTR IDENTIFIER
	| expression_postfix OP_INC
	| expression_postfix OP_DEC
	| '(' type_name ')' '{' initializer_list '}'
	| '(' type_name ')' '{' initializer_list ',' '}'
	;

argument_expression_list
	: expression_assignment
	| argument_expression_list ',' expression_assignment
	;

expression_unary
	: expression_postfix
	| OP_INC expression_unary
	| OP_DEC expression_unary
	| unary_operator expression_cast
	| SIZEOF expression_unary
	| SIZEOF '(' type_name ')'
	| ALIGNOF '(' type_name ')'
	;

unary_operator
	: '&'
	| '*'
	| '+'
	| '-'
	| '~'
	| '!'
	;

expression_cast
	: expression_unary
	| '(' type_name ')' expression_cast
	;

expression_multiplicative
	: expression_cast
	| expression_multiplicative '*' expression_cast
	| expression_multiplicative '/' expression_cast
	| expression_multiplicative '%' expression_cast
	;

expression_additive
	: expression_multiplicative
	| expression_additive '+' expression_multiplicative
	| expression_additive '-' expression_multiplicative
	;

expression_shift
	: expression_additive
	| expression_shift OP_BITLEFT expression_additive
	| expression_shift OP_BITRIGHT expression_additive
	;

expression_relational
	: expression_shift
	| expression_relational OP_LT expression_shift
	| expression_relational OP_GT expression_shift
	| expression_relational OP_LTE expression_shift
	| expression_relational OP_GTE expression_shift
	;

expression_equality
	: expression_relational
	| expression_equality OP_EQ expression_relational
	| expression_equality OP_NEQ expression_relational
	;

expression_bitwise_and
	: expression_equality
	| expression_bitwise_and '&' expression_equality
	;

expression_bitwise_xor
	: expression_bitwise_and
	| expression_bitwise_xor '^' expression_bitwise_and
	;

expression_bitwise_or
	: expression_bitwise_xor
	| expression_bitwise_or '|' expression_bitwise_xor
	;

expression_logical_and
	: expression_bitwise_or
	| expression_logical_and OP_AND expression_bitwise_or
	;

expression_logical_or
	: expression_logical_and
	| expression_logical_or OP_OR expression_logical_and
	;

expression_ternary
	: expression_logical_or
	| expression_logical_or '?' expression ':' expression_ternary
	;

expression_assignment
	: expression_ternary
	| expression_unary assignment_operator expression_assignment
	;

assignment_operator
	: '='
	| OP_ASSIGN_MUL
	| OP_ASSIGN_DIV
	| OP_ASSIGN_MOD
	| OP_ASSIGN_ADD
	| OP_ASSIGN_SUB
	| OP_ASSIGN_BITLEFT
	| OP_ASSIGN_BITRIGHT
	| OP_ASSIGN_BITAND
	| OP_ASSIGN_BITXOR
	| OP_ASSIGN_BITOR
	;

expression
	: expression_assignment
	| expression ',' expression_assignment
	;

expression_constant
	: expression_ternary	/* with constraints */
	;



storage_class_specifier
	: EXTERN
	| STATIC
	| THREAD_LOCAL
	| AUTO
	| REGISTER
	;

type_specifier
	: VOID
	| CHAR
	| SHORT
	| INT
	| LONG
	| FLOAT
	| DOUBLE
	| SIGNED
	| UNSIGNED
	| BOOL
	| COMPLEX
	| IMAGINARY	  	/* non-mandated extension */
	| atomic_type_specifier
	| struct_specifier
	| union_specifier
	| enum_specifier
	| NAME_TYPEDEF		/* after it has been defined as such */
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;



struct_specifier
	: STRUCT '{' struct_declaration_list '}'			{ ppp_addsymbol(struct,{ .name=c_strdup("") }); }
	| STRUCT IDENTIFIER '{' struct_declaration_list '}'	{ ppp_addsymbol(struct,{ .name=c_strdup($2) }); }
	| STRUCT IDENTIFIER									{ ppp_addsymbol(struct,{ .name=c_strdup($2) }); }
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: specifier_qualifier_list ';'	/* for anonymous struct/union */
	| specifier_qualifier_list struct_declarator_list ';'
	| static_assert_declaration
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;
struct_declarator
	: ':' expression_constant
	| declarator ':' expression_constant
	| declarator
	;



union_specifier
	: UNION '{' struct_declaration_list '}'				{ ppp_addsymbol(union,{ .name=c_strdup("") }); }
	| UNION IDENTIFIER '{' struct_declaration_list '}'	{ ppp_addsymbol(union,{ .name=c_strdup($2) }); }
	| UNION IDENTIFIER									{ ppp_addsymbol(union,{ .name=c_strdup($2) }); }
	;



enum_specifier
	: ENUM '{' enumerator_list '}'					{ ppp_addsymbol(enum,{ .name=c_strdup("") }); }
	| ENUM '{' enumerator_list ',' '}'				{ ppp_addsymbol(enum,{ .name=c_strdup("") }); }
	| ENUM IDENTIFIER '{' enumerator_list '}'		{ ppp_addsymbol(enum,{ .name=c_strdup($2) }); }
	| ENUM IDENTIFIER '{' enumerator_list ',' '}'	{ ppp_addsymbol(enum,{ .name=c_strdup($2) }); }
	| ENUM IDENTIFIER								{ ppp_addsymbol(enum,{ .name=c_strdup($2) }); }
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;
enumerator	/* identifiers must be flagged as LITERAL_ENUM */
	: IDENTIFIER '=' expression_constant
	| IDENTIFIER
	;



generic_selection
	: GENERIC '(' expression_assignment ',' generic_assoc_list ')'
	;

generic_assoc_list
	: generic_association
	| generic_assoc_list ',' generic_association
	;

generic_association
	: type_name ':' expression_assignment
	| DEFAULT ':' expression_assignment
	;

atomic_type_specifier
	: ATOMIC '(' type_name ')'
	;

function_specifier
	: INLINE
	| NORETURN
	;

alignment_specifier
	: ALIGNAS '(' type_name ')'
	| ALIGNAS '(' expression_constant ')'
	;


parameter_type_list
	: parameter_list ',' ELLIPSIS
	| parameter_list
	;

parameter_list
	: parameter_declaration
	| parameter_list ',' parameter_declaration
	;
parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;



identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
	;

type_name
	: specifier_qualifier_list abstract_declarator
	| specifier_qualifier_list
	;



initializer_list
	: designation initializer
	| initializer
	| initializer_list ',' designation initializer
	| initializer_list ',' initializer
	;
initializer
	: '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	| expression_assignment
	;

designation
	: designator_list '='
	;

designator_list
	: designator
	| designator_list designator
	;
designator
	: '[' expression_constant ']'
	| '.' IDENTIFIER
	;

static_assert_declaration
	: STATIC_ASSERT '(' expression_constant ',' LITERAL_STRING ')' ';'
	;



labeled_statement
	: IDENTIFIER ':' statement
	| CASE expression_constant ':' statement
	| DEFAULT ':' statement
	;

statement_expression
	: ';'
	| expression ';'
	;

statement_condition
	: IF '(' expression ')' statement ELSE statement
	| IF '(' expression ')' statement
	| SWITCH '(' expression ')' statement
	;

statement_iteration
	: WHILE '(' expression ')' statement
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' statement_expression statement_expression ')' statement
	| FOR '(' statement_expression statement_expression expression ')' statement
	| FOR '(' declaration statement_expression ')' statement
	| FOR '(' declaration statement_expression expression ')' statement
	;

statement_jump
	: GOTO IDENTIFIER ';'
	| CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expression ';'
	;

statement
	: labeled_statement
	| compound_statement
	| statement_expression
	| statement_condition
	| statement_iteration
	| statement_jump
	;



block_item_list
	: block_item
	| block_item_list block_item
	;
block_item
	: declaration
	| statement
	;

compound_statement
	: '{' '}'
	| '{' block_item_list '}'
	;



type_qualifier
	: CONST
	| RESTRICT
	| VOLATILE
	| ATOMIC
	;
type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;

pointer
	: '*' type_qualifier_list pointer
	| '*' type_qualifier_list
	| '*' pointer
	| '*'
	;



direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' '*' ']'
	| '[' STATIC type_qualifier_list expression_assignment ']'
	| '[' STATIC expression_assignment ']'
	| '[' type_qualifier_list STATIC expression_assignment ']'
	| '[' type_qualifier_list expression_assignment ']'
	| '[' type_qualifier_list ']'
	| '[' expression_assignment ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' '*' ']'
	| direct_abstract_declarator '[' STATIC type_qualifier_list expression_assignment ']'
	| direct_abstract_declarator '[' STATIC expression_assignment ']'
	| direct_abstract_declarator '[' type_qualifier_list expression_assignment ']'
	| direct_abstract_declarator '[' type_qualifier_list STATIC expression_assignment ']'
	| direct_abstract_declarator '[' type_qualifier_list ']'
	| direct_abstract_declarator '[' expression_assignment ']'
	| '(' ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	;

abstract_declarator
	: pointer direct_abstract_declarator
	| pointer
	| direct_abstract_declarator
	;

direct_declarator
	: IDENTIFIER
	| '(' declarator ')'
	| direct_declarator '[' ']'
	| direct_declarator '[' '*' ']'
	| direct_declarator '[' STATIC type_qualifier_list expression_assignment ']'
	| direct_declarator '[' STATIC expression_assignment ']'
	| direct_declarator '[' type_qualifier_list '*' ']'
	| direct_declarator '[' type_qualifier_list STATIC expression_assignment ']'
	| direct_declarator '[' type_qualifier_list expression_assignment ']'
	| direct_declarator '[' type_qualifier_list ']'
	| direct_declarator '[' expression_assignment ']'
	| direct_declarator '(' parameter_type_list ')'
	| direct_declarator '(' ')'
	| direct_declarator '(' identifier_list ')'
	;



declarator_list
	: declarator
	| declarator_list ',' declarator
	;
declarator
	: pointer direct_declarator
	| direct_declarator
	;



declarator_initializer_list
	: declarator_initializer
	| declarator_initializer_list ',' declarator_initializer
	;
declarator_initializer
	: declarator '=' initializer
	| declarator
	;



declaration_specifiers
	: storage_class_specifier declaration_specifiers
	| storage_class_specifier
	| type_specifier declaration_specifiers
	| type_specifier
	| type_qualifier declaration_specifiers
	| type_qualifier
	| function_specifier declaration_specifiers
	| function_specifier
	| alignment_specifier declaration_specifiers
	| alignment_specifier
	;

declaration
	: TYPEDEF declaration_specifiers declarator_list ';'	{ ppp_addsymbol(type,{ .name=c_strdup($3), .type=c_strdup($2) }); }
	| declaration_specifiers ';'
	| declaration_specifiers declarator_initializer_list ';'
	| static_assert_declaration
	;
declaration_list
	: declaration
	| declaration_list declaration
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement
	;

external_declaration
	: function_definition
	| declaration
	| preprocessor
	;

translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

%%

void yyerror(char const* str)
{
	ppp_error("%s", str);
}
