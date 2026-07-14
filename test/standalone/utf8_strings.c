/*
**	Standalone test program for the StringUTF8_* and StringArrayUTF8_* modules.
**	Build (from repo root, after building the library):
**		cc -Wall -Wextra -g -fsanitize=address,undefined \
**			test/standalone/utf8_strings.c \
**			-I./hdr -L./bin/debug_linux_x86-64/static -lccc \
**			-o utf8_strings_test && ./utf8_strings_test
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"
#include "libccc/text/char/unicode.h"

#define U8(x)	((t_utf8 const*)(x))
#define M8(x)	((t_utf8*)(x))

static int g_tests = 0;
static int g_failed = 0;

#define CHECK(NAME, COND) \
	do { \
		++g_tests; \
		if (!(COND)) \
		{ \
			++g_failed; \
			printf("FAIL: %s (line %d)\n", NAME, __LINE__); \
		} \
	} while (0)

#define CHECK_STR(NAME, RESULT, EXPECT) \
	do { \
		++g_tests; \
		t_utf8 const* _r = (RESULT); \
		if (_r == NULL || strcmp((char const*)_r, (char const*)(EXPECT)) != 0) \
		{ \
			++g_failed; \
			printf("FAIL: %s (line %d): got \"%s\", expected \"%s\"\n", \
				NAME, __LINE__, _r ? (char const*)_r : "(null)", (char const*)(EXPECT)); \
		} \
	} while (0)

#define CHECK_STR_TMP(NAME, RESULT, EXPECT) \
	do { \
		t_utf8* _tmp = (RESULT); \
		CHECK_STR(NAME, _tmp, EXPECT); \
		if (_tmp)	StringUTF8_Free(_tmp); \
	} while (0)

static
t_bool	strarr_content_equals(t_utf8 const* const* strarr, char const* const* expect)
{
	t_uint	i = 0;

	if (strarr == NULL)
		return (0);
	while (strarr[i] && expect[i])
	{
		if (strcmp((char const*)strarr[i], expect[i]) != 0)
			return (0);
		++i;
	}
	return (strarr[i] == NULL && expect[i] == NULL);
}

#define CHECK_STRARR(NAME, RESULT, ...) \
	do { \
		++g_tests; \
		char const* _expect[] = { __VA_ARGS__, NULL }; \
		t_utf8** _arr = (RESULT); \
		if (!strarr_content_equals((t_utf8 const* const*)_arr, _expect)) \
		{ \
			++g_failed; \
			printf("FAIL: %s (line %d)\n", NAME, __LINE__); \
			if (_arr) for (t_uint _i = 0; _arr[_i]; ++_i) \
				printf("      [%u]: \"%s\"\n", (unsigned)_i, (char*)_arr[_i]); \
		} \
		if (_arr)	StringArrayUTF8_Delete(&_arr); \
	} while (0)

/*
**	Test strings:
**	jp:    "お前はもう死んでいる" 10 glyphs, 30 bytes (each glyph is 3 bytes)
**	emoji: "a😀b㈎c"              5 glyphs, 10 bytes
**	nana:  "なはなはな"           5 glyphs, 15 bytes
*/
static t_utf8 const* jp    = U8("お前はもう死んでいる");
static t_utf8 const* emoji = U8("a\xF0\x9F\x98\x80" "b\xE3\x88\x8E" "c");
static t_utf8 const* nana  = U8("なはなはな");



/*============================================================================*\
||                          String: helper callbacks                          ||
\*============================================================================*/

static t_size	g_iter_count = 0;
static t_utf32	g_iter_last = 0;
static void	iter_count(t_utf32 c)					{ ++g_iter_count; g_iter_last = c; }
static t_size	g_iter_lastindex = 0;
static void	iter_index(t_utf32 c, t_size index)		{ (void)c; ++g_iter_count; g_iter_lastindex = index; }

static t_utf32	map_na_to_ha(t_utf32 c)				{ return (c == U'な' ? U'は' : c); }
static t_utf32	map_to_emoji(t_utf32 c)				{ return (c == 'b' ? 0x1F600 : c); }
static t_utf32	map_i_first_to_x(t_utf32 c, t_size i)	{ return (i == 0 ? 'x' : c); }

static t_bool	filter_ascii(t_utf32 c)				{ return (c < 0x80); }
static t_bool	filter_multibyte(t_utf32 c)			{ return (c >= 0x80); }
static t_bool	filter_i_even_byteindex(t_utf32 c, t_size i)	{ (void)c; return (i % 2 == 0); }



