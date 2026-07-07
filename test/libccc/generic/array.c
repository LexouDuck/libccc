
#include "libccc/generic/array.c"

#include "test.h"
#include "test_utils.h"



/*============================================================================*\
||                             Testing Utilities                              ||
\*============================================================================*/

/*
**	NOTE: this test suite exercises the default instantiation of the generic
**	array type (ie: `T` is `void*`, and `T_NAME` is `any`), which is included
**	just above. With this instantiation, the `T_EQUALS()` macro is a simple
**	pointer comparison: so, all of the "equality"-based array functions (like
**	Remove, Find, Count, Contains, Equals, etc) match items by their pointer
**	*identity*, not by their pointed-to contents - the tests below check this
**	semantic explicitly (see the `g_arr_twin` test cases).
**
**	The items used are `char*` strings, so that expected results can be
**	written legibly: every array-returning function is tested by serializing
**	the result array into a string of the form `"[item1][item2][item3]"`
**	(an empty/NULL array serializes to `""`), and comparing with `print_test_str`.
*/

//! The items used to build the test arrays (matching items must be the same pointer)
static char* const	g_arr_item[4] =
{
	"Omae",
	" wa ",
	"mou ",
	"shindeiru.",
};
//! Has the same content as `g_arr_item[0]`, but is a different pointer
static char	g_arr_twin[] = "Omae";

//! Serializes the given array of `char*` items into a newly allocated string: `"[item1][item2]"`
static
char*	gen_array_tostr(s_array(any) const* array)
{
	size_t	length = 0;
	char*	result;
	char const*	str;
	t_uint	i;

	if (array == NULL)
		return (strdup(""));
	for (i = 0; i < array->length; ++i)
	{
		length += 2 + (array->items[i] ? strlen((char const*)array->items[i]) : strlen("NULL"));
	}
	result = (char*)malloc(length + 1);
	if (result == NULL)
		return (NULL);
	length = 0;
	for (i = 0; i < array->length; ++i)
	{
		str = (array->items[i] ? (char const*)array->items[i] : "NULL");
		result[length++] = '[';
		strcpy(result + length, str);
		length += strlen(str);
		result[length++] = ']';
	}
	result[length] = '\0';
	return (result);
}

//! Serializes the given array (like gen_array_tostr()), and then deletes it
static
char*	gen_array_consume(s_array(any)* array)
{
	char*	result = gen_array_tostr(array);
	if (array)
		c_arrfree(any)(array);
	return (result);
}

//! Builds the standard 4-item test array: `[Omae][ wa ][mou ][shindeiru.]`
static
s_array(any)*	gen_array_fixture(void)
{
	return (c_arrcreate(any)(4,
		(void*)g_arr_item[0],
		(void*)g_arr_item[1],
		(void*)g_arr_item[2],
		(void*)g_arr_item[3]));
}

//! The expected serialization of the standard test array fixture
#define GEN_ARRAY_FIXTURE_STR	"[Omae][ wa ][mou ][shindeiru.]"



/*============================================================================*\
||                           Array: basic operations                          ||
\*============================================================================*/

#ifndef c_arritem
void test_arritem(void)	{}
#warning "arritem() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arritem(void* item)
{
	s_array(any)	result = c_arritem(any)(item);
	char*	str = gen_array_tostr(&result);
	if (result.items)
		free(result.items);
	return (str);
}
void	print_test_arritem(char const* test_name, t_testflags flags,
		char const* expecting,
		void* item)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arritem, item)
	TEST_PRINT(str,	arritem, "item=%p", item)
	TEST_FREE()
}
void	test_arritem(void)
{
//	| TEST FUNCTION    | TEST NAME            |TESTFLAG| EXPECTING      | TEST ARGS
	print_test_arritem("arritem            ",	FALSE,	"[Omae]",        (void*)g_arr_item[0]);
	print_test_arritem("arritem            ",	FALSE,	"[shindeiru.]",  (void*)g_arr_item[3]);
	print_test_arritem("arritem (empty str)",	FALSE,	"[]",            (void*)"");
	print_test_arritem("arritem (null item)",	FALSE,	"[NULL]",        NULL);
}
#endif



#ifndef c_arrget
void test_arrget(void)	{}
#warning "arrget() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrget(s_array(any) const* array, t_uint index)
{
	void**	result = c_arrget(any)(array, index);
	if (result == NULL)
		return (strdup("(null)"));
	return (strdup(*result ? (char const*)*result : "NULL"));
}
void	print_test_arrget(char const* test_name, t_testflags flags,
		char const* expecting,
		s_array(any) const* array,
		t_uint index)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrget, array, index)
	TEST_PRINT(str,	arrget, "array=%p, index=%u", (void const*)array, index)
	TEST_FREE()
}
void	test_arrget(void)
{
	s_array(any)*	fixture = gen_array_fixture();
//	| TEST FUNCTION   | TEST NAME             |TESTFLAG| EXPECTING    | TEST ARGS
	print_test_arrget("arrget             ",	FALSE,	"Omae",        fixture, 0);
	print_test_arrget("arrget             ",	FALSE,	" wa ",        fixture, 1);
	print_test_arrget("arrget             ",	FALSE,	"mou ",        fixture, 2);
	print_test_arrget("arrget             ",	FALSE,	"shindeiru.",  fixture, 3);
	print_test_arrget("arrget (beyond end)",	FALSE,	"(null)",      fixture, 4);
	print_test_arrget("arrget (huge index)",	FALSE,	"(null)",      fixture, 12345);
	print_test_arrget("arrget (null array)",	FALSE,	"(null)",      NULL, 0);
	c_arrfree(any)(fixture);
}
#endif



#ifndef c_arrset
void test_arrset(void)	{}
#warning "arrset() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrset(t_uint index, void* item)
{
	s_array(any)*	array = gen_array_fixture();
	c_arrset(any)(array, index, item);
	return (gen_array_consume(array));
}
void	print_test_arrset(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint index,
		void* item)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrset, index, item)
	TEST_PRINT(str,	arrset, "index=%u, item=%p", index, item)
	TEST_FREE()
}
void	test_arrset(void)
{
//	| TEST FUNCTION   | TEST NAME             |TESTFLAG| EXPECTING                            | TEST ARGS
	print_test_arrset("arrset (first)     ",	FALSE,	"[YO][ wa ][mou ][shindeiru.]",        0, (void*)"YO");
	print_test_arrset("arrset (middle)    ",	FALSE,	"[Omae][ wa ][YO][shindeiru.]",        2, (void*)"YO");
	print_test_arrset("arrset (last)      ",	FALSE,	"[Omae][ wa ][mou ][YO]",              3, (void*)"YO");
	print_test_arrset("arrset (null item) ",	FALSE,	"[Omae][NULL][mou ][shindeiru.]",      1, NULL);
	print_test_arrset("arrset (beyond end)",	FALSE,	GEN_ARRAY_FIXTURE_STR,                 4, (void*)"YO");
	print_test_arrset("arrset (huge index)",	FALSE,	GEN_ARRAY_FIXTURE_STR,                 9999, (void*)"YO");
}
#endif



#ifndef c_arrnew
void test_arrnew(void)	{}
#warning "arrnew() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrnew(t_uint n, void* value)
{
	return (gen_array_consume(c_arrnew(any)(n, value)));
}
void	print_test_arrnew(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint n,
		void* value)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrnew, n, value)
	TEST_PRINT(str,	arrnew, "n=%u, value=%p", n, value)
	TEST_FREE()
}
void	test_arrnew(void)
{
//	| TEST FUNCTION   | TEST NAME           |TESTFLAG| EXPECTING              | TEST ARGS
	print_test_arrnew("arrnew             ",	FALSE,	"[yo]",                  1, (void*)"yo");
	print_test_arrnew("arrnew             ",	FALSE,	"[yo][yo][yo]",          3, (void*)"yo");
	print_test_arrnew("arrnew (null value)",	FALSE,	"[NULL][NULL]",          2, NULL);
	print_test_arrnew("arrnew (n = 0)     ",	FALSE,	"",                      0, (void*)"yo");
}
#endif



#ifndef c_arrcreate
void test_arrcreate(void)	{}
#warning "arrcreate() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrcreate(t_uint n)
{
	return (gen_array_consume(c_arrcreate(any)(n,
		(void*)g_arr_item[0],
		(void*)g_arr_item[1],
		(void*)g_arr_item[2],
		(void*)g_arr_item[3])));
}
void	print_test_arrcreate(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint n)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrcreate, n)
	TEST_PRINT(str,	arrcreate, "n=%u, ...", n)
	TEST_FREE()
}
void	test_arrcreate(void)
{
//	| TEST FUNCTION      | TEST NAME              |TESTFLAG| EXPECTING            | TEST ARGS
	print_test_arrcreate("arrcreate          ",	FALSE,	GEN_ARRAY_FIXTURE_STR, 4);
	print_test_arrcreate("arrcreate          ",	FALSE,	"[Omae][ wa ]",        2);
	print_test_arrcreate("arrcreate (1 item) ",	FALSE,	"[Omae]",              1);
	print_test_arrcreate("arrcreate (n = 0)  ",	FALSE,	"",                    0);
}
#endif



