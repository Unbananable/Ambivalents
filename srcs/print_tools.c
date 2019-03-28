/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:56:36 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/03/28 14:57:10 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print_line_count(t_lem lem)
{
	int		i;
	int		count;

	count = 0;
	i = -1;
	while (lem.instr[++i])
		if (lem.instr[i] == '\n')
			count++;
	ft_putstr("line count: ");
	ft_putnbr(count);
	ft_putchar('\n');
}

void		print_paths(t_lem lem)
{
	int		i;

	ft_putstr("paths:");
	i = -1;
	while (++i < lem.nb_rooms)
		if (lem.links[START][i] && lem.split_rooms[2 * i + 1])
		{
			ft_putchar(' ');
			ft_putstr(lem.rooms[i].id);
			ft_putstr(" (");
			ft_putnbr(lem.split_rooms[2 * i + 1] / 2 + 1);
			ft_putstr(")");
		}
	ft_putchar('\n');
}

void		print_ant_nb(t_lem lem)
{
	ft_putstr("ant number: ");
	ft_putnbr(lem.nb_ants);
	ft_putchar('\n');
}
