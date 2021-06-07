# 1 "src/bool/bool_to_str.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "src/bool/bool_to_str.c"

# 1 "./hdr/libccc.h" 1
# 80 "./hdr/libccc.h"
# 1 "./hdr/libccc_config.h" 1
# 26 "./hdr/libccc_config.h"
# 1 "./hdr/libccc_define.h" 1
# 49 "./hdr/libccc_define.h"

# 573 "./hdr/libccc_define.h"

# 27 "./hdr/libccc_config.h" 2
# 1 "./hdr/libccc_errors.h" 1
# 28 "./hdr/libccc_errors.h"

# 185 "./hdr/libccc_errors.h"
typedef enum cccerror
{
 ERROR_UNSPECIFIED = (-1),
 ERROR_NONE = (0),

 ERROR_SYSTEM,
 ERROR_ALLOCFAILURE,

 ERROR_PARSE,
 ERROR_PRINT,
 ERROR_NOTFOUND,

 ERROR_INVALIDARGS,
 ERROR_NULLPOINTER,
 ERROR_MATHDOMAIN,
 ERROR_RESULTRANGE,
 ERROR_NANARGUMENT,
 ERROR_ILLEGALBYTES,
 ERROR_INVALIDENUM,
 ERROR_INVALIDRANGE,
 ERROR_INDEX2SMALL,
 ERROR_INDEX2LARGE,
 ERROR_LENGTH2SMALL,
 ERROR_LENGTH2LARGE,
 ERROR_KEYNOTFOUND,
 ERROR_WRONGTYPE,
 ERROR_DELETEREF,



 ENUMLENGTH_CCCERROR,
} e_cccerror;
# 370 "./hdr/libccc_errors.h"

# 28 "./hdr/libccc_config.h" 2


# 239 "./hdr/libccc_config.h"

# 81 "./hdr/libccc.h" 2


# 1 "./hdr/libccc/error.h" 1
# 26 "./hdr/libccc/error.h"
# 1 "./hdr/libccc_define.h" 1
# 27 "./hdr/libccc/error.h" 2

# 1 "./hdr/libccc/char.h" 1
# 34 "./hdr/libccc/char.h"
# 1 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdint.h" 1 3 4
# 9 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdint.h" 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdint.h" 1 3 4
# 28 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdint.h" 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/crtdefs.h" 1 3 4
# 10 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/crtdefs.h" 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/corecrt.h" 1 3 4
# 10 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/corecrt.h" 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/_mingw.h" 1 3 4
# 10 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/_mingw.h" 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/_mingw_mac.h" 1 3 4
# 98 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/_mingw_mac.h" 3 4
             
# 107 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/_mingw_mac.h" 3 4
             
# 11 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/_mingw.h" 2 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/_mingw_secapi.h" 1 3 4
# 12 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/_mingw.h" 2 3 4
# 283 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/_mingw.h" 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/vadefs.h" 1 3 4
# 9 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/vadefs.h" 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/_mingw.h" 1 3 4
# 609 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/_mingw.h" 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/sdks/_mingw_ddk.h" 1 3 4
# 610 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/_mingw.h" 2 3 4
# 10 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/vadefs.h" 2 3 4




#pragma pack(push,_CRT_PACKING)
# 24 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/vadefs.h" 3 4
  
# 24 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/vadefs.h" 3 4
 typedef __builtin_va_list __gnuc_va_list;






  typedef __gnuc_va_list va_list;
# 103 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/vadefs.h" 3 4
#pragma pack(pop)
# 284 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/_mingw.h" 2 3 4
# 580 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/_mingw.h" 3 4
void __attribute__((__cdecl__)) __debugbreak(void);
extern 
# 581 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/_mingw.h"
inline 
# 581 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/_mingw.h" 3 4
__attribute__((__always_inline__,__gnu_inline__)) void __attribute__((__cdecl__)) __debugbreak(void)
{
  
# 583 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/_mingw.h"
 asm 
# 583 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/_mingw.h" 3 4
         __volatile__("int {$}3":);
}




const char *__mingw_get_crt_info (void);
# 11 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/corecrt.h" 2 3 4




#pragma pack(push,_CRT_PACKING)
# 40 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/corecrt.h" 3 4
__extension__ typedef unsigned long long size_t;
# 50 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/corecrt.h" 3 4
__extension__ typedef long long ssize_t;






typedef size_t rsize_t;
# 67 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/corecrt.h" 3 4
__extension__ typedef long long intptr_t;
# 80 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/corecrt.h" 3 4
__extension__ typedef unsigned long long uintptr_t;
# 93 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/corecrt.h" 3 4
__extension__ typedef long long ptrdiff_t;
# 103 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/corecrt.h" 3 4
typedef unsigned short wchar_t;







typedef unsigned short wint_t;
typedef unsigned short wctype_t;





typedef int errno_t;




typedef long __time32_t;




__extension__ typedef long long __time64_t;
# 143 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/corecrt.h" 3 4
typedef __time64_t time_t;
# 435 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/corecrt.h" 3 4
struct threadlocaleinfostruct;
struct threadmbcinfostruct;
typedef struct threadlocaleinfostruct *pthreadlocinfo;
typedef struct threadmbcinfostruct *pthreadmbcinfo;
struct __lc_time_data;

typedef struct localeinfo_struct {
  pthreadlocinfo locinfo;
  pthreadmbcinfo mbcinfo;
} _locale_tstruct,*_locale_t;



typedef struct tagLC_ID {
  unsigned short wLanguage;
  unsigned short wCountry;
  unsigned short wCodePage;
} LC_ID,*LPLC_ID;




typedef struct threadlocaleinfostruct {





  int refcount;
  unsigned int lc_codepage;
  unsigned int lc_collate_cp;
  unsigned long lc_handle[6];
  LC_ID lc_id[6];
  struct {
    char *locale;
    wchar_t *wlocale;
    int *refcount;
    int *wrefcount;
  } lc_category[6];
  int lc_clike;
  int mb_cur_max;
  int *lconv_intl_refcount;
  int *lconv_num_refcount;
  int *lconv_mon_refcount;
  struct lconv *lconv;
  int *ctype1_refcount;
  unsigned short *ctype1;
  const unsigned short *pctype;
  const unsigned char *pclmap;
  const unsigned char *pcumap;
  struct __lc_time_data *lc_time_curr;

} threadlocinfo;
# 506 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/corecrt.h" 3 4
#pragma pack(pop)
# 11 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/crtdefs.h" 2 3 4
# 29 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdint.h" 2 3 4



# 1 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stddef.h" 1 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stddef.h" 1 3 4
# 18 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stddef.h" 3 4
  __attribute__ ((__dllimport__)) extern int *__attribute__((__cdecl__)) _errno(void);

  errno_t __attribute__((__cdecl__)) _set_errno(int _Value);
  errno_t __attribute__((__cdecl__)) _get_errno(int *_Value);


  __attribute__ ((__dllimport__)) extern unsigned long __attribute__((__cdecl__)) __threadid(void);

  __attribute__ ((__dllimport__)) extern uintptr_t __attribute__((__cdecl__)) __threadhandle(void);
# 2 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stddef.h" 2 3 4
# 416 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stddef.h" 3 4
typedef struct {
  long long __max_align_ll __attribute__((__aligned__(
# 417 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stddef.h"
                                                     _Alignof(
# 417 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stddef.h" 3 4
                                                     long long
# 417 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stddef.h"
                                                     )
# 417 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stddef.h" 3 4
                                                                           )));
  long double __max_align_ld __attribute__((__aligned__(
# 418 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stddef.h"
                                                       _Alignof(
# 418 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stddef.h" 3 4
                                                       long double
# 418 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stddef.h"
                                                       )
# 418 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stddef.h" 3 4
                                                                               )));
# 427 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stddef.h" 3 4
} max_align_t;
# 33 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdint.h" 2 3 4


typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned uint32_t;
__extension__ typedef long long int64_t;
__extension__ typedef unsigned long long uint64_t;


typedef signed char int_least8_t;
typedef unsigned char uint_least8_t;
typedef short int_least16_t;
typedef unsigned short uint_least16_t;
typedef int int_least32_t;
typedef unsigned uint_least32_t;
__extension__ typedef long long int_least64_t;
__extension__ typedef unsigned long long uint_least64_t;





typedef signed char int_fast8_t;
typedef unsigned char uint_fast8_t;
typedef short int_fast16_t;
typedef unsigned short uint_fast16_t;
typedef int int_fast32_t;
typedef unsigned int uint_fast32_t;
__extension__ typedef long long int_fast64_t;
__extension__ typedef unsigned long long uint_fast64_t;


__extension__ typedef long long intmax_t;
__extension__ typedef unsigned long long uintmax_t;
# 10 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdint.h" 2 3 4
# 35 "./hdr/libccc/char.h" 2