#ifndef c_arrdup
void test_arrdup(void)	{}
#warning "arrdup() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrdup(void)
{
	s_array(any)*	original = gen_array_fixture();
	s_array(any)*	result = c_arrdup(any)(original);
	c_arrfree(any)(original); // the duplicate must survive its original being freed
	return (gen_array_consume(result));
}
void	print_test_arrdup(char const* test_name, t_testflags flags,
		char const* expecting)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrdup)
	TEST_PRINT(str,	arrdup, "array=(4-item fixture)")
	TEST_FREE()
}
void	test_arrdup(void)
{
//	| TEST FUNCTION   | TEST NAME           |TESTFLAG| EXPECTING
	print_test_arrdup("arrdup             ",	FALSE,	GEN_ARRAY_FIXTURE_STR);
}
#endif



#ifndef c_arrsub
void test_arrsub(void)	{}
#warning "arrsub() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrsub(t_uint index, t_uint n)
{
	s_array(any)*	array = gen_array_fixture();
	s_array(any)*	result = c_arrsub(any)(array, index, n);
	char*	str = gen_array_consume(result);
	c_arrfree(any)(array);
	return (str);
}
void	print_test_arrsub(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint index,
		t_uint n)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrsub, index, n)
	TEST_PRINT(str,	arrsub, "index=%u, n=%u", index, n)
	TEST_FREE()
}
void	test_arrsub(void)
{
//	| TEST FUNCTION   | TEST NAME             |TESTFLAG| EXPECTING                       | TEST ARGS
	print_test_arrsub("arrsub (beginning)  ",	FALSE,	"[Omae][ wa ]",                   0, 2);
	print_test_arrsub("arrsub (middle)     ",	FALSE,	"[ wa ][mou ]",                   1, 2);
	print_test_arrsub("arrsub (end)        ",	FALSE,	"[mou ][shindeiru.]",             2, 2);
	print_test_arrsub("arrsub (single)     ",	FALSE,	"[ wa ]",                         1, 1);
	print_test_arrsub("arrsub (whole array)",	FALSE,	GEN_ARRAY_FIXTURE_STR,            0, 4);
	print_test_arrsub("arrsub (n=0 -> rest)",	FALSE,	"[mou ][shindeiru.]",             2, 0);
	print_test_arrsub("arrsub (bad index)  ",	FALSE,	"",                               4, 1);
	print_test_arrsub("arrsub (n too large)",	FALSE,	"",                               2, 3);
}
#endif



#ifndef c_arrcpy
void test_arrcpy(void)	{}
#warning "arrcpy() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrcpy(t_uint dest_i, t_uint src_i, t_uint n)
{
	s_array(any)*	dest = c_arrcreate(any)(4, (void*)"D0", (void*)"D1", (void*)"D2", (void*)"D3");
	s_array(any)*	src = gen_array_fixture();
	c_arrcpy(any)(dest, dest_i, src, src_i, n);
	c_arrfree(any)(src);
	return (gen_array_consume(dest));
}
void	print_test_arrcpy(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint dest_i,
		t_uint src_i,
		t_uint n)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrcpy, dest_i, src_i, n)
	TEST_PRINT(str,	arrcpy, "dest_i=%u, src_i=%u, n=%u", dest_i, src_i, n)
	TEST_FREE()
}
void	test_arrcpy(void)
{
//	| TEST FUNCTION   | TEST NAME             |TESTFLAG| EXPECTING                       | TEST ARGS
	print_test_arrcpy("arrcpy (full copy)  ",	FALSE,	GEN_ARRAY_FIXTURE_STR,            0, 0, 4);
	print_test_arrcpy("arrcpy (2 items)    ",	FALSE,	"[Omae][ wa ][D2][D3]",           0, 0, 2);
	print_test_arrcpy("arrcpy (offset dest)",	FALSE,	"[D0][D1][Omae][ wa ]",           2, 0, 2);
	print_test_arrcpy("arrcpy (offset src) ",	FALSE,	"[mou ][shindeiru.][D2][D3]",     0, 2, 2);
	print_test_arrcpy("arrcpy (n=0 -> rest)",	FALSE,	"[D0][mou ][shindeiru.][D3]",     1, 2, 0);
	print_test_arrcpy("arrcpy (bad dest_i) ",	FALSE,	"[D0][D1][D2][D3]",               4, 0, 1);
	print_test_arrcpy("arrcpy (bad src_i)  ",	FALSE,	"[D0][D1][D2][D3]",               0, 4, 1);
	print_test_arrcpy("arrcpy (n too large)",	FALSE,	"[D0][D1][D2][D3]",               2, 0, 3);
}
#endif



#ifndef c_arrdel
void test_arrdel(void)	{}
#warning "arrdel() test suite function defined, but the function isn't defined."
#else
static void*	c_gen_arrdel(void)
{
	s_array(any)*	array = gen_array_fixture();
	c_arrdel(any)(&array);
	return (array); // the given pointer must have been set to NULL
}
void	print_test_arrdel(char const* test_name, t_testflags flags,
		void const* expecting)
{
	TEST_INIT(ptr)
	TEST_PERFORM(gen_arrdel)
	TEST_PRINT(ptr,	arrdel, "array=(4-item fixture)")
}
void	test_arrdel(void)
{
//	| TEST FUNCTION   | TEST NAME           |TESTFLAG| EXPECTING
	print_test_arrdel("arrdel             ",	FALSE,	NULL);
}
#endif



#ifndef c_arrfdel
void test_arrfdel(void)	{}
#warning "arrfdel() test suite function defined, but the function isn't defined."
#else
static t_uint	g_arrfdel_count = 0;
static void	gen_arrfdel_delete(void** a_item)
{
	(void)a_item;
	g_arrfdel_count += 1;
}
static t_uint	c_gen_arrfdel(t_uint n)
{
	s_array(any)*	array = c_arrnew(any)(n, (void*)g_arr_item[0]);
	g_arrfdel_count = 0;
	c_arrfdel(any)(&array, gen_arrfdel_delete);
	if (array != NULL) // the given pointer must have been set to NULL
		return ((t_uint)-1);
	return (g_arrfdel_count); // amount of times the del() function was called
}
void	print_test_arrfdel(char const* test_name, t_testflags flags,
		t_uint expecting,
		t_uint n)
{
	TEST_INIT(uint)
	TEST_PERFORM(gen_arrfdel, n)
	TEST_PRINT(uint,	arrfdel, "array=(%u items), del=(counting function)", n)
}
void	test_arrfdel(void)
{
//	| TEST FUNCTION    | TEST NAME             |TESTFLAG| EXPECTING | TEST ARGS
	print_test_arrfdel("arrfdel             ",	FALSE,	4,          4);
	print_test_arrfdel("arrfdel (1 item)    ",	FALSE,	1,          1);
	print_test_arrfdel("arrfdel (empty)     ",	FALSE,	0,          0);
}
#endif



/*============================================================================*\
||                        Array: adding/removing items                        ||
\*============================================================================*/

#ifndef c_arradd
void test_arradd(void)	{}
#warning "arradd() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arradd(t_uint fixture_size, void* item)
{
	s_array(any)*	array = (fixture_size == 0 ? NULL : gen_array_fixture());
	array = c_arradd(any)(array, item);
	return (gen_array_consume(array));
}
void	print_test_arradd(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint fixture_size,
		void* item)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arradd, fixture_size, item)
	TEST_PRINT(str,	arradd, "array=(%u items), item=%p", fixture_size, item)
	TEST_FREE()
}
void	test_arradd(void)
{
//	| TEST FUNCTION   | TEST NAME            |TESTFLAG| EXPECTING                                 | TEST ARGS
	print_test_arradd("arradd             ",	FALSE,	"[Omae][ wa ][mou ][shindeiru.][YO]",       4, (void*)"YO");
	print_test_arradd("arradd (null array)",	FALSE,	"[YO]",                                     0, (void*)"YO");
	print_test_arradd("arradd (null item) ",	FALSE,	"[Omae][ wa ][mou ][shindeiru.][NULL]",     4, NULL);
}
#endif



