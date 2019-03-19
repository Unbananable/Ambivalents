/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:18:36 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/19 18:46:24 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void    draw_ants(t_lem *lem)
{
    static int  step;
    int         i;
    SDL_Rect    ant_pos;

    if (step >= lem->nb_instr)
        return ;
    if (SDL_RenderClear(lem->visual.rend))
        error(lem);
    if (SDL_RenderCopy(lem->visual.rend, lem->visual.anthill_text, NULL, NULL))
        error(lem);
    ant_pos.h = 8;
    ant_pos.w = 20;
    i = -1;
    while (lem->instr[step][++i].ant_id)
    {
        ant_pos.x = lem->rooms[lem->instr[step][i].i_room].x;
	    ant_pos.y = lem->rooms[lem->instr[step][i].i_room].y;
        if (SDL_RenderCopy(lem->visual.rend, lem->visual.ant_text, NULL,
                &ant_pos))
            error(lem);
    }
    SDL_RenderPresent(lem->visual.rend);
    step++;
}