# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zatais <zatais@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/01 20:49:08 by zatais            #+#    #+#              #
#    Updated: 2025/04/01 20:49:09 by zatais           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	fractol.c init.c render.c sets.c utils.c events.c

OBJS = $(SRCS:.c=.o)
CC = cc -g
CFLAGS = -Wall -Wextra -Werror
LFLAGS =  -L/usr/include/minilibx-linux -lmlx -lXext -lX11 -lm -pthread
RM = rm -f
NAME = fractol

all: $(NAME)

$(NAME): fract_ol.h $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean
