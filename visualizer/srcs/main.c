/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:30:33 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/11 18:58:46 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	usage(void)
{
	ft_putstr_fd("usage: ./visualizer\n", 2);
	ft_putstr_fd("(Nota Bene: visualizer reads the standard input, use ", 2);
	ft_putstr_fd("./lem_in < file | ./visualizer to read the output of lem_in");
	ft_putstr_fd("with a file)\n", 2);
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

int		main(int ac, char **av)
{
	t_lem	lem;

	if (ac != 1)
		usage();
	av += 0;
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		ft_putstr_fd("error: couldn't initialize SDL\n", 2);
		return (1);
	}
	if ((lem.nb_rooms = count_rooms_and_fill_input(&lem)) <= 1)
		error(&lem); //checker ici potentiel pb de free
	initialize(&lem);
	parser(&lem);
	set_weights(&lem);
}
