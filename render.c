#include "fract_ol.h"

float	scale_between(float unscaled_num, float new_min, float new_max,
		float old_min, float old_max)
{
	return ((new_max - new_min) * (unscaled_num - old_min) / (old_max - old_min)
		+ new_min);
}

int	calculate_iterations(t_fractol *f, float pr, float pi)
{
	int	n;

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

void	render(t_fractol *f)
{
	int		x;
	int		y;
	float	pr;
	float	pi;
	int		nb_iter;
	int		color;
	int		t;

	mlx_clear_window(f->mlx, f->win);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			pr = (scale_between(x, -2, 2, 0, WIDTH) * f->zoom) + f->shift_x;
			pi = (scale_between(y, 2, -2, 0, HEIGHT) * f->zoom) + f->shift_y;
			nb_iter = calculate_iterations(f, pr, pi);
			t = (float)nb_iter / MAX_ITER * 255;
			color = (t << 16) | (t << 8) | t;
			// color = scale_between(nb_iter, BLACK, WHITE, 1, MAX_ITER);
			my_put_pixel(f, x, y, color);
		}
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}
