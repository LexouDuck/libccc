
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
	char*	result;

#ifdef __MINGW32__
/*
// windows sockets
	int error = WSAGetLastError();
	DWORD len = FormatMessageA(
		FORMAT_MESSAGE_ARGUMENT_ARRAY |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, error, 0, result, IO_BUFFER_SIZE, NULL);
	if (len)
		buffer[len] = '\0';
	else
		sprintf(result, "Error: %d", error);
*/
	result = String_Duplicate(strerror(error));
#else
	char	buffer[IO_BUFFER_SIZE] = {0};
	strerror_r(errno, buffer, IO_BUFFER_SIZE);
	result = String_Duplicate(buffer);
#endif
	return (result);
}
