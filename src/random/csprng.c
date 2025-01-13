
#include "libccc/pointer.h"

#ifndef __NOSTD__
#ifdef _WIN32
	#include <windows.h>
	#include <wincrypt.h>

	#ifdef _MSC_VER
	#pragma comment(lib, "advapi32.lib")
	#endif
#else
	#include <stdio.h>
#endif
#else
	typedef struct file	FILE;
	FILE*	fopen(char const* path, char const* mode);
	int		fclose(FILE* file);
	size_t	fread(void* ptr, size_t size, size_t n, FILE* file);
#endif

#include "libccc/math/fixed.h"
#include "libccc/math/float.h"
#include "libccc/random/csprng.h"

#include LIBCONFIG_ERROR_INCLUDE



typedef union csprng
{
	t_csprng*   state;
#ifdef _WIN32
	HCRYPTPROV  hCryptProv;
#else
	FILE*       urandom;
#endif
}		u_csprng;



t_csprng*	CSPRNG_New(void)
{
	u_csprng	csprng;

#ifdef _WIN32
	if (!CryptAcquireContextA(&csprng.hCryptProv, NULL, NULL,
		PROV_RSA_FULL, (CRYPT_VERIFYCONTEXT | CRYPT_SILENT)))
		csprng.hCryptProv = 0;
#else
	csprng.urandom = fopen("/dev/urandom", "rb");
#endif
	if CCCERROR((csprng.state == NULL), ERROR_SYSTEM, 
		"error occurred while initializing crypto-secure PRNG state.")
		return (NULL);
	return (csprng.state);
}



void	CSPRNG_Delete(t_csprng* *a_state)
{
	u_csprng	csprng;

	if CCCERROR((a_state == NULL), ERROR_NULLPOINTER,
		"PRNG state address given is NULL")
		return;
	csprng.state = *a_state;
#ifdef _WIN32
	if (csprng.hCryptProv)
		CryptReleaseContext(csprng.hCryptProv, 0);
#else
	if (csprng.urandom)
		fclose(csprng.urandom); // TODO error handling
#endif
	*a_state = NULL;
}



e_cccerror	CSPRNG_Next(t_csprng* state, void* dest, t_size size)
{
	u_csprng	csprng;

	if CCCERROR((dest  == NULL), ERROR_NULLPOINTER,
		"destination pointer given is NULL")
		return (ERROR_NULLPOINTER);
	if CCCERROR((state == NULL), ERROR_NULLPOINTER,
		"CSPRNG state given is NULL")
		return (ERROR_NULLPOINTER);
	csprng.state = state;
#ifdef _WIN32
	BOOL result;
	if CCCERROR((csprng.hCryptProv == 0), ERROR_SYSTEM,
		"invalid CSPRNG state (hCryptProv)")
		return (ERROR_SYSTEM);
	t_u64 n = (size >> 30);
	while (n--)
	{
		result = CryptGenRandom(csprng.hCryptProv, (1ul << 30), (BYTE*)dest);
		if CCCERROR((!result), ERROR_SYSTEM,
			"call to CryptGenRandom() failed")
			return (ERROR_SYSTEM);
	}
	result = CryptGenRandom(csprng.hCryptProv, (size & ((1ull << 30) - 1)), (BYTE*)dest);
	if CCCERROR((!result), ERROR_SYSTEM,
		"call to CryptGenRandom() failed")
		return (ERROR_SYSTEM);
#else
	t_size  result;
	if CCCERROR((csprng.urandom == NULL), ERROR_SYSTEM,
		"invalid CSPRNG state (urandom)")
		return (ERROR_SYSTEM);
	result = fread((char*)dest, 1, size, csprng.urandom);
	if CCCERROR((result != size), ERROR_SYSTEM,
		"call to fread() on /dev/urandom failed")
		return (ERROR_SYSTEM);
#endif
	return (ERROR_NONE);
}


#define CSPRNG_INIT_STATE() \
	t_csprng*	state; \
	state = CSPRNG_New(); \
	if CCCERROR((state == NULL), ERROR_ALLOCFAILURE, \
		"could not create crypto-secure PRNG state") \
		return (0); \

void*	CSPRNG_Get(void* dest, t_size size)
{
	if CCCERROR((dest == NULL), ERROR_NULLPOINTER,
		"destination pointer is NULL")
		return (0);
	CSPRNG_INIT_STATE() 
	if (CSPRNG_Next(state, dest, size)) return (0);
	CSPRNG_Delete(&state);
	return (dest);
}



