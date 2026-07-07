
#include "libccc/generic/array.c"
#include "libccc/generic/list.c"

#include "test.h"
#include "test_utils.h"



/*============================================================================*\
||                             Testing Utilities                              ||
\*============================================================================*/

/*
**	NOTE: this test suite exercises the default instantiation of the generic
**	list type (ie: `T` is `void*`, and `T_NAME` is `any`), which is included
**	just above. With this instantiation, the `T_EQUALS()` macro is a simple
**	pointer comparison: so, all of the "equality"-based list functions (like
**	Remove, Find, Count, Contains, Equals, etc) match items by their pointer
**	*identity*, not by their pointed-to contents - the tests below check this
**	semantic explicitly (see the `g_lst_twin` test cases).
**
**	The items used are `char*` strings, so that expected results can be
**	written legibly: every list-returning function is tested by serializing
**	the result list into a string of the form `"[item1][item2][item3]"`
**	(an empty/NULL list serializes to `""`), and comparing with `print_test_str`.
*/

//! The items used to build the test lists (matching items must be the same pointer)
static char* const	g_lst_item[4] =
{
	"Omae",
	" wa ",
	"mou ",
	"shindeiru.",
};
//! Has the same content as `g_lst_item[0]`, but is a different pointer
static char	g_lst_twin[] = "Omae";

//! Serializes the given list of `char*` items into a newly allocated string: `"[item1][item2]"`
static
char*	gen_list_tostr(s_list(any) const* list)
{
	s_list(any) const*	elem;
	size_t	length = 0;
	char*	result;
	char const*	str;

	for (elem = list; elem; elem = elem->next)
	{
		length += 2 + (elem->item ? strlen((char const*)elem->item) : strlen("NULL"));
	}
	result = (char*)malloc(length + 1);
	if (result == NULL)
		return (NULL);
	length = 0;
	for (elem = list; elem; elem = elem->next)
	{
		str = (elem->item ? (char const*)elem->item : "NULL");
		result[length++] = '[';
		strcpy(result + length, str);
		length += strlen(str);
		result[length++] = ']';
	}
	result[length] = '\0';
	return (result);
}

//! Serializes the given list (like gen_list_tostr()), and then deletes it
static
char*	gen_list_consume(s_list(any)* list)
{
	char*	result = gen_list_tostr(list);
	if (list)
		c_lstfree(any)(list);
	return (result);
}

//! Builds the standard 4-item test list: `[Omae][ wa ][mou ][shindeiru.]`
static
s_list(any)*	gen_list_fixture(void)
{
	return (c_lstcreate(any)(4,
		(void*)g_lst_item[0],
		(void*)g_lst_item[1],
		(void*)g_lst_item[2],
		(void*)g_lst_item[3]));
}

//! The expected serialization of the standard test list fixture
#define GEN_LIST_FIXTURE_STR	"[Omae][ wa ][mou ][shindeiru.]"



/*============================================================================*\
||                            List: basic operations                          ||
\*============================================================================*/

#ifndef c_lstitem
void test_lstitem(void)	{}
#warning "lstitem() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstitem(void* item)
{
	return (gen_list_consume(c_lstitem(any)(item)));
}
void	print_test_lstitem(char const* test_name, t_testflags flags,
		char const* expecting,
		void* item)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstitem, item)
	TEST_PRINT(str,	lstitem, "item=%p", item)
	TEST_FREE()
}
void	test_lstitem(void)
{
//	| TEST FUNCTION    | TEST NAME           |TESTFLAG| EXPECTING      | TEST ARGS
	print_test_lstitem("lstitem            ",	FALSE,	"[Omae]",        (void*)g_lst_item[0]);
	print_test_lstitem("lstitem            ",	FALSE,	"[ wa ]",        (void*)g_lst_item[1]);
	print_test_lstitem("lstitem            ",	FALSE,	"[mou ]",        (void*)g_lst_item[2]);
	print_test_lstitem("lstitem            ",	FALSE,	"[shindeiru.]",  (void*)g_lst_item[3]);
	print_test_lstitem("lstitem (empty str)",	FALSE,	"[]",            (void*)"");
	print_test_lstitem("lstitem (null item)",	FALSE,	"[NULL]",        NULL);
}
#endif



#ifndef c_lstlen
void test_lstlen(void)	{}
#warning "lstlen() test suite function defined, but the function isn't defined."
#else
void	print_test_lstlen(char const* test_name, t_testflags flags,
		t_uint expecting,
		s_list(any) const* list)
{
	TEST_INIT(uint)
	TEST_PERFORM(lstlen(any), list)
	TEST_PRINT(uint,	lstlen, "list=%p", (void const*)list)
	// no TEST_FREE(): the caller owns the given list
}
void	test_lstlen(void)
{
	s_list(any)*	fixture = gen_list_fixture();
	s_list(any)*	single = c_lstitem(any)((void*)g_lst_item[0]);
//	| TEST FUNCTION   | TEST NAME           |TESTFLAG| EXPECTING | TEST ARGS
	print_test_lstlen("lstlen             ",	FALSE,	4,          fixture);
	print_test_lstlen("lstlen (1 item)    ",	FALSE,	1,          single);
	print_test_lstlen("lstlen (sub-list)  ",	FALSE,	2,          fixture->next->next);
	print_test_lstlen("lstlen (null list) ",	FALSE,	0,          NULL);
	c_lstfree(any)(fixture);
	c_lstfree(any)(single);
}
#endif



#ifndef c_lstget
void test_lstget(void)	{}
#warning "lstget() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstget(s_list(any) const* list, t_uint index)
{
	void**	result = c_lstget(any)(list, index);
	if (result == NULL)
		return (strdup("(null)"));
	return (strdup(*result ? (char const*)*result : "NULL"));
}
void	print_test_lstget(char const* test_name, t_testflags flags,
		char const* expecting,
		s_list(any) const* list,
		t_uint index)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstget, list, index)
	TEST_PRINT(str,	lstget, "list=%p, index=%u", (void const*)list, index)
	TEST_FREE()
}
void	test_lstget(void)
{
	s_list(any)*	fixture = gen_list_fixture();
//	| TEST FUNCTION   | TEST NAME             |TESTFLAG| EXPECTING    | TEST ARGS
	print_test_lstget("lstget             ",	FALSE,	"Omae",        fixture, 0);
	print_test_lstget("lstget             ",	FALSE,	" wa ",        fixture, 1);
	print_test_lstget("lstget             ",	FALSE,	"mou ",        fixture, 2);
	print_test_lstget("lstget             ",	FALSE,	"shindeiru.",  fixture, 3);
	print_test_lstget("lstget (beyond end)",	FALSE,	"(null)",      fixture, 4);
	print_test_lstget("lstget (huge index)",	FALSE,	"(null)",      fixture, 12345);
	print_test_lstget("lstget (null list) ",	FALSE,	"(null)",      NULL, 0);
	c_lstfree(any)(fixture);
}
#endif



#ifndef c_lstset
void test_lstset(void)	{}
#warning "lstset() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstset(t_uint index, void* item)
{
	s_list(any)*	list = gen_list_fixture();
	c_lstset(any)(list, index, item);
	return (gen_list_consume(list));
}
void	print_test_lstset(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint index,
		void* item)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstset, index, item)
	TEST_PRINT(str,	lstset, "index=%u, item=%p", index, item)
	TEST_FREE()
}
void	test_lstset(void)
{
//	| TEST FUNCTION   | TEST NAME             |TESTFLAG| EXPECTING                            | TEST ARGS
	print_test_lstset("lstset (first)     ",	FALSE,	"[YO][ wa ][mou ][shindeiru.]",        0, (void*)"YO");
	print_test_lstset("lstset (middle)    ",	FALSE,	"[Omae][ wa ][YO][shindeiru.]",        2, (void*)"YO");
	print_test_lstset("lstset (last)      ",	FALSE,	"[Omae][ wa ][mou ][YO]",              3, (void*)"YO");
	print_test_lstset("lstset (null item) ",	FALSE,	"[Omae][NULL][mou ][shindeiru.]",      1, NULL);
	print_test_lstset("lstset (beyond end)",	FALSE,	GEN_LIST_FIXTURE_STR,                  4, (void*)"YO");
	print_test_lstset("lstset (huge index)",	FALSE,	GEN_LIST_FIXTURE_STR,                  9999, (void*)"YO");
}
#endif



#ifndef c_lstnew
void test_lstnew(void)	{}
#warning "lstnew() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstnew(t_uint n, void* value)
{
	return (gen_list_consume(c_lstnew(any)(n, value)));
}
void	print_test_lstnew(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint n,
		void* value)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstnew, n, value)
	TEST_PRINT(str,	lstnew, "n=%u, value=%p", n, value)
	TEST_FREE()
}
void	test_lstnew(void)
{
//	| TEST FUNCTION   | TEST NAME           |TESTFLAG| EXPECTING              | TEST ARGS
	print_test_lstnew("lstnew             ",	FALSE,	"[yo]",                  1, (void*)"yo");
	print_test_lstnew("lstnew             ",	FALSE,	"[yo][yo][yo]",          3, (void*)"yo");
	print_test_lstnew("lstnew (null value)",	FALSE,	"[NULL][NULL]",          2, NULL);
	print_test_lstnew("lstnew (n = 0)     ",	FALSE,	"",                      0, (void*)"yo");
}
#endif



