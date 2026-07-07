
#include "libccc/generic/set.c"

#include "test.h"
#include "test_utils.h"



/*============================================================================*\
||                             Testing Utilities                              ||
\*============================================================================*/

/*
**	NOTE: this test suite exercises the default instantiation of the generic
**	set type (ie: `T` is `void*`, and `T_NAME` is `any`), which is included
**	just above. With this instantiation, the `T_EQUALS()` macro is a simple
**	pointer comparison: so, the set matches values by their pointer *identity*
**	(a user instantiation can define `T_EQUALS` to compare by content instead).
**
**	The values used are `char*` strings, so that expected results can be
**	written legibly: every set-returning function is tested by serializing
**	the result set into a string of the form `"{item1, item2}"` — in internal
**	storage order, which is an implementation detail (currently: insertion
**	order, with removals moving the last item into the removed slot). Tests
**	which should not depend on storage order use `Set_Equals()` instead
**	(which is order-independent), or check length/membership properties.
*/

//! The values used to build the test sets
static char* const	g_set_val[4] =
{
	"Omae",
	" wa ",
	"mou ",
	"shindeiru.",
};
//! Has the same content as `g_set_val[0]`, but is a different pointer
static char	g_set_val_twin[] = "Omae";

//! Serializes the given set of `char*` values into a newly allocated string: `"{item1, item2}"`
static
char*	gen_set_tostr(s_set(any) const* set)
{
	size_t	length = 0;
	char*	result;
	char const*	val;
	t_uint	i;

	if (set == NULL)
		return (strdup("(null)"));
	length = 2;
	for (i = 0; i < set->length; ++i)
	{
		val = (char const*)set->items[i];
		length += (val ? strlen(val) : 6) + 2;
	}
	result = (char*)malloc(length + 1);
	if (result == NULL)
		return (NULL);
	strcpy(result, "{");
	for (i = 0; i < set->length; ++i)
	{
		if (i > 0)
			strcat(result, ", ");
		val = (char const*)set->items[i];
		strcat(result, (val ? val : "(null)"));
	}
	strcat(result, "}");
	return (result);
}

//! Serializes the given set, and then frees it
static
char*	gen_set_consume(s_set(any)* set)
{
	char*	result = gen_set_tostr(set);
	if (set != NULL)
		c_setfree(any)(set);
	return (result);
}

//! Creates the canonical (JoJo) test set with `n` items (in order)
static
s_set(any)*	gen_set_fixture(t_uint n)
{
	s_set(any)*	result = c_setnew(any)();
	if (result == NULL)
		return (NULL);
	for (t_uint i = 0; i < n && i < 4; ++i)
	{
		if (c_setadd(any)(result, g_set_val[i]) == NULL)
		{
			c_setfree(any)(result);
			return (NULL);
		}
	}
	return (result);
}



/*============================================================================*\
||                        Set: construction/destruction                       ||
\*============================================================================*/

#ifndef c_setnew
void test_setnew(void)	{}
#warning "setnew() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_setnew(void)
{
	s_set(any)*	set = c_setnew(any)();
	if (set == NULL)
		return (strdup("(null)"));
	if (set->length != 0 || set->items != NULL)
	{
		c_setfree(any)(set);
		return (strdup("(not empty)"));
	}
	return (gen_set_consume(set));
}
void	print_test_setnew(char const* test_name, t_testflags flags,
		char const* expecting)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_setnew)
	TEST_PRINT(str,	setnew, "(no arguments)")
	TEST_FREE()
}
void	test_setnew(void)
{
//	| TEST FUNCTION  | TEST NAME           |TESTFLAG| EXPECTING
	print_test_setnew("setnew             ",	FALSE,	"{}");
}
#endif



#ifndef c_setitem
void test_setitem(void)	{}
#warning "setitem() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_setitem(void)
{
	return (gen_set_consume(c_setitem(any)(g_set_val[0])));
}
void	print_test_setitem(char const* test_name, t_testflags flags,
		char const* expecting)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_setitem)
	TEST_PRINT(str,	setitem, "item=\"%s\"", g_set_val[0])
	TEST_FREE()
}
void	test_setitem(void)
{
//	| TEST FUNCTION   | TEST NAME           |TESTFLAG| EXPECTING
	print_test_setitem("setitem            ",	FALSE,	"{Omae}");
}
#endif



