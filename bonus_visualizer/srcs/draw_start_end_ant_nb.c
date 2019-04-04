/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_start_end_ant_nb.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:00:57 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/04/04 20:53:45 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	set_start_end_ant_nb(t_lem *lem, int step, int anim_step, SDL_Keycode key)
{
	int		i;
	int		j;
	int		count;
	static int	prev_start = 0;
	static int	prev_end = 0;

	if (step == -1)
	{
		lem->rooms[START].ant_nb = lem->nb_ants;
		lem->rooms[END].ant_nb = 0;
		return ;
	}
	if (key == SDLK_LEFT && lem->visual.step != 0)
		lem->rooms[START].ant_nb += prev_start;
	else if (key == SDLK_RIGHT)
	{
		i = -1;
		count = 0;
		if (anim_step == DIV_ANIM - 1)
		{
			while (lem->instr[step][++i].ant_id)
			{
				j = -1;
				while (lem->instr[START][++j].ant_id)
					if (lem->instr[step][i].i_room == lem->instr[START][j].i_room)
						count++;
			}
			lem->rooms[START].ant_nb -= count;
			prev_start = count;
		}
		else if (anim_step == 0)
		{
			while (lem->instr[step][++i].ant_id)
				if (lem->instr[step][i].i_room == END)
					count++;
			lem->rooms[END].ant_nb += count;
			prev_end = count;
		}
	}
}

void		draw_start_end_ant_nb(t_lem *lem, int step, int anim_step, SDL_Keycode key)
{
	SDL_Surface	*text_surf;
	SDL_Texture *text_text;
	SDL_Rect	text_pos;
	char		*res;

	set_start_end_ant_nb(lem, step, anim_step, key);
	if (!(res = ft_itoa(lem->rooms[START].ant_nb)))
		error(lem);
	if (!(text_surf = TTF_RenderText_Shaded(lem->visual.font,
					res, lem->visual.colors[WHITE],
					lem->visual.colors[BLACK])))
	{
		free(res);
		error(lem);
	}
	text_pos.x = lem->rooms[START].x + 20;
	text_pos.y = lem->rooms[START].y + 10;
	text_pos.h = 30;
	text_pos.w = 30;
	text_text = SDL_CreateTextureFromSurface(lem->visual.rend, text_surf);
	if (!text_text)
		error(lem);
	if (SDL_RenderCopy(lem->visual.rend, text_text, NULL, &text_pos))
		error(lem);
	if (!(res = ft_itoa(lem->rooms[END].ant_nb)))
		error(lem);
	if (!(text_surf = TTF_RenderText_Shaded(lem->visual.font,
					res, lem->visual.colors[WHITE],
					lem->visual.colors[BLACK])))
	{
		free(res);
		error(lem);
	}
	ft_strdel(&res);
	text_pos.x = lem->rooms[END].x + 20;
	text_pos.y = lem->rooms[END].y + 20;
	text_text = SDL_CreateTextureFromSurface(lem->visual.rend, text_surf);
	SDL_FreeSurface(text_surf);
	if (!text_text)
		error(lem);
	if (SDL_RenderCopy(lem->visual.rend, text_text, NULL, &text_pos))
		error(lem);
	SDL_DestroyTexture(text_text);
}
