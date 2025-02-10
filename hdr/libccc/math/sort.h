/*============================================================================*\
||                                            ______________________________  ||
||  libccc/math/sort.h                       |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_MATH_SORT_H
#define __LIBCCC_MATH_SORT_H
/*!@group{libccc_math_sort,58,libccc/math/sort.h}
**
**	This header defines functions for sorting arrays/lists of any type.
**	There are several different kinds of sorting algorithms provided.
**	Some of these algorithms are better suited for arrays, others for lists -
**	some are better for small sizes, others for large sizes, etc.
**
**	TODO other algorithms than quicksort
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc/int.h"
#include "libccc/pointer.h"

HEADER_CPP

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

#define TYPE	void

void	QuickSort(TYPE* ptr, t_size count, t_size size,
	t_sint (*compare)(TYPE const*, TYPE const*));

TYPE*	QuickSort_New(TYPE const* ptr, t_size count, t_size size,
	t_sint (*compare)(TYPE const*, TYPE const*));

#define c_qsort	QuickSort



#define DEFINEFUNC_H_QUICKSORT(TYPE, NAME) \
void	QuickSort_Rec_##NAME(TYPE* array, t_uint start, t_uint end, \
	t_sint (*compare)(TYPE, TYPE), \
	t_bool (*exclude)(TYPE)); \
TYPE*	QuickSort_New_##NAME(TYPE const* array, t_uint items); \
void	QuickSort_##NAME(TYPE* array, t_uint items); \



#define DEFINEFUNC_C_QUICKSORT(TYPE, NAME, COMPARE, EXCLUDE) \
void	QuickSort_Rec_##NAME(TYPE* array, t_uint start, t_uint end, \
	t_sint (*compare)(TYPE, TYPE), \
	t_bool (*exclude)(TYPE)) \
{ \
	t_uint	pivot_id; \
	t_uint	rise_id; \
	t_uint	fall_id; \
	TYPE	pivot = array[start]; \
	if (start >= end || (exclude != NULL && exclude(pivot))) \
		return; \
	if (start == end - 1) \
	{ \
		if (compare(pivot, array[end]) <= 0) \
			Memory_Swap(array + start, array + end, sizeof(TYPE)); \
		return; \
	} \
	rise_id = start + 1; \
	fall_id = end; \
	while (rise_id < fall_id) \
	{ \
		while (rise_id <= end && compare(pivot, array[rise_id]) <= 0) \
		{ \
			++rise_id; \
		} \
		while (fall_id > start && compare(pivot, array[fall_id]) > 0) \
		{ \
			--fall_id; \
		} \
		if (rise_id < fall_id) \
			Memory_Swap(array + rise_id, array + fall_id, sizeof(TYPE)); \
	} \
	pivot_id = fall_id; \
	if (start != fall_id) \
		Memory_Swap(array + start, array + fall_id, sizeof(TYPE)); \
	if (pivot_id > start) \
		QuickSort_Rec_##NAME(array, start, pivot_id - 1, compare, exclude); \
	if (pivot_id < end) \
		QuickSort_Rec_##NAME(array, pivot_id + 1, end, compare, exclude); \
} \
 \
TYPE*	QuickSort_New_##NAME(TYPE const* array, t_uint items) \
{ \
	TYPE*	result = (TYPE*)Memory_Duplicate(array, items * sizeof(TYPE)); \
	if (items <= 1) \
		return (result); \
	QuickSort_Rec_##NAME(result, 0, items - 1, COMPARE, EXCLUDE); \
	return (result); \
} \
 \
void	QuickSort_##NAME(TYPE* array, t_uint items) \
{ \
	QuickSort_Rec_##NAME(array, 0, items - 1, COMPARE, EXCLUDE); \
} \



/*! @endgroup */
HEADER_END
#endif
