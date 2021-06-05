
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
	HANDLE_ERROR(SYSTEM, (csprng.state == NULL), return (NULL);)
	return (csprng.state);
}



void	CSPRNG_Delete(t_csprng* *a_state)
{
	u_csprng	csprng;

	HANDLE_ERROR(NULLPOINTER, (a_state == NULL), return;)
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

	HANDLE_ERROR(NULLPOINTER, (dest == NULL), return (ERROR_NULLPOINTER);)
	HANDLE_ERROR(NULLPOINTER, (state == NULL), return (ERROR_NULLPOINTER);)
	csprng.state = state;
#ifdef _WIN32
	WINBOOL result;
	HANDLE_ERROR(SYSTEM, (csprng.hCryptProv == 0), return (ERROR_SYSTEM);)
	t_u64 n = (size >> 30);
	while (n--)
	{
		result = CryptGenRandom(csprng.hCryptProv, (1ul << 30), (BYTE*)dest);
		HANDLE_ERROR(SYSTEM, (!result), return (ERROR_SYSTEM);)
	}
	result = CryptGenRandom(csprng.hCryptProv, (size & ((1ull << 30) - 1)), (BYTE*)dest);
	HANDLE_ERROR(SYSTEM, (!result), return (ERROR_SYSTEM);)
#else
	t_size  result;
	HANDLE_ERROR(SYSTEM, (csprng.urandom == NULL), return (ERROR_SYSTEM);)
	result = fread((char*)dest, 1, size, csprng.urandom);
	HANDLE_ERROR(SYSTEM, (result != size), return (ERROR_SYSTEM);)
#endif
	return (OK);
}


#define CSPRNG_INIT_STATE() \
	t_csprng*	state;                                       \
	state = CSPRNG_New();                                    \
	HANDLE_ERROR(ALLOCFAILURE, (state == NULL), return (0);) \

void*	CSPRNG_Get(void* dest, t_size size)
{
	HANDLE_ERROR(NULLPOINTER, (dest == NULL), return (0);)
	CSPRNG_INIT_STATE() 
	if (CSPRNG_Next(state, dest, size)) return (0);
	CSPRNG_Delete(&state);
	return (dest);
}



#define DEFINE_CSPRNG(TYPE, ACTION_ERROR) \
	TYPE	result = 0;			\
	if (CSPRNG_Next(state,		\
		&result, sizeof(TYPE)))	\
		ACTION_ERROR			\

inline t_uint	CSPRNG_UInt (t_csprng* state)	{ DEFINE_CSPRNG(t_uint,	return (0);)	return (result); }
inline t_sint	CSPRNG_SInt (t_csprng* state)	{ DEFINE_CSPRNG(t_sint,	return (0);)	return (result); }
inline t_fixed	CSPRNG_Fixed(t_csprng* state)	{ DEFINE_CSPRNG(t_fixed,	return (0);)	return (result); }
inline t_float	CSPRNG_Float(t_csprng* state)
{
	t_float	result = NAN;
	while (isnan(result))
	{
		if (CSPRNG_Next(state, &result, sizeof(t_float)))
			return (NAN);
	}
	return (result);
}



#define DEFINE_CSPRNG_RANGE(ACTION_ERROR) \
	if (min == max)				\
		return (min);			\
	HANDLE_ERROR(INVALIDRANGE,	\
		(min > max),			\
		ACTION_ERROR)			\

t_uint  CSPRNG_UInt_Range     (t_csprng* state, t_uint  min, t_uint  max) { DEFINE_CSPRNG_RANGE(return (0);)	return (         (CSPRNG_UInt(state) % (max - min)) + min); }
t_sint  CSPRNG_SInt_Range     (t_csprng* state, t_sint  min, t_sint  max) { DEFINE_CSPRNG_RANGE(return (0);)	return (         (CSPRNG_SInt(state) % (max - min)) + min); }
t_fixed CSPRNG_Fixed_Range    (t_csprng* state, t_fixed min, t_fixed max) { DEFINE_CSPRNG_RANGE(return (0);)	return (Fixed_Mod(CSPRNG_Fixed(state), (max - min)) + min); }
t_float CSPRNG_Float_Range    (t_csprng* state, t_float min, t_float max) { DEFINE_CSPRNG_RANGE(return (0);)	return (Float_Mod(CSPRNG_Float(state), (max - min)) + min); }

t_uint  CSPRNG_UInt_Get       (void)                      { CSPRNG_INIT_STATE()  t_uint  result = CSPRNG_UInt       (state);            CSPRNG_Delete(&state);  return (result); }
t_sint  CSPRNG_SInt_Get       (void)                      { CSPRNG_INIT_STATE()  t_sint  result = CSPRNG_SInt       (state);            CSPRNG_Delete(&state);  return (result); }
t_fixed CSPRNG_Fixed_Get      (void)                      { CSPRNG_INIT_STATE()  t_fixed result = CSPRNG_Fixed      (state);            CSPRNG_Delete(&state);  return (result); }
t_float CSPRNG_Float_Get      (void)                      { CSPRNG_INIT_STATE()  t_float result = CSPRNG_Float      (state);            CSPRNG_Delete(&state);  return (result); }

t_uint  CSPRNG_UInt_Get_Range (t_uint  min, t_uint  max)  { CSPRNG_INIT_STATE()  t_uint  result = CSPRNG_UInt_Range (state, min, max);  CSPRNG_Delete(&state);  return (result); }
t_sint  CSPRNG_SInt_Get_Range (t_sint  min, t_sint  max)  { CSPRNG_INIT_STATE()  t_sint  result = CSPRNG_SInt_Range (state, min, max);  CSPRNG_Delete(&state);  return (result); }
t_fixed CSPRNG_Fixed_Get_Range(t_fixed min, t_fixed max)  { CSPRNG_INIT_STATE()  t_fixed result = CSPRNG_Fixed_Range(state, min, max);  CSPRNG_Delete(&state);  return (result); }
t_float CSPRNG_Float_Get_Range(t_float min, t_float max)  { CSPRNG_INIT_STATE()  t_float result = CSPRNG_Float_Range(state, min, max);  CSPRNG_Delete(&state);  return (result); }
