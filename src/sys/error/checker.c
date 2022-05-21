
#include "libccc.h"
#include "libccc/sys/error.h"

#ifndef __NOSTD__
	#include <stdarg.h>
#else
	typedef __builtin_va_list va_list;
	#define va_start(v,l) __builtin_va_start(v,l)
	#define va_end(v)     __builtin_va_end(v)
	#define va_arg(v,l)   __builtin_va_arg(v,l)
	#define va_copy(d,s)  __builtin_va_copy(d,s)
#endif

#include LIBCONFIG_ERROR_INCLUDE



t_bool Error_If(e_cccerror errorcode,
    t_bool shouldhandle,
    char const* funcname,
    char const* format, ...)
{
    va_list args;

    Error_Set(errorcode);
    if (shouldhandle)
    {
        if (format == NULL)
        {
            Error_Handle(errorcode,
                funcname,
                NULL);
        }
        else
        {
            Error_Handle(errorcode,
                funcname,
                String_Format_VA(format, args));
        }
    }
    return (TRUE); // tres important, comme ca le if-body sera toujours executé
}
