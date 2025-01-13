
#include "libccc/monad/array.c"
#include "libccc/monad/list.c"

#include "test.h"
#include "test_utils.h"



#ifndef c_lstitem
void test_lstitem(void)	{}
#warning "lstitem() test suite function defined, but the function isn't defined."
#else
void	print_test_lstitem(char const* test_name, t_testflags flags,
		char const* expecting,
		void* item,
		t_size item_size)
{
	/*
	TEST_PERFORM(s_list(any)*, lstitem, item);
	print_test_str(test_name, "_lstitem->item",      result_libccc->item,      expecting,   can_segfault);
//	print_test_size(NULL,     "_lstitem->item_size", result_libccc->item_size, expect_size, can_segfault);
	print_timer_result(&t, FALSE);
	if (result_libccc) free(result_libccc);
	*/
}
void	test_lstitem(void)
{
/*	| TEST FUNCTION  | TEST NAME         |TESTFLAG| EXPECTING   | TEST ARGS */
/* TODO
	print_test_lstitem("lstitem            ",	FALSE,  "Omae",       "Omae",        5);
	print_test_lstitem("lstitem            ",	FALSE,  " wa ",       " wa ",        5);
	print_test_lstitem("lstitem            ",	FALSE,  "mou ",       "mou ",        5);
	print_test_lstitem("lstitem            ",	FALSE,  "shindeiru.", "shindeiru.", 11);
	print_test_lstitem("lstitem (empty str)",	FALSE,  "",           "",            1);
	print_test_lstitem("lstitem (null  ptr)",	TRUE,   NULL,         NULL,          5);
*/
}
#endif



#ifndef c_lstlen
void test_lstlen(void)	{}
#warning "lstlen() test suite function defined, but the function isn't defined."
#else
void	print_test_lstsize(char const* test_name, t_testflags flags,
		char const* expecting,
		s_list(any) *list)
{
	// TODO
}
void	test_lstsize(void)
{
/*	| TEST FUNCTION  | TEST NAME          |TESTFLAG| EXPECTING | TEST ARGS */
/*	TODO
	//	int		c_lstsize(s_list(any) *list);
		c_putstr("\nft_lstsize : ");
		c_putnbr(c_lstsize(*mixed_list));
		c_putstr("\nExpected : 9\n");
*/
}
#endif



#ifndef c_lstdel
void test_lstdel(void)	{}
#warning "lstdel() test suite function defined, but the function isn't defined."
#else
void	print_test_lstdel(char const* test_name, t_testflags flags,
		char const* expecting,
		s_list(any) **a_lst)
{
	// TODO
}
void	test_lstdel(void)
{
/*	| TEST FUNCTION  | TEST NAME          |TESTFLAG| EXPECTING | TEST ARGS */
/*	TODO
*/
}
#endif



#ifndef c_lstfdel
void test_lstfdel(void)	{}
#warning "lstfdel() test suite function defined, but the function isn't defined."
#else
void	print_test_lstfdel(char const* test_name, t_testflags flags,
		char const* expecting,
		s_list(any) **a_lst,
		void (*delete_func)(void *, t_size))
{
	// TODO
}
void	test_lstfdel(void)
{
/*	| TEST FUNCTION  | TEST NAME          |TESTFLAG| EXPECTING | TEST ARGS */
/*	TODO
	//	void	c_lstfdel(s_list(any) **a_lst, void (*del)(void *, t_size));
		c_putstr("\nft_lstfdel :\n");	
		c_lstfdel(mixed_list, c_delete);

		if (*mixed_list) // || *mixed_list || (*mixed_list)->item)
		{
			c_putstr_fd("Error deleting with c_lstfdel\n", 2);
		}
		else
		{
			c_putstr("Function seems to work; should still check for leaks.\n");
		}
	//	void	c_lstfdel(s_list(any) **a_lst, void (*del)(void *, t_size));
		c_putstr("\nft_lstfdel :\n");	
		c_lstfdel(&tmp, c_delete);
		c_lstfdel(a_slst, c_delete);
		if (*a_slst || tmp) // || *a_slst || (*a_ilst)->item || tmp->item)
		{
			c_putstr_fd("Error deleting with c_lstfdel\n", 2);
		}
		else
		{
			c_putstr("Function seems to work; should still check for leaks.\n");
		}
*/
}
#endif



