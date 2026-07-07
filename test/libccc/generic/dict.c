
#include "libccc/generic/dict.c"

#include "test.h"
#include "test_utils.h"



/*============================================================================*\
||                             Testing Utilities                              ||
\*============================================================================*/

/*
**	NOTE: this test suite exercises the default instantiation of the generic
**	dict type (ie: `T` is `void*`, and `T_NAME` is `any`), which is included
**	just above. With this instantiation, the `T_EQUALS()` macro is a simple
**	pointer comparison: so, all of the *value*-based dict functions (Contains,
**	Count, KeyOf, RemoveMatch, etc) match values by their pointer *identity*.
**	*Key* lookups, however, always compare the key strings by *content*
**	(accelerated by comparing the cached SipHash-1-3 key hashes first).
**
**	The values used are `char*` strings, so that expected results can be
**	written legibly: every dict-returning function is tested by serializing
**	the result dict into a string of the form `"[key1:value1][key2:value2]"`
**	(in storage order, which is insertion order), and comparing with `print_test_str`.
*/

//! The keys used to build the test dicts
static char const* const	g_dict_key[4] =
{
	"Omae",
	" wa ",
	"mou ",
	"shindeiru.",
};
//! The values used to build the test dicts (matching values must be the same pointer)
static char* const	g_dict_val[4] =
{
	"0",
	"1",
	"2",
	"3",
};
//! Has the same content as `g_dict_val[0]`, but is a different pointer
static char	g_dict_val_twin[] = "0";

//! Serializes the given dict of `char*` values into a newly allocated string: `"[key1:value1][key2:value2]"`
static
char*	gen_dict_tostr(s_dict(any) const* dict)
{
	size_t	length = 0;
	char*	result;
	char const*	val;
	t_uint	i;

	if (dict == NULL)
		return (strdup(""));
	for (i = 0; i < dict->length; ++i)
	{
		length += 3 + strlen(dict->items[i].key)
			+ (dict->items[i].value ? strlen((char const*)dict->items[i].value) : strlen("NULL"));
	}
	result = (char*)malloc(length + 1);
	if (result == NULL)
		return (NULL);
	length = 0;
	for (i = 0; i < dict->length; ++i)
	{
		val = (dict->items[i].value ? (char const*)dict->items[i].value : "NULL");
		length += sprintf(result + length, "[%s:%s]", dict->items[i].key, val);
	}
	result[length] = '\0';
	return (result);
}

//! Serializes the given dict (like gen_dict_tostr()), and then deletes it
static
char*	gen_dict_consume(s_dict(any)* dict)
{
	char*	result = gen_dict_tostr(dict);
	if (dict)
		c_dictfree(any)(dict);
	return (result);
}

//! Builds the standard 4-pair test dict: `[Omae:0][ wa :1][mou :2][shindeiru.:3]`
static
s_dict(any)*	gen_dict_fixture(void)
{
	return (c_dictcreate(any)(4,
		g_dict_key[0], (void*)g_dict_val[0],
		g_dict_key[1], (void*)g_dict_val[1],
		g_dict_key[2], (void*)g_dict_val[2],
		g_dict_key[3], (void*)g_dict_val[3]));
}

//! The expected serialization of the standard test dict fixture
#define GEN_DICT_FIXTURE_STR	"[Omae:0][ wa :1][mou :2][shindeiru.:3]"



/*============================================================================*\
||                            KeyVal: hashing/pairs                           ||
\*============================================================================*/

#ifndef c_dicthash
void test_dicthash(void)	{}
#warning "dicthash() test suite function defined, but the function isn't defined."
#else
void	print_test_dicthash(char const* test_name, t_testflags flags,
		t_u64 expecting,
		t_char const* key)
{
	TEST_INIT(u64)
	TEST_PERFORM(dicthash(any), key)
	TEST_PRINT(u64,	dicthash, "key=\"%s\"", (key ? key : "NULL"))
}
void	test_dicthash(void)
{
/*
**	NOTE: these expected values are official SipHash-1-3 hashes, generated with
**	the reference implementation (https://github.com/veorq/SipHash), compiled
**	with `cROUNDS=1, dROUNDS=3`, using the canonical reference seed key
**	(ie: the byte sequence `000102030405060708090A0B0C0D0E0F`), which is the
**	default value of the `LIBCONFIG_DICT_HASHSEED_*` macros.
*/
//	| TEST FUNCTION      | TEST NAME                |TESTFLAG| EXPECTING             | TEST ARGS
	print_test_dicthash("dicthash (empty str) ",	FALSE,	0xABAC0158050FC4DCULL,  "");
	print_test_dicthash("dicthash (1 char)    ",	FALSE,	0x1C2697AB786A6237ULL,  "a");
	print_test_dicthash("dicthash (2 chars)   ",	FALSE,	0x0C149F5D943A15EDULL,  "ab");
	print_test_dicthash("dicthash (3 chars)   ",	FALSE,	0x3477D32DD11798E1ULL,  "key");
	print_test_dicthash("dicthash (5 chars)   ",	FALSE,	0xB6BE2B8CD61385B7ULL,  "hello");
	print_test_dicthash("dicthash (22 chars)  ",	FALSE,	0xD39BFF5DFFF13AD7ULL,  "Omae wa mou shindeiru.");
	print_test_dicthash("dicthash (44 chars)  ",	FALSE,	0xC553A4D2CE0EF348ULL,  "the quick brown fox jumps over the lazy dog");
	print_test_dicthash("dicthash (null key)  ",	FALSE,	0xABAC0158050FC4DCULL,  NULL);
}
#endif



#ifndef c_keyval
void test_keyval(void)	{}
#warning "keyval() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_keyval(t_bool null_key)
{
	char	key_buffer[8] = "Omae";
	s_keyval(any)	keyval = c_keyval(any)((null_key ? NULL : key_buffer), (void*)g_dict_val[0]);
	char	result[64];
	if (null_key || keyval.key == NULL)
	{
		if (keyval.key != NULL)
			return (strdup("(expected NULL key)"));
		return (strdup("(null)"));
	}
	key_buffer[0] = 'X'; // the pair must own its own copy of the key string
	if (keyval.hash != c_dicthash(any)(keyval.key))
		return (strdup("(hash mismatch)"));
	snprintf(result, sizeof(result), "[%s:%s]", keyval.key, (char const*)keyval.value);
	c_keyvalfree(any)(&keyval);
	if (keyval.key != NULL || keyval.hash != 0)
		return (strdup("(keyvalfree failed)"));
	return (strdup(result));
}
void	print_test_keyval(char const* test_name, t_testflags flags,
		char const* expecting,
		t_bool null_key)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_keyval, null_key)
	TEST_PRINT(str,	keyval, "key=%s, value=\"0\"", (null_key ? "NULL" : "\"Omae\""))
	TEST_FREE()
}
void	test_keyval(void)
{
//	| TEST FUNCTION    | TEST NAME            |TESTFLAG| EXPECTING   | TEST ARGS
	print_test_keyval("keyval             ",	FALSE,	"[Omae:0]",   FALSE);
	print_test_keyval("keyval (null key)  ",	FALSE,	"(null)",     TRUE);
}
#endif



