
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



t_uint	Tensor_Size(s_tensor const* tensor)
{
	t_uint size;
	t_uint i;

	if CCCERROR((tensor == NULL), ERROR_NULLPOINTER, NULL)
		return (0);
	if (tensor->values == NULL)
		return (0);
	size = 1;
	for (i = 0; i < tensor->order; ++i)
	{
		size *= tensor->dims[i];
	}
	return (size);
}
