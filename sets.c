#include "fract_ol.h"

int	mandelbrot(float cr, float ci)
{
	int		i;
	float	zr;
	float	zi;
	float	tmp;

	zr = 0;
	zi = 0;
	i = 0;
	while (i < MAX_ITER)
	{
		if ((zr * zr + zi * zi) > 4.0)
			break ;
		tmp = 2 * zr * zi + ci;
		zr = zr * zr - zi * zi + cr;
		zi = tmp;
		i++;
	}
	return (i);
}

int	julia(t_fractol *f, float zr, float zi)
{
	int		i;
	float	tmp;

	i = -1;
	while (++i < MAX_ITER)
	{
		if ((zi * zi + zr * zr) > 4.0)
			break ;
		tmp = 2 * zr * zi + f->julia_x;
		zr = zr * zr - zi * zi + f->julia_y;
		zi = tmp;
	}
	return (i);
}

int	tricorn(float cr, float ci)
{
	int		i;
	float	zr;
	float	zi;
	float	tmp;

	zr = cr;
	zi = ci;
	i = -1;
	while (++i < MAX_ITER)
	{
		if ((zr * zr + zi * zi) > 4.0)
			break ;
		tmp = -2 * zr * zi + ci;
		zr = zr * zr - zi * zi + cr;
		zi = tmp;
	}
	return (i);
}