/*============================================================================*\
||                           Dict: basic operations                           ||
\*============================================================================*/

#ifndef c_dictnew
void test_dictnew(void)	{}
#warning "dictnew() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_dictnew(void)
{
	s_dict(any)*	dict = c_dictnew(any)();
	if (dict == NULL)
		return (strdup("(null)"));
	if (dict->length != 0 || dict->items != NULL)
	{
		c_dictfree(any)(dict);
		return (strdup("(not empty)"));
	}
	return (gen_dict_consume(dict));
}
void	print_test_dictnew(char const* test_name, t_testflags flags,
		char const* expecting)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_dictnew)
	TEST_PRINT(str,	dictnew, "(no arguments)")
	TEST_FREE()
}
void	test_dictnew(void)
{
//	| TEST FUNCTION    | TEST NAME           |TESTFLAG| EXPECTING
	print_test_dictnew("dictnew            ",	FALSE,	"");
}
#endif



#ifndef c_dictcreate
void test_dictcreate(void)	{}
#warning "dictcreate() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_dictcreate(t_uint variant)
{
	s_dict(any)*	dict = NULL;
	if (variant == 0) // no pairs
		dict = c_dictcreate(any)(0);
	else if (variant == 1) // 2 pairs
		dict = c_dictcreate(any)(2,
			g_dict_key[0], (void*)g_dict_val[0],
			g_dict_key[1], (void*)g_dict_val[1]);
	else if (variant == 2) // the standard 4-pair fixture
		dict = gen_dict_fixture();
	else if (variant == 3) // repeated key: only the last value given is kept
		dict = c_dictcreate(any)(3,
			g_dict_key[0], (void*)g_dict_val[0],
			g_dict_key[1], (void*)g_dict_val[1],
			g_dict_key[0], (void*)g_dict_val[2]);
	return (gen_dict_consume(dict));
}
void	print_test_dictcreate(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_dictcreate, variant)
	TEST_PRINT(str,	dictcreate, "(variant %u)", variant)
	TEST_FREE()
}
void	test_dictcreate(void)
{
//	| TEST FUNCTION       | TEST NAME                  |TESTFLAG| EXPECTING                 | TEST ARGS
	print_test_dictcreate("dictcreate (0 pairs)     ",	FALSE,	"",                         0);
	print_test_dictcreate("dictcreate (2 pairs)     ",	FALSE,	"[Omae:0][ wa :1]",         1);
	print_test_dictcreate("dictcreate (4 pairs)     ",	FALSE,	GEN_DICT_FIXTURE_STR,       2);
	print_test_dictcreate("dictcreate (repeated key)",	FALSE,	"[Omae:2][ wa :1]",         3);
}
#endif



#ifndef c_dictdup
void test_dictdup(void)	{}
#warning "dictdup() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_dictdup(void)
{
	s_dict(any)*	original = gen_dict_fixture();
	s_dict(any)*	result = c_dictdup(any)(original);
	c_dictfree(any)(original); // the duplicate (and its key copies) must survive its original being freed
	return (gen_dict_consume(result));
}
void	print_test_dictdup(char const* test_name, t_testflags flags,
		char const* expecting)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_dictdup)
	TEST_PRINT(str,	dictdup, "dict=(4-pair fixture)")
	TEST_FREE()
}
void	test_dictdup(void)
{
//	| TEST FUNCTION    | TEST NAME           |TESTFLAG| EXPECTING
	print_test_dictdup("dictdup            ",	FALSE,	GEN_DICT_FIXTURE_STR);
}
#endif



#ifndef c_dictfdel
void test_dictfdel(void)	{}
#warning "dictfdel() test suite function defined, but the function isn't defined."
#else
static t_uint	g_dictfdel_count = 0;
static void	gen_dictfdel_delete(void* value)
{
	(void)value;
	g_dictfdel_count += 1;
}
static t_uint	c_gen_dictfdel(t_uint n)
{
	s_dict(any)*	dict = c_dictnew(any)();
	char	key[8];
	for (t_uint i = 0; i < n; ++i)
	{
		snprintf(key, sizeof(key), "key%u", i);
		c_dictset(any)(dict, key, (void*)g_dict_val[0]);
	}
	g_dictfdel_count = 0;
	c_dictfdel(any)(&dict, gen_dictfdel_delete);
	if (dict != NULL) // the given pointer must have been set to NULL
		return ((t_uint)-1);
	return (g_dictfdel_count); // amount of times the del() function was called
}
void	print_test_dictfdel(char const* test_name, t_testflags flags,
		t_uint expecting,
		t_uint n)
{
	TEST_INIT(uint)
	TEST_PERFORM(gen_dictfdel, n)
	TEST_PRINT(uint,	dictfdel, "dict=(%u pairs), del=(counting function)", n)
}
void	test_dictfdel(void)
{
//	| TEST FUNCTION     | TEST NAME             |TESTFLAG| EXPECTING | TEST ARGS
	print_test_dictfdel("dictfdel            ",	FALSE,	4,          4);
	print_test_dictfdel("dictfdel (1 pair)   ",	FALSE,	1,          1);
	print_test_dictfdel("dictfdel (empty)    ",	FALSE,	0,          0);
}
#endif



/*============================================================================*\
||                        Dict: access operations                             ||
\*============================================================================*/

