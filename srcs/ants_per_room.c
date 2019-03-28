/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_per_room.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:05:55 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/28 15:51:13 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void initialize_nb_ants_paths(t_path *paths)
{
    int     i;

    i = -1;
    while (paths[++i].index_first != -1)
    {
        paths[i].nb_ants = 0;
        paths[i].nb_remaining = 0;
    }
    paths[i].nb_ants = -1;
    paths[i].nb_remaining = -1;
}

void    set_ants_per_room(t_lem *lem, t_path *paths)
{
    int     ants_left;
    int     i;
    int     room_end;

    initialize_nb_ants_paths(paths);
    ants_left = lem->nb_ants;
//display_paths(paths);
    while (ants_left)
    {
        i = 1;
        while (ants_left && paths[i].index_first != -1)
        {
            room_end = 0;
            while (!room_end && ants_left)
                if (paths[i].w + paths[i].nb_ants + 1 <= paths[0].w + paths[0].nb_ants)
                {
                    ants_left--;
                    paths[i].nb_ants++;
                    paths[i].nb_remaining++;
                }
                else
                    room_end = 1;
            i++;
        }
        if (ants_left)
        {
            ants_left--;
            paths[0].nb_ants++;
            paths[0].nb_remaining++;
        }
    }
}