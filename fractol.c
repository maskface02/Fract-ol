/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:48:56 by zatais            #+#    #+#             */
/*   Updated: 2025/04/01 20:48:58 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void	usage(void)
{
	print_err("Usage : \n", 0, 0);
	print_err("./fractol < set_type M or J or T >\n", 0, 0);
	print_err(" if set is JULIA ./fractol J <real> <imag> \n", 0, 1);
}

int	check_errors(char *av)
{
	int (i), (comma), (errors), (comma_index);
	(1) && (i = -1, comma = 0, errors = 0);
	while (av[++i])
	{
		if (av[i] == '.')
			(1) && (comma_index = i, comma += 1);
	}
	i = 0;
	if (av[i] == '-' || av[i] == '+')
		i++;
	while (av[i])
	{
		if (i == comma_index)
		{
			++i;
			continue ;
		}
		if (!(av[i] >= '0' && av[i] <= '9' && comma <= 1))
			errors += 1;
		i++;
	}
	if (errors)
		return (0);
	return (1);
}

int	check_julia(char **av)
{
	int	i;

	i = 0;
	if (!av[2] || !av[3])
		return (0);
	if (!check_errors(av[2]) || !check_errors(av[3]))
		return (0);
	if (ft_atod(av[2]) > 2 || ft_atod(av[3]) > 2)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_fractol	f;

	if (ac >= 2 && ac <= 4 && (!ft_strncmp(av[1], "M", 2) || !ft_strncmp(av[1],
				"J", 2) || !ft_strncmp(av[1], "T", 2)))
	{
		f.name = av[1];
		if (!ft_strncmp(f.name, "J", 1) && check_julia(av))
		{
			f.julia_x = ft_atod(av[2]);
			f.julia_y = ft_atod(av[3]);
		}
		else
			print_err("aaa", 0, 1);
		init(&f);
		render(&f);
		mlx_hook(f.win, 17, 0, clean_exit, &f);
		mlx_key_hook(f.win, key_handler, &f);
		mlx_mouse_hook(f.win, mouse_handler, &f);
		mlx_loop(f.mlx);
	}
	else
		usage();
}