#ifndef c_dictget
void test_dictget(void)	{}
#warning "dictget() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_dictget(t_char const* key, t_bool stack_key)
{
	s_dict(any)*	dict = gen_dict_fixture();
	char	key_buffer[16];
	void**	value;
	char*	result;
	if (stack_key && key)
	{	// key lookups must succeed with any string of equal content (not just the same pointer)
		snprintf(key_buffer, sizeof(key_buffer), "%s", key);
		key = key_buffer;
	}
	value = c_dictget(any)(dict, key);
	if (value == NULL)
		result = strdup("(null)");
	else
		result = strdup((char const*)*value);
	c_dictfree(any)(dict);
	return (result);
}
void	print_test_dictget(char const* test_name, t_testflags flags,
		char const* expecting,
		t_char const* key,
		t_bool stack_key)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_dictget, key, stack_key)
	TEST_PRINT(str,	dictget, "dict=(fixture), key=%s%s%s%s", (key ? "\"" : ""), (key ? key : "NULL"), (key ? "\"" : ""), (stack_key ? " (stack copy)" : ""))
	TEST_FREE()
}
void	test_dictget(void)
{
//	| TEST FUNCTION    | TEST NAME               |TESTFLAG| EXPECTING | TEST ARGS
	print_test_dictget("dictget (first)       ",	FALSE,	"0",        "Omae",       FALSE);
	print_test_dictget("dictget (middle)      ",	FALSE,	"2",        "mou ",       FALSE);
	print_test_dictget("dictget (last)        ",	FALSE,	"3",        "shindeiru.", FALSE);
	print_test_dictget("dictget (stack copy)  ",	FALSE,	"1",        " wa ",       TRUE);
	print_test_dictget("dictget (missing key) ",	FALSE,	"(null)",   "yare yare",  FALSE);
	print_test_dictget("dictget (empty key)   ",	FALSE,	"(null)",   "",           FALSE);
	print_test_dictget("dictget (null key)    ",	FALSE,	"(null)",   NULL,         FALSE);
}
#endif



#ifndef c_dictset
void test_dictset(void)	{}
#warning "dictset() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_dictset(t_char const* key, t_uint val_index, t_bool empty_dict)
{
	s_dict(any)*	dict = (empty_dict ? c_dictnew(any)() : gen_dict_fixture());
	s_keyval(any)*	keyval = c_dictset(any)(dict, key, (void*)g_dict_val[val_index]);
	if (key != NULL && keyval == NULL)
	{
		c_dictfree(any)(dict);
		return (strdup("(set returned NULL)"));
	}
	return (gen_dict_consume(dict));
}
void	print_test_dictset(char const* test_name, t_testflags flags,
		char const* expecting,
		t_char const* key,
		t_uint val_index,
		t_bool empty_dict)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_dictset, key, val_index, empty_dict)
	TEST_PRINT(str,	dictset, "dict=(%s), key=%s%s%s, value=\"%s\"", (empty_dict ? "empty" : "fixture"), (key ? "\"" : ""), (key ? key : "NULL"), (key ? "\"" : ""), g_dict_val[val_index])
	TEST_FREE()
}
void	test_dictset(void)
{
//	| TEST FUNCTION    | TEST NAME                 |TESTFLAG| EXPECTING                                     | TEST ARGS
	print_test_dictset("dictset (overwrite first)",	FALSE,	"[Omae:3][ wa :1][mou :2][shindeiru.:3]",       "Omae", 3, FALSE);
	print_test_dictset("dictset (overwrite last) ",	FALSE,	"[Omae:0][ wa :1][mou :2][shindeiru.:0]",       "shindeiru.", 0, FALSE);
	print_test_dictset("dictset (append new)     ",	FALSE,	"[Omae:0][ wa :1][mou :2][shindeiru.:3][NANI:0]", "NANI", 0, FALSE);
	print_test_dictset("dictset (into empty)     ",	FALSE,	"[Omae:0]",                                     "Omae", 0, TRUE);
}
#endif



#ifndef c_dictadd
void test_dictadd(void)	{}
#warning "dictadd() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_dictadd(t_char const* key, t_uint val_index)
{
	s_dict(any)*	dict = gen_dict_fixture();
	s_keyval(any)*	keyval = c_dictadd(any)(dict, key, (void*)g_dict_val[val_index]);
	char*	serialized = gen_dict_consume(dict);
	char*	result;
	size_t	length = strlen(serialized) + 16;
	result = (char*)malloc(length);
	// serialize both the return value (pair added or NULL) and the resulting dict state
	snprintf(result, length, "%s -> %s", (keyval ? "pair" : "NULL"), serialized);
	free(serialized);
	return (result);
}
void	print_test_dictadd(char const* test_name, t_testflags flags,
		char const* expecting,
		t_char const* key,
		t_uint val_index)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_dictadd, key, val_index)
	TEST_PRINT(str,	dictadd, "dict=(fixture), key=\"%s\", value=\"%s\"", key, g_dict_val[val_index])
	TEST_FREE()
}
void	test_dictadd(void)
{
//	| TEST FUNCTION    | TEST NAME               |TESTFLAG| EXPECTING                                              | TEST ARGS
	print_test_dictadd("dictadd (new key)     ",	FALSE,	"pair -> [Omae:0][ wa :1][mou :2][shindeiru.:3][NANI:1]", "NANI", 1);
	print_test_dictadd("dictadd (existing key)",	FALSE,	"NULL -> " GEN_DICT_FIXTURE_STR,                         "Omae", 1);
}
#endif



/*============================================================================*\
||                        Dict: editing operations                            ||
\*============================================================================*/

#ifndef c_dictremove
void test_dictremove(void)	{}
#warning "dictremove() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_dictremove(t_char const* key, t_bool single_pair)
{
	s_dict(any)*	dict;
	if (single_pair)
		dict = c_dictcreate(any)(1, g_dict_key[0], (void*)g_dict_val[0]);
	else
		dict = gen_dict_fixture();
	c_dictremove(any)(dict, key);
	if (single_pair && dict->length == 0 && dict->items != NULL)
	{
		c_dictfree(any)(dict);
		return (strdup("(items not freed)"));
	}
	return (gen_dict_consume(dict));
}
void	print_test_dictremove(char const* test_name, t_testflags flags,
		char const* expecting,
		t_char const* key,
		t_bool single_pair)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_dictremove, key, single_pair)
	TEST_PRINT(str,	dictremove, "dict=(%s), key=\"%s\"", (single_pair ? "1 pair" : "fixture"), key)
	TEST_FREE()
}
void	test_dictremove(void)
{
//	| TEST FUNCTION       | TEST NAME                 |TESTFLAG| EXPECTING                        | TEST ARGS
	print_test_dictremove("dictremove (first)      ",	FALSE,	"[ wa :1][mou :2][shindeiru.:3]",  "Omae",       FALSE);
	print_test_dictremove("dictremove (middle)     ",	FALSE,	"[Omae:0][ wa :1][shindeiru.:3]",  "mou ",       FALSE);
	print_test_dictremove("dictremove (last)       ",	FALSE,	"[Omae:0][ wa :1][mou :2]",        "shindeiru.", FALSE);
	print_test_dictremove("dictremove (missing key)",	FALSE,	GEN_DICT_FIXTURE_STR,              "yare yare",  FALSE);
	print_test_dictremove("dictremove (only pair)  ",	FALSE,	"",                                "Omae",       TRUE);
}
#endif



