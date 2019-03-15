/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 17:04:49 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/03/15 21:31:37 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static SDL_Color	set_color(t_lem *lem)
{
	SDL_Color	res = {255, 255, 255, 255};

	if (lem->color == PATTERN_1)
	{
		res.r = 128;
		res.g = 0;
		res.b = 0;
	}
	else if (lem->color == PATTERN_2)
	{
		res.r = 230;
		res.g = 0;
		res.b = 0;
	}
	else if (lem->color == PATTERN_3)
	{
		res.g = 33;
		res.b = 0;
	}
	else if (lem->color == PATTERN_4)
	{
		res.g = 112;
		res.b = 77;
	}
	else
	{
		res.g = 194;
		res.b = 153;
	}
	return (res);

}
static void	draw(t_lem *lem, int i_room)
{
	TTF_Font	*police = NULL;
	SDL_Color	rouge = {100, 100, 255, 255};
	SDL_Surface	*texte = NULL;
	SDL_Rect	position;
    SDL_Texture *texture = NULL;
    int         i;
	SDL_Color	color;

	color = set_color(lem);
    position.x = 0;
	position.y = 0;
	if (TTF_Init() == -1)
		error(lem);
	if (!(police = TTF_OpenFont("fonts/Phosphate.ttf", 150)))
		error(lem);
	i = -1;
	texte = TTF_RenderText_Shaded(police, "Anleclab", rouge, color);
	position.x = lem->rooms[i_room].x ;
	position.y = lem->rooms[i_room].y;
	position.h = 50;
	position.w = 100;
    if (!(texture = SDL_CreateTextureFromSurface(lem->rend, texte)))
		error(lem);
    if (SDL_RenderCopy(lem->rend, texture, NULL, &position))
		error(lem);
	SDL_RenderPresent(lem->rend);
    TTF_CloseFont(police);
    TTF_Quit();
}

static void	move_one_step(t_lem *lem, int i_visu)
{
	int		i;

	i = -1;
	while (i_visu < lem->nb_instr && lem->visu[i_visu][++i].ant_id)
		draw(lem, lem->visu[i_visu][i].i_room);
	lem->color++;
}

void	draw_ants(t_lem *lem)
{
	int			loop;
	int			i;
	SDL_Event	event;

	loop = 1;
	i = -1;
	while (loop)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				loop = 0;
			else if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_n)
					if (++i < lem->nb_instr)
						move_one_step(lem, i);
			}
		}
	}
	/* draw image */
}