#ifndef c_lstcreate
void test_lstcreate(void)	{}
#warning "lstcreate() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstcreate(t_uint n)
{
	return (gen_list_consume(c_lstcreate(any)(n,
		(void*)g_lst_item[0],
		(void*)g_lst_item[1],
		(void*)g_lst_item[2],
		(void*)g_lst_item[3])));
}
void	print_test_lstcreate(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint n)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstcreate, n)
	TEST_PRINT(str,	lstcreate, "n=%u, ...", n)
	TEST_FREE()
}
void	test_lstcreate(void)
{
//	| TEST FUNCTION      | TEST NAME              |TESTFLAG| EXPECTING            | TEST ARGS
	print_test_lstcreate("lstcreate          ",	FALSE,	GEN_LIST_FIXTURE_STR,  4);
	print_test_lstcreate("lstcreate          ",	FALSE,	"[Omae][ wa ]",        2);
	print_test_lstcreate("lstcreate (1 item) ",	FALSE,	"[Omae]",              1);
	print_test_lstcreate("lstcreate (n = 0)  ",	FALSE,	"",                    0);
}
#endif



#ifndef c_lstdup
void test_lstdup(void)	{}
#warning "lstdup() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstdup(void)
{
	s_list(any)*	original = gen_list_fixture();
	s_list(any)*	result = c_lstdup(any)(original);
	c_lstfree(any)(original); // the duplicate must survive its original being freed
	return (gen_list_consume(result));
}
void	print_test_lstdup(char const* test_name, t_testflags flags,
		char const* expecting)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstdup)
	TEST_PRINT(str,	lstdup, "list=(4-item fixture)")
	TEST_FREE()
}
void	test_lstdup(void)
{
//	| TEST FUNCTION   | TEST NAME           |TESTFLAG| EXPECTING
	print_test_lstdup("lstdup             ",	FALSE,	GEN_LIST_FIXTURE_STR);
}
#endif



#ifndef c_lstsub
void test_lstsub(void)	{}
#warning "lstsub() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstsub(t_uint index, t_uint n)
{
	s_list(any)*	list = gen_list_fixture();
	s_list(any)*	result = c_lstsub(any)(list, index, n);
	char*	str = gen_list_tostr(result);
	if (result)
		c_lstfree(any)(result);
	c_lstfree(any)(list);
	return (str);
}
void	print_test_lstsub(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint index,
		t_uint n)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstsub, index, n)
	TEST_PRINT(str,	lstsub, "index=%u, n=%u", index, n)
	TEST_FREE()
}
void	test_lstsub(void)
{
//	| TEST FUNCTION   | TEST NAME             |TESTFLAG| EXPECTING                       | TEST ARGS
	print_test_lstsub("lstsub (beginning)  ",	FALSE,	"[Omae][ wa ]",                   0, 2);
	print_test_lstsub("lstsub (middle)     ",	FALSE,	"[ wa ][mou ]",                   1, 2);
	print_test_lstsub("lstsub (end)        ",	FALSE,	"[mou ][shindeiru.]",             2, 2);
	print_test_lstsub("lstsub (single)     ",	FALSE,	"[ wa ]",                         1, 1);
	print_test_lstsub("lstsub (whole list) ",	FALSE,	GEN_LIST_FIXTURE_STR,             0, 4);
	print_test_lstsub("lstsub (n=0 -> rest)",	FALSE,	"[mou ][shindeiru.]",             2, 0);
	print_test_lstsub("lstsub (bad index)  ",	FALSE,	"",                               4, 1);
	print_test_lstsub("lstsub (n too large)",	FALSE,	"",                               2, 3);
}
#endif



#ifndef c_lstcpy
void test_lstcpy(void)	{}
#warning "lstcpy() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstcpy(t_uint dest_i, t_uint src_i, t_uint n)
{
	s_list(any)*	dest = c_lstcreate(any)(4, (void*)"D0", (void*)"D1", (void*)"D2", (void*)"D3");
	s_list(any)*	src = gen_list_fixture();
	c_lstcpy(any)(dest, dest_i, src, src_i, n);
	c_lstfree(any)(src);
	return (gen_list_consume(dest));
}
void	print_test_lstcpy(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint dest_i,
		t_uint src_i,
		t_uint n)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstcpy, dest_i, src_i, n)
	TEST_PRINT(str,	lstcpy, "dest_i=%u, src_i=%u, n=%u", dest_i, src_i, n)
	TEST_FREE()
}
void	test_lstcpy(void)
{
//	| TEST FUNCTION   | TEST NAME             |TESTFLAG| EXPECTING                       | TEST ARGS
	print_test_lstcpy("lstcpy (full copy)  ",	FALSE,	GEN_LIST_FIXTURE_STR,             0, 0, 4);
	print_test_lstcpy("lstcpy (2 items)    ",	FALSE,	"[Omae][ wa ][D2][D3]",           0, 0, 2);
	print_test_lstcpy("lstcpy (offset dest)",	FALSE,	"[D0][D1][Omae][ wa ]",           2, 0, 2);
	print_test_lstcpy("lstcpy (offset src) ",	FALSE,	"[mou ][shindeiru.][D2][D3]",     0, 2, 2);
	print_test_lstcpy("lstcpy (n=0 -> rest)",	FALSE,	"[D0][mou ][shindeiru.][D3]",     1, 2, 0);
	print_test_lstcpy("lstcpy (bad dest_i) ",	FALSE,	"[D0][D1][D2][D3]",               4, 0, 1);
	print_test_lstcpy("lstcpy (bad src_i)  ",	FALSE,	"[D0][D1][D2][D3]",               0, 4, 1);
	print_test_lstcpy("lstcpy (n too large)",	FALSE,	"[D0][D1][D2][D3]",               2, 0, 3);
}
#endif



#ifndef c_lstdel
void test_lstdel(void)	{}
#warning "lstdel() test suite function defined, but the function isn't defined."
#else
static void*	c_gen_lstdel(void)
{
	s_list(any)*	list = gen_list_fixture();
	c_lstdel(any)(&list);
	return (list); // the given pointer must have been set to NULL
}
void	print_test_lstdel(char const* test_name, t_testflags flags,
		void const* expecting)
{
	TEST_INIT(ptr)
	TEST_PERFORM(gen_lstdel)
	TEST_PRINT(ptr,	lstdel, "list=(4-item fixture)")
}
void	test_lstdel(void)
{
//	| TEST FUNCTION   | TEST NAME           |TESTFLAG| EXPECTING
	print_test_lstdel("lstdel             ",	FALSE,	NULL);
}
#endif



#ifndef c_lstfdel
void test_lstfdel(void)	{}
#warning "lstfdel() test suite function defined, but the function isn't defined."
#else
static t_uint	g_lstfdel_count = 0;
static void	gen_lstfdel_delete(void** a_item)
{
	(void)a_item;
	g_lstfdel_count += 1;
}
static t_uint	c_gen_lstfdel(t_uint n)
{
	s_list(any)*	list = (n == 0 ? NULL : c_lstnew(any)(n, (void*)g_lst_item[0]));
	g_lstfdel_count = 0;
	c_lstfdel(any)(&list, gen_lstfdel_delete);
	if (list != NULL) // the given pointer must have been set to NULL
		return ((t_uint)-1);
	return (g_lstfdel_count); // amount of times the del() function was called
}
void	print_test_lstfdel(char const* test_name, t_testflags flags,
		t_uint expecting,
		t_uint n)
{
	TEST_INIT(uint)
	TEST_PERFORM(gen_lstfdel, n)
	TEST_PRINT(uint,	lstfdel, "list=(%u items), del=(counting function)", n)
}
void	test_lstfdel(void)
{
//	| TEST FUNCTION    | TEST NAME            |TESTFLAG| EXPECTING | TEST ARGS
	print_test_lstfdel("lstfdel            ",	FALSE,	4,          4);
	print_test_lstfdel("lstfdel (1 item)   ",	FALSE,	1,          1);
	print_test_lstfdel("lstfdel (null list)",	FALSE,	0,          0);
}
#endif



/*============================================================================*\
||                         List: adding/removing items                        ||
\*============================================================================*/

#ifndef c_lstadd
void test_lstadd(void)	{}
#warning "lstadd() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstadd(t_uint fixture_size, void* item)
{
	s_list(any)*	list = (fixture_size == 0 ? NULL : gen_list_fixture());
	list = c_lstadd(any)(list, item);
	return (gen_list_consume(list));
}
void	print_test_lstadd(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint fixture_size,
		void* item)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstadd, fixture_size, item)
	TEST_PRINT(str,	lstadd, "list=(%u items), item=%p", fixture_size, item)
	TEST_FREE()
}
void	test_lstadd(void)
{
//	| TEST FUNCTION   | TEST NAME           |TESTFLAG| EXPECTING                                 | TEST ARGS
	print_test_lstadd("lstadd             ",	FALSE,	"[Omae][ wa ][mou ][shindeiru.][YO]",       4, (void*)"YO");
	print_test_lstadd("lstadd (null list) ",	FALSE,	"[YO]",                                     0, (void*)"YO");
	print_test_lstadd("lstadd (null item) ",	FALSE,	"[Omae][ wa ][mou ][shindeiru.][NULL]",     4, NULL);
}
#endif



