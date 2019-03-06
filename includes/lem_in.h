/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:00:52 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/03/06 17:01:14 by anleclab         ###   ########.fr       */
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

void			error(void);

int				get_nb_rooms(t_lem *lem);
void			parser(t_lem *lem);

/* DEV */
void			display_rooms(t_lem lem);
void			display_links(t_lem lem);

#endif
