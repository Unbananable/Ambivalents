/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rooms_and_ants.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:12:02 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/03/28 14:29:55 by dtrigalo         ###   ########.fr       */
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

	//printf("\t\t/// IN SET_ROOMS ///\n");
	i = 0;
	//printf("\t\t1/5\n");
	while (str[i] && str[i] != '\n')
		i++;
	//printf("\t\t2/5\n");
	if ((i_end_id = is_room(str, i - 1)) == -1
			&& current_room != lem->nb_rooms - 1)
		return (ERROR);
	//printf("\t\t3/5\n");
	if (!(lem->rooms[current_room].id = ft_strsub(str, 0, i_end_id + 1)))
	{//printf("\t\terror (input = %.10s)\n", str);
		error(lem);
	}
	//printf("\t\t4/5\n");
	i = -1;
	while (++i < current_room)
		if (ft_strequ(lem->rooms[i].id, lem->rooms[current_room].id))
			error(lem);
	//printf("\t\t5/5\n");
	lem->rooms[current_room].is_full = 0;
	lem->rooms[current_room].w = 0;
	return(1);
}