static
void	test_string_lifecycle(void)
{
	t_utf8*	str;

	str = StringUTF8_New(4);
	CHECK("New: zero-filled", str && str[0] == 0 && str[4] == 0);
	StringUTF8_Free(str);

	str = StringUTF8_New_C(3, 'x');
	CHECK_STR("New_C", str, "xxx");
	StringUTF8_Clear(str);
	CHECK("Clear", str[0] == 0 && str[1] == 0 && str[2] == 0);
	StringUTF8_Delete(&str);
	CHECK("Delete: nulls the pointer", str == NULL);

	str = StringUTF8_Duplicate(jp);
	StringUTF8_SetBytes(str, 'z');
	CHECK("SetBytes: fills every byte", strlen((char*)str) == 30 && str[0] == 'z' && str[29] == 'z');
	StringUTF8_Free(str);

	str = StringUTF8_Duplicate(jp);
	StringUTF8_SetChars(str, 'c');
	CHECK_STR("SetChars: one byte per glyph", str, "cccccccccc");
	StringUTF8_Free(str);
}

static
void	test_string_duplicate(void)
{
	CHECK_STR_TMP("Duplicate", StringUTF8_Duplicate(jp), jp);
	CHECK_STR_TMP("Duplicate_N: exact", StringUTF8_Duplicate_N(jp, 30), jp);
	CHECK_STR_TMP("Duplicate_N: glyph boundary", StringUTF8_Duplicate_N(jp, 6), U8("お前"));
	CHECK_STR_TMP("Duplicate_N: mid-glyph stops early", StringUTF8_Duplicate_N(jp, 7), U8("お前"));
	CHECK_STR_TMP("Duplicate_N: n too large", StringUTF8_Duplicate_N(jp, 999), jp);
	CHECK_STR_TMP("Duplicate_N: emoji boundary", StringUTF8_Duplicate_N(emoji, 4), U8("a"));
	CHECK_STR_TMP("Duplicate_Char", StringUTF8_Duplicate_Char(jp, U'う'), U8("お前はも"));
	CHECK_STR_TMP("Duplicate_Char: ascii", StringUTF8_Duplicate_Char(emoji, 'b'), U8("a\xF0\x9F\x98\x80"));
	CHECK_STR_TMP("Duplicate_Char: absent", StringUTF8_Duplicate_Char(jp, 'z'), jp);
	CHECK_STR_TMP("Duplicate_Charset", StringUTF8_Duplicate_Charset(jp, U8("んう")), U8("お前はも"));
	CHECK_STR_TMP("Duplicate_String", StringUTF8_Duplicate_String(jp, U8("死んで")), U8("お前はもう"));
	CHECK_STR_TMP("Duplicate_String: absent", StringUTF8_Duplicate_String(jp, U8("qq")), jp);
}

static
void	test_string_copy_add(void)
{
	t_utf8	buffer[64];
	t_size	len;

	memset(buffer, 0, sizeof(buffer));
	CHECK_STR("Copy", StringUTF8_Copy(buffer, jp), jp);
	CHECK_STR("Copy_N: pads with zeros", StringUTF8_Copy_N(buffer, U8("ab"), 4), U8("ab"));
	CHECK("Copy_N: trailing zeros", buffer[2] == 0 && buffer[3] == 0);

	memset(buffer, 'D', sizeof(buffer));
	len = StringUTF8_Copy_L(buffer, jp, 8);
	CHECK("Copy_L: returns source length", len == 30);
	CHECK_STR("Copy_L: whole glyphs only", buffer, U8("お前"));

	memset(buffer, 0, sizeof(buffer));
	StringUTF8_Copy(buffer, U8("abc"));
	CHECK_STR("Add", StringUTF8_Add(buffer, U8("死ね")), U8("abc死ね"));
	CHECK_STR("Add_N", StringUTF8_Add_N(buffer, U8("xyz"), 2), U8("abc死ねxy"));

	memset(buffer, 0, sizeof(buffer));
	StringUTF8_Copy(buffer, U8("ab"));
	len = StringUTF8_Add_L(buffer, jp, 9);
	CHECK("Add_L: returns total length", len == 2 + 30);
	CHECK_STR("Add_L: whole glyphs only", buffer, U8("abお前"));
}

