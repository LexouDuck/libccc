#include <math.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>

int main()
{
	for (uint8_t i = 1; i != 0; ++i)
	{
		#define f8_MANTISSA_SIZE	16 // 2^MANTISSA_BITS = 2^4 = 16
		#define f8_MANTISSA_BITS	4
		#define f8_EXPONENT_BIAS	4 // 2^(EXPONENT_BITS-1) = 2^2 = 4
		#define f8_EXPONENT_BITS	3
		#define f8_SIGN_BIT_MASK	(1 << (f8_EXPONENT_BITS + f8_MANTISSA_BITS)) // 0x80
		#define f8_EXPONENT_MASK	(((1 << f8_EXPONENT_BITS) - 1) << f8_MANTISSA_BITS) // 0x70
		#define f8_MANTISSA_MASK	(((1 << f8_MANTISSA_BITS) - 1) << 0) // 0x0F
		#define f8_signchar(x)	((x & f8_SIGN_BIT_MASK) ? '-' : '+')
		#define f8_signbit(x)	((x & f8_SIGN_BIT_MASK) ? -1 : +1)
		#define f8_exponent(x)	((x & f8_EXPONENT_MASK) >> f8_MANTISSA_BITS) - f8_EXPONENT_BIAS
		#define f8_mantissa(x)	((x & f8_MANTISSA_MASK) )
		#define f8_isnormal(x)	(f8_exponent(x) != -f8_EXPONENT_BIAS)
		#define f8_isnan(x)	(f8_exponent(x) == -f8_EXPONENT_BIAS && f8_mantissa(x) > 1)
		#define f8_isinf(x)	(f8_exponent(x) == -f8_EXPONENT_BIAS && f8_mantissa(x) < 2)
		printf("%04i = 0x%02X = 0b%c%c%c%c%c%c%c%c = %c0x1.%01Xp%+02i = %g\n",
			i, i,
			((i >> 7) & 1) ? '1' : '0',
			((i >> 6) & 1) ? '1' : '0',
			((i >> 5) & 1) ? '1' : '0',
			((i >> 4) & 1) ? '1' : '0',
			((i >> 3) & 1) ? '1' : '0',
			((i >> 2) & 1) ? '1' : '0',
			((i >> 1) & 1) ? '1' : '0',
			((i >> 0) & 1) ? '1' : '0',
			f8_signchar(i), f8_mantissa(i), f8_exponent(i),
			(f8_isnan(i) ? f8_signbit(i) * NAN :
			(f8_isinf(i) ? f8_signbit(i) * INFINITY :
				(f8_signbit(i) *
				(1. + f8_mantissa(i) / (double)f8_MANTISSA_SIZE) *
				pow(2, f8_exponent(i)))))
		);
	}
}
