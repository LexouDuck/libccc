
#include "libccc/math/algebra.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



s_vector	Vector_Duplicate(s_vector const* vector)
{
	if CCCERROR((vector == NULL), ERROR_NULLPOINTER, NULL)
		return (VECTOR_NULL);
	return (Vector(vector->dims, vector->values));
}
