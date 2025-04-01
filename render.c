/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:49:11 by zatais            #+#    #+#             */
/*   Updated: 2025/04/01 20:53:37 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

double	scale(double unscaled_num, double new_min, double new_max,
		double old_max)
{
	return (((new_max - new_min) * (unscaled_num) / old_max) + new_min);
}

double	calculate_iterations(t_fractol *f, double pr, double pi)
{
	double	n;

	if (!ft_strncmp(f->name, "M", 1))
		n = mandelbrot(pr, pi);
	else if (!ft_strncmp(f->name, "J", 1))
		n = julia(f, pr, pi);
	else if (!ft_strncmp(f->name, "T", 1))
		n = tricorn(pr, pi);
	return (n);
}

void	my_put_pixel(t_fractol *f, int x, int y, int color)
{
	char	*pixel;

	pixel = f->data_addr + (y * f->size_line) + (x * (f->bpp / 8));
	*(int *)pixel = color;
}

int	lerp(int color1, int color2, double fraction)
{
	int (r1), (r2), (r), (g1), (g2), (g), (b1), (b2), (b);
	r1 = (color1 >> 16) & 0xFF;
	g1 = (color1 >> 8) & 0xFF;
	b1 = color1 & 0xFF;
	r2 = (color2 >> 16) & 0xFF;
	g2 = (color2 >> 8) & 0xFF;
	b2 = color2 & 0xFF;
	r = (int)(r1 + (r2 - r1) * fraction);
	g = (int)(g1 + (g2 - g1) * fraction);
	b = (int)(b1 + (b2 - b1) * fraction);
	return ((r << 16) | (g << 8) | b);
}

void	render(t_fractol *f)
{
	int (x), (y), (color), (idx1), (idx2);
	double (pr), (pi), (nb_iter), (t), (fraction);
	(1) && (y = -1, mlx_clear_window(f->mlx, f->win));
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			pr = (scale(x, -2, 2, WIDTH) * f->zoom) + f->shift_x;
			pi = (scale(y, -2, 2, HEIGHT) * f->zoom) + f->shift_y;
			nb_iter = calculate_iterations(f, pr, pi);
			if (nb_iter >= MAX_ITER)
				color = 0x000000;
			else
			{
				t = fmod(nb_iter / MAX_ITER * (f->palette_size - 1),
						f->palette_size - 1);
				(1) && (idx1 = (int)t, idx2 = (idx1 + 1) % f->palette_size,
					fraction = t - idx1);
				color = lerp(f->palette[idx1], f->palette[idx2], fraction);
			}
			my_put_pixel(f, x, y, color);
		}
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}
