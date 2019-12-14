/*
** ************************************************************************** *|
**                              Includes & Defines                            *|
** ************************************************************************** *|
*/

#include "test.h"

/*
** ************************************************************************** *|
**                           Basic Utility Functions                          *|
** ************************************************************************** *|
*/

int	bool_equals(int a, int b)
{
	return (a == 0) ? (b == 0) : (b != 0);
}

int	str_equals(char const *str1, char const *str2)
{
	size_t i;

	if (str1 == str2)
		return (1);
	if (str1 && str2)
	{
		i = 0;
		while (str1[i] && str2[i])
		{
			if (str1[i] != str2[i])
				return (0);
			++i;
		}
		return (str1[0] == str2[0]);
	}
	return (0);
}

char *print_memory(void const *ptr, size_t length)
{
	char *result;
	t_u8 byte;
	char hi;
	char lo;

	if (ptr == NULL)
		return (NULL);
	if (str_equals((char const *)ptr, segstr))
		return (segstr);
	if (!(result = (char *)malloc(length * 3)))
		return (NULL);
	for (size_t i = 0; i < length; ++i)
	{
		byte = ((t_u8 const *)ptr)[i];
		hi = ((byte >> 4) & 0xF);
		lo = (byte & 0xF);
		result[i * 3 + 0] = hi + (hi < 10 ? '0' : 'A' - 10);
		result[i * 3 + 1] = lo + (lo < 10 ? '0' : 'A' - 10);
		result[i * 3 + 2] = (i + 1 == length) ? '\0' : ' ';
	}
	return (result);
}

char	*str_padleft(char const *str, char c, size_t length)
{
	char	*result;
	long	offset;
	size_t	i;

	if (!(result = (char *)malloc(length + 1)))
		return (NULL);
	offset = length - ft_strlen(str);
	i = 0;
	while (i < (size_t)offset)
	{
		result[i] = c;
		++i;
	}
	while (i < length)
	{
		result[i] = str[i - offset];
		++i;
	}
	result[length] = '\0';
	return (result);
}

char*	str_to_escape(char const* str)
{
	unsigned char HI_nibble;
	unsigned char LO_nibble;
	char*	result;
	size_t	index = 0;
	size_t	i = 0;

	if (!str || !(result = (char *)malloc(strlen(str) * 4)))
		return (NULL);
	while (str[index])
	{
		if (!isprint(str[index]))
		{
			result[i++] = '\\';
			switch (str[index])
			{
				case 0x07: result[i++] =  'a'; break; // Alert (Beep, Bell) (added in C89)[1]
				case 0x08: result[i++] =  'b'; break; // Backspace
				case 0x0C: result[i++] =  'f'; break; // Formfeed
				case 0x0A: result[i++] =  'n'; break; // Newline (Line Feed); see notes below
				case 0x0D: result[i++] =  'r'; break; // Carriage Return
				case 0x09: result[i++] =  't'; break; // Horizontal Tab
				case 0x0B: result[i++] =  'v'; break; // Vertical Tab
				case 0x5C: result[i++] = '\\'; break; // Backslash
				case 0x27: result[i++] = '\''; break; // Single quotation mark
				case 0x22: result[i++] = '\"'; break; // Double quotation mark
				case 0x3F: result[i++] =  '?'; break; // Question mark (used to avoid trigraphs)
				default: result[i++] = 'x'; // Hexadecimal char notation: \xFF
					HI_nibble = (str[index] & 0xF0) >> 4;
					LO_nibble = (str[index] & 0x0F);
					result[i++] = (HI_nibble < 10) ? (HI_nibble + '0') : (HI_nibble - 10 + 'A');
					result[i++] = (LO_nibble < 10) ? (LO_nibble + '0') : (LO_nibble - 10 + 'A');
				break;
			}
		}
		else result[i++] = str[index];
		++index;
	}
	result[i] = '\0';
	return (result);
}

/*
** ************************************************************************** *|
**                           Timer utility functions                          *|
** ************************************************************************** *|
*/

