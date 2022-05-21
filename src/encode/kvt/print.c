
#include "libccc/memory.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_ERROR_INCLUDE



void	KVT_Print_UpdateOffset(s_kvt_print* p)
{
	t_utf8 const* buffer_pointer = NULL;
	if ((p == NULL) || (p->result == NULL))
		return;
	buffer_pointer = p->result + p->offset;
	p->offset += String_Length(buffer_pointer);
}



t_utf8*	KVT_Print_EnsureBuffer(s_kvt_print* p, t_size needed)
{
	t_utf8*	newbuffer = NULL;
	t_size	newsize = 0;

	if ((p == NULL) || (p->result == NULL))
		return (NULL);
	if ((p->length > 0) && (p->offset >= p->length))
	{	// make sure that offset is valid
		return (NULL);
	}
	if (needed > SIZE_MAX)
	{	// sizes bigger than SIZE_MAX are currently not supported
		return (NULL);
	}
	needed += p->offset + 1;
	if (needed <= p->length)
		return (p->result + p->offset);
	if (p->noalloc)
		return (NULL);
	// calculate new buffer size
	if (needed > (SIZE_MAX / 2))
	{
		// overflow of t_sint, use SIZE_MAX if possible
		if (needed <= SIZE_MAX)
		{
			newsize = SIZE_MAX;
		}
		else
			return (NULL);
	}
	else
	{
		newsize = needed * 2;
	}

#ifdef c_realloc // TODO make this ifdef check more robust ?
	// reallocate with realloc if available
	newbuffer = (t_utf8*)Memory_Reallocate(p->result, newsize);
	if CCCERROR((newbuffer == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		Memory_Free(p->result);
		p->length = 0;
		p->result = NULL;
		return (NULL);
	}
#else
	// otherwise reallocate manually
	newbuffer = (t_utf8*)Memory_Allocate(newsize);
	if CCCERROR((newbuffer == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		Memory_Free(p->result);
		p->length = 0;
		p->result = NULL;
		return (NULL);
	}
	Memory_Copy(newbuffer, p->result, p->offset + 1);
	Memory_Free(p->result);
#endif
	p->length = newsize;
	p->result = newbuffer;
	return (newbuffer + p->offset);
}
