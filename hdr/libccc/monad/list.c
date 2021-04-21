
// make all generic functions be defined as 'static', so that DCE can occur on any compiler
#undef _GENERIC
#if (defined(__GNUC__) || defined(__llvm__))
	#define _GENERIC()		__attribute__((unused))	static
#elif (defined(_MSC_VER) || defined(__SWIG__))
	#pragma warning(push)
	#pragma warning(disable : 4505)
	#define _GENERIC()		static
#else
	#define _GENERIC()		static
#endif

// force re-inclusion of header (with the current generic type `T`)
#undef __LIBCCC_MONAD_LIST_H
#include "libccc/monad/list.h"

// generate code for all generic functions
#include "libccc/../../src/monad/list/item.c"
#include "libccc/../../src/monad/list/length.c"
#include "libccc/../../src/monad/list/new.c"
#include "libccc/../../src/monad/list/delete.c"
#include "libccc/../../src/monad/list/duplicate.c"
#include "libccc/../../src/monad/list/get.c"
#include "libccc/../../src/monad/list/set.c"
#include "libccc/../../src/monad/list/copy.c"
#include "libccc/../../src/monad/list/sub.c"
#include "libccc/../../src/monad/list/append.c"
#include "libccc/../../src/monad/list/prepend.c"
#include "libccc/../../src/monad/list/insert.c"
#include "libccc/../../src/monad/list/remove.c"
#include "libccc/../../src/monad/list/removeall.c"
#include "libccc/../../src/monad/list/removeat.c"
#include "libccc/../../src/monad/list/replace.c"
#include "libccc/../../src/monad/list/find.c"
#include "libccc/../../src/monad/list/count.c"
#include "libccc/../../src/monad/list/contains.c"
#include "libccc/../../src/monad/list/has.c"
#include "libccc/../../src/monad/list/equals.c"
#include "libccc/../../src/monad/list/compare.c"
#include "libccc/../../src/monad/list/iterate.c"
#include "libccc/../../src/monad/list/map.c"
#include "libccc/../../src/monad/list/filter.c"

// remove all generic type macros
#undef list_T
#undef s_list_T

#undef T
#undef T_NAME
#undef T_DEFAULT
#undef T_EQUALS

// redefine the _GENERIC() macro as empty, so everything works as normal again
#undef _GENERIC
#if (defined(__GNUC__) || defined(__llvm__))
	#define _GENERIC()	
#elif (defined(_MSC_VER) || defined(__SWIG__))
	#pragma warning(pop)
	#define _GENERIC()	
#else
	#define _GENERIC()	
#endif
