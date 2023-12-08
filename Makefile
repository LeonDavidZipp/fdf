# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 12:42:09 by lzipp             #+#    #+#              #
#    Updated: 2023/12/08 11:19:00 by lzipp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= fdf

cc := gcc

CFLAGS	:= -Wextra -Wall -Werror

LIBMLX	:= ./scr/MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include

LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SOURCEDIR	:= ./src

SOURCES	:= $(SOURCEDIR)/fractol.c \
$(SOURCEDIR)/hooks.c \
$(SOURCEDIR)/julia.c \
$(SOURCEDIR)/mandelbrot.c

OBJECTS	:= ${SOURCES:.c=.o}

all: libmlx $(NAME)

libft:
	@make -C ./lib/libft

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJECTS) libft
	@$(CC) $(OBJECTS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@make -C ./lib/libft clean
	@rm -rf $(OBJECTS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@make -C ./lib/libft fclean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
