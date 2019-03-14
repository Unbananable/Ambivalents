/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 15:14:46 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/14 09:04:15 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void init_room_pos(t_room room, SDL_Rect *room_pos)
{
    room_pos->x = room.x - 15; //10 est l'echelle juste pour test, a changer
    room_pos->y = room.y - 15;
}

static void draw_weight(t_lem *lem)
{
    TTF_Font	*police = NULL;
	SDL_Color	rouge = {100, 100, 255, 255};
	SDL_Color	blanc = {255, 255, 255, 255};
	SDL_Surface	*texte = NULL;
	SDL_Rect	position;
    SDL_Texture *texture = NULL;
    int         i;

    position.x = 0;
	position.y = 0;
	if (TTF_Init() == -1)
		error(lem);
	if (!(police = TTF_OpenFont("fonts/SignPainter.ttf", 50)))
		error(lem);
	i = -1;
	while (++i < lem->nb_rooms)
	{
	texte = TTF_RenderText_Shaded(police, ft_itoa(lem->rooms[i].w), rouge, blanc);
	position.x = lem->rooms[i].x ;
	position.y = lem->rooms[i].y;
	position.h = 20;
	position.w = 20;
    if (!(texture = SDL_CreateTextureFromSurface(lem->rend, texte)))
		error(lem);
    if (SDL_RenderCopy(lem->rend, texture, NULL, &position))
		error(lem);
	}
    TTF_CloseFont(police);
    TTF_Quit();
}

void        draw_rooms(t_lem *lem)
{
    SDL_Surface *room_img;
    SDL_Texture *room_texture;
    int         i;
    SDL_Rect    room_pos;

    if (!(room_img = IMG_Load("imgs/room_ant.jpg")))
		error(lem);
    room_texture = SDL_CreateTextureFromSurface(lem->rend, room_img);
    room_pos.h = 50; //il faudra peut etre adapter la taille de la room en fonction de l'echelle aussi
    room_pos.w = 50;
    i = -1;
    while (++i < lem->nb_rooms)
    {
        init_room_pos(lem->rooms[i], &room_pos);
        SDL_RenderCopy(lem->rend, room_texture, NULL, &room_pos);
    }
    SDL_DestroyTexture(room_texture); //il faudrait aussi peut-etre plutot inclure ca dans le t_lem pour pas avoir a les recharger plein de fois ? (je sais pas si c'est necessaire pour les rooms)
    SDL_FreeSurface(room_img);
    draw_weight(lem);
}
