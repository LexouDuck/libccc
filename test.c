
#include <math.h>
#include <stdio.h>

#include "libft.h"
#include "libft_math.h"
#include "libft_convert.h"



#define F_LIBFT(x)		ft_nrt(x,    7)
#define F_LIBC(x)		   pow(x, 1./7)

int main(int argc, char** argv)
{
	t_float result_libft;
	t_float result_libc;
	t_float difference;
	t_float largest = 0;
	t_float sum = 0;
	t_float x;
	int i = 1;

	if (argc == 1)
	{
		i = 0;
		x = 0.00000000001;
		while (i <= 200)
		{
			result_libft = F_LIBFT(x);
			result_libc	 = F_LIBC(x);
			difference = fabs(result_libft - result_libc);
			if (largest < difference)
				largest = difference;
			printf("%f -> ft: %f | c: %f \t-> difference: %f\n", x, result_libft, result_libc, difference);
			if (!IS_NAN(difference) && result_libft != result_libc)
				sum += difference;
			++i;
			x += x;
		}
		printf("largest difference was:%f\n\ntotal difference: %f\n", largest, sum);
	}
	else
	{
		while (i < argc)
		{
			x = FT_String_To_F64(argv[i]);
			result_libft = F_LIBFT(x);
			result_libc	 = F_LIBC(x);
			difference = fabs(result_libft - result_libc);
			if (largest < difference)
				largest = difference;
			printf("%f -> ft: %f | c: %f \t-> difference: %f\n", x, result_libft, result_libc, difference);
			++i;
		}
	}
}