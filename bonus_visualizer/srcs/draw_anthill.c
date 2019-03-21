/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_anthill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 16:25:38 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/21 18:50:51 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void draw_tunnels(t_lem *lem)
{
    int	i = -1;
	int	j = -1;

	while (++i < lem->nb_rooms - 1)
	{
		j = i;
		while (++j < lem->nb_rooms)
			if (lem->links[i][j] == 1)
				if (thickLineRGBA(lem->visual.rend, lem->rooms[i].x,
                        lem->rooms[i].y, lem->rooms[j].x, lem->rooms[j].y, 5, rand() % 255,
                        rand() % 255, rand() % 255, 255))
                    error(lem);
	}
}

static void draw_room_names(t_lem *lem)
{
	SDL_Surface	*text_surf;
    SDL_Texture *text_text;
	SDL_Rect	text_pos;
    int         i;

	i = -1;
	while (++i < lem->nb_rooms)
	{
	    if (!(text_surf = TTF_RenderText_Shaded(lem->visual.font,
                lem->rooms[i].id, lem->visual.colors[RED],
                lem->visual.colors[WHITE])))
            error(lem);
	    text_pos.x = lem->rooms[i].x;
	    text_pos.y = lem->rooms[i].y;
	    text_pos.h = 20;
	    text_pos.w = 20;
        text_text = SDL_CreateTextureFromSurface(lem->visual.rend, text_surf);
        SDL_FreeSurface(text_surf);
        if (!text_text)
            error(lem);
        if (SDL_RenderCopy(lem->visual.rend, text_text, NULL, &text_pos))
            error(lem);
        SDL_DestroyTexture(text_text);
	}
}

static void draw_rooms(t_lem *lem)
{
    SDL_Surface *room_surf;
    SDL_Texture *room_text;
    int         i;
    SDL_Rect    room_pos;

    if (!(room_surf = IMG_Load("imgs/room_ant.jpg")))
		error(lem);
    room_text = SDL_CreateTextureFromSurface(lem->visual.rend, room_surf);
    SDL_FreeSurface(room_surf);
    if (!room_text)
        error(lem);
    room_pos.h = 50; //il faudra peut etre adapter la taille de la room en fonction de l'echelle aussi
    room_pos.w = 50;
    i = -1;
    while (++i < lem->nb_rooms)
    {
        room_pos.x = lem->rooms[i].x - 15;
        room_pos.y = lem->rooms[i].y - 15;
        if (SDL_RenderCopy(lem->visual.rend, room_text, NULL, &room_pos))
            error(lem);
    }
    SDL_DestroyTexture(room_text);
}

void        draw_anthill(t_lem *lem)
{
    /* On dit que la texture de la foumilliere sert de renderer le temps de mettre toutes les images des rools et tunnels dedans */
	if (SDL_SetRenderTarget(lem->visual.rend, lem->visual.anthill_text))
		error(lem);
	draw_tunnels(lem);
	draw_rooms(lem);
    draw_room_names(lem);
	/* On reset le renderer */
	if (SDL_SetRenderTarget(lem->visual.rend, NULL))
		error(lem);
}
