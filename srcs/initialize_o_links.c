/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_o_links.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:13:52 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/03 18:51:29 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Assigns the current weight to al the rooms whic are linked to the ones with
** the lower weight and which do not already have a weight. It also stores their
** indexes in a list and then swaps the 2 lists of indexes for the new list to
** be used in the next iteration of the bfs algorithm. Returns 0 when no more
** rooms are found.
*/
static int	bfs(t_lem *lem, int **current_w_list, int **next_w_list, int weight)
{
	int		i;
	int		j;
	int		count;
	int		*tmp;

	if (!(*current_w_list)[0])
		return (0);
	i = -1;
	count = -1;
	while ((*current_w_list)[++i])
	{
		j = 0;
		while (++j < lem->nb_rooms)
			if (lem->links[(*current_w_list)[i]][j] == 1 && !lem->rooms[j].w)
			{
				lem->rooms[j].w = weight;
				(*next_w_list)[++count] = j;
			}
	}
	(*next_w_list)[++count] = 0;
	tmp = *current_w_list;
	*current_w_list = *next_w_list;
	*next_w_list = tmp;
	return (1);
}

/*
** Returns the total number of links in the matrix, not counting duplicates as the matrix
** is symetrical.
*/
static int	count_links(t_lem *lem)
{
	int		i;
	int		j;
	int		res;

	i = -1;
	res = 0;
	while (++i < lem->nb_rooms)
	{
		j = i;
		while (++j < lem->nb_rooms)
			res += lem->links[i][j];
	}
	return (res);
}

/*
** Sets the weight of each room, which is its distance to the end room, using a
** breadth first search algorithm. It uses 2 lists of indexes of rooms with a
** specific weight.
*/
static void	set_weights(t_lem *lem)
{
	int		i;
	int		count;
	int		*current_w_list;
	int		*next_w_list;
	int		weight;

	i = count_links(lem);
	if (!(current_w_list = (int *)malloc(sizeof(int) * (i + 1))))
		error(lem);
	if (!(next_w_list = (int *)malloc(sizeof(int) * (i + 1))))
		error(lem);
	ft_bzero(next_w_list, sizeof(int) * (i + 1));
	ft_bzero(current_w_list, sizeof(int) * (i + 1));
	i = -1;
	count = -1;
	while (++i < lem->nb_rooms)
		if (lem->links[END][i] == 1)
		{
			lem->rooms[i].w = 1;
			current_w_list[++count] = i;
		}
	weight = 1;
	while (bfs(lem, &current_w_list, &next_w_list, ++weight))
		;
	free(current_w_list);
	free(next_w_list);
}

/*
** Initializes the oriented matrix. In the directed matrix, the rooms are
** subdivided in 'in' and 'out' subrooms to simulate the fact that the room
** behaves like a vertice with a flow of one for the Edmonds-Karp algorithm.
** The oriented matrix is not symetrical as the original links are oriented
** from the room closest to the end roomto the room furthest from the end room.
*/
void		initialize_o_links(t_lem *lem)
{
	int		i;
	int		j;

	set_weights(lem);
	i = -1;
	while (++i < lem->nb_rooms)
	{
		if (i != END && i != START)
			lem->o_links[in(i)][out(i)] = 1;
		j = i - 1;
		while (++j < lem->nb_rooms)
			if (lem->links[i][j] && (i == START || j == END
						|| (lem->rooms[i].w > lem->rooms[j].w
						&& j > END && i > END)))
				lem->o_links[out(j)][in(i)] = 1;
			else if (lem->links[i][j] && lem->rooms[i].w == lem->rooms[j].w)
			{
				lem->o_links[out(j)][in(i)] = 1;
				lem->o_links[out(i)][in(j)] = 1;
			}
			else if (lem->links[i][j])
				lem->o_links[out(i)][in(j)] = 1;
	}
}
