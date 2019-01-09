# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/07 10:32:17 by dfinnis           #+#    #+#              #
#    Updated: 2019/01/09 13:51:01 by svaskeli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PUSH_SWAP = push_swap
CHECKER = checker

FLAGS = -Wall -Werror -Wextra
D_G = -g
D_FS = -fsanitize=address
DEBUG = $(D_G) $(D_FS)

PS_SRCS_DIR = srcs/push_swap/
CH_SRCS_DIR = srcs/checker/
SH_SRCS_DIR = srcs/shared/
SRCS_DIRS = $(PS_SRCS_DIR) $(CH_SRCS_DIR) $(SH_SRCS_DIR)

PS_OBJS_DIR = objs/push_swap/
CH_OBJS_DIR = objs/checker/
SH_OBJS_DIR = objs/shared/
OBJ_SUB_DIR = $(PS_OBJS_DIR) $(CH_OBJS_DIR) $(SH_OBJS_DIR)

INC = includes/

OBJS_DIR = objs/
SRCS_DIR = srcs/

LIBFT = libft/ft_printf
LIBFT_A = $(LIBFT)/libftprintf.a

PS_SRCS = push_swap.c ps_functions.c ps_find_refs.c ps_sort_pb.c \
	ps_sort_pa.c ps_sort_small.c

CH_SRCS = checker.c checker_functions.c visualizer.c visualizer_colour.c

SH_SRCS = stack.c stack_overflow.c do_push_swap.c do_rotate.c do_comb.c \
	error.c error_null.c

PS_OBJS = $(PS_SRCS:%.c=%.o)
CH_OBJS = $(CH_SRCS:%.c=%.o)
SH_OBJS = $(SH_SRCS:%.c=%.o)
OBJS = $(PS_OBJS) $(CH_OBJS) $(SH_OBJS)

PS_SRCS_PATH = $(PS_SRCS:%=$(PS_SRCS_DIR)%)
CH_SRCS_PATH = $(CH_SRCS:%=$(CH_SRCS_DIR)%)
SH_SRCS_PATH = $(SH_SRCS:%=$(SH_SRCS_DIR)%)
SRCS_PATH = $(PS_SRCS_PATH) $(CH_SRCS_PATH) $(SH_SRCS_PATH)

PS_OBJS_PATH = $(addprefix $(PS_OBJS_DIR), $(PS_OBJS))
CH_OBJS_PATH = $(addprefix $(CH_OBJS_DIR), $(CH_OBJS))
SH_OBJS_PATH = $(addprefix $(SH_OBJS_DIR), $(SH_OBJS))
OBJS_PATH = $(PS_OBJS_PATH) $(CH_OBJS_PATH) $(SH_OBJS_PATH)

GREEN = "\033[0;32m"
DEFAULT = "\033[0m"

all: $(PUSH_SWAP) $(CHECKER)

norm:
	norminette -R CheckForbiddenSourceHeader $(INC) $(SRCS_DIR)

$(PUSH_SWAP): $(LIBFT_A) $(OBJS_DIR) $(PS_OBJS_DIR) $(SH_OBJS_DIR) $(PS_OBJS_PATH) $(SH_OBJS_PATH)
	@echo "Compiling:" $(GREEN) $(PUSH_SWAP) $(DEFAULT)
	gcc $(FLAGS) $(PS_OBJS_PATH) $(SH_OBJS_PATH) $(LIBFT_A) -o $(PUSH_SWAP) -I $(LIBFT)

$(CHECKER): $(LIBFT_A) $(OBJS_DIR) $(CH_OBJS_DIR) $(SH_OBJS_DIR) $(CH_OBJS_PATH) $(SH_OBJS_PATH)
	@echo "Compiling:" $(GREEN) $(CHECKER) $(DEFAULT)
	gcc $(FLAGS) $(CH_OBJS_PATH) $(SH_OBJS_PATH) $(LIBFT_A) -o $(CHECKER) -I $(LIBFT)

$(LIBFT_A):
	@echo "Compiling:" $(GREEN) Libft $(DEFAULT)
	@make -C $(LIBFT)

$(PS_OBJS_DIR):
	@mkdir -p $(PS_OBJS_DIR)

$(CH_OBJS_DIR):
	@mkdir -p $(CH_OBJS_DIR)

$(SH_OBJS_DIR):
	@mkdir -p $(SH_OBJS_DIR)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@echo "Compiling:" $(GREEN) $< $(DEFAULT)
	gcc $(FLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT)/ clean
	@rm -rf $(OBJS_DIR)

fclean:
	@make -C $(LIBFT)/ fclean
	@rm -rf $(OBJS_DIR) $(PUSH_SWAP) $(CHECKER)

re: fclean all

.PHONY: all norm clean fclean re
