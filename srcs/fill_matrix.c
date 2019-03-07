/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:14:35 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/03/07 16:15:38 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	fill_adjacency_matrix(t_lem *lem) //Ne sera appelé que si l'input a deja été confirmé comme étant valide
{
	int		i;
	int		count;

	i = -1;
	while (lem->input[++i])
	{
		count += (lem->input[i] == '\n') ? 1 : 0;
		if (count > lem->nb_rooms + 1)
		{
			if (lem->input[i] == '#')
				while (lem->input[++i] != '\n')
					;
			else
			{
				// C'est là qu'on identifie le nom1 et le nom2 du link nom1-nom2 et qu'on set link[x][y] = [1 | 0]
				// Deux difficultés:
				// 1: Identifier nom1 et nom2 si un des deux, ou les deux, ont des '-'
				// 2: Sur le resultat(genre les lignes qui disent que la fourmis va dans telle ou telle room), comment identifier le fait que la room définie par link[indice_1][indice_2] est la room qui porte le nom SOME_NAME (Proposition: rajouter les coord de link dans t_room ?)
			}
		}
	}
}
