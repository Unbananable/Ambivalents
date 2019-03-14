/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 11:48:27 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/03/14 13:33:33 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/* t_lem: char *instr; */

// vieux try par insertion degolass, on peut changer ça si les perfs sont nulachiai
static void	sort_matrix(t_lem *lem)
{
	int		i;
	int		*tmp;

	i = END;
	if (!(tmp = (int *)malloc(sizeof(int) * nb_ants)))
		error(lem);
	while (++i < lem->nb_ants - 1)
	{
		if (lem->rooms[i].w > lem->rooms[i + 1].w)
		{
			tmp = lem->links[i];
			lem->links[i] = lem->links[i + 1];
			lem->links[i + 1] = tmp;
			i = END;
		}
	}
	free(tmp);
}

void		send_ants(t_lem *lem)
{
	int		i;
	int		ants_left;

	i = -1;
	ants_left = lem->nb_ants;
	sort_matrix(lem);
	while (ants_left && lem->links[START][++i] == 1 && rooms[i].w)
	{
		if (ants_left > lem->rooms[i].w)
		{
			ft_char_realloc(lem->instr, ft_strlen(lem->instr) + ft_intlen(ants_left) + ft_strlen(lem->rooms[i].id) + 3);
			ft_strcat(lem->instr, "L");
			ft_strcat(lem->instr, ft_itoa(lem->nb_ants - ants_left + 1));
			ft_strcat(lem->instr, "-");
			ft_strcat(lem->instr, lem->rooms[i].id);
			ft_strcat(lem->instr, " ");
			ants_left--;
		}
		lem->instr[ft_strlen(lem->instr) - 1] = '\n';
	}
	ft_putstr_fd(lem->instr, 1);
}
