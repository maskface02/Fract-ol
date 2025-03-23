#ifndef FRACT_OL
# define FRACT_OL

# define WIDTH 800
# define HEIGHT 800
# define BLACK 0x000000
# define WHITE 0xFFFFFF
#define MAX_ITER 50
# include "mlx_linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <limits.h>

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
	float	shift_x;
	float	shift_y;
	float	zoom;
	float	julia_x;
	float	julia_y;
}			t_fractol;

int	ft_strncmp(char *s1, char *s2, size_t n);
void		init(t_fractol *f);
void	render(t_fractol *f);
int	julia(t_fractol *f, float zr, float zi);
void	print_err(char *mess, int is_syscall_func, int x);
int	mandelbrot(float cr, float ci);
int	tricorn(float cr, float ci);
double	ft_atod(char *s);
#endif
