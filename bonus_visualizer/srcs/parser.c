/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 16:48:26 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/22 14:37:46 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	scale(t_lem *lem)
{
	int		i;

	i = -1;
	while (++i < lem->nb_rooms)
	{
		lem->rooms[i].x = (lem->rooms[i].x - lem->x_min) * lem->scale + lem->x_offset;
		lem->rooms[i].y = (lem->rooms[i].y - lem->y_min) * lem->scale + lem->y_offset;
	}
}

static void	set_scale(t_lem *lem)
{
	int		tmp;

	lem->scale = (HEIGHT - 2 * MARGIN) / (lem->y_max - lem->y_min);
	tmp = (WIDTH - 2 * MARGIN) / (lem->x_max - lem->x_min);
	if (tmp < lem->scale)
	{
		lem->scale = tmp;
		lem->x_offset = MARGIN;
		lem->y_offset = (HEIGHT - MARGIN - lem->scale * (lem->y_max - lem->y_min)) / 2;
	}
	else
	{
		lem->y_offset = MARGIN;
		lem->x_offset = (WIDTH - MARGIN - lem->scale * (lem->x_max - lem->x_min)) / 2;
	}
}

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
	int		i_visu;
	int		parse_step;
	int		current_room;

	i = 0;
	i_visu = -1;
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
		else if (parse_step == SET_ROOMS && lem->input[i] != 'L')
		{
			if ((parse_step = set_rooms(lem, lem->input + i, current_room)) == ERROR)
				error(lem);
			current_room++;
			if (current_room == lem->nb_rooms)
				parse_step = SET_LINKS;
		}
		else if (parse_step == SET_LINKS && lem->input[i] != 'L' && lem->input[i] != '\n')
			parse_step = fill_adjacency_matrix(lem, lem->input + i);
		else if (lem->input[i] == '\n' && lem->input[i + 1] == 'L')
			parse_step++;
		else if (parse_step != SET_INSTR || lem->input[i] != 'L')
			error(lem);
		else if (parse_step == SET_INSTR && lem->input[i] == 'L')
		{
			if ((parse_step = set_instructions(lem, lem->input + i, ++i_visu)) == -1)
				error(lem);
		}
		else
			parse_step = ERROR;
		if (parse_step == ERROR)
			lem->input[--i] = 0;
		next_line(lem->input, &i);
	}
	set_scale(lem);
	scale(lem);
}
