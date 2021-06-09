

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

 typedef _Bool t_bool;


typedef __signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;
typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;



typedef int8_t int_fast8_t;
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef int64_t int_fast64_t;
typedef uint8_t uint_fast8_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
typedef uint64_t uint_fast64_t;





typedef signed char __int8_t;



typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef long long __int64_t;
typedef unsigned long long __uint64_t;

typedef long __darwin_intptr_t;
typedef unsigned int __darwin_natural_t;
typedef int __darwin_ct_rune_t;





typedef union {
 char __mbstate8[128];
 long long _mbstateL;
} __mbstate_t;

typedef __mbstate_t __darwin_mbstate_t;


typedef long int __darwin_ptrdiff_t;







typedef long unsigned int __darwin_size_t;





typedef __builtin_va_list __darwin_va_list;





typedef int __darwin_wchar_t;




typedef __darwin_wchar_t __darwin_rune_t;


typedef int __darwin_wint_t;




typedef unsigned long __darwin_clock_t;
typedef __uint32_t __darwin_socklen_t;
typedef long __darwin_ssize_t;
typedef long __darwin_time_t;
typedef __int64_t __darwin_blkcnt_t;
typedef __int32_t __darwin_blksize_t;
typedef __int32_t __darwin_dev_t;
typedef unsigned int __darwin_fsblkcnt_t;
typedef unsigned int __darwin_fsfilcnt_t;
typedef __uint32_t __darwin_gid_t;
typedef __uint32_t __darwin_id_t;
typedef __uint64_t __darwin_ino64_t;

typedef __darwin_ino64_t __darwin_ino_t;



typedef __darwin_natural_t __darwin_mach_port_name_t;
typedef __darwin_mach_port_name_t __darwin_mach_port_t;
typedef __uint16_t __darwin_mode_t;
typedef __int64_t __darwin_off_t;
typedef __int32_t __darwin_pid_t;
typedef __uint32_t __darwin_sigset_t;
typedef __int32_t __darwin_suseconds_t;
typedef __uint32_t __darwin_uid_t;
typedef __uint32_t __darwin_useconds_t;
typedef unsigned char __darwin_uuid_t[16];
typedef char __darwin_uuid_string_t[37];


struct __darwin_pthread_handler_rec {
 void (*__routine)(void *);
 void *__arg;
 struct __darwin_pthread_handler_rec *__next;
};

struct _opaque_pthread_attr_t {
 long __sig;
 char __opaque[56];
};

struct _opaque_pthread_cond_t {
 long __sig;
 char __opaque[40];
};

struct _opaque_pthread_condattr_t {
 long __sig;
 char __opaque[8];
};

struct _opaque_pthread_mutex_t {
 long __sig;
 char __opaque[56];
};

struct _opaque_pthread_mutexattr_t {
 long __sig;
 char __opaque[8];
};

struct _opaque_pthread_once_t {
 long __sig;
 char __opaque[8];
};

struct _opaque_pthread_rwlock_t {
 long __sig;
 char __opaque[192];
};

struct _opaque_pthread_rwlockattr_t {
 long __sig;
 char __opaque[16];
};

struct _opaque_pthread_t {
 long __sig;
 struct __darwin_pthread_handler_rec *__cleanup_stack;
 char __opaque[8176];
};

typedef struct _opaque_pthread_attr_t __darwin_pthread_attr_t;
typedef struct _opaque_pthread_cond_t __darwin_pthread_cond_t;
typedef struct _opaque_pthread_condattr_t __darwin_pthread_condattr_t;
typedef unsigned long __darwin_pthread_key_t;
typedef struct _opaque_pthread_mutex_t __darwin_pthread_mutex_t;
typedef struct _opaque_pthread_mutexattr_t __darwin_pthread_mutexattr_t;
typedef struct _opaque_pthread_once_t __darwin_pthread_once_t;
typedef struct _opaque_pthread_rwlock_t __darwin_pthread_rwlock_t;
typedef struct _opaque_pthread_rwlockattr_t __darwin_pthread_rwlockattr_t;
typedef struct _opaque_pthread_t *__darwin_pthread_t;
typedef unsigned char u_int8_t;
typedef unsigned short u_int16_t;
typedef unsigned int u_int32_t;
typedef unsigned long long u_int64_t;