static
void	test_string_has(void)
{
	CHECK("Has: true", StringUTF8_Has(jp, U8("z死")) == TRUE);
	CHECK("Has: false", StringUTF8_Has(jp, U8("zx")) == FALSE);
	CHECK("HasOnly: true", StringUTF8_HasOnly(nana, U8("なは")) == TRUE);
	CHECK("HasOnly: false", StringUTF8_HasOnly(jp, U8("なは")) == FALSE);
	CHECK("HasOnly: empty str", StringUTF8_HasOnly(U8(""), U8("なは")) == TRUE);
}

static
void	test_string_concat_join(void)
{
	t_utf8*	str1;
	t_utf8*	str2;
	t_utf8*	result;
	t_utf8 const*	strarr[4] = { U8("お"), U8("前"), U8("は"), NULL };

	CHECK_STR_TMP("Concat", StringUTF8_Concat(U8("お前"), U8("はもう")), U8("お前はもう"));

	str1 = StringUTF8_Duplicate(U8("お前"));
	result = StringUTF8_Append(&str1, U8("は"));
	CHECK_STR("Append", result, U8("お前は"));
	CHECK("Append: replaces dest", str1 == result);
	StringUTF8_Free(str1);

	str1 = StringUTF8_Duplicate(U8("前は"));
	result = StringUTF8_Prepend(U8("お"), &str1);
	CHECK_STR("Prepend", result, U8("お前は"));
	StringUTF8_Free(str1);

	str1 = StringUTF8_Duplicate(U8("お前"));
	str2 = StringUTF8_Duplicate(U8("はもう"));
	result = StringUTF8_Merge(&str1, &str2);
	CHECK_STR("Merge", result, U8("お前はもう"));
	CHECK("Merge: both point to result", str1 == result && str2 == result);
	StringUTF8_Free(result);

	CHECK_STR_TMP("Join", StringUTF8_Join(strarr, U8("・")), U8("お・前・は"));
	CHECK_STR_TMP("Join: empty sep", StringUTF8_Join(strarr, U8("")), U8("お前は"));
}

static
void	test_string_sub_insert_reverse_remove(void)
{
	t_utf8*	str;
	t_utf8*	result;

	CHECK_STR_TMP("Sub", StringUTF8_Sub(jp, 15, 9), U8("死んで"));
	CHECK_STR_TMP("Sub: zero length", StringUTF8_Sub(jp, 15, 0), U8(""));
	CHECK("Sub: index too large", StringUTF8_Sub(jp, 31, 1) == NULL);
	CHECK("Sub: length too large", StringUTF8_Sub(jp, 15, 16) == NULL);

	CHECK_STR_TMP("Insert", StringUTF8_Insert(U8("おはる"), U8("前"), 3), U8("お前はる"));
	CHECK_STR_TMP("Insert: at start", StringUTF8_Insert(jp, U8(">>"), 0), U8(">>お前はもう死んでいる"));
	CHECK_STR_TMP("Insert: at end", StringUTF8_Insert(U8("ab"), U8("る"), 2), U8("abる"));
	CHECK("Insert: index too large", StringUTF8_Insert(U8("ab"), U8("る"), 3) == NULL);

	str = StringUTF8_Duplicate(U8("おはる"));
	result = StringUTF8_Insert_InPlace(&str, U8("前"), 3);
	CHECK_STR("Insert_InPlace", result, U8("お前はる"));
	StringUTF8_Free(str);

	CHECK_STR_TMP("Reverse: glyphs", StringUTF8_Reverse(jp), U8("るいでん死うもは前お"));
	CHECK_STR_TMP("Reverse: mixed sizes", StringUTF8_Reverse(emoji), U8("c\xE3\x88\x8E" "b\xF0\x9F\x98\x80" "a"));
	CHECK_STR_TMP("Reverse: empty", StringUTF8_Reverse(U8("")), U8(""));

	CHECK_STR_TMP("Remove", StringUTF8_Remove(nana, U8("な")), U8("はは"));
	CHECK_STR_TMP("Remove: multi-glyph query", StringUTF8_Remove(jp, U8("死んで")), U8("お前はもういる"));
	CHECK_STR_TMP("Remove: absent", StringUTF8_Remove(jp, U8("zz")), jp);
	CHECK_STR_TMP("Remove: empty query", StringUTF8_Remove(jp, U8("")), jp);
}

