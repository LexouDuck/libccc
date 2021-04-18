
#include "libccc/memory.h"
#include "libccc/monad/stringarray.h"



inline char	**c_strarrnew(t_u32 length)
{
	return ((char**)c_memnew(sizeof(char*) * (length + 1)));
}
