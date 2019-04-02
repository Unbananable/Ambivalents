/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:52:15 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/04/02 20:05:18 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	add_sentence_to_menu(t_lem *lem, char *str, SDL_Rect text_pos)
{
	SDL_Surface	*text_surf;
	SDL_Texture *text_text;
	int			i;

	i = -1;
	while (++i < lem->nb_rooms)
	{
		if (!(text_surf = TTF_RenderText_Blended(lem->visual.font,
						str, lem->visual.colors[WHITE])))
			error(lem);
		text_text = SDL_CreateTextureFromSurface(lem->visual.rend, text_surf);
		SDL_FreeSurface(text_surf);
		if (!text_text)
			error(lem);
		if (SDL_RenderCopy(lem->visual.rend, text_text, NULL, &text_pos))
			error(lem);
		SDL_DestroyTexture(text_text);
	}
}

static void	add_syntaxed_sentence(t_lem *lem, char *str, SDL_Rect *pos,
		int delta_y)
{
	pos->y += delta_y;
	add_sentence_to_menu(lem, str, *pos);
}

void		render_menu(t_lem *lem)
{
	SDL_Rect	pos;
	char		*ants;

	pos.x = 10;
	pos.y = 10;
	pos.h = 20;
	pos.w = 250;
	add_syntaxed_sentence(lem, "    /_\\ Command Menu /_\\    ", &pos, 0);
	add_syntaxed_sentence(lem, "--------", &pos, 20);
//	add_syntaxed_sentence(lem, "Step by Step: <- / ->", &pos, 20);
	add_syntaxed_sentence(lem, "Launch Animation: A", &pos, 20);
	add_syntaxed_sentence(lem, "    Reset: [SPACE]    ", &pos, 20);
	add_syntaxed_sentence(lem, "--------", &pos, 20);
	add_syntaxed_sentence(lem, "Nombre de fourmis total:", &pos, 20);
	pos.x = 100;
	pos.h = 50;
	pos.w = 50;
	if (!(ants = ft_itoa(lem->nb_ants)))
		error(lem);
	add_syntaxed_sentence(lem, ants, &pos, 20);
	free(ants);
}
