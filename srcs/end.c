/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 17:25:54 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/28 11:58:49 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void    end(t_lem *lem)
{
    int     i;

    free(lem->input);
    if (lem->rooms)
    {
        i = -1;
        while (++i < lem->nb_rooms)
            free(lem->rooms[i].id);
    }
    free(lem->rooms);
    free(lem->split_rooms);
    if (lem->links)
    {
        i = -1;
        while (++i < lem->nb_rooms)
            free(lem->links[i]);
    }
    free(lem->links);
	free(lem->instr);
    free(lem->ants_per_room);
}

void    error(t_lem *lem)
{


    end(lem);
    ft_putstr_fd("ERROR\n", 2);
    exit(0);
}
