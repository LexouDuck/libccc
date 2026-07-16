
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



t_float		Tensor_Norm(s_tensor const* tensor)
{
	t_float	tmp;
	t_float	sum;
	t_uint size;
	t_uint i;

	if CCCERROR((tensor == NULL), ERROR_NULLPOINTER, NULL)
		return (0);
	sum = 0;
	size = Tensor_Size(tensor);
	for (i = 0; i < size; ++i)
	{
		tmp = tensor->values[i];
		tmp *= tmp;
		sum += tmp;
	}
	return (sum);
}