#ifndef c_setcreate
void test_setcreate(void)	{}
#warning "setcreate() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_setcreate(t_uint variant)
{
	s_set(any)*	set = NULL;
	if (variant == 0) // no items
		set = c_setcreate(any)(0);
	else if (variant == 1) // one item
		set = c_setcreate(any)(1, g_set_val[0]);
	else if (variant == 2) // several items
		set = c_setcreate(any)(4, g_set_val[0], g_set_val[1], g_set_val[2], g_set_val[3]);
	else if (variant == 3) // duplicate items among the arguments (should be deduplicated)
		set = c_setcreate(any)(6, g_set_val[0], g_set_val[1], g_set_val[0], g_set_val[2], g_set_val[1], g_set_val[0]);
	else if (variant == 4) // same content but a different pointer: both are kept (pointer identity)
		set = c_setcreate(any)(2, g_set_val[0], g_set_val_twin);
	return (gen_set_consume(set));
}
void	print_test_setcreate(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_setcreate, variant)
	TEST_PRINT(str,	setcreate, "variant=%u", variant)
	TEST_FREE()
}
void	test_setcreate(void)
{
//	| TEST FUNCTION     | TEST NAME                    |TESTFLAG| EXPECTING                          | ARGS
	print_test_setcreate("setcreate (empty)           ",	FALSE,	"{}",                                0);
	print_test_setcreate("setcreate (one item)        ",	FALSE,	"{Omae}",                            1);
	print_test_setcreate("setcreate (several items)   ",	FALSE,	"{Omae,  wa , mou , shindeiru.}",    2);
	print_test_setcreate("setcreate (duplicate args)  ",	FALSE,	"{Omae,  wa , mou }",                3);
	print_test_setcreate("setcreate (twin pointer)    ",	FALSE,	"{Omae, Omae}",                      4);
}
#endif



#ifndef c_setdup
void test_setdup(void)	{}
#warning "setdup() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_setdup(t_uint variant)
{
	s_set(any)*	set;
	s_set(any)*	copy;
	char*	result;

	if (variant == 0) // duplicate an empty set
	{
		set = c_setnew(any)();
		copy = c_setdup(any)(set);
		c_setfree(any)(set);
		return (gen_set_consume(copy));
	}
	else if (variant == 1) // duplicate a filled set
	{
		set = gen_set_fixture(3);
		copy = c_setdup(any)(set);
		c_setfree(any)(set);
		return (gen_set_consume(copy));
	}
	else if (variant == 2) // the copy must be independent from the source
	{
		set = gen_set_fixture(3);
		copy = c_setdup(any)(set);
		c_setrem(any)(copy, g_set_val[0]); // modify the copy...
		result = gen_set_consume(set); // ...and check that the source is unchanged
		c_setfree(any)(copy);
		return (result);
	}
	else if (variant == 3) // NULL set
	{
		copy = c_setdup(any)(NULL);
		return (gen_set_consume(copy));
	}
	return (strdup("(bad variant)"));
}
void	print_test_setdup(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_setdup, variant)
	TEST_PRINT(str,	setdup, "variant=%u", variant)
	TEST_FREE()
}
void	test_setdup(void)
{
//	| TEST FUNCTION  | TEST NAME                    |TESTFLAG| EXPECTING                | ARGS
	print_test_setdup("setdup (empty)              ",	FALSE,	"{}",                      0);
	print_test_setdup("setdup (filled)             ",	FALSE,	"{Omae,  wa , mou }",      1);
	print_test_setdup("setdup (independent copy)   ",	FALSE,	"{Omae,  wa , mou }",      2);
	print_test_setdup("setdup (null)               ",	FALSE,	"(null)",                  3);
}
#endif



/*============================================================================*\
||                            Set: basic operations                           ||
\*============================================================================*/

