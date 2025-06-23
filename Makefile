# # **************************************************************************** #
# #                                                                              #
# #                                                         :::      ::::::::    #
# #    Makefile                                           :+:      :+:    :+:    #
# #                                                     +:+ +:+         +:+      #
# #    By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+         #
# #                                                 +#+#+#+#+#+   +#+            #
# #    Created: 2025/01/20 13:38:18 by abdsebba          #+#    #+#              #
# #    Updated: 2025/02/02 15:48:12 by abdsebba         ###   ########.fr        #
# #                                                                              #
# # **************************************************************************** #

# SRC = 2d_array.c check_map.c creat_window.c ft_split.c get_next_line.c get_next_line_utils.c so_long.c handle_map.c Error_print.c \
# 	putnbr.c put_texture.c

# OBJ = $(SRC:.c=.o)
# CC = gcc
# CFLAGS = -Wall -Wextra -Werror
# NAME = so_long

# all: $(NAME)

# $(NAME): $(OBJ)
# 	$(CC) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

# %.o: %.c so_long.h
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	rm -f $(OBJ)

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all

# .PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/20 13:38:18 by abdsebba          #+#    #+#              #
#    Updated: 2025/02/02 15:48:12 by abdsebba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = 2d_array.c check_map.c creat_window.c ft_split.c get_next_line.c \
	get_next_line_utils.c so_long.c handle_map.c Error_print.c \
	putnbr.c put_texture.c

OBJ = $(SRC:.c=.o)
		CC = cc
		CFLAGS = -Wall -Wextra -Werror -I./minilibx-linux

NAME = so_long

MLX_DIR = ./minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJ) $(MLX_LIB)
				$(CC) $(OBJ) $(MLX_FLAGS) -o $(NAME)

%.o: %.c so_long.h
				$(CC) $(CFLAGS) -c $< -o $@

$(MLX_LIB):
				$(MAKE) -C $(MLX_DIR)

clean:
				rm -f $(OBJ)
						$(MAKE) -C $(MLX_DIR) clean

fclean: clean
				rm -f $(NAME)

re: fclean all