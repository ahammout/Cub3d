# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: verdant <verdant@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/28 14:50:41 by ahammout          #+#    #+#              #
#    Updated: 2023/07/10 20:39:50 by verdant          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET := cub3D
LIBFT    := lib/libft/libft.a
MLX42    := lib/MLX42/build/libmlx42.a
SRC_DIR := srcs/
OBJ_DIR := obj/
CC 		:= gcc
CFLAGS := -Wunreachable-code -Ofast -Wall -Wextra -Werror
LIBPATH  :=	-L/Users/ahammout/homebrew/opt/glfw/lib -lglfw 
# LIBPATH  :=  -L/Users/mwilsch/.brew/opt/glfw/lib -lglfw
LIBPATH  := -L/opt/homebrew/opt/glfw/lib -lglfw
MACOS := -framework Cocoa -framework OpenGL -framework IOKit
MLXFLAGS := $(MLX42) $(MACOS)  $(LIBPATH) -ldl -pthread -lm
INC      := -I includes/ -I lib/MLX42/include

SRC := $(wildcard $(SRC_DIR)*.c $(SRC_DIR)*/*.c)
OBJ := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

## Debugging ##
ifdef DEBUG
		CFLAGS += -g -fsanitize=address
endif

all: $(TARGET)

$(TARGET): $(OBJ) $(LIBFT) $(MLX42)
	@$(CC) $(CFLAGS) $(MLXFLAGS) $^ -o $@
	@echo "$(GREEN)Executable created.$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c includes/*.h
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT):
	@echo "$(GREEN)Building libft ...$(RESET)"
	@$(MAKE) -C lib/libft

$(MLX42):
	@echo "$(GREEN)Building MLX42 ...$(RESET)"
	@cd lib/MLX42 && cmake -B build && cmake --build build -j4 

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C lib/libft fclean
	@$(MAKE) -C lib/MLX42/build clean
	@echo "$(RED)Object files removed.$(RESET)"

fclean: clean
	@rm -f $(TARGET)
	@echo "$(RED)Executable removed.$(RESET)"

re: fclean all

























# NAME = Cub3d

# CC = cc

# CFLAGS = -Wall -Wextra -Werror

# INCLUDES = includes/cub3d.h

# LIBFT = libft/libft.a

# SRCS =	srcs/main.c \
# 		srcs/parser.c \
# 		srcs/parse_directions.c \
# 		srcs/parse_fc.c \
# 		srcs/parser_tools.c \
# 		srcs/parse_map.c \
# 		srcs/analyze_map.c \
# 		srcs/tools.c \
# 		get_next_line/get_next_line.c \

# OBJS = $(SRCS:.c=.o)

# %.o : %.c $(INCLUDES)
# 	$(CC) $(CFLAGS) -c $< -o $@

# all : $(NAME)

# $(NAME) : $(INCLUDES) $(OBJS)
# 	@make -C libft
# 	$(CC) $(CFLAGS) $(OBJS) $(LIBFT)   -o $(NAME)

# clean:
# 	@make fclean -C libft
# 	@rm -fr $(OBJS)

# fclean: clean
# 	@make fclean -C libft
# 	@rm -fr $(NAME)

# re: fclean all