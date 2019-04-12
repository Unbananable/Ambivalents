/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:44:58 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/12 12:40:13 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	usage(void)
{
	ft_putstr_fd("usage: ./lem_in [options]\n", 2);
	ft_putstr_fd("(Nota Bene: lem_in reads the standard input, use ", 2);
	ft_putstr_fd("./lem_in < file to read from a file)\n", 2);
	ft_putstr_fd("options: --silent --show-paths --line-count ", 2);
	ft_putstr_fd("--ant-number --full-info\n", 2);
	exit(0);
}

static void	initialize(t_lem *lem)
{
	int		i;

	lem->rooms = (t_room *)malloc(sizeof(t_room) * lem->nb_rooms);
	if (lem->rooms)
	{
		i = -1;
		while (++i < lem->nb_rooms)
		{
			lem->rooms[i].w = 0;
			lem->rooms[i].ant_id = NULL;
			lem->rooms[i].id = NULL;
		}
	}
	lem->o_links = (int **)malloc(sizeof(int *) * (lem->nb_rooms * 2));
	if (lem->o_links)
	{
		i = -1;
		while (++i < lem->nb_rooms * 2)
			if (!(lem->o_links[i] = (int *)malloc(sizeof(int)
							* (lem->nb_rooms * 2))))
			{
				while (--i >= 0)
					free(lem->o_links[i]);
				free(lem->o_links);
				lem->o_links = NULL;
			}
			else
				ft_bzero(lem->o_links[i], (lem->nb_rooms * 2) * sizeof(int));
	}
	lem->instr = ft_strdup("\n");
	lem->paths = NULL;
	if (!lem->rooms || !lem->o_links || !lem->o_links
			|| !lem->instr)
		error(lem);
}

void		print_options(t_lem lem, int options)
{
	if (!(options & (1 << ('s' - 'a'))))
	{
		ft_putstr(lem.input);
		ft_putstr(lem.instr);
		ft_putchar('\n');
	}
	if ((options & (1 << ('a' - 'a'))))
	{
		if (!(options & (1 << ('s' - 'a'))))
			ft_putchar('#');
		print_ant_nb(lem);
	}
	if ((options & (1 << ('l' - 'a'))))
	{
		if (!(options & (1 << ('s' - 'a'))))
			ft_putchar('#');
		if (lem.o_links[out(START)][in(END)])
			ft_putstr("1\n");
		else
			print_line_count(lem);
	}
	if ((options & (1 << ('p' - 'a'))))
	{
		if (!(options & (1 << ('s' - 'a'))))
			ft_putchar('#');
		print_paths(lem);
	}
	if ((options & (1 << ('r' - 'a'))))
	{
		if (!(options & (1 << ('s' - 'a'))))
			ft_putchar('#');
		print_ants_per_room(lem);
	}
}

int			main(int ac, char **av)
{
	t_lem	lem;
	int		options;

	if ((options = get_options(&ac, &av)) == -1)
		usage();
	if ((lem.nb_rooms = count_rooms_and_fill_input(&lem)) <= 1)
		error(&lem);
	initialize(&lem);
	parser(&lem);
	if (lem.o_links[out(START)][in(END)])
		send_all_ants(&lem);
	else
	{
		find_paths(&lem);
		if (!lem.paths)
			error(&lem);
		send_ants(&lem);
	}
	print_options(lem, options);
	end(&lem);
	return (0);
}