/*	There are a couple of different cross-platform clock possibilities:
**	- CLOCK_REALTIME	System-wide real-time clock. This clock returns the number of seconds and nanoseconds since the Epoch.
**						This clock can be set via clock_settime but doing so requires appropriate privileges, because it's linked to the system time.
**	- CLOCK_MONOTONIC 			Represents monotonic time since some unspecified starting point. This clock cannot be set.
**	- CLOCK_PROCESS_CPUTIME_ID 	High-resolution per-process timer from the CPU.
**	- CLOCK_THREAD_CPUTIME_ID 	Thread-specific CPU-time clock. 
*/
inline void	timer_clock(t_time* result)
{
	if (clock_gettime(CLOCK_MONOTONIC, result) == -1)
	{
		perror("clock_gettime() returned -1");
		exit(EXIT_FAILURE);
	}
}

/*	Define a 10e9 macro we use for nanosecond modulo */
#define BILLION 1000000000L
inline t_time timer_getdiff(t_time start, t_time end)
{
	t_time result;
	
	result.tv_sec = end.tv_sec - start.tv_sec;
	result.tv_nsec = end.tv_nsec - start.tv_nsec;
	if (result.tv_nsec >= BILLION)
	{
		result.tv_nsec -= BILLION;
		result.tv_sec++;
	}
	return (result);
}

/* Returns negative if 'a' is lower than 'b', positive if 'b' > 'a' and 0 if equal. */
inline t_s64 timer_compare(t_time a, t_time b)
{
	if (a.tv_sec == b.tv_sec)
		return (a.tv_nsec - b.tv_nsec);
	else
		return (a.tv_sec - b.tv_sec);
}

/* prints the result of a timer (and potentially a comparison with the secondary timer) */
void		print_timer_result(t_timer* t, t_s64 compare)
{
	char result1[64] = { 0 };
	char result2[64] = { 0 };

	t->time1 = timer_getdiff(t->start1, t->end1);
	if (t->time1.tv_nsec < 0 || t->time1.tv_nsec < 0)
		sprintf((char*)&result1, "SEGV");
	else sprintf((char*)&result1, "%lld.%.09ld", (long long)t->time1.tv_sec, t->time1.tv_nsec);

	printf(" [libft:");
	if (compare)
	{
		t->time2 = timer_getdiff(t->start2, t->end2);
		if (t->time2.tv_nsec < 0 || t->time2.tv_nsec < 0)
			sprintf((char*)&result2, "SEGV");
		else sprintf((char*)&result2, "%lld.%.09ld", (long long)t->time2.tv_sec, t->time2.tv_nsec);

		if ((t->time1.tv_sec >= 0 && t->time1.tv_nsec >= 0) ||
			(t->time2.tv_sec >= 0 && t->time2.tv_nsec >= 0))
			compare = timer_compare(t->time1, t->time2);
		else compare = 0;

		if (compare == 0)
			printf("%s, libc:", result1);
		else if (compare < 0)
			printf(C_GREEN"%s"C_RESET", libc:", result1);
		else
			printf(C_RED"%s"C_RESET", libc:", result1);

		printf("%s]", result2);
	}
	else printf("%s]", result1);
}

char	*s_to_str(t_s64 number)
{
	char	*result;
	t_u8	digits[MAXDIGIT_64BIT];
	t_u8	i;
	t_u64	n;

	n = number;
	if (number < 0)
		n = -n;
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 10;
		n /= 10;
	}
	if (!(result = (char *)malloc(i + 2)))
		return (NULL);
	result[0] = (number == 0) ? '0' : '-';
	n = 1;
	while (i--)
		result[n++] = '0' + digits[i];
	result[n] = '\0';
	return (number <= 0 ? result : result + 1);
}

char	*u_to_str(t_u64 number)
{
	char	*result;
	t_u8	digits[MAXDIGIT_64BIT];
	t_u8	i;
	t_u64	n;

	n = number;
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 10;
		n /= 10;
	}
	if (i == 0)
		digits[i++] = 0;
	if (!(result = (char *)malloc(i + 1)))
		return (NULL);
	n = 0;
	while (i--)
		result[n++] = '0' + digits[i];
	result[n] = '\0';
	return (result);
}

/*
** ************************************************************************** *|
**                              Testing Functions                             *|
** ************************************************************************** *|
*/

