// This file is meant to be included sevral times, to avoid code repetition
#ifndef SYMBOLKIND
#define SYMBOLKIND(KIND, SYMBOLINFO)
#endif

SYMBOLKIND(macro,  
	char*	name;	//!< preprocessor define
	char*	text;	//!< contents
	char**	args;	//!< contents
)

SYMBOLKIND(struct,   
	char*	name;	//!< struct type name
	t_uint	size;	//!< amount of fields
	char*	types;	//!< struct field types
	char*	fields;	//!< struct field names
)

SYMBOLKIND(union,   
	char*	name;	//!< union type name
	t_uint	size;	//!< amount of fields
	char*	types;	//!< union field types
	char*	fields;	//!< union field names
)

SYMBOLKIND(enum,   
	char*	name;	//!< enum type name
	t_uint	size;	//!< amount of fields
	char*	values;	//!< enum item values
	char*	fields;	//!< enum item names
)

SYMBOLKIND(type,   
	char*	name;	//!< typedef name
	char*	type;	//!< underlying type
)

SYMBOLKIND(func,   
	char*	name;		//!< function name
	char*	type;		//!< return type
	char*	arg_types;	//!< argument types
	char*	arg_names;	//!< argument names
)

SYMBOLKIND(global, 
	char*	name;	//!< variable/function name
	char*	type;	//!< associated type
)

SYMBOLKIND(local,  
	char*	name;	//!< variable/function name
	char*	type;	//!< associated type
)
