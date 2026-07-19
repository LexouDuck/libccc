
#include <stdlib.h>

#include "libccc.h"
#include "libccc/bool.h"
#include "libccc/pointerarray.h"
#include "libccc/text/format.h"

#include "test.h"
#include "test_utils.h"



/*============================================================================*\
||                           Test Fixtures (Helpers)                          ||
\*============================================================================*/

/*
**	Pointer arrays are compared by pointer identity, so these tests use the
**	addresses of a few static sentinel objects (with recognizable int values,
**	which some tests also use, for value-based compare/reduce/fold callbacks).
**
**	Most functions under test either allocate a new result array (which is
**	compared against a static expected array, then freed), or mutate an array
**	in-place (in which case, a `perform_` helper duplicates a static base
**	array, applies the mutation, and returns the result for comparison).
*/

static int	data_A = 1;
static int	data_B = 2;
static int	data_C = 3;
static int	data_D = 4;
static int	data_X = 99;

#define PA	((void*)&data_A)
#define PB	((void*)&data_B)
#define PC	((void*)&data_C)
#define PD	((void*)&data_D)
#define PX	((void*)&data_X)

static void*	ptrarr_empty[]   = {                 NULL };
static void*	ptrarr_A[]       = { PA,             NULL };
static void*	ptrarr_B[]       = { PB,             NULL };
static void*	ptrarr_D[]       = { PD,             NULL };
static void*	ptrarr_X[]       = { PX,             NULL };
static void*	ptrarr_AA[]      = { PA, PA,         NULL };
static void*	ptrarr_AB[]      = { PA, PB,         NULL };
static void*	ptrarr_CD[]      = { PC, PD,         NULL };
static void*	ptrarr_AAA[]     = { PA, PA, PA,     NULL };
static void*	ptrarr_ABA[]     = { PA, PB, PA,     NULL };
static void*	ptrarr_ABC[]     = { PA, PB, PC,     NULL };
static void*	ptrarr_ABC_bis[] = { PA, PB, PC,     NULL };
static void*	ptrarr_ABD[]     = { PA, PB, PD,     NULL };
static void*	ptrarr_ABX[]     = { PA, PB, PX,     NULL };
static void*	ptrarr_BAC[]     = { PB, PA, PC,     NULL };
static void*	ptrarr_XBC[]     = { PX, PB, PC,     NULL };
static void*	ptrarr_XBA[]     = { PX, PB, PA,     NULL };
static void*	ptrarr_XBX[]     = { PX, PB, PX,     NULL };
static void*	ptrarr_CBA[]     = { PC, PB, PA,     NULL };
static void*	ptrarr_BCD[]     = { PB, PC, PD,     NULL };
static void*	ptrarr_ACD[]     = { PA, PC, PD,     NULL };
static void*	ptrarr_BA[]      = { PB, PA,         NULL };
static void*	ptrarr_BC[]      = { PB, PC,         NULL };
static void*	ptrarr_AC[]      = { PA, PC,         NULL };
static void*	ptrarr_ABCD[]    = { PA, PB, PC, PD, NULL };
static void*	ptrarr_DABC[]    = { PD, PA, PB, PC, NULL };
static void*	ptrarr_ADBC[]    = { PA, PD, PB, PC, NULL };
static void*	ptrarr_ACDB[]    = { PA, PC, PD, PB, NULL };
static void*	ptrarr_CDAB[]    = { PC, PD, PA, PB, NULL };
static void*	ptrarr_CBCD[]    = { PC, PB, PC, PD, NULL };
static void*	ptrarr_ABAB[]    = { PA, PB, PA, PB, NULL };
static void*	ptrarr_ABXCD[]   = { PA, PB, PX, PC, PD, NULL };

// arrays-of-arrays, for the Join tests
static void**	ptrarrs_2[]      = { ptrarr_AB, ptrarr_CD, NULL };
static void**	ptrarrs_1[]      = { ptrarr_AB,            NULL };
static void**	ptrarrs_none[]   = {                       NULL };

// convenience casts, for the various levels of constness in the API under test
#define _PTRS(X)	((void* const*)(X))
#define _CPTRS(X)	((void const* const*)(X))



//! FIXTURE: perform-helper for in-place removal functions: duplicates `base`, applies the removal, returns the result
static
void**	perform_removeat(void** base, t_uint index)
{
	void**	dup = c_ptrarrdup(_PTRS(base));

	c_ptrarrdelat(dup, index);
	return (dup);
}
static
void**	perform_remove(void** base, void* item)
{
	void**	dup = c_ptrarrdup(_PTRS(base));

	c_ptrarrdelone(dup, item);
	return (dup);
}
static
void**	perform_removeall(void** base, void* item)
{
	void**	dup = c_ptrarrdup(_PTRS(base));

	c_ptrarrdelall(dup, item);
	return (dup);
}

//! FIXTURE: perform-helper for Add: duplicates `base` (or passes NULL through), and adds `item`
static
void**	perform_add(void** base, void* item)
{
	void**	dup = (base == NULL ? NULL : c_ptrarrdup(_PTRS(base)));

	return (c_ptrarradd(dup, item));
}

//! FIXTURE: perform-helper for Insert: duplicates `base`, inserts `item` at `index` (freeing the duplicate, if the call rejects the index)
static
void**	perform_insert(void** base, void* item, t_uint index)
{
	void**	dup = c_ptrarrdup(_PTRS(base));
	void**	result = c_ptrarrinsert(dup, item, index);

	if (result == NULL)
		c_ptrarrfree(dup); // the call did nothing: the duplicate is still owned here
	return (result);
}

//! FIXTURE: perform-helper for Wedge: duplicates `base`, wedges `src` at `index` (freeing the duplicate, if the call rejects the index)
static
void**	perform_wedge(void** base, void** src, t_uint index)
{
	void**	dup = c_ptrarrdup(_PTRS(base));
	void**	result = c_ptrarrwedge(dup, _PTRS(src), index);

	if (result == NULL)
		c_ptrarrfree(dup); // the call did nothing: the duplicate is still owned here
	return (result);
}

//! FIXTURE: perform-helper for Copy: duplicates `dest_base`, copies `n` items of `src` into it (freeing the duplicate, if the call errors)
static
void**	perform_copy(void** dest_base, t_uint dest_i, void** src, t_uint src_i, t_uint n)
{
	void**	dup = c_ptrarrdup(_PTRS(dest_base));
	void**	result = c_ptrarrcpy(dup, dest_i, _PTRS(src), src_i, n);

	if (result == NULL)
		c_ptrarrfree(dup); // the call did nothing: the duplicate is still owned here
	return (result);
}

//! FIXTURE: perform-helper for Append: duplicates `dest_base`, appends `src` to it (the function deletes the old duplicate internally)
static
void**	perform_append(void** dest_base, void** src)
{
	void**	dup = c_ptrarrdup(_PTRS(dest_base));

	return (c_ptrarrappend(&dup, _PTRS(src)));
}

//! FIXTURE: perform-helper for Prepend: duplicates `dest_base`, prepends `src` to it (the function deletes the old duplicate internally)
static
void**	perform_prepend(void** src, void** dest_base)
{
	void**	dup = c_ptrarrdup(_PTRS(dest_base));

	return (c_ptrarrprepend(_PTRS(src), &dup));
}

//! FIXTURE: perform-helper for Merge: duplicates both arrays, merges them (the function deletes both old duplicates internally)
static
void**	perform_merge(void** base1, void** base2)
{
	void**	dup1 = c_ptrarrdup(_PTRS(base1));
	void**	dup2 = c_ptrarrdup(_PTRS(base2));

	return (c_ptrarrmerge(&dup1, &dup2));
}



// callback functions, for the map/filter/find/compare/reduce/fold tests:

