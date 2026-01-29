/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:48:35 by zatais            #+#    #+#             */
/*   Updated: 2025/04/01 20:48:38 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

int	key_handler(int keysym, t_fractol *f)
{
	if (keysym == XK_Escape)
		clean_exit(f);
	else if (keysym == XK_Right)
		f->shift_x += (0.1 * f->zoom);
	else if (keysym == XK_Left)
		f->shift_x -= (0.1 * f->zoom);
	else if (keysym == XK_Down)
		f->shift_y += (0.1 * f->zoom);
	else if (keysym == XK_Up)
		f->shift_y -= (0.1 * f->zoom);
	else if (keysym == 45)
		f->i = (f->i + 1) % 8;
	else if (keysym == 61)
		f->i = (f->i - 1 + 8) % 8;
	else if (keysym == XK_space)
		f->mouse_track = !f->mouse_track;
	init_palette(f);
	render(f);
	return (0);
}

int	clean_exit(t_fractol *f)
{
	mlx_destroy_image(f->mlx, f->img);
	mlx_destroy_window(f->mlx, f->win);
	mlx_destroy_display(f->mlx);
	free(f->mlx);
	exit(0);
}

int	mouse_handler(int button, int x, int y, t_fractol *f)
{
	double	mouse_re;
	double	mouse_im;
	double	zoom_factor;

	mouse_re = (scale(x, -2, 2, WIDTH) * f->zoom) + f->shift_x;
	mouse_im = (scale(y, -2, 2, HEIGHT) * f->zoom) + f->shift_y;
	if (button == Button5)
	{
		zoom_factor = 1.1;
		f->shift_x = mouse_re - (mouse_re - f->shift_x) * zoom_factor;
		f->shift_y = mouse_im - (mouse_im - f->shift_y) * zoom_factor;
		f->zoom *= zoom_factor;
	}
	else if (button == Button4)
	{
		zoom_factor = 1.0 / 1.1;
		f->shift_x = mouse_re - (mouse_re - f->shift_x) * zoom_factor;
		f->shift_y = mouse_im - (mouse_im - f->shift_y) * zoom_factor;
		f->zoom *= zoom_factor;
	}
	render(f);
	return (0);
}

int	mouse_move(int x, int y, t_fractol *f)
{
	if (!ft_strncmp(f->name, "J", 1) && f->mouse_track)
	{
		f->julia_x = scale(x, -2, 2, WIDTH);
		f->julia_y = scale(y, -2, 2, HEIGHT);
		render(f);
	}
	return (0);
}
