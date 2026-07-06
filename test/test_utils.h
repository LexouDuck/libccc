
#ifndef LIBCCCTEST_UTILS_H_
#define LIBCCCTEST_UTILS_H_

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include <stdbool.h>
#ifndef __cplusplus
#ifndef bool
#define bool	_Bool
#endif
#endif

#include "libccc.h"
#include "libccc/char.h"
#include "libccc/text/char/ascii.h"
#include "libccc/text/char/unicode.h"
#include "libccc/sys/time.h"
#include "libccc/math/stat.h"

#include "test_catch.h"
#include "test_timer.h"
#include "test_print.h"



/*============================================================================*\
||                                   Defines                                  ||
\*============================================================================*/



/*
**	Global variables used in tests
*/
extern char const* test1;	extern size_t const test1_len;
extern char const* test2;	extern size_t const test2_len;
extern char const* test3;	extern size_t const test3_len;

extern char const* teststr_cc_c0;
extern char const* teststr_cc_c1;
extern char const* teststr_utf8_fr;
extern char const* teststr_utf8_ru;
extern char const* teststr_utf8_jp;
extern char const* teststr_utf8_ho;
extern char const* teststr_utf8_one_symbol_two_seq ;
extern char const* teststr_utf8_one_symbol_three_seq ;
extern char const* teststr_utf8_hardcore;
extern size_t const teststr_utf8_hardcore_len;
extern size_t const teststr_utf8_hardcore_bytelen;



/*============================================================================*\
||                              Utility Functions                             ||
\*============================================================================*/

int		bool_equals(int a, int b);
int		str_equals(char const* str1, char const* str2);
int		ptrarr_equals(void const** ptr1, void const** ptr2);
int		strarr_equals(char const** strarr1, char const** strarr2);
int		str_equals_until(char const* str1, char const* str2, char c);

char*	strtoescape(char const* str);
char*	strsurround(char const* str, char begin, char end);
char*	print_memory(void const* ptr, t_size length);

char*	ptrtostr(void const* ptr);



s_sorted_uint	print_test_random_uint	(t_uint sample_size, t_uint  range_min, t_uint  range_max);
s_sorted_sint	print_test_random_sint	(t_uint sample_size, t_sint  range_min, t_sint  range_max);
s_sorted_fixed	print_test_random_fixed	(t_uint sample_size, t_fixed range_min, t_fixed range_max);
s_sorted_float	print_test_random_float	(t_uint sample_size, t_float range_min, t_float range_max);



#define DECLARE_NUMBER_UTILITY_FUNCTIONS(TYPE, NAME) \
char*	NAME##tostr(TYPE number); \
void	quicksort_                 ##NAME(TYPE * array, unsigned int start, unsigned int end); \
TYPE	stat_getmin_               ##NAME(const TYPE * values, unsigned int length); \
TYPE	stat_getmax_               ##NAME(const TYPE * values, unsigned int length); \
double*	stat_quantiles_            ##NAME(const TYPE * values, unsigned int length, unsigned int n); \
double	stat_median_               ##NAME(const TYPE * values, unsigned int length); \
double	stat_mode_                 ##NAME(const TYPE * values, unsigned int length); \
double	stat_range_                ##NAME(const TYPE * values, unsigned int length); \
double	stat_midrange_             ##NAME(const TYPE * values, unsigned int length); \
double	stat_midhinge_             ##NAME(const TYPE * values, unsigned int length); \
double	stat_trimean_              ##NAME(const TYPE * values, unsigned int length); \
double	stat_mean_arithmetic_      ##NAME(const TYPE * values, unsigned int length); \
double	stat_mean_geometric_       ##NAME(const TYPE * values, unsigned int length); \
double	stat_mean_harmonic_        ##NAME(const TYPE * values, unsigned int length); \
double	stat_mean_contraharmonic_  ##NAME(const TYPE * values, unsigned int length); \
double	stat_mean_interquartile_   ##NAME(const TYPE * values, unsigned int length); \
double	stat_mean_quadratic_       ##NAME(const TYPE * values, unsigned int length); \
double	stat_mean_cubic_           ##NAME(const TYPE * values, unsigned int length); \
double	stat_mean_power_           ##NAME(const TYPE * values, unsigned int length, double power); \
double	stat_mean_lehmer_          ##NAME(const TYPE * values, unsigned int length, int power); \
double	stat_variance_             ##NAME(const TYPE * values, unsigned int length); \
double	stat_stddev_               ##NAME(const TYPE * values, unsigned int length); \
double	stat_cv_                   ##NAME(const TYPE * values, unsigned int length); \
double	stat_iqr_                  ##NAME(const TYPE * values, unsigned int length); \
double	stat_mad_                  ##NAME(const TYPE * values, unsigned int length); \
double	stat_aad_                  ##NAME(const TYPE * values, unsigned int length, TYPE center); \
double	stat_agm_                  ##NAME(TYPE x, TYPE y); \
double	stat_msd_                  ##NAME(const TYPE * values, const TYPE * expect, unsigned int length); \
double	stat_mse_                  ##NAME(const TYPE * values, const TYPE * expect, unsigned int length); \
double	stat_mae_                  ##NAME(const TYPE * values, const TYPE * expect, unsigned int length); \
double	stat_md_                   ##NAME(const TYPE * values, const TYPE * expect, unsigned int length); \
double	stat_rmd_                  ##NAME(const TYPE * values, const TYPE * expect, unsigned int length); \
double	stat_rmsd_                 ##NAME(const TYPE * values, const TYPE * expect, unsigned int length); \
double	stat_mpe_                  ##NAME(const TYPE * values, const TYPE * expect, unsigned int length); \
double	stat_mape_                 ##NAME(const TYPE * values, const TYPE * expect, unsigned int length); \
double	stat_mspe_                 ##NAME(const TYPE * values, const TYPE * expect, unsigned int length); \
double	stat_rss_                  ##NAME(const TYPE * values, const TYPE * expect, unsigned int length); \
/*
double	stat_moving_average_simple_      ##NAME(const TYPE * values, unsigned int length); \
double	stat_moving_average_cumulative_  ##NAME(const TYPE * values, unsigned int length); \
double	stat_moving_average_weighted_    ##NAME(const TYPE * values, unsigned int length); \
*/

DECLARE_NUMBER_UTILITY_FUNCTIONS(t_uint  , uint)
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_u8    , u8)
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_u16   , u16)
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_u32   , u32)
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_u64   , u64)
#if LIBCONFIG_USE_INT128
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_u128  , u128)
#endif

DECLARE_NUMBER_UTILITY_FUNCTIONS(t_sint  , sint)
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_s8    , s8)
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_s16   , s16)
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_s32   , s32)
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_s64   , s64)
#if LIBCONFIG_USE_INT128
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_s128  , s128)
#endif

DECLARE_NUMBER_UTILITY_FUNCTIONS(t_fixed , fixed)
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_q8    , q8)
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_q16   , q16)
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_q32   , q32)
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_q64   , q64)
#if LIBCONFIG_USE_INT128
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_q128  , q128)
#endif

DECLARE_NUMBER_UTILITY_FUNCTIONS(t_float , float)
#if LIBCONFIG_USE_FLOAT16
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_f16   , f16)
#endif
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_f32   , f32)

DECLARE_NUMBER_UTILITY_FUNCTIONS(t_f64   , f64)
#if LIBCONFIG_USE_FLOAT80
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_f80   , f80)
#endif
#if LIBCONFIG_USE_FLOAT128
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_f128  , f128)
#endif



#endif
