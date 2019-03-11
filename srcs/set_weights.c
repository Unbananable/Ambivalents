/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_weights.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:40:23 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/03/11 16:49:24 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

printf("\t\t/// IN BFS ///\n");
	i = -1;
	count = 0;
printf("\t\t1/6\n");
	while (current_w[++i] != -1)
		count += count_links(lem, current_w[i]);
	if (!(tmp = (int *)malloc(sizeof(int) * (count + 1))))
		error(lem);
printf("\t\t2/6 (count = %d)\n", count);
	i = -1;
	count = 0;
	while (current_w[++i] != -1)
	{
		j = 1;
		while (++j < lem->nb_rooms)
		{
			if (lem->links[current_w[i]][j] == 1 && lem->rooms[j].w == 0) //j commence à 2 donc no need de rajouter les conditions associées
			{
				tmp[count++] = j;
printf("\t\t\tweight set (%d)\n", weight);
				lem->rooms[j].w = weight;
			}
		}
	}
printf("\t\t3/6 (count = %d)\n", count);
	tmp[count] = -1;
	free(current_w);
printf("\t\t4/6\n");
printf("\t\t5/6\n");
	if (tmp[0] == -1)
	{
printf("\t\t6/6 (hard end)\n");
		free(tmp);
		return ;
	}
	bfs(lem, weight + 1, tmp);
printf("\t\t6/6 (soft end)\n");
}

void			set_weights(t_lem *lem)
{
	int		i;
	int		count;
	int		*current_w;

printf("\t/// IN SET_WEIGHTS ///\n");
printf("\t1/4\n");
	if (!(current_w = (int *)malloc(sizeof(int) * (count_links(lem, 1) + 1))))
		error(lem);
printf("\t2/4\n");
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
printf("\t3/4\n");
	current_w[count] = -1;
	bfs(lem, 2, current_w);
printf("\t4/4\n");
}
