/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:00:52 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/03/28 17:13:23 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <unistd.h>

# include <stdio.h>

# define BUFF_SIZE 4096

# define START 0
# define END 1

# define SET_NB_ANTS 0
# define SET_ROOMS 1
# define SET_LINKS 2

# define ERROR -1

typedef struct	s_room
{
	char	*id;
	int		w;
	char	*ant_id;
}				t_room;

typedef struct	s_link
{
	int		st;
	int		nd;
}				t_link;

typedef struct	s_path
{
	char	*id_first;
	int		index_first;
	int		w;
	int		nb_ants;
	int		nb_remaining;
}				t_path;


typedef struct	s_lem
{
	char	*input;
	int		nb_rooms;
	int		nb_ants;
	t_room	*rooms;
	int		*split_rooms;
	int		**links;
	int		**d_links;
	char	*instr;
	t_path	*paths;
}				t_lem;

int				get_options(int *ac, char ***av);
void			print_line_count(t_lem lem);
void			print_paths(t_lem lem);
void    		print_ant_nb(t_lem lem);
void    		print_ants_per_room(t_lem lem);

void			error(t_lem *lem);
void			end(t_lem *lem);

int				count_rooms_and_fill_input(t_lem *lem);
void			send_ants(t_lem *lem);

void			parser(t_lem *lem);
int				set_nb_ants(t_lem *lem, char *str);
int				set_rooms(t_lem *lem, char *str, int current_room);
int				fill_adjacency_matrix(t_lem *lem, char *str);

void			edmonds_karp(t_lem *lem);
void			make_d_links(t_lem *lem);
void			set_ants_per_room(t_lem *lem, t_path *paths);

int				**copy_matrix(t_lem *lem, int **matrix);
void			delete_matrix(t_lem *lem, int ***matrix);

/* DEV */
void			display_rooms(t_lem lem);
void			display_adj_matrix(t_lem lem);
void			display_d_weights(t_lem lem);
void			display_weights(t_lem lem);
void			display_d_links(t_lem lem, int **matrix);
void			display_paths(t_path *paths);

#endif
