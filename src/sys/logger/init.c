
#include "libccc/string.h"
#include "libccc/sys/io.h"
#include "libccc/sys/logger.h"



void	Logger_Init(s_logger *a_logger)
{
	t_io_open flags = (OPEN_CREATE | OPEN_WRITEONLY);
	s_logfile* logfile = NULL;
	for (t_uint i = 0; i < LOGFILES_MAX; ++i)
	{
		logfile = &a_logger->dest_files[i];
		if (logfile->path)
		{
			logfile->fd = IO_Open(logfile->path,
				(flags | (logfile->append ? OPEN_APPEND : OPEN_CLEARFILE)), 0644);
			if (logfile->fd < 0)
			{
				logfile->fd = 0;
				Log_FatalError(a_logger, "Could not open logfile");
			}
			else
			{
				Log_Verbose(a_logger, "Logging for software initialized\n");
			}
		}
	}
}



void	Logger_Exit(s_logger *a_logger)
{
	s_logfile* logfile = NULL;
	for (t_uint i = 0; i < LOGFILES_MAX; ++i)
	{
		logfile = &a_logger->dest_files[i];
		if (logfile->path && logfile->fd > STDERR)
		{
			if (IO_Close(logfile->fd))
			{
				Log_FatalError(a_logger, "Could not close logfile");
			}
			String_Delete(&logfile->path);
		}
	}
}



void	Logger_DeleteMemory(s_logger *a_logger)
{
	s_logfile* logfile = NULL;
	for (t_uint i = 0; i < LOGFILES_MAX; ++i)
	{
		logfile = &a_logger->dest_files[i];
		if (logfile->path && logfile->fd > STDERR)
		{
			String_Delete(&logfile->path);
		}
	}
}