#ifndef c_arrinsert
void test_arrinsert(void)	{}
#warning "arrinsert() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrinsert(t_uint fixture_size, void* item, t_uint index)
{
	s_array(any)*	array = NULL;
	s_array(any)*	result;
	char*	str;
	if (fixture_size == 4)
		array = gen_array_fixture();
	else if (fixture_size != (t_uint)-1) // -1 means "pass a NULL array pointer"
		array = c_arrnew(any)(fixture_size, (void*)"yo");
	result = c_arrinsert(any)(array, item, index);
	str = gen_array_consume(result);
	if (result != array && array != NULL)
		c_arrfree(any)(array);
	return (str);
}
void	print_test_arrinsert(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint fixture_size,
		void* item,
		t_uint index)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrinsert, fixture_size, item, index)
	TEST_PRINT(str,	arrinsert, "array=(%d items), item=%p, index=%u", (int)fixture_size, item, index)
	TEST_FREE()
}
void	test_arrinsert(void)
{
//	| TEST FUNCTION      | TEST NAME               |TESTFLAG| EXPECTING                                 | TEST ARGS
	print_test_arrinsert("arrinsert (start)     ",	FALSE,	"[YO][Omae][ wa ][mou ][shindeiru.]",       4, (void*)"YO", 0);
	print_test_arrinsert("arrinsert (middle)    ",	FALSE,	"[Omae][ wa ][YO][mou ][shindeiru.]",       4, (void*)"YO", 2);
	print_test_arrinsert("arrinsert (end)       ",	FALSE,	"[Omae][ wa ][mou ][shindeiru.][YO]",       4, (void*)"YO", 4);
	print_test_arrinsert("arrinsert (empty)     ",	FALSE,	"[YO]",                                     0, (void*)"YO", 0);
	print_test_arrinsert("arrinsert (null array)",	FALSE,	"[YO]",                                     (t_uint)-1, (void*)"YO", 0);
	print_test_arrinsert("arrinsert (beyond end)",	FALSE,	GEN_ARRAY_FIXTURE_STR,                      4, (void*)"YO", 9);
}
#endif



#ifndef c_arrwedge
void test_arrwedge(void)	{}
#warning "arrwedge() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrwedge(t_uint fixture_size, t_uint index)
{
	s_array(any)*	array = (fixture_size == 4 ? gen_array_fixture() : c_arrnew(any)(fixture_size, (void*)"yo"));
	s_array(any)*	src = c_arrcreate(any)(2, (void*)"S0", (void*)"S1");
	c_arrwedge(any)(array, src, index);
	c_arrfree(any)(src); // wedge copies the src content: src remains owned by the caller
	return (gen_array_consume(array));
}
void	print_test_arrwedge(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint fixture_size,
		t_uint index)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrwedge, fixture_size, index)
	TEST_PRINT(str,	arrwedge, "array=(%u items), src=[S0][S1], index=%u", fixture_size, index)
	TEST_FREE()
}
void	test_arrwedge(void)
{
//	| TEST FUNCTION     | TEST NAME              |TESTFLAG| EXPECTING                                     | TEST ARGS
	print_test_arrwedge("arrwedge (start)     ",	FALSE,	"[S0][S1][Omae][ wa ][mou ][shindeiru.]",       4, 0);
	print_test_arrwedge("arrwedge (middle)    ",	FALSE,	"[Omae][ wa ][S0][S1][mou ][shindeiru.]",       4, 2);
	print_test_arrwedge("arrwedge (end)       ",	FALSE,	"[Omae][ wa ][mou ][shindeiru.][S0][S1]",       4, 4);
	print_test_arrwedge("arrwedge (empty)     ",	FALSE,	"[S0][S1]",                                     0, 0);
	print_test_arrwedge("arrwedge (beyond end)",	FALSE,	GEN_ARRAY_FIXTURE_STR,                          4, 9);
}
#endif



#ifndef c_arrdelat
void test_arrdelat(void)	{}
#warning "arrdelat() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrdelat(t_uint index)
{
	s_array(any)*	array = gen_array_fixture();
	c_arrdelat(any)(array, index);
	return (gen_array_consume(array));
}
void	print_test_arrdelat(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint index)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrdelat, index)
	TEST_PRINT(str,	arrdelat, "index=%u", index)
	TEST_FREE()
}
void	test_arrdelat(void)
{
//	| TEST FUNCTION     | TEST NAME              |TESTFLAG| EXPECTING                       | TEST ARGS
	print_test_arrdelat("arrdelat (first)     ",	FALSE,	"[ wa ][mou ][shindeiru.]",       0);
	print_test_arrdelat("arrdelat (middle)    ",	FALSE,	"[Omae][mou ][shindeiru.]",       1);
	print_test_arrdelat("arrdelat (last)      ",	FALSE,	"[Omae][ wa ][mou ]",             3);
	print_test_arrdelat("arrdelat (beyond end)",	FALSE,	GEN_ARRAY_FIXTURE_STR,            4);
	print_test_arrdelat("arrdelat (huge index)",	FALSE,	GEN_ARRAY_FIXTURE_STR,            9999);
}
#endif



#ifndef c_arrdelone
void test_arrdelone(void)	{}
#warning "arrdelone() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrdelone(t_bool duplicates, void* item)
{
	s_array(any)*	array;
	if (duplicates)
		array = c_arrcreate(any)(4,
			(void*)g_arr_item[0], (void*)g_arr_item[1],
			(void*)g_arr_item[0], (void*)g_arr_item[1]);
	else
		array = gen_array_fixture();
	c_arrdelone(any)(array, item);
	return (gen_array_consume(array));
}
void	print_test_arrdelone(char const* test_name, t_testflags flags,
		char const* expecting,
		t_bool duplicates,
		void* item)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrdelone, duplicates, item)
	TEST_PRINT(str,	arrdelone, "array=(%s), item=%p", (duplicates ? "with duplicates" : "fixture"), item)
	TEST_FREE()
}
void	test_arrdelone(void)
{
//	| TEST FUNCTION      | TEST NAME                 |TESTFLAG| EXPECTING                       | TEST ARGS
	print_test_arrdelone("arrdelone (first)       ",	FALSE,	"[ wa ][mou ][shindeiru.]",       FALSE, (void*)g_arr_item[0]);
	print_test_arrdelone("arrdelone (middle)      ",	FALSE,	"[Omae][ wa ][shindeiru.]",       FALSE, (void*)g_arr_item[2]);
	print_test_arrdelone("arrdelone (last)        ",	FALSE,	"[Omae][ wa ][mou ]",             FALSE, (void*)g_arr_item[3]);
	print_test_arrdelone("arrdelone (only first)  ",	FALSE,	"[ wa ][Omae][ wa ]",             TRUE,  (void*)g_arr_item[0]);
	print_test_arrdelone("arrdelone (identity)    ",	FALSE,	GEN_ARRAY_FIXTURE_STR,            FALSE, (void*)g_arr_twin);
	print_test_arrdelone("arrdelone (not present) ",	FALSE,	GEN_ARRAY_FIXTURE_STR,            FALSE, (void*)"nope");
}
#endif



#ifndef c_arrdelall
void test_arrdelall(void)	{}
#warning "arrdelall() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrdelall(t_bool all_same, void* item)
{
	s_array(any)*	array;
	if (all_same)
		array = c_arrnew(any)(5, (void*)g_arr_item[0]);
	else
		array = c_arrcreate(any)(5,
			(void*)g_arr_item[0], (void*)g_arr_item[1],
			(void*)g_arr_item[0], (void*)g_arr_item[1],
			(void*)g_arr_item[0]);
	c_arrdelall(any)(array, item);
	return (gen_array_consume(array));
}
void	print_test_arrdelall(char const* test_name, t_testflags flags,
		char const* expecting,
		t_bool all_same,
		void* item)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrdelall, all_same, item)
	TEST_PRINT(str,	arrdelall, "array=(%s), item=%p", (all_same ? "5x same item" : "mixed"), item)
	TEST_FREE()
}
void	test_arrdelall(void)
{
//	| TEST FUNCTION      | TEST NAME                 |TESTFLAG| EXPECTING                             | TEST ARGS
	print_test_arrdelall("arrdelall               ",	FALSE,	"[ wa ][ wa ]",                         FALSE, (void*)g_arr_item[0]);
	print_test_arrdelall("arrdelall               ",	FALSE,	"[Omae][Omae][Omae]",                   FALSE, (void*)g_arr_item[1]);
	print_test_arrdelall("arrdelall (all items)   ",	FALSE,	"",                                     TRUE,  (void*)g_arr_item[0]);
	print_test_arrdelall("arrdelall (identity)    ",	FALSE,	"[Omae][ wa ][Omae][ wa ][Omae]",       FALSE, (void*)g_arr_twin);
	print_test_arrdelall("arrdelall (not present) ",	FALSE,	"[Omae][ wa ][Omae][ wa ][Omae]",       FALSE, (void*)"nope");
}
#endif



/*============================================================================*\
||                        Array: replacing/reordering                         ||
\*============================================================================*/