# 1 "./hdr/libccc_config.h" 1
# 41 "./hdr/libccc/char.h" 2
# 1 "./hdr/libccc_naming.h" 1
# 50 "./hdr/libccc_naming.h"

# 408 "./hdr/libccc_naming.h"

# 42 "./hdr/libccc/char.h" 2


# 1 "./hdr/libccc/text/ascii.h" 1
# 35 "./hdr/libccc/text/ascii.h"
# 1 "./hdr/libccc/bool.h" 1
# 42 "./hdr/libccc/bool.h"

# 91 "./hdr/libccc/bool.h"
 
# 91 "./hdr/libccc/bool.h"
typedef _Bool t_bool;
# 103 "./hdr/libccc/bool.h"

# 174 "./hdr/libccc/bool.h"

# 36 "./hdr/libccc/text/ascii.h" 2




# 51 "./hdr/libccc/text/ascii.h"
typedef char t_ascii;

# 159 "./hdr/libccc/text/ascii.h"
t_bool ASCII_IsLetter(t_ascii c);
# 172 "./hdr/libccc/text/ascii.h"
t_bool ASCII_IsUppercase(t_ascii c);
# 185 "./hdr/libccc/text/ascii.h"
t_bool ASCII_IsLowercase(t_ascii c);
# 198 "./hdr/libccc/text/ascii.h"
t_bool ASCII_IsAlphaNumeric(t_ascii c);
# 213 "./hdr/libccc/text/ascii.h"
t_bool ASCII_IsDigit_Decimal(t_ascii c);
# 228 "./hdr/libccc/text/ascii.h"
t_bool ASCII_IsDigit_Hexadecimal(t_ascii c);
# 242 "./hdr/libccc/text/ascii.h"
t_bool ASCII_IsDigit_Octal(t_ascii c);
# 256 "./hdr/libccc/text/ascii.h"
t_bool ASCII_IsDigit_Binary(t_ascii c);
# 280 "./hdr/libccc/text/ascii.h"
t_bool ASCII_IsWhiteSpace(t_ascii c);
# 293 "./hdr/libccc/text/ascii.h"
t_bool ASCII_IsPunctuation(t_ascii c);
# 308 "./hdr/libccc/text/ascii.h"
t_bool ASCII_IsPrintable(t_ascii c);
# 321 "./hdr/libccc/text/ascii.h"
t_bool ASCII_IsValid(t_ascii c);
# 337 "./hdr/libccc/text/ascii.h"
t_bool ASCII_IsInCharset(t_ascii c, t_ascii const* charset);
# 357 "./hdr/libccc/text/ascii.h"
t_ascii ASCII_ToUppercase(t_ascii c);
# 370 "./hdr/libccc/text/ascii.h"
t_ascii ASCII_ToLowercase(t_ascii c);
# 381 "./hdr/libccc/text/ascii.h"

# 45 "./hdr/libccc/char.h" 2
# 1 "./hdr/libccc/text/unicode.h" 1
# 39 "./hdr/libccc/text/unicode.h"
# 1 "./hdr/libccc/int.h" 1
# 83 "./hdr/libccc/int.h"

# 98 "./hdr/libccc/int.h"
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;



typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
# 128 "./hdr/libccc/int.h"
typedef u8 t_u8;

# 144 "./hdr/libccc/int.h"
typedef u16 t_u16;

# 160 "./hdr/libccc/int.h"
typedef u32 t_u32;

# 176 "./hdr/libccc/int.h"
typedef u64 t_u64;

# 215 "./hdr/libccc/int.h"
typedef s8 t_s8;

# 231 "./hdr/libccc/int.h"
typedef s16 t_s16;

# 247 "./hdr/libccc/int.h"
typedef s32 t_s32;

# 263 "./hdr/libccc/int.h"
typedef s64 t_s64;

# 305 "./hdr/libccc/int.h"
typedef t_u32 t_uint;

# 326 "./hdr/libccc/int.h"
typedef t_s32 t_sint;

# 420 "./hdr/libccc/int.h"
typedef union varuint
{
 t_u8 uc;
 t_u16 us;
 t_u32 ui;
 t_u64 ul;
} u_varuint;

typedef union varsint
{
 t_s8 sc;
 t_s16 ss;
 t_s32 si;
 t_s64 sl;
} u_varsint;
# 982 "./hdr/libccc/int.h"

# 40 "./hdr/libccc/text/unicode.h" 2
# 1 "./hdr/libccc/pointer.h" 1
# 39 "./hdr/libccc/pointer.h"
# 1 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stddef.h" 1 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stddef.h" 1 3 4
# 2 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stddef.h" 2 3 4
# 40 "./hdr/libccc/pointer.h" 2
# 61 "./hdr/libccc/pointer.h"

# 93 "./hdr/libccc/pointer.h"
typedef size_t t_size;






typedef ptrdiff_t t_ptrdiff;








typedef intmax_t t_sintmax;






typedef uintmax_t t_uintmax;








typedef intptr_t t_sintptr;






typedef uintptr_t t_uintptr;

# 200 "./hdr/libccc/pointer.h"

# 41 "./hdr/libccc/text/unicode.h" 2





# 57 "./hdr/libccc/text/unicode.h"
typedef char t_utf8;

# 67 "./hdr/libccc/text/unicode.h"
typedef uint_least16_t t_utf16;

# 77 "./hdr/libccc/text/unicode.h"
typedef uint_least32_t t_utf32;

# 154 "./hdr/libccc/text/unicode.h"
t_bool UTF32_IsLetter(t_utf32 c);
# 167 "./hdr/libccc/text/unicode.h"
t_bool UTF32_IsUppercase(t_utf32 c);
# 180 "./hdr/libccc/text/unicode.h"
t_bool UTF32_IsLowercase(t_utf32 c);
# 193 "./hdr/libccc/text/unicode.h"
t_bool UTF32_IsAlphaNumeric(t_utf32 c);
# 208 "./hdr/libccc/text/unicode.h"
t_bool UTF32_IsDigit_Decimal(t_utf32 c);
# 222 "./hdr/libccc/text/unicode.h"
t_bool UTF32_IsDigit_Hexadecimal(t_utf32 c);
# 235 "./hdr/libccc/text/unicode.h"
t_bool UTF32_IsDigit_Octal(t_utf32 c);
# 248 "./hdr/libccc/text/unicode.h"
t_bool UTF32_IsDigit_Binary(t_utf32 c);
# 263 "./hdr/libccc/text/unicode.h"
t_bool UTF32_IsWhiteSpace(t_utf32 c);
# 276 "./hdr/libccc/text/unicode.h"
t_bool UTF32_IsPunctuation(t_utf32 c);
# 291 "./hdr/libccc/text/unicode.h"
t_bool UTF32_IsPrintable(t_utf32 c);
# 304 "./hdr/libccc/text/unicode.h"
t_bool UTF32_IsASCII(t_utf32 c);
# 316 "./hdr/libccc/text/unicode.h"
t_bool UTF32_IsValid(t_utf32 c);
# 331 "./hdr/libccc/text/unicode.h"
t_bool UTF32_IsInCharset(t_utf32 c, t_utf32 const* charset);
# 356 "./hdr/libccc/text/unicode.h"
t_utf32 UTF32_ToUppercase(t_utf32 c);
# 369 "./hdr/libccc/text/unicode.h"
t_utf32 UTF32_ToLowercase(t_utf32 c);
# 398 "./hdr/libccc/text/unicode.h"
t_size UTF32_ToUTF8(t_utf8* dest, t_utf32 c);
# 413 "./hdr/libccc/text/unicode.h"
t_size UTF32_ToUTF16(t_utf16* dest, t_utf32 c);
# 428 "./hdr/libccc/text/unicode.h"
t_utf32 UTF32_FromUTF8(t_utf8 const* str);
# 441 "./hdr/libccc/text/unicode.h"
t_utf32 UTF32_FromUTF16(t_utf16 const* str);
# 456 "./hdr/libccc/text/unicode.h"
t_utf32 UTF32_Parse(t_ascii const* str);
# 470 "./hdr/libccc/text/unicode.h"
t_size UTF32_Parse_N(t_utf32* dest, t_ascii const* str, t_size n);
# 487 "./hdr/libccc/text/unicode.h"
t_sint UTF8_ByteOrderMark(t_utf8 const* str);
# 497 "./hdr/libccc/text/unicode.h"
t_sint UTF16_ByteOrderMark(t_utf16 const* str);
# 507 "./hdr/libccc/text/unicode.h"
t_sint UTF32_ByteOrderMark(t_utf32 const* str);
# 831 "./hdr/libccc/text/unicode.h"

# 46 "./hdr/libccc/char.h" 2


