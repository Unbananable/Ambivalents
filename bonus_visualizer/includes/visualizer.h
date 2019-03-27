/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:27:35 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/27 20:09:37 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include <SDL2_gfxPrimitives.h>
# include "libft.h"
# include <unistd.h>

# define BUFF_SIZE 4096

# define START 0
# define END 1

# define SET_NB_ANTS 0
# define SET_ROOMS 1
# define SET_LINKS 2
# define SET_INSTR 3
# define PARSING_IS_OVER 4

# define ANTS 0
# define INSTR 1

# define ERROR -1

# define HEIGHT 1000
# define WIDTH 1000
# define MARGIN 35

# define WHITE 0
# define BLACK 1

# define BG_R 250
# define BG_G 150
# define BG_B 90
# define BG_A 255

typedef struct	s_room
{
	int		is_full;
	char	*id;
	int		w;
	int		x;
	int		y;
}				t_room;

typedef struct	s_link
{
	int		st;
	int		nd;
}				t_link;

typedef struct	s_ant
{
	int		x;
	int		y;
	int		last_x;
	int		last_y;
}				t_ant;

typedef struct	s_instr
{
	int		ant_id;
	int		i_room;
}				t_instr;

typedef struct	s_visual
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Texture		*anthill_text;
	TTF_Font		*font;
	SDL_Color		*colors;
	SDL_Texture		*ant_text;
	int				step;
}				t_visual;

typedef struct	s_lem
{
	char			*input;
	int				nb_rooms;
	int				nb_ants;
	int				nb_instr;
	t_room			*rooms;
	int				**links;
	int				x_min;
	int				x_max;
	int				y_min;
	int				y_max;
	int				x_offset;
	int				y_offset;
	int				scale;
	t_instr			**instr;
	t_ant			*ants;
	t_visual		visual;
	int				parse_step;
}				t_lem;

int				count_and_fill_input(t_lem *lem);

void			parser(t_lem *lem);
int				set_nb_ants(t_lem *lem, char *str);
int				set_rooms(t_lem *lem, char *str, int current_room);
int				fill_adjacency_matrix(t_lem *lem, char *str);
int				set_instructions(t_lem *lem, char *str, int i_visu);

void			scale(t_lem *lem);
void			set_scale(t_lem *lem);

void			draw_anthill(t_lem *lem);
void			draw_ants(t_lem *lem, SDL_Keycode key);
void			draw_start_ants(t_lem *lem);
void			event_manager(t_lem lem);
void			render_menu(t_lem *lem);

void			error(t_lem *lem);
void			end(t_lem *lem);

#endif
