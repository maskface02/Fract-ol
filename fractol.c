#include "fract_ol.h"

void	usage(void)
{
	print_err("Usage : \n", 0, 0);
	print_err("./fractol < set_type M or J or T >", 0, 0);
	print_err(" if set is JULIA ./fractol J <real> <imag> \n", 0, 1);
}

int	main(int ac, char **av)
{
	t_fractol	f;

	if (ac >= 2 && ac <= 4 && (!ft_strncmp(av[1], "M", 2) || !ft_strncmp(av[1],
				"J", 2) || !ft_strncmp(av[1], "T", 2)))
	{
		f.name = av[1];
		if (!ft_strncmp(f.name, "J", 1) && av[2] && av[3])
		{
			if (ft_atod(av[2]) == __DBL_MAX__ || ft_atod(av[3]) == __DBL_MAX__)
				usage();
			else
			{
				f.julia_x = ft_atod(av[2]);
				f.julia_y = ft_atod(av[3]);
			}
		}
		init(&f);
		render(&f);
		mlx_loop(f.mlx);
	}
	else
		usage();
}
