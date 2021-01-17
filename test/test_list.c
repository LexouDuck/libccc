
#include "libccc_list.h"

#include "test.h"



#ifdef			c_lstnew
void	print_test_lstnew(char const* test_name, int can_segfault,
		char const* expecting,
		void* item,
		t_size item_size)
{
	t_size expect_size = expecting ? strlen(expecting) + 1 : 0;
	TEST_PERFORM_RESULT_TYPE(s_list*, lstnew, item, item_size);
	print_test_size(test_name, "_lstnew->item_size", result_libccc->item_size, expect_size, can_segfault);
	print_test_str(NULL,       "_lstnew->item",      result_libccc->item,      expecting,   can_segfault);
	print_timer_result(&t, FALSE);
	if (result_libccc) free(result_libccc);
}
void	test_lstnew(void)
{
/*	| TEST FUNCTION  | TEST NAME         |CAN SEGV| EXPECTING   | TEST ARGS */
	print_test_lstnew("lstnew            ",	FALSE,  "Omae",       "Omae",        5);
	print_test_lstnew("lstnew            ",	FALSE,  " wa ",       " wa ",        5);
	print_test_lstnew("lstnew            ",	FALSE,  "mou ",       "mou ",        5);
	print_test_lstnew("lstnew            ",	FALSE,  "shindeiru.", "shindeiru.", 11);
	print_test_lstnew("lstnew (empty str)",	FALSE,  "",           "",            1);
	print_test_lstnew("lstnew (null  ptr)",	TRUE,   NULL,         NULL,          5);
}
#endif



