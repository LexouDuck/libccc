
#include "libccc/math/algebra.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



void	Matrix_Free(s_matrix* matrix)
{
	if CCCERROR((matrix == NULL), ERROR_NULLPOINTER, NULL)
		return;
	if (matrix->values != NULL)
		Memory_Free(matrix->values);
	matrix->values = NULL;
	matrix->rows = 0;
	matrix->cols = 0;
}



void	Matrix_Delete(s_matrix* *a_matrix)
{
	if CCCERROR((a_matrix == NULL), ERROR_NULLPOINTER, NULL)
		return;
	if (*a_matrix == NULL)
		return;
	Matrix_Free(*a_matrix);
	Memory_Delete((void**)a_matrix);
}
