
#include "libccc/memory.h"
#include "libccc/math.h"
#include "libccc/math/stat.h"

#include LIBCONFIG_ERROR_INCLUDE



s_prob_mass	Stat_ProbMassFunc_New(t_uint length)
{
	s_prob_mass	result;

	result.value = NULL;
	result.prob = NULL;
	result.length = 0;
	if (length == 0)	return (result);
	result.value = (t_float*)Memory_Allocate(length * sizeof(t_float));
	if CCCERROR((result.value == NULL), ERROR_ALLOCFAILURE, NULL)
		return (result);
	result.prob = (t_float*)Memory_Allocate(length * sizeof(t_float));
	if CCCERROR((result.prob == NULL), ERROR_ALLOCFAILURE, NULL)
		return (result);
	result.length = length;
	return (result);
}



void	Stat_ProbMassFunc_Delete(s_prob_mass *drv)
{
	if CCCERROR((drv == NULL), ERROR_NULLPOINTER, NULL)
		return;
	if (drv->value)
	{
		Memory_Free(drv->value);
		drv->value = NULL;
	}
	if (drv->prob)
	{
		Memory_Free(drv->prob);
		drv->prob = NULL;
	}
	drv->length = 0;
}