#ifndef c_setadd
void test_setadd(void)	{}
#warning "setadd() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_setadd(t_uint variant)
{
	s_set(any)*	set;

	if (variant == 0) // add to an empty set
	{
		set = c_setnew(any)();
		c_setadd(any)(set, g_set_val[0]);
		return (gen_set_consume(set));
	}
	else if (variant == 1) // add a new item to a filled set
	{
		set = gen_set_fixture(2);
		c_setadd(any)(set, g_set_val[2]);
		return (gen_set_consume(set));
	}
	else if (variant == 2) // add an item which is already contained: nothing happens
	{
		set = gen_set_fixture(3);
		c_setadd(any)(set, g_set_val[1]);
		return (gen_set_consume(set));
	}
	else if (variant == 3) // adding an existing item returns the pointer to the stored item
	{
		set = gen_set_fixture(3);
		void** added = c_setadd(any)(set, g_set_val[1]);
		void** found = c_setfind(any)(set, g_set_val[1]);
		char* result = strdup(added == found && added != NULL ?
			"(returned the stored item)" : "(returned something else)");
		c_setfree(any)(set);
		return (result);
	}
	else if (variant == 4) // a twin pointer with equal content is a distinct item (pointer identity)
	{
		set = gen_set_fixture(1);
		c_setadd(any)(set, g_set_val_twin);
		return (gen_set_consume(set));
	}
	else if (variant == 5) // NULL set
	{
		void** added = c_setadd(any)(NULL, g_set_val[0]);
		return (strdup(added == NULL ? "(null)" : "(non-null)"));
	}
	return (strdup("(bad variant)"));
}
void	print_test_setadd(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_setadd, variant)
	TEST_PRINT(str,	setadd, "variant=%u", variant)
	TEST_FREE()
}
void	test_setadd(void)
{
//	| TEST FUNCTION  | TEST NAME                    |TESTFLAG| EXPECTING                       | ARGS
	print_test_setadd("setadd (to empty)           ",	FALSE,	"{Omae}",                         0);
	print_test_setadd("setadd (new item)           ",	FALSE,	"{Omae,  wa , mou }",             1);
	print_test_setadd("setadd (already contained)  ",	FALSE,	"{Omae,  wa , mou }",             2);
	print_test_setadd("setadd (returns stored)     ",	FALSE,	"(returned the stored item)",     3);
	print_test_setadd("setadd (twin pointer)       ",	FALSE,	"{Omae, Omae}",                   4);
	print_test_setadd("setadd (null set)           ",	FALSE,	"(null)",                         5);
}
#endif



#ifndef c_setrem
void test_setrem(void)	{}
#warning "setrem() test suite function defined, but the function isn't defined."
#else
static t_uint	g_setrem_del_count = 0;
static void gen_setrem_del(void* item) { (void)item; g_setrem_del_count += 1; }

static char*	c_gen_setrem(t_uint variant)
{
	s_set(any)*	set;

	if (variant == 0) // remove the first item: the last item takes its slot
	{
		set = gen_set_fixture(4);
		c_setrem(any)(set, g_set_val[0]);
		return (gen_set_consume(set));
	}
	else if (variant == 1) // remove the last item
	{
		set = gen_set_fixture(3);
		c_setrem(any)(set, g_set_val[2]);
		return (gen_set_consume(set));
	}
	else if (variant == 2) // remove the only item: the set becomes empty
	{
		set = gen_set_fixture(1);
		c_setrem(any)(set, g_set_val[0]);
		if (set->items != NULL)
		{
			c_setfree(any)(set);
			return (strdup("(items should be NULL)"));
		}
		return (gen_set_consume(set));
	}
	else if (variant == 3) // remove an item which is not contained: nothing happens
	{
		set = gen_set_fixture(2);
		c_setrem(any)(set, g_set_val[3]);
		return (gen_set_consume(set));
	}
	else if (variant == 4) // remove from an empty set: nothing happens
	{
		set = c_setnew(any)();
		c_setrem(any)(set, g_set_val[0]);
		return (gen_set_consume(set));
	}
	else if (variant == 5) // NULL set
	{
		return (strdup(c_setrem(any)(NULL, g_set_val[0]) == NULL ? "(null)" : "(non-null)"));
	}
	else if (variant == 6) // Remove_F: the `del` function is called exactly once, on the removed item
	{
		set = gen_set_fixture(3);
		g_setrem_del_count = 0;
		c_setfrem(any)(set, g_set_val[1], gen_setrem_del);
		c_setfrem(any)(set, g_set_val[3], gen_setrem_del); // absent: `del` is not called
		char buffer[64];
		snprintf(buffer, 64, "del calls: %u, remaining: %u", g_setrem_del_count, set->length);
		c_setfree(any)(set);
		return (strdup(buffer));
	}
	return (strdup("(bad variant)"));
}
void	print_test_setrem(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_setrem, variant)
	TEST_PRINT(str,	setrem, "variant=%u", variant)
	TEST_FREE()
}
void	test_setrem(void)
{
//	| TEST FUNCTION  | TEST NAME                    |TESTFLAG| EXPECTING                          | ARGS
	print_test_setrem("setrem (first item)         ",	FALSE,	"{shindeiru.,  wa , mou }",          0);
	print_test_setrem("setrem (last item)          ",	FALSE,	"{Omae,  wa }",                      1);
	print_test_setrem("setrem (only item)          ",	FALSE,	"{}",                                2);
	print_test_setrem("setrem (absent item)        ",	FALSE,	"{Omae,  wa }",                      3);
	print_test_setrem("setrem (empty set)          ",	FALSE,	"{}",                                4);
	print_test_setrem("setrem (null set)           ",	FALSE,	"(null)",                            5);
	print_test_setrem("setrem_f (del callback)     ",	FALSE,	"del calls: 1, remaining: 2",        6);
}
#endif



