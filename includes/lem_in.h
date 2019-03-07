/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:00:52 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/03/07 16:16:58 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

typedef struct	s_room
{
	int		is_full;
	char	*id;
}				t_room;

typedef struct	s_lem
{
	char	*input;
	int		nb_rooms;
	int		nb_ants;
	t_room	*rooms;
	int		**links; //adjacency matrix
}				t_lem;

void			error(t_lem *lem);

int				count_room_and_fill_input(t_lem *lem);
int				get_ant_number(t_lem *lem);
void			fill_adjacency_matric(t_lem *lem);
void			parser(t_lem *lem); //empty

/* DEV */
void			display_rooms(t_lem lem); //empty
void			display_links(t_lem lem); //empty

#endif