typedef int64_t register_t;





typedef unsigned long uintptr_t;



typedef u_int64_t user_addr_t;
typedef u_int64_t user_size_t;
typedef int64_t user_ssize_t;
typedef int64_t user_long_t;
typedef u_int64_t user_ulong_t;
typedef int64_t user_time_t;
typedef int64_t user_off_t;







typedef u_int64_t syscall_arg_t;

typedef __darwin_intptr_t intptr_t;




typedef long int intmax_t;
typedef long unsigned int uintmax_t;






typedef char t_ascii;
typedef char t_utf8;
typedef uint_least16_t t_utf16;
typedef uint_least32_t t_utf32;
typedef t_ascii t_char;


typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;



typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;





typedef u8 t_u8;
typedef u16 t_u16;
typedef u32 t_u32;
typedef u64 t_u64;
typedef s8 t_s8;
typedef s16 t_s16;
typedef s32 t_s32;
typedef s64 t_s64;
typedef t_u32 t_uint;
typedef t_s32 t_sint;


 typedef s16 t_q16;
 typedef s32 t_q32;
 typedef s64 t_q64;
typedef t_q32 t_fixed;


typedef float t_f32;
typedef double t_f64;
typedef t_f64 t_float;
typedef union float_cast
{
 t_float value_float;



 s64 value_int;



} u_float_cast;


typedef long int ptrdiff_t;
typedef long unsigned int size_t;
typedef long unsigned int rsize_t;
typedef int wchar_t;
typedef long double max_align_t;
typedef size_t t_size;






typedef ptrdiff_t t_ptrdiff;
typedef intmax_t t_sintmax;






typedef uintmax_t t_uintmax;
typedef intptr_t t_sintptr;






typedef uintptr_t t_uintptr;


typedef t_u16 t_argb16;
typedef t_u32 t_argb32;
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
t_bool ASCII_IsLetter(t_ascii c);
t_bool ASCII_IsUppercase(t_ascii c);
t_bool ASCII_IsLowercase(t_ascii c);
t_bool ASCII_IsAlphaNumeric(t_ascii c);
t_bool ASCII_IsDigit_Decimal(t_ascii c);
t_bool ASCII_IsDigit_Hexadecimal(t_ascii c);
t_bool ASCII_IsDigit_Octal(t_ascii c);
t_bool ASCII_IsDigit_Binary(t_ascii c);
t_bool ASCII_IsWhiteSpace(t_ascii c);
t_bool ASCII_IsPunctuation(t_ascii c);
t_bool ASCII_IsPrintable(t_ascii c);
t_bool ASCII_IsValid(t_ascii c);
t_bool ASCII_IsInCharset(t_ascii c, t_ascii const* charset);
t_ascii ASCII_ToUppercase(t_ascii c);
t_ascii ASCII_ToLowercase(t_ascii c);
t_bool UTF32_IsLetter(t_utf32 c);
t_bool UTF32_IsUppercase(t_utf32 c);
t_bool UTF32_IsLowercase(t_utf32 c);
t_bool UTF32_IsAlphaNumeric(t_utf32 c);
t_bool UTF32_IsDigit_Decimal(t_utf32 c);
t_bool UTF32_IsDigit_Hexadecimal(t_utf32 c);
t_bool UTF32_IsDigit_Octal(t_utf32 c);
t_bool UTF32_IsDigit_Binary(t_utf32 c);
t_bool UTF32_IsWhiteSpace(t_utf32 c);
t_bool UTF32_IsPunctuation(t_utf32 c);
t_bool UTF32_IsPrintable(t_utf32 c);
t_bool UTF32_IsASCII(t_utf32 c);
t_bool UTF32_IsValid(t_utf32 c);
t_bool UTF32_IsInCharset(t_utf32 c, t_utf32 const* charset);
t_utf32 UTF32_ToUppercase(t_utf32 c);
t_utf32 UTF32_ToLowercase(t_utf32 c);
t_size UTF32_ToUTF8(t_utf8* dest, t_utf32 c);
t_size UTF32_ToUTF16(t_utf16* dest, t_utf32 c);
t_utf32 UTF32_FromUTF8(t_utf8 const* str);
t_utf32 UTF32_FromUTF16(t_utf16 const* str);
t_utf32 UTF32_Parse(t_ascii const* str);
t_size UTF32_Parse_N(t_utf32* dest, t_ascii const* str, t_size n);
t_sint UTF8_ByteOrderMark(t_utf8 const* str);
t_sint UTF16_ByteOrderMark(t_utf16 const* str);
t_sint UTF32_ByteOrderMark(t_utf32 const* str);
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;



typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
__attribute__((malloc)) t_char* U8_ToString(t_u8 number);
__attribute__((malloc)) t_char* U16_ToString(t_u16 number);
__attribute__((malloc)) t_char* U32_ToString(t_u32 number);
__attribute__((malloc)) t_char* U64_ToString(t_u64 number);
__attribute__((malloc)) t_char* S8_ToString(t_s8 number);
__attribute__((malloc)) t_char* S16_ToString(t_s16 number);
__attribute__((malloc)) t_char* S32_ToString(t_s32 number);
__attribute__((malloc)) t_char* S64_ToString(t_s64 number);
__attribute__((malloc)) t_char* U8_ToString_Hex(t_u8 number, t_bool prefix);
__attribute__((malloc)) t_char* U16_ToString_Hex(t_u16 number, t_bool prefix);
__attribute__((malloc)) t_char* U32_ToString_Hex(t_u32 number, t_bool prefix);
__attribute__((malloc)) t_char* U64_ToString_Hex(t_u64 number, t_bool prefix);
__attribute__((malloc)) t_char* S8_ToString_Hex(t_s8 number, t_bool prefix);
__attribute__((malloc)) t_char* S16_ToString_Hex(t_s16 number, t_bool prefix);
__attribute__((malloc)) t_char* S32_ToString_Hex(t_s32 number, t_bool prefix);
__attribute__((malloc)) t_char* S64_ToString_Hex(t_s64 number, t_bool prefix);
__attribute__((malloc)) t_char* U8_ToString_Oct(t_u8 number, t_bool prefix);
__attribute__((malloc)) t_char* U16_ToString_Oct(t_u16 number, t_bool prefix);
__attribute__((malloc)) t_char* U32_ToString_Oct(t_u32 number, t_bool prefix);
__attribute__((malloc)) t_char* U64_ToString_Oct(t_u64 number, t_bool prefix);
__attribute__((malloc)) t_char* S8_ToString_Oct(t_s8 number, t_bool prefix);
__attribute__((malloc)) t_char* S16_ToString_Oct(t_s16 number, t_bool prefix);
__attribute__((malloc)) t_char* S32_ToString_Oct(t_s32 number, t_bool prefix);
__attribute__((malloc)) t_char* S64_ToString_Oct(t_s64 number, t_bool prefix);
__attribute__((malloc)) t_char* U8_ToString_Bin(t_u8 number, t_bool prefix);
__attribute__((malloc)) t_char* U16_ToString_Bin(t_u16 number, t_bool prefix);
__attribute__((malloc)) t_char* U32_ToString_Bin(t_u32 number, t_bool prefix);
__attribute__((malloc)) t_char* U64_ToString_Bin(t_u64 number, t_bool prefix);
__attribute__((malloc)) t_char* S8_ToString_Bin(t_s8 number, t_bool prefix);
__attribute__((malloc)) t_char* S16_ToString_Bin(t_s16 number, t_bool prefix);
__attribute__((malloc)) t_char* S32_ToString_Bin(t_s32 number, t_bool prefix);
__attribute__((malloc)) t_char* S64_ToString_Bin(t_s64 number, t_bool prefix);
__attribute__((malloc)) t_char* U8_ToString_Base(t_u8 number, t_char const* base);
__attribute__((malloc)) t_char* U16_ToString_Base(t_u16 number, t_char const* base);
__attribute__((malloc)) t_char* U32_ToString_Base(t_u32 number, t_char const* base);
__attribute__((malloc)) t_char* U64_ToString_Base(t_u64 number, t_char const* base);
__attribute__((malloc)) t_char* S8_ToString_Base(t_s8 number, t_char const* base);
__attribute__((malloc)) t_char* S16_ToString_Base(t_s16 number, t_char const* base);
__attribute__((malloc)) t_char* S32_ToString_Base(t_s32 number, t_char const* base);
__attribute__((malloc)) t_char* S64_ToString_Base(t_s64 number, t_char const* base);
t_u8 U8_FromString(t_char const* str);
t_u16 U16_FromString(t_char const* str);
t_u32 U32_FromString(t_char const* str);
t_u64 U64_FromString(t_char const* str);
t_s8 S8_FromString(t_char const* str);
t_s16 S16_FromString(t_char const* str);
t_s32 S32_FromString(t_char const* str);
t_s64 S64_FromString(t_char const* str);
t_u8 U8_FromString_Dec(t_char const* str);
t_u16 U16_FromString_Dec(t_char const* str);
t_u32 U32_FromString_Dec(t_char const* str);
t_u64 U64_FromString_Dec(t_char const* str);
t_s8 S8_FromString_Dec(t_char const* str);
t_s16 S16_FromString_Dec(t_char const* str);
t_s32 S32_FromString_Dec(t_char const* str);
t_s64 S64_FromString_Dec(t_char const* str);
t_u8 U8_FromString_Hex(t_char const* str);
t_u16 U16_FromString_Hex(t_char const* str);
t_u32 U32_FromString_Hex(t_char const* str);
t_u64 U64_FromString_Hex(t_char const* str);
t_s8 S8_FromString_Hex(t_char const* str);
t_s16 S16_FromString_Hex(t_char const* str);
t_s32 S32_FromString_Hex(t_char const* str);
t_s64 S64_FromString_Hex(t_char const* str);
t_u8 U8_FromString_Oct(t_char const* str);
t_u16 U16_FromString_Oct(t_char const* str);
t_u32 U32_FromString_Oct(t_char const* str);
t_u64 U64_FromString_Oct(t_char const* str);
t_s8 S8_FromString_Oct(t_char const* str);
t_s16 S16_FromString_Oct(t_char const* str);
t_s32 S32_FromString_Oct(t_char const* str);
t_s64 S64_FromString_Oct(t_char const* str);
t_u8 U8_FromString_Bin(t_char const* str);
t_u16 U16_FromString_Bin(t_char const* str);
t_u32 U32_FromString_Bin(t_char const* str);
t_u64 U64_FromString_Bin(t_char const* str);
t_s8 S8_FromString_Bin(t_char const* str);
t_s16 S16_FromString_Bin(t_char const* str);
t_s32 S32_FromString_Bin(t_char const* str);
t_s64 S64_FromString_Bin(t_char const* str);
t_u8 U8_FromString_Base(t_char const* str, t_char const* base);
t_u16 U16_FromString_Base(t_char const* str, t_char const* base);
t_u32 U32_FromString_Base(t_char const* str, t_char const* base);
t_u64 U64_FromString_Base(t_char const* str, t_char const* base);
t_s8 S8_FromString_Base(t_char const* str, t_char const* base);
t_s16 S16_FromString_Base(t_char const* str, t_char const* base);
t_s32 S32_FromString_Base(t_char const* str, t_char const* base);
t_s64 S64_FromString_Base(t_char const* str, t_char const* base);

typedef __builtin_va_list va_list;
typedef __builtin_va_list __gnuc_va_list;
__attribute__((format(printf, 1, 2)))
__attribute__((malloc))
t_char* String_Format(t_char const* format, ...);






__attribute__((malloc))
t_char* String_Format_VA(t_char const* format, va_list args);
__attribute__((format(printf, 3, 4)))
t_size String_Format_N(t_char* dest, t_size max, t_char const* format, ...);






t_size String_Format_N_VA(t_char* dest, t_size max, t_char const* format, va_list args);
__attribute__((malloc))
t_char* String_New(t_size n);
__attribute__((malloc))
t_char* String_New_C(t_size n, t_char c);
void String_Delete(t_char* *a_str);
__attribute__((malloc))
t_char* String_Duplicate(t_char const* str);
__attribute__((malloc))
t_char* String_Duplicate_N(t_char const* str, t_size n);
__attribute__((malloc))
t_char* String_Duplicate_Char(t_char const* str, t_char const c);
__attribute__((malloc))
t_char* String_Duplicate_Charset(t_char const* str, t_char const* charset);
__attribute__((malloc))
t_char* String_Duplicate_String(t_char const* str, t_char const* target);
void String_Clear(t_char* str);
void String_Set(t_char* str, t_char c);
t_char* String_Copy(t_char* dest, t_char const* src);
t_char* String_Copy_N(t_char* dest, t_char const* src, t_size n);
t_size String_Copy_L(t_char* dest, t_char const* src, t_size size);
t_char* String_Concat(t_char* dest, t_char const* src);
t_char* String_Concat_N(t_char* dest, t_char const* src, t_size n);
t_size String_Concat_L(t_char* dest, t_char const* src, t_size size);
t_size String_Length(t_char const* str);
t_bool String_Equals(t_char const* str1, t_char const* str2);
t_bool String_Equals_N(t_char const* str1, t_char const* str2, t_size n);
t_bool String_Equals_IgnoreCase(t_char const* str1, t_char const* str2);
t_bool String_Equals_N_IgnoreCase(t_char const* str1, t_char const* str2, t_size n);
t_sint String_Compare(t_char const* str1, t_char const* str2);
t_sint String_Compare_N(t_char const* str1, t_char const* str2, t_size n);
t_sint String_Compare_IgnoreCase(t_char const* str1, t_char const* str2);
t_sint String_Compare_N_IgnoreCase(t_char const* str1, t_char const* str2, t_size n);
t_bool String_Has(t_char const* str, t_char const* charset);
t_bool String_HasOnly(t_char const* str, t_char const* charset);
t_size String_Count_Char(t_char const* str, t_char c);
t_size String_Count_Charset(t_char const* str, t_char const* charset);
t_size String_Count_String(t_char const* str, t_char const* query);
t_char* String_Find_Char(t_char const* str, t_char c);
t_char* String_Find_Charset(t_char const* str, t_char const* charset);
t_char* String_Find_String(t_char const* str, t_char const* query);
t_char* String_Find_R_Char(t_char const* str, t_char c);
t_char* String_Find_R_Charset(t_char const* str, t_char const* charset);
t_char* String_Find_R_String(t_char const* str, t_char const* query);
t_char* String_Find_N_Char(t_char const* str, t_char c, t_size n);
t_char* String_Find_N_Charset(t_char const* str, t_char const* charset, t_size n);
t_char* String_Find_N_String(t_char const* str, t_char const* query, t_size n);
t_sintmax String_IndexOf_Char(t_char const* str, t_char c);
t_sintmax String_IndexOf_Charset(t_char const* str, t_char const* charset);
t_sintmax String_IndexOf_String(t_char const* str, t_char const* query);
t_sintmax String_IndexOf_R_Char(t_char const* str, t_char c);
t_sintmax String_IndexOf_R_Charset(t_char const* str, t_char const* charset);
t_sintmax String_IndexOf_R_String(t_char const* str, t_char const* query);
t_sintmax String_IndexOf_N_Char(t_char const* str, t_char c, t_size n);
t_sintmax String_IndexOf_N_Charset(t_char const* str, t_char const* charset, t_size n);
t_sintmax String_IndexOf_N_String(t_char const* str, t_char const* query, t_size n);
__attribute__((malloc))
t_char* String_Remove(t_char const* str, t_char const* query);
__attribute__((malloc))
t_char* String_Replace_Char(t_char const* str, t_char const char_old, t_char const char_new);
__attribute__((malloc))
t_char* String_Replace_Charset(t_char const* str, t_char const* charset_old, t_char const* charset_new);
__attribute__((malloc))
t_char* String_Replace_String(t_char const* str, t_char const* str_old, t_char const* str_new);
__attribute__((malloc))
t_char* String_Join(t_char const* str1, t_char const* str2);
__attribute__((malloc))
t_char* String_Merge(t_char* *a_str1, t_char* *a_str2);
__attribute__((malloc))
t_char* String_Append(t_char* *dest, t_char const* src);
__attribute__((malloc))
t_char* String_Prepend(t_char const* src, t_char* *dest);
t_char* String_Insert_InPlace(t_char* *dest, t_char const* src, t_u32 index);
void String_Replace_Char_InPlace(t_char* str, t_char const char_old, t_char const char_new);
void String_Replace_Charset_InPlace(t_char* str, t_char const* charset_old, t_char const* charset_new);
void String_Replace_String_InPlace(t_char* *a_str, t_char const* str_old, t_char const* str_new);
t_char* String_Map_InPlace(t_char* *a_str, t_char (*map)(t_char));
__attribute__((malloc))
t_char* String_Trim(t_char const* str, t_char const* charset);
__attribute__((malloc))
t_char* String_Trim_L(t_char const* str, t_char const* charset);
__attribute__((malloc))
t_char* String_Trim_R(t_char const* str, t_char const* charset);
__attribute__((malloc))
t_char* String_Pad(t_char const* str, t_char c, t_size length);
__attribute__((malloc))
t_char* String_Pad_L(t_char const* str, t_char c, t_size length);
__attribute__((malloc))
t_char* String_Pad_R(t_char const* str, t_char c, t_size length);
__attribute__((malloc))
t_char* String_Print(t_char const* str, t_char const* charset_extra);
__attribute__((malloc))
t_char* String_Parse(t_char const* str, t_bool any_escape);
__attribute__((malloc))
t_char* String_Reverse(t_char const* str);
__attribute__((malloc))
t_char* String_Insert(t_char const* dest, t_char const* src, t_size index);
__attribute__((malloc))
t_char* String_Sub(t_char const* str, t_size index, t_size n);
void String_Iterate(t_char* str, void (*f)(t_char* c));
void String_Iterate_I(t_char* str, void (*f)(t_char* c, t_size index));
__attribute__((malloc))
t_char* String_Map(t_char const* str, t_char (*map)(t_char c));
__attribute__((malloc))
t_char* String_Map_I(t_char const* str, t_char (*map)(t_char c, t_size index));
__attribute__((malloc))
t_char* String_Filter(t_char const* str, t_bool (*filter)(t_char c));
__attribute__((malloc))
t_char* String_Filter_I(t_char const* str, t_bool (*filter)(t_char c, t_size index));



typedef __darwin_mode_t mode_t;
typedef __darwin_off_t off_t;
typedef __darwin_pid_t pid_t;





struct flock {
 off_t l_start;
 off_t l_len;
 pid_t l_pid;
 short l_type;
 short l_whence;
};


struct timespec
{
 __darwin_time_t tv_sec;
 long tv_nsec;
};






struct flocktimeout {
 struct flock fl;
 struct timespec timeout;
};
struct radvisory {
 off_t ra_offset;
 int ra_count;
};



typedef struct fcodeblobs {
 void *f_cd_hash;
 size_t f_hash_size;
 void *f_cd_buffer;
 size_t f_cd_size;
 unsigned int *f_out_size;
 int f_arch;
 int __padding;
} fcodeblobs_t;
typedef struct fsignatures {
 off_t fs_file_start;
 void *fs_blob_start;
 size_t fs_blob_size;
} fsignatures_t;
typedef struct fchecklv {
 off_t lv_file_start;
 size_t lv_error_message_size;
 void *lv_error_message;
} fchecklv_t;
typedef struct fstore {
 unsigned int fst_flags;
 int fst_posmode;
 off_t fst_offset;
 off_t fst_length;
 off_t fst_bytesalloc;
} fstore_t;


typedef struct fpunchhole {
 unsigned int fp_flags;
 unsigned int reserved;
 off_t fp_offset;
 off_t fp_length;
} fpunchhole_t;


