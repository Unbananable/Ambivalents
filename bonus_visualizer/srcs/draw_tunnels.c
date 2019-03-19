/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tunnels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:29:13 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/19 18:40:09 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void    draw_tunnels(t_lem *lem)
{
    int	i = -1;
	int	j = -1;

	while (++i < lem->nb_rooms - 1)
	{
		j = i;
		while (++j < lem->nb_rooms)
			if (lem->links[i][j] == 1)
				if (thickLineRGBA(lem->visual.rend, lem->rooms[i].x,
                        lem->rooms[i].y, lem->rooms[j].x, lem->rooms[j].y, 5, 0,
                        0, 255,255))
                    error(lem);
	}
}