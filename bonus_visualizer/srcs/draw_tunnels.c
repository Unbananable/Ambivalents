/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tunnels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 11:37:24 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/13 11:38:42 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void    draw_tunnels(t_lem *lem)
{
    int	i = -1;
	int	j = -1;


	SDL_SetRenderDrawColor(lem->rend, 255, 0, 0, SDL_ALPHA_OPAQUE);
	while (++i < lem->nb_rooms - 1)
	{
		j = i;
		while (++j < lem->nb_rooms)
			if (lem->links[i][j] == 1)
				thickLineRGBA(lem->rend, lem->rooms[i].x, lem->rooms[i].y, lem->rooms[j].x, lem->rooms[j].y, 5, 0, 0, 255,255);
	}
}