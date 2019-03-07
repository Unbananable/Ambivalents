/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:20:23 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/07 17:38:05 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
		error();
}

int			main(int ac, char **av)
{
	t_lem	lem;

	if (ac != 1)
		usage();
	/* PARSING */

	if ((lem.nb_rooms = count_room_and_fill_input(&lem)) <= 1)
		error();
	initialize(&lem);
	parser(&lem);
//	display_rooms(lem);
//	display_adj_matix(lem);

	/* CALCUL DU CHEMIN */

	/* AFFICHAGE */

	return (0);
}
