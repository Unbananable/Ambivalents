# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anleclab <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/15 15:21:21 by anleclab          #+#    #+#              #
#    Updated: 2019/03/12 16:44:02 by dtrigalo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visualizer

CFLAGS = -Wall -Wextra -Werror

SRC = main.c \
	  parser.c \
	  parser_steps.c \
	  set_weights.c \
	  count_rooms_and_fill_input.c \
	  draw_rooms.c \
	  end.c
SRCSFD = srcs/
OBJSFD = objs/
OBJS = $(addprefix $(OBJSFD),$(SRC:.c=.o))

HDR = visualizer.h
HDRSFD = includes/
HDRS = $(addprefix $(HDRSFD),$(HDR))

HDR_INC = -I./includes
LIBFT_HDR = -I../libft/inc
LIB_BINARY = -L../libft -lft

RED = \033[0;31m
GREEN = \033[0;32m
NONE = \033[0m

all: sdl2 $(NAME) $(HDRS)

$(NAME): $(OBJSFD) $(OBJS) $(HDRS)
	@gcc $(CFLAGS) $(MLX) $(OBJS) $(LIB_BINARY) -L/Users/dtrigalo/.brew/lib -lSDL2 -lSDL2_image -o $@
	@echo "\t[ \033[0;32m✔\033[0m ] visualizer executable"

sdl2:
	@sdl2-config --cflags --libs

$(OBJSFD):
	@mkdir $@

$(OBJSFD)%.o: $(SRCSFD)%.c $(HDRS)
	@gcc $(CFLAGS) $(HDR_INC) $(LIBFT_HDR) -I/Users/dtrigalo/.brew/include/SDL2 -I/Users/dtrigalo/.brew/include/SDL_image -D_THREAD_SAFE -c $< -o $@

clean:
	@rm -rf $(OBJSFD)
	@echo "\t[ $(RED)✗$(NONE) ] $(OBJSFD) directory"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\t[ $(RED)✗$(NONE) ] $(NAME) executable"

re: fclean all

.PHONY: sdl2 all project clean fclean re
