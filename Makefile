SRCS =	fractol.c init.c render.c sets.c utils.c events.c

OBJS = $(SRCS:.c=.o)
CC = cc -g
CFLAGS = -Wall -Wextra -Werror -Imlx_linux
LFLAGS = -Lmlx_linux -lmlx_Linux -lXext -lX11 -lm
RM = rm -f
NAME = fract_ol

all: $(NAME)

$(NAME): fract_ol.h $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean