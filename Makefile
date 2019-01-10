# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/07 10:32:17 by dfinnis           #+#    #+#              #
#    Updated: 2019/01/10 14:36:28 by svaskeli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEM_IN = lem-in

G = -g
FSAN = -fsanitize=address
FLAGS = -Wall -Werror -Wextra

SRCS_DIR = srcs/
OBJS_DIR = objs/

INC = includes/

LIBFT = libft/ft_printf
LIBFT_A = $(LIBFT)/libftprintf.a

SRCS_FILES = lem_in.c parse.c error.c
SRCS_PATH = $(SRCS_FILES:%=$(SRCS_DIR)%)

OBJS = $(SRCS_FILES:%.c=%.o)
OBJS_PATH = $(addprefix $(OBJS_DIR), $(OBJS))

GREEN = "\033[0;32m"
RED = "\033[0;31m"
DEFAULT = "\033[0m"

all: $(LEM_IN)

norm:
	norminette -R CheckForbiddenSourceHeader $(INC) $(SRCS_DIR)

g:
	@echo $(RED)"Compiling all with -g:" $(LEM_IN) $(DEFAULT)
	make -C $(LIBFT)/ g
	gcc $(FLAGS) $(G) -c $(SRCS_PATH) -I $(INC)
	mkdir -p $(OBJS_DIR)
	mv $(OBJS) $(OBJS_DIR)
	gcc $(FLAGS) $(G) $(OBJS_PATH) $(LIBFT_A) -o $(LEM_IN) -I $(LIBFT) -I $(INC)

fsanitize:
	@echo $(RED)"Compiling all with -g and -fsanitize:" $(LEM_IN) $(DEFAULT)
	make -C $(LIBFT)/ fsanitize
	gcc $(FLAGS) $(G) $(FSAN) -c $(SRCS_PATH) -I $(INC)
	mkdir -p $(OBJS_DIR)
	mv $(OBJS) $(OBJS_DIR)
	gcc $(FLAGS) $(G) $(FSAN) $(OBJS_PATH) $(LIBFT_A) -o $(LEM_IN) -I $(LIBFT) -I $(INC)

$(LEM_IN): $(LIBFT_A) $(OBJS_DIR) $(OBJS_PATH)
	@echo "Compiling:" $(GREEN) $(LEM_IN) $(DEFAULT)
	gcc $(FLAGS) $(OBJS_PATH) $(LIBFT_A) -o $(LEM_IN) -I $(LIBFT) -I $(INC)

$(LIBFT_A):
	@echo "Compiling:" $(GREEN) Libft $(DEFAULT)
	make -C $(LIBFT)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@echo "Compiling:" $(GREEN) $< $(DEFAULT)
	gcc $(FLAGS) -c $< -o $@ -I $(INC)

clean:
	@make -C $(LIBFT)/ clean
	@rm -rf $(OBJS_DIR)

fclean:
	@make -C $(LIBFT)/ fclean
	@rm -rf $(OBJS_DIR) $(LEM_IN)

re: fclean all

.PHONY: all norm clean fclean re g fsanitize
