# 1 "./test/_foreach.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "./test/_foreach.c"


# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 1 3 4
# 9 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/corecrt_stdio_config.h" 1 3 4
# 10 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/corecrt_stdio_config.h" 3 4
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
extern __inline__ __attribute__((__always_inline__,__gnu_inline__)) void __attribute__((__cdecl__)) __debugbreak(void)
{
  __asm__ __volatile__("int {$}3":);
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
# 11 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/corecrt_stdio_config.h" 2 3 4
# 10 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 2 3 4

#pragma pack(push,_CRT_PACKING)
# 24 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
  struct _iobuf {
    char *_ptr;
    int _cnt;
    char *_base;
    int _flag;
    int _file;
    int _charbuf;
    int _bufsiz;
    char *_tmpfname;
  };
  typedef struct _iobuf FILE;
# 78 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/_mingw_off_t.h" 1 3 4




  typedef long _off_t;

  typedef long off32_t;





  __extension__ typedef long long _off64_t;

  __extension__ typedef long long off64_t;
# 26 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/_mingw_off_t.h" 3 4
typedef off32_t off_t;
# 79 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 2 3 4

__attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) __acrt_iob_func(unsigned index);


  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) __iob_func(void);
# 102 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
  __extension__ typedef long long fpos_t;
# 142 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
extern
  __attribute__((__format__ (gnu_scanf, 2, 3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_sscanf(const char * __restrict__ _Src,const char * __restrict__ _Format,...);
extern
  __attribute__((__format__ (gnu_scanf, 2, 0))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_vsscanf (const char * __restrict__ _Str,const char * __restrict__ Format,va_list argp);
extern
  __attribute__((__format__ (gnu_scanf, 1, 2))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __mingw_scanf(const char * __restrict__ _Format,...);
extern
  __attribute__((__format__ (gnu_scanf, 1, 0))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __mingw_vscanf(const char * __restrict__ Format, va_list argp);
extern
  __attribute__((__format__ (gnu_scanf, 2, 3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_fscanf(FILE * __restrict__ _File,const char * __restrict__ _Format,...);
extern
  __attribute__((__format__ (gnu_scanf, 2, 0))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_vfscanf (FILE * __restrict__ fp, const char * __restrict__ Format,va_list argp);

extern
  __attribute__((__format__ (gnu_printf, 3, 0))) __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __mingw_vsnprintf(char * __restrict__ _DstBuf,size_t _MaxCount,const char * __restrict__ _Format,
                               va_list _ArgList);
extern
  __attribute__((__format__ (gnu_printf, 3, 4))) __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __mingw_snprintf(char * __restrict__ s, size_t n, const char * __restrict__ format, ...);
extern
  __attribute__((__format__ (gnu_printf, 1, 2))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __mingw_printf(const char * __restrict__ , ... ) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__ (gnu_printf, 1, 0))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __mingw_vprintf (const char * __restrict__ , va_list) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__ (gnu_printf, 2, 3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_fprintf (FILE * __restrict__ , const char * __restrict__ , ...) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__ (gnu_printf, 2, 0))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_vfprintf (FILE * __restrict__ , const char * __restrict__ , va_list) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__ (gnu_printf, 2, 3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_sprintf (char * __restrict__ , const char * __restrict__ , ...) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__ (gnu_printf, 2, 0))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_vsprintf (char * __restrict__ , const char * __restrict__ , va_list) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__ (gnu_printf, 2, 3))) __attribute__((nonnull (1,2)))
  int __attribute__((__cdecl__)) __mingw_asprintf(char ** __restrict__ , const char * __restrict__ , ...) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__ (gnu_printf, 2, 0))) __attribute__((nonnull (1,2)))
  int __attribute__((__cdecl__)) __mingw_vasprintf(char ** __restrict__ , const char * __restrict__ , va_list) __attribute__ ((__nothrow__));

extern
  __attribute__((__format__ (ms_scanf, 2, 3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_sscanf(const char * __restrict__ _Src,const char * __restrict__ _Format,...);
extern
  __attribute__((__format__ (ms_scanf, 1, 2))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __ms_scanf(const char * __restrict__ _Format,...);
extern
  __attribute__((__format__ (ms_scanf, 2, 3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_fscanf(FILE * __restrict__ _File,const char * __restrict__ _Format,...);

extern
  __attribute__((__format__ (ms_printf, 1, 2))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __ms_printf(const char * __restrict__ , ... ) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__ (ms_printf, 1, 0))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __ms_vprintf (const char * __restrict__ , va_list) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__ (ms_printf, 2, 3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_fprintf (FILE * __restrict__ , const char * __restrict__ , ...) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__ (ms_printf, 2, 0))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_vfprintf (FILE * __restrict__ , const char * __restrict__ , va_list) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__ (ms_printf, 2, 3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_sprintf (char * __restrict__ , const char * __restrict__ , ...) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__ (ms_printf, 2, 0))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_vsprintf (char * __restrict__ , const char * __restrict__ , va_list) __attribute__ ((__nothrow__));
# 274 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
__attribute__((__format__ (gnu_scanf, 2, 3))) __attribute__ ((__nonnull__ (2)))
int sscanf(const char *__source, const char *__format, ...)
{
  int __retval;
  __builtin_va_list __local_argv; __builtin_va_start( __local_argv, __format );
  __retval = __mingw_vsscanf( __source, __format, __local_argv );
  __builtin_va_end( __local_argv );
  return __retval;
}

static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
__attribute__((__format__ (gnu_scanf, 1, 2))) __attribute__ ((__nonnull__ (1)))
int scanf(const char *__format, ...)
{
  int __retval;
  __builtin_va_list __local_argv; __builtin_va_start( __local_argv, __format );
  __retval = __mingw_vfscanf( (__acrt_iob_func(0)), __format, __local_argv );
  __builtin_va_end( __local_argv );
  return __retval;
}

static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
__attribute__((__format__ (gnu_scanf, 2, 3))) __attribute__ ((__nonnull__ (2)))
int fscanf(FILE *__stream, const char *__format, ...)
{
  int __retval;
  __builtin_va_list __local_argv; __builtin_va_start( __local_argv, __format );
  __retval = __mingw_vfscanf( __stream, __format, __local_argv );
  __builtin_va_end( __local_argv );
  return __retval;
}



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"


static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
__attribute__((__format__ (gnu_scanf, 2, 0))) __attribute__ ((__nonnull__ (2)))
int vsscanf (const char *__source, const char *__format, __builtin_va_list __local_argv)
{
  return __mingw_vsscanf( __source, __format, __local_argv );
}

static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
__attribute__((__format__ (gnu_scanf, 1, 0))) __attribute__ ((__nonnull__ (1)))
int vscanf(const char *__format, __builtin_va_list __local_argv)
{
  return __mingw_vfscanf( (__acrt_iob_func(0)), __format, __local_argv );
}

static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
__attribute__((__format__ (gnu_scanf, 2, 0))) __attribute__ ((__nonnull__ (2)))
int vfscanf (FILE *__stream, const char *__format, __builtin_va_list __local_argv)
{
  return __mingw_vfscanf( __stream, __format, __local_argv );
}


#pragma GCC diagnostic pop





static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
__attribute__((__format__ (gnu_printf, 2, 3))) __attribute__ ((__nonnull__ (2)))
int fprintf (FILE *__stream, const char *__format, ...)
{
  int __retval;
  __builtin_va_list __local_argv; __builtin_va_start( __local_argv, __format );
  __retval = __mingw_vfprintf( __stream, __format, __local_argv );
  __builtin_va_end( __local_argv );
  return __retval;
}

static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
__attribute__((__format__ (gnu_printf, 1, 2))) __attribute__ ((__nonnull__ (1)))
int printf (const char *__format, ...)
{
  int __retval;
  __builtin_va_list __local_argv; __builtin_va_start( __local_argv, __format );
  __retval = __mingw_vfprintf( (__acrt_iob_func(1)), __format, __local_argv );
  __builtin_va_end( __local_argv );
  return __retval;
}
# 380 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
__attribute__((__format__ (gnu_printf, 2, 3))) __attribute__ ((__nonnull__ (2)))
int sprintf (char *__stream, const char *__format, ...)
{
  int __retval;
  __builtin_va_list __local_argv; __builtin_va_start( __local_argv, __format );
  __retval = __mingw_vsprintf( __stream, __format, __local_argv );
  __builtin_va_end( __local_argv );
  return __retval;
}



static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
__attribute__((__format__ (gnu_printf, 2, 0))) __attribute__ ((__nonnull__ (2)))
int vfprintf (FILE *__stream, const char *__format, __builtin_va_list __local_argv)
{
  return __mingw_vfprintf( __stream, __format, __local_argv );
}

static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
__attribute__((__format__ (gnu_printf, 1, 0))) __attribute__ ((__nonnull__ (1)))
int vprintf (const char *__format, __builtin_va_list __local_argv)
{
  return __mingw_vfprintf( (__acrt_iob_func(1)), __format, __local_argv );
}

static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
__attribute__((__format__ (gnu_printf, 2, 0))) __attribute__ ((__nonnull__ (2)))
int vsprintf (char *__stream, const char *__format, __builtin_va_list __local_argv)
{
# 419 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
  return __mingw_vsprintf( __stream, __format, __local_argv );
}
# 435 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
__attribute__((__format__ (gnu_printf, 3, 4))) __attribute__ ((__nonnull__ (3)))
int snprintf (char *__stream, size_t __n, const char *__format, ...)
{
  int __retval;
  __builtin_va_list __local_argv; __builtin_va_start( __local_argv, __format );
  __retval = __mingw_vsnprintf( __stream, __n, __format, __local_argv );
  __builtin_va_end( __local_argv );
  return __retval;
}



static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
__attribute__((__format__ (gnu_printf, 3, 0))) __attribute__ ((__nonnull__ (3)))
int vsnprintf (char *__stream, size_t __n, const char *__format, __builtin_va_list __local_argv)
{



  return __mingw_vsnprintf( __stream, __n, __format, __local_argv );
}
# 625 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _filbuf(FILE *_File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _flsbuf(int _Ch,FILE *_File);



  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) _fsopen(const char *_Filename,const char *_Mode,int _ShFlag);

  void __attribute__((__cdecl__)) clearerr(FILE *_File);
  int __attribute__((__cdecl__)) fclose(FILE *_File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fcloseall(void);



  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) _fdopen(int _FileHandle,const char *_Mode);

  int __attribute__((__cdecl__)) feof(FILE *_File);
  int __attribute__((__cdecl__)) ferror(FILE *_File);
  int __attribute__((__cdecl__)) fflush(FILE *_File);
  int __attribute__((__cdecl__)) fgetc(FILE *_File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fgetchar(void);
  int __attribute__((__cdecl__)) fgetpos(FILE * __restrict__ _File ,fpos_t * __restrict__ _Pos);
  int __attribute__((__cdecl__)) fgetpos64(FILE * __restrict__ _File ,fpos_t * __restrict__ _Pos);
  char *__attribute__((__cdecl__)) fgets(char * __restrict__ _Buf,int _MaxCount,FILE * __restrict__ _File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fileno(FILE *_File);



  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _tempnam(const char *_DirName,const char *_FilePrefix);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _flushall(void);
  FILE *__attribute__((__cdecl__)) fopen(const char * __restrict__ _Filename,const char * __restrict__ _Mode) ;
  FILE *fopen64(const char * __restrict__ filename,const char * __restrict__ mode);
  int __attribute__((__cdecl__)) fputc(int _Ch,FILE *_File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fputchar(int _Ch);
  int __attribute__((__cdecl__)) fputs(const char * __restrict__ _Str,FILE * __restrict__ _File);
  size_t __attribute__((__cdecl__)) fread(void * __restrict__ _DstBuf,size_t _ElementSize,size_t _Count,FILE * __restrict__ _File);
  FILE *__attribute__((__cdecl__)) freopen(const char * __restrict__ _Filename,const char * __restrict__ _Mode,FILE * __restrict__ _File) ;
  int __attribute__((__cdecl__)) fsetpos(FILE *_File,const fpos_t *_Pos);
  int __attribute__((__cdecl__)) fsetpos64(FILE *_File,const fpos_t *_Pos);
  int __attribute__((__cdecl__)) fseek(FILE *_File,long _Offset,int _Origin);
  long __attribute__((__cdecl__)) ftell(FILE *_File);



  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fseeki64(FILE *_File,long long _Offset,int _Origin);
  __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _ftelli64(FILE *_File);
# 684 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
  int fseeko64(FILE* stream, _off64_t offset, int whence);
  int fseeko(FILE* stream, _off_t offset, int whence);

  _off_t ftello(FILE * stream);
  _off64_t ftello64(FILE * stream);
# 705 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
  size_t __attribute__((__cdecl__)) fwrite(const void * __restrict__ _Str,size_t _Size,size_t _Count,FILE * __restrict__ _File);
  int __attribute__((__cdecl__)) getc(FILE *_File);
  int __attribute__((__cdecl__)) getchar(void);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _getmaxstdio(void);
  char *__attribute__((__cdecl__)) gets(char *_Buffer) ;
  int __attribute__((__cdecl__)) _getw(FILE *_File);


  void __attribute__((__cdecl__)) perror(const char *_ErrMsg);


  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _pclose(FILE *_File);
  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) _popen(const char *_Command,const char *_Mode);





  int __attribute__((__cdecl__)) putc(int _Ch,FILE *_File);
  int __attribute__((__cdecl__)) putchar(int _Ch);
  int __attribute__((__cdecl__)) puts(const char *_Str);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _putw(int _Word,FILE *_File);


  int __attribute__((__cdecl__)) remove(const char *_Filename);
  int __attribute__((__cdecl__)) rename(const char *_OldFilename,const char *_NewFilename);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _unlink(const char *_Filename);

  int __attribute__((__cdecl__)) unlink(const char *_Filename) ;


  void __attribute__((__cdecl__)) rewind(FILE *_File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _rmtmp(void);
  void __attribute__((__cdecl__)) setbuf(FILE * __restrict__ _File,char * __restrict__ _Buffer) ;
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _setmaxstdio(int _Max);
  __attribute__ ((__dllimport__)) unsigned int __attribute__((__cdecl__)) _set_output_format(unsigned int _Format);
  __attribute__ ((__dllimport__)) unsigned int __attribute__((__cdecl__)) _get_output_format(void);
  int __attribute__((__cdecl__)) setvbuf(FILE * __restrict__ _File,char * __restrict__ _Buf,int _Mode,size_t _Size);
# 765 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _scprintf(const char * __restrict__ _Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snscanf(const char * __restrict__ _Src,size_t _MaxCount,const char * __restrict__ _Format,...) ;

  FILE *__attribute__((__cdecl__)) tmpfile(void) ;
  char *__attribute__((__cdecl__)) tmpnam(char *_Buffer);
  int __attribute__((__cdecl__)) ungetc(int _Ch,FILE *_File);
# 787 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
  __attribute__((__format__ (ms_printf, 3, 4))) __attribute__ ((__nonnull__ (3)))
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snprintf(char * __restrict__ _Dest,size_t _Count,const char * __restrict__ _Format,...) ;
  __attribute__((__format__ (ms_printf, 3, 0))) __attribute__ ((__nonnull__ (3)))
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsnprintf(char * __restrict__ _Dest,size_t _Count,const char * __restrict__ _Format,va_list _Args) ;
# 952 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vscprintf(const char * __restrict__ _Format,va_list _ArgList);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _set_printf_count_output(int _Value);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _get_printf_count_output(void);




                                                     __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_swscanf(const wchar_t * __restrict__ _Src,const wchar_t * __restrict__ _Format,...);
                                                     __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_vswscanf (const wchar_t * __restrict__ _Str,const wchar_t * __restrict__ Format,va_list argp);
                                                     __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __mingw_wscanf(const wchar_t * __restrict__ _Format,...);
                                                     __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __mingw_vwscanf(const wchar_t * __restrict__ Format, va_list argp);
                                                     __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_fwscanf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,...);
                                                     __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_vfwscanf (FILE * __restrict__ fp, const wchar_t * __restrict__ Format,va_list argp);

                                                      __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_fwprintf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,...);
                                                      __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __mingw_wprintf(const wchar_t * __restrict__ _Format,...);
                                                     __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_vfwprintf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,va_list _ArgList);
                                                     __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __mingw_vwprintf(const wchar_t * __restrict__ _Format,va_list _ArgList);
                                                      __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __mingw_snwprintf (wchar_t * __restrict__ s, size_t n, const wchar_t * __restrict__ format, ...);
                                                      __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __mingw_vsnwprintf (wchar_t * __restrict__ , size_t, const wchar_t * __restrict__ , va_list);
                                                      __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_swprintf(wchar_t * __restrict__ , const wchar_t * __restrict__ , ...);
                                                      __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_vswprintf(wchar_t * __restrict__ , const wchar_t * __restrict__ ,va_list);

                                                    __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_swscanf(const wchar_t * __restrict__ _Src,const wchar_t * __restrict__ _Format,...);
                                                    __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __ms_wscanf(const wchar_t * __restrict__ _Format,...);
                                                    __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_fwscanf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,...);

                                                     __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_fwprintf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,...);
                                                     __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __ms_wprintf(const wchar_t * __restrict__ _Format,...);
                                                    __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_vfwprintf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,va_list _ArgList);
                                                    __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __ms_vwprintf(const wchar_t * __restrict__ _Format,va_list _ArgList);
                                                     __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_swprintf(wchar_t * __restrict__ , const wchar_t * __restrict__ , ...);
                                                     __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_vswprintf(wchar_t * __restrict__ , const wchar_t * __restrict__ ,va_list);
# 1022 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
                                                     __attribute__ ((__nonnull__ (2)))
int swscanf(const wchar_t *__source, const wchar_t *__format, ...)
{
  int __retval;
  __builtin_va_list __local_argv; __builtin_va_start( __local_argv, __format );
  __retval = __mingw_vswscanf( __source, __format, __local_argv );
  __builtin_va_end( __local_argv );
  return __retval;
}

static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
                                                     __attribute__ ((__nonnull__ (1)))
int wscanf(const wchar_t *__format, ...)
{
  int __retval;
  __builtin_va_list __local_argv; __builtin_va_start( __local_argv, __format );
  __retval = __mingw_vfwscanf( (__acrt_iob_func(0)), __format, __local_argv );
  __builtin_va_end( __local_argv );
  return __retval;
}

static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
                                                     __attribute__ ((__nonnull__ (2)))
int fwscanf(FILE *__stream, const wchar_t *__format, ...)
{
  int __retval;
  __builtin_va_list __local_argv; __builtin_va_start( __local_argv, __format );
  __retval = __mingw_vfwscanf( __stream, __format, __local_argv );
  __builtin_va_end( __local_argv );
  return __retval;
}


static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
                                                     __attribute__ ((__nonnull__ (2)))
int vswscanf (const wchar_t * __restrict__ __source, const wchar_t * __restrict__ __format, __builtin_va_list __local_argv)
{
  return __mingw_vswscanf( __source, __format, __local_argv );
}

static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
                                                     __attribute__ ((__nonnull__ (1)))
int vwscanf(const wchar_t *__format, __builtin_va_list __local_argv)
{
  return __mingw_vfwscanf( (__acrt_iob_func(0)), __format, __local_argv );
}

static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
                                                     __attribute__ ((__nonnull__ (2)))
int vfwscanf (FILE *__stream, const wchar_t *__format, __builtin_va_list __local_argv)
{
  return __mingw_vfwscanf( __stream, __format, __local_argv );
}




static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
                                                      __attribute__ ((__nonnull__ (2)))
int fwprintf (FILE *__stream, const wchar_t *__format, ...)
{
  int __retval;
  __builtin_va_list __local_argv; __builtin_va_start( __local_argv, __format );
  __retval = __mingw_vfwprintf( __stream, __format, __local_argv );
  __builtin_va_end( __local_argv );
  return __retval;
}

static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
                                                      __attribute__ ((__nonnull__ (1)))
int wprintf (const wchar_t *__format, ...)
{
  int __retval;
  __builtin_va_list __local_argv; __builtin_va_start( __local_argv, __format );
  __retval = __mingw_vfwprintf( (__acrt_iob_func(1)), __format, __local_argv );
  __builtin_va_end( __local_argv );
  return __retval;
}

static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
                                                      __attribute__ ((__nonnull__ (2)))
int vfwprintf (FILE *__stream, const wchar_t *__format, __builtin_va_list __local_argv)
{
  return __mingw_vfwprintf( __stream, __format, __local_argv );
}

static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
                                                      __attribute__ ((__nonnull__ (1)))
int vwprintf (const wchar_t *__format, __builtin_va_list __local_argv)
{
  return __mingw_vfwprintf( (__acrt_iob_func(1)), __format, __local_argv );
}
# 1130 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
                                                      __attribute__ ((__nonnull__ (3)))
int snwprintf (wchar_t *__stream, size_t __n, const wchar_t *__format, ...)
{
  int __retval;
  __builtin_va_list __local_argv; __builtin_va_start( __local_argv, __format );
  __retval = __mingw_vsnwprintf( __stream, __n, __format, __local_argv );
  __builtin_va_end( __local_argv );
  return __retval;
}



static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
                                                      __attribute__ ((__nonnull__ (3)))
int vsnwprintf (wchar_t *__stream, size_t __n, const wchar_t *__format, __builtin_va_list __local_argv)
{



  return __mingw_vsnwprintf( __stream, __n, __format, __local_argv );
}
# 1283 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) _wfsopen(const wchar_t *_Filename,const wchar_t *_Mode,int _ShFlag);


  wint_t __attribute__((__cdecl__)) fgetwc(FILE *_File);
  __attribute__ ((__dllimport__)) wint_t __attribute__((__cdecl__)) _fgetwchar(void);
  wint_t __attribute__((__cdecl__)) fputwc(wchar_t _Ch,FILE *_File);
  __attribute__ ((__dllimport__)) wint_t __attribute__((__cdecl__)) _fputwchar(wchar_t _Ch);
  wint_t __attribute__((__cdecl__)) getwc(FILE *_File);
  wint_t __attribute__((__cdecl__)) getwchar(void);
  wint_t __attribute__((__cdecl__)) putwc(wchar_t _Ch,FILE *_File);
  wint_t __attribute__((__cdecl__)) putwchar(wchar_t _Ch);
  wint_t __attribute__((__cdecl__)) ungetwc(wint_t _Ch,FILE *_File);
  wchar_t *__attribute__((__cdecl__)) fgetws(wchar_t * __restrict__ _Dst,int _SizeInWords,FILE * __restrict__ _File);
  int __attribute__((__cdecl__)) fputws(const wchar_t * __restrict__ _Str,FILE * __restrict__ _File);
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _getws(wchar_t *_String) ;
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _putws(const wchar_t *_Str);
# 1365 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _scwprintf(const wchar_t * __restrict__ _Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _swprintf_c(wchar_t * __restrict__ _DstBuf,size_t _SizeInWords,const wchar_t * __restrict__ _Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vswprintf_c(wchar_t * __restrict__ _DstBuf,size_t _SizeInWords,const wchar_t * __restrict__ _Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snwprintf(wchar_t * __restrict__ _Dest,size_t _Count,const wchar_t * __restrict__ _Format,...) ;
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsnwprintf(wchar_t * __restrict__ _Dest,size_t _Count,const wchar_t * __restrict__ _Format,va_list _Args) ;
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vscwprintf(const wchar_t * __restrict__ _Format,va_list _ArgList);
# 1401 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _swprintf(wchar_t * __restrict__ _Dest,const wchar_t * __restrict__ _Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vswprintf(wchar_t * __restrict__ _Dest,const wchar_t * __restrict__ _Format,va_list _Args);



# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/swprintf.inl" 1 3 4
# 25 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/swprintf.inl" 3 4
static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
                                                      __attribute__ ((__nonnull__ (3)))
int vswprintf (wchar_t *__stream, size_t __count, const wchar_t *__format, __builtin_va_list __local_argv)
{
  return vsnwprintf( __stream, __count, __format, __local_argv );
}

static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__))
                                                      __attribute__ ((__nonnull__ (3)))
int swprintf (wchar_t *__stream, size_t __count, const wchar_t *__format, ...)
{
  int __retval;
  __builtin_va_list __local_argv;

  __builtin_va_start( __local_argv, __format );
  __retval = vswprintf( __stream, __count, __format, __local_argv );
  __builtin_va_end( __local_argv );
  return __retval;
}
# 1407 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 2 3 4
# 1416 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wtempnam(const wchar_t *_Directory,const wchar_t *_FilePrefix);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snwscanf(const wchar_t * __restrict__ _Src,size_t _MaxCount,const wchar_t * __restrict__ _Format,...);
  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) _wfdopen(int _FileHandle ,const wchar_t *_Mode);
  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) _wfopen(const wchar_t * __restrict__ _Filename,const wchar_t *__restrict__ _Mode) ;
  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) _wfreopen(const wchar_t * __restrict__ _Filename,const wchar_t * __restrict__ _Mode,FILE * __restrict__ _OldFile) ;



  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _wperror(const wchar_t *_ErrMsg);

  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) _wpopen(const wchar_t *_Command,const wchar_t *_Mode);




  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wremove(const wchar_t *_Filename);
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wtmpnam(wchar_t *_Buffer);
  __attribute__ ((__dllimport__)) wint_t __attribute__((__cdecl__)) _fgetwc_nolock(FILE *_File);
  __attribute__ ((__dllimport__)) wint_t __attribute__((__cdecl__)) _fputwc_nolock(wchar_t _Ch,FILE *_File);
  __attribute__ ((__dllimport__)) wint_t __attribute__((__cdecl__)) _ungetwc_nolock(wint_t _Ch,FILE *_File);
# 1472 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _lock_file(FILE *_File);
  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _unlock_file(FILE *_File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fclose_nolock(FILE *_File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fflush_nolock(FILE *_File);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _fread_nolock(void * __restrict__ _DstBuf,size_t _ElementSize,size_t _Count,FILE * __restrict__ _File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fseek_nolock(FILE *_File,long _Offset,int _Origin);
  __attribute__ ((__dllimport__)) long __attribute__((__cdecl__)) _ftell_nolock(FILE *_File);
  __extension__ __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fseeki64_nolock(FILE *_File,long long _Offset,int _Origin);
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _ftelli64_nolock(FILE *_File);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _fwrite_nolock(const void * __restrict__ _DstBuf,size_t _Size,size_t _Count,FILE * __restrict__ _File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _ungetc_nolock(int _Ch,FILE *_File);





  char *__attribute__((__cdecl__)) tempnam(const char *_Directory,const char *_FilePrefix) ;
  int __attribute__((__cdecl__)) fcloseall(void) ;
  FILE *__attribute__((__cdecl__)) fdopen(int _FileHandle,const char *_Format) ;
  int __attribute__((__cdecl__)) fgetchar(void) ;
  int __attribute__((__cdecl__)) fileno(FILE *_File) ;
  int __attribute__((__cdecl__)) flushall(void) ;
  int __attribute__((__cdecl__)) fputchar(int _Ch) ;
  int __attribute__((__cdecl__)) getw(FILE *_File) ;
  int __attribute__((__cdecl__)) putw(int _Ch,FILE *_File) ;
  int __attribute__((__cdecl__)) rmtmp(void) ;
# 1514 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
int __attribute__((__cdecl__)) __mingw_str_wide_utf8 (const wchar_t * const wptr, char **mbptr, size_t * buflen);
# 1528 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
int __attribute__((__cdecl__)) __mingw_str_utf8_wide (const char *const mbptr, wchar_t ** wptr, size_t * buflen);
# 1537 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
void __attribute__((__cdecl__)) __mingw_str_free(void *ptr);






  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnl(int _Mode,const wchar_t *_Filename,const wchar_t *_ArgList,...);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnle(int _Mode,const wchar_t *_Filename,const wchar_t *_ArgList,...);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnlp(int _Mode,const wchar_t *_Filename,const wchar_t *_ArgList,...);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnlpe(int _Mode,const wchar_t *_Filename,const wchar_t *_ArgList,...);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnv(int _Mode,const wchar_t *_Filename,const wchar_t *const *_ArgList);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnve(int _Mode,const wchar_t *_Filename,const wchar_t *const *_ArgList,const wchar_t *const *_Env);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnvp(int _Mode,const wchar_t *_Filename,const wchar_t *const *_ArgList);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnvpe(int _Mode,const wchar_t *_Filename,const wchar_t *const *_ArgList,const wchar_t *const *_Env);
# 1568 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 3 4
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _spawnv(int _Mode,const char *_Filename,const char *const *_ArgList);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _spawnve(int _Mode,const char *_Filename,const char *const *_ArgList,const char *const *_Env);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _spawnvp(int _Mode,const char *_Filename,const char *const *_ArgList);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _spawnvpe(int _Mode,const char *_Filename,const char *const *_ArgList,const char *const *_Env);







#pragma pack(pop)

# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/sec_api/stdio_s.h" 1 3 4
# 9 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/sec_api/stdio_s.h" 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 1 3 4
# 10 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/sec_api/stdio_s.h" 2 3 4
# 29 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/sec_api/stdio_s.h" 3 4
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) clearerr_s(FILE *_File);

  size_t __attribute__((__cdecl__)) fread_s(void *_DstBuf,size_t _DstSize,size_t _ElementSize,size_t _Count,FILE *_File);
# 494 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/sec_api/stdio_s.h" 3 4
  int __attribute__((__cdecl__)) fprintf_s(FILE *_File,const char *_Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fscanf_s_l(FILE *_File,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) fscanf_s(FILE *_File, const char *_Format, ...);
  int __attribute__((__cdecl__)) printf_s(const char *_Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _scanf_l(const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _scanf_s_l(const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) scanf_s(const char *_Format, ...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snprintf_c(char *_DstBuf,size_t _MaxCount,const char *_Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsnprintf_c(char *_DstBuf,size_t _MaxCount,const char *_Format,va_list _ArgList);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fscanf_l(FILE *_File,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _sscanf_l(const char *_Src,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _sscanf_s_l(const char *_Src,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) sscanf_s(const char *_Src,const char *_Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snscanf_s(const char *_Src,size_t _MaxCount,const char *_Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snscanf_l(const char *_Src,size_t _MaxCount,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snscanf_s_l(const char *_Src,size_t _MaxCount,const char *_Format,_locale_t _Locale,...);
  int __attribute__((__cdecl__)) vfprintf_s(FILE *_File,const char *_Format,va_list _ArgList);
  int __attribute__((__cdecl__)) vprintf_s(const char *_Format,va_list _ArgList);

  int __attribute__((__cdecl__)) vsnprintf_s(char *_DstBuf,size_t _DstSize,size_t _MaxCount,const char *_Format,va_list _ArgList);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsnprintf_s(char *_DstBuf,size_t _DstSize,size_t _MaxCount,const char *_Format,va_list _ArgList);

  __attribute__((dllimport)) int __attribute__((__cdecl__)) vsprintf_s(char *_DstBuf,size_t _Size,const char *_Format,va_list _ArgList);

  __attribute__((dllimport)) int __attribute__((__cdecl__)) sprintf_s(char *_DstBuf,size_t _DstSize,const char *_Format,...);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snprintf_s(char *_DstBuf,size_t _DstSize,size_t _MaxCount,const char *_Format,...);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fprintf_p(FILE *_File,const char *_Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _printf_p(const char *_Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _sprintf_p(char *_Dst,size_t _MaxCount,const char *_Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vfprintf_p(FILE *_File,const char *_Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vprintf_p(const char *_Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsprintf_p(char *_Dst,size_t _MaxCount,const char *_Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _scprintf_p(const char *_Format,...);
  __attribute__((dllimport)) int __attribute__((__cdecl__)) _vscprintf_p(const char *_Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _printf_l(const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _printf_p_l(const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vprintf_l(const char *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vprintf_p_l(const char *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fprintf_l(FILE *_File,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fprintf_p_l(FILE *_File,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vfprintf_l(FILE *_File,const char *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vfprintf_p_l(FILE *_File,const char *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _sprintf_l(char *_DstBuf,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _sprintf_p_l(char *_DstBuf,size_t _MaxCount,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsprintf_l(char *_DstBuf,const char *_Format,_locale_t,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsprintf_p_l(char *_DstBuf,size_t _MaxCount,const char *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _scprintf_l(const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _scprintf_p_l(const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vscprintf_l(const char *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vscprintf_p_l(const char *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _printf_s_l(const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vprintf_s_l(const char *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fprintf_s_l(FILE *_File,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vfprintf_s_l(FILE *_File,const char *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _sprintf_s_l(char *_DstBuf,size_t _DstSize,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsprintf_s_l(char *_DstBuf,size_t _DstSize,const char *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snprintf_s_l(char *_DstBuf,size_t _DstSize,size_t _MaxCount,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsnprintf_s_l(char *_DstBuf,size_t _DstSize,size_t _MaxCount,const char *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snprintf_l(char *_DstBuf,size_t _MaxCount,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snprintf_c_l(char *_DstBuf,size_t _MaxCount,const char *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsnprintf_l(char *_DstBuf,size_t _MaxCount,const char *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsnprintf_c_l(char *_DstBuf,size_t _MaxCount,const char *,_locale_t _Locale,va_list _ArgList);


 
 
 
 
 

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) fopen_s(FILE **_File,const char *_Filename,const char *_Mode);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) freopen_s(FILE** _File, const char *_Filename, const char *_Mode, FILE *_Stream);

  __attribute__ ((__dllimport__)) char* __attribute__((__cdecl__)) gets_s(char*,rsize_t);
 

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) tmpnam_s(char*,rsize_t);
 




  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _getws_s(wchar_t *_Str,size_t _SizeInWords);
 
# 786 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/sec_api/stdio_s.h" 3 4
  int __attribute__((__cdecl__)) fwprintf_s(FILE *_File,const wchar_t *_Format,...);
  int __attribute__((__cdecl__)) wprintf_s(const wchar_t *_Format,...);
  int __attribute__((__cdecl__)) vfwprintf_s(FILE *_File,const wchar_t *_Format,va_list _ArgList);
  int __attribute__((__cdecl__)) vwprintf_s(const wchar_t *_Format,va_list _ArgList);

  int __attribute__((__cdecl__)) vswprintf_s(wchar_t *_Dst,size_t _SizeInWords,const wchar_t *_Format,va_list _ArgList);

  int __attribute__((__cdecl__)) swprintf_s(wchar_t *_Dst,size_t _SizeInWords,const wchar_t *_Format,...);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsnwprintf_s(wchar_t *_DstBuf,size_t _DstSizeInWords,size_t _MaxCount,const wchar_t *_Format,va_list _ArgList);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snwprintf_s(wchar_t *_DstBuf,size_t _DstSizeInWords,size_t _MaxCount,const wchar_t *_Format,...);


  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wprintf_s_l(const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vwprintf_s_l(const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fwprintf_s_l(FILE *_File,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vfwprintf_s_l(FILE *_File,const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _swprintf_s_l(wchar_t *_DstBuf,size_t _DstSize,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vswprintf_s_l(wchar_t *_DstBuf,size_t _DstSize,const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snwprintf_s_l(wchar_t *_DstBuf,size_t _DstSize,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsnwprintf_s_l(wchar_t *_DstBuf,size_t _DstSize,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fwscanf_s_l(FILE *_File,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) fwscanf_s(FILE *_File, const wchar_t *_Format, ...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _swscanf_s_l(const wchar_t *_Src,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) swscanf_s(const wchar_t *_Src,const wchar_t *_Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snwscanf_s(const wchar_t *_Src,size_t _MaxCount,const wchar_t *_Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snwscanf_s_l(const wchar_t *_Src,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wscanf_s_l(const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) wscanf_s(const wchar_t *_Format, ...);


 
 
 
 

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wfopen_s(FILE **_File,const wchar_t *_Filename,const wchar_t *_Mode);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wfreopen_s(FILE **_File,const wchar_t *_Filename,const wchar_t *_Mode,FILE *_OldFile);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wtmpnam_s(wchar_t *_DstBuf,size_t _SizeInWords);
 


  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fwprintf_p(FILE *_File,const wchar_t *_Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wprintf_p(const wchar_t *_Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vfwprintf_p(FILE *_File,const wchar_t *_Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vwprintf_p(const wchar_t *_Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _swprintf_p(wchar_t *_DstBuf,size_t _MaxCount,const wchar_t *_Format,...);
  __attribute__((dllimport)) int __attribute__((__cdecl__)) _vswprintf_p(wchar_t *_DstBuf,size_t _MaxCount,const wchar_t *_Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _scwprintf_p(const wchar_t *_Format,...);
  __attribute__((dllimport)) int __attribute__((__cdecl__)) _vscwprintf_p(const wchar_t *_Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wprintf_l(const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wprintf_p_l(const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vwprintf_l(const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vwprintf_p_l(const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fwprintf_l(FILE *_File,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fwprintf_p_l(FILE *_File,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vfwprintf_l(FILE *_File,const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vfwprintf_p_l(FILE *_File,const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _swprintf_c_l(wchar_t *_DstBuf,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _swprintf_p_l(wchar_t *_DstBuf,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vswprintf_c_l(wchar_t *_DstBuf,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vswprintf_p_l(wchar_t *_DstBuf,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _scwprintf_l(const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _scwprintf_p_l(const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vscwprintf_p_l(const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snwprintf_l(wchar_t *_DstBuf,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsnwprintf_l(wchar_t *_DstBuf,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) __swprintf_l(wchar_t *_Dest,const wchar_t *_Format,_locale_t _Plocinfo,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) __vswprintf_l(wchar_t *_Dest,const wchar_t *_Format,_locale_t _Plocinfo,va_list _Args);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vscwprintf_l(const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fwscanf_l(FILE *_File,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _swscanf_l(const wchar_t *_Src,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snwscanf_l(const wchar_t *_Src,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wscanf_l(const wchar_t *_Format,_locale_t _Locale,...);





  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _fread_nolock_s(void *_DstBuf,size_t _DstSize,size_t _ElementSize,size_t _Count,FILE *_File);
# 1582 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdio.h" 2 3 4
# 4 "./test/_foreach.c" 2

# 1 "./hdr/libccc.h" 1
# 54 "./hdr/libccc.h"
# 1 "./hdr/libccc_config.h" 1
# 26 "./hdr/libccc_config.h"
# 1 "./hdr/libccc_define.h" 1
# 49 "./hdr/libccc_define.h"

# 345 "./hdr/libccc_define.h"

# 27 "./hdr/libccc_config.h" 2


# 525 "./hdr/libccc_config.h"

# 55 "./hdr/libccc.h" 2


# 1 "./hdr/libccc/bool.h" 1
# 27 "./hdr/libccc/bool.h"
# 1 "./hdr/libccc_config.h" 1
# 28 "./hdr/libccc/bool.h" 2
# 1 "./hdr/libccc_define.h" 1
# 29 "./hdr/libccc/bool.h" 2


# 80 "./hdr/libccc/bool.h"

# 80 "./hdr/libccc/bool.h"
typedef _Bool t_bool;
typedef t_bool t_bool;
# 92 "./hdr/libccc/bool.h"
__attribute__((malloc))
char* Bool_ToString(t_bool value, t_bool uppercase);



t_bool Bool_FromString(char const* str);






# 58 "./hdr/libccc.h" 2
# 1 "./hdr/libccc/int.h" 1
# 52 "./hdr/libccc/int.h"
# 1 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdint.h" 1 3 4
# 9 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdint.h" 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdint.h" 1 3 4
# 28 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdint.h" 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/crtdefs.h" 1 3 4
# 29 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdint.h" 2 3 4



# 1 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stddef.h" 1 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stddef.h" 1 3 4
# 18 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stddef.h" 3 4
  
# 18 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stddef.h" 3 4
 __attribute__ ((__dllimport__)) extern int *__attribute__((__cdecl__)) _errno(void);

  errno_t __attribute__((__cdecl__)) _set_errno(int _Value);
  errno_t __attribute__((__cdecl__)) _get_errno(int *_Value);


  __attribute__ ((__dllimport__)) extern unsigned long __attribute__((__cdecl__)) __threadid(void);

  __attribute__ ((__dllimport__)) extern uintptr_t __attribute__((__cdecl__)) __threadhandle(void);
# 2 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stddef.h" 2 3 4
# 416 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stddef.h" 3 4
typedef struct {
  long long __max_align_ll __attribute__((__aligned__(__alignof__(long long))));
  long double __max_align_ld __attribute__((__aligned__(__alignof__(long double))));
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
# 53 "./hdr/libccc/int.h" 2





# 88 "./hdr/libccc/int.h"

# 88 "./hdr/libccc/int.h"
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;



typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
# 118 "./hdr/libccc/int.h"
typedef u8 t_u8;
typedef t_u8 t_u8;
# 134 "./hdr/libccc/int.h"
typedef u16 t_u16;
typedef t_u16 t_u16;
# 150 "./hdr/libccc/int.h"
typedef u32 t_u32;
typedef t_u32 t_u32;
# 166 "./hdr/libccc/int.h"
typedef u64 t_u64;
typedef t_u64 t_u64;
# 205 "./hdr/libccc/int.h"
typedef s8 t_s8;
typedef t_s8 t_s8;
# 221 "./hdr/libccc/int.h"
typedef s16 t_s16;
typedef t_s16 t_s16;
# 237 "./hdr/libccc/int.h"
typedef s32 t_s32;
typedef t_s32 t_s32;
# 253 "./hdr/libccc/int.h"
typedef s64 t_s64;
typedef t_s64 t_s64;
# 288 "./hdr/libccc/int.h"
typedef t_u32 t_uint;
typedef t_uint t_uint;
# 300 "./hdr/libccc/int.h"
typedef t_s32 t_sint;
typedef t_sint t_sint;
# 364 "./hdr/libccc/int.h"
__attribute__((malloc))
char* S8_ToString(t_s8 n);



__attribute__((malloc))
char* S16_ToString(t_s16 n);



__attribute__((malloc))
char* S32_ToString(t_s32 n);



__attribute__((malloc))
char* S64_ToString(t_s64 n);



__attribute__((malloc))
char* U8_ToString(t_u8 n);



__attribute__((malloc))
char* U16_ToString(t_u16 n);



__attribute__((malloc))
char* U32_ToString(t_u32 n);



__attribute__((malloc))
char* U64_ToString(t_u64 n);





__attribute__((malloc))
char* U8_ToString_Hex(t_u8 n);



__attribute__((malloc))
char* U16_ToString_Hex(t_u16 n);



__attribute__((malloc))
char* U32_ToString_Hex(t_u32 n);



__attribute__((malloc))
char* U64_ToString_Hex(t_u64 n);





__attribute__((malloc))
char* S8_ToString_Base(t_s8 n, char const* base);



__attribute__((malloc))
char* S16_ToString_Base(t_s16 n, char const* base);



__attribute__((malloc))
char* S32_ToString_Base(t_s32 n, char const* base);



__attribute__((malloc))
char* S64_ToString_Base(t_s64 n, char const* base);



__attribute__((malloc))
char* U8_ToString_Base(t_u8 n, char const* base);



__attribute__((malloc))
char* U16_ToString_Base(t_u16 n, char const* base);



__attribute__((malloc))
char* U32_ToString_Base(t_u32 n, char const* base);



__attribute__((malloc))
char* U64_ToString_Base(t_u64 n, char const* base);
# 476 "./hdr/libccc/int.h"
t_s8 S8_FromString(char const* str);



t_s16 S16_FromString(char const* str);



t_s32 S32_FromString(char const* str);



t_s64 S64_FromString(char const* str);



t_u8 U8_FromString(char const* str);



t_u16 U16_FromString(char const* str);



t_u32 U32_FromString(char const* str);



t_u64 U64_FromString(char const* str);





t_u8 U8_FromString_Hex(char const* str);



t_u16 U16_FromString_Hex(char const* str);



t_u32 U32_FromString_Hex(char const* str);



t_u64 U64_FromString_Hex(char const* str);





t_s8 S8_FromString_Base(char const* str, char const* base);



t_s16 S16_FromString_Base(char const* str, char const* base);



t_s32 S32_FromString_Base(char const* str, char const* base);



t_s64 S64_FromString_Base(char const* str, char const* base);



t_u8 U8_FromString_Base(char const* str, char const* base);



t_u16 U16_FromString_Base(char const* str, char const* base);



t_u32 U32_FromString_Base(char const* str, char const* base);



t_u64 U64_FromString_Base(char const* str, char const* base);
# 573 "./hdr/libccc/int.h"
typedef union varint
{
 t_s8 sc;
 t_s16 ss;
 t_s32 si;
 t_s64 sl;
 t_u8 uc;
 t_u16 us;
 t_u32 ui;
 t_u64 ul;
} u_varint;





# 59 "./hdr/libccc.h" 2
# 1 "./hdr/libccc/fixed.h" 1
# 69 "./hdr/libccc/fixed.h"
# 1 "./hdr/libccc/int.h" 1
# 70 "./hdr/libccc/fixed.h" 2
# 1 "./hdr/libccc/float.h" 1
# 38 "./hdr/libccc/float.h"
# 1 "./hdr/libccc/bool.h" 1
# 39 "./hdr/libccc/float.h" 2



# 65 "./hdr/libccc/float.h"
typedef float t_f32;
typedef t_f32 t_f32;







typedef double t_f64;
typedef t_f64 t_f64;
# 119 "./hdr/libccc/float.h"
typedef t_f32 t_float;
typedef t_float t_float;
# 360 "./hdr/libccc/float.h"
typedef union float_cast
{
 t_float value_float;

 t_s32





    value_int;
} u_float_cast;
# 382 "./hdr/libccc/float.h"
t_bool F32_Equals(t_f32 n1, t_f32 n2);




t_bool F64_Equals(t_f64 n1, t_f64 n2);
# 404 "./hdr/libccc/float.h"
t_bool Float_Equals(t_float n1, t_float n2);
# 416 "./hdr/libccc/float.h"
__attribute__((malloc))
char* F32_ToString(t_f32 n, t_u8 precision);



__attribute__((malloc))
char* F64_ToString(t_f64 n, t_u8 precision);
# 439 "./hdr/libccc/float.h"
__attribute__((malloc))
char* Float_ToString(t_float n, t_u8 precision);





__attribute__((malloc))
char* F32_ToString_Exp(t_f32 n, t_u8 precision);







__attribute__((malloc))
char* F64_ToString_Exp(t_f64 n, t_u8 precision);
# 485 "./hdr/libccc/float.h"
__attribute__((malloc))
char* Float_ToString_Exp(t_float n, t_u8 precision);
# 496 "./hdr/libccc/float.h"
__attribute__((malloc))
char* F32_ToString_Dec(t_f32 n, t_u8 precision);




__attribute__((malloc))
char* F64_ToString_Dec(t_f64 n, t_u8 precision);
# 523 "./hdr/libccc/float.h"
__attribute__((malloc))
char* Float_ToString_Dec(t_float n, t_u8 precision);






__attribute__((malloc))
char* F32_ToString_Hex(t_f32 n, t_u8 precision);




__attribute__((malloc))
char* F64_ToString_Hex(t_f64 n, t_u8 precision);
# 558 "./hdr/libccc/float.h"
__attribute__((malloc))
char* Float_ToString_Hex(t_float n, t_u8 precision);






__attribute__((malloc))
char* F32_ToString_Bin(t_f32 n, t_u8 precision);




__attribute__((malloc))
char* F64_ToString_Bin(t_f64 n, t_u8 precision);
# 593 "./hdr/libccc/float.h"
__attribute__((malloc))
char* Float_ToString_Bin(t_float n, t_u8 precision);
# 607 "./hdr/libccc/float.h"
t_f32 F32_FromString(char const* str);



t_f64 F64_FromString(char const* str);
# 626 "./hdr/libccc/float.h"
t_float Float_FromString(char const* str);





t_f32 F32_FromString_Exp(char const* str);







t_f64 F64_FromString_Exp(char const* str);
# 667 "./hdr/libccc/float.h"
t_float Float_FromString_Exp(char const* str);
# 677 "./hdr/libccc/float.h"
t_f32 F32_FromString_Dec(char const* str);




t_f64 F64_FromString_Dec(char const* str);
# 700 "./hdr/libccc/float.h"
t_float Float_FromString_Dec(char const* str);






t_f32 F32_FromString_Hex(char const* str);




t_f64 F64_FromString_Hex(char const* str);
# 730 "./hdr/libccc/float.h"
t_float Float_FromString_Hex(char const* str);






t_f32 F32_FromString_Bin(char const* str);




t_f64 F64_FromString_Bin(char const* str);
# 760 "./hdr/libccc/float.h"
t_float Float_FromString_Bin(char const* str);
# 778 "./hdr/libccc/float.h"
typedef union varfloat
{
 t_f32 f;
 t_f64 d;






} u_varfloat;





# 71 "./hdr/libccc/fixed.h" 2


# 168 "./hdr/libccc/fixed.h"
 typedef t_s16 t_q16;
 typedef t_q16 t_q16;
# 181 "./hdr/libccc/fixed.h"
 typedef t_s32 t_q32;
 typedef t_q32 t_q32;
# 194 "./hdr/libccc/fixed.h"
 typedef t_s64 t_q64;
 typedef t_q64 t_q64;
# 229 "./hdr/libccc/fixed.h"
typedef t_q32 t_fixed;
typedef t_fixed t_q128;
# 259 "./hdr/libccc/fixed.h"
t_fixed Fixed (t_fixed part_integer, t_u64 part_fraction, t_u64 denominator);
t_q16 Q16 (t_s64 part_integer, t_u64 part_fraction, t_u64 denominator);
t_q32 Q32 (t_s64 part_integer, t_u64 part_fraction, t_u64 denominator);
t_q64 Q64 (t_s64 part_integer, t_u64 part_fraction, t_u64 denominator);




t_fixed Fixed_FromInt (t_fixed number);
t_q16 Q16_FromInt (t_s16 number);
t_q32 Q32_FromInt (t_s32 number);
t_q64 Q64_FromInt (t_s64 number);




t_fixed Fixed_FromFloat(t_fixed number);
t_q16 Q16_FromFloat (t_f64 number);
t_q32 Q32_FromFloat (t_f64 number);
t_q64 Q64_FromFloat (t_f64 number);






t_fixed Fixed_IntegerPart (t_fixed number);
t_q16 Q16_IntegerPart (t_q16 number);
t_q32 Q32_IntegerPart (t_q32 number);
t_q64 Q64_IntegerPart (t_q64 number);




t_fixed Fixed_FractionPart (t_fixed number);
t_q16 Q16_FractionPart (t_q16 number);
t_q32 Q32_FractionPart (t_q32 number);
t_q64 Q64_FractionPart (t_q64 number);




t_fixed Fixed_Rounded (t_fixed number);
t_q16 Q16_Rounded (t_q16 number);
t_q32 Q32_Rounded (t_q32 number);
t_q64 Q64_Rounded (t_q64 number);






t_fixed Fixed_Add (t_fixed q1, t_fixed q2);
t_q16 Q16_Add (t_q16 q1, t_q16 q2);
t_q32 Q32_Add (t_q32 q1, t_q32 q2);
t_q64 Q64_Add (t_q64 q1, t_q64 q2);




t_fixed Fixed_Sub (t_fixed q1, t_fixed q2);
t_q16 Q16_Sub (t_q16 q1, t_q16 q2);
t_q32 Q32_Sub (t_q32 q1, t_q32 q2);
t_q64 Q64_Sub (t_q64 q1, t_q64 q2);




t_fixed Fixed_Mul (t_fixed q1, t_fixed q2);
t_q16 Q16_Mul (t_q16 q1, t_q16 q2);
t_q32 Q32_Mul (t_q32 q1, t_q32 q2);
t_q64 Q64_Mul (t_q64 q1, t_q64 q2);




t_fixed Fixed_Div (t_fixed q1, t_fixed q2);
t_q16 Q16_Div (t_q16 q1, t_q16 q2);
t_q32 Q32_Div (t_q32 q1, t_q32 q2);
t_q64 Q64_Div (t_q64 q1, t_q64 q2);
# 352 "./hdr/libccc/fixed.h"
__attribute__((malloc))
char* Q16_ToString(t_q16 n);



__attribute__((malloc))
char* Q32_ToString(t_q32 n);



__attribute__((malloc))
char* Q64_ToString(t_q64 n);
# 376 "./hdr/libccc/fixed.h"
__attribute__((malloc))
char* Q16_ToString_Hex(t_q16 n);



__attribute__((malloc))
char* Q32_ToString_Hex(t_q32 n);



__attribute__((malloc))
char* Q64_ToString_Hex(t_q64 n);
# 400 "./hdr/libccc/fixed.h"
__attribute__((malloc))
char* Q16_ToString_Base(t_q16 n);



__attribute__((malloc))
char* Q32_ToString_Base(t_q32 n);



__attribute__((malloc))
char* Q64_ToString_Base(t_q64 n);
# 430 "./hdr/libccc/fixed.h"
t_q16 Q16_FromString(char const* str);



t_q32 Q32_FromString(char const* str);



t_q64 Q64_FromString(char const* str);
# 450 "./hdr/libccc/fixed.h"

# 60 "./hdr/libccc.h" 2
# 1 "./hdr/libccc/float.h" 1
# 61 "./hdr/libccc.h" 2
# 1 "./hdr/libccc/pointer.h" 1
# 43 "./hdr/libccc/pointer.h"
# 1 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stddef.h" 1 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stddef.h" 1 3 4
# 2 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stddef.h" 2 3 4
# 44 "./hdr/libccc/pointer.h" 2
# 56 "./hdr/libccc/pointer.h"

# 87 "./hdr/libccc/pointer.h"
typedef size_t t_size;
typedef t_size t_size;





typedef ptrdiff_t t_ptrdiff;
typedef t_ptrdiff t_ptrdiff;







typedef intmax_t t_sintmax;
typedef t_sintmax t_sintmax;





typedef uintmax_t t_uintmax;
typedef t_uintmax t_uintmax;







typedef intptr_t t_sintptr;
typedef t_sintptr t_sintptr;





typedef uintptr_t t_uintptr;
typedef t_uintptr t_uintptr;
# 138 "./hdr/libccc/pointer.h"
__attribute__((malloc))
char* Size_ToString(t_size value);



__attribute__((malloc))
char* Size_ToString_Hex(t_size value);



__attribute__((malloc))
char* Size_ToString_Readable(t_size value);



t_size Size_FromString(char const* str);






__attribute__((malloc))
char* Pointer_ToString(void const* ptr);


__attribute__((malloc))
char* Pointer_ToString_Hex(void const* ptr);






# 62 "./hdr/libccc.h" 2




# 89 "./hdr/libccc.h"

# 6 "./test/_foreach.c" 2
# 1 "./hdr/libccc/string.h" 1
# 34 "./hdr/libccc/string.h"
# 1 "./hdr/libccc/pointer.h" 1
# 35 "./hdr/libccc/string.h" 2
# 1 "./hdr/libccc/format.h" 1
# 27 "./hdr/libccc/format.h"
# 1 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 1 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdarg.h" 1 3 4
# 140 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdarg.h" 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/_mingw_stdarg.h" 1 3 4
# 141 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdarg.h" 2 3 4
# 2 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 2 3 4
# 28 "./hdr/libccc/format.h" 2




# 227 "./hdr/libccc/format.h"
__attribute__((format(gnu_printf, 1, 2)))
__attribute__((malloc))
char* String_Format(char const* format, ...);






__attribute__((malloc))
char* String_Format_VA(char const* format, va_list args);
# 252 "./hdr/libccc/format.h"
__attribute__((format(gnu_printf, 3, 4)))
t_size String_Format_N(char* dest, t_size max, char const* format, ...);






t_size String_Format_N_VA(char* dest, t_size max, char const* format, va_list args);
# 285 "./hdr/libccc/format.h"

# 36 "./hdr/libccc/string.h" 2


# 60 "./hdr/libccc/string.h"
__attribute__((malloc))
# 70 "./hdr/libccc/string.h"
char* String_New(t_size n);


__attribute__((malloc))
# 84 "./hdr/libccc/string.h"
char* String_New_C(t_size n, char c);
# 94 "./hdr/libccc/string.h"
void String_Set(char* str, char c);





void String_Clear(char* str);





void String_Delete(char* *a_str);






__attribute__((malloc))
char* String_Duplicate(char const* str);







__attribute__((malloc))
char* String_Duplicate_N(char const* str, t_size n);







__attribute__((malloc))
char* String_Duplicate_Char(char const* str, char const c);






char* String_Copy(char* dest, char const* src);







char* String_Copy_N(char* dest, char const* src, t_size n);
# 156 "./hdr/libccc/string.h"
t_size String_Copy_L(char* dest, char const* src, t_size size);






char* String_Concat(char* dest, char const* src);






char* String_Concat_N(char* dest, char const* src, t_size n);







t_size String_Concat_L(char* dest, char const* src, t_size size);
# 192 "./hdr/libccc/string.h"
t_size String_Length(char const* str);







int String_Compare(char const* str1, char const* str2);






int String_Compare_N(char const* str1, char const* str2, t_size n);







int String_Compare_IgnoreCase(char const* str1, char const* str2);







int String_Compare_N_IgnoreCase(char const* str1, char const* str2, t_size n);







t_bool String_Equals(char const* str1, char const* str2);






t_bool String_Equals_N(char const* str1, char const* str2, t_size n);






t_bool String_Equals_IgnoreCase(char const* str1, char const* str2);







t_bool String_Equals_N_IgnoreCase(char const* str1, char const* str2, t_size n);







t_bool String_Has(char const* str, char const* charset);






t_bool String_HasOnly(char const* str, char const* charset);





t_size String_Count_Char(char const* str, char c);






t_size String_Count_Charset(char const* str, char const* charset);





t_size String_Count_String(char const* str, char const* query);
# 299 "./hdr/libccc/string.h"
char* String_Find_Char(char const* str, char c);


char* String_Find_Charset(char const* str, char const* charset);


char* String_Find_String(char const* str, char const* query);



char* String_Find_R_Char(char const* str, char c);



char* String_Find_R_Charset(char const* str, char const* charset);



char* String_Find_R_String(char const* str, char const* query);




char* String_Find_N_Char(char const* str, char c, t_size n);


char* String_Find_N_Charset(char const* str, char const* charset, t_size n);


char* String_Find_N_String(char const* str, char const* query, t_size n);





t_ptrdiff String_IndexOf_Char(char const* str, char c);


t_ptrdiff String_IndexOf_Charset(char const* str, char const* charset);


t_ptrdiff String_IndexOf_String(char const* str, char const* query);



t_ptrdiff String_IndexOf_R_Char(char const* str, char c);



t_ptrdiff String_IndexOf_R_Charset(char const* str, char const* charset);



t_ptrdiff String_IndexOf_R_String(char const* str, char const* query);




t_ptrdiff String_IndexOf_N_Char(char const* str, char c, t_size n);


t_ptrdiff String_IndexOf_N_Charset(char const* str, char const* charset, t_size n);


t_ptrdiff String_IndexOf_N_String(char const* str, char const* query, t_size n);
# 372 "./hdr/libccc/string.h"
__attribute__((malloc))
char* String_Remove(char const* str, char const* query);







__attribute__((malloc))
char* String_ToEscape(char const* str);







__attribute__((malloc))
char* String_Replace_Char(char const* str, char const char_old, char const char_new);
# 400 "./hdr/libccc/string.h"
__attribute__((malloc))
char* String_Replace_Charset(char const* str, char const* charset_old, char const* charset_new);







__attribute__((malloc))
char* String_Replace_String(char const* str, char const* str_old, char const* str_new);
# 425 "./hdr/libccc/string.h"
__attribute__((malloc))
char* String_Join(char const* str1, char const* str2);






__attribute__((malloc))
char* String_Merge(char* *a_s1, char* *a_s2);






__attribute__((malloc))
char* String_Append(char* *dest, char const* src);







__attribute__((malloc))
char* String_Prepend(char const* src, char* *dest);
# 466 "./hdr/libccc/string.h"
char* String_Insert_InPlace(char* *dest, char const* src, t_u32 index);







void String_Replace_Char_InPlace(char* str, char const char_old, char const char_new);
# 484 "./hdr/libccc/string.h"
void String_Replace_Charset_InPlace(char* str, char const* charset_old, char const* charset_new);






void String_Replace_String_InPlace(char* *a_str, char const* str_old, char const* str_new);
# 501 "./hdr/libccc/string.h"
char* String_Map_InPlace(char* *a_str, char (*f)(char));
# 516 "./hdr/libccc/string.h"
__attribute__((malloc))
char* String_Trim(char const* str, char const* charset);






__attribute__((malloc))
char* String_Trim_L(char const* str, char const* charset);






__attribute__((malloc))
char* String_Trim_R(char const* str, char const* charset);







__attribute__((malloc))
char* String_Pad(char const* str, char c, t_size length);







__attribute__((malloc))
char* String_Pad_L(char const* str, char c, t_size length);







__attribute__((malloc))
char* String_Pad_R(char const* str, char c, t_size length);







__attribute__((malloc))
char* String_ToPrintableString(char const* str);
# 584 "./hdr/libccc/string.h"
__attribute__((malloc))
char* String_Reverse(char const* str);






__attribute__((malloc))
char* String_Insert(char const* dest, char const* src, t_size offset);






__attribute__((malloc))
char* String_Sub(char const* str, t_size index, t_size n);
# 610 "./hdr/libccc/string.h"
void String_Iterate(char* str, void (*f)(char* c));






void String_Iterate_I(char* str, void (*f)(t_size index, char* c));






__attribute__((malloc))
char* String_Map(char const* str, char (*f)(char c));






__attribute__((malloc))
char* String_Map_I(char const* str, char (*f)(t_size index, char c));






# 7 "./test/_foreach.c" 2
# 1 "./hdr/libccc/sys/io.h" 1
# 29 "./hdr/libccc/sys/io.h"
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
  void * __attribute__((__cdecl__)) memcpy(void * __restrict__ _Dst,const void * __restrict__ _Src,size_t _Size) ;
  __attribute__((dllimport)) errno_t __attribute__((__cdecl__)) memcpy_s (void *_dest,size_t _numberOfElements,const void *_src,size_t _count);
  void * __attribute__((__cdecl__)) mempcpy (void *_Dst, const void *_Src, size_t _Size);
  void * __attribute__((__cdecl__)) memset(void *_Dst,int _Val,size_t _Size);

  void * __attribute__((__cdecl__)) memccpy(void *_Dst,const void *_Src,int _Val,size_t _Size) ;
  int __attribute__((__cdecl__)) memicmp(const void *_Buf1,const void *_Buf2,size_t _Size) ;


  char * __attribute__((__cdecl__)) _strset(char *_Str,int _Val) ;
  char * __attribute__((__cdecl__)) _strset_l(char *_Str,int _Val,_locale_t _Locale) ;
  char * __attribute__((__cdecl__)) strcpy(char * __restrict__ _Dest,const char * __restrict__ _Source);
  char * __attribute__((__cdecl__)) strcat(char * __restrict__ _Dest,const char * __restrict__ _Source);
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
  char *__attribute__((__cdecl__)) strncat(char * __restrict__ _Dest,const char * __restrict__ _Source,size_t _Count) ;
  int __attribute__((__cdecl__)) strncmp(const char *_Str1,const char *_Str2,size_t _MaxCount);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _strnicmp(const char *_Str1,const char *_Str2,size_t _MaxCount);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _strnicmp_l(const char *_Str1,const char *_Str2,size_t _MaxCount,_locale_t _Locale);
  char *strncpy(char * __restrict__ _Dest,const char * __restrict__ _Source,size_t _Count) ;
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _strnset(char *_Str,int _Val,size_t _MaxCount) ;
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _strnset_l(char *str,int c,size_t count,_locale_t _Locale) ;
  char *__attribute__((__cdecl__)) strpbrk(const char *_Str,const char *_Control);
  char *__attribute__((__cdecl__)) strrchr(const char *_Str,int _Ch);
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _strrev(char *_Str);
  size_t __attribute__((__cdecl__)) strspn(const char *_Str,const char *_Control);
  char *__attribute__((__cdecl__)) strstr(const char *_Str,const char *_SubStr);
  char *__attribute__((__cdecl__)) strtok(char * __restrict__ _Str,const char * __restrict__ _Delim) ;
       

  char *strtok_r(char * __restrict__ _Str, const char * __restrict__ _Delim, char ** __restrict__ __last);
       
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _strupr(char *_String) ;
  __attribute__ ((__dllimport__)) char *_strupr_l(char *_String,_locale_t _Locale) ;
  size_t __attribute__((__cdecl__)) strxfrm(char * __restrict__ _Dst,const char * __restrict__ _Src,size_t _MaxCount);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _strxfrm_l(char * __restrict__ _Dst,const char * __restrict__ _Src,size_t _MaxCount,_locale_t _Locale);


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
  wchar_t *__attribute__((__cdecl__)) wcscat(wchar_t * __restrict__ _Dest,const wchar_t * __restrict__ _Source) ;
  wchar_t *__attribute__((__cdecl__)) wcschr(const wchar_t *_Str,wchar_t _Ch);
  int __attribute__((__cdecl__)) wcscmp(const wchar_t *_Str1,const wchar_t *_Str2);
  wchar_t *__attribute__((__cdecl__)) wcscpy(wchar_t * __restrict__ _Dest,const wchar_t * __restrict__ _Source) ;
  size_t __attribute__((__cdecl__)) wcscspn(const wchar_t *_Str,const wchar_t *_Control);
  size_t __attribute__((__cdecl__)) wcslen(const wchar_t *_Str);
  size_t __attribute__((__cdecl__)) wcsnlen(const wchar_t *_Src,size_t _MaxCount);
  wchar_t *wcsncat(wchar_t * __restrict__ _Dest,const wchar_t * __restrict__ _Source,size_t _Count) ;
  int __attribute__((__cdecl__)) wcsncmp(const wchar_t *_Str1,const wchar_t *_Str2,size_t _MaxCount);
  wchar_t *wcsncpy(wchar_t * __restrict__ _Dest,const wchar_t * __restrict__ _Source,size_t _Count) ;
  wchar_t *__attribute__((__cdecl__)) _wcsncpy_l(wchar_t * __restrict__ _Dest,const wchar_t * __restrict__ _Source,size_t _Count,_locale_t _Locale) ;
  wchar_t *__attribute__((__cdecl__)) wcspbrk(const wchar_t *_Str,const wchar_t *_Control);
  wchar_t *__attribute__((__cdecl__)) wcsrchr(const wchar_t *_Str,wchar_t _Ch);
  size_t __attribute__((__cdecl__)) wcsspn(const wchar_t *_Str,const wchar_t *_Control);
  wchar_t *__attribute__((__cdecl__)) wcsstr(const wchar_t *_Str,const wchar_t *_SubStr);
  wchar_t *__attribute__((__cdecl__)) wcstok(wchar_t * __restrict__ _Str,const wchar_t * __restrict__ _Delim) ;
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
  size_t __attribute__((__cdecl__)) wcsxfrm(wchar_t * __restrict__ _Dst,const wchar_t * __restrict__ _Src,size_t _MaxCount);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _wcsxfrm_l(wchar_t * __restrict__ _Dst,const wchar_t * __restrict__ _Src,size_t _MaxCount,_locale_t _Locale);
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

  extern __inline__ __attribute__((__always_inline__,__gnu_inline__)) size_t __attribute__((__cdecl__)) wcsnlen_s(const wchar_t * _src, size_t _count) {
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
# 223 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/io.h" 3 4
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
# 30 "./hdr/libccc/sys/io.h" 2


# 1 "./hdr/libccc/color.h" 1
# 37 "./hdr/libccc/color.h"

# 46 "./hdr/libccc/color.h"

# 46 "./hdr/libccc/color.h"
typedef t_u16 t_argb16;
typedef t_argb16 t_LIBCONFIG_TYPENAME_COLOR_ARGB16;
# 65 "./hdr/libccc/color.h"
typedef t_u32 t_argb32;
typedef t_argb32 t_LIBCONFIG_TYPENAME_COLOR_ARGB32;
# 84 "./hdr/libccc/color.h"
typedef struct argb
{
 t_float a;
 t_float r;
 t_float g;
 t_float b;
} s_argb;
typedef s_argb s_LIBCONFIG_TYPENAME_COLOR_ARGB;




typedef struct ahsl
{
 t_float a;
 t_float hue;
 t_float sat;
 t_float lum;
} s_ahsl;
typedef s_ahsl s_LIBCONFIG_TYPENAME_COLOR_AHSL;
# 114 "./hdr/libccc/color.h"
t_u8 Color_ARGB16_Get_A(t_argb16 color);



t_u8 Color_ARGB16_Get_R(t_argb16 color);



t_u8 Color_ARGB16_Get_G(t_argb16 color);



t_u8 Color_ARGB16_Get_B(t_argb16 color);
# 143 "./hdr/libccc/color.h"
t_argb16 Color_ARGB16_Set(t_u8 a, t_u8 r, t_u8 g, t_u8 b);



t_argb16 Color_ARGB16_Set_A(t_argb16 color, t_bool a);



t_argb16 Color_ARGB16_Set_R(t_argb16 color, t_u8 r);



t_argb16 Color_ARGB16_Set_G(t_argb16 color, t_u8 g);



t_argb16 Color_ARGB16_Set_B(t_argb16 color, t_u8 b);
# 171 "./hdr/libccc/color.h"
t_argb32 Color_ARGB16_To_ARGB32(t_argb16 color);



s_argb Color_ARGB16_To_ARGB(t_argb16 color);
# 187 "./hdr/libccc/color.h"
t_u16 Color_ARGB16_Difference(t_argb16 c1, t_argb16 c2);
# 198 "./hdr/libccc/color.h"
t_argb16 const* Color_ARGB16_GetNearest(t_argb16 target, t_argb16 const* colors, t_size n);
# 210 "./hdr/libccc/color.h"
t_u8 Color_ARGB32_Get_A(t_argb32 color);



t_u8 Color_ARGB32_Get_R(t_argb32 color);



t_u8 Color_ARGB32_Get_G(t_argb32 color);



t_u8 Color_ARGB32_Get_B(t_argb32 color);
# 239 "./hdr/libccc/color.h"
t_argb32 Color_ARGB32_Set(t_u8 a, t_u8 r, t_u8 g, t_u8 b);



t_argb32 Color_ARGB32_Set_A(t_argb32 color, t_u8 a);



t_argb32 Color_ARGB32_Set_R(t_argb32 color, t_u8 r);



t_argb32 Color_ARGB32_Set_G(t_argb32 color, t_u8 g);



t_argb32 Color_ARGB32_Set_B(t_argb32 color, t_u8 b);
# 267 "./hdr/libccc/color.h"
t_argb16 Color_ARGB32_To_ARGB16(t_argb32 color);



s_argb Color_ARGB32_To_ARGB(t_argb32 color);
# 283 "./hdr/libccc/color.h"
t_u32 Color_ARGB32_Difference(t_argb32 c1, t_argb32 c2);
# 294 "./hdr/libccc/color.h"
t_argb32 const* Color_ARGB32_GetNearest(t_argb32 target, t_argb32 const* colors, t_size n);
# 316 "./hdr/libccc/color.h"
s_argb Color_ARGB_Set(t_float a, t_float r, t_float g, t_float b);



void Color_ARGB_Set_A(s_argb* color, t_float a);



void Color_ARGB_Set_R(s_argb* color, t_float r);



void Color_ARGB_Set_G(s_argb* color, t_float g);



void Color_ARGB_Set_B(s_argb* color, t_float b);
# 344 "./hdr/libccc/color.h"
t_argb16 Color_ARGB_To_ARGB16(s_argb const* color);
# 353 "./hdr/libccc/color.h"
t_argb32 Color_ARGB_To_ARGB32(s_argb const* color);







s_ahsl Color_ARGB_To_AHSL(s_argb const* color);
# 374 "./hdr/libccc/color.h"
s_argb const* Color_ARGB_GetNearest(s_argb target, s_argb const* colors, t_size n);
# 396 "./hdr/libccc/color.h"
s_ahsl Color_AHSL_Set(t_float a, t_float hue, t_float sat, t_float lum);



void Color_AHSL_Set_A(s_ahsl* color, t_float a);



void Color_AHSL_Set_H(s_ahsl* color, t_float hue);



void Color_AHSL_Set_S(s_ahsl* color, t_float sat);



void Color_AHSL_Set_L(s_ahsl* color, t_float lum);
# 423 "./hdr/libccc/color.h"
s_argb Color_AHSL_To_ARGB(s_ahsl const* color);
# 436 "./hdr/libccc/color.h"
s_ahsl const* Color_AHSL_GetNearest(s_ahsl target, s_ahsl const* colors, t_size n);






# 33 "./hdr/libccc/sys/io.h" 2


# 46 "./hdr/libccc/sys/io.h"
typedef int t_fd;
typedef t_fd t_LIBCONFIG_TYPENAME_FILEDESC;
# 82 "./hdr/libccc/sys/io.h"
typedef int t_io_error;
typedef t_io_error t_io_error;




typedef unsigned int t_io_mode;
typedef t_io_mode t_io_mode;
# 112 "./hdr/libccc/sys/io.h"
typedef unsigned int t_io_open;
typedef t_io_open t_io_open;
# 251 "./hdr/libccc/sys/io.h"
char* IO_GetError(int error_num);
# 262 "./hdr/libccc/sys/io.h"
t_u8 IO_GetColor(t_argb32 color);
# 272 "./hdr/libccc/sys/io.h"
t_bool IO_IsTerminal(t_fd fd);
# 294 "./hdr/libccc/sys/io.h"
t_fd IO_Open(char const* filepath, t_io_open flags, t_io_mode mode);
# 306 "./hdr/libccc/sys/io.h"
t_io_error IO_Close(t_fd fd);
# 319 "./hdr/libccc/sys/io.h"
t_io_error IO_ChangeMode(char const* filepath, t_io_mode mode);
# 363 "./hdr/libccc/sys/io.h"
t_sintmax IO_Read_File(t_fd const fd, char* *a_file, t_size max);
# 380 "./hdr/libccc/sys/io.h"
t_sintmax IO_Read_Lines(t_fd const fd, char** *a_strarr);
# 398 "./hdr/libccc/sys/io.h"
int IO_Read_NextLine(t_fd const fd, char* *a_line);
# 416 "./hdr/libccc/sys/io.h"
t_io_error IO_Write_Char(t_fd fd, char c);



t_io_error IO_Write_String(t_fd fd, char const* str);



t_io_error IO_Write_Line(t_fd fd, char const* str);



t_io_error IO_Write_Lines(t_fd fd, char const** strarr);



t_io_error IO_Write_Memory(t_fd fd, t_u8 const* ptr, t_size n, t_u8 cols);



__attribute__((format(gnu_printf, 2, 3)))
t_io_error IO_Write_Format(t_fd fd, char const* format, ...);
# 450 "./hdr/libccc/sys/io.h"
t_io_error IO_Output_Char(char c);




t_io_error IO_Output_String(char const* str);




t_io_error IO_Output_Line(char const* str);




t_io_error IO_Output_Lines(char const** strarr);




t_io_error IO_Output_Memory(t_u8 const* ptr, t_size n, t_u8 cols);




__attribute__((format(gnu_printf, 1, 2)))
t_io_error IO_Output_Format(char const* format, ...);
# 622 "./hdr/libccc/sys/io.h"

# 8 "./test/_foreach.c" 2

# 1 "./hdr/libccc/monad/list.c" 1


# 1 "./hdr/libccc/monad/list.h" 1
# 40 "./hdr/libccc/monad/list.h"
# 1 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 1 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdarg.h" 1 3 4
# 2 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 2 3 4
# 41 "./hdr/libccc/monad/list.h" 2




# 74 "./hdr/libccc/monad/list.h"
typedef struct list
{

 struct list* next;
 void* item;
} s_list;
# 105 "./hdr/libccc/monad/list.h"
__attribute__((malloc))
s_list* List_Item(void* item);
# 119 "./hdr/libccc/monad/list.h"
__attribute__((malloc))
s_list* List_New(t_uint n, ...);






void List_Delete(s_list* *a_list);







__attribute__((malloc))
s_list* List_Duplicate(s_list const* list);
# 148 "./hdr/libccc/monad/list.h"
s_list* List_Get(s_list const* list, t_uint index);
# 158 "./hdr/libccc/monad/list.h"
s_list* List_Set(s_list* list, t_uint index, void* item);
# 168 "./hdr/libccc/monad/list.h"
s_list* List_Copy(s_list* dest, s_list const* src, t_uint n);
# 179 "./hdr/libccc/monad/list.h"
__attribute__((malloc))
s_list* List_Sub(s_list const* list, t_uint index, t_uint n);
# 202 "./hdr/libccc/monad/list.h"
s_list* List_Append(s_list* list, s_list* elem);
# 215 "./hdr/libccc/monad/list.h"
s_list* List_Prepend(s_list* list, s_list* elem);
# 230 "./hdr/libccc/monad/list.h"
s_list* List_Insert(s_list* list, void* item, t_uint index);





s_list* List_Remove(s_list* list, t_uint index);




s_list* List_RemoveAll(s_list* list, void* item);






__attribute__((malloc))
s_list* List_Replace(s_list const* list, void* old, void* new);
# 267 "./hdr/libccc/monad/list.h"
t_uint List_Length(s_list const* list);
# 277 "./hdr/libccc/monad/list.h"
s_list const* List_Find(s_list const* list, void* item);
# 287 "./hdr/libccc/monad/list.h"
t_sint List_IndexOf(s_list const* list, void* item);
# 299 "./hdr/libccc/monad/list.h"
t_bool List_Equals(s_list const* list1, s_list const* list2);



t_bool List_Equals_N(s_list const* list1, s_list const* list2, t_uint n);



t_sint List_Compare(s_list const* list1, s_list const* list2, t_sint (*compare)(void* item1, void* item2));



t_sint List_Compare_N(s_list const* list1, s_list const* list2, t_sint (*compare)(void* item1, void* item2), t_uint n);
# 327 "./hdr/libccc/monad/list.h"
void List_Iterate(s_list* list, void (*f)(void* item));


void List_Iterate_I(s_list* list, void (*f)(void* item, t_uint index));
# 340 "./hdr/libccc/monad/list.h"
__attribute__((malloc))
s_list* List_Map(s_list const* list, void* (*map)(void* item));


__attribute__((malloc))
s_list* List_Map_I(s_list const* list, void* (*map)(void* item, t_uint index));





__attribute__((malloc))
s_list* List_Filter(s_list const* list, t_bool (*filter)(void* item));


__attribute__((malloc))
s_list* List_Filter_I(s_list const* list, t_bool (*filter)(void* item, t_uint index));






# 4 "./hdr/libccc/monad/list.c" 2

# 1 "./hdr/libccc/../../src/monad/list/lstitem.c" 1

# 1 "./hdr/libccc/memory.h" 1
# 35 "./hdr/libccc/memory.h"

# 54 "./hdr/libccc/memory.h"
__attribute__((malloc))
void* Memory_Alloc(t_size size);
# 68 "./hdr/libccc/memory.h"
__attribute__((malloc))
void* Memory_New(t_size size);
# 80 "./hdr/libccc/memory.h"
__attribute__((malloc))
void* Memory_New_C(t_size size, char c);
# 93 "./hdr/libccc/memory.h"
void Memory_Free(void* ptr);
# 104 "./hdr/libccc/memory.h"
void Memory_Delete(void* *a_ptr);
# 116 "./hdr/libccc/memory.h"
void Memory_Set(void* ptr, t_u8 byte, t_size n);
# 125 "./hdr/libccc/memory.h"
void Memory_Clear(void* ptr, t_size n);
# 136 "./hdr/libccc/memory.h"
void* Memory_Copy(void* dest, void const* src, t_size n);
# 147 "./hdr/libccc/memory.h"
void* Memory_Copy_C(void* dest, void const* src, t_u8 byte, t_size n);
# 158 "./hdr/libccc/memory.h"
void* Memory_Move(void* dest, void const* src, t_size n);
# 171 "./hdr/libccc/memory.h"
__attribute__((malloc))
void* Memory_Duplicate(void const* ptr, t_size n);
# 184 "./hdr/libccc/memory.h"
void* Memory_Join(void const* ptr1, t_size length1, void const* ptr2, t_size length2);



void* Memory_Append(void* *a_dest, t_size dest_length, void const* src, t_size src_length);



void* Memory_Prepend(void const* src, t_size src_length, void* *a_dest, t_size dest_length);



void* Memory_Merge(void* *a_ptr1, t_size length1, void* *a_ptr2, t_size length2);
# 215 "./hdr/libccc/memory.h"
void* Memory_Find(void const* ptr, t_u8 byte, t_size n);
# 227 "./hdr/libccc/memory.h"
void Memory_Replace(void* ptr, t_u8 old, t_u8 new, t_size n);
# 240 "./hdr/libccc/memory.h"
int Memory_Compare(void const* ptr1, void const* ptr2, t_size n);
# 253 "./hdr/libccc/memory.h"
int Memory_Swap(void* ptr1, void* ptr2, t_size size);
# 266 "./hdr/libccc/memory.h"
t_u64 Memory_GetBits(t_u64 value, t_u8 bit, t_u8 length);






# 3 "./hdr/libccc/../../src/monad/list/lstitem.c" 2




s_list* List_Item(void* item)
{
 s_list* result;

 result = (s_list*)Memory_New(sizeof(s_list));
 if (result == ((void*)0))
  return (((void*)0));
 result->item = item;
 return (result);
}
# 6 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstnew.c" 1

# 1 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 1 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdarg.h" 1 3 4
# 2 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 2 3 4
# 3 "./hdr/libccc/../../src/monad/list/lstnew.c" 2






s_list* List_New(t_uint n, ...)
{
 va_list list;
 void* item;
 s_list* result = ((void*)0);
 s_list* elem;
 s_list* new;

 if (n == 0)
  return (((void*)0));
 
# 19 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
__builtin_va_start(
# 19 "./hdr/libccc/../../src/monad/list/lstnew.c"
list
# 19 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
,
# 19 "./hdr/libccc/../../src/monad/list/lstnew.c"
n
# 19 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
)
# 19 "./hdr/libccc/../../src/monad/list/lstnew.c"
                 ;
 for (t_uint i = 1; i <= n; ++i)
 {
  item = 
# 22 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
        __builtin_va_arg(
# 22 "./hdr/libccc/../../src/monad/list/lstnew.c"
        list
# 22 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
        ,
# 22 "./hdr/libccc/../../src/monad/list/lstnew.c"
        void*
# 22 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
        )
# 22 "./hdr/libccc/../../src/monad/list/lstnew.c"
                       ;
  if (!(new = (s_list*)Memory_Alloc(sizeof(s_list))))
   break;
  new->next = ((void*)0);
  new->item = item;
  if (i == 1)
  {
   elem = new;
   result = new;
  }
  else
  {
   elem->next = new;
   elem = new;
  }
 }
 
# 38 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
__builtin_va_end(
# 38 "./hdr/libccc/../../src/monad/list/lstnew.c"
list
# 38 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
)
# 38 "./hdr/libccc/../../src/monad/list/lstnew.c"
            ;
 return (result);
}
# 7 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstdel.c" 1






void List_Delete(s_list* *a_list)
{

 s_list* next;
 s_list* i;


 if (a_list == ((void*)0))
  return ;

 i = *a_list;
 while (i)
 {

  next = i->next;
  Memory_Free(i);
  i = next;


 }
 *a_list = ((void*)0);
}
# 8 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstdup.c" 1






s_list* List_Duplicate(s_list const* list)
{
 s_list* result = ((void*)0);
 s_list* elem = ((void*)0);
 s_list* tmp;


 if (list == ((void*)0))
  return (((void*)0));

 while (list)
 {
  if (!(tmp = (s_list*)Memory_Duplicate(list, sizeof(s_list))))
   break;
  if (result == ((void*)0))
   result = tmp;
  else
  {

   elem->next = tmp;
  }
  elem = tmp;
  list = list->next;
 }
 return (result);
}
# 9 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstget.c" 1





s_list* List_Get(s_list const* list, t_uint index)
{

 if (list == ((void*)0))
  return (((void*)0));

 for (t_uint i = 0; i < index; ++i)
 {
  if (list->next == ((void*)0))
   return (((void*)0));
  else
   list = list->next;
 }
 return ((s_list*)list);
}
# 10 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstset.c" 1





s_list* List_Set(s_list* list, t_uint index, void* item)
{

 if (list == ((void*)0))
  return (((void*)0));

 for (t_uint i = 0; i < index; ++i)
 {
  if (list->next == ((void*)0))
   return (((void*)0));
  else
  {
   list->item = item;
   return (list);
  }
  list = list->next;
 }
 return (((void*)0));
}
# 11 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstcpy.c" 1





s_list* List_Copy(s_list* dest, s_list const* src, t_uint n)
{
 s_list* list;


 if (dest == ((void*)0) || src == ((void*)0))
  return (((void*)0));

 list = dest;
 while (list && n--)
 {
  list->item = src->item;
  src = src->next;
  list = list->next;
 }
 return (dest);
}
# 12 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstsub.c" 1






s_list* List_Sub(s_list const* list, t_uint index, t_uint n)
{
 s_list* result = ((void*)0);
 s_list* elem = ((void*)0);
 s_list* tmp;


 if (list == ((void*)0))
  return (((void*)0));

 if (n == 0)
  return (((void*)0));
 while (list && index--)
 {
  list = list->next;
 }
 if (list == ((void*)0))
  return (((void*)0));
 elem = result;
 list = list->next;
 while (list && n--)
 {
  if (!(tmp = (s_list*)Memory_Duplicate(list, sizeof(s_list))))
   break;
  if (result == ((void*)0))
   result = tmp;
  else
  {

   elem->next = tmp;
  }
  elem = tmp;
  list = list->next;
 }
 return (result);
}
# 13 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstappend.c" 1





s_list* List_Append(s_list* list, s_list* elem)
{
 s_list* i;


 if (list == ((void*)0))
  return (((void*)0));

 if (elem == ((void*)0))
  return (list);
 i = list;
 while (i->next != ((void*)0))
 {
  i = i->next;
 }

 i->next = elem;
 return (list);
}
# 14 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstprepend.c" 1





s_list* List_Prepend(s_list* list, s_list* elem)
{

 if (list == ((void*)0))
  return (((void*)0));

 if (elem == ((void*)0))
  return (list);

 elem->next = list;
 return (elem);
}
# 15 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstinsert.c" 1






s_list* List_Insert(s_list* list, void* item, t_uint index)
{
 s_list* elem;
 s_list* new;
 s_list* tmp;


 if (list == ((void*)0))
  return (((void*)0));

 if (!(new = (s_list*)Memory_Alloc(sizeof(s_list))))
  return (list);
 if (list == ((void*)0) || index == 0)
 {
  new->item = item;
  new->next = list;
  return (new);
 }
 elem = list;
 for (t_uint i = 0; i < index; ++i)
 {
  elem = elem->next;
 }

 tmp = elem->next;
 elem->next = new;
 new->next = tmp;
 return (list);
}
# 16 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstremove.c" 1






s_list* List_Remove(s_list* list, t_uint index)
{
 s_list* elem;
 s_list* tmp;


 if (list == ((void*)0))
  return (((void*)0));

 elem = list;
 if (index == 0)
 {
  list = list->next;
  Memory_Free(elem);
  return (list);
 }
 for (t_uint i = 0; elem && i < index; ++i)
 {
  elem = elem->next;
 }
 if (elem == ((void*)0) || elem->next == ((void*)0))
  return (list);
 tmp = elem->next;
 elem->next = tmp->next;

 Memory_Free(tmp);
 return (list);
}



s_list* List_RemoveAll(s_list* list, void* item)
{
 s_list* elem;
 s_list* tmp;


 if (list == ((void*)0))
  return (((void*)0));

 elem = list;
 for (t_uint i = 0; elem; ++i)
 {
  if (((elem->item) == (item)))
  {
   tmp = elem->next;
   elem->next = tmp->next;

   Memory_Free(tmp);
  }
  elem = elem->next;
 }
 return (list);
}
# 17 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstreplace.c" 1





s_list* List_Replace(s_list const* list, void* old, void* new)
{
 s_list* result = ((void*)0);
 s_list* elem;


 if (list == ((void*)0))
  return (((void*)0));

 while (list)
 {
  elem = List_Item(((list->item) == (old)) ? new : list->item);
  if (elem == ((void*)0))
   break;
  List_Append(result, elem);
  list = list->next;
 }
 return (result);
}
# 18 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstsize.c" 1





t_uint List_Size(s_list const* lst)
{
 t_uint result;


 if (lst == ((void*)0))
  return (0);

 result = 0;
 while (lst)
 {
  ++result;
  lst = lst->next;
 }
 return (result);
}
# 19 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstequ.c" 1





t_bool List_Equals(s_list const* list1, s_list const* list2)
{

 if (list1 == list2)
  return ((1));
 if (list1 == ((void*)0) || list2 == ((void*)0))
  return ((0));

 while (list1 && list2)
 {
  if (!((list1->item) == (list2->item)))
   return ((0));
  list1 = list1->next;
  list2 = list2->next;
 }
 return ((1));
}



t_bool List_Equals_N(s_list const* list1, s_list const* list2, t_uint n)
{

 if (list1 == list2)
  return ((1));
 if (list1 == ((void*)0) || list2 == ((void*)0))
  return ((0));

 while (list1 && list2 && n--)
 {
  if (!((list1->item) == (list2->item)))
   return ((0));
  list1 = list1->next;
  list2 = list2->next;
 }
 return ((1));
}
# 20 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstcmp.c" 1





t_sint List_Compare(s_list const* list1, s_list const* list2, t_sint (*compare)(void* item1, void* item2))
{
 t_sint result;


 if (list1 == list2)
  return (0);
 if (list1 == ((void*)0) || list2 == ((void*)0) || compare == ((void*)0))
  return ((-1));

 while (list1 && list2)
 {
  result = compare(list1->item, list2->item);
  if (result != 0)
   return (result);
  list1 = list1->next;
  list2 = list2->next;
 }
 return (0);
}



t_sint List_Compare_N(s_list const* list1, s_list const* list2, t_sint (*compare)(void* item1, void* item2), t_uint n)
{
 t_sint result;


 if (list1 == list2)
  return (0);
 if (list1 == ((void*)0) || list2 == ((void*)0) || compare == ((void*)0))
  return ((-1));

 while (list1 && list2 && n--)
 {
  result = compare(list1->item, list2->item);
  if (result != 0)
   return (result);
  list1 = list1->next;
  list2 = list2->next;
 }
 return (0);
}
# 21 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstiter.c" 1





void List_Iterate(s_list* list, void (*f)(void* item))
{

 if (list == ((void*)0) || f == ((void*)0))
  return ;

 while (list)
 {
  f(list->item);
  list = list->next;
 }
}



void List_Iterate_I(s_list* list, void (*f)(void* item, t_uint index))
{
 t_uint i;


 if (list == ((void*)0) || f == ((void*)0))
  return ;

 i = 0;
 while (list)
 {
  f(list->item, i);
  list = list->next;
  ++i;
 }
}
# 22 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstmap.c" 1





s_list* List_Map(s_list const* list, void* (*map)(void* item))
{
 s_list* result = ((void*)0);
 s_list* elem;


 if (list == ((void*)0) || map == ((void*)0))
  return (((void*)0));

 while (list)
 {
  elem = List_Item(map(list->item));
  if (elem == ((void*)0))
   break;
  List_Append(result, elem);
  list = list->next;
 }
 return (result);
}



s_list* List_Map_I(s_list const* list, void* (*map)(void* item, t_uint index))
{
 s_list* result = ((void*)0);
 s_list* elem;
 t_uint i;


 if (list == ((void*)0) || map == ((void*)0))
  return (((void*)0));

 i = 0;
 while (list)
 {
  elem = List_Item(map(list->item, i));
  if (elem == ((void*)0))
   break;
  List_Append(result, elem);
  list = list->next;
  ++i;
 }
 return (result);
}
# 23 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstfilt.c" 1





s_list* List_Filter(s_list const* list, t_bool (*filter)(void* item))
{
 s_list* result = ((void*)0);
 s_list* elem;


 if (list == ((void*)0) || filter == ((void*)0))
  return (((void*)0));

 while (list)
 {
  if (filter(list->item))
  {
   elem = List_Item(list->item);
   List_Append(result, elem);
  }
  list = list->next;
 }
 return (result);
}



s_list* List_Filter_I(s_list const* list, t_bool (*filter)(void* item, t_uint index))
{
 s_list* result = ((void*)0);
 s_list* elem;
 t_uint i;


 if (list == ((void*)0) || filter == ((void*)0))
  return (((void*)0));

 i = 0;
 while (list)
 {
  if (filter(list->item, i))
  {
   elem = List_Item(list->item);
   List_Append(result, elem);
  }
  list = list->next;
  ++i;
 }
 return (result);
}
# 24 "./hdr/libccc/monad/list.c" 2
# 10 "./test/_foreach.c" 2


# 1 "./hdr/libccc/monad/array.c" 1


# 1 "./hdr/libccc/monad/array.h" 1
# 40 "./hdr/libccc/monad/array.h"
# 1 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 1 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdarg.h" 1 3 4
# 2 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 2 3 4
# 41 "./hdr/libccc/monad/array.h" 2




# 73 "./hdr/libccc/monad/array.h"
typedef struct array_str
{
 t_uint length;
 char** items;
} s_array_str;
# 104 "./hdr/libccc/monad/array.h"
s_array_str Array_str_New(t_uint n, ...);






void Array_str_Delete(s_array_str* array);







s_array_str Array_str_Duplicate(s_array_str const* array);





char* Array_str_Get(s_array_str const* array, t_uint index);



void Array_str_Set(s_array_str* array, t_uint index, char* item);



s_array_str* Array_str_Copy(s_array_str* dest, s_array_str const* src, t_uint n);



s_array_str Array_str_Sub(s_array_str const* array, t_uint index, t_uint n);
# 149 "./hdr/libccc/monad/array.h"
void Array_str_Append(s_array_str* array, char* item);



void Array_str_Prepend(s_array_str* array, char* item);



void Array_str_Insert(s_array_str* array, char* item, t_uint index);





void Array_str_Remove(s_array_str* array, t_uint index);




void Array_str_RemoveAll(s_array_str* array, char* target);






s_array_str Array_str_Replace(s_array_str const* array, char* old, char* new);
# 188 "./hdr/libccc/monad/array.h"
char** Array_str_Find(s_array_str const* array, char* item);



t_sint Array_str_IndexOf(s_array_str const* array, char* item);
# 204 "./hdr/libccc/monad/array.h"
t_bool Array_str_Equals (s_array_str const* array1, s_array_str const* array2);



t_bool Array_str_Equals_N (s_array_str const* array1, s_array_str const* array2, t_uint n);



t_sint Array_str_Compare (s_array_str const* array1, s_array_str const* array2, t_sint (*compare)(char* item1, char* item2));



t_sint Array_str_Compare_N (s_array_str const* array1, s_array_str const* array2, t_sint (*compare)(char* item1, char* item2), t_uint n);
# 228 "./hdr/libccc/monad/array.h"
void Array_str_Iterate (s_array_str* array, void (*f)(char* item));


void Array_str_Iterate_I (s_array_str* array, void (*f)(char* item, t_uint index));





s_array_str Array_str_Map (s_array_str const* array, char* (*map)(char* item));


s_array_str Array_str_Map_I (s_array_str const* array, char* (*map)(char* item, t_uint index));





s_array_str Array_str_Filter (s_array_str const* array, t_bool (*filter)(char* item));


s_array_str Array_str_Filter_I (s_array_str const* array, t_bool (*filter)(char* item, t_uint index));
# 258 "./hdr/libccc/monad/array.h"

# 4 "./hdr/libccc/monad/array.c" 2

# 1 "./hdr/libccc/../../src/monad/array/arrnew.c" 1

# 1 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 1 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdarg.h" 1 3 4
# 2 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 2 3 4
# 3 "./hdr/libccc/../../src/monad/array/arrnew.c" 2






s_array_str Array_str_New(t_uint n, ...)
{
 va_list array;
 char* item;
 s_array_str result;

 result.length = n;
 result.items = ((void*)0);
 if (n == 0)
  return (result);
 result.items = (char**)Memory_Alloc(sizeof(char*) * n);
 if (result.items == ((void*)0))
  return (result);
 
# 22 "./hdr/libccc/../../src/monad/array/arrnew.c" 3 4
__builtin_va_start(
# 22 "./hdr/libccc/../../src/monad/array/arrnew.c"
array
# 22 "./hdr/libccc/../../src/monad/array/arrnew.c" 3 4
,
# 22 "./hdr/libccc/../../src/monad/array/arrnew.c"
n
# 22 "./hdr/libccc/../../src/monad/array/arrnew.c" 3 4
)
# 22 "./hdr/libccc/../../src/monad/array/arrnew.c"
                  ;
 for (t_uint i = 1; i <= n; ++i)
 {
  item = 
# 25 "./hdr/libccc/../../src/monad/array/arrnew.c" 3 4
        __builtin_va_arg(
# 25 "./hdr/libccc/../../src/monad/array/arrnew.c"
        array
# 25 "./hdr/libccc/../../src/monad/array/arrnew.c" 3 4
        ,
# 25 "./hdr/libccc/../../src/monad/array/arrnew.c"
        char*
# 25 "./hdr/libccc/../../src/monad/array/arrnew.c" 3 4
        )
# 25 "./hdr/libccc/../../src/monad/array/arrnew.c"
                        ;
  result.items[i - 1] = item;
 }
 
# 28 "./hdr/libccc/../../src/monad/array/arrnew.c" 3 4
__builtin_va_end(
# 28 "./hdr/libccc/../../src/monad/array/arrnew.c"
array
# 28 "./hdr/libccc/../../src/monad/array/arrnew.c" 3 4
)
# 28 "./hdr/libccc/../../src/monad/array/arrnew.c"
             ;
 return (result);
}
# 6 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrdel.c" 1






void Array_str_Delete(s_array_str* array)
{

 if (array == ((void*)0))
  return;

 Memory_Free(array->items);
 array->items = ((void*)0);
 array->length = 0;
}
# 7 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrdup.c" 1






s_array_str Array_str_Duplicate(s_array_str const* array)
{
 s_array_str result = {0};


 if (array == ((void*)0) || array->items == ((void*)0))
  return (result);

 result.items = (char**)Memory_Duplicate(array->items, sizeof(char*) * array->length);
 if (result.items)
  result.length = array->length;
 return (result);
}
# 8 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrget.c" 1





char* Array_str_Get(s_array_str const* array, t_uint index)
{

 if (array == ((void*)0) || array->items == ((void*)0))
  return (((void*)0));

 if (index >= array->length)
  return (((void*)0));
 return (array->items[index]);
}
# 9 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrset.c" 1





void Array_str_Set(s_array_str* array, t_uint index, char* item)
{

 if (array == ((void*)0))
  return;

 if (index >= array->length)
  return;
 array->items[index] = item;
}
# 10 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrcpy.c" 1





s_array_str* Array_str_Copy(s_array_str* dest, s_array_str const* src, t_uint n)
{

 if (dest == ((void*)0) || dest->items == ((void*)0) ||
  src == ((void*)0) || src->items == ((void*)0))
  return (((void*)0));

 for (t_uint i = 0; i < n; ++i)
 {
  if (i >= dest->length || i >= src->length)
   return (dest);
  dest->items[i] = src->items[i];
 }
 return (dest);
}
# 11 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrsub.c" 1






s_array_str Array_str_Sub(s_array_str const* array, t_uint index, t_uint n)
{
 s_array_str result = {0};


 if (array == ((void*)0) || array->items == ((void*)0))
  return (result);

 if (index > array->length || index + n > array->length)
  return (result);
 result.items = (char**)Memory_Alloc(sizeof(char*) * n);
 if (result.items == ((void*)0))
  return (result);
 result.length = n;
 for (t_uint i = 0; i < n; ++i)
 {
  result.items[i] = array->items[index + i];
 }
 return (result);
}
# 12 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrappend.c" 1






void Array_str_Append(s_array_str* array, char* item)
{
 char** result;


 if (array == ((void*)0) || array->items == ((void*)0))
  return;

 result = (char**)Memory_Alloc(sizeof(char*) * (array->length + 1));
 if (result == ((void*)0))
  return;
 for (t_uint i = 0; i < array->length; ++i)
 {
  result[i] = array->items[i];
 }
 result[array->length] = item;
 Memory_Free(array->items);
 array->items = result;
 array->length += 1;
}
# 13 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrprepend.c" 1






void Array_str_Prepend(s_array_str* array, char* item)
{
 char** result;


 if (array == ((void*)0) || array->items == ((void*)0))
  return;

 result = (char**)Memory_Alloc(sizeof(char*) * (array->length + 1));
 if (result == ((void*)0))
  return;
 result[0] = item;
 for (t_uint i = 0; i < array->length; ++i)
 {
  result[i + 1] = array->items[i];
 }
 Memory_Free(array->items);
 array->items = result;
 array->length += 1;
}
# 14 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrinsert.c" 1






void Array_str_Insert(s_array_str* array, char* item, t_uint index)
{
 char** result;


 if (array == ((void*)0) || array->items == ((void*)0))
  return;

 if (array->length < index)
  return;
 result = (char**)Memory_Alloc(sizeof(char*) * (array->length + 1));
 if (result == ((void*)0))
  return;
 for (t_uint i = 0; i <= array->length; ++i)
 {
  if (i < index)
   result[i] = array->items[i];
  else if (i == index)
   result[i] = item;
  else
   result[i] = array->items[i - 1];
 }
 Memory_Free(array->items);
 array->items = result;
 array->length += 1;
}
# 15 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrremove.c" 1






void Array_str_Remove(s_array_str* array, t_uint index)
{
 char** result;


 if (array == ((void*)0) || array->items == ((void*)0))
  return;

 if (array->length == 0 ||
  array->length <= index)
  return;
 result = (char**)Memory_Alloc(sizeof(char*) * (array->length - 1));
 if (result == ((void*)0))
  return;
 for (t_uint i = 0; i < array->length - 1; ++i)
 {
  if (i < index)
   result[i] = array->items[i];
  else if (i == index)
   continue;
  else
   result[i] = array->items[i + 1];
 }
 Memory_Free(array->items);
 array->items = result;
 array->length -= 1;
}



void Array_str_RemoveAll(s_array_str* array, char* item)
{
 char** result;
 t_uint i;
 t_uint amount;


 if (array == ((void*)0) || array->items == ((void*)0))
  return;

 if (array->length == 0)
  return;
 amount = 0;
 for (i = 0; i < array->length; ++i)
 {
  if (((array->items[i]) == (item)))
  {
   ++amount;
  }
 }
 if (array->length == amount)
 {
  Memory_Free(array->items);
  array->items = ((void*)0);
  array->length = 0;
  return;
 }
 result = (char**)Memory_Alloc(sizeof(char*) * (array->length - amount));
 if (result == ((void*)0))
  return;
 amount = 0;
 for (i = 0; i < array->length; ++i)
 {
  if (((array->items[i]) == (item)))
  {
   ++amount;
   continue;
  }
  result[i] = array->items[i + amount];
 }
 Memory_Free(array->items);
 array->items = result;
 array->length = i;
}
# 16 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrreplace.c" 1






s_array_str Array_str_Replace(s_array_str const* array, char* old, char* new)
{
 s_array_str result = {0};


 if (array == ((void*)0) || array->items == ((void*)0))
  return (result);

 result.items = (char**)Memory_Duplicate(array->items, sizeof(char*) * array->length);
 if (result.items == ((void*)0))
  return (result);
 result.length = array->length;
 for (t_uint i = 0; i < result.length; ++i)
 {
  if (((result.items[i]) == (old)))
   result.items[i] = new;
 }
 return (result);
}
# 17 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrequ.c" 1





t_bool Array_str_Equals(s_array_str const* array1, s_array_str const* array2)
{

 if (array1 == array2 || (array1->length == array2->length && array1->items == array2->items))
  return ((1));
 if (array1 == ((void*)0) || array1->items == ((void*)0) ||
  array2 == ((void*)0) || array2->items == ((void*)0))
  return ((0));

 for (t_uint i = 0; (i < array1->length) && (i < array2->length); ++i)
 {
  if (!((array1->items[i]) == (array2->items[i])))
   return ((0));
 }
 return ((1));
}



t_bool Array_str_Equals_N(s_array_str const* array1, s_array_str const* array2, t_uint n)
{

 if (array1 == array2 || (array1->length == array2->length && array1->items == array2->items))
  return ((1));
 if (array1 == ((void*)0) || array1->items == ((void*)0) ||
  array2 == ((void*)0) || array2->items == ((void*)0))
  return ((0));

 for (t_uint i = 0; (i < n) && (i < array1->length) && (i < array2->length); ++i)
 {
  if (!((array1->items[i]) == (array2->items[i])))
   return ((0));
 }
 return ((1));
}
# 18 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrcmp.c" 1





t_sint Array_str_Compare(s_array_str const* array1, s_array_str const* array2, t_sint (*compare)(char* item1, char* item2))
{
 t_sint result;


 if (array1 == array2 || (array1->length == array2->length && array1->items == array2->items))
  return (0);
 if (array1 == ((void*)0) || array1->items == ((void*)0) ||
  array2 == ((void*)0) || array2->items == ((void*)0) ||
  compare == ((void*)0))
  return ((-1));

 for (t_uint i = 0; (i < array1->length) && (i < array2->length); ++i)
 {
  result = compare(array1->items[i], array2->items[i]);
  if (result)
   return (result);
 }
 return (0);
}



t_sint Array_str_Compare_N(s_array_str const* array1, s_array_str const* array2, t_sint (*compare)(char* item1, char* item2), t_uint n)
{
 t_sint result;


 if (array1 == array2 || (array1->length == array2->length && array1->items == array2->items))
  return (0);
 if (array1 == ((void*)0) || array1->items == ((void*)0) ||
  array2 == ((void*)0) || array2->items == ((void*)0) ||
  compare == ((void*)0))
  return ((-1));

 for (t_uint i = 0; (i < n) && (i < array1->length) && (i < array2->length); ++i)
 {
  result = compare(array1->items[i], array2->items[i]);
  if (result)
   return (result);
 }
 return (0);
}
# 19 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arriter.c" 1





void Array_str_Iterate(s_array_str* array, void (*f)(char* item))
{
 t_uint i;


 if (array == ((void*)0) || array->items == ((void*)0) || f == ((void*)0))
  return;

 for (i = 0; i < array->length; ++i)
 {
  f(array->items[i]);
 }
}



void Array_str_Iterate_I(s_array_str* array, void (*f)(char* item, t_uint index))
{
 t_uint i;


 if (array == ((void*)0) || array->items == ((void*)0) || f == ((void*)0))
  return;

 for (i = 0; i < array->length; ++i)
 {
  f(array->items[i], i);
 }
}
# 20 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrmap.c" 1






s_array_str Array_str_Map(s_array_str const* array, char* (*map)(char* item))
{
 s_array_str result = {0};
 t_uint i;


 if (array == ((void*)0) || array->items == ((void*)0) || map == ((void*)0))
  return (result);

 result.items = (char**)Memory_Alloc(sizeof(char*) * array->length);
 if (result.items == ((void*)0))
  return (result);
 result.length = array->length;
 for (i = 0; i < result.length; ++i)
 {
  result.items[i] = map(array->items[i]);
 }
 return (result);
}



s_array_str Array_str_Map_I(s_array_str const* array, char* (*map)(char* item, t_uint index))
{
 s_array_str result = {0};
 t_uint i;


 if (array == ((void*)0) || array->items == ((void*)0) || map == ((void*)0))
  return (result);

 result.items = (char**)Memory_Alloc(sizeof(char*) * array->length);
 if (result.items == ((void*)0))
  return (result);
 result.length = array->length;
 for (i = 0; i < result.length; ++i)
 {
  result.items[i] = map(array->items[i], i);
 }
 return (result);
}
# 21 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrfilt.c" 1






s_array_str Array_str_Filter(s_array_str const* array, t_bool (*filter)(char* item))
{
 s_array_str result = {0};
 t_bool* tmp;
 t_uint amount;
 t_uint i;


 if (array == ((void*)0) || array->items == ((void*)0) || filter == ((void*)0))
  return (result);

 tmp = (t_bool*)Memory_Alloc(sizeof(t_bool) * array->length);
 if (tmp == ((void*)0))
  return (result);
 amount = 0;
 for (i = 0; i < array->length; ++i)
 {
  tmp[i] = filter(array->items[i]);
  if (tmp[i])
   ++amount;
 }
 result.items = (char**)Memory_Alloc(sizeof(char*) * amount);
 if (result.items == ((void*)0))
  return (result);
 result.length = amount;
 amount = 0;
 for (i = 0; i < result.length; ++i)
 {
  if (tmp[i])
  {
   result.items[i] = array->items[i + amount];
  }
  else ++amount;
 }
 Memory_Free(tmp);
 return (result);
}



s_array_str Array_str_Filter_I(s_array_str const* array, t_bool (*filter)(char* item, t_uint index))
{
 s_array_str result = {0};
 t_bool* tmp;
 t_uint amount;
 t_uint i;


 if (array == ((void*)0) || array->items == ((void*)0) || filter == ((void*)0))
  return (result);

 tmp = (t_bool*)Memory_Alloc(sizeof(t_bool) * array->length);
 if (tmp == ((void*)0))
  return (result);
 amount = 0;
 for (i = 0; i < array->length; ++i)
 {
  tmp[i] = filter(array->items[i], i);
  if (tmp[i])
   ++amount;
 }
 result.items = (char**)Memory_Alloc(sizeof(char*) * amount);
 if (result.items == ((void*)0))
  return (result);
 result.length = amount;
 amount = 0;
 for (i = 0; i < result.length; ++i)
 {
  if (tmp[i])
  {
   result.items[i] = array->items[i + amount];
  }
  else ++amount;
 }
 Memory_Free(tmp);
 return (result);
}
# 22 "./hdr/libccc/monad/array.c" 2
# 13 "./test/_foreach.c" 2


# 1 "./hdr/libccc/monad/list.c" 1


# 1 "./hdr/libccc/monad/list.h" 1
# 40 "./hdr/libccc/monad/list.h"
# 1 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 1 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdarg.h" 1 3 4
# 2 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 2 3 4
# 41 "./hdr/libccc/monad/list.h" 2




# 74 "./hdr/libccc/monad/list.h"
typedef struct list_str
{

 struct list_str* next;
 char* item;
} s_list_str;
# 105 "./hdr/libccc/monad/list.h"
__attribute__((malloc))
s_list_str* List_str_Item(char* item);
# 119 "./hdr/libccc/monad/list.h"
__attribute__((malloc))
s_list_str* List_str_New(t_uint n, ...);






void List_str_Delete(s_list_str* *a_list);







__attribute__((malloc))
s_list_str* List_str_Duplicate(s_list_str const* list);
# 148 "./hdr/libccc/monad/list.h"
s_list_str* List_str_Get(s_list_str const* list, t_uint index);
# 158 "./hdr/libccc/monad/list.h"
s_list_str* List_str_Set(s_list_str* list, t_uint index, char* item);
# 168 "./hdr/libccc/monad/list.h"
s_list_str* List_str_Copy(s_list_str* dest, s_list_str const* src, t_uint n);
# 179 "./hdr/libccc/monad/list.h"
__attribute__((malloc))
s_list_str* List_str_Sub(s_list_str const* list, t_uint index, t_uint n);
# 202 "./hdr/libccc/monad/list.h"
s_list_str* List_str_Append(s_list_str* list, s_list_str* elem);
# 215 "./hdr/libccc/monad/list.h"
s_list_str* List_str_Prepend(s_list_str* list, s_list_str* elem);
# 230 "./hdr/libccc/monad/list.h"
s_list_str* List_str_Insert(s_list_str* list, char* item, t_uint index);





s_list_str* List_str_Remove(s_list_str* list, t_uint index);




s_list_str* List_str_RemoveAll(s_list_str* list, char* item);






__attribute__((malloc))
s_list_str* List_str_Replace(s_list_str const* list, char* old, char* new);
# 267 "./hdr/libccc/monad/list.h"
t_uint List_str_Length(s_list_str const* list);
# 277 "./hdr/libccc/monad/list.h"
s_list_str const* List_str_Find(s_list_str const* list, char* item);
# 287 "./hdr/libccc/monad/list.h"
t_sint List_str_IndexOf(s_list_str const* list, char* item);
# 299 "./hdr/libccc/monad/list.h"
t_bool List_str_Equals(s_list_str const* list1, s_list_str const* list2);



t_bool List_str_Equals_N(s_list_str const* list1, s_list_str const* list2, t_uint n);



t_sint List_str_Compare(s_list_str const* list1, s_list_str const* list2, t_sint (*compare)(char* item1, char* item2));



t_sint List_str_Compare_N(s_list_str const* list1, s_list_str const* list2, t_sint (*compare)(char* item1, char* item2), t_uint n);
# 327 "./hdr/libccc/monad/list.h"
void List_str_Iterate(s_list_str* list, void (*f)(char* item));


void List_str_Iterate_I(s_list_str* list, void (*f)(char* item, t_uint index));
# 340 "./hdr/libccc/monad/list.h"
__attribute__((malloc))
s_list_str* List_str_Map(s_list_str const* list, char* (*map)(char* item));


__attribute__((malloc))
s_list_str* List_str_Map_I(s_list_str const* list, char* (*map)(char* item, t_uint index));





__attribute__((malloc))
s_list_str* List_str_Filter(s_list_str const* list, t_bool (*filter)(char* item));


__attribute__((malloc))
s_list_str* List_str_Filter_I(s_list_str const* list, t_bool (*filter)(char* item, t_uint index));






# 4 "./hdr/libccc/monad/list.c" 2

# 1 "./hdr/libccc/../../src/monad/list/lstitem.c" 1






s_list_str* List_str_Item(char* item)
{
 s_list_str* result;

 result = (s_list_str*)Memory_New(sizeof(s_list_str));
 if (result == ((void*)0))
  return (((void*)0));
 result->item = item;
 return (result);
}
# 6 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstnew.c" 1

# 1 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 1 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdarg.h" 1 3 4
# 2 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 2 3 4
# 3 "./hdr/libccc/../../src/monad/list/lstnew.c" 2






s_list_str* List_str_New(t_uint n, ...)
{
 va_list list;
 char* item;
 s_list_str* result = ((void*)0);
 s_list_str* elem;
 s_list_str* new;

 if (n == 0)
  return (((void*)0));
 
# 19 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
__builtin_va_start(
# 19 "./hdr/libccc/../../src/monad/list/lstnew.c"
list
# 19 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
,
# 19 "./hdr/libccc/../../src/monad/list/lstnew.c"
n
# 19 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
)
# 19 "./hdr/libccc/../../src/monad/list/lstnew.c"
                 ;
 for (t_uint i = 1; i <= n; ++i)
 {
  item = 
# 22 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
        __builtin_va_arg(
# 22 "./hdr/libccc/../../src/monad/list/lstnew.c"
        list
# 22 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
        ,
# 22 "./hdr/libccc/../../src/monad/list/lstnew.c"
        char*
# 22 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
        )
# 22 "./hdr/libccc/../../src/monad/list/lstnew.c"
                       ;
  if (!(new = (s_list_str*)Memory_Alloc(sizeof(s_list_str))))
   break;
  new->next = ((void*)0);
  new->item = item;
  if (i == 1)
  {
   elem = new;
   result = new;
  }
  else
  {
   elem->next = new;
   elem = new;
  }
 }
 
# 38 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
__builtin_va_end(
# 38 "./hdr/libccc/../../src/monad/list/lstnew.c"
list
# 38 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
)
# 38 "./hdr/libccc/../../src/monad/list/lstnew.c"
            ;
 return (result);
}
# 7 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstdel.c" 1






void List_str_Delete(s_list_str* *a_list)
{

 s_list_str* next;
 s_list_str* i;


 if (a_list == ((void*)0))
  return ;

 i = *a_list;
 while (i)
 {

  next = i->next;
  Memory_Free(i);
  i = next;


 }
 *a_list = ((void*)0);
}
# 8 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstdup.c" 1






s_list_str* List_str_Duplicate(s_list_str const* list)
{
 s_list_str* result = ((void*)0);
 s_list_str* elem = ((void*)0);
 s_list_str* tmp;


 if (list == ((void*)0))
  return (((void*)0));

 while (list)
 {
  if (!(tmp = (s_list_str*)Memory_Duplicate(list, sizeof(s_list_str))))
   break;
  if (result == ((void*)0))
   result = tmp;
  else
  {

   elem->next = tmp;
  }
  elem = tmp;
  list = list->next;
 }
 return (result);
}
# 9 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstget.c" 1





s_list_str* List_str_Get(s_list_str const* list, t_uint index)
{

 if (list == ((void*)0))
  return (((void*)0));

 for (t_uint i = 0; i < index; ++i)
 {
  if (list->next == ((void*)0))
   return (((void*)0));
  else
   list = list->next;
 }
 return ((s_list_str*)list);
}
# 10 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstset.c" 1





s_list_str* List_str_Set(s_list_str* list, t_uint index, char* item)
{

 if (list == ((void*)0))
  return (((void*)0));

 for (t_uint i = 0; i < index; ++i)
 {
  if (list->next == ((void*)0))
   return (((void*)0));
  else
  {
   list->item = item;
   return (list);
  }
  list = list->next;
 }
 return (((void*)0));
}
# 11 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstcpy.c" 1





s_list_str* List_str_Copy(s_list_str* dest, s_list_str const* src, t_uint n)
{
 s_list_str* list;


 if (dest == ((void*)0) || src == ((void*)0))
  return (((void*)0));

 list = dest;
 while (list && n--)
 {
  list->item = src->item;
  src = src->next;
  list = list->next;
 }
 return (dest);
}
# 12 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstsub.c" 1






s_list_str* List_str_Sub(s_list_str const* list, t_uint index, t_uint n)
{
 s_list_str* result = ((void*)0);
 s_list_str* elem = ((void*)0);
 s_list_str* tmp;


 if (list == ((void*)0))
  return (((void*)0));

 if (n == 0)
  return (((void*)0));
 while (list && index--)
 {
  list = list->next;
 }
 if (list == ((void*)0))
  return (((void*)0));
 elem = result;
 list = list->next;
 while (list && n--)
 {
  if (!(tmp = (s_list_str*)Memory_Duplicate(list, sizeof(s_list_str))))
   break;
  if (result == ((void*)0))
   result = tmp;
  else
  {

   elem->next = tmp;
  }
  elem = tmp;
  list = list->next;
 }
 return (result);
}
# 13 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstappend.c" 1





s_list_str* List_str_Append(s_list_str* list, s_list_str* elem)
{
 s_list_str* i;


 if (list == ((void*)0))
  return (((void*)0));

 if (elem == ((void*)0))
  return (list);
 i = list;
 while (i->next != ((void*)0))
 {
  i = i->next;
 }

 i->next = elem;
 return (list);
}
# 14 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstprepend.c" 1





s_list_str* List_str_Prepend(s_list_str* list, s_list_str* elem)
{

 if (list == ((void*)0))
  return (((void*)0));

 if (elem == ((void*)0))
  return (list);

 elem->next = list;
 return (elem);
}
# 15 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstinsert.c" 1






s_list_str* List_str_Insert(s_list_str* list, char* item, t_uint index)
{
 s_list_str* elem;
 s_list_str* new;
 s_list_str* tmp;


 if (list == ((void*)0))
  return (((void*)0));

 if (!(new = (s_list_str*)Memory_Alloc(sizeof(s_list_str))))
  return (list);
 if (list == ((void*)0) || index == 0)
 {
  new->item = item;
  new->next = list;
  return (new);
 }
 elem = list;
 for (t_uint i = 0; i < index; ++i)
 {
  elem = elem->next;
 }

 tmp = elem->next;
 elem->next = new;
 new->next = tmp;
 return (list);
}
# 16 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstremove.c" 1






s_list_str* List_str_Remove(s_list_str* list, t_uint index)
{
 s_list_str* elem;
 s_list_str* tmp;


 if (list == ((void*)0))
  return (((void*)0));

 elem = list;
 if (index == 0)
 {
  list = list->next;
  Memory_Free(elem);
  return (list);
 }
 for (t_uint i = 0; elem && i < index; ++i)
 {
  elem = elem->next;
 }
 if (elem == ((void*)0) || elem->next == ((void*)0))
  return (list);
 tmp = elem->next;
 elem->next = tmp->next;

 Memory_Free(tmp);
 return (list);
}



s_list_str* List_str_RemoveAll(s_list_str* list, char* item)
{
 s_list_str* elem;
 s_list_str* tmp;


 if (list == ((void*)0))
  return (((void*)0));

 elem = list;
 for (t_uint i = 0; elem; ++i)
 {
  if (((elem->item) == (item)))
  {
   tmp = elem->next;
   elem->next = tmp->next;

   Memory_Free(tmp);
  }
  elem = elem->next;
 }
 return (list);
}
# 17 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstreplace.c" 1





s_list_str* List_str_Replace(s_list_str const* list, char* old, char* new)
{
 s_list_str* result = ((void*)0);
 s_list_str* elem;


 if (list == ((void*)0))
  return (((void*)0));

 while (list)
 {
  elem = List_str_Item(((list->item) == (old)) ? new : list->item);
  if (elem == ((void*)0))
   break;
  List_str_Append(result, elem);
  list = list->next;
 }
 return (result);
}
# 18 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstsize.c" 1





t_uint List_str_Size(s_list_str const* lst)
{
 t_uint result;


 if (lst == ((void*)0))
  return (0);

 result = 0;
 while (lst)
 {
  ++result;
  lst = lst->next;
 }
 return (result);
}
# 19 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstequ.c" 1





t_bool List_str_Equals(s_list_str const* list1, s_list_str const* list2)
{

 if (list1 == list2)
  return ((1));
 if (list1 == ((void*)0) || list2 == ((void*)0))
  return ((0));

 while (list1 && list2)
 {
  if (!((list1->item) == (list2->item)))
   return ((0));
  list1 = list1->next;
  list2 = list2->next;
 }
 return ((1));
}



t_bool List_str_Equals_N(s_list_str const* list1, s_list_str const* list2, t_uint n)
{

 if (list1 == list2)
  return ((1));
 if (list1 == ((void*)0) || list2 == ((void*)0))
  return ((0));

 while (list1 && list2 && n--)
 {
  if (!((list1->item) == (list2->item)))
   return ((0));
  list1 = list1->next;
  list2 = list2->next;
 }
 return ((1));
}
# 20 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstcmp.c" 1





t_sint List_str_Compare(s_list_str const* list1, s_list_str const* list2, t_sint (*compare)(char* item1, char* item2))
{
 t_sint result;


 if (list1 == list2)
  return (0);
 if (list1 == ((void*)0) || list2 == ((void*)0) || compare == ((void*)0))
  return ((-1));

 while (list1 && list2)
 {
  result = compare(list1->item, list2->item);
  if (result != 0)
   return (result);
  list1 = list1->next;
  list2 = list2->next;
 }
 return (0);
}



t_sint List_str_Compare_N(s_list_str const* list1, s_list_str const* list2, t_sint (*compare)(char* item1, char* item2), t_uint n)
{
 t_sint result;


 if (list1 == list2)
  return (0);
 if (list1 == ((void*)0) || list2 == ((void*)0) || compare == ((void*)0))
  return ((-1));

 while (list1 && list2 && n--)
 {
  result = compare(list1->item, list2->item);
  if (result != 0)
   return (result);
  list1 = list1->next;
  list2 = list2->next;
 }
 return (0);
}
# 21 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstiter.c" 1





void List_str_Iterate(s_list_str* list, void (*f)(char* item))
{

 if (list == ((void*)0) || f == ((void*)0))
  return ;

 while (list)
 {
  f(list->item);
  list = list->next;
 }
}



void List_str_Iterate_I(s_list_str* list, void (*f)(char* item, t_uint index))
{
 t_uint i;


 if (list == ((void*)0) || f == ((void*)0))
  return ;

 i = 0;
 while (list)
 {
  f(list->item, i);
  list = list->next;
  ++i;
 }
}
# 22 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstmap.c" 1





s_list_str* List_str_Map(s_list_str const* list, char* (*map)(char* item))
{
 s_list_str* result = ((void*)0);
 s_list_str* elem;


 if (list == ((void*)0) || map == ((void*)0))
  return (((void*)0));

 while (list)
 {
  elem = List_str_Item(map(list->item));
  if (elem == ((void*)0))
   break;
  List_str_Append(result, elem);
  list = list->next;
 }
 return (result);
}



s_list_str* List_str_Map_I(s_list_str const* list, char* (*map)(char* item, t_uint index))
{
 s_list_str* result = ((void*)0);
 s_list_str* elem;
 t_uint i;


 if (list == ((void*)0) || map == ((void*)0))
  return (((void*)0));

 i = 0;
 while (list)
 {
  elem = List_str_Item(map(list->item, i));
  if (elem == ((void*)0))
   break;
  List_str_Append(result, elem);
  list = list->next;
  ++i;
 }
 return (result);
}
# 23 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstfilt.c" 1





s_list_str* List_str_Filter(s_list_str const* list, t_bool (*filter)(char* item))
{
 s_list_str* result = ((void*)0);
 s_list_str* elem;


 if (list == ((void*)0) || filter == ((void*)0))
  return (((void*)0));

 while (list)
 {
  if (filter(list->item))
  {
   elem = List_str_Item(list->item);
   List_str_Append(result, elem);
  }
  list = list->next;
 }
 return (result);
}



s_list_str* List_str_Filter_I(s_list_str const* list, t_bool (*filter)(char* item, t_uint index))
{
 s_list_str* result = ((void*)0);
 s_list_str* elem;
 t_uint i;


 if (list == ((void*)0) || filter == ((void*)0))
  return (((void*)0));

 i = 0;
 while (list)
 {
  if (filter(list->item, i))
  {
   elem = List_str_Item(list->item);
   List_str_Append(result, elem);
  }
  list = list->next;
  ++i;
 }
 return (result);
}
# 24 "./hdr/libccc/monad/list.c" 2
# 16 "./test/_foreach.c" 2
# 24 "./test/_foreach.c"
# 1 "./hdr/libccc/monad/array.c" 1


# 1 "./hdr/libccc/monad/array.h" 1
# 40 "./hdr/libccc/monad/array.h"
# 1 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 1 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdarg.h" 1 3 4
# 2 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 2 3 4
# 41 "./hdr/libccc/monad/array.h" 2




# 73 "./hdr/libccc/monad/array.h"
typedef struct array_int
{
 t_uint length;
 int* items;
} s_array_int;
# 104 "./hdr/libccc/monad/array.h"
s_array_int Array_int_New(t_uint n, ...);






void Array_int_Delete(s_array_int* array);







s_array_int Array_int_Duplicate(s_array_int const* array);





int Array_int_Get(s_array_int const* array, t_uint index);



void Array_int_Set(s_array_int* array, t_uint index, int item);



s_array_int* Array_int_Copy(s_array_int* dest, s_array_int const* src, t_uint n);



s_array_int Array_int_Sub(s_array_int const* array, t_uint index, t_uint n);
# 149 "./hdr/libccc/monad/array.h"
void Array_int_Append(s_array_int* array, int item);



void Array_int_Prepend(s_array_int* array, int item);



void Array_int_Insert(s_array_int* array, int item, t_uint index);





void Array_int_Remove(s_array_int* array, t_uint index);




void Array_int_RemoveAll(s_array_int* array, int target);






s_array_int Array_int_Replace(s_array_int const* array, int old, int new);
# 188 "./hdr/libccc/monad/array.h"
int* Array_int_Find(s_array_int const* array, int item);



t_sint Array_int_IndexOf(s_array_int const* array, int item);
# 204 "./hdr/libccc/monad/array.h"
t_bool Array_int_Equals (s_array_int const* array1, s_array_int const* array2);



t_bool Array_int_Equals_N (s_array_int const* array1, s_array_int const* array2, t_uint n);



t_sint Array_int_Compare (s_array_int const* array1, s_array_int const* array2, t_sint (*compare)(int item1, int item2));



t_sint Array_int_Compare_N (s_array_int const* array1, s_array_int const* array2, t_sint (*compare)(int item1, int item2), t_uint n);
# 228 "./hdr/libccc/monad/array.h"
void Array_int_Iterate (s_array_int* array, void (*f)(int item));


void Array_int_Iterate_I (s_array_int* array, void (*f)(int item, t_uint index));





s_array_int Array_int_Map (s_array_int const* array, int (*map)(int item));


s_array_int Array_int_Map_I (s_array_int const* array, int (*map)(int item, t_uint index));





s_array_int Array_int_Filter (s_array_int const* array, t_bool (*filter)(int item));


s_array_int Array_int_Filter_I (s_array_int const* array, t_bool (*filter)(int item, t_uint index));
# 258 "./hdr/libccc/monad/array.h"

# 4 "./hdr/libccc/monad/array.c" 2

# 1 "./hdr/libccc/../../src/monad/array/arrnew.c" 1

# 1 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 1 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdarg.h" 1 3 4
# 2 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 2 3 4
# 3 "./hdr/libccc/../../src/monad/array/arrnew.c" 2






s_array_int Array_int_New(t_uint n, ...)
{
 va_list array;
 int item;
 s_array_int result;

 result.length = n;
 result.items = ((void*)0);
 if (n == 0)
  return (result);
 result.items = (int*)Memory_Alloc(sizeof(int) * n);
 if (result.items == ((void*)0))
  return (result);
 
# 22 "./hdr/libccc/../../src/monad/array/arrnew.c" 3 4
__builtin_va_start(
# 22 "./hdr/libccc/../../src/monad/array/arrnew.c"
array
# 22 "./hdr/libccc/../../src/monad/array/arrnew.c" 3 4
,
# 22 "./hdr/libccc/../../src/monad/array/arrnew.c"
n
# 22 "./hdr/libccc/../../src/monad/array/arrnew.c" 3 4
)
# 22 "./hdr/libccc/../../src/monad/array/arrnew.c"
                  ;
 for (t_uint i = 1; i <= n; ++i)
 {
  item = 
# 25 "./hdr/libccc/../../src/monad/array/arrnew.c" 3 4
        __builtin_va_arg(
# 25 "./hdr/libccc/../../src/monad/array/arrnew.c"
        array
# 25 "./hdr/libccc/../../src/monad/array/arrnew.c" 3 4
        ,
# 25 "./hdr/libccc/../../src/monad/array/arrnew.c"
        int
# 25 "./hdr/libccc/../../src/monad/array/arrnew.c" 3 4
        )
# 25 "./hdr/libccc/../../src/monad/array/arrnew.c"
                        ;
  result.items[i - 1] = item;
 }
 
# 28 "./hdr/libccc/../../src/monad/array/arrnew.c" 3 4
__builtin_va_end(
# 28 "./hdr/libccc/../../src/monad/array/arrnew.c"
array
# 28 "./hdr/libccc/../../src/monad/array/arrnew.c" 3 4
)
# 28 "./hdr/libccc/../../src/monad/array/arrnew.c"
             ;
 return (result);
}
# 6 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrdel.c" 1






void Array_int_Delete(s_array_int* array)
{

 if (array == ((void*)0))
  return;

 Memory_Free(array->items);
 array->items = ((void*)0);
 array->length = 0;
}
# 7 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrdup.c" 1






s_array_int Array_int_Duplicate(s_array_int const* array)
{
 s_array_int result = {0};


 if (array == ((void*)0) || array->items == ((void*)0))
  return (result);

 result.items = (int*)Memory_Duplicate(array->items, sizeof(int) * array->length);
 if (result.items)
  result.length = array->length;
 return (result);
}
# 8 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrget.c" 1





int Array_int_Get(s_array_int const* array, t_uint index)
{

 if (array == ((void*)0) || array->items == ((void*)0))
  return (0);

 if (index >= array->length)
  return (0);
 return (array->items[index]);
}
# 9 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrset.c" 1





void Array_int_Set(s_array_int* array, t_uint index, int item)
{

 if (array == ((void*)0))
  return;

 if (index >= array->length)
  return;
 array->items[index] = item;
}
# 10 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrcpy.c" 1





s_array_int* Array_int_Copy(s_array_int* dest, s_array_int const* src, t_uint n)
{

 if (dest == ((void*)0) || dest->items == ((void*)0) ||
  src == ((void*)0) || src->items == ((void*)0))
  return (((void*)0));

 for (t_uint i = 0; i < n; ++i)
 {
  if (i >= dest->length || i >= src->length)
   return (dest);
  dest->items[i] = src->items[i];
 }
 return (dest);
}
# 11 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrsub.c" 1






s_array_int Array_int_Sub(s_array_int const* array, t_uint index, t_uint n)
{
 s_array_int result = {0};


 if (array == ((void*)0) || array->items == ((void*)0))
  return (result);

 if (index > array->length || index + n > array->length)
  return (result);
 result.items = (int*)Memory_Alloc(sizeof(int) * n);
 if (result.items == ((void*)0))
  return (result);
 result.length = n;
 for (t_uint i = 0; i < n; ++i)
 {
  result.items[i] = array->items[index + i];
 }
 return (result);
}
# 12 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrappend.c" 1






void Array_int_Append(s_array_int* array, int item)
{
 int* result;


 if (array == ((void*)0) || array->items == ((void*)0))
  return;

 result = (int*)Memory_Alloc(sizeof(int) * (array->length + 1));
 if (result == ((void*)0))
  return;
 for (t_uint i = 0; i < array->length; ++i)
 {
  result[i] = array->items[i];
 }
 result[array->length] = item;
 Memory_Free(array->items);
 array->items = result;
 array->length += 1;
}
# 13 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrprepend.c" 1






void Array_int_Prepend(s_array_int* array, int item)
{
 int* result;


 if (array == ((void*)0) || array->items == ((void*)0))
  return;

 result = (int*)Memory_Alloc(sizeof(int) * (array->length + 1));
 if (result == ((void*)0))
  return;
 result[0] = item;
 for (t_uint i = 0; i < array->length; ++i)
 {
  result[i + 1] = array->items[i];
 }
 Memory_Free(array->items);
 array->items = result;
 array->length += 1;
}
# 14 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrinsert.c" 1






void Array_int_Insert(s_array_int* array, int item, t_uint index)
{
 int* result;


 if (array == ((void*)0) || array->items == ((void*)0))
  return;

 if (array->length < index)
  return;
 result = (int*)Memory_Alloc(sizeof(int) * (array->length + 1));
 if (result == ((void*)0))
  return;
 for (t_uint i = 0; i <= array->length; ++i)
 {
  if (i < index)
   result[i] = array->items[i];
  else if (i == index)
   result[i] = item;
  else
   result[i] = array->items[i - 1];
 }
 Memory_Free(array->items);
 array->items = result;
 array->length += 1;
}
# 15 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrremove.c" 1






void Array_int_Remove(s_array_int* array, t_uint index)
{
 int* result;


 if (array == ((void*)0) || array->items == ((void*)0))
  return;

 if (array->length == 0 ||
  array->length <= index)
  return;
 result = (int*)Memory_Alloc(sizeof(int) * (array->length - 1));
 if (result == ((void*)0))
  return;
 for (t_uint i = 0; i < array->length - 1; ++i)
 {
  if (i < index)
   result[i] = array->items[i];
  else if (i == index)
   continue;
  else
   result[i] = array->items[i + 1];
 }
 Memory_Free(array->items);
 array->items = result;
 array->length -= 1;
}



void Array_int_RemoveAll(s_array_int* array, int item)
{
 int* result;
 t_uint i;
 t_uint amount;


 if (array == ((void*)0) || array->items == ((void*)0))
  return;

 if (array->length == 0)
  return;
 amount = 0;
 for (i = 0; i < array->length; ++i)
 {
  if (((array->items[i]) == (item)))
  {
   ++amount;
  }
 }
 if (array->length == amount)
 {
  Memory_Free(array->items);
  array->items = ((void*)0);
  array->length = 0;
  return;
 }
 result = (int*)Memory_Alloc(sizeof(int) * (array->length - amount));
 if (result == ((void*)0))
  return;
 amount = 0;
 for (i = 0; i < array->length; ++i)
 {
  if (((array->items[i]) == (item)))
  {
   ++amount;
   continue;
  }
  result[i] = array->items[i + amount];
 }
 Memory_Free(array->items);
 array->items = result;
 array->length = i;
}
# 16 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrreplace.c" 1






s_array_int Array_int_Replace(s_array_int const* array, int old, int new)
{
 s_array_int result = {0};


 if (array == ((void*)0) || array->items == ((void*)0))
  return (result);

 result.items = (int*)Memory_Duplicate(array->items, sizeof(int) * array->length);
 if (result.items == ((void*)0))
  return (result);
 result.length = array->length;
 for (t_uint i = 0; i < result.length; ++i)
 {
  if (((result.items[i]) == (old)))
   result.items[i] = new;
 }
 return (result);
}
# 17 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrequ.c" 1





t_bool Array_int_Equals(s_array_int const* array1, s_array_int const* array2)
{

 if (array1 == array2 || (array1->length == array2->length && array1->items == array2->items))
  return ((1));
 if (array1 == ((void*)0) || array1->items == ((void*)0) ||
  array2 == ((void*)0) || array2->items == ((void*)0))
  return ((0));

 for (t_uint i = 0; (i < array1->length) && (i < array2->length); ++i)
 {
  if (!((array1->items[i]) == (array2->items[i])))
   return ((0));
 }
 return ((1));
}



t_bool Array_int_Equals_N(s_array_int const* array1, s_array_int const* array2, t_uint n)
{

 if (array1 == array2 || (array1->length == array2->length && array1->items == array2->items))
  return ((1));
 if (array1 == ((void*)0) || array1->items == ((void*)0) ||
  array2 == ((void*)0) || array2->items == ((void*)0))
  return ((0));

 for (t_uint i = 0; (i < n) && (i < array1->length) && (i < array2->length); ++i)
 {
  if (!((array1->items[i]) == (array2->items[i])))
   return ((0));
 }
 return ((1));
}
# 18 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrcmp.c" 1





t_sint Array_int_Compare(s_array_int const* array1, s_array_int const* array2, t_sint (*compare)(int item1, int item2))
{
 t_sint result;


 if (array1 == array2 || (array1->length == array2->length && array1->items == array2->items))
  return (0);
 if (array1 == ((void*)0) || array1->items == ((void*)0) ||
  array2 == ((void*)0) || array2->items == ((void*)0) ||
  compare == ((void*)0))
  return ((-1));

 for (t_uint i = 0; (i < array1->length) && (i < array2->length); ++i)
 {
  result = compare(array1->items[i], array2->items[i]);
  if (result)
   return (result);
 }
 return (0);
}



t_sint Array_int_Compare_N(s_array_int const* array1, s_array_int const* array2, t_sint (*compare)(int item1, int item2), t_uint n)
{
 t_sint result;


 if (array1 == array2 || (array1->length == array2->length && array1->items == array2->items))
  return (0);
 if (array1 == ((void*)0) || array1->items == ((void*)0) ||
  array2 == ((void*)0) || array2->items == ((void*)0) ||
  compare == ((void*)0))
  return ((-1));

 for (t_uint i = 0; (i < n) && (i < array1->length) && (i < array2->length); ++i)
 {
  result = compare(array1->items[i], array2->items[i]);
  if (result)
   return (result);
 }
 return (0);
}
# 19 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arriter.c" 1





void Array_int_Iterate(s_array_int* array, void (*f)(int item))
{
 t_uint i;


 if (array == ((void*)0) || array->items == ((void*)0) || f == ((void*)0))
  return;

 for (i = 0; i < array->length; ++i)
 {
  f(array->items[i]);
 }
}



void Array_int_Iterate_I(s_array_int* array, void (*f)(int item, t_uint index))
{
 t_uint i;


 if (array == ((void*)0) || array->items == ((void*)0) || f == ((void*)0))
  return;

 for (i = 0; i < array->length; ++i)
 {
  f(array->items[i], i);
 }
}
# 20 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrmap.c" 1






s_array_int Array_int_Map(s_array_int const* array, int (*map)(int item))
{
 s_array_int result = {0};
 t_uint i;


 if (array == ((void*)0) || array->items == ((void*)0) || map == ((void*)0))
  return (result);

 result.items = (int*)Memory_Alloc(sizeof(int) * array->length);
 if (result.items == ((void*)0))
  return (result);
 result.length = array->length;
 for (i = 0; i < result.length; ++i)
 {
  result.items[i] = map(array->items[i]);
 }
 return (result);
}



s_array_int Array_int_Map_I(s_array_int const* array, int (*map)(int item, t_uint index))
{
 s_array_int result = {0};
 t_uint i;


 if (array == ((void*)0) || array->items == ((void*)0) || map == ((void*)0))
  return (result);

 result.items = (int*)Memory_Alloc(sizeof(int) * array->length);
 if (result.items == ((void*)0))
  return (result);
 result.length = array->length;
 for (i = 0; i < result.length; ++i)
 {
  result.items[i] = map(array->items[i], i);
 }
 return (result);
}
# 21 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrfilt.c" 1






s_array_int Array_int_Filter(s_array_int const* array, t_bool (*filter)(int item))
{
 s_array_int result = {0};
 t_bool* tmp;
 t_uint amount;
 t_uint i;


 if (array == ((void*)0) || array->items == ((void*)0) || filter == ((void*)0))
  return (result);

 tmp = (t_bool*)Memory_Alloc(sizeof(t_bool) * array->length);
 if (tmp == ((void*)0))
  return (result);
 amount = 0;
 for (i = 0; i < array->length; ++i)
 {
  tmp[i] = filter(array->items[i]);
  if (tmp[i])
   ++amount;
 }
 result.items = (int*)Memory_Alloc(sizeof(int) * amount);
 if (result.items == ((void*)0))
  return (result);
 result.length = amount;
 amount = 0;
 for (i = 0; i < result.length; ++i)
 {
  if (tmp[i])
  {
   result.items[i] = array->items[i + amount];
  }
  else ++amount;
 }
 Memory_Free(tmp);
 return (result);
}



s_array_int Array_int_Filter_I(s_array_int const* array, t_bool (*filter)(int item, t_uint index))
{
 s_array_int result = {0};
 t_bool* tmp;
 t_uint amount;
 t_uint i;


 if (array == ((void*)0) || array->items == ((void*)0) || filter == ((void*)0))
  return (result);

 tmp = (t_bool*)Memory_Alloc(sizeof(t_bool) * array->length);
 if (tmp == ((void*)0))
  return (result);
 amount = 0;
 for (i = 0; i < array->length; ++i)
 {
  tmp[i] = filter(array->items[i], i);
  if (tmp[i])
   ++amount;
 }
 result.items = (int*)Memory_Alloc(sizeof(int) * amount);
 if (result.items == ((void*)0))
  return (result);
 result.length = amount;
 amount = 0;
 for (i = 0; i < result.length; ++i)
 {
  if (tmp[i])
  {
   result.items[i] = array->items[i + amount];
  }
  else ++amount;
 }
 Memory_Free(tmp);
 return (result);
}
# 22 "./hdr/libccc/monad/array.c" 2
# 25 "./test/_foreach.c" 2




# 1 "./hdr/libccc/monad/array.c" 1


# 1 "./hdr/libccc/monad/array.h" 1
# 40 "./hdr/libccc/monad/array.h"
# 1 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 1 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdarg.h" 1 3 4
# 2 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 2 3 4
# 41 "./hdr/libccc/monad/array.h" 2




# 73 "./hdr/libccc/monad/array.h"
typedef struct array_array_int
{
 t_uint length;
 s_array_int* items;
} s_array_array_int;
# 104 "./hdr/libccc/monad/array.h"
s_array_array_int Array_array_int_New(t_uint n, ...);






void Array_array_int_Delete(s_array_array_int* array);







s_array_array_int Array_array_int_Duplicate(s_array_array_int const* array);





s_array_int Array_array_int_Get(s_array_array_int const* array, t_uint index);



void Array_array_int_Set(s_array_array_int* array, t_uint index, s_array_int item);



s_array_array_int* Array_array_int_Copy(s_array_array_int* dest, s_array_array_int const* src, t_uint n);



s_array_array_int Array_array_int_Sub(s_array_array_int const* array, t_uint index, t_uint n);
# 149 "./hdr/libccc/monad/array.h"
void Array_array_int_Append(s_array_array_int* array, s_array_int item);



void Array_array_int_Prepend(s_array_array_int* array, s_array_int item);



void Array_array_int_Insert(s_array_array_int* array, s_array_int item, t_uint index);





void Array_array_int_Remove(s_array_array_int* array, t_uint index);




void Array_array_int_RemoveAll(s_array_array_int* array, s_array_int target);






s_array_array_int Array_array_int_Replace(s_array_array_int const* array, s_array_int old, s_array_int new);
# 188 "./hdr/libccc/monad/array.h"
s_array_int* Array_array_int_Find(s_array_array_int const* array, s_array_int item);



t_sint Array_array_int_IndexOf(s_array_array_int const* array, s_array_int item);
# 204 "./hdr/libccc/monad/array.h"
t_bool Array_array_int_Equals (s_array_array_int const* array1, s_array_array_int const* array2);



t_bool Array_array_int_Equals_N (s_array_array_int const* array1, s_array_array_int const* array2, t_uint n);



t_sint Array_array_int_Compare (s_array_array_int const* array1, s_array_array_int const* array2, t_sint (*compare)(s_array_int item1, s_array_int item2));



t_sint Array_array_int_Compare_N (s_array_array_int const* array1, s_array_array_int const* array2, t_sint (*compare)(s_array_int item1, s_array_int item2), t_uint n);
# 228 "./hdr/libccc/monad/array.h"
void Array_array_int_Iterate (s_array_array_int* array, void (*f)(s_array_int item));


void Array_array_int_Iterate_I (s_array_array_int* array, void (*f)(s_array_int item, t_uint index));





s_array_array_int Array_array_int_Map (s_array_array_int const* array, s_array_int (*map)(s_array_int item));


s_array_array_int Array_array_int_Map_I (s_array_array_int const* array, s_array_int (*map)(s_array_int item, t_uint index));





s_array_array_int Array_array_int_Filter (s_array_array_int const* array, t_bool (*filter)(s_array_int item));


s_array_array_int Array_array_int_Filter_I (s_array_array_int const* array, t_bool (*filter)(s_array_int item, t_uint index));
# 258 "./hdr/libccc/monad/array.h"

# 4 "./hdr/libccc/monad/array.c" 2

# 1 "./hdr/libccc/../../src/monad/array/arrnew.c" 1

# 1 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 1 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdarg.h" 1 3 4
# 2 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 2 3 4
# 3 "./hdr/libccc/../../src/monad/array/arrnew.c" 2






s_array_array_int Array_array_int_New(t_uint n, ...)
{
 va_list array;
 s_array_int item;
 s_array_array_int result;

 result.length = n;
 result.items = ((void*)0);
 if (n == 0)
  return (result);
 result.items = (s_array_int*)Memory_Alloc(sizeof(s_array_int) * n);
 if (result.items == ((void*)0))
  return (result);
 
# 22 "./hdr/libccc/../../src/monad/array/arrnew.c" 3 4
__builtin_va_start(
# 22 "./hdr/libccc/../../src/monad/array/arrnew.c"
array
# 22 "./hdr/libccc/../../src/monad/array/arrnew.c" 3 4
,
# 22 "./hdr/libccc/../../src/monad/array/arrnew.c"
n
# 22 "./hdr/libccc/../../src/monad/array/arrnew.c" 3 4
)
# 22 "./hdr/libccc/../../src/monad/array/arrnew.c"
                  ;
 for (t_uint i = 1; i <= n; ++i)
 {
  item = 
# 25 "./hdr/libccc/../../src/monad/array/arrnew.c" 3 4
        __builtin_va_arg(
# 25 "./hdr/libccc/../../src/monad/array/arrnew.c"
        array
# 25 "./hdr/libccc/../../src/monad/array/arrnew.c" 3 4
        ,
# 25 "./hdr/libccc/../../src/monad/array/arrnew.c"
        s_array_int
# 25 "./hdr/libccc/../../src/monad/array/arrnew.c" 3 4
        )
# 25 "./hdr/libccc/../../src/monad/array/arrnew.c"
                        ;
  result.items[i - 1] = item;
 }
 
# 28 "./hdr/libccc/../../src/monad/array/arrnew.c" 3 4
__builtin_va_end(
# 28 "./hdr/libccc/../../src/monad/array/arrnew.c"
array
# 28 "./hdr/libccc/../../src/monad/array/arrnew.c" 3 4
)
# 28 "./hdr/libccc/../../src/monad/array/arrnew.c"
             ;
 return (result);
}
# 6 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrdel.c" 1






void Array_array_int_Delete(s_array_array_int* array)
{

 if (array == ((void*)0))
  return;

 Memory_Free(array->items);
 array->items = ((void*)0);
 array->length = 0;
}
# 7 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrdup.c" 1






s_array_array_int Array_array_int_Duplicate(s_array_array_int const* array)
{
 s_array_array_int result = {0};


 if (array == ((void*)0) || array->items == ((void*)0))
  return (result);

 result.items = (s_array_int*)Memory_Duplicate(array->items, sizeof(s_array_int) * array->length);
 if (result.items)
  result.length = array->length;
 return (result);
}
# 8 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrget.c" 1





s_array_int Array_array_int_Get(s_array_array_int const* array, t_uint index)
{

 if (array == ((void*)0) || array->items == ((void*)0))
  return ((s_array_int){ .length = 0, .items = ((void*)0) });

 if (index >= array->length)
  return ((s_array_int){ .length = 0, .items = ((void*)0) });
 return (array->items[index]);
}
# 9 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrset.c" 1





void Array_array_int_Set(s_array_array_int* array, t_uint index, s_array_int item)
{

 if (array == ((void*)0))
  return;

 if (index >= array->length)
  return;
 array->items[index] = item;
}
# 10 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrcpy.c" 1





s_array_array_int* Array_array_int_Copy(s_array_array_int* dest, s_array_array_int const* src, t_uint n)
{

 if (dest == ((void*)0) || dest->items == ((void*)0) ||
  src == ((void*)0) || src->items == ((void*)0))
  return (((void*)0));

 for (t_uint i = 0; i < n; ++i)
 {
  if (i >= dest->length || i >= src->length)
   return (dest);
  dest->items[i] = src->items[i];
 }
 return (dest);
}
# 11 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrsub.c" 1






s_array_array_int Array_array_int_Sub(s_array_array_int const* array, t_uint index, t_uint n)
{
 s_array_array_int result = {0};


 if (array == ((void*)0) || array->items == ((void*)0))
  return (result);

 if (index > array->length || index + n > array->length)
  return (result);
 result.items = (s_array_int*)Memory_Alloc(sizeof(s_array_int) * n);
 if (result.items == ((void*)0))
  return (result);
 result.length = n;
 for (t_uint i = 0; i < n; ++i)
 {
  result.items[i] = array->items[index + i];
 }
 return (result);
}
# 12 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrappend.c" 1






void Array_array_int_Append(s_array_array_int* array, s_array_int item)
{
 s_array_int* result;


 if (array == ((void*)0) || array->items == ((void*)0))
  return;

 result = (s_array_int*)Memory_Alloc(sizeof(s_array_int) * (array->length + 1));
 if (result == ((void*)0))
  return;
 for (t_uint i = 0; i < array->length; ++i)
 {
  result[i] = array->items[i];
 }
 result[array->length] = item;
 Memory_Free(array->items);
 array->items = result;
 array->length += 1;
}
# 13 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrprepend.c" 1






void Array_array_int_Prepend(s_array_array_int* array, s_array_int item)
{
 s_array_int* result;


 if (array == ((void*)0) || array->items == ((void*)0))
  return;

 result = (s_array_int*)Memory_Alloc(sizeof(s_array_int) * (array->length + 1));
 if (result == ((void*)0))
  return;
 result[0] = item;
 for (t_uint i = 0; i < array->length; ++i)
 {
  result[i + 1] = array->items[i];
 }
 Memory_Free(array->items);
 array->items = result;
 array->length += 1;
}
# 14 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrinsert.c" 1






void Array_array_int_Insert(s_array_array_int* array, s_array_int item, t_uint index)
{
 s_array_int* result;


 if (array == ((void*)0) || array->items == ((void*)0))
  return;

 if (array->length < index)
  return;
 result = (s_array_int*)Memory_Alloc(sizeof(s_array_int) * (array->length + 1));
 if (result == ((void*)0))
  return;
 for (t_uint i = 0; i <= array->length; ++i)
 {
  if (i < index)
   result[i] = array->items[i];
  else if (i == index)
   result[i] = item;
  else
   result[i] = array->items[i - 1];
 }
 Memory_Free(array->items);
 array->items = result;
 array->length += 1;
}
# 15 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrremove.c" 1






void Array_array_int_Remove(s_array_array_int* array, t_uint index)
{
 s_array_int* result;


 if (array == ((void*)0) || array->items == ((void*)0))
  return;

 if (array->length == 0 ||
  array->length <= index)
  return;
 result = (s_array_int*)Memory_Alloc(sizeof(s_array_int) * (array->length - 1));
 if (result == ((void*)0))
  return;
 for (t_uint i = 0; i < array->length - 1; ++i)
 {
  if (i < index)
   result[i] = array->items[i];
  else if (i == index)
   continue;
  else
   result[i] = array->items[i + 1];
 }
 Memory_Free(array->items);
 array->items = result;
 array->length -= 1;
}



void Array_array_int_RemoveAll(s_array_array_int* array, s_array_int item)
{
 s_array_int* result;
 t_uint i;
 t_uint amount;


 if (array == ((void*)0) || array->items == ((void*)0))
  return;

 if (array->length == 0)
  return;
 amount = 0;
 for (i = 0; i < array->length; ++i)
 {
  if (((array->items[i]).length == (item).length && (array->items[i]).items == (item).items))
  {
   ++amount;
  }
 }
 if (array->length == amount)
 {
  Memory_Free(array->items);
  array->items = ((void*)0);
  array->length = 0;
  return;
 }
 result = (s_array_int*)Memory_Alloc(sizeof(s_array_int) * (array->length - amount));
 if (result == ((void*)0))
  return;
 amount = 0;
 for (i = 0; i < array->length; ++i)
 {
  if (((array->items[i]).length == (item).length && (array->items[i]).items == (item).items))
  {
   ++amount;
   continue;
  }
  result[i] = array->items[i + amount];
 }
 Memory_Free(array->items);
 array->items = result;
 array->length = i;
}
# 16 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrreplace.c" 1






s_array_array_int Array_array_int_Replace(s_array_array_int const* array, s_array_int old, s_array_int new)
{
 s_array_array_int result = {0};


 if (array == ((void*)0) || array->items == ((void*)0))
  return (result);

 result.items = (s_array_int*)Memory_Duplicate(array->items, sizeof(s_array_int) * array->length);
 if (result.items == ((void*)0))
  return (result);
 result.length = array->length;
 for (t_uint i = 0; i < result.length; ++i)
 {
  if (((result.items[i]).length == (old).length && (result.items[i]).items == (old).items))
   result.items[i] = new;
 }
 return (result);
}
# 17 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrequ.c" 1





t_bool Array_array_int_Equals(s_array_array_int const* array1, s_array_array_int const* array2)
{

 if (array1 == array2 || (array1->length == array2->length && array1->items == array2->items))
  return ((1));
 if (array1 == ((void*)0) || array1->items == ((void*)0) ||
  array2 == ((void*)0) || array2->items == ((void*)0))
  return ((0));

 for (t_uint i = 0; (i < array1->length) && (i < array2->length); ++i)
 {
  if (!((array1->items[i]).length == (array2->items[i]).length && (array1->items[i]).items == (array2->items[i]).items))
   return ((0));
 }
 return ((1));
}



t_bool Array_array_int_Equals_N(s_array_array_int const* array1, s_array_array_int const* array2, t_uint n)
{

 if (array1 == array2 || (array1->length == array2->length && array1->items == array2->items))
  return ((1));
 if (array1 == ((void*)0) || array1->items == ((void*)0) ||
  array2 == ((void*)0) || array2->items == ((void*)0))
  return ((0));

 for (t_uint i = 0; (i < n) && (i < array1->length) && (i < array2->length); ++i)
 {
  if (!((array1->items[i]).length == (array2->items[i]).length && (array1->items[i]).items == (array2->items[i]).items))
   return ((0));
 }
 return ((1));
}
# 18 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrcmp.c" 1





t_sint Array_array_int_Compare(s_array_array_int const* array1, s_array_array_int const* array2, t_sint (*compare)(s_array_int item1, s_array_int item2))
{
 t_sint result;


 if (array1 == array2 || (array1->length == array2->length && array1->items == array2->items))
  return (0);
 if (array1 == ((void*)0) || array1->items == ((void*)0) ||
  array2 == ((void*)0) || array2->items == ((void*)0) ||
  compare == ((void*)0))
  return ((-1));

 for (t_uint i = 0; (i < array1->length) && (i < array2->length); ++i)
 {
  result = compare(array1->items[i], array2->items[i]);
  if (result)
   return (result);
 }
 return (0);
}



t_sint Array_array_int_Compare_N(s_array_array_int const* array1, s_array_array_int const* array2, t_sint (*compare)(s_array_int item1, s_array_int item2), t_uint n)
{
 t_sint result;


 if (array1 == array2 || (array1->length == array2->length && array1->items == array2->items))
  return (0);
 if (array1 == ((void*)0) || array1->items == ((void*)0) ||
  array2 == ((void*)0) || array2->items == ((void*)0) ||
  compare == ((void*)0))
  return ((-1));

 for (t_uint i = 0; (i < n) && (i < array1->length) && (i < array2->length); ++i)
 {
  result = compare(array1->items[i], array2->items[i]);
  if (result)
   return (result);
 }
 return (0);
}
# 19 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arriter.c" 1





void Array_array_int_Iterate(s_array_array_int* array, void (*f)(s_array_int item))
{
 t_uint i;


 if (array == ((void*)0) || array->items == ((void*)0) || f == ((void*)0))
  return;

 for (i = 0; i < array->length; ++i)
 {
  f(array->items[i]);
 }
}



void Array_array_int_Iterate_I(s_array_array_int* array, void (*f)(s_array_int item, t_uint index))
{
 t_uint i;


 if (array == ((void*)0) || array->items == ((void*)0) || f == ((void*)0))
  return;

 for (i = 0; i < array->length; ++i)
 {
  f(array->items[i], i);
 }
}
# 20 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrmap.c" 1






s_array_array_int Array_array_int_Map(s_array_array_int const* array, s_array_int (*map)(s_array_int item))
{
 s_array_array_int result = {0};
 t_uint i;


 if (array == ((void*)0) || array->items == ((void*)0) || map == ((void*)0))
  return (result);

 result.items = (s_array_int*)Memory_Alloc(sizeof(s_array_int) * array->length);
 if (result.items == ((void*)0))
  return (result);
 result.length = array->length;
 for (i = 0; i < result.length; ++i)
 {
  result.items[i] = map(array->items[i]);
 }
 return (result);
}



s_array_array_int Array_array_int_Map_I(s_array_array_int const* array, s_array_int (*map)(s_array_int item, t_uint index))
{
 s_array_array_int result = {0};
 t_uint i;


 if (array == ((void*)0) || array->items == ((void*)0) || map == ((void*)0))
  return (result);

 result.items = (s_array_int*)Memory_Alloc(sizeof(s_array_int) * array->length);
 if (result.items == ((void*)0))
  return (result);
 result.length = array->length;
 for (i = 0; i < result.length; ++i)
 {
  result.items[i] = map(array->items[i], i);
 }
 return (result);
}
# 21 "./hdr/libccc/monad/array.c" 2
# 1 "./hdr/libccc/../../src/monad/array/arrfilt.c" 1






s_array_array_int Array_array_int_Filter(s_array_array_int const* array, t_bool (*filter)(s_array_int item))
{
 s_array_array_int result = {0};
 t_bool* tmp;
 t_uint amount;
 t_uint i;


 if (array == ((void*)0) || array->items == ((void*)0) || filter == ((void*)0))
  return (result);

 tmp = (t_bool*)Memory_Alloc(sizeof(t_bool) * array->length);
 if (tmp == ((void*)0))
  return (result);
 amount = 0;
 for (i = 0; i < array->length; ++i)
 {
  tmp[i] = filter(array->items[i]);
  if (tmp[i])
   ++amount;
 }
 result.items = (s_array_int*)Memory_Alloc(sizeof(s_array_int) * amount);
 if (result.items == ((void*)0))
  return (result);
 result.length = amount;
 amount = 0;
 for (i = 0; i < result.length; ++i)
 {
  if (tmp[i])
  {
   result.items[i] = array->items[i + amount];
  }
  else ++amount;
 }
 Memory_Free(tmp);
 return (result);
}



s_array_array_int Array_array_int_Filter_I(s_array_array_int const* array, t_bool (*filter)(s_array_int item, t_uint index))
{
 s_array_array_int result = {0};
 t_bool* tmp;
 t_uint amount;
 t_uint i;


 if (array == ((void*)0) || array->items == ((void*)0) || filter == ((void*)0))
  return (result);

 tmp = (t_bool*)Memory_Alloc(sizeof(t_bool) * array->length);
 if (tmp == ((void*)0))
  return (result);
 amount = 0;
 for (i = 0; i < array->length; ++i)
 {
  tmp[i] = filter(array->items[i], i);
  if (tmp[i])
   ++amount;
 }
 result.items = (s_array_int*)Memory_Alloc(sizeof(s_array_int) * amount);
 if (result.items == ((void*)0))
  return (result);
 result.length = amount;
 amount = 0;
 for (i = 0; i < result.length; ++i)
 {
  if (tmp[i])
  {
   result.items[i] = array->items[i + amount];
  }
  else ++amount;
 }
 Memory_Free(tmp);
 return (result);
}
# 22 "./hdr/libccc/monad/array.c" 2
# 30 "./test/_foreach.c" 2




# 1 "./hdr/libccc/monad/list.c" 1


# 1 "./hdr/libccc/monad/list.h" 1
# 40 "./hdr/libccc/monad/list.h"
# 1 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 1 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdarg.h" 1 3 4
# 2 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 2 3 4
# 41 "./hdr/libccc/monad/list.h" 2




# 74 "./hdr/libccc/monad/list.h"
typedef struct list_int
{

 struct list_int* next;
 int item;
} s_list_int;
# 105 "./hdr/libccc/monad/list.h"
__attribute__((malloc))
s_list_int* List_int_Item(int item);
# 119 "./hdr/libccc/monad/list.h"
__attribute__((malloc))
s_list_int* List_int_New(t_uint n, ...);






void List_int_Delete(s_list_int* *a_list);







__attribute__((malloc))
s_list_int* List_int_Duplicate(s_list_int const* list);
# 148 "./hdr/libccc/monad/list.h"
s_list_int* List_int_Get(s_list_int const* list, t_uint index);
# 158 "./hdr/libccc/monad/list.h"
s_list_int* List_int_Set(s_list_int* list, t_uint index, int item);
# 168 "./hdr/libccc/monad/list.h"
s_list_int* List_int_Copy(s_list_int* dest, s_list_int const* src, t_uint n);
# 179 "./hdr/libccc/monad/list.h"
__attribute__((malloc))
s_list_int* List_int_Sub(s_list_int const* list, t_uint index, t_uint n);
# 202 "./hdr/libccc/monad/list.h"
s_list_int* List_int_Append(s_list_int* list, s_list_int* elem);
# 215 "./hdr/libccc/monad/list.h"
s_list_int* List_int_Prepend(s_list_int* list, s_list_int* elem);
# 230 "./hdr/libccc/monad/list.h"
s_list_int* List_int_Insert(s_list_int* list, int item, t_uint index);





s_list_int* List_int_Remove(s_list_int* list, t_uint index);




s_list_int* List_int_RemoveAll(s_list_int* list, int item);






__attribute__((malloc))
s_list_int* List_int_Replace(s_list_int const* list, int old, int new);
# 267 "./hdr/libccc/monad/list.h"
t_uint List_int_Length(s_list_int const* list);
# 277 "./hdr/libccc/monad/list.h"
s_list_int const* List_int_Find(s_list_int const* list, int item);
# 287 "./hdr/libccc/monad/list.h"
t_sint List_int_IndexOf(s_list_int const* list, int item);
# 299 "./hdr/libccc/monad/list.h"
t_bool List_int_Equals(s_list_int const* list1, s_list_int const* list2);



t_bool List_int_Equals_N(s_list_int const* list1, s_list_int const* list2, t_uint n);



t_sint List_int_Compare(s_list_int const* list1, s_list_int const* list2, t_sint (*compare)(int item1, int item2));



t_sint List_int_Compare_N(s_list_int const* list1, s_list_int const* list2, t_sint (*compare)(int item1, int item2), t_uint n);
# 327 "./hdr/libccc/monad/list.h"
void List_int_Iterate(s_list_int* list, void (*f)(int item));


void List_int_Iterate_I(s_list_int* list, void (*f)(int item, t_uint index));
# 340 "./hdr/libccc/monad/list.h"
__attribute__((malloc))
s_list_int* List_int_Map(s_list_int const* list, int (*map)(int item));


__attribute__((malloc))
s_list_int* List_int_Map_I(s_list_int const* list, int (*map)(int item, t_uint index));





__attribute__((malloc))
s_list_int* List_int_Filter(s_list_int const* list, t_bool (*filter)(int item));


__attribute__((malloc))
s_list_int* List_int_Filter_I(s_list_int const* list, t_bool (*filter)(int item, t_uint index));






# 4 "./hdr/libccc/monad/list.c" 2

# 1 "./hdr/libccc/../../src/monad/list/lstitem.c" 1






s_list_int* List_int_Item(int item)
{
 s_list_int* result;

 result = (s_list_int*)Memory_New(sizeof(s_list_int));
 if (result == ((void*)0))
  return (((void*)0));
 result->item = item;
 return (result);
}
# 6 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstnew.c" 1

# 1 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 1 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdarg.h" 1 3 4
# 2 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 2 3 4
# 3 "./hdr/libccc/../../src/monad/list/lstnew.c" 2






s_list_int* List_int_New(t_uint n, ...)
{
 va_list list;
 int item;
 s_list_int* result = ((void*)0);
 s_list_int* elem;
 s_list_int* new;

 if (n == 0)
  return (((void*)0));
 
# 19 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
__builtin_va_start(
# 19 "./hdr/libccc/../../src/monad/list/lstnew.c"
list
# 19 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
,
# 19 "./hdr/libccc/../../src/monad/list/lstnew.c"
n
# 19 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
)
# 19 "./hdr/libccc/../../src/monad/list/lstnew.c"
                 ;
 for (t_uint i = 1; i <= n; ++i)
 {
  item = 
# 22 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
        __builtin_va_arg(
# 22 "./hdr/libccc/../../src/monad/list/lstnew.c"
        list
# 22 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
        ,
# 22 "./hdr/libccc/../../src/monad/list/lstnew.c"
        int
# 22 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
        )
# 22 "./hdr/libccc/../../src/monad/list/lstnew.c"
                       ;
  if (!(new = (s_list_int*)Memory_Alloc(sizeof(s_list_int))))
   break;
  new->next = ((void*)0);
  new->item = item;
  if (i == 1)
  {
   elem = new;
   result = new;
  }
  else
  {
   elem->next = new;
   elem = new;
  }
 }
 
# 38 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
__builtin_va_end(
# 38 "./hdr/libccc/../../src/monad/list/lstnew.c"
list
# 38 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
)
# 38 "./hdr/libccc/../../src/monad/list/lstnew.c"
            ;
 return (result);
}
# 7 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstdel.c" 1






void List_int_Delete(s_list_int* *a_list)
{

 s_list_int* next;
 s_list_int* i;


 if (a_list == ((void*)0))
  return ;

 i = *a_list;
 while (i)
 {

  next = i->next;
  Memory_Free(i);
  i = next;


 }
 *a_list = ((void*)0);
}
# 8 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstdup.c" 1






s_list_int* List_int_Duplicate(s_list_int const* list)
{
 s_list_int* result = ((void*)0);
 s_list_int* elem = ((void*)0);
 s_list_int* tmp;


 if (list == ((void*)0))
  return (((void*)0));

 while (list)
 {
  if (!(tmp = (s_list_int*)Memory_Duplicate(list, sizeof(s_list_int))))
   break;
  if (result == ((void*)0))
   result = tmp;
  else
  {

   elem->next = tmp;
  }
  elem = tmp;
  list = list->next;
 }
 return (result);
}
# 9 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstget.c" 1





s_list_int* List_int_Get(s_list_int const* list, t_uint index)
{

 if (list == ((void*)0))
  return (((void*)0));

 for (t_uint i = 0; i < index; ++i)
 {
  if (list->next == ((void*)0))
   return (((void*)0));
  else
   list = list->next;
 }
 return ((s_list_int*)list);
}
# 10 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstset.c" 1





s_list_int* List_int_Set(s_list_int* list, t_uint index, int item)
{

 if (list == ((void*)0))
  return (((void*)0));

 for (t_uint i = 0; i < index; ++i)
 {
  if (list->next == ((void*)0))
   return (((void*)0));
  else
  {
   list->item = item;
   return (list);
  }
  list = list->next;
 }
 return (((void*)0));
}
# 11 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstcpy.c" 1





s_list_int* List_int_Copy(s_list_int* dest, s_list_int const* src, t_uint n)
{
 s_list_int* list;


 if (dest == ((void*)0) || src == ((void*)0))
  return (((void*)0));

 list = dest;
 while (list && n--)
 {
  list->item = src->item;
  src = src->next;
  list = list->next;
 }
 return (dest);
}
# 12 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstsub.c" 1






s_list_int* List_int_Sub(s_list_int const* list, t_uint index, t_uint n)
{
 s_list_int* result = ((void*)0);
 s_list_int* elem = ((void*)0);
 s_list_int* tmp;


 if (list == ((void*)0))
  return (((void*)0));

 if (n == 0)
  return (((void*)0));
 while (list && index--)
 {
  list = list->next;
 }
 if (list == ((void*)0))
  return (((void*)0));
 elem = result;
 list = list->next;
 while (list && n--)
 {
  if (!(tmp = (s_list_int*)Memory_Duplicate(list, sizeof(s_list_int))))
   break;
  if (result == ((void*)0))
   result = tmp;
  else
  {

   elem->next = tmp;
  }
  elem = tmp;
  list = list->next;
 }
 return (result);
}
# 13 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstappend.c" 1





s_list_int* List_int_Append(s_list_int* list, s_list_int* elem)
{
 s_list_int* i;


 if (list == ((void*)0))
  return (((void*)0));

 if (elem == ((void*)0))
  return (list);
 i = list;
 while (i->next != ((void*)0))
 {
  i = i->next;
 }

 i->next = elem;
 return (list);
}
# 14 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstprepend.c" 1





s_list_int* List_int_Prepend(s_list_int* list, s_list_int* elem)
{

 if (list == ((void*)0))
  return (((void*)0));

 if (elem == ((void*)0))
  return (list);

 elem->next = list;
 return (elem);
}
# 15 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstinsert.c" 1






s_list_int* List_int_Insert(s_list_int* list, int item, t_uint index)
{
 s_list_int* elem;
 s_list_int* new;
 s_list_int* tmp;


 if (list == ((void*)0))
  return (((void*)0));

 if (!(new = (s_list_int*)Memory_Alloc(sizeof(s_list_int))))
  return (list);
 if (list == ((void*)0) || index == 0)
 {
  new->item = item;
  new->next = list;
  return (new);
 }
 elem = list;
 for (t_uint i = 0; i < index; ++i)
 {
  elem = elem->next;
 }

 tmp = elem->next;
 elem->next = new;
 new->next = tmp;
 return (list);
}
# 16 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstremove.c" 1






s_list_int* List_int_Remove(s_list_int* list, t_uint index)
{
 s_list_int* elem;
 s_list_int* tmp;


 if (list == ((void*)0))
  return (((void*)0));

 elem = list;
 if (index == 0)
 {
  list = list->next;
  Memory_Free(elem);
  return (list);
 }
 for (t_uint i = 0; elem && i < index; ++i)
 {
  elem = elem->next;
 }
 if (elem == ((void*)0) || elem->next == ((void*)0))
  return (list);
 tmp = elem->next;
 elem->next = tmp->next;

 Memory_Free(tmp);
 return (list);
}



s_list_int* List_int_RemoveAll(s_list_int* list, int item)
{
 s_list_int* elem;
 s_list_int* tmp;


 if (list == ((void*)0))
  return (((void*)0));

 elem = list;
 for (t_uint i = 0; elem; ++i)
 {
  if (((elem->item) == (item)))
  {
   tmp = elem->next;
   elem->next = tmp->next;

   Memory_Free(tmp);
  }
  elem = elem->next;
 }
 return (list);
}
# 17 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstreplace.c" 1





s_list_int* List_int_Replace(s_list_int const* list, int old, int new)
{
 s_list_int* result = ((void*)0);
 s_list_int* elem;


 if (list == ((void*)0))
  return (((void*)0));

 while (list)
 {
  elem = List_int_Item(((list->item) == (old)) ? new : list->item);
  if (elem == ((void*)0))
   break;
  List_int_Append(result, elem);
  list = list->next;
 }
 return (result);
}
# 18 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstsize.c" 1





t_uint List_int_Size(s_list_int const* lst)
{
 t_uint result;


 if (lst == ((void*)0))
  return (0);

 result = 0;
 while (lst)
 {
  ++result;
  lst = lst->next;
 }
 return (result);
}
# 19 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstequ.c" 1





t_bool List_int_Equals(s_list_int const* list1, s_list_int const* list2)
{

 if (list1 == list2)
  return ((1));
 if (list1 == ((void*)0) || list2 == ((void*)0))
  return ((0));

 while (list1 && list2)
 {
  if (!((list1->item) == (list2->item)))
   return ((0));
  list1 = list1->next;
  list2 = list2->next;
 }
 return ((1));
}



t_bool List_int_Equals_N(s_list_int const* list1, s_list_int const* list2, t_uint n)
{

 if (list1 == list2)
  return ((1));
 if (list1 == ((void*)0) || list2 == ((void*)0))
  return ((0));

 while (list1 && list2 && n--)
 {
  if (!((list1->item) == (list2->item)))
   return ((0));
  list1 = list1->next;
  list2 = list2->next;
 }
 return ((1));
}
# 20 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstcmp.c" 1





t_sint List_int_Compare(s_list_int const* list1, s_list_int const* list2, t_sint (*compare)(int item1, int item2))
{
 t_sint result;


 if (list1 == list2)
  return (0);
 if (list1 == ((void*)0) || list2 == ((void*)0) || compare == ((void*)0))
  return ((-1));

 while (list1 && list2)
 {
  result = compare(list1->item, list2->item);
  if (result != 0)
   return (result);
  list1 = list1->next;
  list2 = list2->next;
 }
 return (0);
}



t_sint List_int_Compare_N(s_list_int const* list1, s_list_int const* list2, t_sint (*compare)(int item1, int item2), t_uint n)
{
 t_sint result;


 if (list1 == list2)
  return (0);
 if (list1 == ((void*)0) || list2 == ((void*)0) || compare == ((void*)0))
  return ((-1));

 while (list1 && list2 && n--)
 {
  result = compare(list1->item, list2->item);
  if (result != 0)
   return (result);
  list1 = list1->next;
  list2 = list2->next;
 }
 return (0);
}
# 21 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstiter.c" 1





void List_int_Iterate(s_list_int* list, void (*f)(int item))
{

 if (list == ((void*)0) || f == ((void*)0))
  return ;

 while (list)
 {
  f(list->item);
  list = list->next;
 }
}



void List_int_Iterate_I(s_list_int* list, void (*f)(int item, t_uint index))
{
 t_uint i;


 if (list == ((void*)0) || f == ((void*)0))
  return ;

 i = 0;
 while (list)
 {
  f(list->item, i);
  list = list->next;
  ++i;
 }
}
# 22 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstmap.c" 1





s_list_int* List_int_Map(s_list_int const* list, int (*map)(int item))
{
 s_list_int* result = ((void*)0);
 s_list_int* elem;


 if (list == ((void*)0) || map == ((void*)0))
  return (((void*)0));

 while (list)
 {
  elem = List_int_Item(map(list->item));
  if (elem == ((void*)0))
   break;
  List_int_Append(result, elem);
  list = list->next;
 }
 return (result);
}



s_list_int* List_int_Map_I(s_list_int const* list, int (*map)(int item, t_uint index))
{
 s_list_int* result = ((void*)0);
 s_list_int* elem;
 t_uint i;


 if (list == ((void*)0) || map == ((void*)0))
  return (((void*)0));

 i = 0;
 while (list)
 {
  elem = List_int_Item(map(list->item, i));
  if (elem == ((void*)0))
   break;
  List_int_Append(result, elem);
  list = list->next;
  ++i;
 }
 return (result);
}
# 23 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstfilt.c" 1





s_list_int* List_int_Filter(s_list_int const* list, t_bool (*filter)(int item))
{
 s_list_int* result = ((void*)0);
 s_list_int* elem;


 if (list == ((void*)0) || filter == ((void*)0))
  return (((void*)0));

 while (list)
 {
  if (filter(list->item))
  {
   elem = List_int_Item(list->item);
   List_int_Append(result, elem);
  }
  list = list->next;
 }
 return (result);
}



s_list_int* List_int_Filter_I(s_list_int const* list, t_bool (*filter)(int item, t_uint index))
{
 s_list_int* result = ((void*)0);
 s_list_int* elem;
 t_uint i;


 if (list == ((void*)0) || filter == ((void*)0))
  return (((void*)0));

 i = 0;
 while (list)
 {
  if (filter(list->item, i))
  {
   elem = List_int_Item(list->item);
   List_int_Append(result, elem);
  }
  list = list->next;
  ++i;
 }
 return (result);
}
# 24 "./hdr/libccc/monad/list.c" 2
# 35 "./test/_foreach.c" 2




# 1 "./hdr/libccc/monad/list.c" 1


# 1 "./hdr/libccc/monad/list.h" 1
# 40 "./hdr/libccc/monad/list.h"
# 1 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 1 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdarg.h" 1 3 4
# 2 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 2 3 4
# 41 "./hdr/libccc/monad/list.h" 2




# 74 "./hdr/libccc/monad/list.h"
typedef struct list_list_int
{

 struct list_list_int* next;
 s_list_int item;
} s_list_list_int;
# 105 "./hdr/libccc/monad/list.h"
__attribute__((malloc))
s_list_list_int* List_list_int_Item(s_list_int item);
# 119 "./hdr/libccc/monad/list.h"
__attribute__((malloc))
s_list_list_int* List_list_int_New(t_uint n, ...);






void List_list_int_Delete(s_list_list_int* *a_list);







__attribute__((malloc))
s_list_list_int* List_list_int_Duplicate(s_list_list_int const* list);
# 148 "./hdr/libccc/monad/list.h"
s_list_list_int* List_list_int_Get(s_list_list_int const* list, t_uint index);
# 158 "./hdr/libccc/monad/list.h"
s_list_list_int* List_list_int_Set(s_list_list_int* list, t_uint index, s_list_int item);
# 168 "./hdr/libccc/monad/list.h"
s_list_list_int* List_list_int_Copy(s_list_list_int* dest, s_list_list_int const* src, t_uint n);
# 179 "./hdr/libccc/monad/list.h"
__attribute__((malloc))
s_list_list_int* List_list_int_Sub(s_list_list_int const* list, t_uint index, t_uint n);
# 202 "./hdr/libccc/monad/list.h"
s_list_list_int* List_list_int_Append(s_list_list_int* list, s_list_list_int* elem);
# 215 "./hdr/libccc/monad/list.h"
s_list_list_int* List_list_int_Prepend(s_list_list_int* list, s_list_list_int* elem);
# 230 "./hdr/libccc/monad/list.h"
s_list_list_int* List_list_int_Insert(s_list_list_int* list, s_list_int item, t_uint index);





s_list_list_int* List_list_int_Remove(s_list_list_int* list, t_uint index);




s_list_list_int* List_list_int_RemoveAll(s_list_list_int* list, s_list_int item);






__attribute__((malloc))
s_list_list_int* List_list_int_Replace(s_list_list_int const* list, s_list_int old, s_list_int new);
# 267 "./hdr/libccc/monad/list.h"
t_uint List_list_int_Length(s_list_list_int const* list);
# 277 "./hdr/libccc/monad/list.h"
s_list_list_int const* List_list_int_Find(s_list_list_int const* list, s_list_int item);
# 287 "./hdr/libccc/monad/list.h"
t_sint List_list_int_IndexOf(s_list_list_int const* list, s_list_int item);
# 299 "./hdr/libccc/monad/list.h"
t_bool List_list_int_Equals(s_list_list_int const* list1, s_list_list_int const* list2);



t_bool List_list_int_Equals_N(s_list_list_int const* list1, s_list_list_int const* list2, t_uint n);



t_sint List_list_int_Compare(s_list_list_int const* list1, s_list_list_int const* list2, t_sint (*compare)(s_list_int item1, s_list_int item2));



t_sint List_list_int_Compare_N(s_list_list_int const* list1, s_list_list_int const* list2, t_sint (*compare)(s_list_int item1, s_list_int item2), t_uint n);
# 327 "./hdr/libccc/monad/list.h"
void List_list_int_Iterate(s_list_list_int* list, void (*f)(s_list_int item));


void List_list_int_Iterate_I(s_list_list_int* list, void (*f)(s_list_int item, t_uint index));
# 340 "./hdr/libccc/monad/list.h"
__attribute__((malloc))
s_list_list_int* List_list_int_Map(s_list_list_int const* list, s_list_int (*map)(s_list_int item));


__attribute__((malloc))
s_list_list_int* List_list_int_Map_I(s_list_list_int const* list, s_list_int (*map)(s_list_int item, t_uint index));





__attribute__((malloc))
s_list_list_int* List_list_int_Filter(s_list_list_int const* list, t_bool (*filter)(s_list_int item));


__attribute__((malloc))
s_list_list_int* List_list_int_Filter_I(s_list_list_int const* list, t_bool (*filter)(s_list_int item, t_uint index));






# 4 "./hdr/libccc/monad/list.c" 2

# 1 "./hdr/libccc/../../src/monad/list/lstitem.c" 1






s_list_list_int* List_list_int_Item(s_list_int item)
{
 s_list_list_int* result;

 result = (s_list_list_int*)Memory_New(sizeof(s_list_list_int));
 if (result == ((void*)0))
  return (((void*)0));
 result->item = item;
 return (result);
}
# 6 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstnew.c" 1

# 1 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 1 3 4
# 1 "/usr/x86_64-w64-mingw32/sys-root/mingw/include/stdarg.h" 1 3 4
# 2 "/usr/lib/gcc/x86_64-w64-mingw32/10/include/stdarg.h" 2 3 4
# 3 "./hdr/libccc/../../src/monad/list/lstnew.c" 2






s_list_list_int* List_list_int_New(t_uint n, ...)
{
 va_list list;
 s_list_int item;
 s_list_list_int* result = ((void*)0);
 s_list_list_int* elem;
 s_list_list_int* new;

 if (n == 0)
  return (((void*)0));
 
# 19 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
__builtin_va_start(
# 19 "./hdr/libccc/../../src/monad/list/lstnew.c"
list
# 19 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
,
# 19 "./hdr/libccc/../../src/monad/list/lstnew.c"
n
# 19 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
)
# 19 "./hdr/libccc/../../src/monad/list/lstnew.c"
                 ;
 for (t_uint i = 1; i <= n; ++i)
 {
  item = 
# 22 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
        __builtin_va_arg(
# 22 "./hdr/libccc/../../src/monad/list/lstnew.c"
        list
# 22 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
        ,
# 22 "./hdr/libccc/../../src/monad/list/lstnew.c"
        s_list_int
# 22 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
        )
# 22 "./hdr/libccc/../../src/monad/list/lstnew.c"
                       ;
  if (!(new = (s_list_list_int*)Memory_Alloc(sizeof(s_list_list_int))))
   break;
  new->next = ((void*)0);
  new->item = item;
  if (i == 1)
  {
   elem = new;
   result = new;
  }
  else
  {
   elem->next = new;
   elem = new;
  }
 }
 
# 38 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
__builtin_va_end(
# 38 "./hdr/libccc/../../src/monad/list/lstnew.c"
list
# 38 "./hdr/libccc/../../src/monad/list/lstnew.c" 3 4
)
# 38 "./hdr/libccc/../../src/monad/list/lstnew.c"
            ;
 return (result);
}
# 7 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstdel.c" 1






void List_list_int_Delete(s_list_list_int* *a_list)
{

 s_list_list_int* next;
 s_list_list_int* i;


 if (a_list == ((void*)0))
  return ;

 i = *a_list;
 while (i)
 {

  next = i->next;
  Memory_Free(i);
  i = next;


 }
 *a_list = ((void*)0);
}
# 8 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstdup.c" 1






s_list_list_int* List_list_int_Duplicate(s_list_list_int const* list)
{
 s_list_list_int* result = ((void*)0);
 s_list_list_int* elem = ((void*)0);
 s_list_list_int* tmp;


 if (list == ((void*)0))
  return (((void*)0));

 while (list)
 {
  if (!(tmp = (s_list_list_int*)Memory_Duplicate(list, sizeof(s_list_list_int))))
   break;
  if (result == ((void*)0))
   result = tmp;
  else
  {

   elem->next = tmp;
  }
  elem = tmp;
  list = list->next;
 }
 return (result);
}
# 9 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstget.c" 1





s_list_list_int* List_list_int_Get(s_list_list_int const* list, t_uint index)
{

 if (list == ((void*)0))
  return (((void*)0));

 for (t_uint i = 0; i < index; ++i)
 {
  if (list->next == ((void*)0))
   return (((void*)0));
  else
   list = list->next;
 }
 return ((s_list_list_int*)list);
}
# 10 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstset.c" 1





s_list_list_int* List_list_int_Set(s_list_list_int* list, t_uint index, s_list_int item)
{

 if (list == ((void*)0))
  return (((void*)0));

 for (t_uint i = 0; i < index; ++i)
 {
  if (list->next == ((void*)0))
   return (((void*)0));
  else
  {
   list->item = item;
   return (list);
  }
  list = list->next;
 }
 return (((void*)0));
}
# 11 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstcpy.c" 1





s_list_list_int* List_list_int_Copy(s_list_list_int* dest, s_list_list_int const* src, t_uint n)
{
 s_list_list_int* list;


 if (dest == ((void*)0) || src == ((void*)0))
  return (((void*)0));

 list = dest;
 while (list && n--)
 {
  list->item = src->item;
  src = src->next;
  list = list->next;
 }
 return (dest);
}
# 12 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstsub.c" 1






s_list_list_int* List_list_int_Sub(s_list_list_int const* list, t_uint index, t_uint n)
{
 s_list_list_int* result = ((void*)0);
 s_list_list_int* elem = ((void*)0);
 s_list_list_int* tmp;


 if (list == ((void*)0))
  return (((void*)0));

 if (n == 0)
  return (((void*)0));
 while (list && index--)
 {
  list = list->next;
 }
 if (list == ((void*)0))
  return (((void*)0));
 elem = result;
 list = list->next;
 while (list && n--)
 {
  if (!(tmp = (s_list_list_int*)Memory_Duplicate(list, sizeof(s_list_list_int))))
   break;
  if (result == ((void*)0))
   result = tmp;
  else
  {

   elem->next = tmp;
  }
  elem = tmp;
  list = list->next;
 }
 return (result);
}
# 13 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstappend.c" 1





s_list_list_int* List_list_int_Append(s_list_list_int* list, s_list_list_int* elem)
{
 s_list_list_int* i;


 if (list == ((void*)0))
  return (((void*)0));

 if (elem == ((void*)0))
  return (list);
 i = list;
 while (i->next != ((void*)0))
 {
  i = i->next;
 }

 i->next = elem;
 return (list);
}
# 14 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstprepend.c" 1





s_list_list_int* List_list_int_Prepend(s_list_list_int* list, s_list_list_int* elem)
{

 if (list == ((void*)0))
  return (((void*)0));

 if (elem == ((void*)0))
  return (list);

 elem->next = list;
 return (elem);
}
# 15 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstinsert.c" 1






s_list_list_int* List_list_int_Insert(s_list_list_int* list, s_list_int item, t_uint index)
{
 s_list_list_int* elem;
 s_list_list_int* new;
 s_list_list_int* tmp;


 if (list == ((void*)0))
  return (((void*)0));

 if (!(new = (s_list_list_int*)Memory_Alloc(sizeof(s_list_list_int))))
  return (list);
 if (list == ((void*)0) || index == 0)
 {
  new->item = item;
  new->next = list;
  return (new);
 }
 elem = list;
 for (t_uint i = 0; i < index; ++i)
 {
  elem = elem->next;
 }

 tmp = elem->next;
 elem->next = new;
 new->next = tmp;
 return (list);
}
# 16 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstremove.c" 1






s_list_list_int* List_list_int_Remove(s_list_list_int* list, t_uint index)
{
 s_list_list_int* elem;
 s_list_list_int* tmp;


 if (list == ((void*)0))
  return (((void*)0));

 elem = list;
 if (index == 0)
 {
  list = list->next;
  Memory_Free(elem);
  return (list);
 }
 for (t_uint i = 0; elem && i < index; ++i)
 {
  elem = elem->next;
 }
 if (elem == ((void*)0) || elem->next == ((void*)0))
  return (list);
 tmp = elem->next;
 elem->next = tmp->next;

 Memory_Free(tmp);
 return (list);
}



s_list_list_int* List_list_int_RemoveAll(s_list_list_int* list, s_list_int item)
{
 s_list_list_int* elem;
 s_list_list_int* tmp;


 if (list == ((void*)0))
  return (((void*)0));

 elem = list;
 for (t_uint i = 0; elem; ++i)
 {
  if (((elem->item).next == (item).next && (elem->item).item == (item).item))
  {
   tmp = elem->next;
   elem->next = tmp->next;

   Memory_Free(tmp);
  }
  elem = elem->next;
 }
 return (list);
}
# 17 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstreplace.c" 1





s_list_list_int* List_list_int_Replace(s_list_list_int const* list, s_list_int old, s_list_int new)
{
 s_list_list_int* result = ((void*)0);
 s_list_list_int* elem;


 if (list == ((void*)0))
  return (((void*)0));

 while (list)
 {
  elem = List_list_int_Item(((list->item).next == (old).next && (list->item).item == (old).item) ? new : list->item);
  if (elem == ((void*)0))
   break;
  List_list_int_Append(result, elem);
  list = list->next;
 }
 return (result);
}
# 18 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstsize.c" 1





t_uint List_list_int_Size(s_list_list_int const* lst)
{
 t_uint result;


 if (lst == ((void*)0))
  return (0);

 result = 0;
 while (lst)
 {
  ++result;
  lst = lst->next;
 }
 return (result);
}
# 19 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstequ.c" 1





t_bool List_list_int_Equals(s_list_list_int const* list1, s_list_list_int const* list2)
{

 if (list1 == list2)
  return ((1));
 if (list1 == ((void*)0) || list2 == ((void*)0))
  return ((0));

 while (list1 && list2)
 {
  if (!((list1->item).next == (list2->item).next && (list1->item).item == (list2->item).item))
   return ((0));
  list1 = list1->next;
  list2 = list2->next;
 }
 return ((1));
}



t_bool List_list_int_Equals_N(s_list_list_int const* list1, s_list_list_int const* list2, t_uint n)
{

 if (list1 == list2)
  return ((1));
 if (list1 == ((void*)0) || list2 == ((void*)0))
  return ((0));

 while (list1 && list2 && n--)
 {
  if (!((list1->item).next == (list2->item).next && (list1->item).item == (list2->item).item))
   return ((0));
  list1 = list1->next;
  list2 = list2->next;
 }
 return ((1));
}
# 20 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstcmp.c" 1





t_sint List_list_int_Compare(s_list_list_int const* list1, s_list_list_int const* list2, t_sint (*compare)(s_list_int item1, s_list_int item2))
{
 t_sint result;


 if (list1 == list2)
  return (0);
 if (list1 == ((void*)0) || list2 == ((void*)0) || compare == ((void*)0))
  return ((-1));

 while (list1 && list2)
 {
  result = compare(list1->item, list2->item);
  if (result != 0)
   return (result);
  list1 = list1->next;
  list2 = list2->next;
 }
 return (0);
}



t_sint List_list_int_Compare_N(s_list_list_int const* list1, s_list_list_int const* list2, t_sint (*compare)(s_list_int item1, s_list_int item2), t_uint n)
{
 t_sint result;


 if (list1 == list2)
  return (0);
 if (list1 == ((void*)0) || list2 == ((void*)0) || compare == ((void*)0))
  return ((-1));

 while (list1 && list2 && n--)
 {
  result = compare(list1->item, list2->item);
  if (result != 0)
   return (result);
  list1 = list1->next;
  list2 = list2->next;
 }
 return (0);
}
# 21 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstiter.c" 1





void List_list_int_Iterate(s_list_list_int* list, void (*f)(s_list_int item))
{

 if (list == ((void*)0) || f == ((void*)0))
  return ;

 while (list)
 {
  f(list->item);
  list = list->next;
 }
}



void List_list_int_Iterate_I(s_list_list_int* list, void (*f)(s_list_int item, t_uint index))
{
 t_uint i;


 if (list == ((void*)0) || f == ((void*)0))
  return ;

 i = 0;
 while (list)
 {
  f(list->item, i);
  list = list->next;
  ++i;
 }
}
# 22 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstmap.c" 1





s_list_list_int* List_list_int_Map(s_list_list_int const* list, s_list_int (*map)(s_list_int item))
{
 s_list_list_int* result = ((void*)0);
 s_list_list_int* elem;


 if (list == ((void*)0) || map == ((void*)0))
  return (((void*)0));

 while (list)
 {
  elem = List_list_int_Item(map(list->item));
  if (elem == ((void*)0))
   break;
  List_list_int_Append(result, elem);
  list = list->next;
 }
 return (result);
}



s_list_list_int* List_list_int_Map_I(s_list_list_int const* list, s_list_int (*map)(s_list_int item, t_uint index))
{
 s_list_list_int* result = ((void*)0);
 s_list_list_int* elem;
 t_uint i;


 if (list == ((void*)0) || map == ((void*)0))
  return (((void*)0));

 i = 0;
 while (list)
 {
  elem = List_list_int_Item(map(list->item, i));
  if (elem == ((void*)0))
   break;
  List_list_int_Append(result, elem);
  list = list->next;
  ++i;
 }
 return (result);
}
# 23 "./hdr/libccc/monad/list.c" 2
# 1 "./hdr/libccc/../../src/monad/list/lstfilt.c" 1





s_list_list_int* List_list_int_Filter(s_list_list_int const* list, t_bool (*filter)(s_list_int item))
{
 s_list_list_int* result = ((void*)0);
 s_list_list_int* elem;


 if (list == ((void*)0) || filter == ((void*)0))
  return (((void*)0));

 while (list)
 {
  if (filter(list->item))
  {
   elem = List_list_int_Item(list->item);
   List_list_int_Append(result, elem);
  }
  list = list->next;
 }
 return (result);
}



s_list_list_int* List_list_int_Filter_I(s_list_list_int const* list, t_bool (*filter)(s_list_int item, t_uint index))
{
 s_list_list_int* result = ((void*)0);
 s_list_list_int* elem;
 t_uint i;


 if (list == ((void*)0) || filter == ((void*)0))
  return (((void*)0));

 i = 0;
 while (list)
 {
  if (filter(list->item, i))
  {
   elem = List_list_int_Item(list->item);
   List_list_int_Append(result, elem);
  }
  list = list->next;
  ++i;
 }
 return (result);
}
# 24 "./hdr/libccc/monad/list.c" 2
# 40 "./test/_foreach.c" 2
# 48 "./test/_foreach.c"
int main()
{
 t_uint i;

 IO_Output_String("\n- s_array<char*>:\n");
 {
  s_array_str str_array = Array_str_New(10,
   "Yo, my boi!",
   "What's up, dog?",
   "Not much, you ?",
   "...",
   "Yo, spit it out.",
   "What's the deal ?",
   "You got the dope ?",
   "I ask the questions.",
   "He's got a gun!",
   "FREEZE! HANDS IN THE AIR!");
  i = 0;
  t_uint str_i = 0; if ((void*)(&str_array) != ((void*)0) && (&str_array)->items) for(char* str; (str_i < (&str_array)->length); ++str_i, str = (str_i == (&str_array)->length ? str : (&str_array)->items[str_i]))
  {
   IO_Output_Format("i:%u,\titer:%u,\tstr:%p -> \"%s\"\n", i++, str_i, str, str);
  }
 }
 IO_Output_String("\n- s_list<char*>:\n");
 {
  s_list_str* str_list = List_str_New(10,
   "Yo, my boi!",
   "What's up, dog?",
   "Not much, you ?",
   "...",
   "Yo, spit it out.",
   "What's the deal ?",
   "You got the dope ?",
   "I ask the questions.",
   "He's got a gun!",
   "FREEZE! HANDS IN THE AIR!");
  i = 0;
  struct _str{ struct _str*next; char* item; }* str_i = (struct _str*)(str_list); if ((void*)(str_list) != ((void*)0)) for(char* str; (str_i != ((void*)0)); str_i = str_i->next, str = (str_i == ((void*)0) ? str : (char*)(str_i->item)))
  {
   IO_Output_Format("i:%u,\titer:%p,\tstr:%p -> \"%s\"\n", i++, str_i, str, str);
  }
 }



 IO_Output_String("\n- s_array<s_array<int>>:\n");
 {
  s_array_array_int int_array_array = Array_array_int_New(3,
   Array_int_New(3, 0, 1, 10),
   Array_int_New(3, 42, 69, 420),
   Array_int_New(6, 42, 69, 420, 0, 1, 10));
  i = 0;
  t_uint int_array_i = 0; if ((void*)(&int_array_array) != ((void*)0) && (&int_array_array)->items) for(s_array_int int_array; (int_array_i < (&int_array_array)->length); ++int_array_i, int_array = (int_array_i == (&int_array_array)->length ? int_array : (&int_array_array)->items[int_array_i]))
  {
   t_uint integer_i = 0; if ((void*)(&int_array) != ((void*)0) && (&int_array)->items) for(int integer; (integer_i < (&int_array)->length); ++integer_i, integer = (integer_i == (&int_array)->length ? integer : (&int_array)->items[integer_i]))
   {
    IO_Output_Format("i:%u,\titer:%u,\tint: %i\n", i++, integer_i, integer);
   }
  }
 }
 IO_Output_String("\n- s_list<s_list<int>>:\n");
 {
  s_list_list_int* int_list_list = List_list_int_New(3,
   List_int_New(3, 0, 1, 10),
   List_int_New(3, 42, 69, 420),
   List_int_New(6, 42, 69, 420, 0, 1, 10));
  i = 0;
  struct _int_list{ struct _int_list*next; s_list_int item; }* int_list_i = (struct _int_list*)(&int_list_list); if ((void*)(&int_list_list) != ((void*)0)) for(s_list_int int_list; (int_list_i != ((void*)0)); int_list_i = int_list_i->next, int_list = (int_list_i == ((void*)0) ? int_list : (s_list_int)(int_list_i->item)))
  {
   struct _integer{ struct _integer*next; int item; }* integer_i = (struct _integer*)(&int_list); if ((void*)(&int_list) != ((void*)0)) for(int integer; (integer_i != ((void*)0)); integer_i = integer_i->next, integer = (integer_i == ((void*)0) ? integer : (int)(integer_i->item)))
   {
    IO_Output_Format("i:%u,\titer:%p,\tint: %i\n", i++, integer_i, integer);
   }
  }
 }
 return ((0));
}
