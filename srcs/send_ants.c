/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:08:08 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/16 20:03:42 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	make_ants_move(t_lem *lem, int *mem)
{
	int		i;
	t_plist	*cache;
	int		rval;
	int		len_next;
	int	len_ant_id;
	int	pow;
	int	len;
	int	tmp;



	rval = 0;
	i = -1;
	while (lem->paths[++i].id_first)
	{
		cache = lem->paths[i].rooms;
		while (cache->room->ant_id)
		{
			len_next = (cache->next) ? ft_strlen(cache->next->room->id) : ft_strlen(lem->rooms[END].id);
			len_ant_id = ft_intlen(cache->room->ant_id);
			len = lem->instr_len;
			lem->instr_len += len_ant_id + len_next + 3;
			if(lem->instr_len > (unsigned long)(*mem * BUFF_SIZE))
				if (!(lem->instr = ft_char_realloc(lem->instr, ++(*mem) * BUFF_SIZE)))
					error(lem);
			lem->instr[len] = 'L';
			pow = 1;
			tmp = cache->room->ant_id;
			while (tmp / pow >= 10)
				pow *= 10;
			while (pow)
			{
				lem->instr[++len] = tmp / pow + 48;
				tmp %= pow;
				pow /= 10;
			}
			lem->instr[++len] = '-';
			if (cache->next)
				ft_strcat(lem->instr, cache->next->room->id);
			else
				ft_strcat(lem->instr, lem->rooms[END].id);
			ft_strcat(lem->instr, " ");
			if (cache->next)
				cache->next->room->ant_id = cache->room->ant_id;
			cache->room->ant_id = 0;
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
	int	len_ant_id;
	int	ten;
	int	j;
	int	len;

	j = 0;
	ten = 1;
	if (lem->paths[i].nb_remaining > 0)
	{
		len_ant_id = ft_intlen(lem->nb_ants - *ants_left + 1);
		lem->rooms[lem->paths[i].i_first].ant_id = lem->nb_ants - *ants_left + 1;
		len = lem->instr_len;
		lem->instr_len += len_ant_id + ft_strlen(lem->paths[i].id_first) + 3;
		if (lem->instr_len > (unsigned long)(*mem * BUFF_SIZE))
			if (!(lem->instr = ft_char_realloc(lem->instr, ++(*mem) * BUFF_SIZE)))
				error(lem);
		lem->instr[len] = 'L';
		while (++j < len_ant_id)
			ten *= 10;
		j = 0;
		while (++j < len_ant_id)
		{
			lem->instr[++len] = (lem->nb_ants - *ants_left + 1) / ten + 48;
			ten /= 10;
		}
		lem->instr[++len] = (lem->nb_ants - *ants_left + 1) % 10 + 48;
		lem->instr[++len] = '-';
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