#ifndef c_lstinsert
void test_lstinsert(void)	{}
#warning "lstinsert() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstinsert(t_uint fixture_size, void* item, t_uint index)
{
	s_list(any)*	list = (fixture_size == 0 ? NULL : gen_list_fixture());
	list = c_lstinsert(any)(list, item, index);
	return (gen_list_consume(list));
}
void	print_test_lstinsert(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint fixture_size,
		void* item,
		t_uint index)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstinsert, fixture_size, item, index)
	TEST_PRINT(str,	lstinsert, "list=(%u items), item=%p, index=%u", fixture_size, item, index)
	TEST_FREE()
}
void	test_lstinsert(void)
{
//	| TEST FUNCTION      | TEST NAME               |TESTFLAG| EXPECTING                                 | TEST ARGS
	print_test_lstinsert("lstinsert (start)     ",	FALSE,	"[YO][Omae][ wa ][mou ][shindeiru.]",       4, (void*)"YO", 0);
	print_test_lstinsert("lstinsert (middle)    ",	FALSE,	"[Omae][ wa ][YO][mou ][shindeiru.]",       4, (void*)"YO", 2);
	print_test_lstinsert("lstinsert (end)       ",	FALSE,	"[Omae][ wa ][mou ][shindeiru.][YO]",       4, (void*)"YO", 4);
	print_test_lstinsert("lstinsert (null list) ",	FALSE,	"[YO]",                                     0, (void*)"YO", 0);
	print_test_lstinsert("lstinsert (beyond end)",	FALSE,	"",                                         4, (void*)"YO", 9);
}
#endif



#ifndef c_lstwedge
void test_lstwedge(void)	{}
#warning "lstwedge() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstwedge(t_uint fixture_size, t_uint index)
{
	s_list(any)*	list = (fixture_size == 0 ? NULL : gen_list_fixture());
	s_list(any)*	src = c_lstcreate(any)(2, (void*)"S0", (void*)"S1");
	list = c_lstwedge(any)(list, src, index);
	c_lstfree(any)(src); // wedge duplicates the src content: src remains owned by the caller
	return (gen_list_consume(list));
}
void	print_test_lstwedge(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint fixture_size,
		t_uint index)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstwedge, fixture_size, index)
	TEST_PRINT(str,	lstwedge, "list=(%u items), src=[S0][S1], index=%u", fixture_size, index)
	TEST_FREE()
}
void	test_lstwedge(void)
{
//	| TEST FUNCTION     | TEST NAME              |TESTFLAG| EXPECTING                                     | TEST ARGS
	print_test_lstwedge("lstwedge (start)     ",	FALSE,	"[S0][S1][Omae][ wa ][mou ][shindeiru.]",       4, 0);
	print_test_lstwedge("lstwedge (middle)    ",	FALSE,	"[Omae][ wa ][S0][S1][mou ][shindeiru.]",       4, 2);
	print_test_lstwedge("lstwedge (end)       ",	FALSE,	"[Omae][ wa ][mou ][shindeiru.][S0][S1]",       4, 4);
	print_test_lstwedge("lstwedge (null list) ",	FALSE,	"[S0][S1]",                                     0, 0);
	print_test_lstwedge("lstwedge (beyond end)",	FALSE,	"",                                             4, 9);
}
#endif



#ifndef c_lstdelat
void test_lstdelat(void)	{}
#warning "lstdelat() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstdelat(t_uint index)
{
	s_list(any)*	list = gen_list_fixture();
	list = c_lstdelat(any)(list, index);
	return (gen_list_consume(list));
}
void	print_test_lstdelat(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint index)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstdelat, index)
	TEST_PRINT(str,	lstdelat, "index=%u", index)
	TEST_FREE()
}
void	test_lstdelat(void)
{
//	| TEST FUNCTION     | TEST NAME              |TESTFLAG| EXPECTING                       | TEST ARGS
	print_test_lstdelat("lstdelat (first)     ",	FALSE,	"[ wa ][mou ][shindeiru.]",       0);
	print_test_lstdelat("lstdelat (middle)    ",	FALSE,	"[Omae][mou ][shindeiru.]",       1);
	print_test_lstdelat("lstdelat (last)      ",	FALSE,	"[Omae][ wa ][mou ]",             3);
	print_test_lstdelat("lstdelat (beyond end)",	FALSE,	GEN_LIST_FIXTURE_STR,             4);
	print_test_lstdelat("lstdelat (huge index)",	FALSE,	GEN_LIST_FIXTURE_STR,             9999);
}
#endif



#ifndef c_lstdelone
void test_lstdelone(void)	{}
#warning "lstdelone() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstdelone(t_bool duplicates, void* item)
{
	s_list(any)*	list;
	if (duplicates)
		list = c_lstcreate(any)(4,
			(void*)g_lst_item[0], (void*)g_lst_item[1],
			(void*)g_lst_item[0], (void*)g_lst_item[1]);
	else
		list = gen_list_fixture();
	list = c_lstdelone(any)(list, item);
	return (gen_list_consume(list));
}
void	print_test_lstdelone(char const* test_name, t_testflags flags,
		char const* expecting,
		t_bool duplicates,
		void* item)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstdelone, duplicates, item)
	TEST_PRINT(str,	lstdelone, "list=(%s), item=%p", (duplicates ? "with duplicates" : "fixture"), item)
	TEST_FREE()
}
void	test_lstdelone(void)
{
//	| TEST FUNCTION      | TEST NAME                 |TESTFLAG| EXPECTING                       | TEST ARGS
	print_test_lstdelone("lstdelone (first)       ",	FALSE,	"[ wa ][mou ][shindeiru.]",       FALSE, (void*)g_lst_item[0]);
	print_test_lstdelone("lstdelone (middle)      ",	FALSE,	"[Omae][ wa ][shindeiru.]",       FALSE, (void*)g_lst_item[2]);
	print_test_lstdelone("lstdelone (last)        ",	FALSE,	"[Omae][ wa ][mou ]",             FALSE, (void*)g_lst_item[3]);
	print_test_lstdelone("lstdelone (only first)  ",	FALSE,	"[ wa ][Omae][ wa ]",             TRUE,  (void*)g_lst_item[0]);
	print_test_lstdelone("lstdelone (identity)    ",	FALSE,	GEN_LIST_FIXTURE_STR,             FALSE, (void*)g_lst_twin);
	print_test_lstdelone("lstdelone (not present) ",	FALSE,	GEN_LIST_FIXTURE_STR,             FALSE, (void*)"nope");
}
#endif



#ifndef c_lstdelall
void test_lstdelall(void)	{}
#warning "lstdelall() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstdelall(void* item)
{
	s_list(any)*	list = c_lstcreate(any)(5,
		(void*)g_lst_item[0], (void*)g_lst_item[1],
		(void*)g_lst_item[0], (void*)g_lst_item[1],
		(void*)g_lst_item[0]);
	list = c_lstdelall(any)(list, item);
	return (gen_list_consume(list));
}
void	print_test_lstdelall(char const* test_name, t_testflags flags,
		char const* expecting,
		void* item)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstdelall, item)
	TEST_PRINT(str,	lstdelall, "list=[Omae][ wa ][Omae][ wa ][Omae], item=%p", item)
	TEST_FREE()
}
void	test_lstdelall(void)
{
//	| TEST FUNCTION      | TEST NAME                 |TESTFLAG| EXPECTING                             | TEST ARGS
	print_test_lstdelall("lstdelall               ",	FALSE,	"[ wa ][ wa ]",                         (void*)g_lst_item[0]);
	print_test_lstdelall("lstdelall               ",	FALSE,	"[Omae][Omae][Omae]",                   (void*)g_lst_item[1]);
	print_test_lstdelall("lstdelall (identity)    ",	FALSE,	"[Omae][ wa ][Omae][ wa ][Omae]",       (void*)g_lst_twin);
	print_test_lstdelall("lstdelall (not present) ",	FALSE,	"[Omae][ wa ][Omae][ wa ][Omae]",       (void*)"nope");
}
#endif



/*============================================================================*\
||                         List: replacing/reordering                         ||
\*============================================================================*/

#ifndef c_lstrep
void test_lstrep(void)	{}
#warning "lstrep() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstrep(void* item_old, void* item_new)
{
	s_list(any)*	list = c_lstcreate(any)(4,
		(void*)g_lst_item[0], (void*)g_lst_item[1],
		(void*)g_lst_item[0], (void*)g_lst_item[2]);
	s_list(any)*	result = c_lstrep(any)(list, item_old, item_new);
	char*	str = gen_list_consume(result);
	c_lstfree(any)(list); // the operation is pure: the original list is untouched
	return (str);
}
void	print_test_lstrep(char const* test_name, t_testflags flags,
		char const* expecting,
		void* item_old,
		void* item_new)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstrep, item_old, item_new)
	TEST_PRINT(str,	lstrep, "list=[Omae][ wa ][Omae][mou ], old=%p, new=%p", item_old, item_new)
	TEST_FREE()
}
void	test_lstrep(void)
{
//	| TEST FUNCTION   | TEST NAME              |TESTFLAG| EXPECTING                       | TEST ARGS
	print_test_lstrep("lstrep (all matches) ",	FALSE,	"[YO][ wa ][YO][mou ]",           (void*)g_lst_item[0], (void*)"YO");
	print_test_lstrep("lstrep (one match)   ",	FALSE,	"[Omae][YO][Omae][mou ]",         (void*)g_lst_item[1], (void*)"YO");
	print_test_lstrep("lstrep (identity)    ",	FALSE,	"[Omae][ wa ][Omae][mou ]",       (void*)g_lst_twin,    (void*)"YO");
	print_test_lstrep("lstrep (not present) ",	FALSE,	"[Omae][ wa ][Omae][mou ]",       (void*)"nope",        (void*)"YO");
}
#endif



