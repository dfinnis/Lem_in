# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/07 10:44:29 by dfinnis           #+#    #+#              #
#    Updated: 2019/01/09 13:53:17 by svaskeli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = ft_printf.c \
	   initialize.c \
	   parse_flags_width.c \
	   parse_precision.c \
	   parse_length.c \
	   parse_type.c \
	   read_numbers.c \
	   read_floats.c \
	   read_others.c \
	   build_precision.c \
	   build_width.c \
	   build_prefix.c \
	   build_float.c \
	   error_protection.c \
	   binary.c

LIB_DIR = ../

LIB_C = ft_atoi.c \
		ft_atoi_intmax.c \
		ft_bzero.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_itoa_intmax.c \
		ft_itoa_unsigned.c \
		ft_itoa_base.c \
		ft_memalloc.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memdel.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar.c \
		ft_putchar_fd.c \
		ft_putendl.c \
		ft_putendl_fd.c \
		ft_putnbr.c \
		ft_putnbr_fd.c \
		ft_putstr.c \
		ft_putstr_fd.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strclr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strdel.c \
		ft_strdup.c \
		ft_strequ.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlen.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strncat.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_strnequ.c \
		ft_strnew.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strsplit.c \
		ft_strstr.c \
		ft_strsub.c \
		ft_strtrim.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_lstnew.c \
		ft_lstdelone.c \
		ft_lstdel.c \
		ft_lstadd.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_swap.c \
		ft_strrev.c \
		ft_strndup.c \
		ft_strjoinfree.c \
		ft_strjoinfree_s1.c \
		ft_strjoinfree_s2.c \
		ft_strlcpy.c \
		ft_sqrt.c \
		ft_listlen_int.c \
		ft_listlen_char.c \
		ft_2d_int_free.c \
		ft_2d_char_free.c \
		ft_split_whitespaces.c \
		ft_isblank.c \
		get_next_line.c \
		ft_freestr.c

OBJ = $(SRCS:.c=.o)
LIB_O = $(LIB_C:.c=.o)
LIB_PATH = $(addprefix $(LIB_DIR), $(LIB_O))

FLAGS = -Wall -Werror -Wextra
D_G = -g
D_FS = -fsantize=address
DEBUG = $(D_G) $(D_FS)

INC = ft_printf.h

all: lib $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ) $(LIB_PATH)
	@ranlib $(NAME)

$(OBJ): $(SRCS)
	@gcc -c $(FLAGS) $(SRCS) -I $(INC)

lib: 
	@make -C ../ all

libfclean:
	@make -C ../ fclean

libclean:
	@make -C ../ clean

clean: libclean
	@/bin/rm -f $(OBJ)

fclean: clean libfclean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
