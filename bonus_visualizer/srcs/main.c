/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:30:33 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/15 14:14:59 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	usage(void)
{
	ft_putstr_fd("usage: ./visualizer\n", 2);
	ft_putstr_fd("(Nota Bene: visualizer reads the standard input, use ", 2);
	ft_putstr_fd("./lem_in < file | ./visualizer to read the output of lem_in", 2);
	ft_putstr_fd("with a file)\n", 2);
	exit(0);
}

static void	initialize(t_lem *lem)
{
	int		i;

	if (!(lem->rooms = (t_room *)malloc(sizeof(t_room) * lem->nb_rooms)))
		error(lem);
	i = -1;
	while (++i < lem->nb_rooms)
		lem->rooms[i].id = NULL;
	if (!(lem->links = (int **)malloc(sizeof(int *) * lem->nb_rooms)))
		error(lem);
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
	if (!(lem->visu = (t_visu **)malloc(sizeof(t_visu *) * lem->nb_instr + 1)))
		error(lem);
	if (!lem->links[0])
		error(lem);
	lem->x_max = -2147483648;
	lem->x_min = 2147483647;
	lem->y_max = -2147483648;
	lem->y_min = 2147483647;
}

int		main(int ac, char **av)
{
	t_lem	lem;
	int	quit = 0;
	SDL_Event event;

	if (ac != 1)
		usage();
	av += 0;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return (1);
	}
	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &lem.win, &lem.rend) != 0)
	{
		SDL_Log("Unable to initialize Window and Renderer: %s", SDL_GetError());
		return (1);
	}
	if ((lem.nb_rooms = count_and_fill_input(&lem)) <= 1)
		error(&lem); //checker ici potentiel pb de free
	IMG_Init(IMG_INIT_JPG);
	initialize(&lem);
	parser(&lem);
	set_weights(&lem);
	draw_tunnels(&lem);
	draw_rooms(&lem);
	SDL_RenderPresent(lem.rend);
	while (!quit)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
			quit = 1;
	}
	IMG_Quit();
	SDL_Quit();
	return (0);
}
