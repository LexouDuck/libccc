/*============================================================================*\
||                                            ______________________________  ||
||  libccc/compatibility/msvc/unistd.h       |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef _UNISTD_H
#define _UNISTD_H

/*
**  This is intended as a drop-in replacement for unistd.h on Windows.
**  You are free to add functionalities to this header, as needed.
*/

/* Disable microsoft warnings for posix functions */
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <io.h>
#include <process.h> /* for getpid() and the exec..() family */
#include <direct.h> /* for _getcwd() and _chdir() */



/*
**	Values for the second argument to access.
**	These may be OR'd together.
*/
#define R_OK	4	/* Bitmask for read permission. */
#define W_OK	2	/* Bitmask for write permission. */
//#define X_OK	1	/* Bitmask for execute permission - unsupported in windows */
#define F_OK	0	/* Bitmask for existence. */



#define srandom srand /* random number 'set seed' function */
#define random  rand  /* random number generator function */

#define access    _access     /* Check a file's permissions */
#define waccess   _waccess    /* Check a file's permissions (wchar_t) */
#define access_s  _access_s   /* Check a file's permissions, secure */
#define waccess_s _waccess_s  /* Check a file's permissions, secure (wchar_t) */

#define open      _open       /* Open file */
#define wopen     _wopen      /* Open file (wchar_t) */
#define sopen     _sopen      /* Open file for file sharing */
#define wsopen    _wsopen     /* Open file for file sharing (wchar_t) */
#define sopen_s   _sopen_s    /* Open file for file sharing, secure */
#define wsopen_s  _wsopen_s   /* Open file for file sharing, secure (wchar_t) */

#define close     _close      /* Close file */

#define creat     _creat      /* Create file */
#define wcreat    _wcreat     /* Create file (wchar_t) */

#define unlink    _unlink     /* Delete file */
#define wunlink   _wunlink    /* Delete file (wchar_t) */

#define chdir     _chdir      /* Change current working directory */
#define wchdir    _wchdir     /* Change current working directory */
#define chdrive   _wchdrive   /* Change current working drive (int,[1=A,26=Z]) */
#define getcwd    _getcwd     /* Get current working directory */

#define chmod     _chmod      /* Change current working directory */
#define wchmod    _wchmod     /* Change current working directory */

#define umask     _umask      /* Set file-permission mask */
#define umask_s   _umask_s    /* Set file-permission mask */

#define chsize    _chsize     /* Change file size */
#define chsize_s  _chsize_s   /* Change file size, secure */
#define ftruncate _chsize     /* Change file size */

#define commit    _commit     /* Flush file to disk */

#define dup       _dup        /* Return next available file descriptor for given file */
#define dup2      _dup2       /* Create second descriptor for given file */

#define eof       _eof        /* Test for end of file */
#define read      _read       /* Read data from file */
#define write     _write      /* Write data to file */

#define execve    _execve     /* Execute child process */

#define fileno    _fileno     /* Gets the file descriptor associated with a stream */

#define lseek     _lseek      /* Reposition file pointer to given location */
#define tell      _tell       /* Get current file-pointer position */

#define isatty    _isatty     /* Determines whether a file descriptor is associated with a character device. */

#define getenv    _getenv     /* Gets the value of an environment variable */
#define putenv    _putenv     /* Sets the value of an environment variable */


/*
**  read(), write(), and close() are NOT being #defined here,
**  because, while there are file handle specific versions for Windows,
**  they probably don't work for sockets.
**  You need to look at your app and consider whether to call the
**  appropriate function on a case-by-case basis, e.g. closesocket().
*/

#ifdef _WIN64
#define ssize_t __int64
#else
#define ssize_t long
#endif

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

/* should be in some equivalent to <sys/types.h> */
/*
typedef __int8            int8_t;
typedef __int16           int16_t; 
typedef __int32           int32_t;
typedef __int64           int64_t;
typedef unsigned __int8   uint8_t;
typedef unsigned __int16  uint16_t;
typedef unsigned __int32  uint32_t;
typedef unsigned __int64  uint64_t;
*/


#endif /* _UNISTD_H */
