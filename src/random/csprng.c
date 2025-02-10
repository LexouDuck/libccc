
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

#include "libccc/memory.h"
#include "libccc/pointer.h"
#include "libccc/sys/time.h"
#include "libccc/math/int.h"
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
}	u_csprng;



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
