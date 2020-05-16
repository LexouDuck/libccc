
#include "libft_list.h"

#include "test.h"



/*
**	s_list	*ft_lstnew(void const *item, t_size item_size);
*/
void	print_test_lstnew(char const* test_name, int can_segfault,
		char const* expecting,
		void* item,
		t_size item_size)
{
	t_size expect_size = expecting ? strlen(expecting) + 1 : 0;
	TEST_PERFORM_RESULT_TYPE(s_list*, lstnew, item, item_size);
	print_test_size(test_name, "_lstnew->item_size", result_libft->item_size, expect_size, can_segfault);
	print_test_str(NULL,       "_lstnew->item",      result_libft->item,      expecting,   can_segfault);
	print_timer_result(&t, FALSE);
	if (result_libft) free(result_libft);
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



/*
**	void	ft_lstadd(s_list **alst, s_list *elem);
*/
void	print_test_lstadd(char const* test_name, int can_segfault,
		char const* expecting,
		s_list** alst,
		s_list* elem)
{
	s_timer t = {0};
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		ft_lstadd(alst, elem);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstadd(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
/*	TODO
	a_lst = &lst_3;
	ft_lstadd(a_lst, lst_2);
	ft_lstadd(a_lst, lst_1);
	ft_lstadd(a_lst, lst_0);
	print_test_lst("lstadd", "lstadd", lst_0, expect, FALSE);
*/
}



/*
**	void	ft_lstappend(s_list **alst, s_list *elem);
*/
void	print_test_lstappend(char const* test_name, int can_segfault,
		char const* expecting,
		s_list **alst, s_list *elem)
{
	s_timer t = {0};
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		ft_lstappend(alst, elem);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstappend(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
/*	TODO
	//	void	ft_lstappend(s_list **alst, s_list *new_elem);
		s_list	**mixed_list;
		mixed_list = a_slst;
		ft_putstr("\nft_lstappend (mind the little endianness and the fact that lst was listiter(abs)) :\n");
		ft_lstappend(mixed_list, *a_ilst);
		ft_lstiter(*mixed_list, ft_puthex_llstelem);
		ft_putstr("\nExpected:\n4F 6D 61 65 00\n20 77 61 20 00\n6D 6F 75 20 00\n73 68 69 6E 64 65 69 72 75 2E 00\n00 00 00 00\n00 00 00 00\n9A 02 00 00\n09 03 00 00\n2D 00 00 00\n");
*/
}



/*
**	void	ft_lstinsert(s_list **alst, s_list *elem, t_u32 index);
*/
void	print_test_lstinsert(char const* test_name, int can_segfault,
		char const* expecting,
		s_list **alst,
		s_list *elem,
		t_u32 index)
{
	s_timer t = {0};
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		ft_lstinsert(alst, elem, index);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstinsert(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



/*
**	s_list	*ft_lstcpy(s_list *lst);
*/
void	print_test_lstcpy(char const* test_name, int can_segfault,
		char const* expecting,
		s_list *lst)
{
	s_timer t = {0};
	s_list *result;
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		result = ft_lstcpy(lst);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstcpy(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



/*
**	void	ft_lstpop(s_list **alst, void (*del)(void *, t_size));
*/
void	print_test_lstpop(char const* test_name, int can_segfault,
		char const* expecting,
		s_list **alst,
		void (*del)(void *, t_size))
{
	s_timer t = {0};
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		ft_lstpop(alst, del);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstpop(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



/*
**	void	ft_lstdelone(s_list **alst, void (*del)(void *, t_size));
*/
void	print_test_lstdelone(char const* test_name, int can_segfault,
		char const* expecting,
		s_list **alst,
		void (*del)(void *, t_size))
{
	s_timer t = {0};
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		ft_lstdelone(alst, del);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstdelone(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
/*	TODO
	//	void	ft_lstdelone(s_list **alst, void (*del)(void *, t_size));
		ft_putstr("\nft_lstdelone :\n");
		s_list *tmp = (*a_ilst)->next;
		ft_lstdelone(a_ilst, ft_delete);
		//alternative fix without lstget => (*mixed_list)->next->next->next->next = 0;
		ft_lstget(*mixed_list, 3)->next = 0;
		ft_lstappend(mixed_list, tmp);
		ft_lstiter(*mixed_list, ft_puthex_llstelem);
		ft_putstr("\nExpected:\n4F 6D 61 65 00\n20 77 61 20 00\n6D 6F 75 20 00\n73 68 69 6E 64 65 69 72 75 2E 00\n00 00 00 00\n9A 02 00 00\n09 03 00 00\n2D 00 00 00\n");

		if (*a_ilst) // || *a_ilst || (*a_ilst)->item)
		{
			ft_putstr_fd("Error deleting with ft_lstdel\n", 2);
		}
		else
		{
			ft_putstr("Function seems to work; should still check for leaks.\n");
		}
	//	void	ft_lstdelone(s_list **alst, void (*del)(void *, t_size));
		ft_putstr("\nft_lstdelone :\n");
		s_list *tmp = (*a_ilst)->next;
		ft_lstdelone(a_ilst, ft_delete);
		ft_lstiter(tmp, ft_puthex_llstelem);
		ft_putstr("\nExpected:\n00 00 00 00\n9A 02 00 00\n09 03 00 00\n2D 00 00 00\n");
		if (*a_ilst) // || *a_ilst || (*a_ilst)->item)
		{
			ft_putstr_fd("Error deleting with ft_lstdel\n", 2);
		}
		else
		{
			ft_putstr("Function seems to work; should still check for leaks.\n");
		}
*/
}



/*
**	void	ft_lstdel(s_list **alst, void (*del)(void *, t_size));
*/
void	print_test_lstdel(char const* test_name, int can_segfault,
		char const* expecting,
		s_list **alst,
		void (*del)(void *, t_size))
{
	s_timer t = {0};
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		ft_lstdel(alst, del);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstdel(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
/*	TODO
	//	void	ft_lstdel(s_list **alst, void (*del)(void *, t_size));
		ft_putstr("\nft_lstdel :\n");	
		ft_lstdel(mixed_list, ft_delete);

		if (*mixed_list) // || *mixed_list || (*mixed_list)->item)
		{
			ft_putstr_fd("Error deleting with ft_lstdel\n", 2);
		}
		else
		{
			ft_putstr("Function seems to work; should still check for leaks.\n");
		}
	//	void	ft_lstdel(s_list **alst, void (*del)(void *, t_size));
		ft_putstr("\nft_lstdel :\n");	
		ft_lstdel(&tmp, ft_delete);
		ft_lstdel(a_slst, ft_delete);
		if (*a_slst || tmp) // || *a_slst || (*a_ilst)->item || tmp->item)
		{
			ft_putstr_fd("Error deleting with ft_lstdel\n", 2);
		}
		else
		{
			ft_putstr("Function seems to work; should still check for leaks.\n");
		}
*/
}



/*
**	t_u32	ft_lstsize(s_list *lst);
*/
void	print_test_lstsize(char const* test_name, int can_segfault,
		char const* expecting,
		s_list *lst)
{
	s_timer t = {0};
	t_u32 result;
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		result = ft_lstsize(lst);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstsize(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
/*	TODO
	//	int		ft_lstsize(s_list *lst);
		ft_putstr("\nft_lstsize : ");
		ft_putnbr(ft_lstsize(*mixed_list));
		ft_putstr("\nExpected : 9\n");
*/
}



/*
**	s_list	*ft_lstget(s_list *lst, t_u32 index);
*/
void	print_test_lstget(char const* test_name, int can_segfault,
		char const* expecting,
		s_list *lst,
		t_u32 index)
{
	s_timer t = {0};
	s_list *result;
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		result = ft_lstget(lst, index);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstget(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



/*
**	s_list	*ft_lstfind(s_list *lst, void const* query);
*/
void	print_test_lstfind(char const* test_name, int can_segfault,
		char const* expecting,
		s_list *lst,
		void const* query)
{
	s_timer t = {0};
	s_list *result;
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		result = ft_lstfind(lst, query);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstfind(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



/*
**	s_list	*ft_lstsub(s_list *lst, t_u32 index, t_u32 n);
*/
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
		result = ft_lstsub(lst, index, n);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstsub(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



/*
**	void	ft_lstiter(s_list *lst, void (*f)(s_list *elem));
*/
void	print_test_lstiter(char const* test_name, int can_segfault,
		char const* expecting,
		s_list *lst,
		void (*f)(s_list *))
{
	s_timer t = {0};
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		ft_lstiter(lst, f);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstiter(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
/*	TODO
//	ft_lstiter(s_list *lst, void (*f)(s_list *elem));
	ft_lstiter(*a_lst, ft_lstiter_tolower);
	print_test_lst("lstiter", "lstiter", a_lst, expect_lower, FALSE);
*/
}

/*
**	void	ft_lstiteri(s_list *lst, void (*f)(s_list *elem, t_u32 index));
*/
void	print_test_lstiteri(char const* test_name, int can_segfault,
		char const* expecting,
		s_list *lst,
		void (*f)(s_list *elem, t_u32 index))
{
	s_timer t = {0};
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		ft_lstiteri(lst, f);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstiteri(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
/*	TODO
//	ft_lstiteri(s_list *lst, void (*f)(s_list *elem));
	ft_lstiteri(*a_lst, ft_lstiter_tolower);
	print_test_lst("lstiteri", "lstiteri", a_lst, expect_lower, FALSE);
*/
}



/*
**	s_list	*ft_lstmap(s_list *lst, s_list *(*f)(s_list *elem));
*/
void	print_test_lstmap(char const* test_name, int can_segfault,
		char const* expecting,
		s_list *lst,
		s_list *(*f)(s_list *))
{
	s_timer t = {0};
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		ft_lstmap(lst, f);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstmap(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
/*	TODO
//	s_list	*ft_lstmap(s_list *lst, s_list *(*f)(s_list *elem));
	segfault = setjmp(restore); if (!segfault) *a_lst = ft_lstmap(*a_lst, ft_lstmap_toupper); else *a_lst = NULL;
	print_test_lst("lstmap", "lstmap", *a_lst, expect_upper, FALSE);
*/
}

/*
**	s_list	*ft_lstmapi(s_list *lst, s_list *(*f)(s_list *elem, t_u32 index));
*/
void	print_test_lstmapi(char const* test_name, int can_segfault,
		char const* expecting,
		s_list *lst,
		s_list *(*f)(s_list *elem, t_u32 index))
{
	s_timer t = {0};
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		ft_lstmapi(lst, f);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lstmapi(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
/*	TODO
//	s_list	*ft_lstmapi(s_list *lst, s_list *(*f)(s_list *elem));
	segfault = setjmp(restore); if (!segfault) *a_lst = ft_lstmap(*a_lst, ft_lstmap_toupper); else *a_lst = NULL;
	print_test_lst("lstmapi", "lstmapi", *a_lst, expect_upper, FALSE);
*/
}



/*
**	void	**ft_lst_to_array(s_list **alst);
*/
void	print_test_lst_to_array(char const* test_name, int can_segfault,
		char const* expecting,
		s_list **alst)
{
	s_timer t = {0};
	void **result;
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		result = ft_lst_to_array(alst);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lst_to_array(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



/*
**	s_tuple	*ft_lst_to_tuple(s_list **alst, s_tuple *tuple);
*/
void	print_test_lst_to_tuple(char const* test_name, int can_segfault,
		char const* expecting,
		s_list **alst,
		s_tuple *tuple)
{
	s_timer t = {0};
	s_tuple* result;
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		result = ft_lst_to_tuple(alst, tuple);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lst_to_tuple(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}












/*
**	
*/
void	print_test_lst_(char const* test_name, int can_segfault,
		char const* expecting)
{
	s_timer t = {0};
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
//		ft_lst_();
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_timer_result(&t, FALSE);
}
void	test_lst_(void)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



int		tess_list(void)
{
	s_list **a_lst;
	s_list *lst_0;
	s_list *lst_1;
	s_list *lst_2;
	s_list *lst_3;
	s_list *lst_4;
	char const *expect[]       = { "Omae", " wa ", "mou ", "shindeiru.", NULL };
	char const *expect_upper[] = { "OMAE", " WA ", "MOU ", "SHINDEIRU.", NULL };
	char const *expect_lower[] = { "omae", " wa ", "mou ", "shindeiru.", NULL };

	print_suite_title("list");

	print_nonstd();

	test_lstnew();

/*
	//	void	*ft_lstfold(s_list *lst, void *acc, void *(*f)(void *, void *));
		ft_putstr("\nft_lstfold : ");
		n = 0;
		ft_lstfold(*a_ilst, &n, ft_add);
		ft_putnbr(n);
		ft_putstr("\nExpected : 1488\n");
*/
	return (OK);
}
