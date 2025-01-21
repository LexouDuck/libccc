
#include "libccc/memory.h"
#include "libccc/pointer.h"
#include "libccc/sys/time.h"
#include "libccc/math/int.h"
#include "libccc/math/fixed.h"
#include "libccc/math/float.h"
#include "libccc/random/prng.h"

#include LIBCONFIG_ERROR_INCLUDE



t_u32   PRNG_Shuffle(t_u32 n); // static
t_u32   PRNG_Shuffle(t_u32 n)
{
	n = (n << 12) ^ (n >> 20);
	return (36969 * (n & 0xFFFF) + (n >> 16));
}

t_u32   PRNG_U32(t_prng* state); // static
t_u32   PRNG_U32(t_prng* state)
{
	*state = ((PRNG_CEIL_SQRT_MOD * PRNG_Shuffle(*state) + PRNG_OFFSET) & PRNG_MODULUS);
	return (*state);
}

_INLINE()
void    PRNG_SetSeed(t_prng* state, t_u32 seed)
{
	*state = seed;
}

_INLINE()
void    PRNG_NewSeed(t_prng* state)
{
	*state = PRNG_Shuffle(Time_Now());
}



t_prng* PRNG_New(void)
{
	t_prng* result;

	result = (t_prng*)Memory_Allocate(sizeof(t_prng));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, "could not create PRNG state")
		return (NULL);
	PRNG_SetSeed(result, PRNG_SEED_DEFAULT);
	return (result);
}

void    PRNG_Delete(t_prng* *a_state)
{
	if CCCERROR((a_state == NULL), ERROR_NULLPOINTER, "PRNG state address given is NULL")
		return;
	Memory_Free(*a_state);
	*a_state = NULL;
}



e_cccerror  PRNG_Next(t_prng* state, void* dest, t_size n)
{
	t_u8*   buffer = (t_u8*)dest;
	t_u32   random = 0;
	t_size  i = 0;

	if CCCERROR((dest  == NULL), ERROR_NULLPOINTER, "destination pointer is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((state == NULL), ERROR_NULLPOINTER, "PRNG state argument is NULL")
		return (ERROR_NULLPOINTER);
	while (i < n)
	{
		random = PRNG_U32(state);
		buffer[i] = (random >>  0) & 0xFF;	if (i++ == n)   break;
		buffer[i] = (random >>  8) & 0xFF;	if (i++ == n)   break;
		buffer[i] = (random >> 16) & 0xFF;	if (i++ == n)   break;
		buffer[i] = (random >> 24) & 0xFF;	if (i++ == n)   break;
	}
	return (ERROR_NONE);
}
