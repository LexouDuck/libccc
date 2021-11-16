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



/* Yacc's YYSTYPE Union
	The yacc parser maintains a stack (array) of token values while
	it is parsing.  This union defines all the possible values tokens
	may have.  Yacc creates a typedef of YYSTYPE for this union. All
	token types (see %type declarations below) are taken from
	the field names of this union.  The global variable yylval which lex
	uses to return token values is declared as a YYSTYPE union.
*/

//%union
//{
//	long int4;              /* Constant integer value */
//	float fp;               /* Constant floating point value */
//	char *str;              /* Ptr to constant string (strings are malloc'd) */
//	exprT expr;             /* Expression -  constant or address */
//	operatorT *operatorP;   /* Pointer to run-time expression operator */
//};
//
//%type <str> SYMBOL


%{

#include "ppp.h"

%}

%error-verbose

%locations

%token	PP PP_STRING
%token	PP_IF PP_ELIF PP_ELSE PP_ENDIF
%token	PP_IFDEF PP_IFNDEF
%token	PP_UNDEF PP_DEFINE
%token	PP_INCLUDE
%token	PP_LINE

%token	MACRO_NAME
%token	IDENTIFIER
%token	LITERAL_INT LITERAL_FLOAT
%token	LITERAL_CHAR LITERAL_STRING
%token	LITERAL_ENUM
%token	TYPEDEF_NAME

%token	SIZEOF
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

%token	IF ELSE
%token	WHILE DO FOR
%token	RETURN GOTO CONTINUE BREAK
%token	SWITCH CASE DEFAULT

%token	ALIGNAS ALIGNOF
%token	NORETURN
%token	ATOMIC THREAD_LOCAL
%token	GENERIC
%token	STATIC_ASSERT

%start translation_unit

%%



/* C preprocessor */

preprocessor
	: preprocessor_conditional
	| preprocessor_define
	| preprocessor_undefine
	| preprocessor_include
	| preprocessor_line
	;

preprocessor_conditional
	: PP_IF   PP '\n'
	| PP_ELIF PP '\n'
	| PP_ELSE  '\n'
	| PP_ENDIF '\n'
	| PP_IFDEF  IDENTIFIER '\n'
	| PP_IFNDEF IDENTIFIER '\n'
	;

preprocessor_undefine
	: PP_UNDEF IDENTIFIER
	;

preprocessor_define
	: PP_DEFINE IDENTIFIER
	| PP_DEFINE IDENTIFIER PP
	| PP_DEFINE IDENTIFIER '(' preprocessor_define_args ')'
	| PP_DEFINE IDENTIFIER '(' preprocessor_define_args ')' PP
	;

preprocessor_define_args
	: IDENTIFIER
	| preprocessor_define_args ',' IDENTIFIER
	;

preprocessor_include
	: PP_INCLUDE PP_STRING
	| PP_INCLUDE LITERAL_STRING
	;

preprocessor_line
	: PP_LINE 
	| PP_LINE constant
	| PP_LINE constant PP_STRING
	| PP_LINE constant LITERAL_STRING
	;



/* C language */

constant
	: LITERAL_INT
	| LITERAL_CHAR
	| LITERAL_FLOAT
	| LITERAL_ENUM	/* after it has been defined as such */
	;

enumeration_constant		/* before it has been defined as such */
	: IDENTIFIER
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
	| struct_or_union_specifier
	| enum_specifier
	| TYPEDEF_NAME		/* after it has been defined as such */
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
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
enumerator	/* identifiers must be flagged as LITERAL_ENUM */
	: enumeration_constant '=' expression_constant	{ ppp_addsymbol_enum((s_symbol_enum){ .name=$1, .text=$3 }); }
	| enumeration_constant							{ ppp_addsymbol_enum((s_symbol_enum){ .name=$1, .text="" }); }
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



init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;
init_declarator
	: declarator '=' initializer
	| declarator
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

declarator
	: pointer direct_declarator
	| direct_declarator
	;



declaration_specifiers
	: TYPEDEF declaration_specifiers	/* identifiers must be flagged as TYPEDEF_NAME */
	| TYPEDEF
	| storage_class_specifier declaration_specifiers
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
	: declaration_specifiers ';'
	| declaration_specifiers init_declarator_list ';'
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
