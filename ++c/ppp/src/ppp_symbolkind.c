// This file is meant to be included sevral times, to avoid code repetition
#ifndef SYMBOLKIND
#define SYMBOLKIND(KIND, SYMBOLINFO)
#endif

SYMBOLKIND(macro,
	t_char*	name;	//!< preprocessor define
	t_char*	text;	//!< contents
	t_char**args;	//!< contents
)

SYMBOLKIND(type,
	t_char*	name;	//!< typedef name
	t_char*	type;	//!< underlying type
)

SYMBOLKIND(struct,
	t_char*	name;	//!< struct type name
	t_uint	size;	//!< amount of fields
	t_char*	types;	//!< struct field types
	t_char*	fields;	//!< struct field names
)

SYMBOLKIND(union,
	t_char*	name;	//!< union type name
	t_uint	size;	//!< amount of fields
	t_char*	types;	//!< union field types
	t_char*	fields;	//!< union field names
)

SYMBOLKIND(enum,
	t_char*	name;	//!< enum type name
	t_uint	size;	//!< amount of fields
	t_char*	values;	//!< enum item values
	t_char*	fields;	//!< enum item names
)

SYMBOLKIND(func,
	t_char*	name;		//!< function name
	t_char*	type;		//!< return type
	t_char*	arg_types;	//!< argument types
	t_char*	arg_names;	//!< argument names
)

SYMBOLKIND(global,
	t_char*	name;	//!< variable name
	t_char*	type;	//!< associated type
)

SYMBOLKIND(local,
	t_char*	name;	//!< variable name
	t_char*	type;	//!< associated type
)
