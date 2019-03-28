/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 16:48:26 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/28 14:04:07 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	detect_command(t_lem *lem, int *i, int parse_step)
{
	if (ft_strnequ(lem->input + *i, "##start\n", 8))
	{
		*i += 8;
		if (parse_step != SET_ROOMS || lem->rooms[START].id
				|| (set_rooms(lem, lem->input + *i, START)) == ERROR)
			error(lem);
	}
	else if (ft_strnequ(lem->input + *i, "##end\n", 6))
	{
		*i += 6;
		if (parse_step != SET_ROOMS || lem->rooms[END].id
				|| (set_rooms(lem, lem->input + *i, END)) == -1)
			error(lem);
	}
}

static void	manage_rooms(t_lem *lem, int i, int *parse_step)
{
	static int	current_room = END + 1;

	if ((*parse_step = set_rooms(lem, lem->input + i, current_room)) == ERROR)
		error(lem);
	if (++current_room == lem->nb_rooms)
		*parse_step = SET_LINKS;
}

static void	parse_line_by_line(t_lem *lem, int *i, int *parse_step)
{
	if (lem->input[*i] == '#')
		detect_command(lem, i, *parse_step);
	else if (*parse_step == SET_NB_ANTS)
	{
		if ((*parse_step = set_nb_ants(lem, lem->input + *i)) == ERROR)
			error(lem);
	}
	else if (*parse_step == SET_ROOMS && lem->input[*i] != 'L')
		manage_rooms(lem, *i, parse_step);
	else if (*parse_step != SET_LINKS)
		error(lem);
	else if (*parse_step == SET_LINKS && lem->input[*i] != 'L')
		*parse_step = fill_adjacency_matrix(lem, lem->input + *i);
	else
		*parse_step = ERROR;
	if (*parse_step == ERROR)
		lem->input[--(*i)] = 0;
	while (lem->input[*i] && lem->input[*i] != '\n')
		(*i)++;
	if (lem->input[*i])
		(*i)++;
}

void		parser(t_lem *lem)
{
	int		i;
	int		parse_step;

	i = 0;
	parse_step = SET_NB_ANTS;
	while (lem->input[i])
		parse_line_by_line(lem, &i, &parse_step);
}
