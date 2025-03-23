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

void	init(t_fractol *f)
{
	f->mlx = mlx_init();
	if (!f->mlx)
		print_err("Error Connecting To Graphics Server", 0, 1);
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, f->name);
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
}
