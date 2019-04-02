/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:20:23 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/02 10:51:25 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#include <stdio.h>

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

	if (!(lem->rooms = (t_room *)malloc(sizeof(t_room) * lem->nb_rooms)))
		error(lem);
	i = -1;
	while (++i < lem->nb_rooms)
	{
		lem->rooms[i].w = 0;
		lem->rooms[i].ant_id = NULL;
		lem->rooms[i].id = NULL;
	}
	if (!(lem->split_rooms = (int *)malloc(sizeof(int) * lem->nb_rooms * 2)))
		error(lem);
	ft_bzero(lem->split_rooms, sizeof(int) * lem->nb_rooms * 2);
	if (!(lem->links = (int **)malloc(sizeof(int *) * lem->nb_rooms)))
		error(lem);
	i = -1;
	while (++i < lem->nb_rooms)
		if (!(lem->links[i] = (int *)malloc(sizeof(int) * lem->nb_rooms)))
		{
			while (--i >= 0)
				free(lem->links[i]);
			error(lem);
		}
		else
			ft_bzero(lem->links[i], lem->nb_rooms * sizeof(int));
	if (!(lem->instr = ft_strdup("\n")))
		error(lem);
	if (!(lem->d_links = (int **)malloc(sizeof(int *) * (lem->nb_rooms * 2))))
		error(lem);
	i = -1;
	while (++i < lem->nb_rooms * 2)
		if (!(lem->d_links[i] = (int *)malloc(sizeof(int) * (lem->nb_rooms * 2))))
		{
			while (--i >= 0)
				free(lem->d_links[i]);
			error(lem);
		}
		else
			ft_bzero(lem->d_links[i], (lem->nb_rooms * 2) * sizeof(int));
	lem->paths = NULL;
}

int			main(int ac, char **av)
{
	t_lem	lem;
	int		options;

	if ((options = get_options(&ac, &av)) == -1)
		usage();

	/* PARSING */
//printf("/// IN MAIN ///\n");
//printf("1/7\n");
	if ((lem.nb_rooms = count_rooms_and_fill_input(&lem)) <= 1)
//{printf("SORTIE-> erreur (nb_rooms = %d)\n", lem.nb_rooms);
		error(&lem); //checker ici potentiel pb de free
//}
//printf("2/7 (nb_rooms = %d)\n", lem.nb_rooms);
	initialize(&lem);
//printf("3/7\n");
	parser(&lem);
//printf("4/7\n");
//printf("nb_ants = %d\n", lem.nb_ants);
//display_rooms(lem);
//display_adj_matrix(lem);
//display_d_links(lem);

	/* CALCUL DU CHEMIN */
	if (lem.links[END][START])
		send_all_ants(&lem);
	else
	{
		edmonds_karp(&lem);
		if (!lem.paths)
			error(&lem);
//printf("5/7\n");
//display_weights(lem);
		send_ants(&lem);
	}
//printf("6/7\n");

	/* AFFICHAGE */
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
	end(&lem);
//printf("7/7\n");
	return (0);
}
