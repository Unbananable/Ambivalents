/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:49:21 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/11 15:40:04 by anleclab         ###   ########.fr       */
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
	while (++i <= lem.nb_rooms && (j = -1))
	{
		if (i == 0)
			printf("  ");
		else
			printf("%d ", (i - 1) % 10);
		while (++j < lem.nb_rooms)
			if (i == 0)
				printf("%d ", j % 10);
			else
				printf("%d ", lem.links[i - 1][j]);
		printf("\n");
	}
}

void	display_weights(t_lem lem)
{
	int		i;
	int		max_weight;

	max_weight = 0;
	i = 1;
	while (++i < lem.nb_rooms)
		if (lem.links[START][i] == 1 && max_weight < lem.rooms[i].w)
			max_weight = lem.rooms[i].w;
	while (max_weight >= 0 && i == 1)
	{
		while (++i < lem.nb_rooms)
			if (lem.rooms[i].w == max_weight)
				printf("%d : %s\n", max_weight, lem.rooms[i].id);
		max_weight--;
	}
}