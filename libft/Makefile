# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 18:34:16 by ahammout          #+#    #+#              #
#    Updated: 2023/05/28 16:32:59 by ahammout         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -c -Wall -Wextra -Werror

ARCHC = ar rc

INCLUDES = includes/libft.h

OBJDIR = objs

SRCS = srcs/ft_isalpha.c \
	   srcs/ft_isdigit.c \
	   srcs/ft_isalnum.c \
	   srcs/ft_isascii.c \
	   srcs/ft_bzero.c \
	   srcs/ft_isprint.c \
	   srcs/ft_tolower.c \
	   srcs/ft_toupper.c \
	   srcs/ft_strlen.c \
	   srcs/ft_memcpy.c \
	   srcs/ft_memchr.c \
	   srcs/ft_memcmp.c \
	   srcs/ft_memcpy.c \
	   srcs/ft_memmove.c \
	   srcs/ft_memset.c \
	   srcs/ft_strchr.c \
	   srcs/ft_strlcat.c \
	   srcs/ft_strlcpy.c \
	   srcs/ft_strncmp.c \
	   srcs/ft_strnstr.c \
	   srcs/ft_strrchr.c \
	   srcs/ft_atoi.c \
	   srcs/ft_calloc.c \
	   srcs/ft_strdup.c \
	   srcs/ft_substr.c \
	   srcs/ft_strjoin.c \
	   srcs/ft_strtrim.c \
	   srcs/ft_split.c \
	   srcs/ft_itoa.c \
	   srcs/ft_strmapi.c \
	   srcs/ft_striteri.c \
	   srcs/ft_putchar_fd.c \
	   srcs/ft_putstr_fd.c \
	   srcs/ft_putendl_fd.c \
	   srcs/ft_putnbr_fd.c \

OBJS = $(patsubst SRCS/%.c,OBJDIR/%.o,$(SRCS))

$(OBJDIR)%.o : $(SRCS)%.c $(INCLUDES)
	@$(CC) $(CFLAGS) $< -o $@

all : $(NAME)

$(NAME) : $(OBJS) $(INCLUDES)
	@$(CC) $(CFLAGS) $(SRCS)
	@$(ARCHC) $(NAME) $(OBJS)
	@mv *.o $(OBJDIR)

clean :
	@rm -rf $(OBJDIR)/*.o

fclean : clean
	@rm -rf $(NAME)

re : fclean all
