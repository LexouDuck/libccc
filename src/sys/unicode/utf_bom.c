
#include "libccc/sys/unicode.h"
#include "libccc/pointer.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



t_sint	UTF8_ByteOrderMark(t_utf8 const* str)
{
	t_sint	i = 0;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)
	if (str[i] && str[i] == UTF8_BOM[i])	++i;	else return (0);
	if (str[i] && str[i] == UTF8_BOM[i])	++i;	else return (0);
	if (str[i] && str[i] == UTF8_BOM[i])	++i;	else return (0);
	return (i);
}



t_sint	UTF16_ByteOrderMark(t_utf16 const* wstr)
{
	t_u8*	str = (t_u8*)wstr; 
	t_sint	i = 0;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)
	if (str[i] == '\0')
		return (0);
	else if (str[i] == UTF16_BOM_BE[i])
	{
		++i;
		if (str[i] && str[i] == UTF16_BOM_LE[i])	++i;	else return (0);
		return (i);
	}
	else if (str[i] == UTF16_BOM_BE[i])
	{
		++i;
		if (str[i] && str[i] == UTF16_BOM_BE[i])	++i;	else return (0);
		return (-i);
	}
	else return (0);
}



t_sint	UTF32_ByteOrderMark(t_utf32 const* wstr)
{
	t_u8*	str = (t_u8*)wstr; 
	t_sint	i = 0;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)
	if (str[i] == '\0')
		return (0);
	else if (str[i] == UTF32_BOM_LE[i])
	{
		++i;
		if (str[i] && str[i] == UTF32_BOM_LE[i])	++i;	else return (0);
		if (str[i] && str[i] == UTF32_BOM_LE[i])	++i;	else return (0);
		if (str[i] && str[i] == UTF32_BOM_LE[i])	++i;	else return (0);
		return (i);
	}
	else if (str[i] == UTF32_BOM_BE[i])
	{
		++i;
		if (str[i] && str[i] == UTF32_BOM_BE[i])	++i;	else return (0);
		if (str[i] && str[i] == UTF32_BOM_BE[i])	++i;	else return (0);
		if (str[i] && str[i] == UTF32_BOM_BE[i])	++i;	else return (0);
		return (-i);
	}
	else return (0);
}
