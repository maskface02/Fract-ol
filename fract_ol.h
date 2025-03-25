#ifndef FRACT_OL
# define FRACT_OL

# define WIDTH 800
# define HEIGHT 800

# define MAX_ITER 50
# include "mlx_linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
	int		max_iteration;
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_x;
	double	julia_y;
	int		*palette;
	int		palette_size;
}			t_fractol;

int			ft_strncmp(char *s1, char *s2, size_t n);
void		init(t_fractol *f);
void		render(t_fractol *f);
double		julia(t_fractol *f, double zr, double zi);
void		print_err(char *mess, int is_syscall_func, int x);
double		mandelbrot(double cr, double ci);
double		tricorn(double cr, double ci);
double		ft_atod(char *s);
int			key_handler(int keysym, t_fractol *f);
int			mouse_handler(int button, int x, int y, t_fractol *f);
double		scale(double unscaled_num, double new_min, double new_max,
				double old_max);
int			clean_exit(t_fractol *f);
#endif
