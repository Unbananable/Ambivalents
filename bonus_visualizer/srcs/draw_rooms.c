/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 15:14:46 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/12 17:04:22 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void init_room_pos(t_room room, SDL_Rect *room_pos)
{
    room_pos->x = room.x - 15; //10 est l'echelle juste pour test, a changer
    room_pos->y = room.y - 15;
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
    room_pos.h = 30; //il faudra peut etre adapter la taille de la room en fonction de l'echelle aussi
    room_pos.w = 30;
    i = -1;
    while (++i < lem->nb_rooms)
    {
        init_room_pos(lem->rooms[i], &room_pos);
        SDL_RenderCopy(lem->rend, room_texture, NULL, &room_pos);
    }
    SDL_DestroyTexture(room_texture); //il faudrait aussi peut-etre plutot inclure ca dans le t_lem pour pas avoir a les recharger plein de fois ? (je sais pas si c'est necessaire pour les rooms)
    SDL_FreeSurface(room_img);
}
