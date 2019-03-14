/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 11:48:27 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/03/14 19:33:26 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//ft_intlen a rajouter a la libft

static void	make_w_list(t_lem *lem)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!(lem->w_list = (int *)malloc(sizeof(int) * (lem->nb_rooms - 2))))
		error(lem);
	while (++i < lem->nb_rooms)
		if (lem->rooms[i].w)
			lem->w_list[++j] = i;
	lem->w_list[++j] = 0;
}

static int	search_next_room(t_lem *lem, int i_room)
{
	int	j;

	j = 0;
	while (++j < nb_rooms)
		if (lem->links[i][j] == 1 && (lem->rooms[j].w || j == 1))
			return (j);
	return (-1);
}

static void	make_ants_move(t_lem *lem)
{
	int		i;
	int		next_room;

	i = 1;
	while (++i < lem->nb_rooms)
	{
		if (lem->rooms[i].is_full)
		{
/* Alors la suite est bien mignonne mais il va manquer le numero de la fourmi, donc je propose d associer une case a sa fourmi (et 0 en l absence de fourmi, vu que les fourmi ont un idx >= 1 (cf. t_room) */
			if (!(next_room = search_next_room(lem, i)) == -1)
				error(lem);
			ft_char_realloc(lem->instr, ft_strlen(lem->instr)
					+ ft_intlen(lem->rooms[i].ant_id)
					+ ft_strlen(lem->rooms[next_room].id) + 3);
			ft_strcat(lem->instr, "L");
			ft_strcat(lem->instr, ft_itoa(lem->rooms[i].ant_id));
			ft_strcat(lem->instr, "-");
			ft_strcat(lem->instr, lem->rooms[next_room].id);
			ft_strcat(lem->instr, " ");
			if (next_room != END)
			{
				lem->rooms[next_room].is_full = 1;
				lem->rooms[next_room].ant_id = lem->rooms[i].ant_id;
			}
			lem->rooms[i].is_full = 0;
			lem->rooms[i].ant_id = 0;
		}
	}
}

void		send_ants(t_lem *lem)
{
	int		i;
	int		ants_left;

	i = -1;
	ants_left = lem->nb_ants;
	make_w_list(lem);
	while (ants_left)
	{
		while (lem->w_list[++i] && ants_left
				&& ants_left >= lem->rooms[lem->w_list[i]].w
				- lem->rooms[lem->w_list[0]].w)
		{
			lem->rooms[lem->w_list[i]].ant_id = lem->nb_ants - ants_left + 1;
			lem->rooms[lem->w_list[i]].is_full = 1;
			ft_char_realloc(lem->instr, ft_strlen(lem->instr)
					+ ft_intlen(lem->nb_ants - ants_left + 1)
					+ ft_strlen(lem->rooms[lem->w_list[i]].id) + 3); // 3 pour '-',' ' et 'L'
			ft_strcat(lem->instr, "L");
			ft_strcat(lem->instr, ft_itoa(lem->nb_ants - ants_left + 1));
			ft_strcat(lem->instr, "-");
			ft_strcat(lem->instr, lem->rooms[lem->w_list[i]].id);
			ft_strcat(lem->instr, " ");
			ants_left--;
		}
		make_ants_move(lem);
		lem->instr[ft_strlen(lem->instr) - 1] = '\n';
		i = -1;
	}
	ft_putstr_fd(lem->instr, 1);
	ft_strdel(lem->instr);
}
