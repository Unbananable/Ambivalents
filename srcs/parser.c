/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 16:48:26 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/08 16:08:27 by anleclab         ###   ########.fr       */
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
	int		current_room;

printf("\t/// IN PARSER ///\n");
	i = 0;
	parse_step = 0;
	current_room = 0;
printf("\tLOOP1\n");
	while (lem->input[i])
	{
		if (lem->input[i] == '#')
		{
printf("\tL1 -> comment/instr\n");
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
{printf("\tL1 -> set_nb_ants\n");
			if ((parse_step = set_nb_ants(lem, lem->input + i)) == -1)
				error(lem);
}
		else if (parse_step == 1 && lem->input[i] != 'L')
		{
printf("\tL1 -> set_rooms\n");
			if ((parse_step = set_rooms(lem, lem->input + i, &current_room)) == -1)
				error(lem);
			if (current_room == lem->nb_rooms)
				parse_step = 2;
		}
		else if (parse_step != 2)
			error (lem); // erreur si il n'y a pas de ligne avec le nb de fourmis, si le nombre de fourmis est 0, si une room commence par un 'L'
		else if (parse_step == 2 && lem->input[i] != 'L')
{printf("\tL1 -> fill_adjacency_matrix\n");
			parse_step = fill_adjacency_matrix(lem, lem->input + i);
}
		else 
			parse_step = -1;
		if (parse_step == -1)
		{
			i--;
			lem->input[i] = 0;// on coupe ici l'input (on ignore la suite)
			//if (input[i + 1])
			//	free(input + i + 1); // a verifier si on peut free le reste des instructions ignorees suite a une erreur
		}
			
		next_line(lem->input, &i);
	}
printf("\t/LOOP1\n");
}
