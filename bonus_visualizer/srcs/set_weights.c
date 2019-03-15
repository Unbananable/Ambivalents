/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_weights.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:40:23 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/03/15 11:55:06 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

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

static void		bfs(t_lem *lem, int weight, int *current_w)
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
		return ;
	}
	bfs(lem, weight + 1, tmp);
}

void			set_weights(t_lem *lem)
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
		if (lem->links[END][i] == 1)
		{
			current_w[count++] = i;
			lem->rooms[i].w = 1;
		}
	}
	current_w[count] = -1;
	bfs(lem, 2, current_w);
}
