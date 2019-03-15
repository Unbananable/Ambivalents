/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 11:48:27 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/03/15 14:54:45 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#include <stdio.h>

static int	*make_w_list(t_lem *lem)
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

printf("\t\t\t/// IN GET_PREV_ROOM ///\n");
printf("\t\t\tx links current_room (%s):", lem->rooms[current_room].id);
int j = -1;
while(++j < lem->nb_rooms)
printf(" %d", lem->links[current_room][j]);
printf("\n");
	i = -1;
printf("\t\t\tLOOP1\n");
	while (++i < lem->nb_rooms)
{printf("\t\t\t L1: 1/2\n");
		if (lem->links[current_room][i] && (lem->rooms[i].w == lem->rooms[current_room].w + 1 || i == 0))
{printf("\t\t\t ->return prev room (%s)\n", lem->rooms[i].id);
			return (i);
printf("\t\t\t L1: 2/2");
}
}
printf("\t\t\t/LOOP1\n");
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

printf("\t\t/// IN MAKE_ANTS_MOVE ///\n");
	start_room = -1;
printf("\t\tLOOP1\n");
	while (++start_room < lem->nb_rooms)
	{
printf("\t\t L1: 1/2\n");
		if (lem->links[start_room][END] && lem->rooms[start_room].w)
		{
			current_room = start_room;
			next_room = END;
printf("\t\t LOOP2\n");
			while (current_room != START)
			{
printf("\t\t  L2: 1/3 (current_room = %s)\n", lem->rooms[current_room].id);
				if (lem->rooms[current_room].ant_id)
				{
printf("\t\t  L2: writing instruction\n");
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
printf("\t\t  L2: 2/3\n");
				next_room = current_room;
				current_room = get_prev_room(lem, next_room);
printf("\t\t  L2: 3/3\n");
			}
printf("\t\t /LOOP2\n");
		}
printf("\t\t L1: 2/2\n");
	}
printf("\n\n/LOOP1\n");
}

void		send_ants(t_lem *lem)
{
	int		i;
	int		ants_left;
	int		*w_list;

printf("\t/// IN SEND_ANTS ///\n");
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
	free(w_list);
	i = -1;
	while (++i < lem->rooms[w_list[0]].w)
		make_ants_move(lem);
}