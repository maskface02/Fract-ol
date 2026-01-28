/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:48:53 by zatais            #+#    #+#             */
/*   Updated: 2025/04/01 22:59:10 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# define WIDTH 800
# define HEIGHT 800
# define NUM_THREADS 8

//# define MAX_ITER 100
# include "/usr/include/minilibx-linux/minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_fractol
{
	char	*name;
	void	*mlx;
	void	*win;
	void	*img;
	char	*data_addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		max_iterations;
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_x;
	double	julia_y;
	int		*palette;
	int		palette_size;
	int		i;
	int		mouse_track;
}			t_fractol;

typedef struct s_thread_data
{
	t_fractol	*f;
	int			start_y;
	int			end_y;
}				t_thread_data;

int			ft_strncmp(char *s1, char *s2, size_t n);
void		init(t_fractol *f);
void		render(t_fractol *f);
double		julia(t_fractol *f, double zr, double zi);
void		print_err(char *mess, int is_syscall_func, int x);
double		mandelbrot(t_fractol *f, double cr, double ci);
double		tricorn(t_fractol *f, double cr, double ci);
double		ft_atod(char *s);
int			key_handler(int keysym, t_fractol *f);
int			mouse_handler(int button, int x, int y, t_fractol *f);
int			mouse_move(int x, int y, t_fractol *f);
double		scale(double unscaled_num, double new_min, double new_max,
				double old_max);
int			clean_exit(t_fractol *f);
void		init_palette(t_fractol *f);
#endif
