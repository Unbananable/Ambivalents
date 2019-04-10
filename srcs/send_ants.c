/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:08:08 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/10 19:04:34 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Returns the index of the room before the current room in the path it's in.
*/

static int	get_prev_room(t_lem *lem, int curr_room)
{
	int		i;

	i = -1;
	while (++i < lem->nb_rooms)
		if (lem->o_links[in(i)][out(curr_room)])
			return (i);
	return (-1);
}

/*
** Stores the instructions for the ants already in the rooms and going to the
** next room of the path they're on.
*/

static int	make_ants_move(t_lem *lem)
{
	int		curr_r;
	int		next_r;
	int		start_r;
	int		ret;

	ret = 0;
	start_r = -1;
	while (++start_r < lem->nb_rooms)
	{
		if (lem->o_links[in(start_r)][out(END)])
		{
			curr_r = start_r;
			next_r = END;
			while (curr_r != START && curr_r != -1)
			{
				if (lem->rooms[curr_r].ant_id)
				{
					ret = 1;
					if (!(lem->instr = ft_char_realloc(lem->instr,
									ft_strlen(lem->instr)
									+ ft_strlen(lem->rooms[curr_r].ant_id)
									+ ft_strlen(lem->rooms[next_r].id) + 3)))
						error(lem);
					ft_strcat(lem->instr, "L");
					ft_strcat(lem->instr, lem->rooms[curr_r].ant_id);
					ft_strcat(lem->instr, "-");
					ft_strcat(lem->instr, lem->rooms[next_r].id);
					ft_strcat(lem->instr, " ");
					if (next_r == END)
						free(lem->rooms[curr_r].ant_id);
					else
						lem->rooms[next_r].ant_id = lem->rooms[curr_r].ant_id;
					lem->rooms[curr_r].ant_id = NULL;
				}
				next_r = curr_r;
				curr_r = get_prev_room(lem, next_r);
			}
		}
	}
	return (ret);
}

static void	process_sending(t_lem *lem, int i, int *ants_left)
{
	if (lem->paths[i].nb_remaining > 0)
	{
		if (!(lem->rooms[lem->paths[i].i_first].ant_id = ft_itoa(lem->nb_ants
						- *ants_left + 1)))
			error(lem);
		lem->instr = ft_char_realloc(lem->instr, ft_strlen(lem->instr)
				+ ft_strlen(lem->rooms[lem->paths[i].i_first].ant_id)
				+ ft_strlen(lem->paths[i].id_first) + 3);
		ft_strcat(lem->instr, "L");
		ft_strcat(lem->instr, lem->rooms[lem->paths[i].i_first].ant_id);
		ft_strcat(lem->instr, "-");
		ft_strcat(lem->instr, lem->paths[i].id_first);
		ft_strcat(lem->instr, " ");
		(*ants_left)--;
		lem->paths[i].nb_remaining--;
	}
}

/*
** Builds the instructions in lem->instr. For each line, it makes the ants
** already in the rooms to the next rooms, and then sends the remaining ants
** in the different paths.
*/

void		send_ants(t_lem *lem)
{
	int		i;
	int		ants_left;
	int		first_line;

	ants_left = lem->nb_ants;
	first_line = 1;
	while (first_line || make_ants_move(lem))
	{
		first_line = 0;
		i = -1;
		while (lem->paths[++i].i_first != -1 && ants_left)
			process_sending(lem, i, &ants_left);
		lem->instr[ft_strlen(lem->instr) - 1] = '\n';
	}
	lem->instr[ft_strlen(lem->instr) - 1] = '\0';
}
