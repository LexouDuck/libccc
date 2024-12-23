
#ifndef LIBCCC_TEST_TIMER_H
#define LIBCCC_TEST_TIMER_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include <time.h>



/*
** ************************************************************************** *|
**                                   Defines                                  *|
** ************************************************************************** *|
*/

typedef struct timespec s_time;

typedef struct timer
{
	s_time	result_start;
	s_time	result_end;
	s_time	result_time;

	s_time	expect_start;
	s_time	expect_end;
	s_time	expect_time;

}	s_timer;



/*
** ************************************************************************** *|
**                           Timer utility functions                          *|
** ************************************************************************** *|
*/

void	timer_clock(s_time* t);

s_time	timer_getdiff(s_time start, s_time end);

int		timer_compare(s_time a, s_time b);

void	print_timer_result(s_timer* timer, int compare);



#endif
