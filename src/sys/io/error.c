
/*
**	Functions used from <string.h>:
**	-	char const* strerror(int errnum);
**	-	int strerror_r(int errnum, char *buf, size_t buflen);
*/
#include <string.h>
#include <sys/types.h>

#include "libccc/string.h"
#include "libccc/sys/io.h"



inline char*	IO_GetError(t_io_error error)
{
	char	buffer[IO_BUFFER_SIZE] = {0};

#ifdef __MINGW32__
/*
// windows sockets
	int error = WSAGetLastError();
	DWORD len = FormatMessageA(
		SF_MESSAGE_ARGUMENT_ARRAY |
		SF_MESSAGE_FROM_SYSTEM |
		SF_MESSAGE_IGNORE_INSERTS,
		NULL, error, 0, result, IO_BUFFER_SIZE, NULL);
	if (len)
		buffer[len] = '\0';
	else
		sprintf(result, "Error: %d", error);
*/
	strerror_s(buffer, IO_BUFFER_SIZE, error);
#else
	strerror_r(error, buffer, IO_BUFFER_SIZE);
#endif
	return (String_Duplicate(buffer));
}
