# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/15 15:21:21 by anleclab          #+#    #+#              #
#    Updated: 2019/03/15 13:38:44 by anleclab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

SRC = main.c \
	  count_rooms_and_fill_input.c \
	  parser.c \
	  parser_steps.c \
	  end.c \
	  edmonds_karp.c \
	  send_ants.c \
	  dev_tools.c
SRCSFD = srcs/
OBJSFD = objs/
OBJS = $(addprefix $(OBJSFD),$(SRC:.c=.o))

HDR = lem_in.h
HDRSFD = includes/
HDRS = $(addprefix $(HDRSFD),$(HDR))

HDR_INC = -I./includes
LIBFT_HDR = -I./libft/inc
LIB_BINARY = -L./libft -lft
LIBFT= libft/libft.a

RED = \033[0;31m
GREEN = \033[0;32m
NONE = \033[0m

all: check_libft project $(NAME) $(HDRS)
	@echo "Success !!"

$(NAME): $(OBJSFD) $(OBJS) $(LIBFT) $(HDRS)
	@gcc $(CFLAGS) $(MLX) $(OBJS) $(LIB_BINARY) -o $@
	@echo "\t[ \033[0;32m✔\033[0m ] lem-in executable"

check_libft:
	@echo "Checking libft..."
	@make -C libft

project:
	@echo "Checking project..."

$(OBJSFD):
	@mkdir $@
	@echo "\t[ $(GREEN)✔$(NONE) ] objs/ directory"

$(OBJSFD)%.o: $(SRCSFD)%.c $(HDRS)
	@gcc $(CFLAGS) $(HDR_INC) $(LIBFT_HDR) -c $< -o $@
	@echo "\t[ $(GREEN)✔$(NONE) ] $@ object"

visualizer:
	@echo "Adding visualizer..."
	@make -C ./bonus_visualizer
	@mv bonus_visualizer/visualizer .

clean:
	@/bin/rm -rf $(OBJSFD)
	@echo "\t[ $(RED)✗$(NONE) ] $(OBJSFD) directory"
	@make -C ./libft clean
	@make -C ./bonus_visualizer clean

fclean: clean
	@/bin/rm -f $(NAME) visualizer
	@echo "\t[ $(RED)✗$(NONE) ] $(NAME) executable"
	@echo "\t[ $(RED)✗$(NONE) ] visualizer executable"
	@make -C ./libft fclean

re: fclean all

.PHONY: all check_libft project clean fclean re
