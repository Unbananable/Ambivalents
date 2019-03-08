/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:00:52 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/03/08 11:16:31 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
#include <unistd.h>

typedef struct	s_room
{
	int		is_full;
	char	*id;
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
	int		**links; //adjacency matrix
}				t_lem;

void			error(t_lem *lem);

int				count_rooms_and_fill_input(t_lem *lem);

void			parser(t_lem *lem);
int				set_nb_ants(t_lem *lem, char *str);
int				set_rooms(t_lem *lem, char *str);
int     		fill_adjacency_matrix(t_lem *lem, char *str);

/* DEV */
void			display_rooms(t_lem lem);
void			display_links(t_lem lem);

#endif