#ifndef c_sethas
void test_sethas(void)	{}
#warning "sethas() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_sethas(t_uint variant)
{
	s_set(any)*	set;
	t_bool	result = 2;

	if (variant == 0) // contained item
	{
		set = gen_set_fixture(3);
		result = c_sethas(any)(set, g_set_val[1]);
		c_setfree(any)(set);
	}
	else if (variant == 1) // absent item
	{
		set = gen_set_fixture(3);
		result = c_sethas(any)(set, g_set_val[3]);
		c_setfree(any)(set);
	}
	else if (variant == 2) // twin pointer with equal content: NOT contained (pointer identity)
	{
		set = gen_set_fixture(3);
		result = c_sethas(any)(set, g_set_val_twin);
		c_setfree(any)(set);
	}
	else if (variant == 3) // empty set
	{
		set = c_setnew(any)();
		result = c_sethas(any)(set, g_set_val[0]);
		c_setfree(any)(set);
	}
	else if (variant == 4) // NULL set
	{
		result = c_sethas(any)(NULL, g_set_val[0]);
	}
	return (strdup(result == TRUE ? "TRUE" : result == FALSE ? "FALSE" : "(bad variant)"));
}
void	print_test_sethas(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_sethas, variant)
	TEST_PRINT(str,	sethas, "variant=%u", variant)
	TEST_FREE()
}
void	test_sethas(void)
{
//	| TEST FUNCTION  | TEST NAME                    |TESTFLAG| EXPECTING | ARGS
	print_test_sethas("sethas (contained)          ",	FALSE,	"TRUE",     0);
	print_test_sethas("sethas (absent)             ",	FALSE,	"FALSE",    1);
	print_test_sethas("sethas (twin pointer)       ",	FALSE,	"FALSE",    2);
	print_test_sethas("sethas (empty set)          ",	FALSE,	"FALSE",    3);
	print_test_sethas("sethas (null set)           ",	FALSE,	"FALSE",    4);
}
#endif



#ifndef c_setfind
void test_setfind(void)	{}
#warning "setfind() test suite function defined, but the function isn't defined."
#else
static t_bool gen_setfind_match_mou(void* item) { return (item == (void*)g_set_val[2]); }
static t_bool gen_setfind_match_none(void* item) { (void)item; return (FALSE); }

static char*	c_gen_setfind(t_uint variant)
{
	s_set(any)*	set;
	void**	found = NULL;
	char*	result;

	set = gen_set_fixture(3);
	if (variant == 0) // find a contained item: returns the pointer to the stored item
		found = c_setfind(any)(set, g_set_val[2]);
	else if (variant == 1) // find an absent item: returns NULL (with no error)
		found = c_setfind(any)(set, g_set_val[3]);
	else if (variant == 2) // find with a matching predicate
		found = c_setffind(any)(set, gen_setfind_match_mou);
	else if (variant == 3) // find with a predicate which matches nothing
		found = c_setffind(any)(set, gen_setfind_match_none);
	result = strdup(found == NULL ? "(null)" : (char*)*found);
	c_setfree(any)(set);
	return (result);
}
void	print_test_setfind(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_setfind, variant)
	TEST_PRINT(str,	setfind, "variant=%u", variant)
	TEST_FREE()
}
void	test_setfind(void)
{
//	| TEST FUNCTION   | TEST NAME                    |TESTFLAG| EXPECTING | ARGS
	print_test_setfind("setfind (contained)         ",	FALSE,	"mou ",     0);
	print_test_setfind("setfind (absent)            ",	FALSE,	"(null)",   1);
	print_test_setfind("setffind (predicate match)  ",	FALSE,	"mou ",     2);
	print_test_setfind("setffind (no match)         ",	FALSE,	"(null)",   3);
}
#endif



