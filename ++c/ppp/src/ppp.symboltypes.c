// This file is meant to be included sevral times, to avoid code repetition
#ifndef SYMBOL
#define SYMBOL(SYMBOLKIND, SYMBOLINFO)
#endif

SYMBOL(macro,  
	char const*	name;	//!< preprocessor define
	char const* text;	//!< contents
)

SYMBOL(enum,   
	char const*	name;	//!< enum item name
	char const* text;	//!< value assigned
)

SYMBOL(type,   
	char const*	name;	//!< typedef name
	char const* type;	//!< underlying type
)

SYMBOL(func,   
	char const*	name;		//!< function name
	char const* type;		//!< return type
	char const* arg_types;	//!< argument types
	char const* arg_names;	//!< argument names
)

SYMBOL(global, 
	char const*	name;	//!< variable/function name
	char const* type;	//!< associated type
)

SYMBOL(local,  
	char const*	name;	//!< variable/function name
	char const* type;	//!< associated type
)