#ifndef c_dictfremove
void test_dictfremove(void)	{}
#warning "dictfremove() test suite function defined, but the function isn't defined."
#else
static t_uint	g_dictfremove_count = 0;
static void*	g_dictfremove_value = NULL;
static void	gen_dictfremove_delete(void* value)
{
	g_dictfremove_count += 1;
	g_dictfremove_value = value;
}
static char*	c_gen_dictfremove(t_char const* key, char const* expected_value)
{
	s_dict(any)*	dict = gen_dict_fixture();
	g_dictfremove_count = 0;
	g_dictfremove_value = NULL;
	c_dictfremove(any)(dict, key, gen_dictfremove_delete);
	if (expected_value == NULL) // missing key: the del() function must not have been called
	{
		if (g_dictfremove_count != 0)
		{
			c_dictfree(any)(dict);
			return (strdup("(del was called)"));
		}
	}
	else if (g_dictfremove_count != 1 || g_dictfremove_value != (void*)expected_value)
	{
		c_dictfree(any)(dict);
		return (strdup("(bad del call)"));
	}
	return (gen_dict_consume(dict));
}
void	print_test_dictfremove(char const* test_name, t_testflags flags,
		char const* expecting,
		t_char const* key,
		char const* expected_value)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_dictfremove, key, expected_value)
	TEST_PRINT(str,	dictfremove, "dict=(fixture), key=\"%s\", del=(counting function)", key)
	TEST_FREE()
}
void	test_dictfremove(void)
{
//	| TEST FUNCTION        | TEST NAME                  |TESTFLAG| EXPECTING                        | TEST ARGS
	print_test_dictfremove("dictfremove (middle)     ",	FALSE,	"[Omae:0][ wa :1][shindeiru.:3]",  "mou ",      g_dict_val[2]);
	print_test_dictfremove("dictfremove (missing key)",	FALSE,	GEN_DICT_FIXTURE_STR,              "yare yare", NULL);
}
#endif



#ifndef c_dictremmatch
void test_dictremmatch(void)	{}
#warning "dictremmatch() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_dictremmatch(void* value, t_bool duplicate_values)
{
	s_dict(any)*	dict;
	if (duplicate_values) // two pairs share the same value pointer: only the FIRST pair is removed
		dict = c_dictcreate(any)(3,
			g_dict_key[0], (void*)g_dict_val[0],
			g_dict_key[1], (void*)g_dict_val[1],
			g_dict_key[2], (void*)g_dict_val[0]);
	else
		dict = gen_dict_fixture();
	c_dictremmatch(any)(dict, value);
	return (gen_dict_consume(dict));
}
void	print_test_dictremmatch(char const* test_name, t_testflags flags,
		char const* expecting,
		void* value,
		t_bool duplicate_values)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_dictremmatch, value, duplicate_values)
	TEST_PRINT(str,	dictremmatch, "dict=(%s), value=\"%s\"", (duplicate_values ? "3 pairs, dup values" : "fixture"), (value ? (char const*)value : "NULL"))
	TEST_FREE()
}
void	test_dictremmatch(void)
{
//	| TEST FUNCTION         | TEST NAME                     |TESTFLAG| EXPECTING                          | TEST ARGS
	print_test_dictremmatch("dictremmatch (present)      ",	FALSE,	"[Omae:0][ wa :1][shindeiru.:3]",    (void*)g_dict_val[2], FALSE);
	print_test_dictremmatch("dictremmatch (first only)   ",	FALSE,	"[ wa :1][mou :0]",                  (void*)g_dict_val[0], TRUE);
	print_test_dictremmatch("dictremmatch (twin pointer) ",	FALSE,	GEN_DICT_FIXTURE_STR,                (void*)g_dict_val_twin, FALSE);
}
#endif



#ifndef c_dictremmatches
void test_dictremmatches(void)	{}
#warning "dictremmatches() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_dictremmatches(void* value, t_uint variant)
{
	s_dict(any)*	dict;
	if (variant == 1) // two pairs share the same value pointer: BOTH are removed
		dict = c_dictcreate(any)(3,
			g_dict_key[0], (void*)g_dict_val[0],
			g_dict_key[1], (void*)g_dict_val[1],
			g_dict_key[2], (void*)g_dict_val[0]);
	else if (variant == 2) // every pair has the same value: dict becomes empty
		dict = c_dictcreate(any)(2,
			g_dict_key[0], (void*)g_dict_val[0],
			g_dict_key[1], (void*)g_dict_val[0]);
	else
		dict = gen_dict_fixture();
	c_dictremmatches(any)(dict, value);
	if (variant == 2 && dict->length == 0 && dict->items != NULL)
	{
		c_dictfree(any)(dict);
		return (strdup("(items not freed)"));
	}
	return (gen_dict_consume(dict));
}
void	print_test_dictremmatches(char const* test_name, t_testflags flags,
		char const* expecting,
		void* value,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_dictremmatches, value, variant)
	TEST_PRINT(str,	dictremmatches, "dict=(variant %u), value=\"%s\"", variant, (value ? (char const*)value : "NULL"))
	TEST_FREE()
}
void	test_dictremmatches(void)
{
//	| TEST FUNCTION           | TEST NAME                      |TESTFLAG| EXPECTING            | TEST ARGS
	print_test_dictremmatches("dictremmatches (one match)  ",	FALSE,	"[Omae:0][ wa :1][shindeiru.:3]", (void*)g_dict_val[2], 0);
	print_test_dictremmatches("dictremmatches (two matches)",	FALSE,	"[ wa :1]",            (void*)g_dict_val[0], 1);
	print_test_dictremmatches("dictremmatches (all match)  ",	FALSE,	"",                    (void*)g_dict_val[0], 2);
	print_test_dictremmatches("dictremmatches (no match)   ",	FALSE,	GEN_DICT_FIXTURE_STR,  (void*)g_dict_val_twin, 0);
}
#endif



