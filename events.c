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
	{
		f->shift_x += (0.5 * f->zoom);
		f->max_iterations += 10;
	}
	else if (keysym == XK_Left)
	{
		f->shift_x -= (0.5 * f->zoom);
		f->max_iterations -= 10;
	}
	else if (keysym == XK_Down)
		f->shift_y += (0.5 * f->zoom);
	else if (keysym == XK_Up)
		f->shift_y -= (0.5 * f->zoom);
	else if (keysym == 45)
		f->i = (f->i + 1) % 8;
	else if (keysym == 61)
		f->i = (f->i - 1 + 8) % 8;
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
	(void)x;
	(void)y;
	if (button == Button5)
		f->zoom *= 1.05;
	if (button == Button4)
		f->zoom *= 0.95;
	render(f);
	return (0);
}
