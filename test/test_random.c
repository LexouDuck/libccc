
#include "libft_stat.h"
#include "libft_random.h"

#include "test.h"



int		test_random(void)
{

printf("\n");

	printf("       .----------------------------.       \n");
	printf("---==={   LIBFT TEST: libft_random   }===---\n");
	printf("       '----------------------------'       \n");

printf("\n");

	ft_random_renew_seed();

	t_u32				sample_nb = 20000;
	printf("Stat test of rng, sample size: %d\n", sample_nb);

	t_list_int			i_lst;
	t_sortedlist_int	si_lst;
	t_u64				intmax = (t_u32)-1;
	t_float				tmp;
	t_float				decile_inc = sample_nb / 10.;


	i_lst = ft_stat_new_ilst(sample_nb);

	for (int i = 0; i < i_lst.len; ++i)
		i_lst.data[i] = ft_random_int_a_to_b(-500, 501);

/*	static t_int arr[5] = {-339, 214, 394, -162, -50};//{-339, -162, -50, 214, 394};
	for (int i = 0; i < i_lst.len; ++i)
		i_lst.data[i] = arr[i];

	for (int i = 0; i < i_lst.len; ++i)
		printf("%d, ", i_lst.data[i]);
	printf("\n");
*/
	printf("Quicksorting...\n");
	si_lst = ft_stat_quicksort_i_new(i_lst);
	printf("Done !\n");

	return (OK);
}
