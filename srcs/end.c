/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 17:25:54 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/10 18:46:16 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	end(t_lem *lem)
{
	int		i;

	free(lem->input);
	if (lem->rooms)
	{
		i = -1;
		while (++i < lem->nb_rooms)
		{
			free(lem->rooms[i].id);
			free(lem->rooms[i].ant_id);
		}
	}
	free(lem->rooms);
	if (lem->links)
	{
		i = -1;
		while (++i < lem->nb_rooms)
			free(lem->links[i]);
	}
	free(lem->links);
	if (lem->o_links)
	{
		i = -1;
		while (++i < 2 * lem->nb_rooms)
			free(lem->o_links[i]);
	}
	free(lem->o_links);
	free(lem->instr);
	free(lem->paths);
}

void	error(t_lem *lem)
{
	end(lem);
	ft_putstr_fd("The program has ended.\n", 2);
	exit(0);
}