#ifndef c_dictfremmatches
void test_dictfremmatches(void)	{}
#warning "dictfremmatches() test suite function defined, but the function isn't defined."
#else
static t_uint	g_dictfremmatches_count = 0;
static void	gen_dictfremmatches_delete(void* value)
{
	(void)value;
	g_dictfremmatches_count += 1;
}
static t_uint	c_gen_dictfremmatches(void)
{	// two pairs share the same value pointer: del() must be called exactly twice
	s_dict(any)*	dict = c_dictcreate(any)(3,
		g_dict_key[0], (void*)g_dict_val[0],
		g_dict_key[1], (void*)g_dict_val[1],
		g_dict_key[2], (void*)g_dict_val[0]);
	g_dictfremmatches_count = 0;
	c_dictfremmatches(any)(dict, (void*)g_dict_val[0], gen_dictfremmatches_delete);
	c_dictfree(any)(dict);
	return (g_dictfremmatches_count);
}
void	print_test_dictfremmatches(char const* test_name, t_testflags flags,
		t_uint expecting)
{
	TEST_INIT(uint)
	TEST_PERFORM(gen_dictfremmatches)
	TEST_PRINT(uint,	dictfremmatches, "dict=(3 pairs, 2 matching), del=(counting function)")
}
void	test_dictfremmatches(void)
{
//	| TEST FUNCTION            | TEST NAME              |TESTFLAG| EXPECTING
	print_test_dictfremmatches("dictfremmatches       ",	FALSE,	2);
}
#endif



#ifndef c_dictsub
void test_dictsub(void)	{}
#warning "dictsub() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_dictsub(t_uint variant)
{
	s_dict(any)*	dict = gen_dict_fixture();
	s_dict(any)*	result = NULL;
	if (variant == 0) // subset of keys (in a different order than insertion)
	{
		t_char const*	keys[3] = { "shindeiru.", "Omae", NULL };
		result = c_dictsub(any)(dict, keys);
	}
	else if (variant == 1) // some keys are missing from the dict: they are ignored
	{
		t_char const*	keys[4] = { "yare yare", " wa ", "NANI", NULL };
		result = c_dictsub(any)(dict, keys);
	}
	else if (variant == 2) // empty keys list
	{
		t_char const*	keys[1] = { NULL };
		result = c_dictsub(any)(dict, keys);
	}
	c_dictfree(any)(dict); // the sub-dict (and its key copies) must survive its source being freed
	return (gen_dict_consume(result));
}
void	print_test_dictsub(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_dictsub, variant)
	TEST_PRINT(str,	dictsub, "dict=(fixture), keys=(variant %u)", variant)
	TEST_FREE()
}
void	test_dictsub(void)
{
//	| TEST FUNCTION    | TEST NAME               |TESTFLAG| EXPECTING                  | TEST ARGS
	print_test_dictsub("dictsub (subset)      ",	FALSE,	"[shindeiru.:3][Omae:0]",    0);
	print_test_dictsub("dictsub (missing keys)",	FALSE,	"[ wa :1]",                  1);
	print_test_dictsub("dictsub (empty keys)  ",	FALSE,	"",                          2);
}
#endif



/*============================================================================*\
||                        Dict: checking operations                           ||
\*============================================================================*/

#ifndef c_dictfind
void test_dictfind(void)	{}
#warning "dictfind() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_dictfind(t_char const* key)
{
	s_dict(any)*	dict = gen_dict_fixture();
	s_keyval(any)*	keyval = c_dictfind(any)(dict, key);
	char	result[64];
	if (keyval == NULL)
	{
		c_dictfree(any)(dict);
		return (strdup("(null)"));
	}
	if (keyval->hash != c_dicthash(any)(keyval->key))
	{
		c_dictfree(any)(dict);
		return (strdup("(hash mismatch)"));
	}
	snprintf(result, sizeof(result), "[%s:%s]", keyval->key, (char const*)keyval->value);
	c_dictfree(any)(dict);
	return (strdup(result));
}
void	print_test_dictfind(char const* test_name, t_testflags flags,
		char const* expecting,
		t_char const* key)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_dictfind, key)
	TEST_PRINT(str,	dictfind, "dict=(fixture), key=%s%s%s", (key ? "\"" : ""), (key ? key : "NULL"), (key ? "\"" : ""))
	TEST_FREE()
}
void	test_dictfind(void)
{
//	| TEST FUNCTION     | TEST NAME              |TESTFLAG| EXPECTING        | TEST ARGS
	print_test_dictfind("dictfind (first)     ",	FALSE,	"[Omae:0]",        "Omae");
	print_test_dictfind("dictfind (last)      ",	FALSE,	"[shindeiru.:3]",  "shindeiru.");
	print_test_dictfind("dictfind (missing)   ",	FALSE,	"(null)",          "yare yare");
	print_test_dictfind("dictfind (null key)  ",	FALSE,	"(null)",          NULL);
}
#endif



#ifndef c_dictffind
void test_dictffind(void)	{}
#warning "dictffind() test suite function defined, but the function isn't defined."
#else
static t_bool	gen_dictffind_match_key_space(s_keyval(any) keyval)
{
	return (keyval.key[0] == ' '); // matches the " wa " key
}
static t_bool	gen_dictffind_match_none(s_keyval(any) keyval)
{
	(void)keyval;
	return (FALSE);
}
static char*	c_gen_dictffind(t_bool match_none)
{
	s_dict(any)*	dict = gen_dict_fixture();
	s_keyval(any)*	keyval = c_dictffind(any)(dict,
		(match_none ? gen_dictffind_match_none : gen_dictffind_match_key_space));
	char	result[64];
	if (keyval == NULL)
	{
		c_dictfree(any)(dict);
		return (strdup("(null)"));
	}
	snprintf(result, sizeof(result), "[%s:%s]", keyval->key, (char const*)keyval->value);
	c_dictfree(any)(dict);
	return (strdup(result));
}
void	print_test_dictffind(char const* test_name, t_testflags flags,
		char const* expecting,
		t_bool match_none)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_dictffind, match_none)
	TEST_PRINT(str,	dictffind, "dict=(fixture), match=(%s)", (match_none ? "matches nothing" : "key starts with space"))
	TEST_FREE()
}
void	test_dictffind(void)
{
//	| TEST FUNCTION      | TEST NAME             |TESTFLAG| EXPECTING   | TEST ARGS
	print_test_dictffind("dictffind           ",	FALSE,	"[ wa :1]",   FALSE);
	print_test_dictffind("dictffind (no match)",	FALSE,	"(null)",     TRUE);
}
#endif



