/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:32:13 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/03/28 20:26:56 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	add_sentence_to_menu(t_lem *lem, char *str, SDL_Rect text_pos)
{
	SDL_Surface	*text_surf;
	SDL_Texture *text_text;
	int			i;

	i = -1;
	while (++i < lem->nb_rooms)
	{
		if (!(text_surf = TTF_RenderText_Blended(lem->visual.font,
						str, lem->visual.colors[WHITE])))
			error(lem);
		text_text = SDL_CreateTextureFromSurface(lem->visual.rend, text_surf);
		SDL_FreeSurface(text_surf);
		if (!text_text)
			error(lem);
		if (SDL_RenderCopy(lem->visual.rend, text_text, NULL, &text_pos))
			error(lem);
		SDL_DestroyTexture(text_text);
	}
}

void		render_menu(t_lem *lem)
{
	SDL_Rect	pos;

	pos.x = 10;
	pos.y = 10;
	pos.h = 20;
	pos.w = 250;
	add_sentence_to_menu(lem, "    /_\\ Command Menu /_\\    ", pos);
	pos.y += 20;
	add_sentence_to_menu(lem, "--------", pos);
	pos.y += 20;
	add_sentence_to_menu(lem, "Step by Step: <- / ->", pos);
	pos.y += 30;
	add_sentence_to_menu(lem, "Launch Animation: A", pos);
	pos.y += 30;
	add_sentence_to_menu(lem, "    Reset: [SPACE]    ", pos);
	pos.y += 20;
	add_sentence_to_menu(lem, "--------", pos);
}

void		event_manager(t_lem *lem)
{
	int			quit;
	SDL_Event	event;
	int			i;

	quit = 0;
	i = NO_ANIM;
	while (!quit)
	{
		if (SDL_PollEvent(&event) || i != NO_ANIM)
		{
			if ((event.type == SDL_WINDOWEVENT
						&& event.window.event == SDL_WINDOWEVENT_CLOSE)
					|| (event.type == SDL_KEYUP
						&& event.key.keysym.sym == SDLK_ESCAPE))
				quit = 1;
			else if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_RIGHT
						|| event.key.keysym.sym == SDLK_LEFT
						|| event.key.keysym.sym == SDLK_SPACE)
				{
					draw_ants(lem, event.key.keysym.sym);
					if (i != NO_ANIM)
						i = lem->visual.step;
				}
				else if (event.key.keysym.sym == SDLK_a)
				{
					if (i == NO_ANIM)
						i = lem->visual.step;
					else
						i = NO_ANIM;
				}
			}
			if (i != NO_ANIM && i < lem->nb_instr * (DIV_ANIM + 1))
			{
				draw_ants(lem, SDLK_RIGHT);
				i++;
				if (i >= lem->nb_instr * (DIV_ANIM + 1))
				{
					lem->visual.step = lem->nb_instr - 1;
					draw_ants(lem, SDLK_RIGHT);
					i = NO_ANIM;
				}
			}
		}
	}
}
