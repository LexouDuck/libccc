/*============================================================================*\
||                                            ______________________________  ||
||  libccc/math/algebra.h                    |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_MATH_ALGEBRA_H
#define __LIBCCC_MATH_ALGEBRA_H
/*!@group{libccc_math_algebra,60,libccc/math/algebra.h}
**
**	This header defines useful algebra and calculus types, and functions.
*/

// TODO add other function macros for integral, distance, etc

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc/math/algebra/vector.h"
#include "libccc/math/algebra/matrix.h"
#include "libccc/math/algebra/tensor.h"
#include "libccc/math/algebra/interval.h"

HEADER_CPP

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/



//! The amount of samples used by the numerical/stochastic algebra functions
/*!
**	This is the amount of random sample points taken by the functions which
**	perform numerical approximation (like the Monte-Carlo method integration
**	functions, for instance): a larger value gives more precise results, but
**	takes longer to compute.
*/
#define SAMPLE_NB		(1024)



/*! @endgroup */
HEADER_END
#endif
