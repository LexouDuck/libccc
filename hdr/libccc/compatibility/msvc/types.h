/*============================================================================*\
||                                            ______________________________  ||
||  libccc/compatibility/msvc/types.h        |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef _TYPES_H
#define _TYPES_H

/*
**  This is intended as a drop-in replacement for types on Windows.
**  You are free to add functionalities to this header, as needed.
*/


#if 0
typedef __int8            int8_t;
typedef __int16           int16_t; 
typedef __int32           int32_t;
typedef __int64           int64_t;
typedef unsigned __int8   uint8_t;
typedef unsigned __int16  uint16_t;
typedef unsigned __int32  uint32_t;
typedef unsigned __int64  uint64_t;
#endif

/* fix for windows+clang+msvc which doesnt fully support 128-bit integer division */
#if defined(__clang__) && defined(__MSVC__)
#undef __int128
#endif



#ifdef _WIN64
#define ssize_t __int64
#else
#define ssize_t long
#endif



#undef isnan
#undef isinf
#undef isfinite
#undef isnormal
#undef isunordered
#undef signbit



#endif /* _TYPES_H */