static
void	test_string_replace(void)
{
	t_utf8	buffer[64];
	t_utf8*	str;

	CHECK_STR_TMP("Replace_Char", StringUTF8_Replace_Char(nana, U8("は"), M8("HA")), U8("なHAなHAな"));
	CHECK_STR_TMP("Replace_Charset", StringUTF8_Replace_Charset(nana, U8("なは"), U8("はな")), U8("はなはなは"));
	CHECK_STR_TMP("Replace_Charset: size change", StringUTF8_Replace_Charset(nana, U8("な"), U8("a")), U8("aはaはa"));
	CHECK("Replace_Charset: mismatched counts", StringUTF8_Replace_Charset(nana, U8("なは"), U8("a")) == NULL);
	CHECK("Replace_Charset: duplicate glyph", StringUTF8_Replace_Charset(nana, U8("なな"), U8("ab")) == NULL);
	CHECK_STR_TMP("Replace_String", StringUTF8_Replace_String(jp, U8("死んで"), U8("生きて")), U8("お前はもう生きている"));
	CHECK_STR_TMP("Replace_String: shrink", StringUTF8_Replace_String(nana, U8("なは"), U8("_")), U8("__な"));

	StringUTF8_Copy(buffer, nana);
	StringUTF8_Replace_Char_InPlace(buffer, U'な', U'に');
	CHECK_STR("Replace_Char_InPlace: same size", buffer, U8("にはにはに"));
	StringUTF8_Replace_Char_InPlace(buffer, U'に', 'x');	// different encoded size: must fail silently
	CHECK_STR("Replace_Char_InPlace: different size untouched", buffer, U8("にはにはに"));

	StringUTF8_Copy(buffer, nana);
	StringUTF8_Replace_Charset_InPlace(buffer, U8("なは"), U8("はな"));
	CHECK_STR("Replace_Charset_InPlace", buffer, U8("はなはなは"));
	StringUTF8_Copy(buffer, nana);
	StringUTF8_Replace_Charset_InPlace(buffer, U8("な"), U8("a"));	// different encoded size: must fail silently
	CHECK_STR("Replace_Charset_InPlace: different size untouched", buffer, nana);

	str = StringUTF8_Duplicate(jp);
	StringUTF8_Replace_String_InPlace(&str, U8("お前"), U8("俺"));
	CHECK_STR("Replace_String_InPlace", str, U8("俺はもう死んでいる"));
	StringUTF8_Free(str);
}

static
void	test_string_trim_pad(void)
{
	CHECK_STR_TMP("Trim", StringUTF8_Trim(U8("ななおはよなな"), U8("な")), U8("おはよ"));
	CHECK_STR_TMP("Trim: nothing to trim", StringUTF8_Trim(jp, U8("z")), jp);
	CHECK_STR_TMP("Trim: everything", StringUTF8_Trim(nana, U8("なは")), U8(""));
	CHECK_STR_TMP("Trim_L", StringUTF8_Trim_L(U8("ななおはよなな"), U8("な")), U8("おはよなな"));
	CHECK_STR_TMP("Trim_R", StringUTF8_Trim_R(U8("ななおはよなな"), U8("な")), U8("ななおはよ"));
	CHECK_STR_TMP("Trim_R: mixed charset", StringUTF8_Trim_R(U8("abでで"), U8("で")), U8("ab"));

	CHECK_STR_TMP("Pad_R: grow", StringUTF8_Pad_R(U8("ab"), U'は', 4), U8("abはは"));
	CHECK_STR_TMP("Pad_R: shrink keeps left", StringUTF8_Pad_R(jp, '_', 3), U8("お前は"));
	CHECK_STR_TMP("Pad_L: grow", StringUTF8_Pad_L(U8("ab"), U'は', 4), U8("ははab"));
	CHECK_STR_TMP("Pad_L: shrink keeps right", StringUTF8_Pad_L(jp, '_', 3), U8("でいる"));
	CHECK_STR_TMP("Pad: grow centered", StringUTF8_Pad(U8("お"), '-', 4), U8("-お--"));
	CHECK_STR_TMP("Pad: shrink centered", StringUTF8_Pad(jp, '-', 4), U8("もう死ん"));
	CHECK_STR_TMP("Pad: same size", StringUTF8_Pad(jp, '-', 10), jp);
}

