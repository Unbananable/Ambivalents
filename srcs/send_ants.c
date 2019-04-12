/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:08:08 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/12 18:40:40 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	make_ants_move(t_lem *lem, int *mem)
{
	int		i;
	t_plist	*cache;
	int		rval;
	int		len_next;

	rval = 0;
	i = -1;
	while (lem->paths[++i].id_first)
	{
		cache = lem->paths[i].rooms;
		while (cache->room->ant_id)
		{
			len_next = (cache->next) ? ft_strlen(cache->next->room->id) : ft_strlen(lem->rooms[END].id);
			lem->instr_len += ft_strlen(lem->instr) + ft_strlen(cache->room->ant_id) + len_next + 3;
			if(lem->instr_len > (unsigned long)(*mem * BUFF_SIZE))
				if (!(lem->instr = ft_char_realloc(lem->instr, ++(*mem) * BUFF_SIZE)))
					error(lem);
			ft_strcat(lem->instr, "L");
			ft_strcat(lem->instr, cache->room->ant_id);
			ft_strcat(lem->instr, "-");
			if (cache->next)
				ft_strcat(lem->instr, cache->next->room->id);
			else
				ft_strcat(lem->instr, lem->rooms[END].id);
			ft_strcat(lem->instr, " ");
			if (cache->next)
				cache->next->room->ant_id = cache->room->ant_id;
			else
				free(cache->room->ant_id);
			cache->room->ant_id = NULL;
			if (cache->prev)
				cache = cache->prev;
			rval = 1;
		}
		if (rval && lem->paths[i].rooms->next)
			lem->paths[i].rooms = lem->paths[i].rooms->next;
	}
	return (rval);
}

static void	process_sending(t_lem *lem, int i, int *ants_left, int *mem)
{
	if (lem->paths[i].nb_remaining > 0)
	{
		if (!(lem->rooms[lem->paths[i].i_first].ant_id = ft_itoa(lem->nb_ants
					- *ants_left + 1)))
			error(lem);
		lem->instr_len += ft_strlen(lem->rooms[lem->paths[i].i_first].ant_id) + ft_strlen(lem->paths[i].id_first) + 3;
		if (/*ft_strlen(lem->instr) + ft_strlen(lem->rooms[lem->paths[i].i_first].ant_id) + ft_strlen(lem->paths[i].id_first) + 3*/lem->instr_len > (unsigned long)(*mem * BUFF_SIZE))
			if (!(lem->instr = ft_char_realloc(lem->instr, ++(*mem) * BUFF_SIZE)))
				error(lem);
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
** Places the pointer of each path on the room linked to the start room
*/

void	set_paths_to_start(t_path *paths)
{
	int		i;

	i = -1;
	while (paths[++i].id_first)
	{
		while (paths[i].rooms->prev)
			paths[i].rooms = paths[i].rooms->prev;
	}
}


/*
** Builds the instructions in lem->instr. For each line, it makes the ants
** already in the rooms to the next rooms, and then sends the remaining ants
** in the different paths.
*/

void		send_ants(t_lem *lem)
{
	static int	mem = 0;
	int		i;
	int		ants_left;
	int		first_line;

	lem->instr_len = 1;
	ants_left = lem->nb_ants;
	first_line = 1;
	set_paths_to_start(lem->paths);
	while (first_line || make_ants_move(lem, &mem))
	{
		first_line = 0;
		i = -1;
		while (lem->paths[++i].i_first != -1 && ants_left)
			process_sending(lem, i, &ants_left, &mem);
		lem->instr[ft_strlen(lem->instr) - 1] = '\n';
	}
	lem->instr[ft_strlen(lem->instr) - 1] = '\0';
}
