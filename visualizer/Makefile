# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anleclab <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/15 15:21:21 by anleclab          #+#    #+#              #
#    Updated: 2019/03/12 15:06:20 by anleclab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visualizer

CFLAGS = -Wall -Wextra -Werror

SRC = main.c \
	  parser.c \
	  parser_steps.c \
	  set_weights.c \
	  count_rooms_and_fill_input.c \
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
SDL_HDR = -I./SDL/SDL2 -I./SDL_image/include/SDL2
SDL_BINARY = -L./SDL -lSDL2 -L./SDL_image/lib -lSDL2_image

RED = \033[0;31m
GREEN = \033[0;32m
NONE = \033[0m

all: $(NAME) $(HDRS)

$(NAME): $(OBJSFD) $(OBJS) $(HDRS)
	@gcc $(CFLAGS) $(MLX) $(OBJS) $(LIB_BINARY) $(SDL_BINARY) -o $@
	@echo "\t[ \033[0;32m✔\033[0m ] visualizer executable"

$(OBJSFD):
	@mkdir $@

$(OBJSFD)%.o: $(SRCSFD)%.c $(HDRS)
	@gcc $(CFLAGS) $(HDR_INC) $(LIBFT_HDR) $(SDL_HDR) -c $< -o $@

clean:
	@rm -rf $(OBJSFD)
	@echo "\t[ $(RED)✗$(NONE) ] bonus_visualizer/$(OBJSFD) directory"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\t[ $(RED)✗$(NONE) ] $(NAME) executable"

re: fclean all

.PHONY: all project clean fclean re
