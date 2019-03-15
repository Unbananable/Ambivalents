/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 11:48:27 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/03/15 11:49:18 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	make_w_list(t_lem *lem)
{
	int		i;
	int		j;
	int		*w_list;

	i = -1;
	j = -1;
	if (!(w_list = (int *)malloc(sizeof(int) * (lem->nb_rooms - 2))))
		return (NULL);
	while (++i < lem->nb_rooms)
		if (lem->rooms[i].w)
			w_list[++j] = i;
	w_list[++j] = 0;
	return (w_list);
}

static int	get_prev_room(t_lem *lem, int current_room)
{
	int		i;

	i = -1;
	while (++i < lem->nb_rooms)
		if (lem->links[current_room][i] && (lem->rooms[i].w == lem->rooms[i].w + 1 || i == 0))
			return (i);
	return (-1);
}

/* Piste d'amelioration : pour l'instant la fonction parcourt toutes les rooms
de tous les chemins. Il y a peut-etre moyen de rajouter quelque chose qui lui dise
de s'arreter si il n'y a plus de fourmis sur le chemin (pour les plus grands chemins
en particulier) */
static void	make_ants_move(t_lem *lem)
{
	int		current_room;
	int		next_room;
	int		start_room;

	start_room = -1;
	while (++start_room < lem->nb_rooms)
	{
		if (lem->links[start_room][END] && lem->rooms[start_room].w)
		{
			current_room = start_room;
			next_room = END;
			while (current_room != START)
			{
				if (lem->rooms[current_room].ant_id)
				{
					ft_char_realloc(lem->instr, ft_strlen(lem->instr)
						+ ft_intlen(lem->rooms[current_room].ant_id)
						+ ft_strlen(lem->rooms[next_room].id) + 3);
					ft_strcat(lem->instr, "L");
					ft_strcat(lem->instr, ft_itoa(lem->rooms[current_room].ant_id));
					ft_strcat(lem->instr, "-");
					ft_strcat(lem->instr, lem->rooms[next_room].id);
					ft_strcat(lem->instr, " ");
					lem->rooms[next_room].ant_id = lem->rooms[next_room].ant_id;
					lem->rooms[next_room].ant_id = 0;
				}
				next_room = current_room;
				current_room = get_prev_room(lem, next_room);
			}
		}
	}
}

void		send_ants(t_lem *lem)
{
	int		i;
	int		ants_left;
	int		*w_list;

	i = -1;
	ants_left = lem->nb_ants;
	if (!(w_list = make_w_list(lem)))
		error(lem);
	while (ants_left)
	{
		make_ants_move(lem);
		while (w_list[++i] && ants_left
				&& ants_left >= lem->rooms[w_list[i]].w
				- lem->rooms[w_list[0]].w)
		{
			lem->rooms[w_list[i]].ant_id = lem->nb_ants - ants_left + 1;
			ft_char_realloc(lem->instr, ft_strlen(lem->instr)
					+ ft_intlen(lem->nb_ants - ants_left + 1)
					+ ft_strlen(lem->rooms[w_list[i]].id) + 3);
			ft_strcat(lem->instr, "L");
			ft_strcat(lem->instr, ft_itoa(lem->nb_ants - ants_left + 1));
			ft_strcat(lem->instr, "-");
			ft_strcat(lem->instr, lem->rooms[w_list[i]].id);
			ft_strcat(lem->instr, " ");
			ants_left--;
		}
		lem->instr[ft_strlen(lem->instr) - 1] = '\n';
		i = -1;
	}
	i = -1;
	while (++i < lem->rooms[w_list[0]].w)
		make_ants_move(lem);
	ft_putstr_fd(lem->instr, 1);
	ft_strdel(lem->instr);
}