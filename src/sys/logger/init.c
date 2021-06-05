
#include "libccc/string.h"
#include "libccc/sys/io.h"
#include "libccc/sys/logger.h"

#include LIBCONFIG_ERROR_INCLUDE



void	Logger_Init(s_logger *a_logger)
{
	t_io_open flags = (OPEN_CREATE | OPEN_WRITEONLY);

	if (a_logger->path)
	{
		a_logger->fd = IO_Open(a_logger->path,
			(flags | (a_logger->append ? OPEN_APPEND : OPEN_CLEARFILE)), 0644);
		if (a_logger->fd < 0)
		{
			a_logger->fd = 0;
			Log_FatalError(a_logger, "Could not open a_logger\n");
		}
		else
		{
			Log_Verbose(a_logger, "Logging for software initialized\n");
		}
	}
}



void	Logger_Exit(s_logger *a_logger)
{
	if (a_logger->fd > STDERR)
	{
		if (IO_Close(a_logger->fd))
		{
			Log_FatalError(a_logger, "Could not close a_logger\n");
		}
		a_logger->fd = 0;
	}
	String_Delete(&a_logger->path);
}



void	Logger_DeleteMemory(s_logger *a_logger)
{
	String_Delete(&a_logger->path);
}