#ifndef c_lstrepfirst
void test_lstrepfirst(void)	{}
#warning "lstrepfirst() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstrepfirst(void* item_old, void* item_new, t_uint n)
{
	s_list(any)*	list = c_lstcreate(any)(4,
		(void*)g_lst_item[0], (void*)g_lst_item[1],
		(void*)g_lst_item[0], (void*)g_lst_item[0]);
	s_list(any)*	result = c_lstrepfirst(any)(list, item_old, item_new, n);
	char*	str = gen_list_consume(result);
	c_lstfree(any)(list);
	return (str);
}
void	print_test_lstrepfirst(char const* test_name, t_testflags flags,
		char const* expecting,
		void* item_old,
		void* item_new,
		t_uint n)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstrepfirst, item_old, item_new, n)
	TEST_PRINT(str,	lstrepfirst, "list=[Omae][ wa ][Omae][Omae], old=%p, new=%p, n=%u", item_old, item_new, n)
	TEST_FREE()
}
void	test_lstrepfirst(void)
{
//	| TEST FUNCTION        | TEST NAME               |TESTFLAG| EXPECTING                 | TEST ARGS
	print_test_lstrepfirst("lstrepfirst (n = 1)   ",	FALSE,	"[YO][ wa ][Omae][Omae]",   (void*)g_lst_item[0], (void*)"YO", 1);
	print_test_lstrepfirst("lstrepfirst (n = 2)   ",	FALSE,	"[YO][ wa ][YO][Omae]",     (void*)g_lst_item[0], (void*)"YO", 2);
	print_test_lstrepfirst("lstrepfirst (n > all) ",	FALSE,	"[YO][ wa ][YO][YO]",       (void*)g_lst_item[0], (void*)"YO", 9);
}
#endif



#ifndef c_lstreplast
void test_lstreplast(void)	{}
#warning "lstreplast() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstreplast(void* item_old, void* item_new, t_uint n)
{
	s_list(any)*	list = c_lstcreate(any)(4,
		(void*)g_lst_item[0], (void*)g_lst_item[1],
		(void*)g_lst_item[0], (void*)g_lst_item[0]);
	s_list(any)*	result = c_lstreplast(any)(list, item_old, item_new, n);
	char*	str = gen_list_consume(result);
	c_lstfree(any)(list);
	return (str);
}
void	print_test_lstreplast(char const* test_name, t_testflags flags,
		char const* expecting,
		void* item_old,
		void* item_new,
		t_uint n)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstreplast, item_old, item_new, n)
	TEST_PRINT(str,	lstreplast, "list=[Omae][ wa ][Omae][Omae], old=%p, new=%p, n=%u", item_old, item_new, n)
	TEST_FREE()
}
void	test_lstreplast(void)
{
//	| TEST FUNCTION       | TEST NAME               |TESTFLAG| EXPECTING                 | TEST ARGS
	print_test_lstreplast("lstreplast (n = 1)   ",	FALSE,	"[Omae][ wa ][Omae][YO]",   (void*)g_lst_item[0], (void*)"YO", 1);
	print_test_lstreplast("lstreplast (n = 2)   ",	FALSE,	"[Omae][ wa ][YO][YO]",     (void*)g_lst_item[0], (void*)"YO", 2);
	print_test_lstreplast("lstreplast (n > all) ",	FALSE,	"[YO][ wa ][YO][YO]",       (void*)g_lst_item[0], (void*)"YO", 9);
}
#endif



#ifndef c_lstrev
void test_lstrev(void)	{}
#warning "lstrev() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstrev(t_uint fixture_size)
{
	s_list(any)*	list = NULL;
	s_list(any)*	result;
	char*	str;
	if (fixture_size == 1)
		list = c_lstitem(any)((void*)g_lst_item[0]);
	else if (fixture_size > 1)
		list = gen_list_fixture();
	result = c_lstrev(any)(list);
	str = gen_list_consume(result);
	if (list)
		c_lstfree(any)(list); // the operation is pure: the original list is untouched
	return (str);
}
void	print_test_lstrev(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint fixture_size)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstrev, fixture_size)
	TEST_PRINT(str,	lstrev, "list=(%u items)", fixture_size)
	TEST_FREE()
}
void	test_lstrev(void)
{
//	| TEST FUNCTION   | TEST NAME           |TESTFLAG| EXPECTING                            | TEST ARGS
	print_test_lstrev("lstrev             ",	FALSE,	"[shindeiru.][mou ][ wa ][Omae]",      4);
	print_test_lstrev("lstrev (1 item)    ",	FALSE,	"[Omae]",                              1);
	print_test_lstrev("lstrev (null list) ",	FALSE,	"",                                    0);
}
#endif



/*============================================================================*\
||                          List: combining two lists                         ||
\*============================================================================*/

#ifndef c_lstconcat
void test_lstconcat(void)	{}
#warning "lstconcat() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstconcat(t_bool has_list1, t_bool has_list2)
{
	s_list(any)*	list1 = (has_list1 ? c_lstcreate(any)(2, (void*)"A0", (void*)"A1") : NULL);
	s_list(any)*	list2 = (has_list2 ? c_lstcreate(any)(2, (void*)"B0", (void*)"B1") : NULL);
	s_list(any)*	result = c_lstconcat(any)(list1, list2);
	char*	str = gen_list_consume(result);
	if (list1)	c_lstfree(any)(list1); // the operation is pure: both lists are untouched
	if (list2)	c_lstfree(any)(list2);
	return (str);
}
void	print_test_lstconcat(char const* test_name, t_testflags flags,
		char const* expecting,
		t_bool has_list1,
		t_bool has_list2)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstconcat, has_list1, has_list2)
	TEST_PRINT(str,	lstconcat, "list1=%s, list2=%s", (has_list1 ? "[A0][A1]" : "NULL"), (has_list2 ? "[B0][B1]" : "NULL"))
	TEST_FREE()
}
void	test_lstconcat(void)
{
//	| TEST FUNCTION      | TEST NAME               |TESTFLAG| EXPECTING              | TEST ARGS
	print_test_lstconcat("lstconcat            ",	FALSE,	"[A0][A1][B0][B1]",      TRUE,  TRUE);
	print_test_lstconcat("lstconcat (null lhs) ",	FALSE,	"[B0][B1]",              FALSE, TRUE);
	print_test_lstconcat("lstconcat (null rhs) ",	FALSE,	"[A0][A1]",              TRUE,  FALSE);
	print_test_lstconcat("lstconcat (null both)",	FALSE,	"",                      FALSE, FALSE);
}
#endif



#ifndef c_lstappend
void test_lstappend(void)	{}
#warning "lstappend() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstappend(t_bool has_list1, t_bool has_list2)
{
	s_list(any)*	list1 = (has_list1 ? c_lstcreate(any)(2, (void*)"A0", (void*)"A1") : NULL);
	s_list(any)*	list2 = (has_list2 ? c_lstcreate(any)(2, (void*)"B0", (void*)"B1") : NULL);
	s_list(any)*	result = c_lstappend(any)(list1, list2);
	char*	str = gen_list_consume(result);
	if (list2)	c_lstfree(any)(list2); // NOTE: list1 is consumed by the operation, but list2 is not
	return (str);
}
void	print_test_lstappend(char const* test_name, t_testflags flags,
		char const* expecting,
		t_bool has_list1,
		t_bool has_list2)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstappend, has_list1, has_list2)
	TEST_PRINT(str,	lstappend, "list1=%s, list2=%s", (has_list1 ? "[A0][A1]" : "NULL"), (has_list2 ? "[B0][B1]" : "NULL"))
	TEST_FREE()
}
void	test_lstappend(void)
{
//	| TEST FUNCTION      | TEST NAME               |TESTFLAG| EXPECTING              | TEST ARGS
	print_test_lstappend("lstappend            ",	FALSE,	"[A0][A1][B0][B1]",      TRUE,  TRUE);
	print_test_lstappend("lstappend (null dest)",	FALSE,	"[B0][B1]",              FALSE, TRUE);
	print_test_lstappend("lstappend (null src) ",	FALSE,	"[A0][A1]",              TRUE,  FALSE);
	print_test_lstappend("lstappend (null both)",	FALSE,	"",                      FALSE, FALSE);
}
#endif



#ifndef c_lstprepend
void test_lstprepend(void)	{}
#warning "lstprepend() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstprepend(t_bool has_list1, t_bool has_list2)
{
	s_list(any)*	list1 = (has_list1 ? c_lstcreate(any)(2, (void*)"A0", (void*)"A1") : NULL);
	s_list(any)*	list2 = (has_list2 ? c_lstcreate(any)(2, (void*)"B0", (void*)"B1") : NULL);
	s_list(any)*	result = c_lstprepend(any)(list1, list2);
	char*	str = gen_list_consume(result);
	if (list1)	c_lstfree(any)(list1); // NOTE: list2 is consumed by the operation, but list1 is not
	return (str);
}
void	print_test_lstprepend(char const* test_name, t_testflags flags,
		char const* expecting,
		t_bool has_list1,
		t_bool has_list2)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstprepend, has_list1, has_list2)
	TEST_PRINT(str,	lstprepend, "list1=%s, list2=%s", (has_list1 ? "[A0][A1]" : "NULL"), (has_list2 ? "[B0][B1]" : "NULL"))
	TEST_FREE()
}
void	test_lstprepend(void)
{
//	| TEST FUNCTION       | TEST NAME                |TESTFLAG| EXPECTING              | TEST ARGS
	print_test_lstprepend("lstprepend           ",	FALSE,	"[A0][A1][B0][B1]",      TRUE,  TRUE);
	print_test_lstprepend("lstprepend (null lhs)",	FALSE,	"[B0][B1]",              FALSE, TRUE);
	print_test_lstprepend("lstprepend (null rhs)",	FALSE,	"[A0][A1]",              TRUE,  FALSE);
}
#endif