#ifndef c_arrrep
void test_arrrep(void)	{}
#warning "arrrep() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrrep(void* item_old, void* item_new)
{
	s_array(any)*	array = c_arrcreate(any)(4,
		(void*)g_arr_item[0], (void*)g_arr_item[1],
		(void*)g_arr_item[0], (void*)g_arr_item[2]);
	s_array(any)*	result = c_arrrep(any)(array, item_old, item_new);
	char*	str = gen_array_consume(result);
	c_arrfree(any)(array); // the operation is pure: the original array is untouched
	return (str);
}
void	print_test_arrrep(char const* test_name, t_testflags flags,
		char const* expecting,
		void* item_old,
		void* item_new)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrrep, item_old, item_new)
	TEST_PRINT(str,	arrrep, "array=[Omae][ wa ][Omae][mou ], old=%p, new=%p", item_old, item_new)
	TEST_FREE()
}
void	test_arrrep(void)
{
//	| TEST FUNCTION   | TEST NAME              |TESTFLAG| EXPECTING                       | TEST ARGS
	print_test_arrrep("arrrep (all matches) ",	FALSE,	"[YO][ wa ][YO][mou ]",           (void*)g_arr_item[0], (void*)"YO");
	print_test_arrrep("arrrep (one match)   ",	FALSE,	"[Omae][YO][Omae][mou ]",         (void*)g_arr_item[1], (void*)"YO");
	print_test_arrrep("arrrep (identity)    ",	FALSE,	"[Omae][ wa ][Omae][mou ]",       (void*)g_arr_twin,    (void*)"YO");
	print_test_arrrep("arrrep (not present) ",	FALSE,	"[Omae][ wa ][Omae][mou ]",       (void*)"nope",        (void*)"YO");
}
#endif



#ifndef c_arrrepfirst
void test_arrrepfirst(void)	{}
#warning "arrrepfirst() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrrepfirst(void* item_old, void* item_new, t_uint n)
{
	s_array(any)*	array = c_arrcreate(any)(4,
		(void*)g_arr_item[0], (void*)g_arr_item[1],
		(void*)g_arr_item[0], (void*)g_arr_item[0]);
	s_array(any)*	result = c_arrrepfirst(any)(array, item_old, item_new, n);
	char*	str = gen_array_consume(result);
	c_arrfree(any)(array);
	return (str);
}
void	print_test_arrrepfirst(char const* test_name, t_testflags flags,
		char const* expecting,
		void* item_old,
		void* item_new,
		t_uint n)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrrepfirst, item_old, item_new, n)
	TEST_PRINT(str,	arrrepfirst, "array=[Omae][ wa ][Omae][Omae], old=%p, new=%p, n=%u", item_old, item_new, n)
	TEST_FREE()
}
void	test_arrrepfirst(void)
{
//	| TEST FUNCTION        | TEST NAME               |TESTFLAG| EXPECTING                 | TEST ARGS
	print_test_arrrepfirst("arrrepfirst (n = 1)   ",	FALSE,	"[YO][ wa ][Omae][Omae]",   (void*)g_arr_item[0], (void*)"YO", 1);
	print_test_arrrepfirst("arrrepfirst (n = 2)   ",	FALSE,	"[YO][ wa ][YO][Omae]",     (void*)g_arr_item[0], (void*)"YO", 2);
	print_test_arrrepfirst("arrrepfirst (n > all) ",	FALSE,	"[YO][ wa ][YO][YO]",       (void*)g_arr_item[0], (void*)"YO", 9);
}
#endif



#ifndef c_arrreplast
void test_arrreplast(void)	{}
#warning "arrreplast() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrreplast(void* item_old, void* item_new, t_uint n)
{
	s_array(any)*	array = c_arrcreate(any)(4,
		(void*)g_arr_item[0], (void*)g_arr_item[1],
		(void*)g_arr_item[0], (void*)g_arr_item[0]);
	s_array(any)*	result = c_arrreplast(any)(array, item_old, item_new, n);
	char*	str = gen_array_consume(result);
	c_arrfree(any)(array);
	return (str);
}
void	print_test_arrreplast(char const* test_name, t_testflags flags,
		char const* expecting,
		void* item_old,
		void* item_new,
		t_uint n)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrreplast, item_old, item_new, n)
	TEST_PRINT(str,	arrreplast, "array=[Omae][ wa ][Omae][Omae], old=%p, new=%p, n=%u", item_old, item_new, n)
	TEST_FREE()
}
void	test_arrreplast(void)
{
//	| TEST FUNCTION       | TEST NAME               |TESTFLAG| EXPECTING                 | TEST ARGS
	print_test_arrreplast("arrreplast (n = 1)   ",	FALSE,	"[Omae][ wa ][Omae][YO]",   (void*)g_arr_item[0], (void*)"YO", 1);
	print_test_arrreplast("arrreplast (n = 2)   ",	FALSE,	"[Omae][ wa ][YO][YO]",     (void*)g_arr_item[0], (void*)"YO", 2);
	print_test_arrreplast("arrreplast (n > all) ",	FALSE,	"[YO][ wa ][YO][YO]",       (void*)g_arr_item[0], (void*)"YO", 9);
}
#endif



#ifndef c_arrrev
void test_arrrev(void)	{}
#warning "arrrev() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrrev(t_uint fixture_size)
{
	s_array(any)*	array = (fixture_size == 4 ? gen_array_fixture() : c_arrnew(any)(fixture_size, (void*)g_arr_item[0]));
	s_array(any)*	result = c_arrrev(any)(array);
	char*	str = gen_array_consume(result);
	c_arrfree(any)(array); // the operation is pure: the original array is untouched
	return (str);
}
void	print_test_arrrev(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint fixture_size)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrrev, fixture_size)
	TEST_PRINT(str,	arrrev, "array=(%u items)", fixture_size)
	TEST_FREE()
}
void	test_arrrev(void)
{
//	| TEST FUNCTION   | TEST NAME            |TESTFLAG| EXPECTING                            | TEST ARGS
	print_test_arrrev("arrrev             ",	FALSE,	"[shindeiru.][mou ][ wa ][Omae]",      4);
	print_test_arrrev("arrrev (1 item)    ",	FALSE,	"[Omae]",                              1);
	print_test_arrrev("arrrev (empty)     ",	FALSE,	"",                                    0);
}
#endif



/*============================================================================*\
||                         Array: combining two arrays                        ||
\*============================================================================*/

#ifndef c_arrconcat
void test_arrconcat(void)	{}
#warning "arrconcat() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrconcat(t_bool has_array1, t_bool has_array2)
{
	s_array(any)*	array1 = (has_array1 ? c_arrcreate(any)(2, (void*)"A0", (void*)"A1") : NULL);
	s_array(any)*	array2 = (has_array2 ? c_arrcreate(any)(2, (void*)"B0", (void*)"B1") : NULL);
	s_array(any)*	result = c_arrconcat(any)(array1, array2);
	char*	str = gen_array_consume(result);
	if (array1)	c_arrfree(any)(array1); // the operation is pure: both arrays are untouched
	if (array2)	c_arrfree(any)(array2);
	return (str);
}
void	print_test_arrconcat(char const* test_name, t_testflags flags,
		char const* expecting,
		t_bool has_array1,
		t_bool has_array2)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrconcat, has_array1, has_array2)
	TEST_PRINT(str,	arrconcat, "array1=%s, array2=%s", (has_array1 ? "[A0][A1]" : "NULL"), (has_array2 ? "[B0][B1]" : "NULL"))
	TEST_FREE()
}
void	test_arrconcat(void)
{
//	| TEST FUNCTION      | TEST NAME               |TESTFLAG| EXPECTING              | TEST ARGS
	print_test_arrconcat("arrconcat            ",	FALSE,	"[A0][A1][B0][B1]",      TRUE,  TRUE);
	print_test_arrconcat("arrconcat (null lhs) ",	FALSE,	"[B0][B1]",              FALSE, TRUE);
	print_test_arrconcat("arrconcat (null rhs) ",	FALSE,	"[A0][A1]",              TRUE,  FALSE);
	print_test_arrconcat("arrconcat (null both)",	FALSE,	"",                      FALSE, FALSE);
}
#endif



#ifndef c_arrappend
void test_arrappend(void)	{}
#warning "arrappend() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrappend(t_bool has_array1, t_bool has_array2)
{
	s_array(any)*	array1 = (has_array1 ? c_arrcreate(any)(2, (void*)"A0", (void*)"A1") : NULL);
	s_array(any)*	array2 = (has_array2 ? c_arrcreate(any)(2, (void*)"B0", (void*)"B1") : NULL);
	s_array(any)*	result = c_arrappend(any)(array1, array2);
	char*	str = gen_array_consume(result);
	if (array2)	c_arrfree(any)(array2); // NOTE: array1 is consumed by the operation, but array2 is not
	return (str);
}
void	print_test_arrappend(char const* test_name, t_testflags flags,
		char const* expecting,
		t_bool has_array1,
		t_bool has_array2)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrappend, has_array1, has_array2)
	TEST_PRINT(str,	arrappend, "array1=%s, array2=%s", (has_array1 ? "[A0][A1]" : "NULL"), (has_array2 ? "[B0][B1]" : "NULL"))
	TEST_FREE()
}
void	test_arrappend(void)
{
//	| TEST FUNCTION      | TEST NAME               |TESTFLAG| EXPECTING              | TEST ARGS
	print_test_arrappend("arrappend            ",	FALSE,	"[A0][A1][B0][B1]",      TRUE,  TRUE);
	print_test_arrappend("arrappend (null dest)",	FALSE,	"[B0][B1]",              FALSE, TRUE);
	print_test_arrappend("arrappend (null src) ",	FALSE,	"[A0][A1]",              TRUE,  FALSE);
	print_test_arrappend("arrappend (null both)",	FALSE,	"",                      FALSE, FALSE);
}
#endif



