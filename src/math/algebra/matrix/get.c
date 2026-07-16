
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



t_float	Matrix_Get(s_matrix const* matrix, t_uint row, t_uint col)
{
	if CCCERROR((matrix == NULL || matrix->values == NULL), ERROR_NULLPOINTER, NULL)
		return (0);
	if CCCERROR((row >= matrix->rows), ERROR_INDEX2LARGE, 
		"row index is beyond the amount of rows of the matrix")
		return (0);
	if CCCERROR((col >= matrix->cols), ERROR_INDEX2LARGE, 
		"column index is beyond the amount of columns of the matrix")
		return (0);
	return (matrix->values[row * matrix->cols + col]);
}



void	Matrix_Set(s_matrix* matrix, t_uint row, t_uint col, t_float value)
{
	if CCCERROR((matrix == NULL || matrix->values == NULL), ERROR_NULLPOINTER, NULL)
		return;
	if CCCERROR((row >= matrix->rows), ERROR_INDEX2LARGE, 
		"row index is beyond the amount of rows of the matrix")
		return;
	if CCCERROR((col >= matrix->cols), ERROR_INDEX2LARGE, 
		"column index is beyond the amount of columns of the matrix")
		return;
	matrix->values[row * matrix->cols + col] = value;
}