# 59 "./hdr/libccc/char.h"
typedef t_ascii t_char;

# 296 "./hdr/libccc/char.h"

# 29 "./hdr/libccc/error.h" 2
# 1 "./hdr/libccc/string.h" 1
# 40 "./hdr/libccc/string.h"
# 1 "./hdr/libccc/format.h" 1
# 30 "./hdr/libccc/format.h"
# 1 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 1 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdarg.h" 1 3 4
# 140 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdarg.h" 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/_mingw_stdarg.h" 1 3 4
# 141 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdarg.h" 2 3 4
# 2 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 2 3 4
# 31 "./hdr/libccc/format.h" 2




# 1 "./hdr/libccc.h" 1
# 36 "./hdr/libccc/format.h" 2


# 269 "./hdr/libccc/format.h"
__attribute__((format(gnu_printf, 1, 2)))
__attribute__((malloc))
t_char* String_Format(t_char const* format, ...);






__attribute__((malloc))
t_char* String_Format_VA(t_char const* format, va_list args);
# 300 "./hdr/libccc/format.h"
__attribute__((format(gnu_printf, 3, 4)))
t_size String_Format_N(t_char* dest, t_size max, t_char const* format, ...);






t_size String_Format_N_VA(t_char* dest, t_size max, t_char const* format, va_list args);
# 336 "./hdr/libccc/format.h"

# 41 "./hdr/libccc/string.h" 2



# 80 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_New(t_size n);
# 97 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_New_C(t_size n, t_char c);
# 107 "./hdr/libccc/string.h"
void String_Delete(t_char* *a_str);
# 120 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Duplicate(t_char const* str);
# 133 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Duplicate_N(t_char const* str, t_size n);
# 146 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Duplicate_Char(t_char const* str, t_char const c);
# 159 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Duplicate_Charset(t_char const* str, t_char const* charset);
# 172 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Duplicate_String(t_char const* str, t_char const* target);
# 182 "./hdr/libccc/string.h"
void String_Clear(t_char* str);
# 194 "./hdr/libccc/string.h"
void String_Set(t_char* str, t_char c);
# 210 "./hdr/libccc/string.h"
t_char* String_Copy(t_char* dest, t_char const* src);
# 222 "./hdr/libccc/string.h"
t_char* String_Copy_N(t_char* dest, t_char const* src, t_size n);
# 235 "./hdr/libccc/string.h"
t_size String_Copy_L(t_char* dest, t_char const* src, t_size size);
# 249 "./hdr/libccc/string.h"
t_char* String_Concat(t_char* dest, t_char const* src);
# 261 "./hdr/libccc/string.h"
t_char* String_Concat_N(t_char* dest, t_char const* src, t_size n);
# 274 "./hdr/libccc/string.h"
t_size String_Concat_L(t_char* dest, t_char const* src, t_size size);
# 292 "./hdr/libccc/string.h"
t_size String_Length(t_char const* str);
# 307 "./hdr/libccc/string.h"
t_bool String_Equals(t_char const* str1, t_char const* str2);
# 318 "./hdr/libccc/string.h"
t_bool String_Equals_N(t_char const* str1, t_char const* str2, t_size n);
# 329 "./hdr/libccc/string.h"
t_bool String_Equals_IgnoreCase(t_char const* str1, t_char const* str2);
# 341 "./hdr/libccc/string.h"
t_bool String_Equals_N_IgnoreCase(t_char const* str1, t_char const* str2, t_size n);
# 359 "./hdr/libccc/string.h"
t_sint String_Compare(t_char const* str1, t_char const* str2);
# 370 "./hdr/libccc/string.h"
t_sint String_Compare_N(t_char const* str1, t_char const* str2, t_size n);
# 381 "./hdr/libccc/string.h"
t_sint String_Compare_IgnoreCase(t_char const* str1, t_char const* str2);
# 393 "./hdr/libccc/string.h"
t_sint String_Compare_N_IgnoreCase(t_char const* str1, t_char const* str2, t_size n);
# 411 "./hdr/libccc/string.h"
t_bool String_Has(t_char const* str, t_char const* charset);
# 422 "./hdr/libccc/string.h"
t_bool String_HasOnly(t_char const* str, t_char const* charset);
# 439 "./hdr/libccc/string.h"
t_size String_Count_Char(t_char const* str, t_char c);
# 449 "./hdr/libccc/string.h"
t_size String_Count_Charset(t_char const* str, t_char const* charset);
# 459 "./hdr/libccc/string.h"
t_size String_Count_String(t_char const* str, t_char const* query);
# 478 "./hdr/libccc/string.h"
t_char* String_Find_Char(t_char const* str, t_char c);
# 489 "./hdr/libccc/string.h"
t_char* String_Find_Charset(t_char const* str, t_char const* charset);
# 501 "./hdr/libccc/string.h"
t_char* String_Find_String(t_char const* str, t_char const* query);
# 514 "./hdr/libccc/string.h"
t_char* String_Find_R_Char(t_char const* str, t_char c);
# 526 "./hdr/libccc/string.h"
t_char* String_Find_R_Charset(t_char const* str, t_char const* charset);
# 539 "./hdr/libccc/string.h"
t_char* String_Find_R_String(t_char const* str, t_char const* query);
# 553 "./hdr/libccc/string.h"
t_char* String_Find_N_Char(t_char const* str, t_char c, t_size n);
# 564 "./hdr/libccc/string.h"
t_char* String_Find_N_Charset(t_char const* str, t_char const* charset, t_size n);
# 576 "./hdr/libccc/string.h"
t_char* String_Find_N_String(t_char const* str, t_char const* query, t_size n);
# 589 "./hdr/libccc/string.h"
t_sintmax String_IndexOf_Char(t_char const* str, t_char c);
# 600 "./hdr/libccc/string.h"
t_sintmax String_IndexOf_Charset(t_char const* str, t_char const* charset);
# 612 "./hdr/libccc/string.h"
t_sintmax String_IndexOf_String(t_char const* str, t_char const* query);
# 625 "./hdr/libccc/string.h"
t_sintmax String_IndexOf_R_Char(t_char const* str, t_char c);
# 637 "./hdr/libccc/string.h"
t_sintmax String_IndexOf_R_Charset(t_char const* str, t_char const* charset);
# 650 "./hdr/libccc/string.h"
t_sintmax String_IndexOf_R_String(t_char const* str, t_char const* query);
# 664 "./hdr/libccc/string.h"
t_sintmax String_IndexOf_N_Char(t_char const* str, t_char c, t_size n);
# 675 "./hdr/libccc/string.h"
t_sintmax String_IndexOf_N_Charset(t_char const* str, t_char const* charset, t_size n);
# 687 "./hdr/libccc/string.h"
t_sintmax String_IndexOf_N_String(t_char const* str, t_char const* query, t_size n);
# 706 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Remove(t_char const* str, t_char const* query);
# 720 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Replace_Char(t_char const* str, t_char const char_old, t_char const char_new);
# 733 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Replace_Charset(t_char const* str, t_char const* charset_old, t_char const* charset_new);
# 747 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Replace_String(t_char const* str, t_char const* str_old, t_char const* str_new);
# 766 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Join(t_char const* str1, t_char const* str2);
# 779 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Merge(t_char* *a_str1, t_char* *a_str2);
# 792 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Append(t_char* *dest, t_char const* src);
# 805 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Prepend(t_char const* src, t_char* *dest);
# 823 "./hdr/libccc/string.h"
t_char* String_Insert_InPlace(t_char* *dest, t_char const* src, t_u32 index);
# 836 "./hdr/libccc/string.h"
void String_Replace_Char_InPlace(t_char* str, t_char const char_old, t_char const char_new);
# 849 "./hdr/libccc/string.h"
void String_Replace_Charset_InPlace(t_char* str, t_char const* charset_old, t_char const* charset_new);
# 858 "./hdr/libccc/string.h"
void String_Replace_String_InPlace(t_char* *a_str, t_char const* str_old, t_char const* str_new);
# 873 "./hdr/libccc/string.h"
t_char* String_Map_InPlace(t_char* *a_str, t_char (*map)(t_char));
# 892 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Trim(t_char const* str, t_char const* charset);
# 904 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Trim_L(t_char const* str, t_char const* charset);
# 916 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Trim_R(t_char const* str, t_char const* charset);
# 931 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Pad(t_char const* str, t_char c, t_size length);
# 944 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Pad_L(t_char const* str, t_char c, t_size length);
# 957 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Pad_R(t_char const* str, t_char c, t_size length);
# 1000 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Print(t_char const* str, t_char const* charset_extra);
# 1039 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Parse(t_char const* str, t_bool any_escape);
# 1055 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Reverse(t_char const* str);
# 1069 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Insert(t_char const* dest, t_char const* src, t_size index);
# 1083 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Sub(t_char const* str, t_size index, t_size n);
# 1102 "./hdr/libccc/string.h"
void String_Iterate(t_char* str, void (*f)(t_char* c));
# 1112 "./hdr/libccc/string.h"
void String_Iterate_I(t_char* str, void (*f)(t_char* c, t_size index));
# 1125 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Map(t_char const* str, t_char (*map)(t_char c));
# 1137 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Map_I(t_char const* str, t_char (*map)(t_char c, t_size index));
# 1151 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Filter(t_char const* str, t_bool (*filter)(t_char c));
# 1163 "./hdr/libccc/string.h"
__attribute__((malloc))
t_char* String_Filter_I(t_char const* str, t_bool (*filter)(t_char c, t_size index));
# 1196 "./hdr/libccc/string.h"

