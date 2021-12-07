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
/*!@group{libccc_math_sort}
**
**	This header defines functions for sorting arrays/lists of any type.
**	There are several different kinds of sorting algorithms provided.
**	Some of these algorithms are better suited for arrays, others for lists -
**	some are better for small sizes, others for large sizes, etc.
**
**	TODO other algorithms than quicksort
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc/int.h"
#include "libccc/pointer.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

#define DEFINEFUNC_H_QUICKSORT(TYPE, COMPARE) \
void	QuickSort_Rec_##COMPARE(TYPE* array, t_sint (*compare)(TYPE, TYPE), t_size start, t_size end);	\
TYPE*	QuickSort_New_##COMPARE(TYPE const* array, t_size items);										\
void	QuickSort_##COMPARE(TYPE* array, t_size items);													\



#define DEFINEFUNC_C_QUICKSORT(TYPE, COMPARE) \
void	QuickSort_Rec_##COMPARE(TYPE* array, t_sint (*compare)(TYPE, TYPE), t_size start, t_size end)	\
{																										\
	t_size	pivot_id;																					\
	t_size	rise_id;																					\
	t_size	fall_id;																					\
	TYPE	pivot = array[start];																		\
	if (start >= end)																					\
		return;																							\
	if (start == end - 1)																				\
	{																									\
		if (compare(pivot, array[end]) <= 0)															\
			Memory_Swap(array + start, array + end, sizeof(TYPE));										\
		return;																							\
	}																									\
	rise_id = start + 1;																				\
	fall_id = end;																						\
	while (rise_id < fall_id)																			\
	{																									\
		while (rise_id <= end && compare(pivot, array[rise_id]) <= 0)									\
			++rise_id;																					\
		while (fall_id > start && compare(pivot, array[fall_id]) > 0)									\
			--fall_id;																					\
		if (rise_id < fall_id)																			\
			Memory_Swap(array + rise_id, array + fall_id, sizeof(TYPE));								\
	}																									\
	pivot_id = fall_id;																					\
	if (start != fall_id)																				\
		Memory_Swap(array + start, array + fall_id, sizeof(TYPE));										\
	if (pivot_id > start)	QuickSort_Rec_##COMPARE(array, compare, start, pivot_id - 1);				\
	if (pivot_id < end)		QuickSort_Rec_##COMPARE(array, compare, pivot_id + 1, end);					\
}																										\
																										\
TYPE*	QuickSort_New_##COMPARE(TYPE const* array, t_size items)										\
{																										\
	TYPE*	result = Memory_Duplicate(array, items * sizeof(TYPE));										\
	if (items <= 1)																						\
		return (result);																				\
	QuickSort_Rec_##COMPARE(result, COMPARE, 0, items - 1);												\
	return (result);																					\
}																										\
																										\
void	QuickSort_##COMPARE(TYPE* array, t_size items)													\
{																										\
	QuickSort_Rec_##COMPARE(array, COMPARE, 0, items - 1);												\
}																										\



/*! @endgroup */
HEADER_END
#endif
