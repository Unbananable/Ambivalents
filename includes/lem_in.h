/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:00:52 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/03/14 13:35:16 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <unistd.h>

# define BUFF_SIZE 4096

# define START 0
# define END 1

# define SET_NB_ANTS 0
# define SET_ROOMS 1
# define SET_LINKS 2

# define ERROR -1

typedef struct	s_room
{
	int		is_full;
	char	*id;
	int		w;
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
	char	*instr;
}				t_lem;

void			error(t_lem *lem);

int				count_rooms_and_fill_input(t_lem *lem);
void			send_ants(t_lem *lem);

void			parser(t_lem *lem);
int				set_nb_ants(t_lem *lem, char *str);
int				set_rooms(t_lem *lem, char *str, int current_room);
int     		fill_adjacency_matrix(t_lem *lem, char *str);

void    		edmonds_karp(t_lem *lem);

//void			set_weights(t_lem *lem);

/* DEV */
void			display_rooms(t_lem lem);
void			display_adj_matrix(t_lem lem);
void			display_weights(t_lem lem);

#endif
