
#include "libccc/math/algebra.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



void	Vector_Free(s_vector* vector)
{
	if CCCERROR((vector == NULL), ERROR_NULLPOINTER, NULL)
		return;
	if (vector->values != NULL)
		Memory_Free(vector->values);
	vector->values = NULL;
	vector->dims = 0;
}



void	Vector_Delete(s_vector* *a_vector)
{
	if CCCERROR((a_vector == NULL), ERROR_NULLPOINTER, NULL)
		return;
	if (*a_vector == NULL)
		return;
	Vector_Free(*a_vector);
	Memory_Delete((void**)a_vector);
}
