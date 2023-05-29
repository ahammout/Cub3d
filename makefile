# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/28 14:50:41 by ahammout          #+#    #+#              #
#    Updated: 2023/05/29 00:56:42 by ahammout         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3d

CC = cc

# CFLAGS = -Wall -Wextra -Werror

INCLUDES = includes/cub3d.h

LIBFT = libft/libft.a

SRCS =	srcs/main.c \
		srcs/parser.c \

OBJS = $(SRCS:.c=.o)

%.o : %.c $(INCLUDES)
	@$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(INCLUDES) $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@make fclean -C libft
	@rm $(OBJS)

fclean: clean
	@make fclean -C libft
	@rm -fr $(NAME)

re: fclean all