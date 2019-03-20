/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:18:36 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/20 16:09:49 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

#include <stdio.h>

void    draw_start_ants(t_lem *lem)
{
    SDL_Rect    start_ant_pos;
    int         i;

    i = -1;
    if (lem->visual.step != -1)
        while (lem->instr[lem->visual.step][++i].ant_id)
            if (lem->instr[lem->visual.step][i].ant_id == lem->nb_ants)
                return ;
    start_ant_pos.h = 8;
    start_ant_pos.w = 20;
    start_ant_pos.x = lem->rooms[0].x;
    start_ant_pos.y = lem->rooms[0].y;
    if (SDL_RenderCopy(lem->visual.rend, lem->visual.ant_text, NULL,
            &start_ant_pos))
        error(lem);
}

void    draw_ants(t_lem *lem, SDL_Keycode key)
{
    int         i;
    SDL_Rect    ant_pos;

    lem->visual.step += (key == SDLK_LEFT) ? -1 : 1;
    if (lem->visual.step < -1 || lem->visual.step >= lem->nb_instr)
    {
        lem->visual.step = (lem->visual.step < 0) ? -1 : lem->nb_instr - 1;
        return ;
    }
    if (SDL_RenderClear(lem->visual.rend))
        error(lem);
    if (SDL_RenderCopy(lem->visual.rend, lem->visual.anthill_text, NULL, NULL))
        error(lem);
    if (lem->visual.step != -1)
    {
        ant_pos.h = 8;
        ant_pos.w = 20;
        i = -1;
        while (lem->instr[lem->visual.step][++i].ant_id)
        {
            ant_pos.x = lem->rooms[lem->instr[lem->visual.step][i].i_room].x;
	        ant_pos.y = lem->rooms[lem->instr[lem->visual.step][i].i_room].y;
            if (SDL_RenderCopy(lem->visual.rend, lem->visual.ant_text, NULL,
                    &ant_pos))
                error(lem);
        }
    }
    draw_start_ants(lem);
    SDL_RenderPresent(lem->visual.rend);
}