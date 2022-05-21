
#include "libccc.h"
#include "libccc/pointer.h"

#ifndef __NOSTD__
	#if (!defined(__GNUC__) && defined(__MSVC__))
	#include "libccc/compatibility/msvc/unistd.h"
	#else
	#include <unistd.h>
	#endif
#else
	int	write(int fd, void const* buffer, size_t n);
#endif
#ifndef __NOSTD__
	#include <stdarg.h>
#else
	typedef __builtin_va_list va_list;
	#define va_start(v,l)	__builtin_va_start(v,l)
	#define va_end(v)		__builtin_va_end(v)
	#define va_arg(v,l)		__builtin_va_arg(v,l)
	#define va_copy(d,s)	__builtin_va_copy(d,s)
#endif

#include "libccc/sys/io.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



inline
t_size	IO_Write_Char(t_fd fd, t_char c)
{
	if CCCERROR((fd < 0), ERROR_INVALIDARGS, 
		"`fd` argument given has a negative value: %i", fd)
		return (0);
	int result = 0;
	result = write(fd, &c, 1);
	if CCCERROR((result < 0), ERROR_SYSTEM, 
		"call to write() failed on fd#%i, for char '%c'", fd, c)
		return (0);
	return (result);
}



inline
t_size	IO_Write_String(t_fd fd, t_char const* str)
{
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (0);
	if CCCERROR((fd < 0), ERROR_INVALIDARGS, 
		"`fd` argument given has a negative value: %i", fd)
		return (0);
	int result = 0;
	result = write(fd, str, String_Length(str));
	if CCCERROR((result < 0), ERROR_SYSTEM, 
		"call to write() failed on fd#%i, for string \"%s\"", fd, str)
		return (0);
	return (result);
}



inline
t_size	IO_Write_Data(t_fd fd, t_u8 const* data, t_size n)
{
	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (0);
	if CCCERROR((fd < 0), ERROR_INVALIDARGS, 
		"`fd` argument given has a negative value: %i", fd)
		return (0);
	int result = 0;
	result = write(fd, data, n);
	if CCCERROR((result < 0), ERROR_SYSTEM, 
		"call to write() failed on fd#%i, for data of size=%zu", fd, n)
		return (0);
	return (result);
}



inline
t_size	IO_Write_Line(t_fd fd, t_char const* str)
{
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (0);
	if CCCERROR((fd < 0), ERROR_INVALIDARGS, 
		"`fd` argument given has a negative value: %i", fd)
		return (0);
	int result = 0;
	result = write(fd, str, String_Length(str));
	if CCCERROR((result < 0), ERROR_SYSTEM, 
		"call to write() failed on fd#%i, for string \"%s\"", fd, str)
		return (0);
	result = write(fd, "\n", 1);
	if CCCERROR((result < 0), ERROR_SYSTEM, 
		"call to write() failed on fd#%i, for line return at end of line", fd)
		return (0);
	return (result);
}



t_size	IO_Write_Lines(t_fd fd, t_char const** strarr)
{
	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (0);
	if CCCERROR((fd < 0), ERROR_INVALIDARGS, 
		"`fd` argument given has a negative value: %i", fd)
		return (0);
	int result = 0;
	t_uint i = 0;
	while (strarr[i])
	{
		result = write(fd, strarr[i], String_Length(strarr[i]));
		if CCCERROR((result < 0), ERROR_SYSTEM, 
			"call to write() failed on fd#%i, for string array item %i: \"%s\"", fd, i, strarr[i])
			return (0);
		result = write(fd, "\n", 1);
		if CCCERROR((result < 0), ERROR_SYSTEM, 
			"call to write() failed on fd#%i, for string array item %i line return", fd, i)
			return (0);
		++i;
	}
	return (result);
}



t_size	IO_Write_Memory(t_fd fd, t_u8 const* ptr, t_size n, t_u8 columns)
{
	if CCCERROR((fd < 0), ERROR_INVALIDARGS, 
		"`fd` argument given has a negative value: %i", fd)
		return (0);
	if CCCERROR((ptr == NULL), ERROR_NULLPOINTER, "pointer given is NULL")
		return (0);
	if (n == 0 || columns == 0)
		return (0);
	int		result = 0;
	t_u8	nibble = 0;
	t_size	i = 0;
	while (i < n)
	{
		nibble = (ptr[i] & 0xF0) >> 4;
		nibble += (nibble < 10 ? '0' : 'A' - 10);
		result = write(fd, &nibble, 1);
		if CCCERROR((result < 0), ERROR_SYSTEM, 
			"call to write() failed on fd#%i, for half-byte hi char in byte at index "SF_SIZE, fd, i)
			return (0);
		nibble = (ptr[i] & 0x0F);
		nibble += (nibble < 10 ? '0' : 'A' - 10);
		result = write(fd, &nibble, 1);
		if CCCERROR((result < 0), ERROR_SYSTEM, 
			"call to write() failed on fd#%i, for half-byte lo char in byte at index "SF_SIZE, fd, i)
			return (0);
		++i;
		result = write(fd, (i % columns == 0 ? "\n" : " "), 1);
		if CCCERROR((result < 0), ERROR_SYSTEM, 
			"call to write() failed on fd#%i, for memory column separator at index "SF_SIZE, fd, i)
			return (0);
	}
	return (result);
}



t_size	IO_Write_Format(t_fd fd, t_char const* format, ...)
{
	if CCCERROR((fd < 0), ERROR_INVALIDARGS, 
		"`fd` argument given has a negative value: %i", fd)
		return (0);
	if CCCERROR((format == NULL), ERROR_NULLPOINTER, "format string given is NULL")
		return (0);
	int		result = 0;
	t_char* str = NULL;
	va_list args;
	va_start(args, format);
	str = String_Format_VA(format, args);
	va_end(args);
	if CCCERROR((str == NULL), ERROR_ALLOCFAILURE, NULL) return (0);
	result = write(fd, str, String_Length(str));
	if CCCERROR((result < 0), ERROR_SYSTEM, 
		"call to write() failed on fd#%i, for formatted string \"%s\"", fd, format)
		return (0);
	String_Delete(&str);
	return (result);
}