#ifndef c_dicthaskey
void test_dicthaskey(void)	{}
#warning "dicthaskey() test suite function defined, but the function isn't defined."
#else
static t_bool	c_gen_dicthaskey(t_char const* key, t_bool stack_key)
{
	s_dict(any)*	dict = gen_dict_fixture();
	char	key_buffer[16];
	t_bool	result;
	if (stack_key && key)
	{	// key checks must succeed with any string of equal content (not just the same pointer)
		snprintf(key_buffer, sizeof(key_buffer), "%s", key);
		key = key_buffer;
	}
	result = c_dicthaskey(any)(dict, key);
	c_dictfree(any)(dict);
	return (result);
}
void	print_test_dicthaskey(char const* test_name, t_testflags flags,
		t_bool expecting,
		t_char const* key,
		t_bool stack_key)
{
	TEST_INIT(bool)
	TEST_PERFORM(gen_dicthaskey, key, stack_key)
	TEST_PRINT(bool,	dicthaskey, "dict=(fixture), key=%s%s%s%s", (key ? "\"" : ""), (key ? key : "NULL"), (key ? "\"" : ""), (stack_key ? " (stack copy)" : ""))
}
void	test_dicthaskey(void)
{
//	| TEST FUNCTION       | TEST NAME                 |TESTFLAG| EXPECTING | TEST ARGS
	print_test_dicthaskey("dicthaskey (present)    ",	FALSE,	TRUE,       "mou ",       FALSE);
	print_test_dicthaskey("dicthaskey (stack copy) ",	FALSE,	TRUE,       "shindeiru.", TRUE);
	print_test_dicthaskey("dicthaskey (missing)    ",	FALSE,	FALSE,      "yare yare",  FALSE);
	print_test_dicthaskey("dicthaskey (null key)   ",	FALSE,	FALSE,      NULL,         FALSE);
}
#endif



#ifndef c_dictkeyof
void test_dictkeyof(void)	{}
#warning "dictkeyof() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_dictkeyof(void* value)
{
	s_dict(any)*	dict = gen_dict_fixture();
	t_char const*	key = c_dictkeyof(any)(dict, value);
	char*	result = strdup(key ? key : "(null)");
	c_dictfree(any)(dict);
	return (result);
}
void	print_test_dictkeyof(char const* test_name, t_testflags flags,
		char const* expecting,
		void* value)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_dictkeyof, value)
	TEST_PRINT(str,	dictkeyof, "dict=(fixture), value=\"%s\"", (value ? (char const*)value : "NULL"))
	TEST_FREE()
}
void	test_dictkeyof(void)
{
//	| TEST FUNCTION      | TEST NAME                  |TESTFLAG| EXPECTING     | TEST ARGS
	print_test_dictkeyof("dictkeyof (first value) ",	FALSE,	"Omae",         (void*)g_dict_val[0]);
	print_test_dictkeyof("dictkeyof (last value)  ",	FALSE,	"shindeiru.",   (void*)g_dict_val[3]);
	print_test_dictkeyof("dictkeyof (twin pointer)",	FALSE,	"(null)",       (void*)g_dict_val_twin);
}
#endif



#ifndef c_dictcount
void test_dictcount(void)	{}
#warning "dictcount() test suite function defined, but the function isn't defined."
#else
static t_uint	c_gen_dictcount(void* value, t_bool duplicate_values)
{
	s_dict(any)*	dict;
	t_uint	result;
	if (duplicate_values) // three pairs, two of which share the same value pointer
		dict = c_dictcreate(any)(3,
			g_dict_key[0], (void*)g_dict_val[0],
			g_dict_key[1], (void*)g_dict_val[1],
			g_dict_key[2], (void*)g_dict_val[0]);
	else
		dict = gen_dict_fixture();
	result = c_dictcount(any)(dict, value);
	c_dictfree(any)(dict);
	return (result);
}
void	print_test_dictcount(char const* test_name, t_testflags flags,
		t_uint expecting,
		void* value,
		t_bool duplicate_values)
{
	TEST_INIT(uint)
	TEST_PERFORM(gen_dictcount, value, duplicate_values)
	TEST_PRINT(uint,	dictcount, "dict=(%s), value=\"%s\"", (duplicate_values ? "3 pairs, dup values" : "fixture"), (value ? (char const*)value : "NULL"))
}
void	test_dictcount(void)
{
//	| TEST FUNCTION      | TEST NAME                  |TESTFLAG| EXPECTING | TEST ARGS
	print_test_dictcount("dictcount (one match)   ",	FALSE,	1,          (void*)g_dict_val[1], FALSE);
	print_test_dictcount("dictcount (two matches) ",	FALSE,	2,          (void*)g_dict_val[0], TRUE);
	print_test_dictcount("dictcount (twin pointer)",	FALSE,	0,          (void*)g_dict_val_twin, FALSE);
}
#endif



#ifndef c_dictcontains
void test_dictcontains(void)	{}
#warning "dictcontains() test suite function defined, but the function isn't defined."
#else
static t_bool	c_gen_dictcontains(void* value)
{
	s_dict(any)*	dict = gen_dict_fixture();
	t_bool	result = c_dictcontains(any)(dict, value);
	c_dictfree(any)(dict);
	return (result);
}
void	print_test_dictcontains(char const* test_name, t_testflags flags,
		t_bool expecting,
		void* value)
{
	TEST_INIT(bool)
	TEST_PERFORM(gen_dictcontains, value)
	TEST_PRINT(bool,	dictcontains, "dict=(fixture), value=\"%s\"", (value ? (char const*)value : "NULL"))
}
void	test_dictcontains(void)
{
//	| TEST FUNCTION         | TEST NAME                     |TESTFLAG| EXPECTING | TEST ARGS
	print_test_dictcontains("dictcontains (present)     ",	FALSE,	TRUE,       (void*)g_dict_val[2]);
	print_test_dictcontains("dictcontains (twin pointer)",	FALSE,	FALSE,      (void*)g_dict_val_twin);
}
#endif