/*============================================================================*\
||                          Set: comparison operations                        ||
\*============================================================================*/

#ifndef c_setequ
void test_setequ(void)	{}
#warning "setequ() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_setequ(t_uint variant)
{
	s_set(any)*	set1 = NULL;
	s_set(any)*	set2 = NULL;
	t_bool	result = 2;

	if (variant == 0) // same pointer
	{
		set1 = gen_set_fixture(3);
		result = c_setequ(any)(set1, set1);
	}
	else if (variant == 1) // equal content, same insertion order
	{
		set1 = gen_set_fixture(3);
		set2 = gen_set_fixture(3);
		result = c_setequ(any)(set1, set2);
	}
	else if (variant == 2) // equal content, DIFFERENT insertion order (a set is unordered)
	{
		set1 = gen_set_fixture(3);
		set2 = c_setcreate(any)(3, g_set_val[2], g_set_val[0], g_set_val[1]);
		result = c_setequ(any)(set1, set2);
	}
	else if (variant == 3) // different lengths
	{
		set1 = gen_set_fixture(3);
		set2 = gen_set_fixture(2);
		result = c_setequ(any)(set1, set2);
	}
	else if (variant == 4) // same length, different items
	{
		set1 = gen_set_fixture(2);
		set2 = c_setcreate(any)(2, g_set_val[2], g_set_val[3]);
		result = c_setequ(any)(set1, set2);
	}
	else if (variant == 5) // both empty
	{
		set1 = c_setnew(any)();
		set2 = c_setnew(any)();
		result = c_setequ(any)(set1, set2);
	}
	else if (variant == 6) // NULL set
	{
		set1 = gen_set_fixture(1);
		result = c_setequ(any)(set1, NULL);
	}
	if (set1) c_setfree(any)(set1);
	if (set2) c_setfree(any)(set2);
	return (strdup(result == TRUE ? "TRUE" : result == FALSE ? "FALSE" : "(bad variant)"));
}
void	print_test_setequ(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_setequ, variant)
	TEST_PRINT(str,	setequ, "variant=%u", variant)
	TEST_FREE()
}
void	test_setequ(void)
{
//	| TEST FUNCTION  | TEST NAME                    |TESTFLAG| EXPECTING | ARGS
	print_test_setequ("setequ (same pointer)       ",	FALSE,	"TRUE",     0);
	print_test_setequ("setequ (equal, same order)  ",	FALSE,	"TRUE",     1);
	print_test_setequ("setequ (equal, diff order)  ",	FALSE,	"TRUE",     2);
	print_test_setequ("setequ (different lengths)  ",	FALSE,	"FALSE",    3);
	print_test_setequ("setequ (different items)    ",	FALSE,	"FALSE",    4);
	print_test_setequ("setequ (both empty)         ",	FALSE,	"TRUE",     5);
	print_test_setequ("setequ (null)               ",	FALSE,	"FALSE",    6);
}
#endif