#ifndef c_lstmerge
void test_lstmerge(void)	{}
#warning "lstmerge() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstmerge(t_bool has_list1, t_bool has_list2)
{
	s_list(any)*	list1 = (has_list1 ? c_lstcreate(any)(2, (void*)"A0", (void*)"A1") : NULL);
	s_list(any)*	list2 = (has_list2 ? c_lstcreate(any)(2, (void*)"B0", (void*)"B1") : NULL);
	s_list(any)*	result = c_lstmerge(any)(list1, list2);
	return (gen_list_consume(result)); // NOTE: both given lists are consumed by the operation
}
void	print_test_lstmerge(char const* test_name, t_testflags flags,
		char const* expecting,
		t_bool has_list1,
		t_bool has_list2)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstmerge, has_list1, has_list2)
	TEST_PRINT(str,	lstmerge, "list1=%s, list2=%s", (has_list1 ? "[A0][A1]" : "NULL"), (has_list2 ? "[B0][B1]" : "NULL"))
	TEST_FREE()
}
void	test_lstmerge(void)
{
//	| TEST FUNCTION     | TEST NAME              |TESTFLAG| EXPECTING              | TEST ARGS
	print_test_lstmerge("lstmerge            ",	FALSE,	"[A0][A1][B0][B1]",      TRUE,  TRUE);
	print_test_lstmerge("lstmerge (null lhs) ",	FALSE,	"[B0][B1]",              FALSE, TRUE);
	print_test_lstmerge("lstmerge (null rhs) ",	FALSE,	"[A0][A1]",              TRUE,  FALSE);
}
#endif



/*============================================================================*\
||                         List: comparison operations                        ||
\*============================================================================*/

#ifndef c_lstequ
void test_lstequ(void)	{}
#warning "lstequ() test suite function defined, but the function isn't defined."
#else
void	print_test_lstequ(char const* test_name, t_testflags flags,
		t_bool expecting,
		s_list(any) const* list1,
		s_list(any) const* list2)
{
	TEST_INIT(bool)
	TEST_PERFORM(lstequ(any), list1, list2)
	TEST_PRINT(bool,	lstequ, "list1=%p, list2=%p", (void const*)list1, (void const*)list2)
}
void	test_lstequ(void)
{
	s_list(any)*	fixture = gen_list_fixture();
	s_list(any)*	same = gen_list_fixture();
	s_list(any)*	shorter = c_lstcreate(any)(2, (void*)g_lst_item[0], (void*)g_lst_item[1]);
	s_list(any)*	twin = c_lstcreate(any)(4, (void*)g_lst_twin, (void*)g_lst_item[1], (void*)g_lst_item[2], (void*)g_lst_item[3]);
//	| TEST FUNCTION   | TEST NAME               |TESTFLAG| EXPECTING | TEST ARGS
	print_test_lstequ("lstequ (same lists)   ",	FALSE,	TRUE,       fixture, same);
	print_test_lstequ("lstequ (same pointer) ",	FALSE,	TRUE,       fixture, fixture);
	print_test_lstequ("lstequ (l2 shorter)   ",	FALSE,	FALSE,      fixture, shorter);
	print_test_lstequ("lstequ (l1 shorter)   ",	FALSE,	FALSE,      shorter, fixture);
	print_test_lstequ("lstequ (identity)     ",	FALSE,	FALSE,      fixture, twin);
	print_test_lstequ("lstequ (null lhs)     ",	FALSE,	FALSE,      NULL,    fixture);
	print_test_lstequ("lstequ (null rhs)     ",	FALSE,	FALSE,      fixture, NULL);
	print_test_lstequ("lstequ (null both)    ",	FALSE,	TRUE,       NULL,    NULL);
	c_lstfree(any)(fixture);
	c_lstfree(any)(same);
	c_lstfree(any)(shorter);
	c_lstfree(any)(twin);
}
#endif



#ifndef c_lstnequ
void test_lstnequ(void)	{}
#warning "lstnequ() test suite function defined, but the function isn't defined."
#else
void	print_test_lstnequ(char const* test_name, t_testflags flags,
		t_bool expecting,
		s_list(any) const* list1,
		s_list(any) const* list2,
		t_uint n)
{
	TEST_INIT(bool)
	TEST_PERFORM(lstnequ(any), list1, list2, n)
	TEST_PRINT(bool,	lstnequ, "list1=%p, list2=%p, n=%u", (void const*)list1, (void const*)list2, n)
}
void	test_lstnequ(void)
{
	s_list(any)*	fixture = gen_list_fixture();
	s_list(any)*	differ = c_lstcreate(any)(4, (void*)g_lst_item[0], (void*)g_lst_item[1], (void*)"YO", (void*)"YO");
//	| TEST FUNCTION    | TEST NAME                |TESTFLAG| EXPECTING | TEST ARGS
	print_test_lstnequ("lstnequ (n = 1)        ",	FALSE,	TRUE,       fixture, differ, 1);
	print_test_lstnequ("lstnequ (n = 2)        ",	FALSE,	TRUE,       fixture, differ, 2);
	print_test_lstnequ("lstnequ (n = 3)        ",	FALSE,	FALSE,      fixture, differ, 3);
	print_test_lstnequ("lstnequ (n = 4)        ",	FALSE,	FALSE,      fixture, differ, 4);
	print_test_lstnequ("lstnequ (n > length)   ",	FALSE,	FALSE,      fixture, differ, 9);
	print_test_lstnequ("lstnequ (n = 0)        ",	FALSE,	TRUE,       fixture, differ, 0);
	c_lstfree(any)(fixture);
	c_lstfree(any)(differ);
}
#endif



static t_sint	gen_compare_str(void* item1, void* item2)
{
	int	result = strcmp(
		(item1 ? (char const*)item1 : ""),
		(item2 ? (char const*)item2 : ""));
	return (result < 0 ? -1 : (result > 0 ? +1 : 0));
}

#ifndef c_lstcmp
void test_lstcmp(void)	{}
#warning "lstcmp() test suite function defined, but the function isn't defined."
#else
void	print_test_lstcmp(char const* test_name, t_testflags flags,
		t_sint expecting,
		s_list(any) const* list1,
		s_list(any) const* list2)
{
	TEST_INIT(sint)
	TEST_PERFORM(lstcmp(any), list1, list2, gen_compare_str)
	TEST_PRINT(sint,	lstcmp, "list1=%p, list2=%p, compare=strcmp", (void const*)list1, (void const*)list2)
}
void	test_lstcmp(void)
{
	s_list(any)*	fixture = gen_list_fixture();
	s_list(any)*	twin = c_lstcreate(any)(4, (void*)g_lst_twin, (void*)g_lst_item[1], (void*)g_lst_item[2], (void*)g_lst_item[3]);
	s_list(any)*	bigger = c_lstcreate(any)(2, (void*)"zzz", (void*)g_lst_item[1]);
	s_list(any)*	smaller = c_lstcreate(any)(2, (void*)"AAA", (void*)g_lst_item[1]);
//	| TEST FUNCTION   | TEST NAME                |TESTFLAG| EXPECTING | TEST ARGS
	print_test_lstcmp("lstcmp (equal)         ",	FALSE,	0,          fixture, twin);
	print_test_lstcmp("lstcmp (same pointer)  ",	FALSE,	0,          fixture, fixture);
	print_test_lstcmp("lstcmp (l1 < l2)       ",	FALSE,	-1,         fixture, bigger); // "Omae" < "zzz"
	print_test_lstcmp("lstcmp (l1 > l2)       ",	FALSE,	+1,         fixture, smaller); // "Omae" > "AAA"
	c_lstfree(any)(fixture);
	c_lstfree(any)(twin);
	c_lstfree(any)(bigger);
	c_lstfree(any)(smaller);
}
#endif



#ifndef c_lstncmp
void test_lstncmp(void)	{}
#warning "lstncmp() test suite function defined, but the function isn't defined."
#else
void	print_test_lstncmp(char const* test_name, t_testflags flags,
		t_sint expecting,
		s_list(any) const* list1,
		s_list(any) const* list2,
		t_uint n)
{
	TEST_INIT(sint)
	TEST_PERFORM(lstncmp(any), list1, list2, gen_compare_str, n)
	TEST_PRINT(sint,	lstncmp, "list1=%p, list2=%p, compare=strcmp, n=%u", (void const*)list1, (void const*)list2, n)
}
void	test_lstncmp(void)
{
	s_list(any)*	fixture = gen_list_fixture();
	s_list(any)*	bigger = c_lstcreate(any)(2, (void*)g_lst_item[0], (void*)"zzz");
//	| TEST FUNCTION    | TEST NAME              |TESTFLAG| EXPECTING | TEST ARGS
	print_test_lstncmp("lstncmp (n = 1)      ",	FALSE,	0,          fixture, bigger, 1);
	print_test_lstncmp("lstncmp (n = 2)      ",	FALSE,	-1,         fixture, bigger, 2);
	print_test_lstncmp("lstncmp (n = 0)      ",	FALSE,	0,          fixture, bigger, 0);
	c_lstfree(any)(fixture);
	c_lstfree(any)(bigger);
}
#endif



