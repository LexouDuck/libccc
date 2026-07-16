
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



//! Computes the row-major flat index for the given `coords`, or returns `FALSE` if any coordinate is out of bounds
static
t_bool	Tensor_GetIndex(s_tensor const* tensor, t_uint const* coords, t_uint* index)
{
	t_uint i;

	*index = 0;
	if (tensor->order == 0)
		return (TRUE);
	if CCCERROR((coords == NULL), ERROR_NULLPOINTER, 
		"array of coordinates given is NULL")
		return (FALSE);
	for (i = 0; i < tensor->order; ++i)
	{
		if CCCERROR((coords[i] >= tensor->dims[i]), ERROR_INDEX2LARGE, 
			"coordinate is beyond the size of the corresponding tensor axis")
			return (FALSE);
		*index = (*index * tensor->dims[i]) + coords[i];
	}
	return (TRUE);
}



t_float	Tensor_Get(s_tensor const* tensor, t_uint const* coords)
{
	t_uint index;

	if CCCERROR((tensor == NULL || tensor->values == NULL), ERROR_NULLPOINTER, NULL)
		return (0);
	if (!Tensor_GetIndex(tensor, coords, &index))
		return (0);
	return (tensor->values[index]);
}



void	Tensor_Set(s_tensor* tensor, t_uint const* coords, t_float value)
{
	t_uint index;

	if CCCERROR((tensor == NULL || tensor->values == NULL), ERROR_NULLPOINTER, NULL)
		return;
	if (!Tensor_GetIndex(tensor, coords, &index))
		return;
	tensor->values[index] = value;
}
