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
#include <stdio.h>

// Declare stuff from Flex that Bison needs to know about:
extern int yylex();
extern int yyparse();
extern void yyerror(char const * s);
//extern FILE *yyin;
%}

%token	IDENTIFIER LITERAL_INT LITERAL_CHAR LITERAL_FLOAT LITERAL_STRING FUNC_NAME SIZEOF
%token	OP_PTR OP_INC OP_DEC OP_LEFT OP_RIGHT OP_LTE OP_GTE OP_EQ OP_NEQ
%token	OP_AND OP_OR OP_ASSIGN_MUL OP_ASSIGN_DIV OP_ASSIGN_MOD OP_ASSIGN_ADD
%token	OP_ASSIGN_SUB OP_ASSIGN_BITLEFT OP_ASSIGN_BITRIGHT OP_ASSIGN_BITAND
%token	OP_ASSIGN_BITXOR OP_ASSIGN_BITOR
%token	TYPEDEF_NAME ENUMERATION_CONSTANT

%token	TYPEDEF EXTERN STATIC AUTO REGISTER INLINE
%token	CONST RESTRICT VOLATILE
%token	BOOL CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE VOID
%token	COMPLEX IMAGINARY 
%token	STRUCT UNION ENUM ELLIPSIS

%token	CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%token	ALIGNAS ALIGNOF ATOMIC GENERIC NORETURN STATIC_ASSERT THREAD_LOCAL

%start translation_unit
%%

expression_primary
	: IDENTIFIER
	| constant
	| string
	| '(' expression ')'
	| generic_selection
	;

constant
	: LITERAL_INT
	| LITERAL_CHAR
	| LITERAL_FLOAT
	| ENUMERATION_CONSTANT	/* after it has been defined as such */
	;

enumeration_constant		/* before it has been defined as such */
	: IDENTIFIER
	;

string
	: LITERAL_STRING
	| FUNC_NAME
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
	| expression_shift OP_LEFT expression_additive
	| expression_shift OP_RIGHT expression_additive
	;

expression_relational
	: expression_shift
	| expression_relational '<' expression_shift
	| expression_relational '>' expression_shift
	| expression_relational OP_LTE expression_shift
	| expression_relational OP_GTE expression_shift
	;

expression_equality
	: expression_relational
	| expression_equality OP_EQ expression_relational
	| expression_equality OP_NEQ expression_relational
	;

expression_and
	: expression_equality
	| expression_and '&' expression_equality
	;

expression_exclusive_or
	: expression_and
	| expression_exclusive_or '^' expression_and
	;

expression_inclusive_or
	: expression_exclusive_or
	| expression_inclusive_or '|' expression_exclusive_or
	;

expression_logical_and
	: expression_inclusive_or
	| expression_logical_and OP_AND expression_inclusive_or
	;

expression_logical_or
	: expression_logical_and
	| expression_logical_or OP_OR expression_logical_and
	;

expression_conditional
	: expression_logical_or
	| expression_logical_or '?' expression ':' expression_conditional
	;

expression_assignment
	: expression_conditional
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
	: expression_conditional	/* with constraints */
	;

declaration
	: declaration_specifiers ';'
	| declaration_specifiers init_declarator_list ';'
	| static_assert_declaration
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

init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: declarator '=' initializer
	| declarator
	;

storage_class_specifier
	: TYPEDEF	/* identifiers must be flagged as TYPEDEF_NAME */
	| EXTERN
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
	| struct_or_union_specifier
	| enum_specifier
	| TYPEDEF_NAME		/* after it has been defined as such */
	;

struct_or_union_specifier
	: struct_or_union '{' struct_declaration_list '}'
	| struct_or_union IDENTIFIER '{' struct_declaration_list '}'
	| struct_or_union IDENTIFIER
	;

struct_or_union
	: STRUCT
	| UNION
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

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
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

enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM '{' enumerator_list ',' '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list ',' '}'
	| ENUM IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator	/* identifiers must be flagged as ENUMERATION_CONSTANT */
	: enumeration_constant '=' expression_constant
	| enumeration_constant
	;

atomic_type_specifier
	: ATOMIC '(' type_name ')'
	;

type_qualifier
	: CONST
	| RESTRICT
	| VOLATILE
	| ATOMIC
	;

function_specifier
	: INLINE
	| NORETURN
	;

alignment_specifier
	: ALIGNAS '(' type_name ')'
	| ALIGNAS '(' expression_constant ')'
	;

declarator
	: pointer direct_declarator
	| direct_declarator
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

pointer
	: '*' type_qualifier_list pointer
	| '*' type_qualifier_list
	| '*' pointer
	| '*'
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
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

abstract_declarator
	: pointer direct_abstract_declarator
	| pointer
	| direct_abstract_declarator
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

initializer
	: '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	| expression_assignment
	;

initializer_list
	: designation initializer
	| initializer
	| initializer_list ',' designation initializer
	| initializer_list ',' initializer
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

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: IDENTIFIER ':' statement
	| CASE expression_constant ':' statement
	| DEFAULT ':' statement
	;

compound_statement
	: '{' '}'
	| '{' block_item_list '}'
	;

block_item_list
	: block_item
	| block_item_list block_item
	;

block_item
	: declaration
	| statement
	;

expression_statement
	: ';'
	| expression ';'
	;

selection_statement
	: IF '(' expression ')' statement ELSE statement
	| IF '(' expression ')' statement
	| SWITCH '(' expression ')' statement
	;

iteration_statement
	: WHILE '(' expression ')' statement
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement
	| FOR '(' declaration expression_statement ')' statement
	| FOR '(' declaration expression_statement expression ')' statement
	;

jump_statement
	: GOTO IDENTIFIER ';'
	| CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expression ';'
	;

translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

%%
#include <stdio.h>

void yyerror(const char * s)
{
	fflush(stdout);
	fprintf(stderr, "*** %s\n", s);
}
