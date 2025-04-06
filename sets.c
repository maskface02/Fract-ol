/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:49:20 by zatais            #+#    #+#             */
/*   Updated: 2025/04/01 20:52:58 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

double	mandelbrot(t_fractol *f, double cr, double ci)
{
	int	i;

	double (zr), (zi), (tmp), (log_zn), (nu);
	zr = 0;
	zi = 0;
	i = -1;
	while (++i < f->max_iterations)
	{
		if ((zr * zr + zi * zi) > 4.0)
			break ;
		tmp = 2 * zr * zi + ci;
		zr = zr * zr - zi * zi + cr;
		zi = tmp;
	}
	if (i < f->max_iterations)
	{
		log_zn = log(zr * zr + zi * zi) / 2.0;
		nu = log(log_zn / log(2)) / log(2);
		return (i + 1 - nu);
	}
	return (i);
}

double	julia(t_fractol *f, double zr, double zi)
{
	int		i;
	double	tmp;
	double	log_zn;
	double	nu;

	i = -1;
	while (++i < f->max_iterations)
	{
		if ((zi * zi + zr * zr) > 4.0)
			break ;
		tmp = 2 * zr * zi + f->julia_y;
		zr = zr * zr - zi * zi + f->julia_x;
		zi = tmp;
	}
	if (i < f->max_iterations)
	{
		log_zn = log(zr * zr + zi * zi) / 2.0;
		nu = log(log_zn / log(2)) / log(2);
		return (i + 1 - nu);
	}
	return (i);
}

double	tricorn(t_fractol *f, double cr, double ci)
{
	int	i;

	double (zr), (zi), (tmp), (log_zn), (nu);
	zr = cr;
	zi = ci;
	i = -1;
	while (++i < f->max_iterations)
	{
		if ((zr * zr + zi * zi) > 4.0)
			break ;
		tmp = -2 * zr * zi + ci;
		zr = zr * zr - zi * zi + cr;
		zi = tmp;
	}
	if (i < f->max_iterations)
	{
		log_zn = log(zr * zr + zi * zi) / 2.0;
		nu = log(log_zn / log(2)) / log(2);
		return (i + 1 - nu);
	}
	return (i);
}