typedef struct ftrimactivefile {
 off_t fta_offset;
 off_t fta_length;
} ftrimactivefile_t;


typedef struct fspecread {
 unsigned int fsr_flags;
 unsigned int reserved;
 off_t fsr_offset;
 off_t fsr_length;
} fspecread_t;



typedef struct fbootstraptransfer {
 off_t fbt_offset;
 size_t fbt_length;
 void *fbt_buffer;
} fbootstraptransfer_t;

struct log2phys {
 unsigned int l2p_flags;
 off_t l2p_contigbytes;


 off_t l2p_devoffset;


};

struct _filesec;
typedef struct _filesec *filesec_t;

typedef enum {
 FILESEC_OWNER = 1,
 FILESEC_GROUP = 2,
 FILESEC_UUID = 3,
 FILESEC_MODE = 4,
 FILESEC_ACL = 5,
 FILESEC_GRPUUID = 6,


 FILESEC_ACL_RAW = 100,
 FILESEC_ACL_ALLOCSIZE = 101
} filesec_property_t;






int open(const char *, int, ...) __asm("_" "open" );

int openat(int, const char *, int, ...) __asm("_" "openat" ) __attribute__((availability(macosx,introduced=10.10)));

int creat(const char *, mode_t) __asm("_" "creat" );
int fcntl(int, int, ...) __asm("_" "fcntl" );


