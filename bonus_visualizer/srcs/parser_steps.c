/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_steps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 10:38:30 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/12 13:44:08 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

int		set_nb_ants(t_lem *lem, char *str)
{
	int		i;

	i = -1;
	while (str[++i] && str[i] != '\n')
		if (!ft_isdigit(str[i]))
			return (-1);
	if (i == 0 || (lem->nb_ants = ft_atoi(str)) <= 0)
		return (-1);
	return (1);
}

static int	is_room(char *str, int i, t_room *room)
{
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (i >= 0 && str[i] >= '0' && str[i] <= '9')
		i--;
	if (i >= 0 && str[i] == '-')
		i--;
	room->y = ft_atoi(str + i + 1);
	if (i < 0 || str[i--] != ' ')
		return (-1);
	if (i < 0 || str[i] < '0' || str[i] > '9')
		return (-1);
	while (i >= 0 && str[i] >= '0' && str[i] <= '9')
		i--;
	if (i >= 0 && str[i] == '-')
		i--;
	room->x = ft_atoi(str + i + 1);
	if (i < 0 || str[i--] != ' ')
		return (-1);
	if (i < 0)
		return (-1);
	return (i);
}

int		set_rooms(t_lem *lem, char *str, int current_room)
{
	int		i;
	int		i_end_id;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if ((i_end_id = is_room(str, i - 1, lem->rooms + current_room)) == -1
			&& current_room != lem->nb_rooms - 1)
		return (-1);
	if(!(lem->rooms[current_room].id = ft_strsub(str, 0, i_end_id + 1)))
		error(lem);
	i = -1;
	while (++i < current_room)
		if (ft_strequ(lem->rooms[i].id, lem->rooms[current_room].id))
			error(lem);
	lem->rooms[current_room].is_full = 0;
	lem->rooms[current_room].w = 0;
	return(1);
}

static void init_links(t_link *link1, t_link *link2)
{
    link1->st = -1;
    link1->nd = -1;
    link2->st = -1;
    link2->nd = -1;
}

int         fill_adjacency_matrix(t_lem *lem, char *str)
{
    int     i;
    int     j;
    int     k;
    t_link  link;
    t_link  search;

    init_links(&link, &search);
    i = 0;
    search.st = -1;
    search.nd = -1;
    while (str[i] && str[i] != '\n')
    {
        if (str[i] == '-')
        {
            j = i;
            while (str[j] && str[j] != '\n')
                j++;
			str[i] = 0;
			str[j] = 0;
            k = -1;
            while (++k < lem->nb_rooms)
            {
                if (ft_strequ(str, lem->rooms[k].id))
                    search.st = k;
                if (ft_strequ(str + i + 1, lem->rooms[k].id))
                    search.nd = k;
            }
			str[i] = '-';
			str[j] = '\n';
            if (search.st != -1 && search.nd != -1)
            {
                if (link.st != -1)
                    return (-1);
                link.st = search.st;
                link.nd = search.nd;
            }
        }
        i++;
    }
	if (link.st == -1 || link.nd == -1)
		return (-1);
    lem->links[link.st][link.nd] = 1;
    lem->links[link.nd][link.st] = 1;
    return(2);
}