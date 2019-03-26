/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_of_instr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 17:38:29 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/26 17:39:59 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		number_of_instr(t_lem *lem, int	*plen_list)
{
	int			i;
	int			ants_left;
	int			res;

	res = 0;
	ants_left = lem->nb_ants;
	while (ants_left)
	{
		i = -1;
		while (ants_left && plen_list[++i] && (i == 0
			|| ants_left >= plen_list[i] - plen_list[0] + i))
			ants_left--;
		res++;
	}
	res += plen_list[0];
	return (res);
}
