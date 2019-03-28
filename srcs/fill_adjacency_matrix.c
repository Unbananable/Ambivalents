/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_steps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 10:38:30 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/28 14:28:31 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	init_links(t_link *link1, t_link *link2)
{
	link1->st = -1;
	link1->nd = -1;
	link2->st = -1;
	link2->nd = -1;
}

static int	setup_search(t_lem *lem, t_link *search, int i, char *str)
{
	int		k;
	int		j;

	if (str[i] == '-')
	{
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
		return (1);
	}
	return (0);
}

int			fill_adjacency_matrix(t_lem *lem, char *str)
{
	int		i;
	t_link	link;
	t_link	search;

	init_links(&link, &search);
	i = -1;
	search.st = -1;
	search.nd = -1;
	while (str[++i] && str[i] != '\n')
	{
		if (setup_search(lem, &search, i, str))
			if (search.st != -1 && search.nd != -1)
			{
				if (link.st != -1)
					return (-1);
				link.st = search.st;
				link.nd = search.nd;
			}
	}
	if (link.st == -1 || link.nd == -1)
		return (-1);
	lem->links[link.st][link.nd] = 1;
	lem->links[link.nd][link.st] = 1;
	return(2);
}