#ifndef c_arrprepend
void test_arrprepend(void)	{}
#warning "arrprepend() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrprepend(t_bool has_array1, t_bool has_array2)
{
	s_array(any)*	array1 = (has_array1 ? c_arrcreate(any)(2, (void*)"A0", (void*)"A1") : NULL);
	s_array(any)*	array2 = (has_array2 ? c_arrcreate(any)(2, (void*)"B0", (void*)"B1") : NULL);
	s_array(any)*	result = c_arrprepend(any)(array1, array2);
	char*	str = gen_array_consume(result);
	if (array1)	c_arrfree(any)(array1); // NOTE: array2 is consumed by the operation, but array1 is not
	return (str);
}
void	print_test_arrprepend(char const* test_name, t_testflags flags,
		char const* expecting,
		t_bool has_array1,
		t_bool has_array2)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrprepend, has_array1, has_array2)
	TEST_PRINT(str,	arrprepend, "array1=%s, array2=%s", (has_array1 ? "[A0][A1]" : "NULL"), (has_array2 ? "[B0][B1]" : "NULL"))
	TEST_FREE()
}
void	test_arrprepend(void)
{
//	| TEST FUNCTION       | TEST NAME                |TESTFLAG| EXPECTING              | TEST ARGS
	print_test_arrprepend("arrprepend           ",	FALSE,	"[A0][A1][B0][B1]",      TRUE,  TRUE);
	print_test_arrprepend("arrprepend (null lhs)",	FALSE,	"[B0][B1]",              FALSE, TRUE);
	print_test_arrprepend("arrprepend (null rhs)",	FALSE,	"[A0][A1]",              TRUE,  FALSE);
}
#endif



#ifndef c_arrmerge
void test_arrmerge(void)	{}
#warning "arrmerge() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrmerge(t_bool has_array1, t_bool has_array2)
{
	s_array(any)*	array1 = (has_array1 ? c_arrcreate(any)(2, (void*)"A0", (void*)"A1") : NULL);
	s_array(any)*	array2 = (has_array2 ? c_arrcreate(any)(2, (void*)"B0", (void*)"B1") : NULL);
	s_array(any)*	result = c_arrmerge(any)(array1, array2);
	return (gen_array_consume(result)); // NOTE: both given arrays are consumed by the operation
}
void	print_test_arrmerge(char const* test_name, t_testflags flags,
		char const* expecting,
		t_bool has_array1,
		t_bool has_array2)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrmerge, has_array1, has_array2)
	TEST_PRINT(str,	arrmerge, "array1=%s, array2=%s", (has_array1 ? "[A0][A1]" : "NULL"), (has_array2 ? "[B0][B1]" : "NULL"))
	TEST_FREE()
}
void	test_arrmerge(void)
{
//	| TEST FUNCTION     | TEST NAME              |TESTFLAG| EXPECTING              | TEST ARGS
	print_test_arrmerge("arrmerge            ",	FALSE,	"[A0][A1][B0][B1]",      TRUE,  TRUE);
	print_test_arrmerge("arrmerge (null lhs) ",	FALSE,	"[B0][B1]",              FALSE, TRUE);
	print_test_arrmerge("arrmerge (null rhs) ",	FALSE,	"[A0][A1]",              TRUE,  FALSE);
}
#endif



/*============================================================================*\
||                        Array: comparison operations                        ||
\*============================================================================*/

#ifndef c_arrequ
void test_arrequ(void)	{}
#warning "arrequ() test suite function defined, but the function isn't defined."
#else
void	print_test_arrequ(char const* test_name, t_testflags flags,
		t_bool expecting,
		s_array(any) const* array1,
		s_array(any) const* array2)
{
	TEST_INIT(bool)
	TEST_PERFORM(arrequ(any), array1, array2)
	TEST_PRINT(bool,	arrequ, "array1=%p, array2=%p", (void const*)array1, (void const*)array2)
}
void	test_arrequ(void)
{
	s_array(any)*	fixture = gen_array_fixture();
	s_array(any)*	same = gen_array_fixture();
	s_array(any)*	shorter = c_arrcreate(any)(2, (void*)g_arr_item[0], (void*)g_arr_item[1]);
	s_array(any)*	twin = c_arrcreate(any)(4, (void*)g_arr_twin, (void*)g_arr_item[1], (void*)g_arr_item[2], (void*)g_arr_item[3]);
//	| TEST FUNCTION   | TEST NAME               |TESTFLAG| EXPECTING | TEST ARGS
	print_test_arrequ("arrequ (same arrays)  ",	FALSE,	TRUE,       fixture, same);
	print_test_arrequ("arrequ (same pointer) ",	FALSE,	TRUE,       fixture, fixture);
	print_test_arrequ("arrequ (l2 shorter)   ",	FALSE,	FALSE,      fixture, shorter);
	print_test_arrequ("arrequ (l1 shorter)   ",	FALSE,	FALSE,      shorter, fixture);
	print_test_arrequ("arrequ (identity)     ",	FALSE,	FALSE,      fixture, twin);
	print_test_arrequ("arrequ (null lhs)     ",	FALSE,	FALSE,      NULL,    fixture);
	print_test_arrequ("arrequ (null rhs)     ",	FALSE,	FALSE,      fixture, NULL);
	print_test_arrequ("arrequ (null both)    ",	FALSE,	TRUE,       NULL,    NULL);
	c_arrfree(any)(fixture);
	c_arrfree(any)(same);
	c_arrfree(any)(shorter);
	c_arrfree(any)(twin);
}
#endif



#ifndef c_arrnequ
void test_arrnequ(void)	{}
#warning "arrnequ() test suite function defined, but the function isn't defined."
#else
void	print_test_arrnequ(char const* test_name, t_testflags flags,
		t_bool expecting,
		s_array(any) const* array1,
		s_array(any) const* array2,
		t_uint n)
{
	TEST_INIT(bool)
	TEST_PERFORM(arrnequ(any), array1, array2, n)
	TEST_PRINT(bool,	arrnequ, "array1=%p, array2=%p, n=%u", (void const*)array1, (void const*)array2, n)
}
void	test_arrnequ(void)
{
	s_array(any)*	fixture = gen_array_fixture();
	s_array(any)*	differ = c_arrcreate(any)(4, (void*)g_arr_item[0], (void*)g_arr_item[1], (void*)"YO", (void*)"YO");
//	| TEST FUNCTION    | TEST NAME                |TESTFLAG| EXPECTING | TEST ARGS
	print_test_arrnequ("arrnequ (n = 1)        ",	FALSE,	TRUE,       fixture, differ, 1);
	print_test_arrnequ("arrnequ (n = 2)        ",	FALSE,	TRUE,       fixture, differ, 2);
	print_test_arrnequ("arrnequ (n = 3)        ",	FALSE,	FALSE,      fixture, differ, 3);
	print_test_arrnequ("arrnequ (n = 4)        ",	FALSE,	FALSE,      fixture, differ, 4);
	print_test_arrnequ("arrnequ (n > length)   ",	FALSE,	FALSE,      fixture, differ, 9);
	print_test_arrnequ("arrnequ (n = 0)        ",	FALSE,	TRUE,       fixture, differ, 0);
	c_arrfree(any)(fixture);
	c_arrfree(any)(differ);
}
#endif



static t_sint	gen_compare_str(void* item1, void* item2)
{
	int	result = strcmp(
		(item1 ? (char const*)item1 : ""),
		(item2 ? (char const*)item2 : ""));
	return (result < 0 ? -1 : (result > 0 ? +1 : 0));
}

#ifndef c_arrcmp
void test_arrcmp(void)	{}
#warning "arrcmp() test suite function defined, but the function isn't defined."
#else
void	print_test_arrcmp(char const* test_name, t_testflags flags,
		t_sint expecting,
		s_array(any) const* array1,
		s_array(any) const* array2)
{
	TEST_INIT(sint)
	TEST_PERFORM(arrcmp(any), array1, array2, gen_compare_str)
	TEST_PRINT(sint,	arrcmp, "array1=%p, array2=%p, compare=strcmp", (void const*)array1, (void const*)array2)
}
void	test_arrcmp(void)
{
	s_array(any)*	fixture = gen_array_fixture();
	s_array(any)*	twin = c_arrcreate(any)(4, (void*)g_arr_twin, (void*)g_arr_item[1], (void*)g_arr_item[2], (void*)g_arr_item[3]);
	s_array(any)*	bigger = c_arrcreate(any)(2, (void*)"zzz", (void*)g_arr_item[1]);
	s_array(any)*	smaller = c_arrcreate(any)(2, (void*)"AAA", (void*)g_arr_item[1]);
//	| TEST FUNCTION   | TEST NAME                |TESTFLAG| EXPECTING | TEST ARGS
	print_test_arrcmp("arrcmp (equal)         ",	FALSE,	0,          fixture, twin);
	print_test_arrcmp("arrcmp (same pointer)  ",	FALSE,	0,          fixture, fixture);
	print_test_arrcmp("arrcmp (l1 < l2)       ",	FALSE,	-1,         fixture, bigger); // "Omae" < "zzz"
	print_test_arrcmp("arrcmp (l1 > l2)       ",	FALSE,	+1,         fixture, smaller); // "Omae" > "AAA"
	c_arrfree(any)(fixture);
	c_arrfree(any)(twin);
	c_arrfree(any)(bigger);
	c_arrfree(any)(smaller);
}
#endif