# 30 "./hdr/libccc/error.h" 2

# 1 "./hdr/libccc/sys/io.h" 1
# 30 "./hdr/libccc/sys/io.h"
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/fcntl.h" 1 3 4







# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/io.h" 1 3 4
# 10 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/io.h" 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 1 3 4
# 45 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
  
# 45 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
 __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _memccpy(void *_Dst,const void *_Src,int _Val,size_t _MaxCount);
  void *__attribute__((__cdecl__)) memchr(const void *_Buf ,int _Val,size_t _MaxCount);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _memicmp(const void *_Buf1,const void *_Buf2,size_t _Size);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _memicmp_l(const void *_Buf1,const void *_Buf2,size_t _Size,_locale_t _Locale);
  int __attribute__((__cdecl__)) memcmp(const void *_Buf1,const void *_Buf2,size_t _Size);
  void * __attribute__((__cdecl__)) memcpy(void * 
# 50 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                              restrict 
# 50 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                           _Dst,const void * 
# 50 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                                                             restrict 
# 50 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                                                          _Src,size_t _Size) ;
  __attribute__((dllimport)) errno_t __attribute__((__cdecl__)) memcpy_s (void *_dest,size_t _numberOfElements,const void *_src,size_t _count);
  void * __attribute__((__cdecl__)) mempcpy (void *_Dst, const void *_Src, size_t _Size);
  void * __attribute__((__cdecl__)) memset(void *_Dst,int _Val,size_t _Size);

  void * __attribute__((__cdecl__)) memccpy(void *_Dst,const void *_Src,int _Val,size_t _Size) ;
  int __attribute__((__cdecl__)) memicmp(const void *_Buf1,const void *_Buf2,size_t _Size) ;


  char * __attribute__((__cdecl__)) _strset(char *_Str,int _Val) ;
  char * __attribute__((__cdecl__)) _strset_l(char *_Str,int _Val,_locale_t _Locale) ;
  char * __attribute__((__cdecl__)) strcpy(char * 
# 61 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                              restrict 
# 61 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                           _Dest,const char * 
# 61 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                                                              restrict 
# 61 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                                                           _Source);
  char * __attribute__((__cdecl__)) strcat(char * 
# 62 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                              restrict 
# 62 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                           _Dest,const char * 
# 62 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                                                              restrict 
# 62 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                                                           _Source);
  int __attribute__((__cdecl__)) strcmp(const char *_Str1,const char *_Str2);
  size_t __attribute__((__cdecl__)) strlen(const char *_Str);
  size_t __attribute__((__cdecl__)) strnlen(const char *_Str,size_t _MaxCount);
  void *__attribute__((__cdecl__)) memmove(void *_Dst,const void *_Src,size_t _Size) ;
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _strdup(const char *_Src);
  char *__attribute__((__cdecl__)) strchr(const char *_Str,int _Val);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _stricmp(const char *_Str1,const char *_Str2);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _strcmpi(const char *_Str1,const char *_Str2);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _stricmp_l(const char *_Str1,const char *_Str2,_locale_t _Locale);
  int __attribute__((__cdecl__)) strcoll(const char *_Str1,const char *_Str2);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _strcoll_l(const char *_Str1,const char *_Str2,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _stricoll(const char *_Str1,const char *_Str2);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _stricoll_l(const char *_Str1,const char *_Str2,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _strncoll (const char *_Str1,const char *_Str2,size_t _MaxCount);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _strncoll_l(const char *_Str1,const char *_Str2,size_t _MaxCount,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _strnicoll (const char *_Str1,const char *_Str2,size_t _MaxCount);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _strnicoll_l(const char *_Str1,const char *_Str2,size_t _MaxCount,_locale_t _Locale);
  size_t __attribute__((__cdecl__)) strcspn(const char *_Str,const char *_Control);
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _strerror(const char *_ErrMsg) ;
  char *__attribute__((__cdecl__)) strerror(int) ;
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _strlwr(char *_String) ;
  char *strlwr_l(char *_String,_locale_t _Locale) ;
  char *__attribute__((__cdecl__)) strncat(char * 
# 85 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                              restrict 
# 85 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                           _Dest,const char * 
# 85 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                                                              restrict 
# 85 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                                                           _Source,size_t _Count) ;
  int __attribute__((__cdecl__)) strncmp(const char *_Str1,const char *_Str2,size_t _MaxCount);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _strnicmp(const char *_Str1,const char *_Str2,size_t _MaxCount);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _strnicmp_l(const char *_Str1,const char *_Str2,size_t _MaxCount,_locale_t _Locale);
  char *strncpy(char * 
# 89 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                      restrict 
# 89 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                   _Dest,const char * 
# 89 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                                                      restrict 
# 89 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                                                   _Source,size_t _Count) ;
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _strnset(char *_Str,int _Val,size_t _MaxCount) ;
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _strnset_l(char *str,int c,size_t count,_locale_t _Locale) ;
  char *__attribute__((__cdecl__)) strpbrk(const char *_Str,const char *_Control);
  char *__attribute__((__cdecl__)) strrchr(const char *_Str,int _Ch);
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _strrev(char *_Str);
  size_t __attribute__((__cdecl__)) strspn(const char *_Str,const char *_Control);
  char *__attribute__((__cdecl__)) strstr(const char *_Str,const char *_SubStr);
  char *__attribute__((__cdecl__)) strtok(char * 
# 97 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                             restrict 
# 97 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                          _Str,const char * 
# 97 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                                                            restrict 
# 97 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                                                         _Delim) ;
       

  char *strtok_r(char * 
# 100 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                       restrict 
# 100 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                    _Str, const char * 
# 100 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                                                       restrict 
# 100 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                                                    _Delim, char ** 
# 100 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                                                                                    restrict 
# 100 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                                                                                 __last);
       
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _strupr(char *_String) ;
  __attribute__ ((__dllimport__)) char *_strupr_l(char *_String,_locale_t _Locale) ;
  size_t __attribute__((__cdecl__)) strxfrm(char * 
# 104 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                               restrict 
# 104 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                            _Dst,const char * 
# 104 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                                                              restrict 
# 104 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                                                           _Src,size_t _MaxCount);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _strxfrm_l(char * 
# 105 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                                          restrict 
# 105 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                                       _Dst,const char * 
# 105 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                                                                         restrict 
# 105 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                                                                      _Src,size_t _MaxCount,_locale_t _Locale);


  char *__attribute__((__cdecl__)) strdup(const char *_Src) ;
  int __attribute__((__cdecl__)) strcmpi(const char *_Str1,const char *_Str2) ;
  int __attribute__((__cdecl__)) stricmp(const char *_Str1,const char *_Str2) ;
  char *__attribute__((__cdecl__)) strlwr(char *_Str) ;
  int __attribute__((__cdecl__)) strnicmp(const char *_Str1,const char *_Str,size_t _MaxCount) ;
  int __attribute__((__cdecl__)) strncasecmp (const char *, const char *, size_t);
  int __attribute__((__cdecl__)) strcasecmp (const char *, const char *);







  char *__attribute__((__cdecl__)) strnset(char *_Str,int _Val,size_t _MaxCount) ;
  char *__attribute__((__cdecl__)) strrev(char *_Str) ;
  char *__attribute__((__cdecl__)) strset(char *_Str,int _Val) ;
  char *__attribute__((__cdecl__)) strupr(char *_Str) ;





  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wcsdup(const wchar_t *_Str);
  wchar_t *__attribute__((__cdecl__)) wcscat(wchar_t * 
# 132 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                                   restrict 
# 132 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                                _Dest,const wchar_t * 
# 132 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                                                                      restrict 
# 132 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                                                                   _Source) ;
  wchar_t *__attribute__((__cdecl__)) wcschr(const wchar_t *_Str,wchar_t _Ch);
  int __attribute__((__cdecl__)) wcscmp(const wchar_t *_Str1,const wchar_t *_Str2);
  wchar_t *__attribute__((__cdecl__)) wcscpy(wchar_t * 
# 135 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                                   restrict 
# 135 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                                _Dest,const wchar_t * 
# 135 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                                                                      restrict 
# 135 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                                                                   _Source) ;
  size_t __attribute__((__cdecl__)) wcscspn(const wchar_t *_Str,const wchar_t *_Control);
  size_t __attribute__((__cdecl__)) wcslen(const wchar_t *_Str);
  size_t __attribute__((__cdecl__)) wcsnlen(const wchar_t *_Src,size_t _MaxCount);
  wchar_t *wcsncat(wchar_t * 
# 139 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                            restrict 
# 139 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                         _Dest,const wchar_t * 
# 139 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                                                               restrict 
# 139 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                                                            _Source,size_t _Count) ;
  int __attribute__((__cdecl__)) wcsncmp(const wchar_t *_Str1,const wchar_t *_Str2,size_t _MaxCount);
  wchar_t *wcsncpy(wchar_t * 
# 141 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                            restrict 
# 141 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                         _Dest,const wchar_t * 
# 141 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                                                               restrict 
# 141 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                                                            _Source,size_t _Count) ;
  wchar_t *__attribute__((__cdecl__)) _wcsncpy_l(wchar_t * 
# 142 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                                       restrict 
# 142 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                                    _Dest,const wchar_t * 
# 142 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                                                                          restrict 
# 142 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                                                                       _Source,size_t _Count,_locale_t _Locale) ;
  wchar_t *__attribute__((__cdecl__)) wcspbrk(const wchar_t *_Str,const wchar_t *_Control);
  wchar_t *__attribute__((__cdecl__)) wcsrchr(const wchar_t *_Str,wchar_t _Ch);
  size_t __attribute__((__cdecl__)) wcsspn(const wchar_t *_Str,const wchar_t *_Control);
  wchar_t *__attribute__((__cdecl__)) wcsstr(const wchar_t *_Str,const wchar_t *_SubStr);
  wchar_t *__attribute__((__cdecl__)) wcstok(wchar_t * 
# 147 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                                   restrict 
# 147 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                                _Str,const wchar_t * 
# 147 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                                                                     restrict 
# 147 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                                                                  _Delim) ;
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wcserror(int _ErrNum) ;
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) __wcserror(const wchar_t *_Str) ;
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wcsicmp(const wchar_t *_Str1,const wchar_t *_Str2);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wcsicmp_l(const wchar_t *_Str1,const wchar_t *_Str2,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wcsnicmp(const wchar_t *_Str1,const wchar_t *_Str2,size_t _MaxCount);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wcsnicmp_l(const wchar_t *_Str1,const wchar_t *_Str2,size_t _MaxCount,_locale_t _Locale);
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wcsnset(wchar_t *_Str,wchar_t _Val,size_t _MaxCount) ;
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wcsrev(wchar_t *_Str);
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wcsset(wchar_t *_Str,wchar_t _Val) ;
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wcslwr(wchar_t *_String) ;
  __attribute__ ((__dllimport__)) wchar_t *_wcslwr_l(wchar_t *_String,_locale_t _Locale) ;
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wcsupr(wchar_t *_String) ;
  __attribute__ ((__dllimport__)) wchar_t *_wcsupr_l(wchar_t *_String,_locale_t _Locale) ;
  size_t __attribute__((__cdecl__)) wcsxfrm(wchar_t * 
# 161 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                                  restrict 
# 161 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                               _Dst,const wchar_t * 
# 161 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                                                                    restrict 
# 161 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                                                                 _Src,size_t _MaxCount);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _wcsxfrm_l(wchar_t * 
# 162 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                                             restrict 
# 162 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                                          _Dst,const wchar_t * 
# 162 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h"
                                                                               restrict 
# 162 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 3 4
                                                                                            _Src,size_t _MaxCount,_locale_t _Locale);
  int __attribute__((__cdecl__)) wcscoll(const wchar_t *_Str1,const wchar_t *_Str2);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wcscoll_l(const wchar_t *_Str1,const wchar_t *_Str2,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wcsicoll(const wchar_t *_Str1,const wchar_t *_Str2);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wcsicoll_l(const wchar_t *_Str1,const wchar_t *_Str2,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wcsncoll(const wchar_t *_Str1,const wchar_t *_Str2,size_t _MaxCount);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wcsncoll_l(const wchar_t *_Str1,const wchar_t *_Str2,size_t _MaxCount,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wcsnicoll(const wchar_t *_Str1,const wchar_t *_Str2,size_t _MaxCount);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wcsnicoll_l(const wchar_t *_Str1,const wchar_t *_Str2,size_t _MaxCount,_locale_t _Locale);


  wchar_t *__attribute__((__cdecl__)) wcsdup(const wchar_t *_Str) ;

  int __attribute__((__cdecl__)) wcsicmp(const wchar_t *_Str1,const wchar_t *_Str2) ;
  int __attribute__((__cdecl__)) wcsnicmp(const wchar_t *_Str1,const wchar_t *_Str2,size_t _MaxCount) ;
  wchar_t *__attribute__((__cdecl__)) wcsnset(wchar_t *_Str,wchar_t _Val,size_t _MaxCount) ;
  wchar_t *__attribute__((__cdecl__)) wcsrev(wchar_t *_Str) ;
  wchar_t *__attribute__((__cdecl__)) wcsset(wchar_t *_Str,wchar_t _Val) ;
  wchar_t *__attribute__((__cdecl__)) wcslwr(wchar_t *_Str) ;
  wchar_t *__attribute__((__cdecl__)) wcsupr(wchar_t *_Str) ;
  int __attribute__((__cdecl__)) wcsicoll(const wchar_t *_Str1,const wchar_t *_Str2) ;







# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/sec_api/string_s.h" 1 3 4
# 9 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/sec_api/string_s.h" 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 1 3 4
# 10 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/sec_api/string_s.h" 2 3 4
# 24 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/sec_api/string_s.h" 3 4
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _strset_s(char *_Dst,size_t _DstSize,int _Value);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _strerror_s(char *_Buf,size_t _SizeInBytes,const char *_ErrMsg);
  __attribute__((dllimport)) errno_t __attribute__((__cdecl__)) strerror_s(char *_Buf,size_t _SizeInBytes,int _ErrNum);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _strlwr_s(char *_Str,size_t _Size);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _strlwr_s_l(char *_Str,size_t _Size,_locale_t _Locale);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _strnset_s(char *_Str,size_t _Size,int _Val,size_t _MaxCount);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _strupr_s(char *_Str,size_t _Size);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _strupr_s_l(char *_Str,size_t _Size,_locale_t _Locale);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) strncat_s(char *_Dst,size_t _DstSizeInChars,const char *_Src,size_t _MaxCount);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _strncat_s_l(char *_Dst,size_t _DstSizeInChars,const char *_Src,size_t _MaxCount,_locale_t _Locale);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) strcpy_s(char *_Dst, rsize_t _SizeInBytes, const char *_Src);
 
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) strncpy_s(char *_Dst, size_t _DstSizeInChars, const char *_Src, size_t _MaxCount);
 
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _strncpy_s_l(char *_Dst, size_t _DstSizeInChars, const char *_Src, size_t _MaxCount, _locale_t _Locale);
  ;
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) strtok_s(char *_Str,const char *_Delim,char **_Context);
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _strtok_s_l(char *_Str,const char *_Delim,char **_Context,_locale_t _Locale);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) strcat_s(char *_Dst, rsize_t _SizeInBytes, const char * _Src);
 

  __attribute__((dllimport)) errno_t __attribute__((__cdecl__)) memmove_s(void *_dest,size_t _numberOfElements,const void *_src,size_t _count);


  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) wcstok_s(wchar_t *_Str,const wchar_t *_Delim,wchar_t **_Context);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcserror_s(wchar_t *_Buf,size_t _SizeInWords,int _ErrNum);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) __wcserror_s(wchar_t *_Buffer,size_t _SizeInWords,const wchar_t *_ErrMsg);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcsnset_s(wchar_t *_Dst,size_t _DstSizeInWords,wchar_t _Val,size_t _MaxCount);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcsset_s(wchar_t *_Str,size_t _SizeInWords,wchar_t _Val);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcslwr_s(wchar_t *_Str,size_t _SizeInWords);
 
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcslwr_s_l(wchar_t *_Str,size_t _SizeInWords,_locale_t _Locale);
 
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcsupr_s(wchar_t *_Str,size_t _Size);
 
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcsupr_s_l(wchar_t *_Str,size_t _Size,_locale_t _Locale);
 

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) wcscpy_s(wchar_t *_Dst, rsize_t _SizeInWords, const wchar_t *_Src);
 
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) wcscat_s(wchar_t * _Dst, rsize_t _SizeInWords, const wchar_t *_Src);
 

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) wcsncat_s(wchar_t *_Dst,size_t _DstSizeInChars,const wchar_t *_Src,size_t _MaxCount);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcsncat_s_l(wchar_t *_Dst,size_t _DstSizeInChars,const wchar_t *_Src,size_t _MaxCount,_locale_t _Locale);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) wcsncpy_s(wchar_t *_Dst, size_t _DstSizeInChars, const wchar_t *_Src, size_t _MaxCount);
  ;
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcsncpy_s_l(wchar_t *_Dst, size_t _DstSizeInChars, const wchar_t *_Src, size_t _MaxCount, _locale_t _Locale);
  ;
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wcstok_s_l(wchar_t *_Str,const wchar_t *_Delim,wchar_t **_Context,_locale_t _Locale);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcsset_s_l(wchar_t *_Str,size_t _SizeInChars,unsigned int _Val,_locale_t _Locale);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcsnset_s_l(wchar_t *_Str,size_t _SizeInChars,unsigned int _Val, size_t _Count,_locale_t _Locale);

  extern 
# 78 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/sec_api/string_s.h"
 inline 
# 78 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/sec_api/string_s.h" 3 4
 __attribute__((__always_inline__,__gnu_inline__)) size_t __attribute__((__cdecl__)) wcsnlen_s(const wchar_t * _src, size_t _count) {
    return _src ? wcsnlen(_src, _count) : 0;
  }
# 191 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/string.h" 2 3 4
# 11 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/io.h" 2 3 4
# 21 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/io.h" 3 4
#pragma pack(push,_CRT_PACKING)





__attribute__ ((__dllimport__)) char* __attribute__((__cdecl__)) _getcwd (char*, int);

  typedef unsigned long _fsize_t;





  struct _finddata32_t {
    unsigned attrib;
    __time32_t time_create;
    __time32_t time_access;
    __time32_t time_write;
    _fsize_t size;
    char name[260];
  };

  struct _finddata32i64_t {
    unsigned attrib;
    __time32_t time_create;
    __time32_t time_access;
    __time32_t time_write;
    __extension__ long long size;
    char name[260];
  };

  struct _finddata64i32_t {
    unsigned attrib;
    __time64_t time_create;
    __time64_t time_access;
    __time64_t time_write;
    _fsize_t size;
    char name[260];
  };

  struct __finddata64_t {
    unsigned attrib;
    __time64_t time_create;
    __time64_t time_access;
    __time64_t time_write;
    __extension__ long long size;
    char name[260];
  };
# 94 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/io.h" 3 4
  struct _wfinddata32_t {
    unsigned attrib;
    __time32_t time_create;
    __time32_t time_access;
    __time32_t time_write;
    _fsize_t size;
    wchar_t name[260];
  };

  struct _wfinddata32i64_t {
    unsigned attrib;
    __time32_t time_create;
    __time32_t time_access;
    __time32_t time_write;
    __extension__ long long size;
    wchar_t name[260];
  };

  struct _wfinddata64i32_t {
    unsigned attrib;
    __time64_t time_create;
    __time64_t time_access;
    __time64_t time_write;
    _fsize_t size;
    wchar_t name[260];
  };

  struct _wfinddata64_t {
    unsigned attrib;
    __time64_t time_create;
    __time64_t time_access;
    __time64_t time_write;
    __extension__ long long size;
    wchar_t name[260];
  };
# 178 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/io.h" 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/_mingw_off_t.h" 1 3 4




  typedef long _off_t;

  typedef long off32_t;





  __extension__ typedef long long _off64_t;

  __extension__ typedef long long off64_t;
# 26 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/_mingw_off_t.h" 3 4
typedef off32_t off_t;
# 179 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/io.h" 2 3 4
# 187 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/io.h" 3 4
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _access(const char *_Filename,int _AccessMode);
  __attribute__((dllimport)) errno_t __attribute__((__cdecl__)) _access_s(const char *_Filename,int _AccessMode);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _chmod(const char *_Filename,int _Mode);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _chsize(int _FileHandle,long _Size) ;
  __attribute__((dllimport)) errno_t __attribute__((__cdecl__)) _chsize_s (int _FileHandle,long long _Size);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _close(int _FileHandle);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _commit(int _FileHandle);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _creat(const char *_Filename,int _PermissionMode) ;
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _dup(int _FileHandle);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _dup2(int _FileHandleSrc,int _FileHandleDst);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _eof(int _FileHandle);
  __attribute__ ((__dllimport__)) long __attribute__((__cdecl__)) _filelength(int _FileHandle);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _findfirst32(const char *_Filename,struct _finddata32_t *_FindData);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _findnext32(intptr_t _FindHandle,struct _finddata32_t *_FindData);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _findclose(intptr_t _FindHandle);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _isatty(int _FileHandle);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _locking(int _FileHandle,int _LockMode,long _NumOfBytes);
  __attribute__ ((__dllimport__)) long __attribute__((__cdecl__)) _lseek(int _FileHandle,long _Offset,int _Origin);
  _off64_t lseek64(int fd,_off64_t offset, int whence);
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _mktemp(char *_TemplateName) ;
  __attribute__((dllimport)) errno_t __attribute__((__cdecl__)) _mktemp_s (char *_TemplateName,size_t _Size);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _pipe(int *_PtHandles,unsigned int _PipeSize,int _TextMode);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _read(int _FileHandle,void *_DstBuf,unsigned int _MaxCharCount);



  int __attribute__((__cdecl__)) remove(const char *_Filename);
  int __attribute__((__cdecl__)) rename(const char *_OldFilename,const char *_NewFilename);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _unlink(const char *_Filename);

  int __attribute__((__cdecl__)) unlink(const char *_Filename) ;



  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _setmode(int _FileHandle,int _Mode);
  __attribute__ ((__dllimport__)) long __attribute__((__cdecl__)) _tell(int _FileHandle);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _umask(int _Mode) ;
  __attribute__((dllimport)) errno_t __attribute__((__cdecl__)) _umask_s (int _NewMode,int *_OldMode);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _write(int _FileHandle,const void *_Buf,unsigned int _MaxCharCount);

  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _filelengthi64(int _FileHandle);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _findfirst32i64(const char *_Filename,struct _finddata32i64_t *_FindData);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _findfirst64(const char *_Filename,struct __finddata64_t *_FindData);



  intptr_t __attribute__((__cdecl__)) _findfirst64i32(const char *_Filename,struct _finddata64i32_t *_FindData);
# 254 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/io.h" 3 4
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _findnext32i64(intptr_t _FindHandle,struct _finddata32i64_t *_FindData);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _findnext64(intptr_t _FindHandle,struct __finddata64_t *_FindData);
  int __attribute__((__cdecl__)) _findnext64i32(intptr_t _FindHandle,struct _finddata64i32_t *_FindData);
# 275 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/io.h" 3 4
  __extension__ long long __attribute__((__cdecl__)) _lseeki64(int _FileHandle,long long _Offset,int _Origin);
  __extension__ long long __attribute__((__cdecl__)) _telli64(int _FileHandle);



  int __attribute__((__cdecl__)) chdir (const char *) ;
  char *__attribute__((__cdecl__)) getcwd (char *, int) ;
  int __attribute__((__cdecl__)) mkdir (const char *) ;
  char *__attribute__((__cdecl__)) mktemp(char *) ;
  int __attribute__((__cdecl__)) rmdir (const char*) ;
  int __attribute__((__cdecl__)) chmod (const char *, int) ;



  __attribute__((dllimport)) errno_t __attribute__((__cdecl__)) _sopen_s(int *_FileHandle,const char *_Filename,int _OpenFlag,int _ShareFlag,int _PermissionMode);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _open(const char *_Filename,int _OpenFlag,...) ;
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _sopen(const char *_Filename,int _OpenFlag,int _ShareFlag,...) ;



  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _waccess(const wchar_t *_Filename,int _AccessMode);
  __attribute__((dllimport)) errno_t __attribute__((__cdecl__)) _waccess_s (const wchar_t *_Filename,int _AccessMode);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wchmod(const wchar_t *_Filename,int _Mode);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wcreat(const wchar_t *_Filename,int _PermissionMode) ;
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wfindfirst32(const wchar_t *_Filename,struct _wfinddata32_t *_FindData);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wfindnext32(intptr_t _FindHandle,struct _wfinddata32_t *_FindData);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wunlink(const wchar_t *_Filename);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wrename(const wchar_t *_OldFilename,const wchar_t *_NewFilename);
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wmktemp(wchar_t *_TemplateName) ;
  __attribute__((dllimport)) errno_t __attribute__((__cdecl__)) _wmktemp_s (wchar_t *_TemplateName, size_t _SizeInWords);

  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wfindfirst32i64(const wchar_t *_Filename,struct _wfinddata32i64_t *_FindData);
  intptr_t __attribute__((__cdecl__)) _wfindfirst64i32(const wchar_t *_Filename,struct _wfinddata64i32_t *_FindData);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wfindfirst64(const wchar_t *_Filename,struct _wfinddata64_t *_FindData);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wfindnext32i64(intptr_t _FindHandle,struct _wfinddata32i64_t *_FindData);
  int __attribute__((__cdecl__)) _wfindnext64i32(intptr_t _FindHandle,struct _wfinddata64i32_t *_FindData);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wfindnext64(intptr_t _FindHandle,struct _wfinddata64_t *_FindData);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wsopen_s(int *_FileHandle,const wchar_t *_Filename,int _OpenFlag,int _ShareFlag,int _PermissionFlag);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wopen(const wchar_t *_Filename,int _OpenFlag,...) ;
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wsopen(const wchar_t *_Filename,int _OpenFlag,int _ShareFlag,...) ;



  int __attribute__((__cdecl__)) __lock_fhandle(int _Filehandle);
  void __attribute__((__cdecl__)) _unlock_fhandle(int _Filehandle);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _get_osfhandle(int _FileHandle);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _open_osfhandle(intptr_t _OSFileHandle,int _Flags);


  int __attribute__((__cdecl__)) access(const char *_Filename,int _AccessMode) ;
  int __attribute__((__cdecl__)) chmod(const char *_Filename,int _AccessMode) ;
  int __attribute__((__cdecl__)) chsize(int _FileHandle,long _Size) ;
  int __attribute__((__cdecl__)) close(int _FileHandle) ;
  int __attribute__((__cdecl__)) creat(const char *_Filename,int _PermissionMode) ;
  int __attribute__((__cdecl__)) dup(int _FileHandle) ;
  int __attribute__((__cdecl__)) dup2(int _FileHandleSrc,int _FileHandleDst) ;
  int __attribute__((__cdecl__)) eof(int _FileHandle) ;
  long __attribute__((__cdecl__)) filelength(int _FileHandle) ;
  int __attribute__((__cdecl__)) isatty(int _FileHandle) ;
  int __attribute__((__cdecl__)) locking(int _FileHandle,int _LockMode,long _NumOfBytes) ;
  long __attribute__((__cdecl__)) lseek(int _FileHandle,long _Offset,int _Origin) ;
  char *__attribute__((__cdecl__)) mktemp(char *_TemplateName) ;
  int __attribute__((__cdecl__)) open(const char *_Filename,int _OpenFlag,...) ;
  int __attribute__((__cdecl__)) read(int _FileHandle,void *_DstBuf,unsigned int _MaxCharCount) ;
  int __attribute__((__cdecl__)) setmode(int _FileHandle,int _Mode) ;
  int __attribute__((__cdecl__)) sopen(const char *_Filename,int _OpenFlag,int _ShareFlag,...) ;
  long __attribute__((__cdecl__)) tell(int _FileHandle) ;
  int __attribute__((__cdecl__)) umask(int _Mode) ;
  int __attribute__((__cdecl__)) write(int _Filehandle,const void *_Buf,unsigned int _MaxCharCount) ;
# 492 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/io.h" 3 4
#pragma pack(pop)
# 9 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/fcntl.h" 2 3 4
# 31 "./hdr/libccc/sys/io.h" 2
# 58 "./hdr/libccc/sys/io.h"
# 1 "./hdr/libccc/color.h" 1
# 40 "./hdr/libccc/color.h"

# 49 "./hdr/libccc/color.h"

# 49 "./hdr/libccc/color.h"
typedef t_u16 t_argb16;

# 68 "./hdr/libccc/color.h"
typedef t_u32 t_argb32;

# 87 "./hdr/libccc/color.h"
typedef struct argb
{
 t_float a;
 t_float r;
 t_float g;
 t_float b;
} s_argb;





typedef struct ahsl
{
 t_float a;
 t_float hue;
 t_float sat;
 t_float lum;
} s_ahsl;

# 467 "./hdr/libccc/color.h"

# 59 "./hdr/libccc/sys/io.h" 2
# 1 "./hdr/libccc/sys/ansi.h" 1
# 32 "./hdr/libccc/sys/ansi.h"

# 145 "./hdr/libccc/sys/ansi.h"

# 60 "./hdr/libccc/sys/io.h" 2




# 75 "./hdr/libccc/sys/io.h"
typedef int t_fd;

# 107 "./hdr/libccc/sys/io.h"
typedef unsigned int t_io_mode;

# 133 "./hdr/libccc/sys/io.h"
typedef unsigned int t_io_open;

# 174 "./hdr/libccc/sys/io.h"
t_u8 IO_GetColor(t_argb32 color);
# 186 "./hdr/libccc/sys/io.h"
t_bool IO_IsTerminal(t_fd fd);
# 209 "./hdr/libccc/sys/io.h"
t_fd IO_Open(t_char const* filepath, t_io_open flags, t_io_mode mode);
# 222 "./hdr/libccc/sys/io.h"
e_cccerror IO_Close(t_fd fd);
# 236 "./hdr/libccc/sys/io.h"
e_cccerror IO_ChangeMode(t_char const* filepath, t_io_mode mode);
# 285 "./hdr/libccc/sys/io.h"
t_sintmax IO_Read_File(t_fd const fd, t_char* *a_file, t_size max);
# 305 "./hdr/libccc/sys/io.h"
t_sintmax IO_Read_Lines(t_fd const fd, t_char** *a_strarr);
# 325 "./hdr/libccc/sys/io.h"
int IO_Read_NextLine(t_fd const fd, t_char* *a_line);
# 346 "./hdr/libccc/sys/io.h"
t_size IO_Write_Char(t_fd fd, t_char c);






t_size IO_Write_String(t_fd fd, t_char const* str);






t_size IO_Write_Line(t_fd fd, t_char const* str);






t_size IO_Write_Lines(t_fd fd, t_char const** strarr);






t_size IO_Write_Memory(t_fd fd, t_u8 const* ptr, t_size n, t_u8 cols);






__attribute__((format(gnu_printf, 2, 3)))
t_size IO_Write_Format(t_fd fd, t_char const* format, ...);
# 398 "./hdr/libccc/sys/io.h"
t_size IO_Output_Char(t_char c);







t_size IO_Output_String(t_char const* str);







t_size IO_Output_Line(t_char const* str);







t_size IO_Output_Lines(t_char const** strarr);







t_size IO_Output_Memory(t_u8 const* ptr, t_size n, t_u8 cols);







__attribute__((format(gnu_printf, 1, 2)))
t_size IO_Output_Format(t_char const* format, ...);
# 450 "./hdr/libccc/sys/io.h"

# 32 "./hdr/libccc/error.h" 2


# 42 "./hdr/libccc/error.h"
typedef void (*f_ccchandler)(e_cccerror, char*);
# 63 "./hdr/libccc/error.h"
t_char* Error_STDC(int errno_value);
# 72 "./hdr/libccc/error.h"
e_cccerror Error_Get(void);


e_cccerror Error_Set(e_cccerror error);




t_char* Error_GetMessage(e_cccerror error);


t_char* Error_GetName(e_cccerror error);


e_cccerror Error_GetCode(t_char const* name);




void Error_Handle(e_cccerror error, t_char const* funcname, t_char* message);


void Error_Handler(e_cccerror error, t_char* message);




f_ccchandler Error_GetHandler(e_cccerror error);


void Error_SetHandler(e_cccerror error, f_ccchandler handler);


void Error_SetAllHandlers(f_ccchandler handler);







# 84 "./hdr/libccc.h" 2
# 1 "./hdr/libccc/char.h" 1
# 85 "./hdr/libccc.h" 2
# 1 "./hdr/libccc/bool.h" 1
# 86 "./hdr/libccc.h" 2
# 1 "./hdr/libccc/int.h" 1
# 87 "./hdr/libccc.h" 2
# 1 "./hdr/libccc/fixed.h" 1
# 78 "./hdr/libccc/fixed.h"
# 1 "./hdr/libccc/float.h" 1
# 47 "./hdr/libccc/float.h"

# 63 "./hdr/libccc/float.h"
typedef float t_f32;








typedef double t_f64;

# 136 "./hdr/libccc/float.h"
typedef t_f32 t_float;

# 397 "./hdr/libccc/float.h"
typedef union float_cast
{
 t_float value_float;

 t_s32 value_int;





} u_float_cast;
# 423 "./hdr/libccc/float.h"
typedef union varfloat
{
 t_f32 f;
 t_f64 d;






} u_varfloat;
# 934 "./hdr/libccc/float.h"

# 79 "./hdr/libccc/fixed.h" 2




# 184 "./hdr/libccc/fixed.h"
 typedef t_s16 t_q16;

# 197 "./hdr/libccc/fixed.h"
 typedef t_s32 t_q32;

# 210 "./hdr/libccc/fixed.h"
 typedef t_s64 t_q64;

# 249 "./hdr/libccc/fixed.h"
typedef t_q32 t_fixed;

# 324 "./hdr/libccc/fixed.h"
t_q16 Q16(t_s16 part_integer, t_u16 part_fraction, t_u16 denominator);
t_q32 Q32(t_s32 part_integer, t_u32 part_fraction, t_u32 denominator);
t_q64 Q64(t_s64 part_integer, t_u64 part_fraction, t_u64 denominator);
# 345 "./hdr/libccc/fixed.h"
t_q16 Q16_FromInt(t_s16 number);
t_q32 Q32_FromInt(t_s32 number);
t_q64 Q64_FromInt(t_s64 number);
# 364 "./hdr/libccc/fixed.h"
t_q16 Q16_FromFloat(t_f64 number);
t_q32 Q32_FromFloat(t_f64 number);
t_q64 Q64_FromFloat(t_f64 number);
# 385 "./hdr/libccc/fixed.h"
t_s16 Q16_IntegerPart(t_q16 number);
t_s32 Q32_IntegerPart(t_q32 number);
t_s64 Q64_IntegerPart(t_q64 number);
# 404 "./hdr/libccc/fixed.h"
t_s16 Q16_FractionPart(t_q16 number);
t_s32 Q32_FractionPart(t_q32 number);
t_s64 Q64_FractionPart(t_q64 number);
# 436 "./hdr/libccc/fixed.h"
t_bool Q16_Equals(t_q16 number1, t_q16 number2);
t_bool Q32_Equals(t_q32 number1, t_q32 number2);
t_bool Q64_Equals(t_q64 number1, t_q64 number2);
# 461 "./hdr/libccc/fixed.h"
t_bool Q16_EqualsApprox(t_q16 number1, t_q16 number2);
t_bool Q32_EqualsApprox(t_q32 number1, t_q32 number2);
t_bool Q64_EqualsApprox(t_q64 number1, t_q64 number2);
# 498 "./hdr/libccc/fixed.h"
__attribute__((malloc)) t_char* Q16_ToString(t_q16 number);
__attribute__((malloc)) t_char* Q32_ToString(t_q32 number);
__attribute__((malloc)) t_char* Q64_ToString(t_q64 number);
# 521 "./hdr/libccc/fixed.h"
__attribute__((malloc)) t_char* Q16_ToString_Hex(t_q16 number);
__attribute__((malloc)) t_char* Q32_ToString_Hex(t_q32 number);
__attribute__((malloc)) t_char* Q64_ToString_Hex(t_q64 number);
# 544 "./hdr/libccc/fixed.h"
__attribute__((malloc)) t_char* Q16_ToString_Bin(t_q16 number);
__attribute__((malloc)) t_char* Q32_ToString_Bin(t_q32 number);
__attribute__((malloc)) t_char* Q64_ToString_Bin(t_q64 number);
# 568 "./hdr/libccc/fixed.h"
__attribute__((malloc)) t_char* Q16_ToString_Base(t_q16 number, t_char const* base);
__attribute__((malloc)) t_char* Q32_ToString_Base(t_q32 number, t_char const* base);
__attribute__((malloc)) t_char* Q64_ToString_Base(t_q64 number, t_char const* base);
# 600 "./hdr/libccc/fixed.h"
t_q16 Q16_FromString(t_char const* str);
t_q32 Q32_FromString(t_char const* str);
t_q64 Q64_FromString(t_char const* str);
# 624 "./hdr/libccc/fixed.h"
t_q16 Q16_FromString_Hex(t_char const* str);
t_q32 Q32_FromString_Hex(t_char const* str);
t_q64 Q64_FromString_Hex(t_char const* str);
# 648 "./hdr/libccc/fixed.h"
t_q16 Q16_FromString_Bin(t_char const* str);
t_q32 Q32_FromString_Bin(t_char const* str);
t_q64 Q64_FromString_Bin(t_char const* str);
# 673 "./hdr/libccc/fixed.h"
t_q16 Q16_FromString_Base(t_char const* str, t_char const* base);
t_q32 Q32_FromString_Base(t_char const* str, t_char const* base);
t_q64 Q64_FromString_Base(t_char const* str, t_char const* base);
# 693 "./hdr/libccc/fixed.h"

# 88 "./hdr/libccc.h" 2
# 1 "./hdr/libccc/float.h" 1
# 89 "./hdr/libccc.h" 2
# 1 "./hdr/libccc/pointer.h" 1
# 90 "./hdr/libccc.h" 2




# 102 "./hdr/libccc.h"

# 3 "src/bool/bool_to_str.c" 2

# 1 "./hdr/libccc/memory.h" 1
# 41 "./hdr/libccc/memory.h"

# 93 "./hdr/libccc/memory.h"
__attribute__((malloc))
void* Memory_New(t_size size);
# 109 "./hdr/libccc/memory.h"
__attribute__((malloc))
void* Memory_New_C(t_size size, char c);
# 126 "./hdr/libccc/memory.h"
__attribute__((malloc))
void* Memory_Allocate(t_size size);
# 145 "./hdr/libccc/memory.h"
__attribute__((malloc))
void* Memory_Reallocate(void* ptr, t_size size);
# 160 "./hdr/libccc/memory.h"
void Memory_Deallocate(void* ptr);
# 176 "./hdr/libccc/memory.h"
void Memory_Delete(void* *a_ptr);
# 188 "./hdr/libccc/memory.h"
void Memory_Set(void* ptr, t_u8 byte, t_size n);
# 197 "./hdr/libccc/memory.h"
void Memory_Clear(void* ptr, t_size n);
# 209 "./hdr/libccc/memory.h"
void* Memory_Copy(void* dest, void const* src, t_size n);
# 220 "./hdr/libccc/memory.h"
void* Memory_Copy_C(void* dest, void const* src, t_u8 byte, t_size n);
# 231 "./hdr/libccc/memory.h"
void* Memory_Move(void* dest, void const* src, t_size n);
# 244 "./hdr/libccc/memory.h"
__attribute__((malloc))
void* Memory_Duplicate(void const* ptr, t_size n);
# 260 "./hdr/libccc/memory.h"
void* Memory_Join(void const* ptr1, t_size length1, void const* ptr2, t_size length2);






void* Memory_Append(void* *a_dest, t_size dest_length, void const* src, t_size src_length);






void* Memory_Prepend(void const* src, t_size src_length, void* *a_dest, t_size dest_length);






void* Memory_Merge(void* *a_ptr1, t_size length1, void* *a_ptr2, t_size length2);
# 300 "./hdr/libccc/memory.h"
void* Memory_Find(void const* ptr, t_u8 byte, t_size n);
# 313 "./hdr/libccc/memory.h"
void Memory_Replace(void* ptr, t_u8 old, t_u8 new, t_size n);
# 328 "./hdr/libccc/memory.h"
t_sint Memory_Compare(void const* ptr1, void const* ptr2, t_size n);
# 344 "./hdr/libccc/memory.h"
t_bool Memory_Swap(void* ptr1, void* ptr2, t_size size);
# 357 "./hdr/libccc/memory.h"
t_u64 Memory_GetBits(t_u64 value, t_u8 bit, t_u8 length);
# 401 "./hdr/libccc/memory.h"

# 5 "src/bool/bool_to_str.c" 2

# 1 "./hdr/libccc/error.h" 1
# 7 "src/bool/bool_to_str.c" 2



t_char* Bool_ToString(t_bool value, t_bool uppercase)
{
 t_char* result;

 result = (t_char*)Memory_Allocate(value ? 5 : 6);
 if ((result == 
# 15 "src/bool/bool_to_str.c" 3 4
((void *)0)
# 15 "src/bool/bool_to_str.c"
)) { Error_Set(ERROR_ALLOCFAILURE); if (1) Error_Handle(ERROR_ALLOCFAILURE, __func__, 
# 15 "src/bool/bool_to_str.c" 3 4
((void *)0)
# 15 "src/bool/bool_to_str.c"
); return (
# 15 "src/bool/bool_to_str.c" 3 4
((void *)0)
# 15 "src/bool/bool_to_str.c"
); }
 if (value)
 {
  result[0] = uppercase ? 'T' : 't';
  result[1] = uppercase ? 'R' : 'r';
  result[2] = uppercase ? 'U' : 'u';
  result[3] = uppercase ? 'E' : 'e';
  result[4] = '\0';
 }
 else
 {
  result[0] = uppercase ? 'F' : 'f';
  result[1] = uppercase ? 'A' : 'a';
  result[2] = uppercase ? 'L' : 'l';
  result[3] = uppercase ? 'S' : 's';
  result[4] = uppercase ? 'E' : 'e';
  result[5] = '\0';
 }
 return (result);
}
