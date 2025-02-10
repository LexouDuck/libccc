
#include "libccc.h"
#include "libccc/memory.h"
#include "libccc/pointer.h"
#include "libccc/math/sort.h"



#define TYPE	void



static
void	QuickSort_Rec(TYPE* array, t_size count, t_size size,
	t_sint (*compare)(TYPE const*, TYPE const*))
{
	t_uint	pivot_id;
	t_uint	rise_id;
	t_uint	fall_id;
	t_uint	start = 0;
	t_uint	end = count - 1;
	TYPE*	pivot = (t_u8*)array + (start * size);
	if (start >= end) // || (exclude != NULL && exclude(pivot)))
		return;
	if (start == end - 1)
	{
		if (compare(pivot, (t_u8*)array + (end * size)) <= 0)
			Memory_Swap(
				(t_u8*)array + (start * size),
				(t_u8*)array + (end * size),
				size);
		return;
	}
	rise_id = start + 1;
	fall_id = end;
	while (rise_id < fall_id)
	{
		while (rise_id <= end && compare(pivot, (t_u8*)array + (rise_id * size)) <= 0)
		{
			++rise_id;
		}
		while (fall_id > start && compare(pivot, (t_u8*)array + (fall_id * size)) > 0)
		{
			--fall_id;
		}
		if (rise_id < fall_id)
			Memory_Swap(
				(t_u8*)array + (rise_id * size),
				(t_u8*)array + (fall_id * size),
				size);
	}
	pivot_id = fall_id;
	if (start != fall_id)
		Memory_Swap(
			(t_u8*)array + (start * size),
			(t_u8*)array + (fall_id * size),
			size);

	if (pivot_id > start)
		QuickSort_Rec(
			(t_u8*)array + (start * size),
			pivot_id - 1,
			size, compare);
	if (pivot_id < end)
		QuickSort_Rec(
			(t_u8*)array + (pivot_id + 1) * size,
			count - (pivot_id + 1),
			size, compare);
}



void	QuickSort(TYPE* array, t_size count, t_size size,
	t_sint (*compare)(TYPE const*, TYPE const*))
{
	QuickSort_Rec(array, count, size, compare);
}



TYPE*	QuickSort_New(TYPE const* array, t_size count, t_size size,
	t_sint (*compare)(TYPE const*, TYPE const*))
{
	TYPE*	result = (TYPE*)Memory_Duplicate(array, count * size);
	if (count <= 1)
		return (result);
	QuickSort_Rec(result, count, size, compare);
	return (result);
}
