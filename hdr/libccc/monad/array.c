
#undef __LIBCCC_MONAD_ARRAY_H
#include "libccc/monad/array.h"

#include "libccc/../../src/monad/array/new.c"
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
#include "libccc/../../src/monad/array/equals.c"
#include "libccc/../../src/monad/array/compare.c"
#include "libccc/../../src/monad/array/iterate.c"
#include "libccc/../../src/monad/array/map.c"
#include "libccc/../../src/monad/array/filter.c"

#undef T
#undef T_NAME
#undef T_DEFAULT
#undef T_EQUALS

#undef	Array_T
#undef	array_T
#undef	s_array_T
