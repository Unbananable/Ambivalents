/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 16:48:26 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/07 20:10:57 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	next_line(char *input, int *i)
{
	while (input[*i] && input[*i] != '\n')
		(*i)++;
	if (input[*i])
		(*i)++;
}

void	parser(t_lem *lem)
{
	int		i;
	int		parse_step; // 0=nb_ants / 1=rooms / 2=links

	i = 0;
	parse_step = 0;
	while (lem->input[i])
	{
		if (lem->input[i] == '#')
		{
			if (ft_strnequ(lem->input + i, "##start\n", 8))
			{
				if (parse_step != 1)
					error(lem); //erreur si start est a un autre endroit que dans les rooms
				// MARQUER LA ROOM COMME START
			}
			else if (ft_strnequ(lem->input + i, "##end\n", 6))
				if (parse_step != 1)
					error(lem); //erreur si start est a un autre endroit que dans les rooms
				// MARQUER LA ROOM COMME END
		}
		else if (parse_step == 0)
			parse_step = set_nb_ants(lem, lem->input + (i - 1));
		else if (parse_step == 1 && lem->input[i] != 'L')
			parse_step = set_rooms(lem, lem->input + (i - 1));
		else if (parse != 2)
			error (lem); // erreur si il n'y a pas de ligne avec le nb de fourmis, si le nombre de fourmis est 0, si une room commence par un 'L'
		else if (parse_step == 2 && lem->input[i] != 'L')
			// AJOUTER LE LINK A LA MATRICE
		else 
			input[i] = 0; // on coupe ici l'input (on ignore la suite)
			//if (input[i + 1])
			//	free(input + i + 1); // a verifier si on peut free le reste des instructions ignorees suite a une erreur
		next_line(lem->input, &i);
	}
}