/*============================================================================*\
||                          List: searching operations                        ||
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

#ifndef c_lstfind
void test_lstfind(void)	{}
#warning "lstfind() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstfind(s_list(any) const* list, void* item)
{
	s_list(any) const*	result = c_lstfind(any)(list, item);
	if (result == NULL)
		return (strdup("(null)"));
	return (gen_list_tostr(result)); // serialize the whole remainder, to check *which* node was returned
}
void	print_test_lstfind(char const* test_name, t_testflags flags,
		char const* expecting,
		s_list(any) const* list,
		void* item)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstfind, list, item)
	TEST_PRINT(str,	lstfind, "list=%p, item=%p", (void const*)list, item)
	TEST_FREE()
}
void	test_lstfind(void)
{
	s_list(any)*	fixture = gen_list_fixture();
//	| TEST FUNCTION    | TEST NAME               |TESTFLAG| EXPECTING                       | TEST ARGS
	print_test_lstfind("lstfind (first)       ",	FALSE,	GEN_LIST_FIXTURE_STR,             fixture, (void*)g_lst_item[0]);
	print_test_lstfind("lstfind (middle)      ",	FALSE,	"[mou ][shindeiru.]",             fixture, (void*)g_lst_item[2]);
	print_test_lstfind("lstfind (last)        ",	FALSE,	"[shindeiru.]",                   fixture, (void*)g_lst_item[3]);
	print_test_lstfind("lstfind (identity)    ",	FALSE,	"(null)",                         fixture, (void*)g_lst_twin);
	print_test_lstfind("lstfind (not present) ",	FALSE,	"(null)",                         fixture, (void*)"nope");
	c_lstfree(any)(fixture);
}
#endif



#ifndef c_lstffind
void test_lstffind(void)	{}
#warning "lstffind() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstffind(s_list(any) const* list, t_bool (*match)(void* item))
{
	s_list(any) const*	result = c_lstffind(any)(list, match);
	if (result == NULL)
		return (strdup("(null)"));
	return (gen_list_tostr(result));
}
void	print_test_lstffind(char const* test_name, t_testflags flags,
		char const* expecting,
		s_list(any) const* list,
		t_bool (*match)(void* item))
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstffind, list, match)
	TEST_PRINT(str,	lstffind, "list=%p, match=%p", (void const*)list, (void*)match)
	TEST_FREE()
}
void	test_lstffind(void)
{
	s_list(any)*	fixture = gen_list_fixture();
//	| TEST FUNCTION     | TEST NAME             |TESTFLAG| EXPECTING               | TEST ARGS
	print_test_lstffind("lstffind            ",	FALSE,	"[mou ][shindeiru.]",     fixture, gen_match_starts_with_m);
	print_test_lstffind("lstffind (no match) ",	FALSE,	"(null)",                 fixture, gen_match_never);
	c_lstfree(any)(fixture);
}
#endif



#ifndef c_lstfindi
void test_lstfindi(void)	{}
#warning "lstfindi() test suite function defined, but the function isn't defined."
#else
void	print_test_lstfindi(char const* test_name, t_testflags flags,
		t_sint expecting,
		s_list(any) const* list,
		void* item)
{
	TEST_INIT(sint)
	TEST_PERFORM(lstfindi(any), list, item)
	TEST_PRINT(sint,	lstfindi, "list=%p, item=%p", (void const*)list, item)
}
void	test_lstfindi(void)
{
	s_list(any)*	fixture = gen_list_fixture();
//	| TEST FUNCTION     | TEST NAME               |TESTFLAG| EXPECTING | TEST ARGS
	print_test_lstfindi("lstfindi (first)      ",	FALSE,	0,          fixture, (void*)g_lst_item[0]);
	print_test_lstfindi("lstfindi (middle)     ",	FALSE,	2,          fixture, (void*)g_lst_item[2]);
	print_test_lstfindi("lstfindi (last)       ",	FALSE,	3,          fixture, (void*)g_lst_item[3]);
	print_test_lstfindi("lstfindi (identity)   ",	FALSE,	ERROR,      fixture, (void*)g_lst_twin);
	print_test_lstfindi("lstfindi (not present)",	FALSE,	ERROR,      fixture, (void*)"nope");
	c_lstfree(any)(fixture);
}
#endif



#ifndef c_lstffindi
void test_lstffindi(void)	{}
#warning "lstffindi() test suite function defined, but the function isn't defined."
#else
void	print_test_lstffindi(char const* test_name, t_testflags flags,
		t_sint expecting,
		s_list(any) const* list,
		t_bool (*match)(void* item))
{
	TEST_INIT(sint)
	TEST_PERFORM(lstffindi(any), list, match)
	TEST_PRINT(sint,	lstffindi, "list=%p, match=%p", (void const*)list, (void*)match)
}
void	test_lstffindi(void)
{
	s_list(any)*	fixture = gen_list_fixture();
//	| TEST FUNCTION      | TEST NAME              |TESTFLAG| EXPECTING | TEST ARGS
	print_test_lstffindi("lstffindi            ",	FALSE,	2,          fixture, gen_match_starts_with_m);
	print_test_lstffindi("lstffindi (no match) ",	FALSE,	ERROR,      fixture, gen_match_never);
	c_lstfree(any)(fixture);
}
#endif



#ifndef c_lstcount
void test_lstcount(void)	{}
#warning "lstcount() test suite function defined, but the function isn't defined."
#else
void	print_test_lstcount(char const* test_name, t_testflags flags,
		t_uint expecting,
		s_list(any) const* list,
		void* item)
{
	TEST_INIT(uint)
	TEST_PERFORM(lstcount(any), list, item)
	TEST_PRINT(uint,	lstcount, "list=%p, item=%p", (void const*)list, item)
}
void	test_lstcount(void)
{
	s_list(any)*	list = c_lstcreate(any)(5,
		(void*)g_lst_item[0], (void*)g_lst_item[1],
		(void*)g_lst_item[0], (void*)g_lst_item[1],
		(void*)g_lst_item[0]);
//	| TEST FUNCTION     | TEST NAME                |TESTFLAG| EXPECTING | TEST ARGS
	print_test_lstcount("lstcount              ",	FALSE,	3,          list, (void*)g_lst_item[0]);
	print_test_lstcount("lstcount              ",	FALSE,	2,          list, (void*)g_lst_item[1]);
	print_test_lstcount("lstcount (identity)   ",	FALSE,	0,          list, (void*)g_lst_twin);
	print_test_lstcount("lstcount (not present)",	FALSE,	0,          list, (void*)"nope");
	print_test_lstcount("lstcount (null list)  ",	FALSE,	0,          NULL, (void*)g_lst_item[0]);
	c_lstfree(any)(list);
}
#endif



#ifndef c_lstcontains
void test_lstcontains(void)	{}
#warning "lstcontains() test suite function defined, but the function isn't defined."
#else
void	print_test_lstcontains(char const* test_name, t_testflags flags,
		t_bool expecting,
		s_list(any) const* list,
		void* item)
{
	TEST_INIT(bool)
	TEST_PERFORM(lstcontains(any), list, item)
	TEST_PRINT(bool,	lstcontains, "list=%p, item=%p", (void const*)list, item)
}
void	test_lstcontains(void)
{
	s_list(any)*	fixture = gen_list_fixture();
//	| TEST FUNCTION        | TEST NAME                   |TESTFLAG| EXPECTING | TEST ARGS
	print_test_lstcontains("lstcontains (first)       ",	FALSE,	TRUE,       fixture, (void*)g_lst_item[0]);
	print_test_lstcontains("lstcontains (last)        ",	FALSE,	TRUE,       fixture, (void*)g_lst_item[3]);
	print_test_lstcontains("lstcontains (identity)    ",	FALSE,	FALSE,      fixture, (void*)g_lst_twin);
	print_test_lstcontains("lstcontains (not present) ",	FALSE,	FALSE,      fixture, (void*)"nope");
	print_test_lstcontains("lstcontains (null list)   ",	FALSE,	FALSE,      NULL,    (void*)g_lst_item[0]);
	c_lstfree(any)(fixture);
}
#endif



#ifndef c_lsthas
void test_lsthas(void)	{}
#warning "lsthas() test suite function defined, but the function isn't defined."
#else
void	print_test_lsthas(char const* test_name, t_testflags flags,
		t_bool expecting,
		s_list(any) const* list,
		s_list(any) const* target)
{
	TEST_INIT(bool)
	TEST_PERFORM(lsthas(any), list, target)
	TEST_PRINT(bool,	lsthas, "list=%p, target=%p", (void const*)list, (void const*)target)
}
void	test_lsthas(void)
{
	s_list(any)*	fixture = gen_list_fixture();
	s_list(any)*	one_of = c_lstcreate(any)(2, (void*)"nope", (void*)g_lst_item[2]);
	s_list(any)*	none_of = c_lstcreate(any)(2, (void*)"nope", (void*)g_lst_twin);
//	| TEST FUNCTION   | TEST NAME               |TESTFLAG| EXPECTING | TEST ARGS
	print_test_lsthas("lsthas (one match)    ",	FALSE,	TRUE,       fixture, one_of);
	print_test_lsthas("lsthas (no matches)   ",	FALSE,	FALSE,      fixture, none_of);
	print_test_lsthas("lsthas (with itself)  ",	FALSE,	TRUE,       fixture, fixture);
	c_lstfree(any)(fixture);
	c_lstfree(any)(one_of);
	c_lstfree(any)(none_of);
}
#endif



#ifndef c_lsthasonly
void test_lsthasonly(void)	{}
#warning "lsthasonly() test suite function defined, but the function isn't defined."
#else
void	print_test_lsthasonly(char const* test_name, t_testflags flags,
		t_bool expecting,
		s_list(any) const* list,
		s_list(any) const* target)
{
	TEST_INIT(bool)
	TEST_PERFORM(lsthasonly(any), list, target)
	TEST_PRINT(bool,	lsthasonly, "list=%p, target=%p", (void const*)list, (void const*)target)
}
void	test_lsthasonly(void)
{
	s_list(any)*	fixture = gen_list_fixture();
	s_list(any)*	subset = c_lstcreate(any)(2, (void*)g_lst_item[0], (void*)g_lst_item[1]);
//	| TEST FUNCTION       | TEST NAME                  |TESTFLAG| EXPECTING | TEST ARGS
	print_test_lsthasonly("lsthasonly (with itself) ",	FALSE,	TRUE,       fixture, fixture);
	print_test_lsthasonly("lsthasonly (subset ok)   ",	FALSE,	TRUE,       subset,  fixture);
	print_test_lsthasonly("lsthasonly (extra items) ",	FALSE,	FALSE,      fixture, subset);
	c_lstfree(any)(fixture);
	c_lstfree(any)(subset);
}
#endif



/*============================================================================*\
||                        List: functional programming                        ||
\*============================================================================*/

