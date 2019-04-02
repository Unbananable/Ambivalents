/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:08:08 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/02 18:15:47 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


/*
static int	get_prev_room(t_lem *lem, int current_room)
{
	int		i;

	i = -1;

	while (++i < lem->nb_rooms)

		if (lem->d_links[2 * i][2 * current_room + 1])

			return (i);

	return (-1);
}

static void	make_ants_move(t_lem *lem)
{
	int		current_room;
	int		next_room;
	int		start_room;

	start_room = -1;

	while (++start_room < lem->nb_rooms)
	{

		if (lem->d_links[2 * start_room][2 * END + 1])
		{
			current_room = start_room;
			next_room = END;

			while (current_room != START && current_room != -1)
			{

				if (lem->rooms[current_room].ant_id)
				{

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
	int		nb_paths;

	ants_left = lem->nb_ants;

	while (ants_left)
	{

		make_ants_move(lem);

		i = -1;
		while (lem->paths[++i].index_first != -1 && ants_left)

			if (lem->paths[i].nb_remaining > 0)
			{

				if (!(lem->rooms[lem->paths[i].index_first].ant_id = ft_itoa(lem->nb_ants - ants_left + 1)))
					error(lem);

				lem->instr = ft_char_realloc(lem->instr, ft_strlen(lem->instr)
						+ ft_strlen(lem->rooms[lem->paths[i].index_first].ant_id)
						+ ft_strlen(lem->paths[i].id_first) + 3);

				ft_strcat(lem->instr, "L");

				ft_strcat(lem->instr, lem->rooms[lem->paths[i].index_first].ant_id);

				ft_strcat(lem->instr, "-");

				ft_strcat(lem->instr, lem->paths[i].id_first);

				ft_strcat(lem->instr, " ");

				ants_left--;
				lem->paths[i].nb_remaining--;
			}

		lem->instr[ft_strlen(lem->instr) - 1] = '\n';

	}

	nb_paths = -1;
	while (lem->paths[++nb_paths].index_first != -1)
		;
	while (++i <= lem->paths[nb_paths - 1].w + 1)
	{
		make_ants_move(lem);
		lem->instr[ft_strlen(lem->instr) - 1] = '\n';
	}
	lem->instr[ft_strlen(lem->instr) - 1] = '\0';

}
*/