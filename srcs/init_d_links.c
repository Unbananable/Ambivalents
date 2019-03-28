/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_d_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:13:52 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/28 14:54:28 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	count_links(t_lem *lem)
{
	int		i;
	int		j;
	int		res;

	i = -1;
	res = 0;
	while (++i < lem->nb_rooms)
	{
		j = -1;
		while (++j < lem->nb_rooms)
			res += lem->links[i][j];
	}
	return (res);
}

static int	bfs(t_lem *lem, int **current_w_list, int **next_w_list, int weight)
{
	int		i;
	int		j;
	int		k;
	int		*tmp;

	if (!(*current_w_list)[0])
		return (0);
	i = -1;
	k = -1;
	while ((*current_w_list)[++i])
	{
		j = 0;
		while (++j < lem->nb_rooms)
			if (lem->links[(*current_w_list)[i]][j] == 1 && !lem->rooms[j].w)
			{
				lem->rooms[j].w = weight;
				(*next_w_list)[++k] = j;
			}
	}
	(*next_w_list)[++k] = 0;
	tmp = *current_w_list;
	*current_w_list = *next_w_list;
	*next_w_list = tmp;
	return (1);
}

static void	update_weight(t_lem *lem, int **current_w_list, int i, int j)
{
	lem->rooms[i].w = 1;
	(*current_w_list)[j] = i;
}

static void	set_weights(t_lem *lem)
{
	int		i;
	int		j;
	int		weight;
	int		*current_w_list;
	int		*next_w_list;

	i = count_links(lem);
	if (!(current_w_list = (int *)malloc(sizeof(int) * i)))
		error(lem);
	if (!(next_w_list = (int *)malloc(sizeof(int) * i)))
		error(lem);
	ft_bzero(next_w_list, sizeof(int) * i);
	ft_bzero(current_w_list, sizeof(int) * i);
	i = -1;
	j = -1;
	while (++i < lem->nb_rooms)
		if (lem->links[END][i] == 1 && !lem->rooms[i].w)
			update_weight(lem, &current_w_list, i, ++j);
	weight = 1;
	while (bfs(lem, &current_w_list, &next_w_list, ++weight))
		;
	free(current_w_list);
	free(next_w_list);
}

void		make_d_links(t_lem *lem)
{
	int		i;
	int		j;

	set_weights(lem);
	i = -1;
	while (++i < lem->nb_rooms)
	{
		lem->d_links[2 * i][2 * i + 1] = 1;
		j = i - 1;
		while (++j < lem->nb_rooms)
			if (lem->links[i][j] && (i == START || j == END
						|| (lem->rooms[i].w >= lem->rooms[j].w
							&& j != END && i != END
							&& i != START && j != START)))
				lem->d_links[j * 2 + 1][i * 2] = 1;
			else if (lem->links[i][j])
				lem->d_links[i * 2 + 1][j * 2] = 1;
	}
}
