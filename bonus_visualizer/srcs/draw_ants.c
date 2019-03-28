/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:18:36 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/28 11:50:16 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

#include <stdio.h>

void		draw_start_ants(t_lem *lem)
{
	static int	marker = -1;
	SDL_Rect	start_ant_pos;
	int			i;

	i = -1;
	if (lem->visual.step != -1)
	{
		while (lem->instr[lem->visual.step][++i].ant_id)
		{
			marker = (lem->visual.step == marker) ? -1 : marker;
			if (lem->instr[lem->visual.step][i].ant_id == lem->nb_ants
					|| marker != -1)
			{
				marker = (marker == -1) ? lem->visual.step - 1 : marker;
				return ;
			}
		}
	}
	start_ant_pos.h = 10;
	start_ant_pos.w = 10;
	start_ant_pos.x = lem->rooms[0].x;
	start_ant_pos.y = lem->rooms[0].y;
	if (SDL_RenderCopy(lem->visual.rend, lem->visual.ant_text, NULL,
				&start_ant_pos))
		error(lem);
}

static void	draw_ant_id(t_lem *lem, int ant_id, SDL_Rect ant_pos)
{
	char		*id;
	SDL_Surface	*id_surf;
	SDL_Texture	*id_text;

	ant_pos.x += 20;
	ant_pos.h = 10;
	ant_pos.w = 10;
	if (!(id = ft_itoa(ant_id)))
		error(lem);
	if (!(id_surf = TTF_RenderText_Shaded(lem->visual.font, id,
					lem->visual.colors[BLACK], lem->visual.colors[WHITE])))
		error(lem);
	free(id);
	id_text = SDL_CreateTextureFromSurface(lem->visual.rend, id_surf);
	SDL_FreeSurface(id_surf);
	if (!id_text)
		error(lem);
	if (SDL_RenderCopy(lem->visual.rend, id_text, NULL, &ant_pos))
		error(lem);
	SDL_DestroyTexture(id_text);
}

static void	print_and_draw_ant_id(t_lem *lem, int i, SDL_Rect ant_pos)
{
	int	anim_step;

	anim_step = 4;
	while (--anim_step >= 0)
	{
		usleep(100000);
		if (SDL_RenderCopy(lem->visual.rend, lem->visual.anthill_text, NULL, NULL))
			error(lem);
		ant_pos.x = lem->ants[lem->instr[lem->visual.step][i].ant_id - 1].x
			+ ((lem->ants[lem->instr[lem->visual.step][i].ant_id-1].last_x
						- lem->ants[lem->instr[lem->visual.step][i].ant_id
						- 1].x) / 4) * anim_step;
		ant_pos.y = lem->ants[lem->instr[lem->visual.step][i].ant_id - 1].y
			+ ((lem->ants[lem->instr[lem->visual.step][i].ant_id - 1].last_y
						- lem->ants[lem->instr[lem->visual.step][i].ant_id
						- 1].y) / 4) * anim_step;
//		printf("ant_id: %d, anim_step: %d, (x/y): (%d / %d), last(x/y): (%d / %d)\n", lem->instr[lem->visual.step][i].ant_id, anim_step,  lem->ants[lem->instr[lem->visual.step][i].ant_id - 1].x, lem->ants[lem->instr[lem->visual.step][i].ant_id - 1].y, lem->ants[lem->instr[lem->visual.step][i].ant_id-1].last_x, lem->ants[lem->instr[lem->visual.step][i].ant_id - 1].last_y);
		if (SDL_RenderCopy(lem->visual.rend, lem->visual.ant_text, NULL,
					&ant_pos))
			error(lem);
		if (lem->instr[lem->visual.step][i].i_room != 1 || anim_step != 0)
			draw_ant_id(lem, lem->instr[lem->visual.step][i].ant_id,
					ant_pos);
		SDL_RenderPresent(lem->visual.rend);
	}
}

void		draw_ants(t_lem *lem, SDL_Keycode key)
{
	int			i;
	SDL_Rect	ant_pos;

	lem->visual.step += (key == SDLK_LEFT) ? -1 : 0;
	lem->visual.step += (key == SDLK_RIGHT) ? 1 : 0;
	lem->visual.step = (key == SDLK_SPACE) ? -1 : lem->visual.step;
	if (lem->visual.step < -1 || lem->visual.step >= lem->nb_instr)
	{
		lem->visual.step = (lem->visual.step < 0) ? -1 : lem->nb_instr - 1;
		return ;
	}
	if (SDL_RenderCopy(lem->visual.rend, lem->visual.anthill_text, NULL, NULL))
		error(lem);
	if (lem->visual.step != -1)
	{
		ant_pos.h = 10;
		ant_pos.w = 10;
		i = -1;
		while (lem->instr[lem->visual.step][++i].ant_id)
		{
			lem->ants[lem->instr[lem->visual.step][i].ant_id - 1].last_x
				= lem->ants[lem->instr[lem->visual.step][i].ant_id - 1].x;
			lem->ants[lem->instr[lem->visual.step][i].ant_id - 1].last_y
				= lem->ants[lem->instr[lem->visual.step][i].ant_id - 1].y;
			lem->ants[lem->instr[lem->visual.step][i].ant_id - 1].x = lem->rooms[lem->instr[lem->visual.step][i].i_room].x;
			lem->ants[lem->instr[lem->visual.step][i].ant_id - 1].y = lem->rooms[lem->instr[lem->visual.step][i].i_room].y;
			print_and_draw_ant_id(lem, i, ant_pos);
		}
	}
	draw_start_ants(lem);
	render_menu(lem);
	SDL_RenderPresent(lem->visual.rend);
}
