
#ifndef LIBFT_TEST_H
#define LIBFT_TEST_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <time.h>
#include <math.h>

#include "../libft.h"
#include "../libft_memory.h"
#include "../libft_char.h"
#include "../libft_string.h"
#include "../libft_stringarray.h"
#include "../libft_convert.h"
#include "../libft_list.h"
#include "../libft_math.h"
#include "../libft_stat.h"
#include "../libft_random.h"
#include "../libft_vlq.h"
#include "../libft_io.h"

/*
** ************************************************************************** *|
**                                   Defines                                  *|
** ************************************************************************** *|
*/

/*
** This define makes the program perform overflowing number tests on the libft_convert functions
#define __TEST_OVERFLOW
*/

/*
**	This define is used as the 'can_segfault' arg for certain 'int' tests,
**	so as to have those tests expect a "(segfault)" result.
*/
#define SEGV	(TRUE | (1 << 2))

/*
** ************************************************************************** *|
**                              Segfault handling                             *|
** ************************************************************************** *|
*/

extern char* nullstr;
extern char* segstr;
struct sigaction sig;
int			segfault;
jmp_buf 	restore;

void		segfault_handler(int sig, siginfo_t *info, void *ptr);

/*
** ************************************************************************** *|
**                           Timer utility functions                          *|
** ************************************************************************** *|
*/
typedef struct timespec t_time;

typedef struct	s_timer
{
    t_time	start1;
    t_time	start2;
    t_time	end1;
    t_time	end2;
    t_time	time1;
    t_time	time2;
}				t_timer;

void	timer_clock(t_time* t);
t_time	timer_getdiff(t_time start, t_time end);
t_s64	timer_compare(t_time a, t_time b);
void	print_timer_result(t_timer* timer, t_s64 compare);

/*
** ************************************************************************** *|
**                              Testing Functions                             *|
** ************************************************************************** *|
*/

extern char const* test1; extern size_t const test1_len; 
extern char const* test2; extern size_t const test2_len; 
extern char const* test3; extern size_t const test3_len; 

void	print_nonstd(void);

int		test_memory(void);
int		test_char(void);
int		test_string(void);
int		test_stringarray(void);
int		test_convert(void);
int		test_color(void);
int		test_list(void);
int		test_math(void);
int		test_stat(void);
int		test_random(void);
int		test_vlq(void);
int		test_io(void);

/*
** ************************************************************************** *|
**                              Utility Functions                             *|
** ************************************************************************** *|
*/

int		bool_equals(int a, int b);

int		str_equals(char const* str1, char const* str2);

char	*print_memory(void const* ptr, size_t length);

char	*str_padleft(char const* str, char c, size_t length);

char*	str_to_escape(char const* str);



void	print_test_s8(char const *test_name, char const *function, t_s8 result, t_s8 expect, int can_segfault);
void	print_test_s16(char const *test_name, char const *function, t_s16 result, t_s16 expect, int can_segfault);
void	print_test_s32(char const *test_name, char const *function, t_s32 result, t_s32 expect, int can_segfault);
void	print_test_s64(char const *test_name, char const *function, t_s64 result, t_s64 expect, int can_segfault);

void	print_test_u8(char const *test_name, char const *function, t_u8 result, t_u8 expect, int can_segfault);
void	print_test_u16(char const *test_name, char const *function, t_u16 result, t_u16 expect, int can_segfault);
void	print_test_u32(char const *test_name, char const *function, t_u32 result, t_u32 expect, int can_segfault);
void	print_test_u64(char const *test_name, char const *function, t_u64 result, t_u64 expect, int can_segfault);

void	print_test_f32(char const *test_name, char const *function, t_f32 result, t_f32 expect, int can_segfault);
void	print_test_f64(char const *test_name, char const *function, t_f64 result, t_f64 expect, int can_segfault);

void	print_test_size(char const *test_name, char const *function, size_t result, size_t expect, int can_segfault);
void	print_test_bool(char const *test_name, char const *function, t_bool result, t_bool expect, int can_segfault);

void	print_test_str(char const *test_name, char const *function, char const *result, char const *expect, int can_segfault);
void	print_test_mem(char const *test_name, char const *function, void const *result, void const *expect, size_t length, int can_segfault);

void	print_test_strls(char const *test_name, char const *function, char const **result, char const **expect, int can_segfault);

void	print_test_lst(char const *test_name, char const *function, t_list const *result, char const *expect[], int can_segfault);

#endif
