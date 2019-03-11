/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:20:23 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/11 16:35:54 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#include <stdio.h>

static void	usage(void)
{
	ft_putstr_fd("usage: ./lem_in\n", 2);
	ft_putstr_fd("(Nota Bene: lem_in reads the standard input, use ", 2);
	ft_putstr_fd("./lem_in < file to read from a file)\n", 2);
	exit(0);
}

static void	initialize(t_lem *lem)
{
	int		i;

	lem->rooms = (t_room *)malloc(sizeof(t_room) * lem->nb_rooms);
	i = -1;
	while (++i < lem->nb_rooms)
		lem->rooms[i].id = NULL;
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
			else
				ft_bzero(lem->links[i], lem->nb_rooms * sizeof(int));
	}
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

printf("/// IN MAIN ///\n");
printf("1/7\n");
	if ((lem.nb_rooms = count_rooms_and_fill_input(&lem)) <= 1)
{printf("SORTIE-> erreur (nb_rooms = %d)\n", lem.nb_rooms);
		error(&lem);
}
printf("2/7 (nb_rooms = %d)\n", lem.nb_rooms);
	initialize(&lem);
printf("3/7\n");
	parser(&lem);
printf("4/7\n");
	//printf("nb_ants = %d\n\n", lem.nb_ants);
	//display_rooms(lem);
printf("5/7\n");
	//display_adj_matrix(lem);
printf("6/7\n");
	set_weights(&lem);
	display_weights(lem);
printf("7/7\n");

	/* CALCUL DU CHEMIN */

	/* AFFICHAGE */

	return (0);
}
