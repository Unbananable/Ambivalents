/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:17:34 by anleclab          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/04/12 18:11:50 by anleclab         ###   ########.fr       */
=======
/*   Updated: 2019/04/12 11:41:52 by dtrigalo         ###   ########.fr       */
>>>>>>> 20731213d7c027eb6da35e13b9de5b5b4808cfa0
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Recursively returns the distance of the room to the end room following the
** path made available by the bfs algorithm.
*/
/*
static int		get_weight(t_lem *lem, int current_index)
{
	int		next_index;

	if (current_index == END)
		return (0);
	next_index = -1;
	while (++next_index < lem->nb_rooms)
		if (lem->o_links[in(current_index)][out(next_index)])
			return (1 + get_weight(lem, next_index));
	return (-1);
}
*/

static int		get_path(t_lem *lem, t_plist **rooms, int current_index)
{
	int		next_index;
	t_plist	*link;
	int		rval;

	if (current_index != END && current_index != START)
	{
		if (!(link = new_link(lem->rooms + current_index)))
			return (-1);
		*rooms = add_link(link, *rooms);
	}
	if (current_index == END)
		return (0);
	next_index = -1;
	while (++next_index < lem->nb_rooms)
		if (lem->o_links[in(current_index)][out(next_index)])
		{
			if ((rval = get_path(lem, rooms, next_index)) == -1)
				return (-1);
			return (1 + rval);
		}
	return (-1);
}

/*
** Returns a list of paths containing the information about the index and id of
** the first rooms of the paths and their length (weight). Sorts the list by
** length.
*/

static t_path	*set_path_len_list(t_lem *lem)
{
	int		nb_paths;
	int		i;
	int		count;
	t_path	*paths;
	t_path	tmp;

	nb_paths = 0;
	i = 1;
	while (++i < lem->nb_rooms)
		if (lem->o_links[in(START)][out(i)])
			nb_paths++;
	if (!(paths = (t_path *)malloc(sizeof(t_path) * (nb_paths + 1))))
		return (NULL);
	count = -1;
	i = 1;
	while (++i < lem->nb_rooms)
		if (lem->o_links[in(START)][out(i)])
		{
			paths[++count].id_first = lem->rooms[i].id;
			paths[count].i_first = i;
			paths[count].rooms = NULL;
			paths[count].w = get_path(lem, &(paths[count].rooms), i);
//			paths[count].w = get_weight(lem, i);
		}
	paths[nb_paths].id_first = NULL;
	paths[nb_paths].i_first = -1;
	paths[nb_paths].w = 0;
	count = -1;
	while (++count < nb_paths) // TO DO: Improve with a better sort than bubble
	{
		i = -1;
		while (paths[++i + 1].i_first != -1)
			if (paths[i].w > paths[i + 1].w)
			{
				tmp = paths[i + 1];
				paths[i + 1] = paths[i];
				paths[i] = tmp;
			}
	}
	return (paths);
}

static int		nb_links_from(t_lem *lem, int index)
{
	int		res;
	int		i;

	res = 0;
	i = -1;
	while (++i < lem->nb_rooms * 2)
		res += (lem->rooms[i / 2].w < 2) ? lem->o_links[index][i] : 0;
	return (res);
}

/*
** Recursively returns the index of the index of the room with the cuurent
** weight which is included in the shortest path from start to end. In the
** return process it also swaps the orientation of the links.
*/

static int		bfs_recursive(t_lem *lem, int *current_w_list)
{
	int		*next_w_list;
	int		i;
	int		j;
	int		count;
	int		nb_links;

	i = -1;
	nb_links = 0;
	while (!nb_links && current_w_list[++i] != -1)
		nb_links += nb_links_from(lem, current_w_list[i]);
	next_w_list = NULL;
	if (nb_links != 0)
	{
		if (!(next_w_list = (int *)malloc(sizeof(int) * (lem->nb_rooms - 1) * (lem->nb_rooms - 1)/*(nb_links + 1)*/)))
		{
			free(current_w_list); // TO DO: I think there might be a leak here because all the previous current_w in the recursion are not freed
			error(lem);
		}
		count = -1;
		i = -1;
		while (current_w_list[++i] != -1)
		{
			j = -1;
			while (++j < lem->nb_rooms * 2)
				if (lem->o_links[current_w_list[i]][j] == 1
						&& lem->rooms[j / 2].w < 2)
				{
					if (j == in(START))
					{
						lem->o_links[current_w_list[i]][in(START)] = 0;
						lem->o_links[in(START)][current_w_list[i]] = 1;
						free(next_w_list);
						return (current_w_list[i]);
					}
					next_w_list[++count] = j;
					lem->rooms[j / 2].w++;
				}
		}
		next_w_list[++count] = -1;
		j = bfs_recursive(lem, next_w_list);
	}
	else
		j = -1;
	if (j != -1)
	{
		i = -1;
		while (++i != -1 && current_w_list[i] != -1)
			if (lem->o_links[current_w_list[i]][j])
			{
				lem->o_links[current_w_list[i]][j] = 0;
				lem->o_links[j][current_w_list[i]] = 1;
				j = current_w_list[i];
				i = -2;
			}
	}
	free(next_w_list);
	return (j);
}

/*
** Returns the index of the shortest path from the end room to the start room.
** Initializes the recursive bfs algorithm with the list of rooms linked to
** the end room. It then swaps the orientation of the links which are used in
** the path.
*/

static int		bfs(t_lem *lem)
{
	int		*start_list;
	int 	count;
	int		i;
	int		path_index;

	if (!(start_list = (int *)malloc(sizeof(int)
					* (nb_links_from(lem, out(END)) + 1))))
		error(lem);
	count = -1;
	i = 1;
	while (++i < lem->nb_rooms * 2)
		if (lem->o_links[out(END)][i] == 1)
		{
			start_list[++count] = i;
			lem->rooms[i / 2].w++;
		}
	start_list[++count] = -1;
	path_index = bfs_recursive(lem, start_list);
	if (path_index != -1)
	{
		lem->o_links[out(END)][path_index] = 0;
		lem->o_links[path_index][out(END)] = 1;
	}
	free(start_list);
	return (path_index);
}

/*
** Resets the weight of the rooms to 0.
*/

static void	clear_weights(t_lem *lem)
{
	int		i;

	i = -1;
	while (++i < lem->nb_rooms)
		lem->rooms[i].w = 0;
}

/*
** Uses the Edmonds-Karp algorithm with all the vertices capacities at 1 to
** find paths of incrementing lengths as long as the new paths allow for a
** quicker flow of ants.
*/

void	find_paths(t_lem *lem)
{
	int		stop;
	t_path	*current_paths;
//	int		i;

	stop = 0;
	while (!stop)
	{
		clear_weights(lem);
		if (bfs(lem) == -1)
			stop = 1;
		else
		{
			if (!(current_paths = set_path_len_list(lem)))
				error(lem);
			set_ants_per_room(lem, current_paths);
			if (!lem->paths || current_paths[0].nb_ants + current_paths[0].w
					< lem->paths[0].nb_ants + lem->paths[0].w)
			{
				free(lem->paths);
				lem->paths = current_paths;
			}
			else
				stop = 1;
		}
	}
//	i = -1;
//	while (lem->paths[++i].id_first)
//		lem->paths[i].w = get_path(lem, &(lem->paths[i].rooms), lem->paths[i].i_first);
}
