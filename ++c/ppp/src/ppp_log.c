
#include <libccc.h>
#include <libccc/memory.h>
#include <libccc/string.h>
#include <libccc/sys/io.h>
#include <libccc/sys/ansi.h>

#include "ppp.h"



#define DEFINEFUNC_PPP_LOGGING(KIND, FORMAT, EXTRA) \
void	ppp_##KIND(char const* format, ...)				\
{														\
	int		result = 0;									\
	t_char* message = NULL;								\
	va_list args;										\
														\
	EXTRA												\
	if (format == NULL) return;							\
	va_start(args, format);								\
	message = String_Format_VA(format, args);			\
	va_end(args);										\
	if (message == NULL) return;						\
	result = IO_Write_Format(STDERR, FORMAT,			\
		ppp.current_file,								\
		yylineno,										\
		message);										\
	String_Delete(&message);							\
	if (result < 0) return;								\
	return;												\
}														\

DEFINEFUNC_PPP_LOGGING(error  , "ppp: %s:%i: "IO_COLOR_FG_RED   "error"  C_RESET": %s\n", ppp.errors	+= 1;)
DEFINEFUNC_PPP_LOGGING(failure, "ppp: %s:%i: "IO_COLOR_FG_RED   "failure"C_RESET": %s\n", ppp.errors	+= 1;)
DEFINEFUNC_PPP_LOGGING(warning, "ppp: %s:%i: "IO_COLOR_FG_YELLOW"warning"C_RESET": %s\n", ppp.warnings	+= 1;)
DEFINEFUNC_PPP_LOGGING(message, "ppp: %s:%i: "IO_COLOR_FG_BLUE  "message"C_RESET": %s\n", )
DEFINEFUNC_PPP_LOGGING(verbose, "ppp: %s:%i: "IO_COLOR_FG_BLUE  "verbose"C_RESET": %s\n", if (!ppp.verbose)	return;)
DEFINEFUNC_PPP_LOGGING(debug,   "ppp: %s:%i: "IO_COLOR_FG_CYAN  "debug"  C_RESET": %s\n", if (!ppp.debug)	return;)



char const*	ppp_symbolkind(e_symbolkind kind)
{
	switch (kind)
	{
		case SYMBOLKIND_USER:	return ("user"	);
		case SYMBOLKIND_MACRO:	return ("macro"	);
		case SYMBOLKIND_STRUCT:	return ("struct");
		case SYMBOLKIND_UNION:	return ("union"	);
		case SYMBOLKIND_ENUM:	return ("enum"	);
		case SYMBOLKIND_TYPE:	return ("type"	);
		default:	return (NULL);
	}
}
