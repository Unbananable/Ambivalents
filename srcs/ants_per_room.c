/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_per_room.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:05:55 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/28 11:58:46 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		*ants_per_room(t_lem *lem, int	*plen_list)
{
    int     sent_ants;
    int     *ants_per_room;
    int     i;
    int     room_end;

    i = -1;
    while (plen_list[++i])
        ;
    if (!(ants_per_room = (int *)malloc(sizeof(int) * (i + 1))))
        return (NULL);
    ft_bzero(ants_per_room, sizeof(int) * (i + 1));
    ants_per_room[i] = -1;
    sent_ants = 0;
    while (sent_ants < lem->nb_ants)
    {
        i = 1;
        while (sent_ants < lem->nb_ants && ants_per_room[i] != -1)
        {
            room_end = 0;
            while (!room_end && sent_ants < lem->nb_ants)
                if (plen_list[i] + ants_per_room[i] + 1 <= plen_list[0] + ants_per_room[0])
                {
                    sent_ants++;
                    ants_per_room[i]++;
                }
                else
                    room_end = 1;
            i++;
        }
        if (sent_ants < lem->nb_ants)
        {
            sent_ants++;
            ants_per_room[0] ++;
        }
    }
    return(ants_per_room);
}