#ifndef c_setsubset
void test_setsubset(void)	{}
#warning "setsubset() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_setsubset(t_uint variant)
{
	s_set(any)*	sub = NULL;
	s_set(any)*	super = NULL;
	t_bool	result = 2;

	if (variant == 0) // an empty set is a subset of any set
	{
		sub = c_setnew(any)();
		super = gen_set_fixture(3);
		result = c_setsubset(any)(sub, super);
	}
	else if (variant == 1) // any set is a subset of itself
	{
		sub = gen_set_fixture(3);
		result = c_setsubset(any)(sub, sub);
	}
	else if (variant == 2) // a proper subset
	{
		sub = gen_set_fixture(2);
		super = gen_set_fixture(4);
		result = c_setsubset(any)(sub, super);
	}
	else if (variant == 3) // a superset is not a subset
	{
		sub = gen_set_fixture(4);
		super = gen_set_fixture(2);
		result = c_setsubset(any)(sub, super);
	}
	else if (variant == 4) // partially overlapping sets
	{
		sub = c_setcreate(any)(2, g_set_val[0], g_set_val[3]);
		super = gen_set_fixture(2);
		result = c_setsubset(any)(sub, super);
	}
	else if (variant == 5) // both empty
	{
		sub = c_setnew(any)();
		super = c_setnew(any)();
		result = c_setsubset(any)(sub, super);
	}
	if (super && super != sub) c_setfree(any)(super);
	if (sub) c_setfree(any)(sub);
	return (strdup(result == TRUE ? "TRUE" : result == FALSE ? "FALSE" : "(bad variant)"));
}
void	print_test_setsubset(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_setsubset, variant)
	TEST_PRINT(str,	setsubset, "variant=%u", variant)
	TEST_FREE()
}
void	test_setsubset(void)
{
//	| TEST FUNCTION     | TEST NAME                       |TESTFLAG| EXPECTING | ARGS
	print_test_setsubset("setsubset (empty sub)          ",	FALSE,	"TRUE",     0);
	print_test_setsubset("setsubset (self)               ",	FALSE,	"TRUE",     1);
	print_test_setsubset("setsubset (proper subset)      ",	FALSE,	"TRUE",     2);
	print_test_setsubset("setsubset (superset given)     ",	FALSE,	"FALSE",    3);
	print_test_setsubset("setsubset (partial overlap)    ",	FALSE,	"FALSE",    4);
	print_test_setsubset("setsubset (both empty)         ",	FALSE,	"TRUE",     5);
}
#endif



#ifndef c_setdisjoint
void test_setdisjoint(void)	{}
#warning "setdisjoint() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_setdisjoint(t_uint variant)
{
	s_set(any)*	set1 = NULL;
	s_set(any)*	set2 = NULL;
	t_bool	result = 2;

	if (variant == 0) // fully disjoint sets
	{
		set1 = gen_set_fixture(2);
		set2 = c_setcreate(any)(2, g_set_val[2], g_set_val[3]);
		result = c_setdisjoint(any)(set1, set2);
	}
	else if (variant == 1) // overlapping sets
	{
		set1 = gen_set_fixture(3);
		set2 = c_setcreate(any)(2, g_set_val[2], g_set_val[3]);
		result = c_setdisjoint(any)(set1, set2);
	}
	else if (variant == 2) // an empty set is disjoint with any set
	{
		set1 = c_setnew(any)();
		set2 = gen_set_fixture(3);
		result = c_setdisjoint(any)(set1, set2);
	}
	else if (variant == 3) // a non-empty set is not disjoint with itself
	{
		set1 = gen_set_fixture(2);
		result = c_setdisjoint(any)(set1, set1);
	}
	if (set2 && set2 != set1) c_setfree(any)(set2);
	if (set1) c_setfree(any)(set1);
	return (strdup(result == TRUE ? "TRUE" : result == FALSE ? "FALSE" : "(bad variant)"));
}
void	print_test_setdisjoint(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_setdisjoint, variant)
	TEST_PRINT(str,	setdisjoint, "variant=%u", variant)
	TEST_FREE()
}
void	test_setdisjoint(void)
{
//	| TEST FUNCTION       | TEST NAME                      |TESTFLAG| EXPECTING | ARGS
	print_test_setdisjoint("setdisjoint (disjoint)        ",	FALSE,	"TRUE",     0);
	print_test_setdisjoint("setdisjoint (overlapping)     ",	FALSE,	"FALSE",    1);
	print_test_setdisjoint("setdisjoint (empty set)       ",	FALSE,	"TRUE",     2);
	print_test_setdisjoint("setdisjoint (self, non-empty) ",	FALSE,	"FALSE",    3);
}
#endif



/*============================================================================*\
||                          Set: set-theory operations                        ||
\*============================================================================*/