static
void	test_string_functional(void)
{
	t_utf8*	str;
	t_utf8*	result;

	g_iter_count = 0;
	str = StringUTF8_Duplicate(jp);
	StringUTF8_Iterate(str, iter_count);
	CHECK("Iterate: glyph count and last glyph", g_iter_count == 10 && g_iter_last == U'る');
	g_iter_count = 0;
	StringUTF8_Iterate_I(str, iter_index);
	CHECK("Iterate_I: last byte index", g_iter_count == 10 && g_iter_lastindex == 27);
	StringUTF8_Free(str);

	CHECK_STR_TMP("Map: same size", StringUTF8_Map(nana, map_na_to_ha), U8("ははははは"));
	CHECK_STR_TMP("Map: grows", StringUTF8_Map(emoji, map_to_emoji), U8("a\xF0\x9F\x98\x80\xF0\x9F\x98\x80\xE3\x88\x8E" "c"));
	CHECK_STR_TMP("Map_I", StringUTF8_Map_I(nana, map_i_first_to_x), U8("xはなはな"));

	str = StringUTF8_Duplicate(nana);
	result = StringUTF8_Map_InPlace(&str, map_na_to_ha);
	CHECK_STR("Map_InPlace", result, U8("ははははは"));
	StringUTF8_Free(str);

	CHECK_STR_TMP("Filter: keep ascii", StringUTF8_Filter(emoji, filter_ascii), U8("abc"));
	CHECK_STR_TMP("Filter: keep multibyte", StringUTF8_Filter(emoji, filter_multibyte), U8("\xF0\x9F\x98\x80\xE3\x88\x8E"));
	CHECK_STR_TMP("Filter_I", StringUTF8_Filter_I(jp, filter_i_even_byteindex), U8("おはうんい"));
}

static
void	test_string_split_divide(void)
{
	CHECK_STRARR("Split_Char", StringUTF8_Split_Char(nana, U'は'), "な", "な", "な");
	CHECK_STRARR("Split_Char: ascii sep", StringUTF8_Split_Char(U8("a,b,,c"), ','), "a", "b", "c");
	CHECK_STRARR("Split_Char: seps at edges", StringUTF8_Split_Char(U8("ははおはは"), U'は'), "お");
	CHECK_STRARR("Split_Charset", StringUTF8_Split_Charset(jp, U8("うで")), "お前はも", "死ん", "いる");
	CHECK_STRARR("Split_String", StringUTF8_Split_String(jp, U8("死んで")), "お前はもう", "いる");
	CHECK_STRARR("Split_String: keeps empty parts", StringUTF8_Split_String(U8("|||aa"), U8("||")), "", "|aa");
	CHECK_STRARR("Split_String: sep between", StringUTF8_Split_String(U8("なxなxな"), U8("x")), "な", "な", "な");
	CHECK_STRARR("Divide: glyph chunks", StringUTF8_Divide(jp, 3), "お前は", "もう死", "んでい", "る");
	CHECK_STRARR("Divide: mixed glyph sizes", StringUTF8_Divide(emoji, 2), "a\xF0\x9F\x98\x80", "b\xE3\x88\x8E", "c");
}



/*============================================================================*\
||                       StringArray: helper callbacks                        ||
\*============================================================================*/

static t_utf8*	arr_iter_reverse(t_utf8* str)					{ return (StringUTF8_Reverse(str)); }
static t_utf8*	arr_iter_identity(t_utf8* str)					{ return (str); }
static t_utf8*	arr_iter_i_reverse_first(t_utf8* str, t_uint i)	{ return (i == 0 ? StringUTF8_Reverse(str) : str); }
static t_utf8*	arr_map_reverse(t_utf8 const* str)				{ return (StringUTF8_Reverse(str)); }
static t_utf8*	arr_map_i_dup_or_empty(t_utf8 const* str, t_uint i)	{ return (i % 2 == 0 ? StringUTF8_Duplicate(str) : StringUTF8_New(0)); }
static t_bool	arr_filter_nonempty(t_utf8 const* str)			{ return (str[0] != '\0'); }
static t_bool	arr_filter_i_even(t_utf8 const* str, t_uint i)	{ (void)str; return (i % 2 == 0); }
static t_bool	arr_match_ru(t_utf8 const* str)					{ return (StringUTF8_Equals(str, U8("る"))); }
static void*	arr_reduce_count(t_utf8 const* str, void* acc)	{ (void)str; return ((void*)((t_size)acc + 1)); }
static void*	arr_fold_total(t_utf8 const* str, void* acc)	{ return ((void*)((t_size)acc + StringUTF8_Length(str))); }

static
t_utf8**	make_arr3(void)	// heap-allocated ["お","は","る"]
{
	t_utf8** arr = StringArrayUTF8_New(3);
	arr[0] = StringUTF8_Duplicate(U8("お"));
	arr[1] = StringUTF8_Duplicate(U8("は"));
	arr[2] = StringUTF8_Duplicate(U8("る"));
	return (arr);
}



