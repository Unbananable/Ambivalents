/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 16:48:26 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/11 18:47:27 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	next_line(char *input, int *i)
{
	while (input[*i] && input[*i] != '\n')
		(*i)++;
	if (input[*i])
		(*i)++;
}

void	parser(t_lem *lem)
{
	int		i;
	int		parse_step;
	int		current_room;

	i = 0;
	parse_step = SET_NB_ANTS;
	current_room = END + 1;
	while (lem->input[i])
	{
		if (lem->input[i] == '#')
		{
			if (ft_strnequ(lem->input + i, "##start\n", 8))
			{
				i += 8;
				if (parse_step != SET_ROOMS || lem->rooms[START].id
						|| (set_rooms(lem, lem->input + i, START)) == ERROR)
					error(lem);
			}
			else if (ft_strnequ(lem->input + i, "##end\n", 6))
			{
				i += 6;
				if (parse_step != SET_ROOMS || lem->rooms[END].id
						|| (set_rooms(lem, lem->input + i, END)) == -1)
					error(lem);
			}
		}
		else if (parse_step == SET_NB_ANTS)
		{
			if ((parse_step = set_nb_ants(lem, lem->input + i)) == ERROR)
				error(lem);
		}
		else if (parse_step == 1 && lem->input[i] != 'L')
		{
			if ((parse_step = set_rooms(lem, lem->input + i, current_room)) == ERROR)
				error(lem);
			current_room++;
			if (current_room == lem->nb_rooms)
				parse_step = SET_LINKS;
		}
		else if (parse_step != SET_LINKS)
			error (lem);
		else if (parse_step == SET_LINKS && lem->input[i] != 'L')
			parse_step = fill_adjacency_matrix(lem, lem->input + i);
		else 
			parse_step = ERROR;
		if (parse_step == ERROR)
			lem->input[--i] = 0;
		next_line(lem->input, &i);
	}
}
