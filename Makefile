# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 12:42:09 by lzipp             #+#    #+#              #
#    Updated: 2024/01/18 18:30:07 by lzipp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= fdf

cc := gcc
CFLAGS	:= -Wextra -Wall -Werror

LIBMLX	:= ./lib/MLX42
HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

GETNEXTLINEDIR	:= ./lib/get_next_line
GETNEXTLINESOURCES = $(GETNEXTLINEDIR)/get_next_line.c $(GETNEXTLINEDIR)/get_next_line_utils.c
GETNEXTLINEOBJECTS = ${GETNEXTLINESOURCES:.c=.o}

SOURCEDIR	:= ./src
SOURCES = $(SOURCEDIR)/free_functions.c \
$(SOURCEDIR)/make_map.c \
$(SOURCEDIR)/mlx_hooks.c \
$(SOURCEDIR)/color_conversion.c \
$(SOURCEDIR)/make_window.c \
$(SOURCEDIR)/drawing_functions.c \
$(SOURCEDIR)/isometric_transform.c \
$(SOURCEDIR)/main.c
OBJECTS	:= ${SOURCES:.c=.o} $(GETNEXTLINEOBJECTS)

LIBFTDIR	:= ./lib/libft
LIBFT		:= $(LIBFTDIR)/libft.a
LIBFTSOURCES = SOURCES = $(LIBFTDIR)/ft_lstclear_bonus.c \
$(LIBFTDIR)/ft_null_terminated_arr_len.c \
$(LIBFTDIR)/ft_strlcpy.c \
$(LIBFTDIR)/ft_atoi.c \
$(LIBFTDIR)/ft_lstdelone_bonus.c \
$(LIBFTDIR)/ft_putchar_fd.c \
$(LIBFTDIR)/ft_strlen.c \
$(LIBFTDIR)/ft_bzero.c \
$(LIBFTDIR)/ft_lstiter_bonus.c \
$(LIBFTDIR)/ft_putendl_fd.c \
$(LIBFTDIR)/ft_strmapi.c \
$(LIBFTDIR)/ft_calloc.c \
$(LIBFTDIR)/ft_lstlast_bonus.c \
$(LIBFTDIR)/ft_putnbr_fd.c \
$(LIBFTDIR)/ft_strncmp.c \
$(LIBFTDIR)/ft_isalnum.c \
$(LIBFTDIR)/ft_lstmap_bonus.c \
$(LIBFTDIR)/ft_putstr_fd.c \
$(LIBFTDIR)/ft_strnstr.c \
$(LIBFTDIR)/ft_isalpha.c \
$(LIBFTDIR)/ft_lstnew_bonus.c \
$(LIBFTDIR)/ft_recalloc.c \
$(LIBFTDIR)/ft_strrchr.c \
$(LIBFTDIR)/ft_isascii.c \
$(LIBFTDIR)/ft_lstsize_bonus.c \
$(LIBFTDIR)/ft_split.c \
$(LIBFTDIR)/ft_strrncmp.c \
$(LIBFTDIR)/ft_isdigit.c \
$(LIBFTDIR)/ft_memchr.c \
$(LIBFTDIR)/ft_strchr.c \
$(LIBFTDIR)/ft_strtrim.c \
$(LIBFTDIR)/ft_isprint.c \
$(LIBFTDIR)/ft_memcmp.c \
$(LIBFTDIR)/ft_strdup.c \
$(LIBFTDIR)/ft_substr.c \
$(LIBFTDIR)/ft_itoa.c \
$(LIBFTDIR)/ft_memcpy.c \
$(LIBFTDIR)/ft_striteri.c \
$(LIBFTDIR)/ft_tolower.c \
$(LIBFTDIR)/ft_lstadd_back_bonus.c \
$(LIBFTDIR)/ft_memmove.c \
$(LIBFTDIR)/ft_strjoin.c \
$(LIBFTDIR)/ft_toupper.c \
$(LIBFTDIR)/ft_lstadd_front_bonus.c \
$(LIBFTDIR)/ft_memset.c \
$(LIBFTDIR)/ft_strlcat.c
LIBFTOBJECTS = $(addprefix $(LIBFTDIR)/, $(LIBFTSOURCES:.c=.o))

all: libmlx $(NAME)

libft:
	@make -C ./lib/libft

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	
# getnextline:
# 	@make -C ./lib/get_next_line

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): libft $(OBJECTS)
	@$(CC) $(OBJECTS) $(LIBS) $(HEADERS) -o $(NAME) $(LIBFT)

clean:
	@make -C ./lib/libft clean
	@rm -rf $(OBJECTS)
	@rm -rf $(LIBFTOBJECTS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@make -C ./lib/libft fclean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