#define DEFINE_CSPRNG(TYPE, ACTION_ERROR) \
	TYPE	result = 0; \
	if (CSPRNG_Next(state, \
		&result, sizeof(TYPE))) \
		ACTION_ERROR \

_INLINE() t_uint	CSPRNG_UInt (t_csprng* state)	{ DEFINE_CSPRNG(t_uint ,	return (0);)	return (result); }
_INLINE() t_sint	CSPRNG_SInt (t_csprng* state)	{ DEFINE_CSPRNG(t_sint ,	return (0);)	return (result); }
_INLINE() t_fixed	CSPRNG_Fixed(t_csprng* state)	{ DEFINE_CSPRNG(t_fixed,	return (0);)	return (result); }
t_float	CSPRNG_Float(t_csprng* state)
{
	t_float	result = NAN;
	while (Float_IsNaN(result))
	{
		if (CSPRNG_Next(state, &result, sizeof(t_float)))
			return (NAN);
	}
	return (result);
}



#define CSPRNG_RANGE_CHECK(_ACTION_, _SF_TYPE_) \
	if (min == max) \
		return (min); \
	if CCCERROR((min > max), ERROR_INVALIDRANGE, \
		"invalid random range specified (min=" _SF_TYPE_ " ; max=" _SF_TYPE_ ")", min, max) \
	{ \
		_ACTION_ \
	} \

t_uint  CSPRNG_UInt_Range     (t_csprng* state, t_uint  min, t_uint  max) { CSPRNG_RANGE_CHECK(return (0);, SF_UINT)	return (         (CSPRNG_UInt(state) % (max - min)) + min); }
t_sint  CSPRNG_SInt_Range     (t_csprng* state, t_sint  min, t_sint  max) { CSPRNG_RANGE_CHECK(return (0);, SF_SINT)	return (         (CSPRNG_SInt(state) % (max - min)) + min); }
t_fixed CSPRNG_Fixed_Range    (t_csprng* state, t_fixed min, t_fixed max) { CSPRNG_RANGE_CHECK(return (0);, SF_FIXED)	return (Fixed_Mod(CSPRNG_Fixed(state), (max - min)) + min); }
t_float CSPRNG_Float_Range    (t_csprng* state, t_float min, t_float max) { CSPRNG_RANGE_CHECK(return (0);, SF_FLOAT)	return (Float_Mod(CSPRNG_Float(state), (max - min)) + min); }

t_uint  CSPRNG_UInt_Get       (void)                      { CSPRNG_INIT_STATE()  t_uint  result = CSPRNG_UInt       (state);            CSPRNG_Delete(&state);  return (result); }
t_sint  CSPRNG_SInt_Get       (void)                      { CSPRNG_INIT_STATE()  t_sint  result = CSPRNG_SInt       (state);            CSPRNG_Delete(&state);  return (result); }
t_fixed CSPRNG_Fixed_Get      (void)                      { CSPRNG_INIT_STATE()  t_fixed result = CSPRNG_Fixed      (state);            CSPRNG_Delete(&state);  return (result); }
t_float CSPRNG_Float_Get      (void)                      { CSPRNG_INIT_STATE()  t_float result = CSPRNG_Float      (state);            CSPRNG_Delete(&state);  return (result); }

t_uint  CSPRNG_UInt_Get_Range (t_uint  min, t_uint  max)  { CSPRNG_INIT_STATE()  t_uint  result = CSPRNG_UInt_Range (state, min, max);  CSPRNG_Delete(&state);  return (result); }
t_sint  CSPRNG_SInt_Get_Range (t_sint  min, t_sint  max)  { CSPRNG_INIT_STATE()  t_sint  result = CSPRNG_SInt_Range (state, min, max);  CSPRNG_Delete(&state);  return (result); }
t_fixed CSPRNG_Fixed_Get_Range(t_fixed min, t_fixed max)  { CSPRNG_INIT_STATE()  t_fixed result = CSPRNG_Fixed_Range(state, min, max);  CSPRNG_Delete(&state);  return (result); }
t_float CSPRNG_Float_Get_Range(t_float min, t_float max)  { CSPRNG_INIT_STATE()  t_float result = CSPRNG_Float_Range(state, min, max);  CSPRNG_Delete(&state);  return (result); }