#ifdef			c_lstprepend
void	print_test_lstprepend(char const* test_name, int can_segfault,
		char const* expecting,
		s_list** a_lst,
		s_list* elem)
{
	s_timer t = {0};
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		c_lstadd(a_lst, elem);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstadd(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
/*	TODO
	a_lst = &lst_3;
	c_lstadd(a_lst, lst_2);
	c_lstadd(a_lst, lst_1);
	c_lstadd(a_lst, lst_0);
	print_test_lst("lstadd", "lstadd", lst_0, expect, FALSE);
*/
}
#endif



#ifdef			c_lstappend
void	print_test_lstappend(char const* test_name, int can_segfault,
		char const* expecting,
		s_list **a_lst, s_list *elem)
{
	s_timer t = {0};
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		c_lstappend(a_lst, elem);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstappend(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
/*	TODO
	//	void	c_lstappend(s_list **a_lst, s_list *new_elem);
		s_list	**mixed_list;
		mixed_list = a_slst;
		c_putstr("\nft_lstappend (mind the little endianness and the fact that lst was listiter(abs)) :\n");
		c_lstappend(mixed_list, *a_ilst);
		c_lstiter(*mixed_list, c_puthex_llstelem);
		c_putstr("\nExpected:\n4F 6D 61 65 00\n20 77 61 20 00\n6D 6F 75 20 00\n73 68 69 6E 64 65 69 72 75 2E 00\n00 00 00 00\n00 00 00 00\n9A 02 00 00\n09 03 00 00\n2D 00 00 00\n");
*/
}
#endif



#ifdef			c_lstinsert
void	print_test_lstinsert(char const* test_name, int can_segfault,
		char const* expecting,
		s_list **a_lst,
		s_list *elem,
		t_u32 index)
{
	s_timer t = {0};
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		c_lstinsert(a_lst, elem, index);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstinsert(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}
#endif



#ifdef			c_lstcpy
void	print_test_lstcpy(char const* test_name, int can_segfault,
		char const* expecting,
		s_list *lst)
{
	s_timer t = {0};
	s_list *result;
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		result = c_lstcpy(lst);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstcpy(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}
#endif



#ifdef			c_lstpop
void	print_test_lstpop(char const* test_name, int can_segfault,
		char const* expecting,
		s_list **a_lst,
		void (*del)(void *, t_size))
{
	s_timer t = {0};
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		c_lstpop(a_lst, del);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstpop(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}
#endif



#ifdef			c_lstdelone
void	print_test_lstdelone(char const* test_name, int can_segfault,
		char const* expecting,
		s_list **a_lst,
		void (*del)(void *, t_size))
{
	s_timer t = {0};
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		c_lstdelone(a_lst, del);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstdelone(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
/*	TODO
	//	void	c_lstdelone(s_list **a_lst, void (*del)(void *, t_size));
		c_putstr("\nft_lstdelone :\n");
		s_list *tmp = (*a_ilst)->next;
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
	//	void	c_lstdelone(s_list **a_lst, void (*del)(void *, t_size));
		c_putstr("\nft_lstdelone :\n");
		s_list *tmp = (*a_ilst)->next;
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



#ifdef			c_lstdel
void	print_test_lstdel(char const* test_name, int can_segfault,
		char const* expecting,
		s_list **a_lst,
		void (*del)(void *, t_size))
{
	s_timer t = {0};
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		c_lstdel(a_lst, del);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstdel(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
/*	TODO
	//	void	c_lstdel(s_list **a_lst, void (*del)(void *, t_size));
		c_putstr("\nft_lstdel :\n");	
		c_lstdel(mixed_list, c_delete);

		if (*mixed_list) // || *mixed_list || (*mixed_list)->item)
		{
			c_putstr_fd("Error deleting with c_lstdel\n", 2);
		}
		else
		{
			c_putstr("Function seems to work; should still check for leaks.\n");
		}
	//	void	c_lstdel(s_list **a_lst, void (*del)(void *, t_size));
		c_putstr("\nft_lstdel :\n");	
		c_lstdel(&tmp, c_delete);
		c_lstdel(a_slst, c_delete);
		if (*a_slst || tmp) // || *a_slst || (*a_ilst)->item || tmp->item)
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



#ifdef			c_lstsize
void	print_test_lstsize(char const* test_name, int can_segfault,
		char const* expecting,
		s_list *lst)
{
	s_timer t = {0};
	t_u32 result;
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		result = c_lstsize(lst);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstsize(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
/*	TODO
	//	int		c_lstsize(s_list *lst);
		c_putstr("\nft_lstsize : ");
		c_putnbr(c_lstsize(*mixed_list));
		c_putstr("\nExpected : 9\n");
*/
}
#endif



#ifdef			c_lstget
void	print_test_lstget(char const* test_name, int can_segfault,
		char const* expecting,
		s_list *lst,
		t_u32 index)
{
	s_timer t = {0};
	s_list *result;
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		result = c_lstget(lst, index);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstget(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}
#endif



#ifdef			c_lstfind
void	print_test_lstfind(char const* test_name, int can_segfault,
		char const* expecting,
		s_list *lst,
		void const* query)
{
	s_timer t = {0};
	s_list *result;
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		result = c_lstfind(lst, query);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstfind(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}
#endif



#ifdef			c_lstsub
void	print_test_lstsub(char const* test_name, int can_segfault,
		char const* expecting,
		s_list *lst,
		t_u32 index,
		t_u32 n)
{
	s_timer t = {0};
	s_list *result;
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		result = c_lstsub(lst, index, n);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstsub(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}
#endif



#ifdef			c_lstiter
void	print_test_lstiter(char const* test_name, int can_segfault,
		char const* expecting,
		s_list *lst,
		void (*f)(s_list *))
{
	s_timer t = {0};
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		c_lstiter(lst, f);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstiter(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
/*	TODO
//	c_lstiter(s_list *lst, void (*f)(s_list *elem));
	c_lstiter(*a_lst, c_lstiter_tolower);
	print_test_lst("lstiter", "lstiter", a_lst, expect_lower, FALSE);
*/
}
#endif



#ifdef			c_lstiteri
void	print_test_lstiteri(char const* test_name, int can_segfault,
		char const* expecting,
		s_list *lst,
		void (*f)(s_list *elem, t_u32 index))
{
	s_timer t = {0};
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		c_lstiteri(lst, f);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstiteri(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
/*	TODO
//	c_lstiteri(s_list *lst, void (*f)(s_list *elem));
	c_lstiteri(*a_lst, c_lstiter_tolower);
	print_test_lst("lstiteri", "lstiteri", a_lst, expect_lower, FALSE);
*/
}
#endif



#ifdef			c_lstmap
void	print_test_lstmap(char const* test_name, int can_segfault,
		char const* expecting,
		s_list *lst,
		s_list *(*f)(s_list *))
{
	s_timer t = {0};
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		c_lstmap(lst, f);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstmap(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
/*	TODO
//	s_list	*c_lstmap(s_list *lst, s_list *(*f)(s_list *elem));
	segfault = setjmp(restore); if (!segfault) *a_lst = c_lstmap(*a_lst, c_lstmap_toupper); else *a_lst = NULL;
	print_test_lst("lstmap", "lstmap", *a_lst, expect_upper, FALSE);
*/
}
#endif



#ifdef			c_lstmapi
void	print_test_lstmapi(char const* test_name, int can_segfault,
		char const* expecting,
		s_list *lst,
		s_list *(*f)(s_list *elem, t_u32 index))
{
	s_timer t = {0};
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		c_lstmapi(lst, f);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstmapi(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
/*	TODO
//	s_list	*c_lstmapi(s_list *lst, s_list *(*f)(s_list *elem));
	segfault = setjmp(restore); if (!segfault) *a_lst = c_lstmap(*a_lst, c_lstmap_toupper); else *a_lst = NULL;
	print_test_lst("lstmapi", "lstmapi", *a_lst, expect_upper, FALSE);
*/
}
#endif



#ifdef			c_lstfold
void	print_test_lstfold(char const* test_name, int can_segfault,
		char const* expecting)
{
	s_timer t = {0};
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		c_lstfold();
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstfold(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
	c_putstr("\nft_lstfold : ");
	n = 0;
	c_lstfold(*a_ilst, &n, c_add);
	c_putnbr(n);
	c_putstr("\nExpected : 1488\n");
}
#endif



#ifdef			c_lst_to_array
void	print_test_lst_to_array(char const* test_name, int can_segfault,
		char const* expecting,
		s_list const** a_lst)
{
	s_timer t = {0};
	void** result;
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		result = c_lst_to_array(a_lst);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lst_to_array(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}
#endif



#ifdef			c_lst_to_tuple
void	print_test_lst_to_tuple(char const* test_name, int can_segfault,
		char const* expecting,
		s_list const** a_lst)
{
	s_timer t = {0};
	s_tuple result;
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		result = c_lst_to_tuple(a_lst);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lst_to_tuple(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}
#endif



int		testsuite_list(void)
{
/*
	s_list **a_lst;
	s_list *lst_0;
	s_list *lst_1;
	s_list *lst_2;
	s_list *lst_3;
	s_list *lst_4;
	char const *expect[]       = { "Omae", " wa ", "mou ", "shindeiru.", NULL };
	char const *expect_upper[] = { "OMAE", " WA ", "MOU ", "SHINDEIRU.", NULL };
	char const *expect_lower[] = { "omae", " wa ", "mou ", "shindeiru.", NULL };
*/
	print_suite_title("list");

	print_nonstd();

#ifdef c_lstnew
	test_lstnew();
#endif
#ifdef c_lstadd
//	test_lstadd();
#endif
#ifdef c_lstappend
//	test_lstappend();
#endif
#ifdef c_lstinsert
//	test_lstinsert();
#endif
#ifdef c_lstcpy
//	test_lstcpy();
#endif
#ifdef c_lstpop
//	test_lstpop();
#endif
#ifdef c_lstdelone
//	test_lstdelone();
#endif
#ifdef c_lstdel
//	test_lstdel();
#endif
#ifdef c_lstsize
//	test_lstsize();
#endif
#ifdef c_lstget
//	test_lstget();
#endif
#ifdef c_lstfind
//	test_lstfind();
#endif
#ifdef c_lstsub
//	test_lstsub();
#endif
#ifdef c_lstiter
//	test_lstiter();
#endif
#ifdef c_lstmap
//	test_lstmap();
#endif
#ifdef c_lst_to_array
//	test_lst_to_array();
#endif
#ifdef c_lst_to_tuple
//	test_lst_to_tuple();
#endif

	return (OK);
}
