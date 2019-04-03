/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_adjacency_matrix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 10:38:30 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/02 18:05:49 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	find_link(t_lem *lem, t_link *search, int i, char *str)
{
	int		k;
	int		j;

	j = i;
	while (str[j] && str[j] != '\n')
		j++;
	str[i] = 0;
	str[j] = 0;
	k = -1;
	while (++k < lem->nb_rooms)
	{
		if (ft_strequ(str, lem->rooms[k].id))
			search->st = k;
		if (ft_strequ(str + i + 1, lem->rooms[k].id))
			search->nd = k;
	}
	str[i] = '-';
	str[j] = '\n';
}

static void	init_links(t_link *link1, t_link *link2)
{
	link1->st = -1;
	link1->nd = -1;
	link2->st = -1;
	link2->nd = -1;
}

/*
** For each '-' in the line, checks if the first (st) and second (nd) term
** are valid rooms. If there is no valid combination or more than one, returns
** error. Otherwise, stores the information in the adjacency matrix and returns
** the current parser step.
*/
int			fill_adjacency_matrix(t_lem *lem, char *str)
{
	int		i;
	t_link	link;
	t_link	tmp;

	init_links(&link, &tmp);
	i = -1;
	while (str[++i] && str[i] != '\n')
	{
		tmp.st = -1;
		tmp.nd = -1;
		if (str[i] == '-')
		{
			find_link(lem, &tmp, i, str);
			if (tmp.st != -1 && tmp.nd != -1)
			{
				if (link.st != -1)
					return (ERROR);
				link.st = tmp.st;
				link.nd = tmp.nd;
			}
		}
	}
	if (link.st == -1 || link.nd == -1)
		return (ERROR);
	lem->links[link.st][link.nd] = 1;
	lem->links[link.nd][link.st] = 1;
	return (SET_LINKS);
}
