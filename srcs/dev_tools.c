/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:49:21 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/27 16:44:57 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

void	display_rooms(t_lem lem)
{
	int		i;

	printf("[ ");
	i = -1;
	while (++i < lem.nb_rooms)
	{
		printf("(%s, %d)", lem.rooms[i].id, lem.rooms[i].is_full);
		if (i != lem.nb_rooms - 1)
			printf(", ");
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
		printf("%s\t(%d / %d) : ", lem.rooms[i].id, lem.rooms[i].is_full, lem.rooms[i].w);
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

void	display_d_weights(t_lem lem)
{
	int		i;

printf(">> D_WEIGTHS\n");
	i = -1;
	while (++i < lem.nb_rooms * 2)
		printf("room %.1s:\t%d\n", lem.rooms[i / 2].id, lem.split_rooms[i]);
}

void	display_weights(t_lem lem)
{
	int		i;

printf(">> WEIGTHS\n");
	i = 1;
	while (++i < lem.nb_rooms)
		printf("room %s:\t%d\n", lem.rooms[i].id, lem.rooms[i].w);
}