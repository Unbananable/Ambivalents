/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:17:34 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/02 18:56:41 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
/*
static int	nb_links_from(t_lem *lem, int index)
{
	int		res;
	int		i;

	res = 0;
	i = -1;
	while (++i < lem->nb_rooms * 2)
		res += lem->d_links[index][i];
	return (res);
}

static int	bfs_recursive(t_lem *lem, int *current_w_list, int current_w)
{
	int		*next_w_list;
	int		i;
	int		j;
	int		count;
	int		nb_links;

	i = -1;
	nb_links = 0;
	while (current_w_list[++i] != -1)
		nb_links += nb_links_from(lem, current_w_list[i]);

	next_w_list = NULL;
	if (nb_links != 0) 
	{

		if (!(next_w_list = (int *)malloc(sizeof(int) * (nb_links + 1))))
		{
			free(current_w_list);
			error(lem);
		}

		count = -1;
		i = -1;
		while (current_w_list[++i] != -1)
		{

			j = -1;
			while (++j < lem->nb_rooms * 2)

				if (lem->d_links[current_w_list[i]][j] == 1)
				{
				
					if (j == 2 * START)
					{
						lem->d_links[current_w_list[i]][2 * START] = 0;
						lem->d_links[2 * START][current_w_list[i]] = 1;

						while (count >= 0)

							lem->split_rooms[next_w_list[count--]] = 0;

						count = -1;

						while (current_w_list[++count] != -1)

							if (count != i)

								lem->split_rooms[current_w_list[count]] = 0;

						free(next_w_list);

						return (current_w_list[i]);
					}
				
					lem->split_rooms[j] = current_w;
					next_w_list[++count] = j;
				}

		}

		next_w_list[++count] = -1;
		j = bfs_recursive(lem, next_w_list, current_w + 1);

	}
	else 
		j = -1;

	if (j != -1)
	{
		i = -1;
		while (++i != -1 && current_w_list[i] != -1)
			if (lem->d_links[current_w_list[i]][j])
			{
				lem->d_links[current_w_list[i]][j] = 0;
				lem->d_links[j][current_w_list[i]] = 1;
				j = current_w_list[i];
				i = -1;
			}
	}

	i = -1;
	while (current_w_list[++i] != -1)

		if (current_w_list[i] != j)

			lem->split_rooms[current_w_list[i]] = 0;

	free(next_w_list);

	return (j);
}

static int	bfs(t_lem *lem)
{
	int		*start_list;
	int 	count;
	int		i;
	int		path_index;

	if (!(start_list = (int *)malloc(sizeof(int) * (nb_links_from(lem, 2 * END + 1) + 1))))
		error(lem);

	count = -1;
	i = 1;
	while (++i < lem->nb_rooms * 2)
	{
		if (lem->d_links[2 * END + 1][i] == 1)
		{
			start_list[++count] = i;
			lem->split_rooms[i] = 1;
		}
	}
	start_list[++count] = -1;

	path_index = bfs_recursive(lem, start_list, 2);

	i = -1;

	while (start_list[++i] != -1)

		if (start_list[i] != path_index)

			lem->split_rooms[start_list[i]] = 0;

	if (path_index != -1)
	{
		lem->d_links[2 * END + 1][path_index] = 0;
		lem->d_links[path_index][2 * END + 1] = 1;
	}

	free(start_list);

	return (path_index);

}

static int		get_weight(t_lem *lem, int current_index)
{
	int		next_index;

	if (current_index == END)
		return (0);
	next_index = -1;
	while (++next_index < lem->nb_rooms)
		if (lem->d_links[2 * current_index][2 * next_index + 1])
			return (1 + get_weight(lem, next_index));
	return (-1);
}

static t_path	*set_path_len_list(t_lem *lem)
{
	int		nb_paths;
	int		i;
	int		j;
	t_path	*paths;
	t_path	tmp;

	nb_paths = 0;
	i = 1;
	while (++i < lem->nb_rooms)
		if (lem->d_links[2 * START][2 * i + 1])
			nb_paths++;

	if (!(paths = (t_path *)malloc(sizeof(t_path) * (nb_paths + 1))))
		return (NULL);
	j = -1;
	i = 1;

	while (++i < lem->nb_rooms)
		if (lem->d_links[2 * START][2 * i + 1])
		{

			paths[++j].id_first = lem->rooms[i].id;
			paths[j].index_first = i;
			paths[j].w = get_weight(lem, i);
		}

	paths[nb_paths].id_first = NULL;
	paths[nb_paths].index_first = -1;
	paths[nb_paths].w = 0;

	i = -1;
	while (++i < nb_paths)
	{
		j = -1;
		while (paths[++j + 1].index_first != -1)
			if (paths[j].w > paths[j + 1].w)
			{
				tmp = paths[j + 1];
				paths[j + 1] = paths[j];
				paths[j] = tmp;
			}
	}

	return (paths);
}
*/
void    find_paths(t_lem *lem)
{
	int		stop;
	t_path	*current_paths;

	current_paths = NULL;
	stop = 0;
	initialize_d_links(lem);
	while (!stop)
	{
		if (bfs(lem) == -1) // CONTINUE FROM HERE INCLUDED
			stop = 1;
		else
		{
			if (!(current_paths = set_path_len_list(lem)))
				error(lem); 
			set_ants_per_room(lem, current_paths); 
			if (!lem->paths || current_paths[0].nb_ants + current_paths[0].w < lem->paths[0].nb_ants + lem->paths[0].w) 
			{
				free(lem->paths);
				lem->paths = current_paths;
				current_paths = NULL;
			}
			else 
				stop = 1;
		}
	}
}