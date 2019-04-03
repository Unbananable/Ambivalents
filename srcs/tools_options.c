/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:56:36 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/04/03 15:01:57 by dtrigalo         ###   ########.fr       */
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
	while (lem.paths[++i].id_first)
	{
		ft_putchar(' ');
		ft_putstr(lem.paths[i].id_first);
		ft_putstr(" (");
		ft_putnbr(lem.paths[i].w);
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

void		print_ants_per_room(t_lem lem)
{
	int		i;

	i = -1;
	ft_putstr("ants per room:");
	while (lem.paths[++i].index_first != -1)
	{
		ft_putchar(' ');
		ft_putnbr(lem.paths[i].nb_ants);
	}
	ft_putchar('\n');
}
