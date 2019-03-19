/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:30:33 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/19 19:22:57 by anleclab         ###   ########.fr       */
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

static void	initialize_lem(t_lem *lem)
{
	int		i;

	if (!(lem->rooms = (t_room *)malloc(sizeof(t_room) * lem->nb_rooms)))
		error(lem);
	i = -1;
	while (++i < lem->nb_rooms)
		lem->rooms[i].id = NULL;
	if (!(lem->links = (int **)malloc(sizeof(int *) * lem->nb_rooms)))
		error(lem);
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
	if (!lem->links[0])
		error(lem);
	lem->x_max = -2147483648;
	lem->x_min = 2147483647;
	lem->y_max = -2147483648;
	lem->y_min = 2147483647;
	if (!(lem->instr = (t_instr **)malloc(sizeof(t_instr *) * lem->nb_instr)))
		error(lem);
	lem->visual.win = NULL;
	lem->visual.rend = NULL;
	lem->visual.anthill_text = NULL;
	lem->visual.font = NULL;
	if (!(lem->visual.colors = (SDL_Color *)malloc(sizeof(SDL_Color) * 2)))
		error(lem);
	lem->visual.colors[WHITE].r = 255;
	lem->visual.colors[WHITE].g = 255;
	lem->visual.colors[WHITE].b = 255;
	lem->visual.colors[WHITE].a = 255;
	lem->visual.colors[RED].r = 255;
	lem->visual.colors[RED].g = 0;
	lem->visual.colors[RED].b = 0;
	lem->visual.colors[RED].a = 255;
	lem->visual.ant_text = NULL;
}

static void	initialize_SDL(t_lem *lem)
{
	SDL_Surface	*ant_surf;

	if (SDL_Init(SDL_INIT_VIDEO))
		error(lem);
	if (TTF_Init())
		error(lem);
	if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
		error(lem);
	if (!(lem->visual.win = SDL_CreateWindow("lem-in", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0)))
		error(lem);
	if (!(lem->visual.rend = SDL_CreateRenderer(lem->visual.win, -1,
			SDL_RENDERER_ACCELERATED)))
		error(lem);
	if (SDL_SetRenderDrawColor(lem->visual.rend, 0, 0, 0, 255))
		error(lem);
	if (!(lem->visual.font = TTF_OpenFont("fonts/SignPainter.ttf", 50)))
		error(lem);
	/* On cree une texture qui accueillera toutes les images de la fourmilliere (qui sont fixes) */
	if (!(lem->visual.anthill_text = SDL_CreateTexture(lem->visual.rend,
			SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT)))
		error(lem);
	if (!(ant_surf = IMG_Load("imgs/ant.png")))
		error(lem);
	lem->visual.ant_text = SDL_CreateTextureFromSurface(lem->visual.rend, ant_surf);
	SDL_FreeSurface(ant_surf);
	if (!lem->visual.ant_text)
		error(lem);
}

int			main(int ac, char **av)
{
	t_lem		lem;
	SDL_Event	event;
	int			quit;

	if (ac != 1)
		usage();
	av += 0;
	quit = 0;
	if (!(lem.nb_rooms = count_and_fill_input(&lem)))
		usage();
	initialize_lem(&lem);
	parser(&lem);
	initialize_SDL(&lem);
	/* On dit que la texture de la foumilliere sert de renderer le temps de mettre toutes les images des rools et tunnels dedans */
	if (SDL_SetRenderTarget(lem.visual.rend, lem.visual.anthill_text))
		error(&lem);
	draw_tunnels(&lem);
	draw_rooms(&lem);
	/* On reset le renderer */
	if (SDL_SetRenderTarget(lem.visual.rend, NULL))
		error(&lem);
	/* On copie la texture de la fourmiliere dans le renderer */
	if (SDL_RenderCopy(lem.visual.rend, lem.visual.anthill_text, NULL, NULL))
		error(&lem);
	/* On affiche la fourmiliere vide */
	SDL_RenderPresent(lem.visual.rend);
	while (!quit)
	{
		if (!SDL_WaitEvent(&event))
			error(&lem);
		if (event.type == SDL_WINDOWEVENT
				&& event.window.event == SDL_WINDOWEVENT_CLOSE)
			quit = 1;
		else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_n)
			draw_ants(&lem);
	}
	end(&lem);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return (0);
}
