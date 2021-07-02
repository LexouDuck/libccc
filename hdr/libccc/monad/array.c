
// make all generic functions be defined as 'static', so that DCE can occur on any compiler
#undef _GENERIC
#if (defined(__GNUC__) || defined(__llvm__))
	#define _GENERIC()		__attribute__((unused))	static
#elif defined(__MSVC__)
	#pragma warning(push)
	#pragma warning(disable : 4505)
	#define _GENERIC()		static
#else
	#define _GENERIC()		static
#endif

// force re-inclusion of header (with the current generic type `T`)
#undef __LIBCCC_MONAD_ARRAY_H
#include "libccc/monad/array.h"

// generate code for all generic functions
#include "libccc/../../src/monad/array/new.c"
#include "libccc/../../src/monad/array/create.c"
#include "libccc/../../src/monad/array/delete.c"
#include "libccc/../../src/monad/array/duplicate.c"
#include "libccc/../../src/monad/array/get.c"
#include "libccc/../../src/monad/array/set.c"
#include "libccc/../../src/monad/array/copy.c"
#include "libccc/../../src/monad/array/sub.c"
#include "libccc/../../src/monad/array/append.c"
#include "libccc/../../src/monad/array/prepend.c"
#include "libccc/../../src/monad/array/insert.c"
#include "libccc/../../src/monad/array/remove.c"
#include "libccc/../../src/monad/array/removeall.c"
#include "libccc/../../src/monad/array/removeat.c"
#include "libccc/../../src/monad/array/replace.c"
#include "libccc/../../src/monad/array/find.c"
#include "libccc/../../src/monad/array/count.c"
#include "libccc/../../src/monad/array/contains.c"
#include "libccc/../../src/monad/array/has.c"
#include "libccc/../../src/monad/array/equals.c"
#include "libccc/../../src/monad/array/compare.c"
#include "libccc/../../src/monad/array/iterate.c"
#include "libccc/../../src/monad/array/map.c"
#include "libccc/../../src/monad/array/filter.c"

// remove all generic type macros
#undef	array_T
#undef	s_array_T

#undef T
#undef T_NAME
#undef T_DEFAULT
#undef T_EQUALS

// redefine the _GENERIC() macro as empty, so everything works as normal again
#undef _GENERIC
#if (defined(__GNUC__) || defined(__llvm__))
	#define _GENERIC()	
#elif defined(__MSVC__)
	#pragma warning(pop)
	#define _GENERIC()	
#else
	#define _GENERIC()	
#endif