#ifndef c_dicthas
void test_dicthas(void)	{}
#warning "dicthas() test suite function defined, but the function isn't defined."
#else
static t_bool	c_gen_dicthas(t_uint variant, t_bool has_only)
{
	s_dict(any)*	dict = gen_dict_fixture();
	s_dict(any)*	target = NULL;
	t_bool	result;
	if (variant == 0) // target holds every key of the fixture (and more)
		target = c_dictcreate(any)(5,
			g_dict_key[0], (void*)g_dict_val[0],
			g_dict_key[1], (void*)g_dict_val[1],
			g_dict_key[2], (void*)g_dict_val[2],
			g_dict_key[3], (void*)g_dict_val[3],
			"NANI", (void*)g_dict_val[0]);
	else if (variant == 1) // target holds only some keys of the fixture
		target = c_dictcreate(any)(2,
			g_dict_key[1], (void*)g_dict_val[0],
			"NANI", (void*)g_dict_val[0]);
	else if (variant == 2) // target holds no key of the fixture
		target = c_dictcreate(any)(1,
			"NANI", (void*)g_dict_val[0]);
	result = (has_only
		? c_dicthasonly(any)(dict, target)
		: c_dicthas(any)(dict, target));
	c_dictfree(any)(target);
	c_dictfree(any)(dict);
	return (result);
}
void	print_test_dicthas(char const* test_name, t_testflags flags,
		t_bool expecting,
		t_uint variant,
		t_bool has_only)
{
	TEST_INIT(bool)
	TEST_PERFORM(gen_dicthas, variant, has_only)
	TEST_PRINT(bool,	dicthas, "dict=(fixture), target=(variant %u)%s", variant, (has_only ? " [HasOnly]" : ""))
}
void	test_dicthas(void)
{
//	| TEST FUNCTION    | TEST NAME                |TESTFLAG| EXPECTING | TEST ARGS
	print_test_dicthas("dicthas (all keys)     ",	FALSE,	TRUE,       0, FALSE);
	print_test_dicthas("dicthas (some keys)    ",	FALSE,	TRUE,       1, FALSE);
	print_test_dicthas("dicthas (no keys)      ",	FALSE,	FALSE,      2, FALSE);
}
void	test_dicthasonly(void)
{
//	| TEST FUNCTION    | TEST NAME                 |TESTFLAG| EXPECTING | TEST ARGS
	print_test_dicthas("dicthasonly (all keys) ",	FALSE,	TRUE,       0, TRUE);
	print_test_dicthas("dicthasonly (some keys)",	FALSE,	FALSE,      1, TRUE);
	print_test_dicthas("dicthasonly (no keys)  ",	FALSE,	FALSE,      2, TRUE);
}
#endif



#ifndef c_dictequ
void test_dictequ(void)	{}
#warning "dictequ() test suite function defined, but the function isn't defined."
#else
static t_bool	c_gen_dictequ(t_uint variant)
{
	s_dict(any)*	dict1 = gen_dict_fixture();
	s_dict(any)*	dict2 = NULL;
	t_bool	result;
	if (variant == 0) // same pairs, same order
		dict2 = gen_dict_fixture();
	else if (variant == 1) // same pairs, DIFFERENT insertion order: still equal
		dict2 = c_dictcreate(any)(4,
			g_dict_key[3], (void*)g_dict_val[3],
			g_dict_key[1], (void*)g_dict_val[1],
			g_dict_key[0], (void*)g_dict_val[0],
			g_dict_key[2], (void*)g_dict_val[2]);
	else if (variant == 2) // one differing value
		dict2 = c_dictcreate(any)(4,
			g_dict_key[0], (void*)g_dict_val[0],
			g_dict_key[1], (void*)g_dict_val[1],
			g_dict_key[2], (void*)g_dict_val[2],
			g_dict_key[3], (void*)g_dict_val[0]);
	else if (variant == 3) // one differing key
		dict2 = c_dictcreate(any)(4,
			g_dict_key[0], (void*)g_dict_val[0],
			g_dict_key[1], (void*)g_dict_val[1],
			g_dict_key[2], (void*)g_dict_val[2],
			"NANI", (void*)g_dict_val[3]);
	else if (variant == 4) // differing lengths
		dict2 = c_dictcreate(any)(2,
			g_dict_key[0], (void*)g_dict_val[0],
			g_dict_key[1], (void*)g_dict_val[1]);
	else if (variant == 5) // compare with itself (same pointer)
	{
		result = c_dictequ(any)(dict1, dict1);
		c_dictfree(any)(dict1);
		return (result);
	}
	result = c_dictequ(any)(dict1, dict2);
	c_dictfree(any)(dict2);
	c_dictfree(any)(dict1);
	return (result);
}
void	print_test_dictequ(char const* test_name, t_testflags flags,
		t_bool expecting,
		t_uint variant)
{
	TEST_INIT(bool)
	TEST_PERFORM(gen_dictequ, variant)
	TEST_PRINT(bool,	dictequ, "dict1=(fixture), dict2=(variant %u)", variant)
}
void	test_dictequ(void)
{
//	| TEST FUNCTION    | TEST NAME                    |TESTFLAG| EXPECTING | TEST ARGS
	print_test_dictequ("dictequ (identical)        ",	FALSE,	TRUE,       0);
	print_test_dictequ("dictequ (different order)  ",	FALSE,	TRUE,       1);
	print_test_dictequ("dictequ (differing value)  ",	FALSE,	FALSE,      2);
	print_test_dictequ("dictequ (differing key)    ",	FALSE,	FALSE,      3);
	print_test_dictequ("dictequ (differing length) ",	FALSE,	FALSE,      4);
	print_test_dictequ("dictequ (same pointer)     ",	FALSE,	TRUE,       5);
}
#endif



/*============================================================================*\
||                       Dict: functional operations                          ||
\*============================================================================*/

#ifndef c_dictiter
void test_dictiter(void)	{}
#warning "dictiter() test suite function defined, but the function isn't defined."
#else
static char	g_dictiter_accumulator[128];
static void	gen_dictiter_visit(s_keyval(any) keyval)
{
	size_t	length = strlen(g_dictiter_accumulator);
	snprintf(g_dictiter_accumulator + length, sizeof(g_dictiter_accumulator) - length,
		"[%s:%s]", keyval.key, (char const*)keyval.value);
}
static char*	c_gen_dictiter(void)
{
	s_dict(any)*	dict = gen_dict_fixture();
	g_dictiter_accumulator[0] = '\0';
	c_dictiter(any)(dict, gen_dictiter_visit);
	c_dictfree(any)(dict);
	return (strdup(g_dictiter_accumulator));
}
void	print_test_dictiter(char const* test_name, t_testflags flags,
		char const* expecting)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_dictiter)
	TEST_PRINT(str,	dictiter, "dict=(fixture), f=(accumulates pairs)")
	TEST_FREE()
}
void	test_dictiter(void)
{
//	| TEST FUNCTION     | TEST NAME       |TESTFLAG| EXPECTING
	print_test_dictiter("dictiter       ",	FALSE,	GEN_DICT_FIXTURE_STR);
}
#endif



