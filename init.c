/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:49:02 by zatais            #+#    #+#             */
/*   Updated: 2025/04/01 22:57:51 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	print_err(char *mess, int is_syscall_func, int x)
{
	if (!is_syscall_func)
		ft_putstr_fd(mess, 2);
	else
		perror(mess);
	if (x)
		exit(1);
}

void	init_palette(t_fractol *f)
{
	static int	palettes[8][6] = {{0x000000, 0x3300FF, 0xFF00FF, 0xFF0000,
		0xFF6600, 0xFFFF00}, {0x000033, 0x0000FF, 0x00FFFF, 0xFFFFFF, -1},
	{0xFF00FF, 0x00FF00, 0xFFFF00, 0xFF0000, 0x0000FF, -1}, {0x002200,
		0x005500, 0x008800, 0x00BB00, 0x00FF00, -1}, {0x2E004F, 0x8A2BE2,
		0xFF4500, 0xFFD700, 0xFFFFFF, -1}, {0x000000, 0x4B0082, 0x8A2BE2,
		0x00FFFF, 0xFFFFFF, -1}, {0x00FF00, 0xFF00FF, 0x0000FF, 0xFF0000,
		0xFFFF00, -1}, {0x000000, 0x332200, 0x664400, 0x996600, 0xCC8800,
		0xFFAA00}};
	static int	palette_sizes[8] = {6, 4, 5, 5, 5, 5, 5, 6};

	if (f->i >= 0 && f->i < 8)
	{
		f->palette = palettes[f->i];
		f->palette_size = palette_sizes[f->i];
	}
}

void	init(t_fractol *f)
{
	f->mlx = mlx_init();
	if (!f->mlx)
		print_err("Error Connecting To Graphics Server", 0, 1);
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "Fract-ol");
	if (!f->win)
	{
		mlx_destroy_display(f->mlx);
		free(f->mlx);
		print_err("Error Initializing Window", 0, 1);
	}
	f->img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	if (!f->img)
	{
		mlx_destroy_display(f->mlx);
		mlx_destroy_window(f->win, f->mlx);
		free(f->mlx);
		print_err("Error Initializing Image", 0, 1);
	}
	f->data_addr = mlx_get_data_addr(f->img, &f->bpp, &f->size_line,
			&f->endian);
	f->shift_x = 0.0;
	f->shift_y = 0.0;
	f->zoom = 1.0;
	f->i = 0;
	init_palette(f);
}