//! Accumulates all visited items (and their given index, if any) for the Iterate tests
static char	g_lst_iter_buffer[256];
static void	gen_iterate_visit(void* item)
{
	strcat(g_lst_iter_buffer, "[");
	strcat(g_lst_iter_buffer, (item ? (char const*)item : "NULL"));
	strcat(g_lst_iter_buffer, "]");
}
static void	gen_iterate_visit_i(void* item, t_uint index)
{
	size_t	length = strlen(g_lst_iter_buffer);
	snprintf(g_lst_iter_buffer + length, sizeof(g_lst_iter_buffer) - length,
		"[%u:%s]", index, (item ? (char const*)item : "NULL"));
}

#ifndef c_lstiter
void test_lstiter(void)	{}
#warning "lstiter() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstiter(t_uint fixture_size)
{
	s_list(any)*	list = (fixture_size == 0 ? NULL : gen_list_fixture());
	g_lst_iter_buffer[0] = '\0';
	c_lstiter(any)(list, gen_iterate_visit);
	if (list)
		c_lstfree(any)(list);
	return (strdup(g_lst_iter_buffer));
}
void	print_test_lstiter(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint fixture_size)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstiter, fixture_size)
	TEST_PRINT(str,	lstiter, "list=(%u items), f=(accumulator)", fixture_size)
	TEST_FREE()
}
void	test_lstiter(void)
{
//	| TEST FUNCTION   | TEST NAME            |TESTFLAG| EXPECTING            | TEST ARGS
	print_test_lstiter("lstiter            ",	FALSE,	GEN_LIST_FIXTURE_STR,  4);
	print_test_lstiter("lstiter (null list)",	FALSE,	"",                    0);
}
#endif



#ifndef c_lstiiter
void test_lstiiter(void)	{}
#warning "lstiiter() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstiiter(t_uint fixture_size)
{
	s_list(any)*	list = (fixture_size == 0 ? NULL : gen_list_fixture());
	g_lst_iter_buffer[0] = '\0';
	c_lstiiter(any)(list, gen_iterate_visit_i);
	if (list)
		c_lstfree(any)(list);
	return (strdup(g_lst_iter_buffer));
}
void	print_test_lstiiter(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint fixture_size)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstiiter, fixture_size)
	TEST_PRINT(str,	lstiiter, "list=(%u items), f=(accumulator)", fixture_size)
	TEST_FREE()
}
void	test_lstiiter(void)
{
//	| TEST FUNCTION    | TEST NAME             |TESTFLAG| EXPECTING                                    | TEST ARGS
	print_test_lstiiter("lstiiter            ",	FALSE,	"[0:Omae][1: wa ][2:mou ][3:shindeiru.]",      4);
	print_test_lstiiter("lstiiter (null list)",	FALSE,	"",                                            0);
}
#endif



//! The "uppercase versions" of the `g_lst_item` strings, for the Map tests
static char* const	g_lst_item_upper[4] =
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
		if (item == (void*)g_lst_item[i])
			return ((void*)g_lst_item_upper[i]);
	}
	return (item);
}
//! Maps every item to the standard test item at the given index, reversed
static void*	gen_map_reverse_i(void* item, t_uint index)
{
	(void)item;
	return (index < 4 ? (void*)g_lst_item[3 - index] : NULL);
}

#ifndef c_lstmap
void test_lstmap(void)	{}
#warning "lstmap() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstmap(t_uint fixture_size)
{
	s_list(any)*	list = (fixture_size == 0 ? NULL : gen_list_fixture());
	s_list(any)*	result = c_lstmap(any)(list, gen_map_upper);
	char*	str = gen_list_consume(result);
	if (list)
		c_lstfree(any)(list); // the operation is pure: the original list is untouched
	return (str);
}
void	print_test_lstmap(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint fixture_size)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstmap, fixture_size)
	TEST_PRINT(str,	lstmap, "list=(%u items), map=(to uppercase)", fixture_size)
	TEST_FREE()
}
void	test_lstmap(void)
{
//	| TEST FUNCTION   | TEST NAME           |TESTFLAG| EXPECTING                            | TEST ARGS
	print_test_lstmap("lstmap             ",	FALSE,	"[OMAE][ WA ][MOU ][SHINDEIRU.]",      4);
	print_test_lstmap("lstmap (null list) ",	FALSE,	"",                                    0);
}
#endif



#ifndef c_lstimap
void test_lstimap(void)	{}
#warning "lstimap() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstimap(t_uint fixture_size)
{
	s_list(any)*	list = (fixture_size == 0 ? NULL : gen_list_fixture());
	s_list(any)*	result = c_lstimap(any)(list, gen_map_reverse_i);
	char*	str = gen_list_consume(result);
	if (list)
		c_lstfree(any)(list);
	return (str);
}
void	print_test_lstimap(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint fixture_size)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstimap, fixture_size)
	TEST_PRINT(str,	lstimap, "list=(%u items), map=(reverse by index)", fixture_size)
	TEST_FREE()
}
void	test_lstimap(void)
{
//	| TEST FUNCTION    | TEST NAME           |TESTFLAG| EXPECTING                            | TEST ARGS
	print_test_lstimap("lstimap            ",	FALSE,	"[shindeiru.][mou ][ wa ][Omae]",      4);
	print_test_lstimap("lstimap (null list)",	FALSE,	"",                                    0);
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

#ifndef c_lstfilter
void test_lstfilter(void)	{}
#warning "lstfilter() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstfilter(t_uint fixture_size)
{
	s_list(any)*	list = (fixture_size == 0 ? NULL : gen_list_fixture());
	s_list(any)*	result = c_lstfilter(any)(list, gen_filter_long);
	char*	str = gen_list_consume(result);
	if (list)
		c_lstfree(any)(list); // the operation is pure: the original list is untouched
	return (str);
}
void	print_test_lstfilter(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint fixture_size)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstfilter, fixture_size)
	TEST_PRINT(str,	lstfilter, "list=(%u items), filter=(length > 4)", fixture_size)
	TEST_FREE()
}
void	test_lstfilter(void)
{
//	| TEST FUNCTION      | TEST NAME             |TESTFLAG| EXPECTING       | TEST ARGS
	print_test_lstfilter("lstfilter            ",	FALSE,	"[shindeiru.]",   4);
	print_test_lstfilter("lstfilter (null list)",	FALSE,	"",               0);
}
#endif



