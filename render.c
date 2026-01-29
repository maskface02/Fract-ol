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

	n = 0.0;
	if (!ft_strncmp(f->name, "M", 1))
		n = mandelbrot(f, pr, pi);
	else if (!ft_strncmp(f->name, "J", 1))
		n = julia(f, pr, pi);
	else if (!ft_strncmp(f->name, "T", 1))
		n = tricorn(f, pr, pi);
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

static int	get_pixel_color(t_fractol *f, double nb_iter)
{
	int (idx1), (idx2);
	double (t), (fraction);

	if (nb_iter >= f->max_iterations)
		return (0x000000);
	t = fmod(nb_iter / f->max_iterations * (f->palette_size - 1),
			f->palette_size - 1);
	idx1 = (int)t;
	idx2 = (idx1 + 1) % f->palette_size;
	fraction = t - idx1;
	return (lerp(f->palette[idx1], f->palette[idx2], fraction));
}

static void	*render_thread(void *arg)
{
	t_thread_data	*data;
	t_fractol		*f;
	int				x;
	int				y;

	double (pr), (pi), (nb_iter);
	data = (t_thread_data *)arg;
	f = data->f;
	y = data->start_y - 1;
	while (++y < data->end_y)
	{
		x = -1;
		while (++x < WIDTH)
		{
			pr = (scale(x, -2, 2, WIDTH) * f->zoom) + f->shift_x;
			pi = (scale(y, -2, 2, HEIGHT) * f->zoom) + f->shift_y;
			nb_iter = calculate_iterations(f, pr, pi);
			my_put_pixel(f, x, y, get_pixel_color(f, nb_iter));
		}
	}
	return (NULL);
}

void	render(t_fractol *f)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	thread_data[NUM_THREADS];
	int				i;
	int				rows_per_thread;

	rows_per_thread = HEIGHT / NUM_THREADS;
	i = -1;
	while (++i < NUM_THREADS)
	{
		thread_data[i].f = f;
		thread_data[i].start_y = i * rows_per_thread;
		if (i == NUM_THREADS - 1)
			thread_data[i].end_y = HEIGHT;
		else
			thread_data[i].end_y = (i + 1) * rows_per_thread;
		pthread_create(&threads[i], NULL, render_thread, &thread_data[i]);
	}
	i = -1;
	while (++i < NUM_THREADS)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}
