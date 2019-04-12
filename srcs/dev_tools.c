/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:49:21 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/12 16:57:40 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	display_rooms(t_lem lem)
{
	int		i;

printf("/// ROOMS WITH ANTS\n");
	printf("[ ");
	i = -1;
	while (++i < lem.nb_rooms)
	{
		if (lem.rooms[i].ant_id)
		printf("(%s : %s), ", lem.rooms[i].id, lem.rooms[i].ant_id);
	}
	printf(" ]\n");
}

void	display_adj_matrix(t_lem lem)
{
	int		i;
	int		j;

	i = -1;
	while (++i < lem.nb_rooms && (j = -1))
	{
		printf("%s\t(%d) : ", lem.rooms[i].id, lem.rooms[i].w);
		while (++j < lem.nb_rooms)
			printf("%d ", lem.links[i][j]);
		printf("\n");
	}
}

void	display_d_links(t_lem lem, int **matrix)
{
	int		i;
	int		j;

	i = -1;
	printf("   \t");
	while (++i < (lem.nb_rooms) * 2)
		printf("%.1s ", lem.rooms[i / 2].id);
	printf("\n");
	i = -1;
	while (++i < (lem.nb_rooms) * 2 && (j = -1))
	{
		printf("(%.1s)\t", lem.rooms[i / 2].id);
		while (++j < (lem.nb_rooms) * 2)
			if (matrix[i][j])
				printf("%d ", matrix[i][j]);
			else
				printf("  ");
		printf("\n");
	}
}

void	display_weights(t_lem lem)
{
	int		i;

printf(">> WEIGTHS\n");
	i = 1;
	while (++i < lem.nb_rooms)
		printf("room %s:\t%d\n", lem.rooms[i].id, lem.rooms[i].w);
}

void	display_paths(t_path *paths)
{
	int		i;

	i = -1;
	if (!paths)
	{
		printf(">> NO PATHS\n");
		return ;
	}
	printf(">> PATHS\n");
	while (paths[++i].i_first != -1)
	{
		printf("%d\t", i);
		printf("%s\t", paths[i].id_first);
		printf("%d\t", paths[i].i_first);
		printf("%d\t", paths[i].w);
		printf("%d\t", paths[i].nb_ants);
		printf("%d\n", paths[i].nb_remaining);
	}
}

void	display_path_complete(t_path path)
{
	t_plist	*cache;

	if (!path.rooms)
	{
		printf("the path was not initialised\n");
		return ;
	}
	printf("Path %s (len = %d, nb_ant = %d) : ", path.id_first, path.w, path.nb_ants);
	cache = path.rooms;
	while (cache)
	{
		printf("%s -> ", cache->room->id);
		cache = cache->next;
	}
	printf("(null)\n");
}