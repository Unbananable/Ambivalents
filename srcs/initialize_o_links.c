/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_o_links.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:13:52 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/04 16:39:32 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Initializes the oriented matrix. In the directed matrix, the rooms are
** subdivided in 'in' and 'out' subrooms to simulate the fact that the room
** behaves like a vertice with a flow of one for the Edmonds-Karp algorithm.
** The oriented matrix is not symetrical as the original links are oriented
** from the room closest to the end roomto the room furthest from the end room.
*/
void		initialize_o_links(t_lem *lem)
{
	int		i;
	int		j;

	i = -1;
	while (++i < lem->nb_rooms)
	{
		if (i != END && i != START)
		{
			lem->o_links[out(i)][in(i)] = 1;
			lem->o_links[in(i)][out(i)] = 1;
		}
		j = i - 1;
		while (++j < lem->nb_rooms)
			if (lem->links[i][j])
			{
				lem->o_links[out(j)][in(i)] = 1;
				lem->o_links[out(i)][in(j)] = 1;
			}
	}
}