#if !(defined(c_setunion) && defined(c_setinter) && defined(c_setdiff))
void test_setops(void)	{}
#warning "setops() test suite function defined, but the functions aren't defined."
#else
//! NOTE: results are checked with Set_Equals() against an expected set built
//! with Set_Create(), so these tests do not depend on internal storage order
static char*	c_gen_setops(t_uint variant)
{
	s_set(any)*	set1 = NULL;
	s_set(any)*	set2 = NULL;
	s_set(any)*	expect = NULL;
	s_set(any)*	result = NULL;
	char	buffer[64];

	if (variant == 0) // union of overlapping sets
	{
		set1 = gen_set_fixture(2); // {0, 1}
		set2 = c_setcreate(any)(2, g_set_val[1], g_set_val[2]); // {1, 2}
		expect = gen_set_fixture(3); // {0, 1, 2}
		result = c_setunion(any)(set1, set2);
	}
	else if (variant == 1) // union with an empty set
	{
		set1 = gen_set_fixture(2);
		set2 = c_setnew(any)();
		expect = gen_set_fixture(2);
		result = c_setunion(any)(set1, set2);
	}
	else if (variant == 2) // intersection of overlapping sets
	{
		set1 = gen_set_fixture(3); // {0, 1, 2}
		set2 = c_setcreate(any)(3, g_set_val[1], g_set_val[2], g_set_val[3]); // {1, 2, 3}
		expect = c_setcreate(any)(2, g_set_val[1], g_set_val[2]); // {1, 2}
		result = c_setinter(any)(set1, set2);
	}
	else if (variant == 3) // intersection of disjoint sets is empty
	{
		set1 = gen_set_fixture(2);
		set2 = c_setcreate(any)(2, g_set_val[2], g_set_val[3]);
		expect = c_setnew(any)();
		result = c_setinter(any)(set1, set2);
	}
	else if (variant == 4) // difference of overlapping sets
	{
		set1 = gen_set_fixture(3); // {0, 1, 2}
		set2 = c_setcreate(any)(2, g_set_val[1], g_set_val[3]); // {1, 3}
		expect = c_setcreate(any)(2, g_set_val[0], g_set_val[2]); // {0, 2}
		result = c_setdiff(any)(set1, set2);
	}
	else if (variant == 5) // difference with itself is empty
	{
		set1 = gen_set_fixture(3);
		set2 = gen_set_fixture(3);
		expect = c_setnew(any)();
		result = c_setdiff(any)(set1, set2);
	}
	else if (variant == 6) // difference with an empty set changes nothing
	{
		set1 = gen_set_fixture(3);
		set2 = c_setnew(any)();
		expect = gen_set_fixture(3);
		result = c_setdiff(any)(set1, set2);
	}
	else return (strdup("(bad variant)"));
	snprintf(buffer, 64, "length: %u, equals expected: %s",
		(result ? result->length : 999),
		(c_setequ(any)(result, expect) ? "TRUE" : "FALSE"));
	if (set1) c_setfree(any)(set1);
	if (set2) c_setfree(any)(set2);
	if (expect) c_setfree(any)(expect);
	if (result) c_setfree(any)(result);
	return (strdup(buffer));
}
void	print_test_setops(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_setops, variant)
	TEST_PRINT(str,	setops, "variant=%u", variant)
	TEST_FREE()
}
void	test_setops(void)
{
//	| TEST FUNCTION  | TEST NAME                     |TESTFLAG| EXPECTING                          | ARGS
	print_test_setops("setunion (overlapping)       ",	FALSE,	"length: 3, equals expected: TRUE",  0);
	print_test_setops("setunion (with empty)        ",	FALSE,	"length: 2, equals expected: TRUE",  1);
	print_test_setops("setinter (overlapping)       ",	FALSE,	"length: 2, equals expected: TRUE",  2);
	print_test_setops("setinter (disjoint)          ",	FALSE,	"length: 0, equals expected: TRUE",  3);
	print_test_setops("setdiff (overlapping)        ",	FALSE,	"length: 2, equals expected: TRUE",  4);
	print_test_setops("setdiff (with itself)        ",	FALSE,	"length: 0, equals expected: TRUE",  5);
	print_test_setops("setdiff (with empty)         ",	FALSE,	"length: 3, equals expected: TRUE",  6);
}
#endif



/*============================================================================*\
||                          Set: functional operations                        ||
\*============================================================================*/

#if !(defined(c_setiter) && defined(c_setiiter))
void test_setiter(void)	{}
#warning "setiter() test suite function defined, but the functions aren't defined."
#else
static t_uint	g_setiter_count = 0;
static t_uint	g_setiter_index_sum = 0;
static void gen_setiter_count(void* item) { (void)item; g_setiter_count += 1; }
static void gen_setiter_index(void* item, t_uint index) { (void)item; g_setiter_count += 1; g_setiter_index_sum += index; }

