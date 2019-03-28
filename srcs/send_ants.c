/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 11:48:27 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/03/28 11:58:48 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#include <stdio.h>

static int	*make_w_list(t_lem *lem)
{
	int		i;
	int		j;
	int		*w_list;
	int		tmp;

	i = -1;
	j = -1;
	if (!(w_list = (int *)malloc(sizeof(int) * (lem->nb_rooms - 2)))) // ameliorer la taille pour economie de memoire
		return (NULL);
	while (++i < lem->nb_rooms)
		if (lem->split_rooms[2 * i + 1] && lem->links[START][i])
			w_list[++j] = i;
	w_list[++j] = 0;
	if (j > 1)
	{
		i = 0;
		while (++i < j)
		{
			if (lem->split_rooms[w_list[i] * 2 + 1] < lem->split_rooms[w_list[i - 1] * 2 + 1])
			{
				tmp = w_list[i];
				w_list[i] = w_list[i - 1];
				w_list[i - 1] = tmp;
				i = 0;
			}
		}
	}
	return (w_list);
}

static int	get_prev_room(t_lem *lem, int current_room)
{
	int		i;

//printf("\t\t\t/// IN GET_PREV_ROOM ///\n");
//printf("\t\t\tx links current_room (%s):", lem->rooms[current_room].id);
//int j = -1;
//while(++j < lem->nb_rooms)
//printf(" %d", lem->links[current_room][j]);
//printf("\n");
	i = -1;
//printf("\t\t\tLOOP1\n");
	while (++i < lem->nb_rooms)
//{printf("\t\t\t L1: 1/2\n");
		if (lem->links[current_room][i] && (lem->split_rooms[2 * i] == lem->split_rooms[2 * current_room + 1] + 1 || i == 0))
//{printf("\t\t\t ->return prev room (%s)\n", lem->rooms[i].id);
			return (i);
//printf("\t\t\t L1: 2/2");
//}
//}
//printf("\t\t\t/LOOP1\n");
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

//printf("\t\t/// IN MAKE_ANTS_MOVE ///\n");
	start_room = -1;
//printf("\t\tLOOP1\n");
	while (++start_room < lem->nb_rooms)
	{
//printf("\t\t L1: 1/2\n");
		if (lem->links[start_room][END] && lem->split_rooms[start_room * 2])
		{
			current_room = start_room;
			next_room = END;
//printf("\t\t LOOP2\n");
			while (current_room != START && current_room != -1)
			{
//printf("\t\t  L2: 1/3 (current_room = %s / ant_id = %s)\n", lem->rooms[current_room].id, lem->rooms[current_room].ant_id);
				if (lem->rooms[current_room].ant_id)
				{
//printf("current_room: %d, next_room: %d\n", current_room, next_room);
//printf("lem->rooms[current_room].ant_id: %s\n", lem->rooms[current_room].ant_id);
//printf("\t\t  L2: writing instruction\n");
					lem->instr = ft_char_realloc(lem->instr, ft_strlen(lem->instr)
						+ ft_strlen(lem->rooms[current_room].ant_id)
						+ ft_strlen(lem->rooms[next_room].id) + 3);
					ft_strcat(lem->instr, "L");
					ft_strcat(lem->instr, lem->rooms[current_room].ant_id);
					ft_strcat(lem->instr, "-");
					ft_strcat(lem->instr, lem->rooms[next_room].id);
					ft_strcat(lem->instr, " ");
					if (next_room == END)
						free(lem->rooms[current_room].ant_id);
					else
						lem->rooms[next_room].ant_id = lem->rooms[current_room].ant_id;
					lem->rooms[current_room].ant_id = NULL;
				}
//printf("\t\t  L2: 2/3\n");
				next_room = current_room;
				current_room = get_prev_room(lem, next_room);
//if (current_room != -1 && next_room != -1)
//printf("\t\t  L2: 3/3 (current_room: %s / next_room: %s)\n", lem->rooms[current_room].id, lem->rooms[next_room].id);
			}
//printf("\t\t /LOOP2\n");
		}
//printf("\t\t L1: 2/2\n");
	}
//printf("\t\t/LOOP1\n");
}

void		send_ants(t_lem *lem)
{
	int		i;
	int		ants_left;
	int		nb_paths;
	int		*w_list;

//printf("\t/// IN SEND_ANTS ///\n");
//printf("\t1/4\n");
	ants_left = lem->nb_ants;
	if (!(w_list = make_w_list(lem)))
		error(lem);
	nb_paths = 0;
	while (w_list[nb_paths])
		nb_paths++;
//printf("\tx w_list =");
//int j = -1;
//while (w_list[++j] != 0)
//printf("w_list[j]: %d, j: %d\n", w_list[j], j);
//printf("r: %s\n", lem->rooms[w_list[j]].id);
//printf("\n");
//printf("\t2/4\n");
//printf("\tLOOP1\n");
	while (ants_left)
	{
//printf("\t L1: 1/3\n");
		make_ants_move(lem);
//printf("\t L1: 2/3\n");
//printf("\t LOOP2\n");
		i = -1;
		while (w_list[++i] && ants_left)
			if (lem->ants_per_room[i])
			{
//printf("\t  L2: 1/8\n");
				lem->rooms[w_list[i]].ant_id = ft_itoa(lem->nb_ants - ants_left + 1);
//printf("\t  L2: 2/8\n");
				lem->instr = ft_char_realloc(lem->instr, ft_strlen(lem->instr)
						+ ft_strlen(lem->rooms[w_list[i]].ant_id)
						+ ft_strlen(lem->rooms[w_list[i]].id) + 3);
//printf("\t  L2: 3/8\n");
				ft_strcat(lem->instr, "L");
//printf("\t  L2: 4/8\n");
				ft_strcat(lem->instr, lem->rooms[w_list[i]].ant_id);
//printf("\t  L2: 5/8\n");
				ft_strcat(lem->instr, "-");
//printf("\t  L2: 6/8\n");
				ft_strcat(lem->instr, lem->rooms[w_list[i]].id);
//printf("\t  L2: 7/8\n");
				ft_strcat(lem->instr, " ");
//printf("\t  L2: 8/8\n");
				ants_left--;
				lem->ants_per_room[i]--;
			}
//printf("\t /LOOP2\n");
		lem->instr[ft_strlen(lem->instr) - 1] = '\n';
//printf("\t L1: 3/3\n");
		i = -1;
	}
//printf("\t/LOOP1\n");
//printf("\t3/4 (HERE)\n");
	i = -1;
	while (++i <= lem->rooms[w_list[nb_paths - 1]].w)
	{
		make_ants_move(lem);
		lem->instr[ft_strlen(lem->instr) - 1] = '\n';
	}
	lem->instr[ft_strlen(lem->instr) - 1] = '\0';
	free(w_list);
//printf("\t4/4\n");
}
