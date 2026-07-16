
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



s_matrix	Matrix_Identity(t_uint n)
{
	s_matrix result;
	t_uint i;

	result = Matrix(n, n, NULL);
	if (result.values == NULL)
		return (result);
	for (i = 0; i < n; ++i)
	{
		result.values[i * n + i] = 1;
	}
	return (result);
}