void	print_test(
		char const *test_name,
		char const *function,
		char const *result,
		char const *expect,
		int can_segfault,
		int error)
{
	if (test_name)
	{
		if (can_segfault & 1)
			 printf("\n%s - "C_YELLOW"can segfault"C_RESET, test_name);
		else printf("\n%s", test_name);
		printf(" -> ");
	}
	else printf(", ");
	if (error)
	{
		if (str_equals(expect, "(n/a)"))
			 printf(C_RED"TEST COULD NOT BE PERFORMED\n"C_RESET);
		else printf(C_RED"ERROR\n");
		if (function[0] == '_')
		{
			char *expected = str_padleft("Expected", ' ', strlen(function) + 2);
			printf(">ft%s: {%s}\n>%s: {%s}"C_RESET,
				function, result,
				expected, expect);
			free(expected);
		}
		else printf(">ft_%s: {%s}\n>   %s: {%s}"C_RESET,
				function, result,
				function, expect);
	}
	else printf(C_GREEN"OK!"C_RESET);
}



void	print_test_s8(
		char const *test_name,
		char const *function,
		t_s8 result,
		t_s8 expect,
		int can_segfault)
{
	int error;
	int result_segfault = can_segfault & (1 << 1);
	int expect_segfault = can_segfault & (1 << 2);
	
	if (result_segfault)
		error = (expect_segfault ? FALSE : TRUE);
	else if (expect_segfault)
		 error = TRUE;
	else error = (result != expect);

	print_test(test_name, function,
		(result_segfault ? segstr : s_to_str(result)),
		(expect_segfault ? segstr : s_to_str(expect)),
		can_segfault,
		error);
}

void	print_test_s16(
		char const *test_name,
		char const *function,
		t_s16 result,
		t_s16 expect,
		int can_segfault)
{
	int error;
	int result_segfault = can_segfault & (1 << 1);
	int expect_segfault = can_segfault & (1 << 2);
	
	if (result_segfault)
		error = (expect_segfault ? FALSE : TRUE);
	else if (expect_segfault)
		 error = TRUE;
	else error = (result != expect);

	print_test(test_name, function,
		(result_segfault ? segstr : s_to_str(result)),
		(expect_segfault ? segstr : s_to_str(expect)),
		can_segfault,
		error);
}

void	print_test_s32(
		char const *test_name,
		char const *function,
		t_s32 result,
		t_s32 expect,
		int can_segfault)
{
	int error;
	int result_segfault = can_segfault & (1 << 1);
	int expect_segfault = can_segfault & (1 << 2);
	
	if (result_segfault)
		error = (expect_segfault ? FALSE : TRUE);
	else if (expect_segfault)
		 error = TRUE;
	else error = (result != expect);

	print_test(test_name, function,
		(result_segfault ? segstr : s_to_str(result)),
		(expect_segfault ? segstr : s_to_str(expect)),
		can_segfault,
		error);
}

void	print_test_s64(
		char const *test_name,
		char const *function,
		t_s64 result,
		t_s64 expect,
		int can_segfault)
{
	int error;
	int result_segfault = can_segfault & (1 << 1);
	int expect_segfault = can_segfault & (1 << 2);
	
	if (result_segfault)
		error = (expect_segfault ? FALSE : TRUE);
	else if (expect_segfault)
		 error = TRUE;
	else error = (result != expect);

	print_test(test_name, function,
		(result_segfault ? segstr : s_to_str(result)),
		(expect_segfault ? segstr : s_to_str(expect)),
		can_segfault,
		error);
}



void	print_test_u8(
		char const *test_name,
		char const *function,
		t_u8 result,
		t_u8 expect,
		int can_segfault)
{
	int error;
	int result_segfault = can_segfault & (1 << 1);
	int expect_segfault = can_segfault & (1 << 2);
	
	if (result_segfault)
		error = (expect_segfault ? FALSE : TRUE);
	else if (expect_segfault)
		 error = TRUE;
	else error = (result != expect);

	print_test(test_name, function,
		(result_segfault ? segstr : u_to_str(result)),
		(expect_segfault ? segstr : u_to_str(expect)),
		can_segfault,
		error);
}

