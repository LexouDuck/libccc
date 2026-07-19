
#include "libccc.h"

#ifndef __NOSTD__
	#include <setjmp.h>
#endif

#include "libccc/sys/program.h"

#include LIBCONFIG_ERROR_INCLUDE



// NB: there is no corresponding wrapper function for setjmp() here, because
// the C standard requires setjmp() to be called directly within the stack
// frame which will later be jumped back to: as such, Program_SaveContext()
// can only be defined as a macro (see "libccc/sys/program.h")

_INLINE()
void	Program_RestoreContext(t_jmpbuf context, int status)
{
	longjmp(context, status);
}