#ifndef c_arrncmp
void test_arrncmp(void)	{}
#warning "arrncmp() test suite function defined, but the function isn't defined."
#else
void	print_test_arrncmp(char const* test_name, t_testflags flags,
		t_sint expecting,
		s_array(any) const* array1,
		s_array(any) const* array2,
		t_uint n)
{
	TEST_INIT(sint)
	TEST_PERFORM(arrncmp(any), array1, array2, gen_compare_str, n)
	TEST_PRINT(sint,	arrncmp, "array1=%p, array2=%p, compare=strcmp, n=%u", (void const*)array1, (void const*)array2, n)
}
void	test_arrncmp(void)
{
	s_array(any)*	fixture = gen_array_fixture();
	s_array(any)*	bigger = c_arrcreate(any)(2, (void*)g_arr_item[0], (void*)"zzz");
//	| TEST FUNCTION    | TEST NAME              |TESTFLAG| EXPECTING | TEST ARGS
	print_test_arrncmp("arrncmp (n = 1)      ",	FALSE,	0,          fixture, bigger, 1);
	print_test_arrncmp("arrncmp (n = 2)      ",	FALSE,	-1,         fixture, bigger, 2);
	print_test_arrncmp("arrncmp (n = 0)      ",	FALSE,	0,          fixture, bigger, 0);
	c_arrfree(any)(fixture);
	c_arrfree(any)(bigger);
}
#endif



/*============================================================================*\
||                         Array: searching operations                        ||
\*============================================================================*/

static t_bool	gen_match_starts_with_m(void* item)
{
	return (item != NULL && ((char const*)item)[0] == 'm');
}
static t_bool	gen_match_never(void* item)
{
	(void)item;
	return (FALSE);
}

#ifndef c_arrfind
void test_arrfind(void)	{}
#warning "arrfind() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrfind(s_array(any) const* array, void* item)
{
	void**	result = c_arrfind(any)(array, item);
	if (result == NULL)
		return (strdup("(null)"));
	return (strdup(*result ? (char const*)*result : "NULL"));
}
void	print_test_arrfind(char const* test_name, t_testflags flags,
		char const* expecting,
		s_array(any) const* array,
		void* item)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrfind, array, item)
	TEST_PRINT(str,	arrfind, "array=%p, item=%p", (void const*)array, item)
	TEST_FREE()
}
void	test_arrfind(void)
{
	s_array(any)*	fixture = gen_array_fixture();
//	| TEST FUNCTION    | TEST NAME               |TESTFLAG| EXPECTING     | TEST ARGS
	print_test_arrfind("arrfind (first)       ",	FALSE,	"Omae",         fixture, (void*)g_arr_item[0]);
	print_test_arrfind("arrfind (middle)      ",	FALSE,	"mou ",         fixture, (void*)g_arr_item[2]);
	print_test_arrfind("arrfind (last)        ",	FALSE,	"shindeiru.",   fixture, (void*)g_arr_item[3]);
	print_test_arrfind("arrfind (identity)    ",	FALSE,	"(null)",       fixture, (void*)g_arr_twin);
	print_test_arrfind("arrfind (not present) ",	FALSE,	"(null)",       fixture, (void*)"nope");
	c_arrfree(any)(fixture);
}
#endif



#ifndef c_arrffind
void test_arrffind(void)	{}
#warning "arrffind() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrffind(s_array(any) const* array, t_bool (*match)(void* item))
{
	void**	result = c_arrffind(any)(array, match);
	if (result == NULL)
		return (strdup("(null)"));
	return (strdup(*result ? (char const*)*result : "NULL"));
}
void	print_test_arrffind(char const* test_name, t_testflags flags,
		char const* expecting,
		s_array(any) const* array,
		t_bool (*match)(void* item))
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrffind, array, match)
	TEST_PRINT(str,	arrffind, "array=%p, match=%p", (void const*)array, (void*)match)
	TEST_FREE()
}
void	test_arrffind(void)
{
	s_array(any)*	fixture = gen_array_fixture();
//	| TEST FUNCTION     | TEST NAME             |TESTFLAG| EXPECTING  | TEST ARGS
	print_test_arrffind("arrffind            ",	FALSE,	"mou ",      fixture, gen_match_starts_with_m);
	print_test_arrffind("arrffind (no match) ",	FALSE,	"(null)",    fixture, gen_match_never);
	c_arrfree(any)(fixture);
}
#endif



#ifndef c_arrfindi
void test_arrfindi(void)	{}
#warning "arrfindi() test suite function defined, but the function isn't defined."
#else
void	print_test_arrfindi(char const* test_name, t_testflags flags,
		t_sint expecting,
		s_array(any) const* array,
		void* item)
{
	TEST_INIT(sint)
	TEST_PERFORM(arrfindi(any), array, item)
	TEST_PRINT(sint,	arrfindi, "array=%p, item=%p", (void const*)array, item)
}
void	test_arrfindi(void)
{
	s_array(any)*	fixture = gen_array_fixture();
//	| TEST FUNCTION     | TEST NAME               |TESTFLAG| EXPECTING | TEST ARGS
	print_test_arrfindi("arrfindi (first)      ",	FALSE,	0,          fixture, (void*)g_arr_item[0]);
	print_test_arrfindi("arrfindi (middle)     ",	FALSE,	2,          fixture, (void*)g_arr_item[2]);
	print_test_arrfindi("arrfindi (last)       ",	FALSE,	3,          fixture, (void*)g_arr_item[3]);
	print_test_arrfindi("arrfindi (identity)   ",	FALSE,	ERROR,      fixture, (void*)g_arr_twin);
	print_test_arrfindi("arrfindi (not present)",	FALSE,	ERROR,      fixture, (void*)"nope");
	c_arrfree(any)(fixture);
}
#endif



#ifndef c_arrffindi
void test_arrffindi(void)	{}
#warning "arrffindi() test suite function defined, but the function isn't defined."
#else
void	print_test_arrffindi(char const* test_name, t_testflags flags,
		t_sint expecting,
		s_array(any) const* array,
		t_bool (*match)(void* item))
{
	TEST_INIT(sint)
	TEST_PERFORM(arrffindi(any), array, match)
	TEST_PRINT(sint,	arrffindi, "array=%p, match=%p", (void const*)array, (void*)match)
}
void	test_arrffindi(void)
{
	s_array(any)*	fixture = gen_array_fixture();
//	| TEST FUNCTION      | TEST NAME              |TESTFLAG| EXPECTING | TEST ARGS
	print_test_arrffindi("arrffindi            ",	FALSE,	2,          fixture, gen_match_starts_with_m);
	print_test_arrffindi("arrffindi (no match) ",	FALSE,	ERROR,      fixture, gen_match_never);
	c_arrfree(any)(fixture);
}
#endif



#ifndef c_arrcount
void test_arrcount(void)	{}
#warning "arrcount() test suite function defined, but the function isn't defined."
#else
void	print_test_arrcount(char const* test_name, t_testflags flags,
		t_uint expecting,
		s_array(any) const* array,
		void* item)
{
	TEST_INIT(uint)
	TEST_PERFORM(arrcount(any), array, item)
	TEST_PRINT(uint,	arrcount, "array=%p, item=%p", (void const*)array, item)
}
void	test_arrcount(void)
{
	s_array(any)*	array = c_arrcreate(any)(5,
		(void*)g_arr_item[0], (void*)g_arr_item[1],
		(void*)g_arr_item[0], (void*)g_arr_item[1],
		(void*)g_arr_item[0]);
//	| TEST FUNCTION     | TEST NAME                |TESTFLAG| EXPECTING | TEST ARGS
	print_test_arrcount("arrcount              ",	FALSE,	3,          array, (void*)g_arr_item[0]);
	print_test_arrcount("arrcount              ",	FALSE,	2,          array, (void*)g_arr_item[1]);
	print_test_arrcount("arrcount (identity)   ",	FALSE,	0,          array, (void*)g_arr_twin);
	print_test_arrcount("arrcount (not present)",	FALSE,	0,          array, (void*)"nope");
	print_test_arrcount("arrcount (null array) ",	FALSE,	0,          NULL,  (void*)g_arr_item[0]);
	c_arrfree(any)(array);
}
#endif



