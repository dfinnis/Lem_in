# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/07 10:32:17 by dfinnis           #+#    #+#              #
#    Updated: 2019/01/16 19:09:09 by svaskeli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEM_IN = lem-in

G_FLAG = -g
FSAN = -fsanitize=address
FLAGS = -Wall -Werror -Wextra

SRCS_DIR = srcs/
OBJS_DIR = objs/

INC = includes
INC_FILE = $(INC)/lem_in.h

LIBFT = libft/ft_printf
LIBFT_A = $(LIBFT)/libftprintf.a

SRCS_FILES = lem_in.c parse.c parse_room.c parse_support.c build_graph.c \
path_find.c path_queue.c path_build.c path_prep.c path_group.c \
build_ants.c path_solve.c display_mirror.c \
display_results.c display_parse.c display_links.c display_paths.c \
error.c free.c free_ants.c

SRCS_PATH = $(SRCS_FILES:%=$(SRCS_DIR)%)

OBJS = $(SRCS_FILES:%.c=%.o)
OBJS_PATH = $(addprefix $(OBJS_DIR), $(OBJS))

GREEN = "\033[0;32m"
RED = "\033[0;31m"
DEFAULT = "\033[0m"

all: $(LEM_IN)

norm:
	norminette -R CheckForbiddenSourceHeader $(INC) $(SRCS_DIR)

g_flag:
	@echo $(RED)"Compiling all with -g:" $(LEM_IN) $(DEFAULT)
	make -C $(LIBFT)/ g
	gcc $(FLAGS) $(G_FLAG) -c $(SRCS_PATH) -I $(INC)
	mkdir -p $(OBJS_DIR)
	mv $(OBJS) $(OBJS_DIR)
	gcc $(FLAGS) $(G_FLAG) $(OBJS_PATH) $(LIBFT_A) -o $(LEM_IN) -I $(LIBFT) -I $(INC)

fsanitize:
	@echo $(RED)"Compiling all with -g and -fsanitize:" $(LEM_IN) $(DEFAULT)
	make -C $(LIBFT)/ fsanitize
	gcc $(FLAGS) $(G_FLAG) $(FSAN) -c $(SRCS_PATH) -I $(INC)
	mkdir -p $(OBJS_DIR)
	mv $(OBJS) $(OBJS_DIR)
	gcc $(FLAGS) $(G_FLAG) $(FSAN) $(OBJS_PATH) $(LIBFT_A) -o $(LEM_IN) -I $(LIBFT) -I $(INC)

$(LEM_IN): $(LIBFT_A) $(OBJS_DIR) $(OBJS_PATH) $(INC_FILE)
	@echo "Compiling:" $(GREEN) $(LEM_IN) $(DEFAULT)
	gcc $(FLAGS) $(OBJS_PATH) $(LIBFT_A) -o $(LEM_IN) -I $(LIBFT) -I $(INC)

$(LIBFT_A):
	@echo "Compiling:" $(GREEN) Libft $(DEFAULT)
	make -C $(LIBFT)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@echo "Compiling:" $(GREEN) $< $(DEFAULT)
	gcc $(FLAGS) -g -c $< -o $@ -I $(INC)

clean:
	@make -C $(LIBFT)/ clean
	@rm -rf $(OBJS_DIR)

fclean:
	@make -C $(LIBFT)/ fclean
	@rm -rf $(OBJS_DIR) $(LEM_IN)

re: fclean all

.PHONY: all norm clean fclean re g fsanitize
