/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 17:25:54 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/12 14:56:08 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void    error(t_lem *lem)
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
    if (lem->links)
    {
        i = -1;
        while (++i < lem->nb_rooms)
            free(lem->links[i]);
    }
    free(lem->links);
    ft_putstr_fd("ERROR\n", 2);
    exit(0);
}
