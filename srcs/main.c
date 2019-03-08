/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:20:23 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/08 12:15:24 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#include <stdio.h>

static void	usage(void)
{
	ft_putstr_fd("usage: ./lem_in\n", 2);
	ft_putstr_fd("(Nota Bene: lem_in reads the standard input, use ", 2);
	ft_putstr_fd("./lem_in < file to read from a file\n", 2);
}

static void	initialize(t_lem *lem)
{
	int		i;

	lem->rooms = (t_room *)malloc(sizeof(t_room) * lem->nb_rooms);
	lem->links = (int **)malloc(sizeof(int *) * lem->nb_rooms);
	if (lem->links)
	{
		i = -1;
		while (++i < lem->nb_rooms)
			if (!(lem->links[i] = (int *)malloc(sizeof(int) * lem->nb_rooms)))
			{
				while (--i >= 0)
					free(lem->links[i]);
				i = lem->nb_rooms;
			}
	}
	if (lem->links && lem->links[0])
		ft_bzero(lem->links, lem->nb_rooms * lem->nb_rooms);
	if (!lem->rooms || !lem->links || !lem->links[0])
		error(lem);
}

int			main(int ac, char **av)
{
	t_lem	lem;

	if (ac != 1)
		usage();
	av += 0;
	/* PARSING */

printf("/// IN MAIN ///");
printf("1/6");
	if ((lem.nb_rooms = count_rooms_and_fill_input(&lem)) <= 1)
		error(&lem);
printf("2/6");
	initialize(&lem);
printf("3/6");
	parser(&lem);
printf("4/6");
	display_rooms(lem);
printf("5/6");
	display_adj_matrix(lem);
printf("6/6");

	/* CALCUL DU CHEMIN */

	/* AFFICHAGE */

	return (0);
}
