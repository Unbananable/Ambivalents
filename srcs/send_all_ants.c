/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_all_ants.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:15:35 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/16 19:01:37 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		send_all_ants(t_lem *lem)
{
	int		ant_id;
	int		j;
	int		ten;
	int		len_ant_id;
	int		len;
	int		endid_strlen;

	endid_strlen = ft_strlen(lem->rooms[END].id);
	ant_id = 0;
	while (++ant_id < lem->nb_ants + 1)
	{
		len_ant_id = ft_intlen(ant_id);
		len = ft_strlen(lem->instr);
		if (!(lem->instr = ft_char_realloc(lem->instr, len + len_ant_id + endid_strlen + 3)))
			error(lem);
		lem->instr[len] = 'L';
		j = -1;
		ten = 1;
		while (++j < len_ant_id)
			ten *= 10;
		j = 0;
		while (++j < len_ant_id)
		{
			lem->instr[++len] = ant_id / ten + 48;
			ten /= 10;
		}
		lem->instr[++len] = ant_id % 10 + 48;
		lem->instr[++len] = '-';
		ft_strcat(lem->instr, lem->rooms[END].id); // TO DO: Improve performance by using an index instead of strcat which goes back to the start everytime
		if (ant_id != lem->nb_ants)
			ft_strcat(lem->instr, " "); // TO DO: Improve performance by using an index instead of strcat which goes back to the start everytime
		else
			ft_strcat(lem->instr, "\0"); // TO DO: Improve performance by using an index instead of strcat which goes back to the start everytime
	}
}
