/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_all_ants.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:15:35 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/10 18:40:01 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		send_all_ants(t_lem *lem)
{
	int		i;
	int		endid_strlen;
	char	*ant_id;

	endid_strlen = ft_strlen(lem->rooms[END].id);
	i = -1;
	while (++i < lem->nb_ants)
	{
		if (!(ant_id = ft_itoa(i)))
			error(lem);
		if (!(lem->instr = ft_char_realloc(lem->instr, ft_strlen(lem->instr)
				+ ft_strlen(ant_id) + endid_strlen + 3)))
			error(lem);
		ft_strcat(lem->instr, "L"); // TO DO: Improve performance by using an index instead of strcat which goes back to the start everytime
		ft_strcat(lem->instr, ant_id); // TO DO: Improve performance by using an index instead of strcat which goes back to the start everytime
		ft_strcat(lem->instr, "-"); // TO DO: Improve performance by using an index instead of strcat which goes back to the start everytime
		ft_strcat(lem->instr, lem->rooms[END].id); // TO DO: Improve performance by using an index instead of strcat which goes back to the start everytime
		if (i != lem->nb_ants - 1)
			ft_strcat(lem->instr, " "); // TO DO: Improve performance by using an index instead of strcat which goes back to the start everytime
		else
			ft_strcat(lem->instr, "\0"); // TO DO: Improve performance by using an index instead of strcat which goes back to the start everytime
		ft_strdel(&ant_id);
	}
}
