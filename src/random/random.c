
#include "libccc/memory.h"
#include "libccc/pointer.h"
#include "libccc/sys/time.h"
#include "libccc/math/int.h"
#include "libccc/math/fixed.h"
#include "libccc/math/float.h"
#include "libccc/random/prng.h"
#include "libccc/random/csprng.h"
#include "libccc/random/random.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_RANDOM_GET(RNG_NAME, RNG_TYPE) \
 \
void*	RNG_NAME##_Get(void* dest, t_size size) \
{ \
	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, \
		"destination pointer is NULL") \
		return (0); \
	RNG_TYPE* state = RNG_NAME##_New(); \
	if (RNG_NAME##_Next(state, dest, size)) \
		return (0); \
	RNG_NAME##_Delete(&state); \
	return (dest); \
} \



DEFINEFUNC_RANDOM_GET(  PRNG,   t_prng)
DEFINEFUNC_RANDOM_GET(CSPRNG, t_csprng)



#define DEFINEFUNC_RANDOM(RNG_NAME, RNG_TYPE, TYPE, TYPE_LOWER, TYPE_MIXED, TYPE_UPPER) \
 \
_INLINE() \
TYPE	RNG_NAME##_Get_##TYPE_MIXED(RNG_TYPE* state) \
{ \
	TYPE	result = TYPE_UPPER##_ERROR; \
	do \
	{ \
		if (RNG_NAME##_Next(state, &result, sizeof(TYPE))) \
			return (TYPE_UPPER##_ERROR); \
	} \
	while (TYPE_MIXED##_IsNaN(result)); \
	return (result); \
} \
 \
TYPE	RNG_NAME##_GetInRange_##TYPE_MIXED(RNG_TYPE* state, TYPE min, TYPE max) \
{ \
	TYPE	result = TYPE_UPPER##_ERROR; \
	if CCCERROR(TYPE_MIXED##_GreaterThan(min,/*>*/ max), ERROR_INVALIDRANGE, \
		"invalid random range specified (min=" SF_##TYPE_UPPER " ; max=" SF_##TYPE_UPPER ")", min, max) \
	{ \
		return (TYPE_UPPER##_ERROR); \
	} \
	if (TYPE_MIXED##_Equals(min, max)) \
		return (min); \
	result = RNG_NAME##_Get_##TYPE_MIXED(state); \
	result = TYPE_MIXED##_Add(TYPE_MIXED##_Mod(result, TYPE_MIXED##_Abs(TYPE_MIXED##_Sub(max, min))), min); \
	/* printf("RNG for range [" SF_##TYPE_UPPER " ; " SF_##TYPE_UPPER "] (" SF_##TYPE_UPPER ") -> " SF_##TYPE_UPPER "  \n", min, max, TYPE_MIXED##_Abs(TYPE_MIXED##_Sub(max, min)), result); */ \
	return (result); \
} \
 \
TYPE*	RNG_NAME##_Sample_##TYPE_MIXED(t_size amount) \
{ \
	RNG_TYPE* state = RNG_NAME##_New(); \
	TYPE*	result = (TYPE*)Memory_Allocate(amount * sizeof(TYPE)); \
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL) \
		return (NULL); \
	for (t_size i = 0; i < amount; ++i) \
	{ \
		result[i] = RNG_NAME##_Get_##TYPE_MIXED(state); \
	} \
	RNG_NAME##_Delete(&state); \
	return (result); \
} \
 \
TYPE*	RNG_NAME##_SampleInRange_##TYPE_MIXED(t_size amount, TYPE min, TYPE max) \
{ \
	RNG_TYPE* state = RNG_NAME##_New(); \
	TYPE*	result = (TYPE*)Memory_Allocate(amount * sizeof(TYPE)); \
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL) \
		return (NULL); \
	for (t_size i = 0; i < amount; ++i) \
	{ \
		result[i] = RNG_NAME##_GetInRange_##TYPE_MIXED(state, min, max); \
	} \
	RNG_NAME##_Delete(&state); \
	return (result); \
} \



DEFINEFUNC_RANDOM(PRNG, t_prng, t_uint,  uint,  UInt,  UINT)  // return (         (PRNG_Get_UInt(state) % (max - min)) + min);
DEFINEFUNC_RANDOM(PRNG, t_prng, t_sint,  sint,  SInt,  SINT)  // return (         (PRNG_Get_SInt(state) % (max - min)) + min);
DEFINEFUNC_RANDOM(PRNG, t_prng, t_fixed, fixed, Fixed, FIXED) // return (Fixed_Mod(PRNG_Get_Fixed(state), (max - min)) + min);
DEFINEFUNC_RANDOM(PRNG, t_prng, t_float, float, Float, FLOAT) // return (Float_Mod(PRNG_Get_Float(state), (max - min)) + min);

DEFINEFUNC_RANDOM(CSPRNG, t_csprng, t_uint,  uint,  UInt,  UINT)  // return (         (PRNG_Get_UInt(state) % (max - min)) + min);
DEFINEFUNC_RANDOM(CSPRNG, t_csprng, t_sint,  sint,  SInt,  SINT)  // return (         (PRNG_Get_SInt(state) % (max - min)) + min);
DEFINEFUNC_RANDOM(CSPRNG, t_csprng, t_fixed, fixed, Fixed, FIXED) // return (Fixed_Mod(PRNG_Get_Fixed(state), (max - min)) + min);
DEFINEFUNC_RANDOM(CSPRNG, t_csprng, t_float, float, Float, FLOAT) // return (Float_Mod(PRNG_Get_Float(state), (max - min)) + min);
