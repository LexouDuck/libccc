
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



t_bool	Tensor_Equals(s_tensor const* t1, s_tensor const* t2)
{
	t_uint size;
	t_uint i;

	if CCCERROR((t1 == NULL || t2 == NULL), ERROR_NULLPOINTER, NULL)
		return (FALSE);
	if (t1->order != t2->order)
		return (FALSE);
	for (i = 0; i < t1->order; ++i)
	{
		if (t1->dims[i] != t2->dims[i])
			return (FALSE);
	}
	if (t1->values == t2->values)
		return (TRUE);
	if (t1->values == NULL || t2->values == NULL)
		return (FALSE);
	size = Tensor_Size(t1);
	for (i = 0; i < size; ++i)
	{
		if (t1->values[i] != t2->values[i])
			return (FALSE);
	}
	return (TRUE);
}
