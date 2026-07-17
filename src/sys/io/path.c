
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/sys/io.h"

#include LIBCONFIG_ERROR_INCLUDE



//! Checks whether the given char `c` is a valid path separator char for the current platform
static
t_bool	IO_Path_IsSeparator(t_char c)
{
#ifdef _WIN32
	return (c == '/' || c == '\\');
#else
	return (c == '/');
#endif
}

//! Returns the index just after the last path separator char within `filepath` (or `0` if there is none)
static
t_size	IO_Path_GetFileNameIndex(t_char const* filepath)
{
	t_size	i;
	t_size	result = 0;

	for (i = 0; filepath[i] != '\0'; ++i)
	{
		if (IO_Path_IsSeparator(filepath[i]))
			result = i + 1;
	}
	return (result);
}



t_bool	IO_Path_IsAbsolute(t_char const* filepath)
{
	if CCCERROR((filepath == NULL), ERROR_NULLPOINTER, "filepath given is NULL")
		return (FALSE);
#ifdef _WIN32
	if (IO_Path_IsSeparator(filepath[0]))
		return (TRUE); // handles both `\folder\file` and UNC `\\host\share` paths
	if (Char_IsLetter(filepath[0]) && filepath[1] == ':' &&
		IO_Path_IsSeparator(filepath[2]))
		return (TRUE); // handles drive-letter paths, ie: `C:\folder\file`
	return (FALSE);
#else
	return (IO_Path_IsSeparator(filepath[0]));
#endif
}



t_char*	IO_Path_Combine(t_char const* path1, t_char const* path2)
{
	t_char*	result;
	t_size	len1;
	t_size	len2;
	t_size	i;

	if CCCERROR((path1 == NULL), ERROR_NULLPOINTER, "left-hand path given is NULL")
		return (NULL);
	if CCCERROR((path2 == NULL), ERROR_NULLPOINTER, "right-hand path given is NULL")
		return (NULL);
	if (path1[0] == '\0')
		return (String_Duplicate(path2));
	if (path2[0] == '\0')
		return (String_Duplicate(path1));
	if (IO_Path_IsAbsolute(path2))
		return (String_Duplicate(path2));
	// trim any trailing separator chars from `path1`
	len1 = String_Length(path1);
	while (len1 > 0 && IO_Path_IsSeparator(path1[len1 - 1]))
		len1 -= 1;
	// trim any leading separator chars from `path2`
	while (IO_Path_IsSeparator(path2[0]))
		path2 += 1;
	len2 = String_Length(path2);
	result = (t_char*)Memory_Allocate(len1 + len2 + 2);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (i = 0; i < len1; ++i)
		result[i] = path1[i];
	result[len1] = IO_PATH_SEPARATOR;
	for (i = 0; i < len2; ++i)
		result[len1 + 1 + i] = path2[i];
	result[len1 + 1 + len2] = '\0';
	return (result);
}



t_char*	IO_Path_GetDirectory(t_char const* filepath)
{
	t_size	index;

	if CCCERROR((filepath == NULL), ERROR_NULLPOINTER, "filepath given is NULL")
		return (NULL);
	index = IO_Path_GetFileNameIndex(filepath);
	if (index == 0)
		return (String_Duplicate(".")); // no separator: current directory
	// trim the trailing separator char(s), except if this path is the filesystem root
	while (index > 1 && IO_Path_IsSeparator(filepath[index - 1])
#ifdef _WIN32
		&& !(index > 2 && filepath[index - 2] == ':') // preserve separator for `C:\`
#endif
	)
	{
		index -= 1;
	}
	return (String_Sub(filepath, 0, index));
}



t_char*	IO_Path_GetFileName(t_char const* filepath)
{
	if CCCERROR((filepath == NULL), ERROR_NULLPOINTER, "filepath given is NULL")
		return (NULL);
	return (String_Duplicate(filepath + IO_Path_GetFileNameIndex(filepath)));
}



t_char*	IO_Path_GetExtension(t_char const* filepath)
{
	t_char const*	filename;
	t_size	dot = 0;
	t_size	i;

	if CCCERROR((filepath == NULL), ERROR_NULLPOINTER, "filepath given is NULL")
		return (NULL);
	filename = filepath + IO_Path_GetFileNameIndex(filepath);
	for (i = 0; filename[i] != '\0'; ++i)
	{
		if (filename[i] == '.')
			dot = i;
	}
	if (dot == 0) // no dot found, or filename starts with a dot (ie: "hidden" file)
		return (String_Duplicate(""));
	return (String_Duplicate(filename + dot));
}