static
void	test_strarr_lifecycle(void)
{
	t_utf8**	arr;
	t_utf8 const*	view[4] = { U8("お"), U8("は"), U8("る"), NULL };

	arr = StringArrayUTF8_New(2);
	CHECK("arr New: null slots", arr && arr[0] == NULL && arr[2] == NULL);
	StringArrayUTF8_Free(arr);

	arr = StringArrayUTF8_New_C(2, 3, U'な');
	CHECK("arr New_C: length", StringArrayUTF8_Length((t_utf8 const* const*)arr) == 2);
	CHECK_STR("arr New_C: content", arr[0], U8("ななな"));
	CHECK_STR("arr New_C: content[1]", arr[1], U8("ななな"));
	StringArrayUTF8_Delete(&arr);
	CHECK("arr Delete: nulls the pointer", arr == NULL);

	arr = StringArrayUTF8_Create(2, StringUTF8_Duplicate(U8("お")), StringUTF8_Duplicate(U8("る")));
	CHECK_STRARR("arr Create", arr, "お", "る");

	CHECK("arr Length", StringArrayUTF8_Length(view) == 3);
	CHECK("arr TotalLength", StringArrayUTF8_TotalLength(view, 3) == 9);
	CHECK("arr TotalLength: capped", StringArrayUTF8_TotalLength(view, 2) == 6);

	arr = StringArrayUTF8_Duplicate(view);
	CHECK_STRARR("arr Duplicate", arr, "お", "は", "る");
	CHECK_STRARR("arr Sub", StringArrayUTF8_Sub(view, 1, 2), "は", "る");
	CHECK("arr Sub: bad index", StringArrayUTF8_Sub(view, 4, 1) == NULL);
	CHECK("arr Sub: bad length", StringArrayUTF8_Sub(view, 1, 3) == NULL);
}

static
void	test_strarr_copy_add_insert(void)
{
	t_utf8**	arr;
	t_utf8**	src;
	t_utf8 const*	wedge_view[3] = { U8("1"), U8("2"), NULL };

	arr = make_arr3();
	src = StringArrayUTF8_Create(2, StringUTF8_Duplicate(U8("X")), StringUTF8_Duplicate(U8("Y")));
	CHECK("arr Copy", StringArrayUTF8_Copy(arr, 1, (t_utf8 const* const*)src, 0, 2) == arr);
	CHECK_STR("arr Copy: content[1]", arr[1], U8("X"));
	CHECK_STR("arr Copy: content[2]", arr[2], U8("Y"));
	StringArrayUTF8_Delete(&src);
	StringArrayUTF8_Delete(&arr);

	arr = make_arr3();
	arr = StringArrayUTF8_Add(arr, U8("ぞ"));
	CHECK_STRARR("arr Add", arr, "お", "は", "る", "ぞ");

	arr = make_arr3();
	arr = StringArrayUTF8_Insert(arr, U8("ぞ"), 1);
	CHECK_STRARR("arr Insert", arr, "お", "ぞ", "は", "る");
	arr = make_arr3();
	arr = StringArrayUTF8_Insert(arr, U8("ぞ"), 3);
	CHECK_STRARR("arr Insert: at end", arr, "お", "は", "る", "ぞ");

	arr = make_arr3();
	arr = StringArrayUTF8_Wedge(arr, wedge_view, 1);
	CHECK_STRARR("arr Wedge", arr, "お", "1", "2", "は", "る");
}

