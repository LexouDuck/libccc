#include <math.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>

int main()
{
	for (uint16_t i = 1; i != 0; ++i)
	{
		#define f16_MANTISSA_SIZE	1024 // 2^MANTISSA_BITS = 2^10 = 1024
		#define f16_MANTISSA_BITS	10
		#define f16_EXPONENT_BIAS	16 // 2^(EXPONENT_BITS-1) = 2^4 = 16
		#define f16_EXPONENT_BITS	5
		#define f16_SIGN_BIT_MASK	(1 << (f16_EXPONENT_BITS + f16_MANTISSA_BITS)) // 0x8000
		#define f16_EXPONENT_MASK	(((1 << f16_EXPONENT_BITS) - 1) << f16_MANTISSA_BITS) // 0x7C00
		#define f16_MANTISSA_MASK	(((1 << f16_MANTISSA_BITS) - 1) << 0) // 0x03FF
		#define f16_signchar(x)	((x & f16_SIGN_BIT_MASK) ? '-' : '+')
		#define f16_signbit(x)	((x & f16_SIGN_BIT_MASK) ? -1 : +1)
		#define f16_exponent(x)	((x & f16_EXPONENT_MASK) >> f16_MANTISSA_BITS) - f16_EXPONENT_BIAS
		#define f16_mantissa(x)	((x & f16_MANTISSA_MASK) )
		#define f16_isnormal(x)	(f16_exponent(x) != -f16_EXPONENT_BIAS)
		#define f16_isnan(x)	(f16_exponent(x) == -f16_EXPONENT_BIAS && f16_mantissa(x) > 1)
		#define f16_isinf(x)	(f16_exponent(x) == -f16_EXPONENT_BIAS && f16_mantissa(x) < 2)
		printf("%08i = 0x%04X = 0b%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c = %c0x1.%02Xp%+04i = %g\n",
			i, i,
			((i >> 0xF) & 1) ? '1' : '0',
			((i >> 0xE) & 1) ? '1' : '0',
			((i >> 0xD) & 1) ? '1' : '0',
			((i >> 0xC) & 1) ? '1' : '0',
			((i >> 0xB) & 1) ? '1' : '0',
			((i >> 0xA) & 1) ? '1' : '0',
			((i >> 0x9) & 1) ? '1' : '0',
			((i >> 0x8) & 1) ? '1' : '0',
			((i >> 0x7) & 1) ? '1' : '0',
			((i >> 0x6) & 1) ? '1' : '0',
			((i >> 0x5) & 1) ? '1' : '0',
			((i >> 0x4) & 1) ? '1' : '0',
			((i >> 0x3) & 1) ? '1' : '0',
			((i >> 0x2) & 1) ? '1' : '0',
			((i >> 0x1) & 1) ? '1' : '0',
			((i >> 0x0) & 1) ? '1' : '0',
			f16_signchar(i), f16_mantissa(i), f16_exponent(i),
			(f16_isnan(i) ? f16_signbit(i) * NAN :
			(f16_isinf(i) ? f16_signbit(i) * INFINITY :
				(f16_signbit(i) *
				(1. + f16_mantissa(i) / (double)f16_MANTISSA_SIZE) *
				pow(2, f16_exponent(i)))))
		);
	}
}