//! CALLBACK: maps `PA` to `PB`, and `PB` to `PA` (any other pointer is unchanged)
static
void*	map_swap_ab(void const* ptr)
{
	if (ptr == PA)	return (PB);
	if (ptr == PB)	return (PA);
	return ((void*)ptr);
}
//! CALLBACK: maps the item at index `0` to `PX` (any other item is unchanged)
static
void*	map_i_first_to_x(void const* ptr, t_uint index)
{
	return (index == 0 ? PX : (void*)ptr);
}
//! CALLBACK: matches only the `PA` pointer
static
t_bool	filter_is_a(void const* ptr)
{
	return (ptr == PA);
}
//! CALLBACK: matches anything but the `PA` pointer
static
t_bool	filter_not_a(void const* ptr)
{
	return (ptr != PA);
}
//! CALLBACK: matches items at even indices
static
t_bool	filter_i_even(void const* ptr, t_uint index)
{
	(void)ptr;
	return (index % 2 == 0);
}
//! CALLBACK: matches only the `PC` pointer
static
t_bool	match_is_c(void const* ptr)
{
	return (ptr == PC);
}
//! CALLBACK: compares the pointed-to `int` values
static
t_sint	compare_values(void const* ptr1, void const* ptr2)
{
	return ((t_sint)(*(int const*)ptr1 - *(int const*)ptr2));
}
//! CALLBACK: increments the accumulator for each item (counts items)
static
void*	reduce_count(void const* ptr, void* acc)
{
	(void)ptr;
	return ((void*)((t_uintptr)acc + 1));
}
//! CALLBACK: always returns the current item (so, the final result is the last item)
static
void*	reduce_last(void const* ptr, void* acc)
{
	(void)acc;
	return ((void*)ptr);
}
//! CALLBACK: adds the pointed-to `int` value to the accumulator
static
void*	fold_sum_values(void const* ptr, void* acc)
{
	return ((void*)((t_uintptr)acc + (t_uintptr)*(int const*)ptr));
}
//! CALLBACK: adds `index` to the accumulator, for each item
static
void*	fold_i_sum_indices(void const* ptr, void* acc, t_uint index)
{
	(void)ptr;
	return ((void*)((t_uintptr)acc + index));
}
//! CALLBACK (for Iterate): increments the pointed-to `int` value in-place, returning the same pointer
static
void*	iter_increment(void* ptr)
{
	*(int*)ptr += 1;
	return (ptr);
}
//! CALLBACK (for Iterate): returns a newly allocated `int`, holding double the pointed-to value (the old item gets freed by Iterate)
static
void*	iter_double_new(void* ptr)
{
	int*	result = (int*)malloc(sizeof(int));

	if (result == NULL)
		return (ptr);
	*result = *(int*)ptr * 2;
	return (result);
}
//! CALLBACK (for Iterate_I): adds `index` to the pointed-to `int` value in-place, returning the same pointer
static
void*	iter_i_add_index(void* ptr, t_uint index)
{
	*(int*)ptr += (int)index;
	return (ptr);
}



/*============================================================================*\
||                       Tests: basic/creation operations                     ||
\*============================================================================*/



#ifndef c_ptrarrlen
void test_ptrarrlen(void)	{}
#warning "ptrarrlen() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrlen(char const* test_name, t_testflags flags,
		t_uint expecting,
		void** ptrarr)
{
	TEST_INIT(uint)
	TEST_PERFORM(	ptrarrlen, _CPTRS(ptrarr))
	TEST_PRINT(uint,ptrarrlen, "ptrarr=%p", (void*)ptrarr)
}
void	test_ptrarrlen(void)
{
/*	| TEST FUNCTION      | TEST NAME                       | TESTFLAGS     | EXPECTING | TEST ARGS			*/
	print_test_ptrarrlen("ptrarrlen                       ",	FALSE,        3,         ptrarr_ABC);
	print_test_ptrarrlen("ptrarrlen (4 items)             ",	FALSE,        4,         ptrarr_ABCD);
	print_test_ptrarrlen("ptrarrlen (repeated items)      ",	FALSE,        3,         ptrarr_AAA);
	print_test_ptrarrlen("ptrarrlen (single item)         ",	FALSE,        1,         ptrarr_A);
	print_test_ptrarrlen("ptrarrlen (empty array)         ",	FALSE,        0,         ptrarr_empty);
	print_test_ptrarrlen("ptrarrlen (null array)          ",	ALLOW_SIGSEGV, 0,        NULL);
}
#endif



#ifndef c_ptrarrnew
void test_ptrarrnew(void)	{}
#warning "ptrarrnew() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrnew(char const* test_name, t_testflags flags,
		void** expecting,
		t_uint n,
		void* value)
{
	TEST_INIT(ptrarr)
	TEST_PERFORM(	ptrarrnew, n, value)
	TEST_PRINT(ptrarr,	ptrarrnew, "n=" SF_UINT ", value=%p", n, value)
	TEST_FREE_RESULT(c_ptrarrfree)
}
void	test_ptrarrnew(void)
{
/*	| TEST FUNCTION      | TEST NAME                       | TESTFLAGS | EXPECTING    | TEST ARGS			*/
	print_test_ptrarrnew("ptrarrnew                       ",	FALSE,    ptrarr_AAA,   3, PA);
	print_test_ptrarrnew("ptrarrnew (single item)         ",	FALSE,    ptrarr_B,     1, PB);
	print_test_ptrarrnew("ptrarrnew (n = 0)               ",	FALSE,    ptrarr_empty, 0, PA);
	print_test_ptrarrnew("ptrarrnew (null value)          ",	FALSE,    ptrarr_empty, 2, NULL); // NB: an array full of NULLs is an empty array (NULL is the terminator)
}
#endif



#ifndef c_ptrarrcreate
void test_ptrarrcreate(void)	{}
#warning "ptrarrcreate() test suite function defined, but the function isn't defined."
#else
void	test_ptrarrcreate(void)
{
	// NB: this test function is written without a `print_test_` helper, since variadic arguments cannot be forwarded
	{
		char const* test_name = "ptrarrcreate                    ";	t_testflags flags = FALSE;
		TEST_INIT(ptrarr)
		TEST_PERFORM_(result, c_ptrarrcreate, 3, PA, PB, PC)
		test.expect = ptrarr_ABC;
		TEST_PRINT(ptrarr,	ptrarrcreate, "n=3, args=(PA, PB, PC)")
		TEST_FREE_RESULT(c_ptrarrfree)
	}
	{
		char const* test_name = "ptrarrcreate (single item)      ";	t_testflags flags = FALSE;
		TEST_INIT(ptrarr)
		TEST_PERFORM_(result, c_ptrarrcreate, 1, PD)
		test.expect = ptrarr_D;
		TEST_PRINT(ptrarr,	ptrarrcreate, "n=1, args=(PD)")
		TEST_FREE_RESULT(c_ptrarrfree)
	}
	{
		char const* test_name = "ptrarrcreate (n = 0)            ";	t_testflags flags = FALSE;
		TEST_INIT(ptrarr)
		TEST_PERFORM_(result, c_ptrarrcreate, 0)
		test.expect = ptrarr_empty;
		TEST_PRINT(ptrarr,	ptrarrcreate, "n=0")
		TEST_FREE_RESULT(c_ptrarrfree)
	}
}
#endif



#ifndef c_ptrarrdup
void test_ptrarrdup(void)	{}
#warning "ptrarrdup() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrdup(char const* test_name, t_testflags flags,
		void** expecting,
		void** ptrarr)
{
	TEST_INIT(ptrarr)
	TEST_PERFORM(	ptrarrdup, _PTRS(ptrarr))
	TEST_PRINT(ptrarr,	ptrarrdup, "ptrarr=%p", (void*)ptrarr)
	TEST_FREE_RESULT(c_ptrarrfree)
}
void	test_ptrarrdup(void)
{
/*	| TEST FUNCTION      | TEST NAME                       | TESTFLAGS     | EXPECTING    | TEST ARGS			*/
	print_test_ptrarrdup("ptrarrdup                       ",	FALSE,        ptrarr_ABC,   ptrarr_ABC);
	print_test_ptrarrdup("ptrarrdup (empty array)         ",	FALSE,        ptrarr_empty, ptrarr_empty);
	print_test_ptrarrdup("ptrarrdup (null array)          ",	ALLOW_SIGSEGV, NULL,        NULL);
}
#endif