static
void	test_strarr_remove(void)
{
	t_utf8**	arr;
	t_utf8*		detached;

	arr = make_arr3();
	detached = arr[1];
	StringArrayUTF8_RemoveAt(arr, 1);	// non-_F does not free the removed string
	CHECK_STRARR("arr RemoveAt", arr, "お", "る");
	StringUTF8_Free(detached);

	arr = make_arr3();
	StringArrayUTF8_RemoveAt_F(arr, 2, StringUTF8_Free);
	CHECK_STRARR("arr RemoveAt_F", arr, "お", "は");

	arr = make_arr3();
	detached = arr[1];
	StringArrayUTF8_Remove(arr, U8("は"));
	CHECK_STRARR("arr Remove: content matched", arr, "お", "る");
	StringUTF8_Free(detached);

	arr = make_arr3();
	StringArrayUTF8_Remove_F(arr, U8("る"), StringUTF8_Free);
	CHECK_STRARR("arr Remove_F", arr, "お", "は");

	arr = StringArrayUTF8_Create(5,
		StringUTF8_Duplicate(U8("x")), StringUTF8_Duplicate(U8("な")),
		StringUTF8_Duplicate(U8("x")), StringUTF8_Duplicate(U8("x")),
		StringUTF8_Duplicate(U8("な")));
	StringArrayUTF8_RemoveAll_F(arr, U8("x"), StringUTF8_Free);
	CHECK_STRARR("arr RemoveAll_F", arr, "な", "な");

	arr = StringArrayUTF8_Create(2,
		StringUTF8_Duplicate(U8("x")), StringUTF8_Duplicate(U8("x")));
	StringArrayUTF8_RemoveAll_F(arr, U8("x"), StringUTF8_Free);
	CHECK("arr RemoveAll_F: everything", arr[0] == NULL);
	StringArrayUTF8_Free(arr);
}

static
void	test_strarr_replace_reverse_pad(void)
{
	t_utf8 const*	view[4] = { U8("な"), U8("は"), U8("な"), NULL };

	CHECK_STRARR("arr Replace", StringArrayUTF8_Replace(view, U8("な"), U8("に")), "に", "は", "に");
	CHECK_STRARR("arr Replace: absent", StringArrayUTF8_Replace(view, U8("zz"), U8("に")), "な", "は", "な");
	CHECK_STRARR("arr ReplaceFirst", StringArrayUTF8_ReplaceFirst(view, U8("な"), U8("に"), 1), "に", "は", "な");
	CHECK_STRARR("arr ReplaceLast", StringArrayUTF8_ReplaceLast(view, U8("な"), U8("に"), 1), "な", "は", "に");
	CHECK_STRARR("arr Reverse", StringArrayUTF8_Reverse(view), "な", "は", "な");
	CHECK_STRARR("arr Reverse: distinct", StringArrayUTF8_Reverse((t_utf8 const* const*)(t_utf8 const*[]){ U8("a"), U8("b"), U8("c"), NULL }), "c", "b", "a");
	CHECK_STRARR("arr Pad_L", StringArrayUTF8_Pad_L(view, U'ー', 3), "ーーな", "ーーは", "ーーな");
}

static
void	test_strarr_concat_join(void)
{
	t_utf8**	arr1;
	t_utf8**	arr2;
	t_utf8**	result;
	t_utf8 const*	a[3] = { U8("お"), U8("は"), NULL };
	t_utf8 const*	b[2] = { U8("る"), NULL };
	t_utf8 const*	sep[2] = { U8("・"), NULL };
	t_utf8 const* const*	joined[3] = { a, b, NULL };

	CHECK_STRARR("arr Concat", StringArrayUTF8_Concat(a, b), "お", "は", "る");

	arr1 = StringArrayUTF8_Duplicate(a);
	result = StringArrayUTF8_Append(&arr1, b);
	CHECK("arr Append: replaces dest", result == arr1);
	CHECK_STRARR("arr Append", arr1, "お", "は", "る");

	arr1 = StringArrayUTF8_Duplicate(a);
	StringArrayUTF8_Prepend(b, &arr1);
	CHECK_STRARR("arr Prepend", arr1, "る", "お", "は");

	arr1 = StringArrayUTF8_Duplicate(a);
	arr2 = StringArrayUTF8_Duplicate(b);
	result = StringArrayUTF8_Merge(&arr1, &arr2);
	CHECK("arr Merge: both point to result", arr1 == result && arr2 == result);
	CHECK_STRARR("arr Merge", result, "お", "は", "る");

	CHECK_STRARR("arr Join", StringArrayUTF8_Join(joined, sep), "お", "は", "・", "る");
}

