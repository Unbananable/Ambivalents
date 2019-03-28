/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rooms_and_ants.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:12:02 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/03/28 15:07:36 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			set_nb_ants(t_lem *lem, char *str)
{
	int		i;

	i = -1;
	while (str[++i] && str[i] != '\n')
		if (!ft_isdigit(str[i]))
			return (-1);
	if (i == 0 || (lem->nb_ants = ft_atoi(str)) <= 0)
		return (-1);
	return (1);
}

static int	is_room(char *str, int i)
{
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (i >= 0 && str[i] >= '0' && str[i] <= '9')
		i--;
	if (i >= 0 && str[i] == '-')
		i--;
	if (i < 0 || str[i--] != ' ')
		return (-1);
	if (i < 0 || str[i] < '0' || str[i] > '9')
		return (-1);
	while (i >= 0 && str[i] >= '0' && str[i] <= '9')
		i--;
	if (i >= 0 && str[i] == '-')
		i--;
	if (i < 0 || str[i--] != ' ')
		return (-1);
	if (i < 0)
		return (-1);
	return (i);
}

int			set_rooms(t_lem *lem, char *str, int current_room)
{
	int		i;
	int		i_end_id;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if ((i_end_id = is_room(str, i - 1)) == -1
			&& current_room != lem->nb_rooms - 1)
		return (ERROR);
	if (!(lem->rooms[current_room].id = ft_strsub(str, 0, i_end_id + 1)))
		error(lem);
	i = -1;
	while (++i < current_room)
		if (ft_strequ(lem->rooms[i].id, lem->rooms[current_room].id))
			error(lem);
	lem->rooms[current_room].is_full = 0;
	lem->rooms[current_room].w = 0;
	return (1);
}