void	print_test_u16(
		char const *test_name,
		char const *function,
		t_u16 result,
		t_u16 expect,
		int can_segfault)
{
	int error;
	int result_segfault = can_segfault & (1 << 1);
	int expect_segfault = can_segfault & (1 << 2);
	
	if (result_segfault)
		error = (expect_segfault ? FALSE : TRUE);
	else if (expect_segfault)
		 error = TRUE;
	else error = (result != expect);

	print_test(test_name, function,
		(result_segfault ? segstr : u_to_str(result)),
		(expect_segfault ? segstr : u_to_str(expect)),
		can_segfault,
		error);
}

void	print_test_u32(
		char const *test_name,
		char const *function,
		t_u32 result,
		t_u32 expect,
		int can_segfault)
{
	int error;
	int result_segfault = can_segfault & (1 << 1);
	int expect_segfault = can_segfault & (1 << 2);
	
	if (result_segfault)
		error = (expect_segfault ? FALSE : TRUE);
	else if (expect_segfault)
		 error = TRUE;
	else error = (result != expect);

	print_test(test_name, function,
		(result_segfault ? segstr : u_to_str(result)),
		(expect_segfault ? segstr : u_to_str(expect)),
		can_segfault,
		error);
}

void	print_test_u64(
		char const *test_name,
		char const *function,
		t_u64 result,
		t_u64 expect,
		int can_segfault)
{
	int error;
	int result_segfault = can_segfault & (1 << 1);
	int expect_segfault = can_segfault & (1 << 2);
	
	if (result_segfault)
		error = (expect_segfault ? FALSE : TRUE);
	else if (expect_segfault)
		 error = TRUE;
	else error = (result != expect);

	print_test(test_name, function,
		(result_segfault ? segstr : u_to_str(result)),
		(expect_segfault ? segstr : u_to_str(expect)),
		can_segfault,
		error);
}



void	print_test_size(
		char const *test_name,
		char const *function,
		size_t result,
		size_t expect,
		int can_segfault)
{
	int error;
	int result_segfault = can_segfault & (1 << 1);
	int expect_segfault = can_segfault & (1 << 2);
	
	if (result_segfault)
		error = (expect_segfault ? FALSE : TRUE);
	else if (expect_segfault)
		 error = TRUE;
	else error = (result != expect);

	print_test(test_name, function,
		(result_segfault ? segstr : u_to_str(result)),
		(expect_segfault ? segstr : u_to_str(expect)),
		can_segfault,
		error);
}



void	print_test_bool(
		char const *test_name,
		char const *function,
		t_bool result,
		t_bool expect,
		int can_segfault)
{
	int error;
	int result_segfault = can_segfault & (1 << 1);
	int expect_segfault = can_segfault & (1 << 2);
	
	if (result_segfault)
		error = (expect_segfault ? FALSE : TRUE);
	else if (expect_segfault)
		 error = TRUE;
	else error = (result != expect);

	print_test(test_name, function,
		(result_segfault ? segstr : u_to_str(result)),
		(expect_segfault ? segstr : u_to_str(expect)),
		can_segfault,
		error);
}



void	print_test_f32(
		char const *test_name,
		char const *function,
		t_f32 result,
		t_f32 expect,
		int can_segfault)
{
	int error;
	int result_segfault = can_segfault & (1 << 1);
	int expect_segfault = can_segfault & (1 << 2);
	static const size_t size = 32;
	char str_result[size];
	char str_expect[size];
	
	if (result_segfault)
		error = (expect_segfault ? FALSE : TRUE);
	else if (expect_segfault)
		 error = TRUE;
	else error = (result != expect);

	if (isnan(result) && isnan(expect))
		error = FALSE;

	snprintf(str_result, size, "%f", result);
	snprintf(str_expect, size, "%f", expect);
	print_test(test_name, function,
		(result_segfault ? segstr : str_result),
		(expect_segfault ? segstr : str_expect),
		can_segfault,
		error);
}