#ifndef c_ptrarrsub
void test_ptrarrsub(void)	{}
#warning "ptrarrsub() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrsub(char const* test_name, t_testflags flags,
		void** expecting,
		void** ptrarr,
		t_uint index,
		t_uint n)
{
	TEST_INIT(ptrarr)
	TEST_PERFORM(	ptrarrsub, _PTRS(ptrarr), index, n)
	TEST_PRINT(ptrarr,	ptrarrsub, "index=" SF_UINT ", n=" SF_UINT, index, n)
	TEST_FREE_RESULT(c_ptrarrfree)
}
void	test_ptrarrsub(void)
{
/*	| TEST FUNCTION      | TEST NAME                       | TESTFLAGS     | EXPECTING    | TEST ARGS			*/
	print_test_ptrarrsub("ptrarrsub                       ",	FALSE,        ptrarr_BC,    ptrarr_ABCD, 1, 2);
	print_test_ptrarrsub("ptrarrsub (from start)          ",	FALSE,        ptrarr_AB,    ptrarr_ABCD, 0, 2);
	print_test_ptrarrsub("ptrarrsub (n=0: until the end)  ",	FALSE,        ptrarr_ABCD,  ptrarr_ABCD, 0, 0);
	print_test_ptrarrsub("ptrarrsub (n=0, with offset)    ",	FALSE,        ptrarr_CD,    ptrarr_ABCD, 2, 0);
	print_test_ptrarrsub("ptrarrsub (index at the end)    ",	FALSE,        ptrarr_empty, ptrarr_ABCD, 4, 0);
	print_test_ptrarrsub("ptrarrsub (index too large)     ",	FALSE,        NULL,         ptrarr_ABCD, 5, 1);
	print_test_ptrarrsub("ptrarrsub (n too large)         ",	FALSE,        NULL,         ptrarr_ABCD, 1, 4);
	print_test_ptrarrsub("ptrarrsub (null array)          ",	ALLOW_SIGSEGV, NULL,        NULL,        0, 1);
}
#endif



#ifndef c_ptrarrcpy
void test_ptrarrcpy(void)	{}
#warning "ptrarrcpy() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrcpy(char const* test_name, t_testflags flags,
		void** expecting,
		void** dest_base, t_uint dest_i,
		void** src, t_uint src_i,
		t_uint n)
{
	TEST_INIT(ptrarr)
	TEST_PERFORM_(result, perform_copy, dest_base, dest_i, src, src_i, n)
	test.expect = expecting;
	TEST_PRINT(ptrarr,	ptrarrcpy, "dest_i=" SF_UINT ", src_i=" SF_UINT ", n=" SF_UINT, dest_i, src_i, n)
	TEST_FREE_RESULT(c_ptrarrfree)
}
void	test_ptrarrcpy(void)
{
/*	| TEST FUNCTION      | TEST NAME                       | TESTFLAGS | EXPECTING   | TEST ARGS			*/
	print_test_ptrarrcpy("ptrarrcpy                       ",	FALSE,    ptrarr_CBCD,  ptrarr_ABCD, 0, ptrarr_CBA,  0, 2);
	print_test_ptrarrcpy("ptrarrcpy (n=0: all of src)     ",	FALSE,    ptrarr_ABAB,  ptrarr_ABCD, 2, ptrarr_AB,   0, 0);
	print_test_ptrarrcpy("ptrarrcpy (dest_i too large)    ",	FALSE,    NULL,         ptrarr_ABCD, 4, ptrarr_AB,   0, 1);
	print_test_ptrarrcpy("ptrarrcpy (n too large)         ",	FALSE,    NULL,         ptrarr_ABCD, 3, ptrarr_CBA,  0, 2);
}
#endif



/*============================================================================*\
||                        Tests: editing operations                           ||
\*============================================================================*/



#ifndef c_ptrarradd
void test_ptrarradd(void)	{}
#warning "ptrarradd() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarradd(char const* test_name, t_testflags flags,
		void** expecting,
		void** base,
		void* item)
{
	TEST_INIT(ptrarr)
	TEST_PERFORM_(result, perform_add, base, item)
	test.expect = expecting;
	TEST_PRINT(ptrarr,	ptrarradd, "base=%p, item=%p", (void*)base, item)
	TEST_FREE_RESULT(c_ptrarrfree)
}
void	test_ptrarradd(void)
{
/*	| TEST FUNCTION      | TEST NAME                       | TESTFLAGS | EXPECTING   | TEST ARGS			*/
	print_test_ptrarradd("ptrarradd                       ",	FALSE,    ptrarr_ABCD, ptrarr_ABC,   PD);
	print_test_ptrarradd("ptrarradd (to empty array)      ",	FALSE,    ptrarr_A,    ptrarr_empty, PA);
	print_test_ptrarradd("ptrarradd (to null array)       ",	FALSE,    ptrarr_A,    NULL,         PA);
}
#endif



#ifndef c_ptrarrinsert
void test_ptrarrinsert(void)	{}
#warning "ptrarrinsert() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrinsert(char const* test_name, t_testflags flags,
		void** expecting,
		void** base,
		void* item,
		t_uint index)
{
	TEST_INIT(ptrarr)
	TEST_PERFORM_(result, perform_insert, base, item, index)
	test.expect = expecting;
	TEST_PRINT(ptrarr,	ptrarrinsert, "item=%p, index=" SF_UINT, item, index)
	TEST_FREE_RESULT(c_ptrarrfree)
}
void	test_ptrarrinsert(void)
{
/*	| TEST FUNCTION         | TEST NAME                       | TESTFLAGS | EXPECTING   | TEST ARGS			*/
	print_test_ptrarrinsert("ptrarrinsert (at start)         ",	FALSE,    ptrarr_DABC, ptrarr_ABC, PD, 0);
	print_test_ptrarrinsert("ptrarrinsert (in the middle)    ",	FALSE,    ptrarr_ADBC, ptrarr_ABC, PD, 1);
	print_test_ptrarrinsert("ptrarrinsert (at the end)       ",	FALSE,    ptrarr_ABCD, ptrarr_ABC, PD, 3);
	print_test_ptrarrinsert("ptrarrinsert (index too large)  ",	FALSE,    NULL,        ptrarr_ABC, PD, 4);
}
#endif



#ifndef c_ptrarrwedge
void test_ptrarrwedge(void)	{}
#warning "ptrarrwedge() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrwedge(char const* test_name, t_testflags flags,
		void** expecting,
		void** base,
		void** src,
		t_uint index)
{
	TEST_INIT(ptrarr)
	TEST_PERFORM_(result, perform_wedge, base, src, index)
	test.expect = expecting;
	TEST_PRINT(ptrarr,	ptrarrwedge, "index=" SF_UINT, index)
	TEST_FREE_RESULT(c_ptrarrfree)
}
void	test_ptrarrwedge(void)
{
/*	| TEST FUNCTION        | TEST NAME                       | TESTFLAGS | EXPECTING   | TEST ARGS			*/
	print_test_ptrarrwedge("ptrarrwedge (in the middle)     ",	FALSE,    ptrarr_ACDB, ptrarr_AB, ptrarr_CD, 1);
	print_test_ptrarrwedge("ptrarrwedge (at start)          ",	FALSE,    ptrarr_CDAB, ptrarr_AB, ptrarr_CD, 0);
	print_test_ptrarrwedge("ptrarrwedge (at the end)        ",	FALSE,    ptrarr_ABCD, ptrarr_AB, ptrarr_CD, 2);
	print_test_ptrarrwedge("ptrarrwedge (index too large)   ",	FALSE,    NULL,        ptrarr_AB, ptrarr_CD, 3);
}
#endif