#ifndef c_lstget
void test_lstget(void)	{}
#warning "lstget() test suite function defined, but the function isn't defined."
#else
void	print_test_lstget(char const* test_name, t_testflags flags,
		char const* expecting,
		s_list(any) *list,
		t_uint index)
{
	// TODO
}
void	test_lstget(void)
{
/*	| TEST FUNCTION  | TEST NAME          |TESTFLAG| EXPECTING | TEST ARGS */
//	TODO
}
#endif



#ifndef c_lstset
void test_lstset(void)	{}
#warning "lstset() test suite function defined, but the function isn't defined."
#else
void	print_test_lstset(char const* test_name, t_testflags flags,
		char const* expecting,
		s_list(any) *list,
		t_uint index,
		void* item)
{
	// TODO
}
void	test_lstset(void)
{
/*	| TEST FUNCTION  | TEST NAME          |TESTFLAG| EXPECTING | TEST ARGS */
//	TODO
}
#endif



#ifndef c_lstcpy
void test_lstcpy(void)	{}
#warning "lstcpy() test suite function defined, but the function isn't defined."
#else
void	print_test_lstcpy(char const* test_name, t_testflags flags,
		char const* expecting,
		s_list(any)* dest,
		s_list(any)* src,
		t_uint n)
{
	// TODO
}
void	test_lstcpy(void)
{
/*	| TEST FUNCTION  | TEST NAME          |TESTFLAG| EXPECTING | TEST ARGS */
//	TODO
}
#endif



#ifndef c_lstsub
void test_lstsub(void)	{}
#warning "lstsub() test suite function defined, but the function isn't defined."
#else
void	print_test_lstsub(char const* test_name, t_testflags flags,
		char const* expecting,
		s_list(any) *list,
		t_uint index,
		t_uint n)
{
	// TODO
}
void	test_lstsub(void)
{
/*	| TEST FUNCTION  | TEST NAME          |TESTFLAG| EXPECTING | TEST ARGS */
//	TODO
}
#endif



#ifndef c_lstprepend
void test_lstprepend(void)	{}
#warning "lstprepend() test suite function defined, but the function isn't defined."
#else
void	print_test_lstprepend(char const* test_name, t_testflags flags,
		char const* expecting,
		s_list(any)* list,
		s_list(any)* elem)
{
	// TODO
}
void	test_lstadd(void)
{
/*	| TEST FUNCTION  | TEST NAME          |TESTFLAG| EXPECTING | TEST ARGS */
/*	TODO
	a_lst = &lst_3;
	c_lstadd(a_lst, lst_2);
	c_lstadd(a_lst, lst_1);
	c_lstadd(a_lst, lst_0);
	print_test_list("lstadd", "lstadd", lst_0, expect, FALSE);
*/
}
#endif



#ifndef c_lstappend
void test_lstappend(void)	{}
#warning "lstappend() test suite function defined, but the function isn't defined."
#else
void	print_test_lstappend(char const* test_name, t_testflags flags,
		char const* expecting,
		s_list(any) *list,
		s_list(any) *elem)
{
	// TODO
}
void	test_lstappend(void)
{
/*	| TEST FUNCTION  | TEST NAME          |TESTFLAG| EXPECTING | TEST ARGS */
/*	TODO
	//	void	c_lstappend(s_list(any) **a_lst, s_list(any) *new_elem);
		s_list(any)	**mixed_list;
		mixed_list = a_slst;
		c_putstr("\nft_lstappend (mind the little endianness and the fact that list was listiter(abs)) :\n");
		c_lstappend(mixed_list, *a_ilst);
		c_lstiter(*mixed_list, c_puthex_llstelem);
		c_putstr("\nExpected:\n4F 6D 61 65 00\n20 77 61 20 00\n6D 6F 75 20 00\n73 68 69 6E 64 65 69 72 75 2E 00\n00 00 00 00\n00 00 00 00\n9A 02 00 00\n09 03 00 00\n2D 00 00 00\n");
*/
}
#endif



#ifndef c_lstinsert
void test_lstinsert(void)	{}
#warning "lstinsert() test suite function defined, but the function isn't defined."
#else
void	print_test_lstinsert(char const* test_name, t_testflags flags,
		char const* expecting,
		s_list(any) *list,
		s_list(any) *elem,
		t_uint index)
{
	// TODO
}
void	test_lstinsert(void)
{
/*	| TEST FUNCTION  | TEST NAME          |TESTFLAG| EXPECTING | TEST ARGS */
//	TODO
}
#endif



