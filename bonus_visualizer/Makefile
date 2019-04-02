# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/15 15:21:21 by anleclab          #+#    #+#              #
#    Updated: 2019/04/02 10:06:23 by anleclab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visualizer

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

SRC = main.c \
	  parser.c \
	  set_rooms_and_ants.c \
	  count_and_fill_input.c \
	  draw_anthill.c \
	  draw_ants.c \
	  end.c \
	  fill_adjacency_matrix.c \
	  set_instructions.c \
	  event_manager.c \
	  scale.c
SRCSFD = srcs/
OBJSFD = objs/
OBJS = $(addprefix $(OBJSFD),$(SRC:.c=.o))

HDR = visualizer.h
HDRSFD = includes/
HDRS = $(addprefix $(HDRSFD),$(HDR))

HDR_INC = -I./includes
LIBFT_HDR = -I../libft/inc
LIB_BINARY = -L../libft -lft
SDL_HDR=$(shell sdl2-config --cflags | cut -d' ' -f1)
SDL_IMAGE_HDR=$(SDL_HDR)_image
SDL_TTF_HDR=$(SDL_HDR)_ttf
SDL_GFX_HDR=$(SDL_HDR)_gfx
SDL_BINARY=$(shell sdl2-config --libs) -lSDL2_image -lSDL2_ttf -lSDL2_gfx

RED = \033[0;31m
GREEN = \033[0;32m
NONE = \033[0m

all: check_libft project $(NAME) $(HDRS)
	@echo "Succes !!"

$(NAME): $(OBJSFD) $(OBJS) $(HDRS)
	@gcc $(CFLAGS) $(MLX) $(OBJS) $(LIB_BINARY) $(SDL_BINARY) -o $@
	@echo "\t[ \033[0;32m✔\033[0m ] visualizer executable"

check_libft:
	@echo "Checking libft..."
	@make -C ../libft

project:
	@echo "Checking project..."

$(OBJSFD):
	@mkdir $@

$(OBJSFD)%.o: $(SRCSFD)%.c $(HDRS)
	@gcc $(CFLAGS) $(HDR_INC) $(LIBFT_HDR) $(SDL_HDR) $(SDL_IMAGE_HDR) $(SDL_TTF_HDR) $(SDL_GFX_HDR) -c $< -o $@

clean:
	@rm -rf $(OBJSFD)
	@echo "\t[ $(RED)✗$(NONE) ] bonus_visualizer/$(OBJSFD) directory"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\t[ $(RED)✗$(NONE) ] $(NAME) executable"

re: fclean all

.PHONY: all project clean fclean re