static char*	c_gen_setiter(t_uint variant)
{
	s_set(any)*	set;
	char	buffer[64];

	g_setiter_count = 0;
	g_setiter_index_sum = 0;
	if (variant == 0) // Iterate: the function is called once per item
	{
		set = gen_set_fixture(4);
		c_setiter(any)(set, gen_setiter_count);
		c_setfree(any)(set);
		snprintf(buffer, 64, "calls: %u", g_setiter_count);
	}
	else if (variant == 1) // Iterate on an empty set: the function is never called
	{
		set = c_setnew(any)();
		c_setiter(any)(set, gen_setiter_count);
		c_setfree(any)(set);
		snprintf(buffer, 64, "calls: %u", g_setiter_count);
	}
	else if (variant == 2) // Iterate_I: each item gets a unique index in [0, length)
	{
		set = gen_set_fixture(4);
		c_setiiter(any)(set, gen_setiter_index);
		c_setfree(any)(set);
		snprintf(buffer, 64, "calls: %u, index sum: %u", g_setiter_count, g_setiter_index_sum);
	}
	else return (strdup("(bad variant)"));
	return (strdup(buffer));
}
void	print_test_setiter(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_setiter, variant)
	TEST_PRINT(str,	setiter, "variant=%u", variant)
	TEST_FREE()
}
void	test_setiter(void)
{
//	| TEST FUNCTION   | TEST NAME                   |TESTFLAG| EXPECTING                  | ARGS
	print_test_setiter("setiter (each item)        ",	FALSE,	"calls: 4",                  0);
	print_test_setiter("setiter (empty set)        ",	FALSE,	"calls: 0",                  1);
	print_test_setiter("setiiter (indices)         ",	FALSE,	"calls: 4, index sum: 6",    2);
}
#endif



#if !(defined(c_setmap) && defined(c_setfilt))
void test_setmap(void)	{}
#warning "setmap() test suite function defined, but the functions aren't defined."
#else
static void* gen_setmap_to_first(void* item) { (void)item; return (g_set_val[0]); }
static void* gen_setmap_identity(void* item) { return (item); }
static t_bool gen_setfilt_not_first(void* item) { return (item != (void*)g_set_val[0]); }
static t_bool gen_setfilt_none(void* item) { (void)item; return (FALSE); }

static char*	c_gen_setmap(t_uint variant)
{
	s_set(any)*	set;
	s_set(any)*	result = NULL;

	set = gen_set_fixture(3);
	if (variant == 0) // identity map: same items
		result = c_setmap(any)(set, gen_setmap_identity);
	else if (variant == 1) // map every item to the same value: the result is deduplicated
		result = c_setmap(any)(set, gen_setmap_to_first);
	else if (variant == 2) // filter out one item
		result = c_setfilt(any)(set, gen_setfilt_not_first);
	else if (variant == 3) // filter out everything
		result = c_setfilt(any)(set, gen_setfilt_none);
	c_setfree(any)(set);
	return (gen_set_consume(result));
}
void	print_test_setmap(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_setmap, variant)
	TEST_PRINT(str,	setmap, "variant=%u", variant)
	TEST_FREE()
}
void	test_setmap(void)
{
//	| TEST FUNCTION  | TEST NAME                       |TESTFLAG| EXPECTING              | ARGS
	print_test_setmap("setmap (identity)              ",	FALSE,	"{Omae,  wa , mou }",    0);
	print_test_setmap("setmap (dedupe mapped values)  ",	FALSE,	"{Omae}",                1);
	print_test_setmap("setfilt (remove one)           ",	FALSE,	"{ wa , mou }",          2);
	print_test_setmap("setfilt (remove all)           ",	FALSE,	"{}",                    3);
}
#endif



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_generic_set(void)
{
	print_suite_title("libccc/generic/set");

	print_nonstd();

	test_setnew();
	test_setitem();
	test_setcreate();
	test_setdup();

	test_setadd();
	test_setrem();
	test_sethas();
	test_setfind();

	test_setequ();
	test_setsubset();
	test_setdisjoint();

	test_setops();

	test_setiter();
	test_setmap();

	return (OK);
}
