/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 10:53:45 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/14 13:28:30 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#include <stdio.h>

static int		count_links(t_lem *lem, int x)
{
	int		i;
	int		res;

	i = 1;
	res = 0;
	while (++i < lem->nb_rooms)
		res += lem->links[x][i];
	return (res);
}

static int		bfs_recursion(t_lem *lem, int weight, int *current_w)
{
	int		i;
	int		j;
	int		count;
	int		*tmp;

	i = -1;
	count = 0;
	while (current_w[++i] != -1)
		count += count_links(lem, current_w[i]);
	if (!(tmp = (int *)malloc(sizeof(int) * (count + 1))))
		error(lem);
	i = -1;
	count = 0;
	while (current_w[++i] != -1)
	{
        if (lem->links[current_w[i]][START] == 1)
            return (current_w[i]);
		j = 1;
		while (++j < lem->nb_rooms)
		{
			if (lem->links[current_w[i]][j] == 1 && lem->rooms[j].w == 0)
			{
				tmp[count++] = j;
				lem->rooms[j].w = weight;
			}
		}
	}
	tmp[count] = -1;
	free(current_w);
	if (tmp[0] == -1)
	{
		free(tmp);
		return (-1);
	}
	return(bfs_recursion(lem, weight + 1, tmp));
}

static int  bfs(t_lem *lem)
{
	int		i;
	int		count;
	int		*current_w;

	if (!(current_w = (int *)malloc(sizeof(int) * (count_links(lem, 1) + 1))))
		error(lem);
	count = 0;
	i = 1;
	while (++i < lem->nb_rooms)
	{
		if (lem->links[END][i] == 1 && !lem->rooms[i].w)
		{
			current_w[count++] = i;
			lem->rooms[i].w = 1;
		}
	}
	current_w[count] = -1;
	return(bfs_recursion(lem, 2, current_w));
}

static void  isolate_path(t_lem *lem, int prev_room, int current_room)
{
    int     i;
    int     done;
    int     next_room;

lem->rooms[0].id = ft_strdup("START");
//printf("\t\t/// IN ISOLATE_PATH (prev = %s, current = %s)\n", lem->rooms[prev_room].id, lem->rooms[current_room].id);
    lem->rooms[current_room].is_full = 1;
    i = -1;
    done = 0;
    while (++i < lem->nb_rooms)
        if (done == 2 || (i != prev_room && lem->rooms[i].w != lem->rooms[current_room].w - 1))
        {
            lem->links[current_room][i] = 0;
            lem->links[i][current_room] = 0;
        }
		else
		{
			if (i != prev_room)
                next_room = i;
			done++;
		}
    if (next_room == END)
        return ;
    isolate_path(lem, current_room, next_room);
}

static void clear_weights(t_lem *lem)
{
    int     i;

    i = 1;
    while (++i < lem->nb_rooms)
        if (!lem->rooms[i].is_full)
            lem->rooms[i].w = 0;
}

void    edmonds_karp(t_lem *lem)
{
    int     first_room;

//printf("\t/// IN EDMONDS_KARP ///\n");
    while ((first_room = bfs(lem)) != -1)
    {
//printf("\tfirst_room : room %s\n", lem->rooms[first_room].id);
        isolate_path(lem, START, first_room);
        clear_weights(lem);
    }
}