#ifndef c_ptrarrdelat
void test_ptrarrdelat(void)	{}
#warning "ptrarrdelat() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrdelat(char const* test_name, t_testflags flags,
		void** expecting,
		void** base,
		t_uint index)
{
	TEST_INIT(ptrarr)
	TEST_PERFORM_(result, perform_removeat, base, index)
	test.expect = expecting;
	TEST_PRINT(ptrarr,	ptrarrdelat, "index=" SF_UINT, index)
	TEST_FREE_RESULT(c_ptrarrfree)
}
void	test_ptrarrdelat(void)
{
/*	| TEST FUNCTION        | TEST NAME                       | TESTFLAGS | EXPECTING    | TEST ARGS			*/
	print_test_ptrarrdelat("ptrarrdelat (in the middle)     ",	FALSE,    ptrarr_ACD,   ptrarr_ABCD, 1);
	print_test_ptrarrdelat("ptrarrdelat (at start)          ",	FALSE,    ptrarr_BCD,   ptrarr_ABCD, 0);
	print_test_ptrarrdelat("ptrarrdelat (at the end)        ",	FALSE,    ptrarr_ABC,   ptrarr_ABCD, 3);
	print_test_ptrarrdelat("ptrarrdelat (last remaining)    ",	FALSE,    ptrarr_empty, ptrarr_A,    0);
	print_test_ptrarrdelat("ptrarrdelat (index too large)   ",	FALSE,    ptrarr_ABCD,  ptrarr_ABCD, 4);
}
#endif



#ifndef c_ptrarrdelone
void test_ptrarrdelone(void)	{}
#warning "ptrarrdelone() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrdelone(char const* test_name, t_testflags flags,
		void** expecting,
		void** base,
		void* item)
{
	TEST_INIT(ptrarr)
	TEST_PERFORM_(result, perform_remove, base, item)
	test.expect = expecting;
	TEST_PRINT(ptrarr,	ptrarrdelone, "item=%p", item)
	TEST_FREE_RESULT(c_ptrarrfree)
}
void	test_ptrarrdelone(void)
{
/*	| TEST FUNCTION         | TEST NAME                       | TESTFLAGS | EXPECTING  | TEST ARGS			*/
	print_test_ptrarrdelone("ptrarrdelone (first occurrence) ",	FALSE,    ptrarr_BA,   ptrarr_ABA, PA);
	print_test_ptrarrdelone("ptrarrdelone (middle item)      ",	FALSE,    ptrarr_AC,   ptrarr_ABC, PB);
	print_test_ptrarrdelone("ptrarrdelone (item not present) ",	FALSE,    ptrarr_ABC,  ptrarr_ABC, PX);
}
#endif



#ifndef c_ptrarrdelall
void test_ptrarrdelall(void)	{}
#warning "ptrarrdelall() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrdelall(char const* test_name, t_testflags flags,
		void** expecting,
		void** base,
		void* item)
{
	TEST_INIT(ptrarr)
	TEST_PERFORM_(result, perform_removeall, base, item)
	test.expect = expecting;
	TEST_PRINT(ptrarr,	ptrarrdelall, "item=%p", item)
	TEST_FREE_RESULT(c_ptrarrfree)
}
void	test_ptrarrdelall(void)
{
/*	| TEST FUNCTION         | TEST NAME                       | TESTFLAGS | EXPECTING    | TEST ARGS			*/
	print_test_ptrarrdelall("ptrarrdelall                    ",	FALSE,    ptrarr_B,     ptrarr_ABA, PA);
	print_test_ptrarrdelall("ptrarrdelall (all items match)  ",	FALSE,    ptrarr_empty, ptrarr_AAA, PA);
	print_test_ptrarrdelall("ptrarrdelall (item not present) ",	FALSE,    ptrarr_ABC,   ptrarr_ABC, PX);
}
#endif



#ifndef c_ptrarrrep
void test_ptrarrrep(void)	{}
#warning "ptrarrrep() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrrep(char const* test_name, t_testflags flags,
		void** expecting,
		void** ptrarr,
		void* ptr_old,
		void* ptr_new)
{
	TEST_INIT(ptrarr)
	TEST_PERFORM(	ptrarrrep, _PTRS(ptrarr), ptr_old, ptr_new)
	TEST_PRINT(ptrarr,	ptrarrrep, "ptr_old=%p, ptr_new=%p", ptr_old, ptr_new)
	TEST_FREE_RESULT(c_ptrarrfree)
}
void	test_ptrarrrep(void)
{
/*	| TEST FUNCTION      | TEST NAME                       | TESTFLAGS | EXPECTING  | TEST ARGS			*/
	print_test_ptrarrrep("ptrarrrep (all occurrences)     ",	FALSE,    ptrarr_XBX,  ptrarr_ABA, PA, PX);
	print_test_ptrarrrep("ptrarrrep (single occurrence)   ",	FALSE,    ptrarr_ABX,  ptrarr_ABC, PC, PX);
	print_test_ptrarrrep("ptrarrrep (item not present)    ",	FALSE,    ptrarr_ABC,  ptrarr_ABC, PX, PD);
}
#endif



#ifndef c_ptrarrrepfirst
void test_ptrarrrepfirst(void)	{}
#warning "ptrarrrepfirst() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrrepfirst(char const* test_name, t_testflags flags,
		void** expecting,
		void** ptrarr,
		void* ptr_old,
		void* ptr_new,
		t_uint n)
{
	TEST_INIT(ptrarr)
	TEST_PERFORM(	ptrarrrepfirst, _PTRS(ptrarr), ptr_old, ptr_new, n)
	TEST_PRINT(ptrarr,	ptrarrrepfirst, "ptr_old=%p, ptr_new=%p, n=" SF_UINT, ptr_old, ptr_new, n)
	TEST_FREE_RESULT(c_ptrarrfree)
}
void	test_ptrarrrepfirst(void)
{
/*	| TEST FUNCTION           | TEST NAME                       | TESTFLAGS | EXPECTING  | TEST ARGS			*/
	print_test_ptrarrrepfirst("ptrarrrepfirst (n = 1)          ",	FALSE,    ptrarr_XBA,  ptrarr_ABA, PA, PX, 1);
	print_test_ptrarrrepfirst("ptrarrrepfirst (n = 2)          ",	FALSE,    ptrarr_XBX,  ptrarr_ABA, PA, PX, 2);
	print_test_ptrarrrepfirst("ptrarrrepfirst (n = 0)          ",	FALSE,    ptrarr_ABA,  ptrarr_ABA, PA, PX, 0);
}
#endif



#ifndef c_ptrarrreplast
void test_ptrarrreplast(void)	{}
#warning "ptrarrreplast() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrreplast(char const* test_name, t_testflags flags,
		void** expecting,
		void** ptrarr,
		void* ptr_old,
		void* ptr_new,
		t_uint n)
{
	TEST_INIT(ptrarr)
	TEST_PERFORM(	ptrarrreplast, _PTRS(ptrarr), ptr_old, ptr_new, n)
	TEST_PRINT(ptrarr,	ptrarrreplast, "ptr_old=%p, ptr_new=%p, n=" SF_UINT, ptr_old, ptr_new, n)
	TEST_FREE_RESULT(c_ptrarrfree)
}
void	test_ptrarrreplast(void)
{
/*	| TEST FUNCTION          | TEST NAME                       | TESTFLAGS | EXPECTING | TEST ARGS			*/
	print_test_ptrarrreplast("ptrarrreplast (n = 1)           ",	FALSE,    ptrarr_ABX, ptrarr_ABA, PA, PX, 1);
	print_test_ptrarrreplast("ptrarrreplast (n = 2)           ",	FALSE,    ptrarr_XBX,           ptrarr_ABA, PA, PX, 2);
	print_test_ptrarrreplast("ptrarrreplast (n = 0)           ",	FALSE,    ptrarr_ABA,           ptrarr_ABA, PA, PX, 0);
}
#endif



#ifndef c_ptrarrrev
void test_ptrarrrev(void)	{}
#warning "ptrarrrev() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrrev(char const* test_name, t_testflags flags,
		void** expecting,
		void** ptrarr)
{
	TEST_INIT(ptrarr)
	TEST_PERFORM(	ptrarrrev, _PTRS(ptrarr))
	TEST_PRINT(ptrarr,	ptrarrrev, "ptrarr=%p", (void*)ptrarr)
	TEST_FREE_RESULT(c_ptrarrfree)
}
void	test_ptrarrrev(void)
{
/*	| TEST FUNCTION      | TEST NAME                       | TESTFLAGS     | EXPECTING    | TEST ARGS			*/
	print_test_ptrarrrev("ptrarrrev                       ",	FALSE,        ptrarr_CBA,   ptrarr_ABC);
	print_test_ptrarrrev("ptrarrrev (single item)         ",	FALSE,        ptrarr_A,     ptrarr_A);
	print_test_ptrarrrev("ptrarrrev (empty array)         ",	FALSE,        ptrarr_empty, ptrarr_empty);
	print_test_ptrarrrev("ptrarrrev (null array)          ",	ALLOW_SIGSEGV, NULL,        NULL);
}
#endif



