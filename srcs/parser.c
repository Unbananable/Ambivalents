/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 16:48:26 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/11 13:19:26 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Ignores comments starting with #, and adds the information about the start
** and end room at the START (0) and END (1) indexes if the lines are
** comptible.
*/

static void	detect_command(t_lem *lem, char **str, int parse_step)
{
	if (ft_strnequ(*str, "##start\n", 8))
	{
		*str += 8;
		if (parse_step != SET_ROOMS || lem->rooms[START].id
				|| (set_rooms(lem, *str, START)) == ERROR)
			error(lem);
	}
	else if (ft_strnequ(*str, "##end\n", 6))
	{
		*str += 6;
		if (parse_step != SET_ROOMS || lem->rooms[END].id
				|| (set_rooms(lem, *str, END)) == -1)
			error(lem);
	}
}

/*
** Stores the information about the room, and increments the parsing step
** if the information about the last room has been stored
*/

static void	manage_rooms(t_lem *lem, char *str, int *parse_step)
{
	static int	current_room;

	if (set_rooms(lem, str, END + 1 + current_room) == ERROR)
		error(lem);
	if (++current_room + END + 1 == lem->nb_rooms)
		*parse_step = SET_LINKS;
}

/*
** Depending on the current parsing step and the characteristics of the line,
** stores the information given in the current line. If the information is
** incorrect, it either returns an error or ignores it and the rest of the
** input if it was supposed to record information about the links.
*/

static void	parse_line(t_lem *lem, char **str, int *parse_step)
{
	if (**str == '#')
		detect_command(lem, str, *parse_step);
	else if (*parse_step == SET_NB_ANTS)
	{
		if ((*parse_step = set_nb_ants(lem, *str)) == ERROR)
			error(lem);
	}
	else if (*parse_step == SET_ROOMS && **str != 'L')
		manage_rooms(lem, *str, parse_step);
	else if (*parse_step != SET_LINKS)
		error(lem);
	else if (*parse_step == SET_LINKS && **str != 'L')
		*parse_step = setup_o_links(lem, *str);
	else
		*parse_step = ERROR;
	if (*parse_step == ERROR)
		**str = 0;
}

void		parser(t_lem *lem)
{
	char	*cache;
	int		parse_step;
	int		i;

	cache = lem->input;
	parse_step = SET_NB_ANTS;
	i = -1;
	while (++i < lem->nb_rooms)
		if (i != END && i != START)
		{
			lem->o_links[out(i)][in(i)] = 1;
			lem->o_links[in(i)][out(i)] = 1;
		}
	while (*cache)
	{
		parse_line(lem, &cache, &parse_step);
		while (*cache && *cache != '\n')
			cache++;
		if (*cache)
			cache++;
	}
	if (!lem->rooms[START].id || !lem->rooms[END].id)
		error(lem);
}