static
void	test_strarr_compare_find_count(void)
{
	t_utf8 const*	a[4] = { U8("お"), U8("は"), U8("る"), NULL };
	t_utf8 const*	b[4] = { U8("お"), U8("は"), U8("る"), NULL };
	t_utf8 const*	c[4] = { U8("お"), U8("X"), U8("る"), NULL };
	t_utf8 const*	d[3] = { U8("お"), U8("は"), NULL };
	t_utf8 const*	counts[4] = { nana, jp, U8("なな"), NULL };
	t_utf8* const*	found;

	CHECK("arr Equals: equal", StringArrayUTF8_Equals(a, b) == TRUE);
	CHECK("arr Equals: same pointer", StringArrayUTF8_Equals(a, a) == TRUE);
	CHECK("arr Equals: different content", StringArrayUTF8_Equals(a, c) == FALSE);
	CHECK("arr Equals: different length", StringArrayUTF8_Equals(a, d) == FALSE);
	CHECK("arr Equals_N: prefix equal", StringArrayUTF8_Equals_N(a, c, 1) == TRUE);
	CHECK("arr Equals_N: prefix not equal", StringArrayUTF8_Equals_N(a, c, 2) == FALSE);
	CHECK("arr Equals_N: shorter arrays equal", StringArrayUTF8_Equals_N(a, b, 99) == TRUE);

	found = StringArrayUTF8_Find((t_utf8* const*)a, U8("は"));
	CHECK("arr Find", found == (t_utf8* const*)&a[1]);
	CHECK("arr Find: absent", StringArrayUTF8_Find((t_utf8* const*)a, U8("zz")) == NULL);
	found = StringArrayUTF8_Find_F((t_utf8* const*)a, arr_match_ru);
	CHECK("arr Find_F", found == (t_utf8* const*)&a[2]);
	CHECK("arr IndexOf", StringArrayUTF8_IndexOf(a, U8("る")) == 2);
	CHECK("arr IndexOf: absent", StringArrayUTF8_IndexOf(a, U8("zz")) == ERROR);
	CHECK("arr IndexOf_F", StringArrayUTF8_IndexOf_F(a, arr_match_ru) == 2);

	CHECK("arr Count_Char", StringArrayUTF8_Count_Char(counts, U'な') == 5);
	CHECK("arr Count_Charset", StringArrayUTF8_Count_Charset(counts, U8("なは")) == 8);
	CHECK("arr Count_String", StringArrayUTF8_Count_String(counts, U8("なは")) == 2);
}

static
void	test_strarr_functional(void)
{
	t_utf8**	arr;
	t_utf8 const*	view[4] = { U8("おは"), U8(""), U8("なは"), NULL };

	arr = StringArrayUTF8_Create(2, StringUTF8_Duplicate(U8("おは")), StringUTF8_Duplicate(U8("なは")));
	StringArrayUTF8_Iterate(arr, arr_iter_reverse);
	CHECK_STRARR("arr Iterate", arr, "はお", "はな");

	arr = StringArrayUTF8_Create(2, StringUTF8_Duplicate(U8("おは")), StringUTF8_Duplicate(U8("なは")));
	StringArrayUTF8_Iterate(arr, arr_iter_identity);
	CHECK_STRARR("arr Iterate: identity", arr, "おは", "なは");

	arr = StringArrayUTF8_Create(2, StringUTF8_Duplicate(U8("おは")), StringUTF8_Duplicate(U8("なは")));
	StringArrayUTF8_Iterate_I(arr, arr_iter_i_reverse_first);
	CHECK_STRARR("arr Iterate_I", arr, "はお", "なは");

	CHECK_STRARR("arr Map", StringArrayUTF8_Map(view, arr_map_reverse), "はお", "", "はな");
	CHECK_STRARR("arr Map_I", StringArrayUTF8_Map_I(view, arr_map_i_dup_or_empty), "おは", "", "なは");
	CHECK_STRARR("arr Filter", StringArrayUTF8_Filter(view, arr_filter_nonempty), "おは", "なは");
	CHECK_STRARR("arr Filter_I", StringArrayUTF8_Filter_I(view, arr_filter_i_even), "おは", "なは");

	CHECK("arr Reduce", (t_size)StringArrayUTF8_Reduce(view, arr_reduce_count) == 3);
	CHECK("arr Fold", (t_size)StringArrayUTF8_Fold(view, arr_fold_total, (void*)100) == 100 + 6 + 0 + 6);
}



int	main(void)
{
	test_string_lifecycle();
	test_string_duplicate();
	test_string_copy_add();
	test_string_has();
	test_string_concat_join();
	test_string_sub_insert_reverse_remove();
	test_string_replace();
	test_string_trim_pad();
	test_string_functional();
	test_string_split_divide();

	test_strarr_lifecycle();
	test_strarr_copy_add_insert();
	test_strarr_remove();
	test_strarr_replace_reverse_pad();
	test_strarr_concat_join();
	test_strarr_compare_find_count();
	test_strarr_functional();

	printf("\n%d/%d tests passed\n", g_tests - g_failed, g_tests);
	return (g_failed != 0);
}
