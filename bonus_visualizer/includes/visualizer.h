/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:27:35 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/15 14:05:18 by dtrigalo         ###   ########.fr       */
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

# define ERROR -1

# define HEIGHT 1000
# define WIDTH 1000
# define MARGIN 35

typedef struct	s_room
{
	int		is_full;
	char	*id;
	int		w;
    int     x;
    int     y;
}				t_room;

typedef struct	s_link
{
	int		st;
	int		nd;
}				t_link;

typedef struct	s_visu
{
	int		ant_id;
	int		i_room;
}				t_visu;

typedef struct	s_lem
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
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
	t_visu			**visu;//** to initialize malloc * nb_instr + 1, et set le dernier à ant_id = 0(* init in set_instr)
}				t_lem;

int				count_and_fill_input(t_lem *lem);

void	        parser(t_lem *lem);
int		        set_nb_ants(t_lem *lem, char *str);
int		        set_rooms(t_lem *lem, char *str, int current_room);
int             fill_adjacency_matrix(t_lem *lem, char *str);
int				set_instructions(t_lem *lem, char *str, int i_visu);

void			set_weights(t_lem *lem);

void    		draw_tunnels(t_lem *lem);
void			draw_rooms(t_lem *lems);

void    		error(t_lem *lem);

#endif