#ifndef c_lstfind
void test_lstfind(void)	{}
#warning "lstfind() test suite function defined, but the function isn't defined."
#else
void	print_test_lstfind(char const* test_name, t_testflags flags,
		char const* expecting,
		s_list(any)* list,
		void* query)
{
	// TODO
}
void	test_lstfind(void)
{
/*	| TEST FUNCTION  | TEST NAME          |TESTFLAG| EXPECTING | TEST ARGS */
//	TODO
}
#endif



#ifndef c_lstfindi
void test_lstfindi(void)	{}
#warning "lstfindi() test suite function defined, but the function isn't defined."
#else
void	print_test_lstfindi(char const* test_name, t_testflags flags,
		char const* expecting,
		s_list(any) *list,
		void* query)
{
	// TODO
}
void	test_lstfindi(void)
{
/*	| TEST FUNCTION  | TEST NAME          |TESTFLAG| EXPECTING | TEST ARGS */
//	TODO
}
#endif



#ifndef c_lstdelone
void test_lstdelone(void)	{}
#warning "lstdelone() test suite function defined, but the function isn't defined."
#else
void	print_test_lstdelone(char const* test_name, t_testflags flags,
		char const* expecting,
		s_list(any)* list,
		void (*delete_func)(void*))
{
	// TODO
}
void	test_lstdelone(void)
{
/*	| TEST FUNCTION  | TEST NAME          |TESTFLAG| EXPECTING | TEST ARGS */
/*	TODO
	//	void	c_lstdelone(s_list(any) **a_lst, void (*del)(void *, t_size));
		c_putstr("\nft_lstdelone :\n");
		s_list(any) *tmp = (*a_ilst)->next;
		c_lstdelone(a_ilst, c_delete);
		//alternative fix without lstget => (*mixed_list)->next->next->next->next = 0;
		c_lstget(*mixed_list, 3)->next = 0;
		c_lstappend(mixed_list, tmp);
		c_lstiter(*mixed_list, c_puthex_llstelem);
		c_putstr("\nExpected:\n4F 6D 61 65 00\n20 77 61 20 00\n6D 6F 75 20 00\n73 68 69 6E 64 65 69 72 75 2E 00\n00 00 00 00\n9A 02 00 00\n09 03 00 00\n2D 00 00 00\n");

		if (*a_ilst) // || *a_ilst || (*a_ilst)->item)
		{
			c_putstr_fd("Error deleting with c_lstdel\n", 2);
		}
		else
		{
			c_putstr("Function seems to work; should still check for leaks.\n");
		}
	//	void	c_lstdelone(s_list(any) **a_lst, void (*del)(void *, t_size));
		c_putstr("\nft_lstdelone :\n");
		s_list(any) *tmp = (*a_ilst)->next;
		c_lstdelone(a_ilst, c_delete);
		c_lstiter(tmp, c_puthex_llstelem);
		c_putstr("\nExpected:\n00 00 00 00\n9A 02 00 00\n09 03 00 00\n2D 00 00 00\n");
		if (*a_ilst) // || *a_ilst || (*a_ilst)->item)
		{
			c_putstr_fd("Error deleting with c_lstdel\n", 2);
		}
		else
		{
			c_putstr("Function seems to work; should still check for leaks.\n");
		}
*/
}
#endif



#ifndef c_lstiter
void test_lstiter(void)	{}
#warning "lstiter() test suite function defined, but the function isn't defined."
#else
void	print_test_lstiter(char const* test_name, t_testflags flags,
		char const* expecting,
		s_list(any)* list,
		void (*f)(void* item))
{
	// TODO
}
void	test_lstiter(void)
{
/*	| TEST FUNCTION  | TEST NAME          |TESTFLAG| EXPECTING | TEST ARGS */
/*	TODO
//	c_lstiter(s_list(any) *list, void (*f)(s_list(any) *elem));
	c_lstiter(*a_lst, c_lstiter_tolower);
	print_test_list("lstiter", "lstiter", a_lst, expect_lower, FALSE);
*/
}
#endif



