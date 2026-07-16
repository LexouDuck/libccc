
#include "libccc/math/algebra.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



s_matrix	Matrix_Duplicate(s_matrix const* matrix)
{
	if CCCERROR((matrix == NULL), ERROR_NULLPOINTER, NULL)
		return (MATRIX_NULL);
	return (Matrix(matrix->rows, matrix->cols, matrix->values));
}