void	print_test_f64(
		char const *test_name,
		char const *function,
		t_f64 result,
		t_f64 expect,
		int can_segfault)
{
	int error;
	int result_segfault = can_segfault & (1 << 1);
	int expect_segfault = can_segfault & (1 << 2);
	static const size_t size = 64;
	char str_result[size];
	char str_expect[size];
	
	if (result_segfault)
		error = (expect_segfault ? FALSE : TRUE);
	else if (expect_segfault)
		 error = TRUE;
	else error = (result != expect);

	if (isnan(result) && isnan(expect))
		error = FALSE;

	snprintf(str_result, size, "%f", result);
	snprintf(str_expect, size, "%f", expect);
	print_test(test_name, function,
		(result_segfault ? segstr : str_result),
		(expect_segfault ? segstr : str_expect),
		can_segfault,
		error);
}



void	print_test_mem(
		char const *test_name,
		char const *function,
		void const *result,
		void const *expect,
		size_t length,
		int can_segfault)
{
	int error;

	error = (result && expect) ?
		(memcmp(result, expect, length) != 0) :
		(result != expect);

	print_test(test_name, function,
		print_memory(result, length),
		print_memory(expect, length),
		can_segfault,
		error);
}



void	print_test_str(
		char const *test_name,
		char const *function,
		char const *result,
		char const *expect,
		int can_segfault)
{
	print_test(test_name, function,
		result,
		expect,
		can_segfault,
		!str_equals(result, expect));
}



void	print_test_strls(
		char const *test_name,
		char const *function,
		char const **result,
		char const **expect,
		int can_segfault)
{
	int error = FALSE;
	int length;
	size_t i;
	char *str_result;
	char *str_expect;

	for (int i = 0; result[i] && expect[i]; ++i)
	{
		if (!str_equals(result[i], expect[i]))
		{
			error = TRUE;
			break;
		}
	}
	length = 0;
	for (i = 0; result[i]; ++i)
	{
		length += strlen(result[i]);
	}
	if (!(str_result = (char*)malloc(length + (i - 1) * 2)))
		return;
	length = 0;
	for (i = 0; result[i]; ++i)
	{
		if (i != 0)
		{
			str_result[length++] = ',';
			str_result[length++] = ' ';
		}
		strcpy(str_result + length, result[i]);
		length += strlen(result[i]);
	}

	for (i = 0; expect[i]; ++i) length += strlen(expect[i]);
	if (!(str_expect = (char*)malloc(length + (i - 1) * 2)))
		return;
	length = 0;
	for (i = 0; expect[i]; ++i)
	{
		if (i != 0)
		{
			str_expect[length++] = ',';
			str_expect[length++] = ' ';
		}
		strcpy(str_expect + length, expect[i]);
		length += strlen(expect[i]);
	}

	print_test(test_name, function,
		str_result,
		str_expect,
		can_segfault,
		error);

	if (str_result) free(str_result);
	if (str_expect) free(str_expect);
}

void	print_test_lst(
		char const *test_name,
		char const *function,
		t_list const *result,
		char const *expect[],
		int can_segfault)
{
	int error = FALSE;
	if (test_name)
	{
		if (can_segfault)
			 printf("\n%s - "C_YELLOW"can segfault"C_RESET, test_name);
		else printf("\n%s", test_name);
		printf(" -> ");
	}
	else printf(", ");
	t_list *lst = (t_list *)result;
	t_u32 i = 0;
	if (lst)
	{
		while (expect[i])
		{
			if ((lst->item && expect[i]) ?
				(memcmp(lst->item, expect[i], lst->item_size) != 0) :
				(lst->item != expect[i]))
				error = TRUE;
			lst = lst->next;
			++i;
		}
	}
	else if (expect)
		error = TRUE;
	if (error)
	{
		printf(C_RED"ERROR\n");
		lst = (t_list *)result;
		printf(">ft_%s: [", function);
		while (lst)
		{
			printf("%s{%s}", (lst == result ? "" : ", "), lst->item);
			lst = lst->next;
		}
		i = 0;
		printf("]\n> Expected: [");
		while (expect[i])
		{
			printf("%s{%s}", (i == 0 ? "" : ", "), expect[i]);
			++i;
		}
		printf("]\n"C_RESET);
	}
	else printf(C_GREEN"OK!"C_RESET);
}