/*============================================================================*\
||                       Tests: concatenation operations                      ||
\*============================================================================*/



#ifndef c_ptrarrconcat
void test_ptrarrconcat(void)	{}
#warning "ptrarrconcat() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrconcat(char const* test_name, t_testflags flags,
		void** expecting,
		void** ptrarr1,
		void** ptrarr2)
{
	TEST_INIT(ptrarr)
	TEST_PERFORM(	ptrarrconcat, _PTRS(ptrarr1), _PTRS(ptrarr2))
	TEST_PRINT(ptrarr,	ptrarrconcat, "ptrarr1=%p, ptrarr2=%p", (void*)ptrarr1, (void*)ptrarr2)
	TEST_FREE_RESULT(c_ptrarrfree)
}
void	test_ptrarrconcat(void)
{
/*	| TEST FUNCTION         | TEST NAME                       | TESTFLAGS     | EXPECTING  | TEST ARGS			*/
	print_test_ptrarrconcat("ptrarrconcat                    ",	FALSE,        ptrarr_ABCD, ptrarr_AB,    ptrarr_CD);
	print_test_ptrarrconcat("ptrarrconcat (empty lhs)        ",	FALSE,        ptrarr_ABC,  ptrarr_empty, ptrarr_ABC);
	print_test_ptrarrconcat("ptrarrconcat (empty rhs)        ",	FALSE,        ptrarr_ABC,  ptrarr_ABC,   ptrarr_empty);
	print_test_ptrarrconcat("ptrarrconcat (null lhs)         ",	ALLOW_SIGSEGV, NULL,       NULL,         ptrarr_ABC);
	print_test_ptrarrconcat("ptrarrconcat (null rhs)         ",	ALLOW_SIGSEGV, NULL,       ptrarr_ABC,   NULL);
}
#endif



#ifndef c_ptrarrappend
void test_ptrarrappend(void)	{}
#warning "ptrarrappend() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrappend(char const* test_name, t_testflags flags,
		void** expecting,
		void** dest_base,
		void** src)
{
	TEST_INIT(ptrarr)
	TEST_PERFORM_(result, perform_append, dest_base, src)
	test.expect = expecting;
	TEST_PRINT(ptrarr,	ptrarrappend, "dest=%p, src=%p", (void*)dest_base, (void*)src)
	TEST_FREE_RESULT(c_ptrarrfree)
}
void	test_ptrarrappend(void)
{
/*	| TEST FUNCTION         | TEST NAME                       | TESTFLAGS | EXPECTING  | TEST ARGS			*/
	print_test_ptrarrappend("ptrarrappend                    ",	FALSE,    ptrarr_ABCD, ptrarr_AB,    ptrarr_CD);
	print_test_ptrarrappend("ptrarrappend (to empty array)   ",	FALSE,    ptrarr_CD,   ptrarr_empty, ptrarr_CD);
}
#endif



#ifndef c_ptrarrprepend
void test_ptrarrprepend(void)	{}
#warning "ptrarrprepend() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrprepend(char const* test_name, t_testflags flags,
		void** expecting,
		void** src,
		void** dest_base)
{
	TEST_INIT(ptrarr)
	TEST_PERFORM_(result, perform_prepend, src, dest_base)
	test.expect = expecting;
	TEST_PRINT(ptrarr,	ptrarrprepend, "src=%p, dest=%p", (void*)src, (void*)dest_base)
	TEST_FREE_RESULT(c_ptrarrfree)
}
void	test_ptrarrprepend(void)
{
/*	| TEST FUNCTION          | TEST NAME                       | TESTFLAGS | EXPECTING  | TEST ARGS			*/
	print_test_ptrarrprepend("ptrarrprepend                   ",	FALSE,    ptrarr_ABCD, ptrarr_AB, ptrarr_CD);
	print_test_ptrarrprepend("ptrarrprepend (empty src)       ",	FALSE,    ptrarr_CD,   ptrarr_empty, ptrarr_CD);
}
#endif



#ifndef c_ptrarrmerge
void test_ptrarrmerge(void)	{}
#warning "ptrarrmerge() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrmerge(char const* test_name, t_testflags flags,
		void** expecting,
		void** base1,
		void** base2)
{
	TEST_INIT(ptrarr)
	TEST_PERFORM_(result, perform_merge, base1, base2)
	test.expect = expecting;
	TEST_PRINT(ptrarr,	ptrarrmerge, "ptrarr1=%p, ptrarr2=%p", (void*)base1, (void*)base2)
	TEST_FREE_RESULT(c_ptrarrfree)
}
void	test_ptrarrmerge(void)
{
/*	| TEST FUNCTION        | TEST NAME                       | TESTFLAGS | EXPECTING  | TEST ARGS			*/
	print_test_ptrarrmerge("ptrarrmerge                     ",	FALSE,    ptrarr_ABCD, ptrarr_AB,    ptrarr_CD);
	print_test_ptrarrmerge("ptrarrmerge (both empty)        ",	FALSE,    ptrarr_empty, ptrarr_empty, ptrarr_empty);
}
#endif



#ifndef c_ptrarrjoin
void test_ptrarrjoin(void)	{}
#warning "ptrarrjoin() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrjoin(char const* test_name, t_testflags flags,
		void** expecting,
		void*** ptrarrs,
		void** sep)
{
	TEST_INIT(ptrarr)
	TEST_PERFORM(	ptrarrjoin, (void* const**)ptrarrs, _PTRS(sep))
	TEST_PRINT(ptrarr,	ptrarrjoin, "ptrarrs=%p, sep=%p", (void*)ptrarrs, (void*)sep)
	TEST_FREE_RESULT(c_ptrarrfree)
}
void	test_ptrarrjoin(void)
{
/*	| TEST FUNCTION       | TEST NAME                       | TESTFLAGS | EXPECTING    | TEST ARGS			*/
	print_test_ptrarrjoin("ptrarrjoin                      ",	FALSE,    ptrarr_ABXCD, ptrarrs_2,    ptrarr_X);
	print_test_ptrarrjoin("ptrarrjoin (empty separator)    ",	FALSE,    ptrarr_ABCD,  ptrarrs_2,    ptrarr_empty);
	print_test_ptrarrjoin("ptrarrjoin (single array)       ",	FALSE,    ptrarr_AB,    ptrarrs_1,    ptrarr_empty);
	print_test_ptrarrjoin("ptrarrjoin (no arrays)          ",	FALSE,    ptrarr_empty, ptrarrs_none, ptrarr_empty);
}
#endif



/*============================================================================*\
||                        Tests: comparison operations                        ||
\*============================================================================*/



#ifndef c_ptrarrequ
void test_ptrarrequ(void)	{}
#warning "ptrarrequ() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrequ(char const* test_name, t_testflags flags,
		t_bool expecting,
		void** ptrarr1,
		void** ptrarr2)
{
	TEST_INIT(bool)
	TEST_PERFORM(	ptrarrequ, _CPTRS(ptrarr1), _CPTRS(ptrarr2))
	TEST_PRINT(bool,ptrarrequ, "ptrarr1=%p, ptrarr2=%p", (void*)ptrarr1, (void*)ptrarr2)
}
void	test_ptrarrequ(void)
{
/*	| TEST FUNCTION      | TEST NAME                       | TESTFLAGS     | EXPECTING | TEST ARGS			*/
	print_test_ptrarrequ("ptrarrequ (same content)        ",	FALSE,        TRUE,      ptrarr_ABC,   ptrarr_ABC_bis);
	print_test_ptrarrequ("ptrarrequ (same pointer)        ",	FALSE,        TRUE,      ptrarr_ABC,   ptrarr_ABC);
	print_test_ptrarrequ("ptrarrequ (different order)     ",	FALSE,        FALSE,     ptrarr_ABC,   ptrarr_CBA);
	print_test_ptrarrequ("ptrarrequ (different lengths)   ",	FALSE,        FALSE,     ptrarr_ABC,   ptrarr_AB);
	print_test_ptrarrequ("ptrarrequ (prefix relation)     ",	FALSE,        FALSE,     ptrarr_AB,    ptrarr_ABC);
	print_test_ptrarrequ("ptrarrequ (both empty)          ",	FALSE,        TRUE,      ptrarr_empty, ptrarr_empty);
	print_test_ptrarrequ("ptrarrequ (null lhs)            ",	ALLOW_SIGSEGV, FALSE,    NULL,         ptrarr_ABC);
	print_test_ptrarrequ("ptrarrequ (both null)           ",	ALLOW_SIGSEGV, TRUE,     NULL,         NULL);
}
#endif