#ifndef c_lstifilter
void test_lstifilter(void)	{}
#warning "lstifilter() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstifilter(t_uint fixture_size)
{
	s_list(any)*	list = (fixture_size == 0 ? NULL : gen_list_fixture());
	s_list(any)*	result = c_lstifilter(any)(list, gen_filter_even_i);
	char*	str = gen_list_consume(result);
	if (list)
		c_lstfree(any)(list);
	return (str);
}
void	print_test_lstifilter(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint fixture_size)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstifilter, fixture_size)
	TEST_PRINT(str,	lstifilter, "list=(%u items), filter=(even indices)", fixture_size)
	TEST_FREE()
}
void	test_lstifilter(void)
{
//	| TEST FUNCTION       | TEST NAME              |TESTFLAG| EXPECTING       | TEST ARGS
	print_test_lstifilter("lstifilter            ",	FALSE,	"[Omae][mou ]",   4);
	print_test_lstifilter("lstifilter (null list)",	FALSE,	"",               0);
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

#ifndef c_lstreduce
void test_lstreduce(void)	{}
#warning "lstreduce() test suite function defined, but the function isn't defined."
#else
static t_uint	c_gen_lstreduce(void)
{
	s_list(any)*	list = gen_list_fixture();
	void*	result = c_lstreduce(any)(list, gen_reduce_lengths);
	c_lstfree(any)(list);
	return ((t_uint)(t_uintptr)result);
}
void	print_test_lstreduce(char const* test_name, t_testflags flags,
		t_uint expecting)
{
	TEST_INIT(uint)
	TEST_PERFORM(gen_lstreduce)
	TEST_PRINT(uint,	lstreduce, "list=(4-item fixture), f=(sum item lengths)")
}
void	test_lstreduce(void)
{
//	| TEST FUNCTION      | TEST NAME           |TESTFLAG| EXPECTING (4 + 4 + 4 + 10)
	print_test_lstreduce("lstreduce          ",	FALSE,	22);
}
#endif



#ifndef c_lstireduce
void test_lstireduce(void)	{}
#warning "lstireduce() test suite function defined, but the function isn't defined."
#else
static t_uint	c_gen_lstireduce(void)
{
	s_list(any)*	list = gen_list_fixture();
	void*	result = c_lstireduce(any)(list, gen_reduce_lengths_i);
	c_lstfree(any)(list);
	return ((t_uint)(t_uintptr)result);
}
void	print_test_lstireduce(char const* test_name, t_testflags flags,
		t_uint expecting)
{
	TEST_INIT(uint)
	TEST_PERFORM(gen_lstireduce)
	TEST_PRINT(uint,	lstireduce, "list=(4-item fixture), f=(sum index-weighted lengths)")
}
void	test_lstireduce(void)
{
//	| TEST FUNCTION       | TEST NAME           |TESTFLAG| EXPECTING (0*4 + 1*4 + 2*4 + 3*10)
	print_test_lstireduce("lstireduce         ",	FALSE,	42);
}
#endif



#ifndef c_lstfold
void test_lstfold(void)	{}
#warning "lstfold() test suite function defined, but the function isn't defined."
#else
static t_uint	c_gen_lstfold(t_uint initial)
{
	s_list(any)*	list = gen_list_fixture();
	void*	result = c_lstfold(any)(list, gen_reduce_lengths, (void*)(t_uintptr)initial);
	c_lstfree(any)(list);
	return ((t_uint)(t_uintptr)result);
}
void	print_test_lstfold(char const* test_name, t_testflags flags,
		t_uint expecting,
		t_uint initial)
{
	TEST_INIT(uint)
	TEST_PERFORM(gen_lstfold, initial)
	TEST_PRINT(uint,	lstfold, "list=(4-item fixture), f=(sum item lengths), initial=%u", initial)
}
void	test_lstfold(void)
{
//	| TEST FUNCTION    | TEST NAME             |TESTFLAG| EXPECTING | TEST ARGS
	print_test_lstfold("lstfold             ",	FALSE,	122,        100);
	print_test_lstfold("lstfold (initial 0) ",	FALSE,	22,         0);
}
#endif



#ifndef c_lstifold
void test_lstifold(void)	{}
#warning "lstifold() test suite function defined, but the function isn't defined."
#else
static t_uint	c_gen_lstifold(t_uint initial)
{
	s_list(any)*	list = gen_list_fixture();
	void*	result = c_lstifold(any)(list, gen_reduce_lengths_i, (void*)(t_uintptr)initial);
	c_lstfree(any)(list);
	return ((t_uint)(t_uintptr)result);
}
void	print_test_lstifold(char const* test_name, t_testflags flags,
		t_uint expecting,
		t_uint initial)
{
	TEST_INIT(uint)
	TEST_PERFORM(gen_lstifold, initial)
	TEST_PRINT(uint,	lstifold, "list=(4-item fixture), f=(sum index-weighted lengths), initial=%u", initial)
}
void	test_lstifold(void)
{
//	| TEST FUNCTION     | TEST NAME             |TESTFLAG| EXPECTING | TEST ARGS
	print_test_lstifold("lstifold            ",	FALSE,	142,        100);
}
#endif



/*============================================================================*\
||                          List: conversion operations                       ||
\*============================================================================*/

#ifndef c_lstfrommem
void test_lstfrommem(void)	{}
#warning "lstfrommem() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstfrommem(t_uint n, t_bool null_ptr)
{
	void*	buffer[4] =
	{
		(void*)g_lst_item[0],
		(void*)g_lst_item[1],
		(void*)g_lst_item[2],
		(void*)g_lst_item[3],
	};
	return (gen_list_consume(c_lstfrommem(any)((null_ptr ? NULL : buffer), n)));
}
void	print_test_lstfrommem(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint n,
		t_bool null_ptr)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstfrommem, n, null_ptr)
	TEST_PRINT(str,	lstfrommem, "ptr=%s, n=%u", (null_ptr ? "NULL" : "(4-item buffer)"), n)
	TEST_FREE()
}
void	test_lstfrommem(void)
{
//	| TEST FUNCTION      | TEST NAME               |TESTFLAG| EXPECTING              | TEST ARGS
	print_test_lstfrommem("lstfrommem           ",	FALSE,	GEN_LIST_FIXTURE_STR,    4, FALSE);
	print_test_lstfrommem("lstfrommem (partial) ",	FALSE,	"[Omae][ wa ]",          2, FALSE);
	print_test_lstfrommem("lstfrommem (n = 0)   ",	FALSE,	"",                      0, FALSE);
	print_test_lstfrommem("lstfrommem (null ptr)",	FALSE,	"",                      4, TRUE);
}
#endif



#ifndef c_lsttomem
void test_lsttomem(void)	{}
#warning "lsttomem() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lsttomem(t_uint fixture_size)
{
	s_list(any)*	list = (fixture_size == 0 ? NULL : gen_list_fixture());
	void**	buffer = c_lsttomem(any)(list);
	char*	result;
	size_t	length = 0;
	if (buffer == NULL)
	{
		if (list)
			c_lstfree(any)(list);
		return (strdup("(null)"));
	}
	for (t_uint i = 0; i < fixture_size; ++i)
		length += 2 + strlen((char const*)buffer[i]);
	result = (char*)malloc(length + 1);
	length = 0;
	for (t_uint i = 0; i < fixture_size; ++i)
		length += sprintf(result + length, "[%s]", (char const*)buffer[i]);
	free(buffer);
	c_lstfree(any)(list); // the buffer must survive the list being freed
	return (result);
}
void	print_test_lsttomem(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint fixture_size)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lsttomem, fixture_size)
	TEST_PRINT(str,	lsttomem, "list=(%u items)", fixture_size)
	TEST_FREE()
}
void	test_lsttomem(void)
{
//	| TEST FUNCTION    | TEST NAME            |TESTFLAG| EXPECTING            | TEST ARGS
	print_test_lsttomem("lsttomem           ",	FALSE,	GEN_LIST_FIXTURE_STR,  4);
	print_test_lsttomem("lsttomem (null)    ",	FALSE,	"(null)",              0);
}
#endif



#ifndef c_lstfromptrarr
void test_lstfromptrarr(void)	{}
#warning "lstfromptrarr() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lstfromptrarr(t_uint n, t_bool null_ptrarr)
{
	void*	buffer[4] =
	{
		(void*)g_lst_item[0],
		(void*)g_lst_item[1],
		(void*)g_lst_item[2],
		(void*)g_lst_item[3],
	};
	void* const*	ptrarr[5] = { NULL, NULL, NULL, NULL, NULL };
	for (t_uint i = 0; i < n && i < 4; ++i)
		ptrarr[i] = &buffer[i]; // the pointer array holds pointers to the items, and is NULL-terminated
	return (gen_list_consume(c_lstfromptrarr(any)(null_ptrarr ? NULL : ptrarr)));
}
void	print_test_lstfromptrarr(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint n,
		t_bool null_ptrarr)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lstfromptrarr, n, null_ptrarr)
	TEST_PRINT(str,	lstfromptrarr, "ptrarr=%s (%u items)", (null_ptrarr ? "NULL" : "(pointer array)"), n)
	TEST_FREE()
}
void	test_lstfromptrarr(void)
{
//	| TEST FUNCTION         | TEST NAME                  |TESTFLAG| EXPECTING              | TEST ARGS
	print_test_lstfromptrarr("lstfromptrarr           ",	FALSE,	GEN_LIST_FIXTURE_STR,    4, FALSE);
	print_test_lstfromptrarr("lstfromptrarr (partial) ",	FALSE,	"[Omae][ wa ]",          2, FALSE);
	print_test_lstfromptrarr("lstfromptrarr (empty)   ",	FALSE,	"",                      0, FALSE);
	print_test_lstfromptrarr("lstfromptrarr (null)    ",	FALSE,	"",                      4, TRUE);
}
#endif



#ifndef c_lsttoptrarr
void test_lsttoptrarr(void)	{}
#warning "lsttoptrarr() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_lsttoptrarr(t_uint fixture_size)
{
	s_list(any)*	list = (fixture_size == 0 ? NULL : gen_list_fixture());
	void**	ptrarr = c_lsttoptrarr(any)(list);
	char	result[256];
	size_t	length = 0;
	if (ptrarr == NULL)
	{
		if (list)
			c_lstfree(any)(list);
		return (strdup("(null)"));
	}
	result[0] = '\0';
	for (t_uint i = 0; ptrarr[i]; ++i)
	{	// each entry is a pointer to an item stored within the list
		void*	item = *(void**)ptrarr[i];
		length += snprintf(result + length, sizeof(result) - length,
			"[%s]", (item ? (char const*)item : "NULL"));
	}
	free(ptrarr);
	c_lstfree(any)(list);
	return (strdup(result));
}
void	print_test_lsttoptrarr(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint fixture_size)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_lsttoptrarr, fixture_size)
	TEST_PRINT(str,	lsttoptrarr, "list=(%u items)", fixture_size)
	TEST_FREE()
}
void	test_lsttoptrarr(void)
{
//	| TEST FUNCTION       | TEST NAME             |TESTFLAG| EXPECTING            | TEST ARGS
	print_test_lsttoptrarr("lsttoptrarr         ",	FALSE,	GEN_LIST_FIXTURE_STR,  4);
	print_test_lsttoptrarr("lsttoptrarr (null)  ",	FALSE,	"(null)",              0);
}
#endif



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_generic_list(void)
{
	print_suite_title("libccc/generic/list");

	print_nonstd();

	test_lstitem();
	test_lstlen();
	test_lstget();
	test_lstset();
	test_lstnew();
	test_lstcreate();
	test_lstdup();
	test_lstsub();
	test_lstcpy();
	test_lstdel();
	test_lstfdel();
	test_lstadd();
	test_lstinsert();
	test_lstwedge();
	test_lstdelat();
	test_lstdelone();
	test_lstdelall();
	test_lstrep();
	test_lstrepfirst();
	test_lstreplast();
	test_lstrev();
	test_lstconcat();
	test_lstappend();
	test_lstprepend();
	test_lstmerge();
	test_lstequ();
	test_lstnequ();
	test_lstcmp();
	test_lstncmp();
	test_lstfind();
	test_lstffind();
	test_lstfindi();
	test_lstffindi();
	test_lstcount();
	test_lstcontains();
	test_lsthas();
	test_lsthasonly();
	test_lstiter();
	test_lstiiter();
	test_lstmap();
	test_lstimap();
	test_lstfilter();
	test_lstifilter();
	test_lstreduce();
	test_lstireduce();
	test_lstfold();
	test_lstifold();
	test_lstfrommem();
	test_lsttomem();
	test_lstfromptrarr();
	test_lsttoptrarr();

	return (OK);
}