int openx_np(const char *, int, filesec_t);




int open_dprotected_np( const char *, int, int, int, ...);
int flock(int, int);
filesec_t filesec_init(void);
filesec_t filesec_dup(filesec_t);
void filesec_free(filesec_t);
int filesec_get_property(filesec_t, filesec_property_t, void *);
int filesec_query_property(filesec_t, filesec_property_t, int *);
int filesec_set_property(filesec_t, filesec_property_t, const void *);
int filesec_unset_property(filesec_t, filesec_property_t) __attribute__((availability(macosx,introduced=10.6)));
typedef int t_fd;
typedef unsigned int t_io_mode;
typedef unsigned int t_io_open;
t_u8 IO_GetColor(t_argb32 color);
t_bool IO_IsTerminal(t_fd fd);
t_fd IO_Open(t_char const* filepath, t_io_open flags, t_io_mode mode);
e_cccerror IO_Close(t_fd fd);
e_cccerror IO_ChangeMode(t_char const* filepath, t_io_mode mode);
t_sintmax IO_Read_File(t_fd const fd, t_char* *a_file, t_size max);
t_sintmax IO_Read_Lines(t_fd const fd, t_char** *a_strarr);
int IO_Read_NextLine(t_fd const fd, t_char* *a_line);
t_size IO_Write_Char(t_fd fd, t_char c);






t_size IO_Write_String(t_fd fd, t_char const* str);






t_size IO_Write_Line(t_fd fd, t_char const* str);






t_size IO_Write_Lines(t_fd fd, t_char const** strarr);






t_size IO_Write_Memory(t_fd fd, t_u8 const* ptr, t_size n, t_u8 cols);






__attribute__((format(printf, 2, 3)))
t_size IO_Write_Format(t_fd fd, t_char const* format, ...);
t_size IO_Output_Char(t_char c);







t_size IO_Output_String(t_char const* str);







t_size IO_Output_Line(t_char const* str);







t_size IO_Output_Lines(t_char const** strarr);







t_size IO_Output_Memory(t_u8 const* ptr, t_size n, t_u8 cols);







__attribute__((format(printf, 1, 2)))
t_size IO_Output_Format(t_char const* format, ...);
typedef void (*f_ccchandler)(e_cccerror, t_char const*);
t_char* Error_STDC(int errno_value);
e_cccerror Error_Get(void);


e_cccerror Error_Set(e_cccerror error);




t_char* Error_GetMessage(e_cccerror error);


t_char* Error_GetName(e_cccerror error);


e_cccerror Error_GetCode(t_char const* name);




void Error_Handle(e_cccerror error, t_char const* funcname, t_char* message);


void Error_Handler(e_cccerror error, t_char const* message);




f_ccchandler Error_GetHandler(e_cccerror error);


void Error_SetHandler(e_cccerror error, f_ccchandler handler);


void Error_SetAllHandlers(f_ccchandler handler);



t_bool Bool_FromString(t_char const* str)
{
 t_size i;

 if ((str == ((void*)0))) { Error_Set(ERROR_NULLPOINTER); if (1) { Error_Handle(ERROR_NULLPOINTER, __func__, ((void*)0)); } return ((0)); }
 i = 0;
 while (str[i] && ASCII_IsWhiteSpace(str[i]))
 {
  ++i;
 }
 if (!str[i])
  return ((0));
 if (ASCII_IsDigit_Decimal(str[i]) && S64_FromString(str + i))
  return ((1));
 if ((str[i + 0] == 'T' || str[i + 0] == 't') &&
  (str[i + 1] == 'R' || str[i + 1] == 'r') &&
  (str[i + 2] == 'U' || str[i + 2] == 'u') &&
  (str[i + 3] == 'E' || str[i + 3] == 'e'))
  return ((1));
 return ((0));
}