#ifndef c_ptrarrnequ
void test_ptrarrnequ(void)	{}
#warning "ptrarrnequ() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrnequ(char const* test_name, t_testflags flags,
		t_bool expecting,
		void** ptrarr1,
		void** ptrarr2,
		t_uint n)
{
	TEST_INIT(bool)
	TEST_PERFORM(	ptrarrnequ, _CPTRS(ptrarr1), _CPTRS(ptrarr2), n)
	TEST_PRINT(bool,ptrarrnequ, "n=" SF_UINT, n)
}
void	test_ptrarrnequ(void)
{
/*	| TEST FUNCTION       | TEST NAME                       | TESTFLAGS | EXPECTING | TEST ARGS			*/
	print_test_ptrarrnequ("ptrarrnequ (equal prefix)       ",	FALSE,    TRUE,      ptrarr_ABC, ptrarr_ABX, 2);
	print_test_ptrarrnequ("ptrarrnequ (unequal item)       ",	FALSE,    FALSE,     ptrarr_ABC, ptrarr_ABX, 3);
	print_test_ptrarrnequ("ptrarrnequ (n = 0)              ",	FALSE,    TRUE,      ptrarr_ABC, ptrarr_CBA, 0);
}
#endif



#ifndef c_ptrarrcmp
void test_ptrarrcmp(void)	{}
#warning "ptrarrcmp() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrcmp(char const* test_name, t_testflags flags,
		t_sint expecting,
		void** ptrarr1,
		void** ptrarr2)
{
	TEST_INIT(sint)
	TEST_PERFORM(	ptrarrcmp, _CPTRS(ptrarr1), _CPTRS(ptrarr2), compare_values)
	TEST_PRINT(sint,ptrarrcmp, "ptrarr1=%p, ptrarr2=%p", (void*)ptrarr1, (void*)ptrarr2)
}
void	test_ptrarrcmp(void)
{
/*	| TEST FUNCTION      | TEST NAME                       | TESTFLAGS | EXPECTING | TEST ARGS			*/
	print_test_ptrarrcmp("ptrarrcmp (equal contents)      ",	FALSE,    0,         ptrarr_ABC, ptrarr_ABC_bis);
	print_test_ptrarrcmp("ptrarrcmp (lesser)              ",	FALSE,    -1,        ptrarr_ABC, ptrarr_ABD); // NB: item values are C=3, D=4: so, 3 - 4 = -1
	print_test_ptrarrcmp("ptrarrcmp (greater)             ",	FALSE,    +1,        ptrarr_ABD, ptrarr_ABC);
	print_test_ptrarrcmp("ptrarrcmp (first diff wins)     ",	FALSE,    -1,        ptrarr_ABC, ptrarr_BAC); // NB: A=1, B=2: so, 1 - 2 = -1
}
#endif



#ifndef c_ptrarrncmp
void test_ptrarrncmp(void)	{}
#warning "ptrarrncmp() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrncmp(char const* test_name, t_testflags flags,
		t_sint expecting,
		void** ptrarr1,
		void** ptrarr2,
		t_uint n)
{
	TEST_INIT(sint)
	TEST_PERFORM(	ptrarrncmp, _CPTRS(ptrarr1), _CPTRS(ptrarr2), compare_values, n)
	TEST_PRINT(sint,ptrarrncmp, "n=" SF_UINT, n)
}
void	test_ptrarrncmp(void)
{
/*	| TEST FUNCTION       | TEST NAME                       | TESTFLAGS | EXPECTING | TEST ARGS			*/
	print_test_ptrarrncmp("ptrarrncmp (within prefix)      ",	FALSE,    0,         ptrarr_ABC, ptrarr_ABD, 2);
	print_test_ptrarrncmp("ptrarrncmp (up to difference)   ",	FALSE,    -1,        ptrarr_ABC, ptrarr_ABD, 3);
}
#endif



/*============================================================================*\
||                          Tests: searching operations                       ||
\*============================================================================*/



#ifndef c_ptrarrfind
void test_ptrarrfind(void)	{}
#warning "ptrarrfind() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrfind(char const* test_name, t_testflags flags,
		void const* expecting,
		void** ptrarr,
		void* item)
{
	TEST_INIT(ptr)
	TEST_PERFORM(	ptrarrfind, _PTRS(ptrarr), item)
	TEST_PRINT(ptr,	ptrarrfind, "item=%p", item)
}
void	test_ptrarrfind(void)
{
/*	| TEST FUNCTION       | TEST NAME                       | TESTFLAGS | EXPECTING            | TEST ARGS			*/
	print_test_ptrarrfind("ptrarrfind                      ",	FALSE,    &ptrarr_ABC[1],       ptrarr_ABC, PB);
	print_test_ptrarrfind("ptrarrfind (first occurrence)   ",	FALSE,    &ptrarr_ABA[0],       ptrarr_ABA, PA);
	print_test_ptrarrfind("ptrarrfind (item not present)   ",	FALSE,    NULL,                 ptrarr_ABC, PX);
}
#endif



#ifndef c_ptrarrffind
void test_ptrarrffind(void)	{}
#warning "ptrarrffind() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrffind(char const* test_name, t_testflags flags,
		void const* expecting,
		void** ptrarr,
		t_bool (*match)(void const* ptr))
{
	TEST_INIT(ptr)
	TEST_PERFORM(	ptrarrffind, _PTRS(ptrarr), match)
	TEST_PRINT(ptr,	ptrarrffind, "match=%p", (void*)(t_uintptr)match)
}
void	test_ptrarrffind(void)
{
/*	| TEST FUNCTION        | TEST NAME                       | TESTFLAGS | EXPECTING        | TEST ARGS			*/
	print_test_ptrarrffind("ptrarrffind                     ",	FALSE,    &ptrarr_ABC[2],   ptrarr_ABC, match_is_c);
	print_test_ptrarrffind("ptrarrffind (no match)          ",	FALSE,    NULL,             ptrarr_AB,  match_is_c);
}
#endif



#ifndef c_ptrarrfindi
void test_ptrarrfindi(void)	{}
#warning "ptrarrfindi() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrfindi(char const* test_name, t_testflags flags,
		t_sint expecting,
		void** ptrarr,
		void* item)
{
	TEST_INIT(sint)
	TEST_PERFORM(	ptrarrfindi, _CPTRS(ptrarr), item)
	TEST_PRINT(sint,ptrarrfindi, "item=%p", item)
}
void	test_ptrarrfindi(void)
{
/*	| TEST FUNCTION        | TEST NAME                       | TESTFLAGS | EXPECTING | TEST ARGS			*/
	print_test_ptrarrfindi("ptrarrfindi                     ",	FALSE,    2,         ptrarr_ABC, PC);
	print_test_ptrarrfindi("ptrarrfindi (first occurrence)  ",	FALSE,    0,         ptrarr_ABA, PA);
	print_test_ptrarrfindi("ptrarrfindi (item not present)  ",	FALSE,    -1,        ptrarr_ABC, PX);
}
#endif



#ifndef c_ptrarrffindi
void test_ptrarrffindi(void)	{}
#warning "ptrarrffindi() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrffindi(char const* test_name, t_testflags flags,
		t_sint expecting,
		void** ptrarr,
		t_bool (*match)(void const* ptr))
{
	TEST_INIT(sint)
	TEST_PERFORM(	ptrarrffindi, _CPTRS(ptrarr), match)
	TEST_PRINT(sint,ptrarrffindi, "match=%p", (void*)(t_uintptr)match)
}
void	test_ptrarrffindi(void)
{
/*	| TEST FUNCTION         | TEST NAME                       | TESTFLAGS | EXPECTING | TEST ARGS			*/
	print_test_ptrarrffindi("ptrarrffindi                    ",	FALSE,    2,         ptrarr_ABC, match_is_c);
	print_test_ptrarrffindi("ptrarrffindi (no match)         ",	FALSE,    -1,        ptrarr_AB,  match_is_c);
}
#endif