#ifndef c_dictiiter
void test_dictiiter(void)	{}
#warning "dictiiter() test suite function defined, but the function isn't defined."
#else
static char	g_dictiiter_accumulator[128];
static void	gen_dictiiter_visit(s_keyval(any) keyval, t_uint index)
{
	size_t	length = strlen(g_dictiiter_accumulator);
	snprintf(g_dictiiter_accumulator + length, sizeof(g_dictiiter_accumulator) - length,
		"[%u:%s:%s]", index, keyval.key, (char const*)keyval.value);
}
static char*	c_gen_dictiiter(void)
{
	s_dict(any)*	dict = gen_dict_fixture();
	g_dictiiter_accumulator[0] = '\0';
	c_dictiiter(any)(dict, gen_dictiiter_visit);
	c_dictfree(any)(dict);
	return (strdup(g_dictiiter_accumulator));
}
void	print_test_dictiiter(char const* test_name, t_testflags flags,
		char const* expecting)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_dictiiter)
	TEST_PRINT(str,	dictiiter, "dict=(fixture), f=(accumulates pairs with indices)")
	TEST_FREE()
}
void	test_dictiiter(void)
{
//	| TEST FUNCTION      | TEST NAME        |TESTFLAG| EXPECTING
	print_test_dictiiter("dictiiter       ",	FALSE,	"[0:Omae:0][1: wa :1][2:mou :2][3:shindeiru.:3]");
}
#endif



#ifndef c_dictmap
void test_dictmap(void)	{}
#warning "dictmap() test suite function defined, but the function isn't defined."
#else
static void*	gen_dictmap_swap(t_char const* key, void* value)
{	// maps values "0"<->"3" and "1"<->"2" (reverses the value assignment)
	(void)key;
	for (t_uint i = 0; i < 4; ++i)
	{
		if (value == (void*)g_dict_val[i])
			return ((void*)g_dict_val[3 - i]);
	}
	return (value);
}
static char*	c_gen_dictmap(void)
{
	s_dict(any)*	dict = gen_dict_fixture();
	s_dict(any)*	result = c_dictmap(any)(dict, gen_dictmap_swap);
	c_dictfree(any)(dict); // the mapped dict (and its key copies) must survive its source being freed
	return (gen_dict_consume(result));
}
void	print_test_dictmap(char const* test_name, t_testflags flags,
		char const* expecting)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_dictmap)
	TEST_PRINT(str,	dictmap, "dict=(fixture), map=(reverses values)")
	TEST_FREE()
}
void	test_dictmap(void)
{
//	| TEST FUNCTION    | TEST NAME      |TESTFLAG| EXPECTING
	print_test_dictmap("dictmap       ",	FALSE,	"[Omae:3][ wa :2][mou :1][shindeiru.:0]");
}
#endif



#ifndef c_dictfilter
void test_dictfilter(void)	{}
#warning "dictfilter() test suite function defined, but the function isn't defined."
#else
static t_bool	gen_dictfilter_key_has_4_chars(s_keyval(any) keyval)
{
	return (strlen(keyval.key) == 4); // matches the "Omae", " wa " and "mou " keys
}
static t_bool	gen_dictfilter_none(s_keyval(any) keyval)
{
	(void)keyval;
	return (FALSE);
}
static char*	c_gen_dictfilter(t_bool filter_none)
{
	s_dict(any)*	dict = gen_dict_fixture();
	s_dict(any)*	result = c_dictfilter(any)(dict,
		(filter_none ? gen_dictfilter_none : gen_dictfilter_key_has_4_chars));
	c_dictfree(any)(dict); // the filtered dict (and its key copies) must survive its source being freed
	return (gen_dict_consume(result));
}
void	print_test_dictfilter(char const* test_name, t_testflags flags,
		char const* expecting,
		t_bool filter_none)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_dictfilter, filter_none)
	TEST_PRINT(str,	dictfilter, "dict=(fixture), filter=(%s)", (filter_none ? "matches nothing" : "keys with 4 chars"))
	TEST_FREE()
}
void	test_dictfilter(void)
{
//	| TEST FUNCTION       | TEST NAME               |TESTFLAG| EXPECTING                   | TEST ARGS
	print_test_dictfilter("dictfilter            ",	FALSE,	"[Omae:0][ wa :1][mou :2]",   FALSE);
	print_test_dictfilter("dictfilter (no match) ",	FALSE,	"",                           TRUE);
}
#endif



#ifndef c_dictreduce
void test_dictreduce(void)	{}
#warning "dictreduce() test suite function defined, but the function isn't defined."
#else
static void*	gen_dictreduce_sum_key_lengths(s_keyval(any) keyval, void* acc)
{	// accumulates the total length of every key string (in a uintptr accumulator)
	return ((void*)((t_uintptr)acc + strlen(keyval.key)));
}
static t_uint	c_gen_dictreduce(t_bool fold, t_uint initial)
{
	s_dict(any)*	dict = gen_dict_fixture();
	void*	result;
	if (fold)
		result = c_dictfold(any)(dict, gen_dictreduce_sum_key_lengths, (void*)(t_uintptr)initial);
	else
		result = c_dictreduce(any)(dict, gen_dictreduce_sum_key_lengths);
	c_dictfree(any)(dict);
	return ((t_uint)(t_uintptr)result);
}
void	print_test_dictreduce(char const* test_name, t_testflags flags,
		t_uint expecting,
		t_bool fold,
		t_uint initial)
{
	TEST_INIT(uint)
	TEST_PERFORM(gen_dictreduce, fold, initial)
	TEST_PRINT(uint,	dictreduce, "dict=(fixture), f=(sums key lengths)%s", (fold ? ", with initial value" : ""))
}
void	test_dictreduce(void)
{
	// the fixture key lengths are: "Omae"=4, " wa "=4, "mou "=4, "shindeiru."=10 (total: 22)
//	| TEST FUNCTION       | TEST NAME         |TESTFLAG| EXPECTING | TEST ARGS
	print_test_dictreduce("dictreduce       ",	FALSE,	22,         FALSE, 0);
}
void	test_dictfold(void)
{
//	| TEST FUNCTION       | TEST NAME         |TESTFLAG| EXPECTING | TEST ARGS
	print_test_dictreduce("dictfold         ",	FALSE,	122,        TRUE,  100);
}
#endif



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_generic_dict(void)
{
	print_suite_title("libccc/generic/dict");

	test_dicthash();
	test_keyval();

	test_dictnew();
	test_dictcreate();
	test_dictdup();
	test_dictfdel();

	test_dictget();
	test_dictset();
	test_dictadd();

	test_dictremove();
	test_dictfremove();
	test_dictremmatch();
	test_dictremmatches();
	test_dictfremmatches();
	test_dictsub();

	test_dictfind();
	test_dictffind();
	test_dicthaskey();
	test_dictkeyof();
	test_dictcount();
	test_dictcontains();
	test_dicthas();
	test_dicthasonly();
	test_dictequ();

	test_dictiter();
	test_dictiiter();
	test_dictmap();
	test_dictfilter();
	test_dictreduce();
	test_dictfold();

	return (OK);
}
