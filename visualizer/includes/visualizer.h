/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:27:35 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/11 18:57:55 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

# include <SDL2/SDL.h>
# include "libft.h"
# include <unistd.h>

# define BUFF_SIZE 4096

# define START 0
# define END 1

# define SET_NB_ANTS 0
# define SET_ROOMS 1
# define SET_LINKS 2

# define ERROR -1

# define HEIGHT 650
# define WIDTH 1000

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


typedef struct	s_lem
{
	char	*input;
	int		nb_rooms;
	int		nb_ants;
	t_room	*rooms;
	int		**links;
}				t_lem;

void	        parser(t_lem *lem);
int		        set_nb_ants(t_lem *lem, char *str);
int		        set_rooms(t_lem *lem, char *str, int current_room);
int             fill_adjacency_matrix(t_lem *lem, char *str);

void			set_weights(t_lem *lem);

#endif