#ifndef c_ptrarrcount
void test_ptrarrcount(void)	{}
#warning "ptrarrcount() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrcount(char const* test_name, t_testflags flags,
		t_uint expecting,
		void** ptrarr,
		void* item)
{
	TEST_INIT(uint)
	TEST_PERFORM(	ptrarrcount, _CPTRS(ptrarr), item)
	TEST_PRINT(uint,ptrarrcount, "item=%p", item)
}
void	test_ptrarrcount(void)
{
/*	| TEST FUNCTION        | TEST NAME                       | TESTFLAGS | EXPECTING | TEST ARGS			*/
	print_test_ptrarrcount("ptrarrcount                     ",	FALSE,    2,         ptrarr_ABA, PA);
	print_test_ptrarrcount("ptrarrcount (all items)         ",	FALSE,    3,         ptrarr_AAA, PA);
	print_test_ptrarrcount("ptrarrcount (item not present)  ",	FALSE,    0,         ptrarr_ABC, PX);
}
#endif



#ifndef c_ptrarrcontains
void test_ptrarrcontains(void)	{}
#warning "ptrarrcontains() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrcontains(char const* test_name, t_testflags flags,
		t_bool expecting,
		void** ptrarr,
		void* item)
{
	TEST_INIT(bool)
	TEST_PERFORM(	ptrarrcontains, _CPTRS(ptrarr), item)
	TEST_PRINT(bool,ptrarrcontains, "item=%p", item)
}
void	test_ptrarrcontains(void)
{
/*	| TEST FUNCTION           | TEST NAME                       | TESTFLAGS | EXPECTING | TEST ARGS			*/
	print_test_ptrarrcontains("ptrarrcontains                  ",	FALSE,    TRUE,      ptrarr_ABC,   PB);
	print_test_ptrarrcontains("ptrarrcontains (not present)    ",	FALSE,    FALSE,     ptrarr_ABC,   PX);
	print_test_ptrarrcontains("ptrarrcontains (empty array)    ",	FALSE,    FALSE,     ptrarr_empty, PA);
}
#endif



#ifndef c_ptrarrhas
void test_ptrarrhas(void)	{}
#warning "ptrarrhas() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrhas(char const* test_name, t_testflags flags,
		t_bool expecting,
		void** ptrarr,
		void** target)
{
	TEST_INIT(bool)
	TEST_PERFORM(	ptrarrhas, _CPTRS(ptrarr), _CPTRS(target))
	TEST_PRINT(bool,ptrarrhas, "ptrarr=%p, target=%p", (void*)ptrarr, (void*)target)
}
void	test_ptrarrhas(void)
{
/*	| TEST FUNCTION      | TEST NAME                       | TESTFLAGS | EXPECTING | TEST ARGS			*/
	print_test_ptrarrhas("ptrarrhas (one shared item)     ",	FALSE,    TRUE,      ptrarr_ABC, ptrarr_CD);
	print_test_ptrarrhas("ptrarrhas (no shared items)     ",	FALSE,    FALSE,     ptrarr_AB,  ptrarr_CD);
	print_test_ptrarrhas("ptrarrhas (all shared items)    ",	FALSE,    TRUE,      ptrarr_AB,  ptrarr_ABCD);
}
#endif



#ifndef c_ptrarrhasonly
void test_ptrarrhasonly(void)	{}
#warning "ptrarrhasonly() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrhasonly(char const* test_name, t_testflags flags,
		t_bool expecting,
		void** ptrarr,
		void** target)
{
	TEST_INIT(bool)
	TEST_PERFORM(	ptrarrhasonly, _CPTRS(ptrarr), _CPTRS(target))
	TEST_PRINT(bool,ptrarrhasonly, "ptrarr=%p, target=%p", (void*)ptrarr, (void*)target)
}
void	test_ptrarrhasonly(void)
{
/*	| TEST FUNCTION          | TEST NAME                       | TESTFLAGS | EXPECTING | TEST ARGS			*/
	print_test_ptrarrhasonly("ptrarrhasonly (all in target)   ",	FALSE,    TRUE,      ptrarr_AB,  ptrarr_ABCD);
	print_test_ptrarrhasonly("ptrarrhasonly (one not in)      ",	FALSE,    FALSE,     ptrarr_ABC, ptrarr_AB);
	print_test_ptrarrhasonly("ptrarrhasonly (empty array)     ",	FALSE,    TRUE,      ptrarr_empty, ptrarr_AB);
}
#endif



/*============================================================================*\
||                        Tests: functional operations                        ||
\*============================================================================*/



#ifndef c_ptrarriter
void test_ptrarriter(void)	{}
#warning "ptrarriter() test suite function defined, but the function isn't defined."
#else
//! SCENARIO: iterates over an array of heap-allocated ints with an in-place mutation, and verifies the pointed-to values
static
t_bool	scenario_iterate_inplace(void)
{
	void**	arr;
	t_bool	result;
	int*	values[3];

	values[0] = (int*)malloc(sizeof(int));	*values[0] = 1;
	values[1] = (int*)malloc(sizeof(int));	*values[1] = 2;
	values[2] = (int*)malloc(sizeof(int));	*values[2] = 3;
	arr = c_ptrarrcreate(3, values[0], values[1], values[2]);
	c_ptrarriter(arr, iter_increment);
	result = (*(int*)arr[0] == 2 && *(int*)arr[1] == 3 && *(int*)arr[2] == 4);
	c_ptrarrffree(arr, free);
	return (result);
}
//! SCENARIO: iterates with a callback which returns new allocations (the old items should be freed by Iterate itself)
static
t_bool	scenario_iterate_replace(void)
{
	void**	arr;
	t_bool	result;
	int*	values[2];

	values[0] = (int*)malloc(sizeof(int));	*values[0] = 5;
	values[1] = (int*)malloc(sizeof(int));	*values[1] = 7;
	arr = c_ptrarrcreate(2, values[0], values[1]);
	c_ptrarriter(arr, iter_double_new);
	result = (*(int*)arr[0] == 10 && *(int*)arr[1] == 14);
	c_ptrarrffree(arr, free);
	return (result);
}
//! SCENARIO: iterates with an index-aware callback, and verifies the pointed-to values
static
t_bool	scenario_iterate_i(void)
{
	void**	arr;
	t_bool	result;
	int*	values[3];

	values[0] = (int*)malloc(sizeof(int));	*values[0] = 10;
	values[1] = (int*)malloc(sizeof(int));	*values[1] = 10;
	values[2] = (int*)malloc(sizeof(int));	*values[2] = 10;
	arr = c_ptrarrcreate(3, values[0], values[1], values[2]);
	c_ptrarriiter(arr, iter_i_add_index);
	result = (*(int*)arr[0] == 10 && *(int*)arr[1] == 11 && *(int*)arr[2] == 12);
	c_ptrarrffree(arr, free);
	return (result);
}
void	print_test_ptrarriter_scenario(char const* test_name, t_testflags flags,
		t_bool expecting,
		t_bool (*scenario)(void), char const* description)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario)
	test.expect = expecting;
	TEST_PRINT(bool,ptrarriter, "%s", description)
}
void	test_ptrarriter(void)
{
/*	| TEST FUNCTION              | TEST NAME                       | TESTFLAGS | EXPECTING | TEST ARGS			*/
	print_test_ptrarriter_scenario("ptrarriter (in-place mutation)  ",	FALSE, TRUE,
		scenario_iterate_inplace, "(incrementing each pointed-to int)");
	print_test_ptrarriter_scenario("ptrarriter (item replacement)   ",	FALSE, TRUE,
		scenario_iterate_replace, "(replacing each item with a new allocation)");
	print_test_ptrarriter_scenario("ptrarriiter (index-aware)       ",	FALSE, TRUE,
		scenario_iterate_i,       "(adding the index to each pointed-to int)");
}
#endif



