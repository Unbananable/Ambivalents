/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:32:13 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/03/26 19:32:51 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void		event_manager(t_lem lem)
{
	int		quit;
	SDL_Event	event;

	quit = 0;
	while (!quit)
	{
		if (!SDL_WaitEvent(&event))
			error(&lem);
		if ((event.type == SDL_WINDOWEVENT
					&& event.window.event == SDL_WINDOWEVENT_CLOSE)
				|| (event.type == SDL_KEYUP
					&& event.key.keysym.sym == SDLK_ESCAPE))
			quit = 1;
		else if (event.type == SDL_KEYUP && (event.key.keysym.sym == SDLK_RIGHT
				|| event.key.keysym.sym == SDLK_LEFT))
			draw_ants(&lem, event.key.keysym.sym);
	}
}
