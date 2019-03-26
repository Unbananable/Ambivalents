/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 17:25:54 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/26 17:48:44 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void		error(t_lem *lem)
{
	ft_putstr_fd("ERROR\n", 2);
	end(lem);
	exit(0);
}

static void	terminate_sdl(t_lem *lem)
{
	SDL_DestroyWindow(lem->visual.win);
	SDL_DestroyRenderer(lem->visual.rend);
	SDL_DestroyTexture(lem->visual.anthill_text);
	TTF_CloseFont(lem->visual.font);
	free(lem->visual.colors);
	SDL_DestroyTexture(lem->visual.ant_text);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void		end(t_lem *lem)
{
	int		i;

	free(lem->input);
	if (lem->rooms)
	{
		i = -1;
		while (++i < lem->nb_rooms)
			free(lem->rooms[i].id);
	}
	free(lem->rooms);
	if (lem->links)
	{
		i = -1;
		while (++i < lem->nb_rooms)
			free(lem->links[i]);
	}
	free(lem->links);
	if (lem->instr)
	{
		i = -1;
		while (++i < lem->nb_instr)
			free(lem->instr[i]);
	}
	free(lem->instr);
	terminate_sdl(lem);
}
