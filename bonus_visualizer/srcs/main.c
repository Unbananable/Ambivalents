/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:30:33 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/12 16:11:06 by anleclab         ###   ########.fr       */
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
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return (1);
	}
/*	if (!(lem.win = SDL_CreateWindow("Some Awesome Visualizer, made by awesome people", 0, 0, WIDTH, HEIGHT, 0)))
	{
		SDL_Log("Unable to initialize Window: %s", SDL_GetError());
		return (1);
	};
	if (!(lem.rend = SDL_CreateRenderer(lem.win, -1, 0)))
	{
		SDL_Log("Unable to initialize Renderer: %s", SDL_GetError());
		return (1);
	}*/
	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &lem.win, &lem.rend) != 0)
	{
		SDL_Log("Unable to initialize Window and Renderer: %s", SDL_GetError());
		return (1);
	}
	if ((lem.nb_rooms = count_rooms_and_fill_input(&lem)) <= 1)
		error(&lem); //checker ici potentiel pb de free
	IMG_Init(IMG_INIT_PNG);
	initialize(&lem);
	parser(&lem);
	set_weights(&lem);

	int	i = -1;
	int	j = -1;

	SDL_SetRenderDrawColor(lem.rend, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(lem.rend);
	while (++i < lem.nb_rooms - 1)
	{
		j = i;
		while (++j < lem.nb_rooms)
			if (lem.links[i][j] == 1)
				SDL_RenderDrawLine(lem.rend, lem.rooms[i].x, lem.rooms[i].y, lem.rooms[j].x, lem.rooms[j].y);
	}
	draw_rooms(&lem);
	SDL_RenderPresent(lem.rend);

	IMG_Quit();
	SDL_Quit();
	return (0);
}

/*

A VERIFIER MAIS POUR LES POIDS JE CROIS QU ON FAIT COMME CA

#include <SDL/SDL_ttf.h

	TTF_Font	*police = NULL;
	SDL_Color	rouge = {0, 0, 0};
	SDL_Surface	*texte = NULL;
	SDL_Rect	position;
	SDL_Surface	*ecran = NULL;

	if (TTF_Init() == -1)
		error(lem);
	ecran = CREATION SURFACE;
	police = TTF_OpenFont("file.ttf", 14) //Choisir la police et la stocker dans le dossier
	texte = TTF_RenderText_Shaded(police, "Bonjour Anleclab", rouge);
	position.x = 10;
	position.y = 10;
	SDL_BlitSurface(textem NULL, ecran, &position);
	TTF_CloseFont(police);
	TTF_Quit();

 */