#ifndef c_lstiiter
void test_lstiiter(void)	{}
#warning "lstiiter() test suite function defined, but the function isn't defined."
#else
void	print_test_lstiiter(char const* test_name, t_testflags flags,
		char const* expecting,
		s_list(any)* list,
		void (*f)(void* item, t_uint index))
{
	// TODO
}
void	test_lstiiter(void)
{
/*	| TEST FUNCTION  | TEST NAME          |TESTFLAG| EXPECTING | TEST ARGS */
/*	TODO
//	c_lstiiter(s_list(any) *list, void (*f)(s_list(any) *elem));
	c_lstiiter(*a_lst, c_lstiter_tolower);
	print_test_list("lstiiter", "lstiiter", a_lst, expect_lower, FALSE);
*/
}
#endif



#ifndef c_lstmap
void test_lstmap(void)	{}
#warning "lstmap() test suite function defined, but the function isn't defined."
#else
void	print_test_lstmap(char const* test_name, t_testflags flags,
		char const* expecting,
		s_list(any)* list,
		void* (*map)(void* item))
{
	// TODO
}
void	test_lstmap(void)
{
/*	| TEST FUNCTION  | TEST NAME          |TESTFLAG| EXPECTING | TEST ARGS */
/*	TODO
//	s_list(any)	*c_lstmap(s_list(any) *list, s_list(any) *(*f)(s_list(any) *elem));
	segfault = setjmp(restore); if (!segfault) *a_lst = c_lstmap(*a_lst, c_lstmap_toupper); else *a_lst = NULL;
	print_test_list("lstmap", "lstmap", *a_lst, expect_upper, FALSE);
*/
}
#endif



#ifndef c_lstimap
void test_lstimap(void)	{}
#warning "lstimap() test suite function defined, but the function isn't defined."
#else
void	print_test_lstimap(char const* test_name, t_testflags flags,
		char const* expecting,
		s_list(any)* list,
		void* (*map)(void* item, t_uint index))
{
	// TODO
}
void	test_lstimap(void)
{
/*	| TEST FUNCTION  | TEST NAME          |TESTFLAG| EXPECTING | TEST ARGS */
/*	TODO
//	s_list(any)	*c_lstimap(s_list(any) *list, s_list(any) *(*f)(s_list(any) *elem));
	segfault = setjmp(restore); if (!segfault) *a_lst = c_lstmap(*a_lst, c_lstmap_toupper); else *a_lst = NULL;
	print_test_list("lstimap", "lstimap", *a_lst, expect_upper, FALSE);
*/
}
#endif



#ifndef c_lstfold
void test_lstfold(void)	{}
#warning "lstfold() test suite function defined, but the function isn't defined."
#else
void	print_test_lstfold(char const* test_name, t_testflags flags,
		char const* expecting)
{
	// TODO
}
void	test_lstfold(void)
{
/*	| TEST FUNCTION  | TEST NAME          |TESTFLAG| EXPECTING | TEST ARGS */
#if 0 //	TODO
	c_putstr("\nft_lstfold : ");
	n = 0;
	c_lstfold(*a_ilst, &n, c_add);
	c_putnbr(n);
	c_putstr("\nExpected : 1337\n");
#endif
}
#endif



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_monad_list(void)
{
	print_suite_title("libccc/monad/list");

	print_nonstd();

/*
	s_list(any) **a_lst;
	s_list(any) *lst_0;
	s_list(any) *lst_1;
	s_list(any) *lst_2;
	s_list(any) *lst_3;
	s_list(any) *lst_4;
	char const *expect[]       = { "Omae", " wa ", "mou ", "shindeiru.", NULL };
	char const *expect_upper[] = { "OMAE", " WA ", "MOU ", "SHINDEIRU.", NULL };
	char const *expect_lower[] = { "omae", " wa ", "mou ", "shindeiru.", NULL };
*/


	test_lstitem();
//	test_lstlen();
//	test_lstnew();
//	test_lstdel();
//	test_lstdup();
//	test_lstget();
//	test_lstset();
//	test_lstcopy();
//	test_lstsub();
//	test_lstappend();
//	test_lstprepend();
//	test_lstinsert();
//	test_lstdelone();
//	test_lstdelall();
//	test_lstdelat();
//	test_lstrep();
//	test_lstfind();
//	test_lstequ();
//	test_lstcmp();
//	test_lstiter();
//	test_lstmap();
//	test_lstfilt();
	return (OK);
}