#ifndef c_ptrarrmap
void test_ptrarrmap(void)	{}
#warning "ptrarrmap() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrmap(char const* test_name, t_testflags flags,
		void** expecting,
		void** ptrarr,
		void* (*map)(void const* ptr))
{
	TEST_INIT(ptrarr)
	TEST_PERFORM(	ptrarrmap, _PTRS(ptrarr), map)
	TEST_PRINT(ptrarr,	ptrarrmap, "map=%p", (void*)(t_uintptr)map)
	TEST_FREE_RESULT(c_ptrarrfree)
}
void	print_test_ptrarrimap(char const* test_name, t_testflags flags,
		void** expecting,
		void** ptrarr,
		void* (*map)(void const* ptr, t_uint index))
{
	TEST_INIT(ptrarr)
	TEST_PERFORM(	ptrarrimap, _PTRS(ptrarr), map)
	TEST_PRINT(ptrarr,	ptrarrimap, "map=%p", (void*)(t_uintptr)map)
	TEST_FREE_RESULT(c_ptrarrfree)
}
void	test_ptrarrmap(void)
{
/*	| TEST FUNCTION       | TEST NAME                       | TESTFLAGS | EXPECTING   | TEST ARGS			*/
	print_test_ptrarrmap ("ptrarrmap                       ",	FALSE,    ptrarr_BAC,   ptrarr_ABC,   map_swap_ab);
	print_test_ptrarrmap ("ptrarrmap (empty array)         ",	FALSE,    ptrarr_empty, ptrarr_empty, map_swap_ab);
	print_test_ptrarrimap("ptrarrimap                      ",	FALSE,    ptrarr_XBC,   ptrarr_ABC,   map_i_first_to_x);
}
#endif



#ifndef c_ptrarrfilter
void test_ptrarrfilter(void)	{}
#warning "ptrarrfilter() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrfilter(char const* test_name, t_testflags flags,
		void** expecting,
		void** ptrarr,
		t_bool (*filter)(void const* ptr))
{
	TEST_INIT(ptrarr)
	TEST_PERFORM(	ptrarrfilter, _PTRS(ptrarr), filter)
	TEST_PRINT(ptrarr,	ptrarrfilter, "filter=%p", (void*)(t_uintptr)filter)
	TEST_FREE_RESULT(c_ptrarrfree)
}
void	print_test_ptrarrifilter(char const* test_name, t_testflags flags,
		void** expecting,
		void** ptrarr,
		t_bool (*filter)(void const* ptr, t_uint index))
{
	TEST_INIT(ptrarr)
	TEST_PERFORM(	ptrarrifilter, _PTRS(ptrarr), filter)
	TEST_PRINT(ptrarr,	ptrarrifilter, "filter=%p", (void*)(t_uintptr)filter)
	TEST_FREE_RESULT(c_ptrarrfree)
}
void	test_ptrarrfilter(void)
{
/*	| TEST FUNCTION          | TEST NAME                       | TESTFLAGS | EXPECTING   | TEST ARGS			*/
	print_test_ptrarrfilter ("ptrarrfilter (keep matching)    ",	FALSE,    ptrarr_AA,    ptrarr_ABA, filter_is_a);
	print_test_ptrarrfilter ("ptrarrfilter (keep others)      ",	FALSE,    ptrarr_B,     ptrarr_ABA, filter_not_a);
	print_test_ptrarrfilter ("ptrarrfilter (none match)       ",	FALSE,    ptrarr_empty, ptrarr_AAA, filter_not_a);
	print_test_ptrarrifilter("ptrarrifilter (even indices)    ",	FALSE,    ptrarr_AC,    ptrarr_ABCD, filter_i_even);
}
#endif



#ifndef c_ptrarrreduce
void test_ptrarrreduce(void)	{}
#warning "ptrarrreduce() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrreduce(char const* test_name, t_testflags flags,
		void const* expecting,
		void** ptrarr,
		void* (*f)(void const* ptr, void* acc))
{
	TEST_INIT(ptr)
	TEST_PERFORM(	ptrarrreduce, _CPTRS(ptrarr), f)
	TEST_PRINT(ptr,	ptrarrreduce, "f=%p", (void*)(t_uintptr)f)
}
void	test_ptrarrreduce(void)
{
/*	| TEST FUNCTION         | TEST NAME                       | TESTFLAGS | EXPECTING  | TEST ARGS			*/
	print_test_ptrarrreduce("ptrarrreduce (count items)      ",	FALSE,    (void*)3,    ptrarr_ABC,   reduce_count);
	print_test_ptrarrreduce("ptrarrreduce (last item wins)   ",	FALSE,    PC,          ptrarr_ABC,   reduce_last);
	print_test_ptrarrreduce("ptrarrreduce (empty array)      ",	FALSE,    NULL,        ptrarr_empty, reduce_count);
	print_test_ptrarrreduce("ptrarrreduce (sum of values)    ",	FALSE,    (void*)6,    ptrarr_ABC,   fold_sum_values); // NB: values are A=1, B=2, C=3
}
#endif



#ifndef c_ptrarrfold
void test_ptrarrfold(void)	{}
#warning "ptrarrfold() test suite function defined, but the function isn't defined."
#else
void	print_test_ptrarrfold(char const* test_name, t_testflags flags,
		void const* expecting,
		void** ptrarr,
		void* (*f)(void const* ptr, void* acc),
		void* initial)
{
	TEST_INIT(ptr)
	TEST_PERFORM(	ptrarrfold, _CPTRS(ptrarr), f, initial)
	TEST_PRINT(ptr,	ptrarrfold, "f=%p, initial=%p", (void*)(t_uintptr)f, initial)
}
void	print_test_ptrarrifold(char const* test_name, t_testflags flags,
		void const* expecting,
		void** ptrarr,
		void* (*f)(void const* ptr, void* acc, t_uint index),
		void* initial)
{
	TEST_INIT(ptr)
	TEST_PERFORM(	ptrarrifold, _CPTRS(ptrarr), f, initial)
	TEST_PRINT(ptr,	ptrarrifold, "f=%p, initial=%p", (void*)(t_uintptr)f, initial)
}
void	test_ptrarrfold(void)
{
/*	| TEST FUNCTION        | TEST NAME                       | TESTFLAGS | EXPECTING  | TEST ARGS			*/
	print_test_ptrarrfold ("ptrarrfold (sum, with initial)  ",	FALSE,    (void*)16,   ptrarr_ABC,   fold_sum_values, (void*)10);
	print_test_ptrarrfold ("ptrarrfold (empty array)        ",	FALSE,    (void*)10,   ptrarr_empty, fold_sum_values, (void*)10);
	print_test_ptrarrifold("ptrarrifold (sum of indices)    ",	FALSE,    (void*)6,    ptrarr_ABCD,  fold_i_sum_indices, (void*)0); // NB: 0+1+2+3 = 6
}
#endif



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_pointerarray(void)
{
	print_suite_title("libccc/pointerarray");

	test_ptrarrlen();
	test_ptrarrnew();
	test_ptrarrcreate();
	test_ptrarrdup();
	test_ptrarrsub();
	test_ptrarrcpy();
	test_ptrarradd();
	test_ptrarrinsert();
	test_ptrarrwedge();
	test_ptrarrdelat();
	test_ptrarrdelone();
	test_ptrarrdelall();
	test_ptrarrrep();
	test_ptrarrrepfirst();
	test_ptrarrreplast();
	test_ptrarrrev();
	test_ptrarrconcat();
	test_ptrarrappend();
	test_ptrarrprepend();
	test_ptrarrmerge();
	test_ptrarrjoin();
	test_ptrarrequ();
	test_ptrarrnequ();
	test_ptrarrcmp();
	test_ptrarrncmp();
	test_ptrarrfind();
	test_ptrarrffind();
	test_ptrarrfindi();
	test_ptrarrffindi();
	test_ptrarrcount();
	test_ptrarrcontains();
	test_ptrarrhas();
	test_ptrarrhasonly();
	test_ptrarriter();
	test_ptrarrmap();
	test_ptrarrfilter();
	test_ptrarrreduce();
	test_ptrarrfold();

	return (OK);
}
