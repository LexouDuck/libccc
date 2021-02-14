
#include "libccc/sys/io.h"
#include "libccc/sys/logger.h"



void	Log_Init(s_logger* logger)
{
	t_io_open flags = (OPEN_CREATE | OPEN_WRITEONLY);
	s_logfile* logfile;
	for (t_uint i = 0; i < LOGFILES_MAX; ++i)
	{
		logfile = &logger->dest_files[i];
		if (logfile->path)
		{
			logfile->fd = IO_Open(logfile->path,
				(flags | (logfile->append ? OPEN_APPEND : OPEN_CLEARFILE)), 0644);
			if (logfile->fd < 0)
			{
				logfile->fd = 0;
				Log_FatalError(logger, "Could not open logfile");
			}
			else
			{
				Log_Verbose(*logger, "Logging for software initialized\n");
			}
		}
	}
}



void	Log_Exit(s_logger* logger)
{
	s_logfile* logfile;
	for (t_uint i = 0; i < LOGFILES_MAX; ++i)
	{
		logfile = &logger->dest_files[i];
		if (logfile->path && logfile->fd > STDERR)
		{
			if (IO_Close(logfile->fd))
			{
				Log_FatalError(logger, "Could not close logfile");
			}
		}
	}
}