#ifndef c_arrcontains
void test_arrcontains(void)	{}
#warning "arrcontains() test suite function defined, but the function isn't defined."
#else
void	print_test_arrcontains(char const* test_name, t_testflags flags,
		t_bool expecting,
		s_array(any) const* array,
		void* item)
{
	TEST_INIT(bool)
	TEST_PERFORM(arrcontains(any), array, item)
	TEST_PRINT(bool,	arrcontains, "array=%p, item=%p", (void const*)array, item)
}
void	test_arrcontains(void)
{
	s_array(any)*	fixture = gen_array_fixture();
//	| TEST FUNCTION        | TEST NAME                   |TESTFLAG| EXPECTING | TEST ARGS
	print_test_arrcontains("arrcontains (first)       ",	FALSE,	TRUE,       fixture, (void*)g_arr_item[0]);
	print_test_arrcontains("arrcontains (last)        ",	FALSE,	TRUE,       fixture, (void*)g_arr_item[3]);
	print_test_arrcontains("arrcontains (identity)    ",	FALSE,	FALSE,      fixture, (void*)g_arr_twin);
	print_test_arrcontains("arrcontains (not present) ",	FALSE,	FALSE,      fixture, (void*)"nope");
	print_test_arrcontains("arrcontains (null array)  ",	FALSE,	FALSE,      NULL,    (void*)g_arr_item[0]);
	c_arrfree(any)(fixture);
}
#endif



#ifndef c_arrhas
void test_arrhas(void)	{}
#warning "arrhas() test suite function defined, but the function isn't defined."
#else
void	print_test_arrhas(char const* test_name, t_testflags flags,
		t_bool expecting,
		s_array(any) const* array,
		s_array(any) const* target)
{
	TEST_INIT(bool)
	TEST_PERFORM(arrhas(any), array, target)
	TEST_PRINT(bool,	arrhas, "array=%p, target=%p", (void const*)array, (void const*)target)
}
void	test_arrhas(void)
{
	s_array(any)*	fixture = gen_array_fixture();
	s_array(any)*	one_of = c_arrcreate(any)(2, (void*)"nope", (void*)g_arr_item[2]);
	s_array(any)*	none_of = c_arrcreate(any)(2, (void*)"nope", (void*)g_arr_twin);
//	| TEST FUNCTION   | TEST NAME               |TESTFLAG| EXPECTING | TEST ARGS
	print_test_arrhas("arrhas (one match)    ",	FALSE,	TRUE,       fixture, one_of);
	print_test_arrhas("arrhas (no matches)   ",	FALSE,	FALSE,      fixture, none_of);
	print_test_arrhas("arrhas (with itself)  ",	FALSE,	TRUE,       fixture, fixture);
	c_arrfree(any)(fixture);
	c_arrfree(any)(one_of);
	c_arrfree(any)(none_of);
}
#endif



#ifndef c_arrhasonly
void test_arrhasonly(void)	{}
#warning "arrhasonly() test suite function defined, but the function isn't defined."
#else
void	print_test_arrhasonly(char const* test_name, t_testflags flags,
		t_bool expecting,
		s_array(any) const* array,
		s_array(any) const* target)
{
	TEST_INIT(bool)
	TEST_PERFORM(arrhasonly(any), array, target)
	TEST_PRINT(bool,	arrhasonly, "array=%p, target=%p", (void const*)array, (void const*)target)
}
void	test_arrhasonly(void)
{
	s_array(any)*	fixture = gen_array_fixture();
	s_array(any)*	subset = c_arrcreate(any)(2, (void*)g_arr_item[0], (void*)g_arr_item[1]);
//	| TEST FUNCTION       | TEST NAME                  |TESTFLAG| EXPECTING | TEST ARGS
	print_test_arrhasonly("arrhasonly (with itself) ",	FALSE,	TRUE,       fixture, fixture);
	print_test_arrhasonly("arrhasonly (subset ok)   ",	FALSE,	TRUE,       subset,  fixture);
	print_test_arrhasonly("arrhasonly (extra items) ",	FALSE,	FALSE,      fixture, subset);
	c_arrfree(any)(fixture);
	c_arrfree(any)(subset);
}
#endif



/*============================================================================*\
||                       Array: functional programming                        ||
\*============================================================================*/

//! Accumulates all visited items (and their given index, if any) for the Iterate tests
static char	g_arr_iter_buffer[256];
static void	gen_iterate_visit(void* item)
{
	strcat(g_arr_iter_buffer, "[");
	strcat(g_arr_iter_buffer, (item ? (char const*)item : "NULL"));
	strcat(g_arr_iter_buffer, "]");
}
static void	gen_iterate_visit_i(void* item, t_uint index)
{
	size_t	length = strlen(g_arr_iter_buffer);
	snprintf(g_arr_iter_buffer + length, sizeof(g_arr_iter_buffer) - length,
		"[%u:%s]", index, (item ? (char const*)item : "NULL"));
}

#ifndef c_arriter
void test_arriter(void)	{}
#warning "arriter() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arriter(t_uint fixture_size)
{
	s_array(any)*	array = (fixture_size == 0 ? NULL : gen_array_fixture());
	g_arr_iter_buffer[0] = '\0';
	c_arriter(any)(array, gen_iterate_visit);
	if (array)
		c_arrfree(any)(array);
	return (strdup(g_arr_iter_buffer));
}
void	print_test_arriter(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint fixture_size)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arriter, fixture_size)
	TEST_PRINT(str,	arriter, "array=(%u items), f=(accumulator)", fixture_size)
	TEST_FREE()
}
void	test_arriter(void)
{
//	| TEST FUNCTION   | TEST NAME             |TESTFLAG| EXPECTING             | TEST ARGS
	print_test_arriter("arriter             ",	FALSE,	GEN_ARRAY_FIXTURE_STR,  4);
	print_test_arriter("arriter (null array)",	FALSE,	"",                     0);
}
#endif



#ifndef c_arriiter
void test_arriiter(void)	{}
#warning "arriiter() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arriiter(t_uint fixture_size)
{
	s_array(any)*	array = (fixture_size == 0 ? NULL : gen_array_fixture());
	g_arr_iter_buffer[0] = '\0';
	c_arriiter(any)(array, gen_iterate_visit_i);
	if (array)
		c_arrfree(any)(array);
	return (strdup(g_arr_iter_buffer));
}
void	print_test_arriiter(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint fixture_size)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arriiter, fixture_size)
	TEST_PRINT(str,	arriiter, "array=(%u items), f=(accumulator)", fixture_size)
	TEST_FREE()
}
void	test_arriiter(void)
{
//	| TEST FUNCTION    | TEST NAME              |TESTFLAG| EXPECTING                                    | TEST ARGS
	print_test_arriiter("arriiter             ",	FALSE,	"[0:Omae][1: wa ][2:mou ][3:shindeiru.]",      4);
	print_test_arriiter("arriiter (null array)",	FALSE,	"",                                            0);
}
#endif



//! The "uppercase versions" of the `g_arr_item` strings, for the Map tests
static char* const	g_arr_item_upper[4] =
{
	"OMAE",
	" WA ",
	"MOU ",
	"SHINDEIRU.",
};
//! Maps any standard test item to its uppercase version (leaves other items untouched)
static void*	gen_map_upper(void* item)
{
	for (t_uint i = 0; i < 4; ++i)
	{
		if (item == (void*)g_arr_item[i])
			return ((void*)g_arr_item_upper[i]);
	}
	return (item);
}
//! Maps every item to the standard test item at the given index, reversed
static void*	gen_map_reverse_i(void* item, t_uint index)
{
	(void)item;
	return (index < 4 ? (void*)g_arr_item[3 - index] : NULL);
}

#ifndef c_arrmap
void test_arrmap(void)	{}
#warning "arrmap() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrmap(t_uint fixture_size)
{
	s_array(any)*	array = (fixture_size == 0 ? c_arrnew(any)(0, NULL) : gen_array_fixture());
	s_array(any)*	result = c_arrmap(any)(array, gen_map_upper);
	char*	str = gen_array_consume(result);
	c_arrfree(any)(array); // the operation is pure: the original array is untouched
	return (str);
}
void	print_test_arrmap(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint fixture_size)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrmap, fixture_size)
	TEST_PRINT(str,	arrmap, "array=(%u items), map=(to uppercase)", fixture_size)
	TEST_FREE()
}
void	test_arrmap(void)
{
//	| TEST FUNCTION   | TEST NAME           |TESTFLAG| EXPECTING                            | TEST ARGS
	print_test_arrmap("arrmap             ",	FALSE,	"[OMAE][ WA ][MOU ][SHINDEIRU.]",      4);
	print_test_arrmap("arrmap (empty)     ",	FALSE,	"",                                    0);
}
#endif



