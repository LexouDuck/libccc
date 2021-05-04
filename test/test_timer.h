
#ifndef LIBCCC_TEST_TIMER_H
#define LIBCCC_TEST_TIMER_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include <time.h>

#include "libccc.h"



/*
** ************************************************************************** *|
**                                   Defines                                  *|
** ************************************************************************** *|
*/

typedef struct timespec s_time;

typedef struct timer
{
	s_time	start1;
	s_time	start2;
	s_time	end1;
	s_time	end2;
	s_time	time1;
	s_time	time2;
}				s_timer;



/*
** ************************************************************************** *|
**                           Timer utility functions                          *|
** ************************************************************************** *|
*/

void	timer_clock(s_time* t);

s_time	timer_getdiff(s_time start, s_time end);

t_s64	timer_compare(s_time a, s_time b);

void	print_timer_result(s_timer* timer, t_s64 compare);



#endif
