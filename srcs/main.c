/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:20:23 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/06 16:03:35 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void	usage(void)
{
	ft_putstr("usage: ./lem-in\n");
	ft_putstr("(NB: lem-in reads the stadard input, use ./lem-in < file to ");
	ft_putstr("read from a file\n");
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
		error();
}

int			main(int ac, char **av)
{
	t_lem	lem;

	if (ac != 1)
		usage();

	/* PARSING */
	if ((lem.nb_rooms = get_nb_rooms()) <= 1)
		error();
	initialize(&lem);
	parser(&lem);
//	display_rooms(lem);
//	display_adj_matix(lem);

	/* CALCUL DU CHEMIN */

	/* AFFICHAGE */

	return (0);
}