#ifndef c_arrimap
void test_arrimap(void)	{}
#warning "arrimap() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrimap(t_uint fixture_size)
{
	s_array(any)*	array = (fixture_size == 0 ? c_arrnew(any)(0, NULL) : gen_array_fixture());
	s_array(any)*	result = c_arrimap(any)(array, gen_map_reverse_i);
	char*	str = gen_array_consume(result);
	c_arrfree(any)(array);
	return (str);
}
void	print_test_arrimap(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint fixture_size)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrimap, fixture_size)
	TEST_PRINT(str,	arrimap, "array=(%u items), map=(reverse by index)", fixture_size)
	TEST_FREE()
}
void	test_arrimap(void)
{
//	| TEST FUNCTION    | TEST NAME           |TESTFLAG| EXPECTING                            | TEST ARGS
	print_test_arrimap("arrimap            ",	FALSE,	"[shindeiru.][mou ][ wa ][Omae]",      4);
	print_test_arrimap("arrimap (empty)    ",	FALSE,	"",                                    0);
}
#endif



//! Keeps only the items which are longer than 4 characters
static t_bool	gen_filter_long(void* item)
{
	return (item != NULL && strlen((char const*)item) > 4);
}
//! Keeps only the items at even indices
static t_bool	gen_filter_even_i(void* item, t_uint index)
{
	(void)item;
	return (index % 2 == 0);
}

#ifndef c_arrfilter
void test_arrfilter(void)	{}
#warning "arrfilter() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrfilter(t_uint fixture_size, t_bool (*filter)(void* item))
{
	s_array(any)*	array = (fixture_size == 0 ? c_arrnew(any)(0, NULL) : gen_array_fixture());
	s_array(any)*	result = c_arrfilter(any)(array, filter);
	char*	str = gen_array_consume(result);
	c_arrfree(any)(array); // the operation is pure: the original array is untouched
	return (str);
}
void	print_test_arrfilter(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint fixture_size,
		t_bool (*filter)(void* item))
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrfilter, fixture_size, filter)
	TEST_PRINT(str,	arrfilter, "array=(%u items), filter=%p", fixture_size, (void*)filter)
	TEST_FREE()
}
void	test_arrfilter(void)
{
//	| TEST FUNCTION      | TEST NAME              |TESTFLAG| EXPECTING       | TEST ARGS
	print_test_arrfilter("arrfilter            ",	FALSE,	"[shindeiru.]",   4, gen_filter_long);
	print_test_arrfilter("arrfilter (no match) ",	FALSE,	"",               4, gen_match_never);
	print_test_arrfilter("arrfilter (empty)    ",	FALSE,	"",               0, gen_filter_long);
}
#endif



#ifndef c_arrifilter
void test_arrifilter(void)	{}
#warning "arrifilter() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_arrifilter(t_uint fixture_size)
{
	s_array(any)*	array = (fixture_size == 0 ? c_arrnew(any)(0, NULL) : gen_array_fixture());
	s_array(any)*	result = c_arrifilter(any)(array, gen_filter_even_i);
	char*	str = gen_array_consume(result);
	c_arrfree(any)(array);
	return (str);
}
void	print_test_arrifilter(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint fixture_size)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_arrifilter, fixture_size)
	TEST_PRINT(str,	arrifilter, "array=(%u items), filter=(even indices)", fixture_size)
	TEST_FREE()
}
void	test_arrifilter(void)
{
//	| TEST FUNCTION       | TEST NAME              |TESTFLAG| EXPECTING       | TEST ARGS
	print_test_arrifilter("arrifilter            ",	FALSE,	"[Omae][mou ]",   4);
	print_test_arrifilter("arrifilter (empty)    ",	FALSE,	"",               0);
}
#endif



//! Accumulates the total length of all the item strings (into the `void*` accumulator)
static void*	gen_reduce_lengths(void* item, void* acc)
{
	return ((void*)((t_uintptr)acc + (item ? strlen((char const*)item) : 0)));
}
static void*	gen_reduce_lengths_i(void* item, void* acc, t_uint index)
{
	return ((void*)((t_uintptr)acc + index * (item ? strlen((char const*)item) : 0)));
}

#ifndef c_arrreduce
void test_arrreduce(void)	{}
#warning "arrreduce() test suite function defined, but the function isn't defined."
#else
static t_uint	c_gen_arrreduce(void)
{
	s_array(any)*	array = gen_array_fixture();
	void*	result = c_arrreduce(any)(array, gen_reduce_lengths);
	c_arrfree(any)(array);
	return ((t_uint)(t_uintptr)result);
}
void	print_test_arrreduce(char const* test_name, t_testflags flags,
		t_uint expecting)
{
	TEST_INIT(uint)
	TEST_PERFORM(gen_arrreduce)
	TEST_PRINT(uint,	arrreduce, "array=(4-item fixture), f=(sum item lengths)")
}
void	test_arrreduce(void)
{
//	| TEST FUNCTION      | TEST NAME           |TESTFLAG| EXPECTING (4 + 4 + 4 + 10)
	print_test_arrreduce("arrreduce          ",	FALSE,	22);
}
#endif



#ifndef c_arrireduce
void test_arrireduce(void)	{}
#warning "arrireduce() test suite function defined, but the function isn't defined."
#else
static t_uint	c_gen_arrireduce(void)
{
	s_array(any)*	array = gen_array_fixture();
	void*	result = c_arrireduce(any)(array, gen_reduce_lengths_i);
	c_arrfree(any)(array);
	return ((t_uint)(t_uintptr)result);
}
void	print_test_arrireduce(char const* test_name, t_testflags flags,
		t_uint expecting)
{
	TEST_INIT(uint)
	TEST_PERFORM(gen_arrireduce)
	TEST_PRINT(uint,	arrireduce, "array=(4-item fixture), f=(sum index-weighted lengths)")
}
void	test_arrireduce(void)
{
//	| TEST FUNCTION       | TEST NAME           |TESTFLAG| EXPECTING (0*4 + 1*4 + 2*4 + 3*10)
	print_test_arrireduce("arrireduce         ",	FALSE,	42);
}
#endif



#ifndef c_arrfold
void test_arrfold(void)	{}
#warning "arrfold() test suite function defined, but the function isn't defined."
#else
static t_uint	c_gen_arrfold(t_uint initial)
{
	s_array(any)*	array = gen_array_fixture();
	void*	result = c_arrfold(any)(array, gen_reduce_lengths, (void*)(t_uintptr)initial);
	c_arrfree(any)(array);
	return ((t_uint)(t_uintptr)result);
}
void	print_test_arrfold(char const* test_name, t_testflags flags,
		t_uint expecting,
		t_uint initial)
{
	TEST_INIT(uint)
	TEST_PERFORM(gen_arrfold, initial)
	TEST_PRINT(uint,	arrfold, "array=(4-item fixture), f=(sum item lengths), initial=%u", initial)
}
void	test_arrfold(void)
{
//	| TEST FUNCTION    | TEST NAME             |TESTFLAG| EXPECTING | TEST ARGS
	print_test_arrfold("arrfold             ",	FALSE,	122,        100);
	print_test_arrfold("arrfold (initial 0) ",	FALSE,	22,         0);
}
#endif



#ifndef c_arrifold
void test_arrifold(void)	{}
#warning "arrifold() test suite function defined, but the function isn't defined."
#else
static t_uint	c_gen_arrifold(t_uint initial)
{
	s_array(any)*	array = gen_array_fixture();
	void*	result = c_arrifold(any)(array, gen_reduce_lengths_i, (void*)(t_uintptr)initial);
	c_arrfree(any)(array);
	return ((t_uint)(t_uintptr)result);
}
void	print_test_arrifold(char const* test_name, t_testflags flags,
		t_uint expecting,
		t_uint initial)
{
	TEST_INIT(uint)
	TEST_PERFORM(gen_arrifold, initial)
	TEST_PRINT(uint,	arrifold, "array=(4-item fixture), f=(sum index-weighted lengths), initial=%u", initial)
}
void	test_arrifold(void)
{
//	| TEST FUNCTION     | TEST NAME             |TESTFLAG| EXPECTING | TEST ARGS
	print_test_arrifold("arrifold            ",	FALSE,	142,        100);
}
#endif



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_generic_array(void)
{
	print_suite_title("libccc/generic/array");

	print_nonstd();

	test_arritem();
	test_arrget();
	test_arrset();
	test_arrnew();
	test_arrcreate();
	test_arrdup();
	test_arrsub();
	test_arrcpy();
	test_arrdel();
	test_arrfdel();
	test_arradd();
	test_arrinsert();
	test_arrwedge();
	test_arrdelat();
	test_arrdelone();
	test_arrdelall();
	test_arrrep();
	test_arrrepfirst();
	test_arrreplast();
	test_arrrev();
	test_arrconcat();
	test_arrappend();
	test_arrprepend();
	test_arrmerge();
	test_arrequ();
	test_arrnequ();
	test_arrcmp();
	test_arrncmp();
	test_arrfind();
	test_arrffind();
	test_arrfindi();
	test_arrffindi();
	test_arrcount();
	test_arrcontains();
	test_arrhas();
	test_arrhasonly();
	test_arriter();
	test_arriiter();
	test_arrmap();
	test_arrimap();
	test_arrfilter();
	test_arrifilter();
	test_arrreduce();
	test_arrireduce();
	test_arrfold();
	test_arrifold();

	return (OK);
}
