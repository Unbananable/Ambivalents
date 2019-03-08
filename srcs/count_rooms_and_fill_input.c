/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_rooms_and_fill_input.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 10:42:17 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/08 16:41:14 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#include <stdio.h>

static void	add_buffer(t_lem *lem, char *buff, int rd_size)
{
	if (!(lem->input = ft_char_realloc(lem->input, sizeof(char)
			* (ft_strlen(lem->input) + rd_size)))) // Pas besoin de +1 je penses mais je laisse ça là en cas de segfault hein (y)
{printf("\t->SORTIE (erreur : add_buffer)\n");
		error(lem);
}
	lem->input = ft_strncat(lem->input, buff, rd_size); //strncat est plus lourd que strcat.. a-t-on vraiment besoin de la "sécurité" de strncat ? a retirer en cas de manque de perfs, et voir.
}

static int	is_room(char *str, int i)
{
	if (str[i] < '0' || str[i] > '9')
		return (0);
	while (i >= 0 && str[i] >= '0' && str[i] <= '9')
		i--;
	if (i >= 0 && str[i] == '-')
		i--;
	if (i < 0 || str[i--] != ' ')
		return (0);
	if (i < 0 || str[i] < '0' || str[i] > '9')
		return (0);
	while (i >= 0 && str[i] >= '0' && str[i] <= '9')
		i--;
	if (i >= 0 && str[i] == '-')
		i--;
	if (i < 0 || str[i--] != ' ')
		return (0);
	if (i < 0)
		return (0);
	return (1);
}

int			count_rooms_and_fill_input(t_lem *lem)
{
	int		i;
	int		count;
	int		stop;
	int		rd_size;
	char	buff[BUFF_SIZE + 1];

printf("\t/// IN COUNT_ROOMS_AND_FILL_INPUT ///\n");
printf("\t1/2\n");
	rd_size = 0;
	count = 0;
	stop = -1;
	lem->input = NULL;
printf("\tLOOP1\n");
	while ((rd_size = read(0, buff, BUFF_SIZE)) > 0)
	{
		buff[rd_size] = 0;
		i = ft_strlen(lem->input) - 1;
		add_buffer(lem, buff, rd_size);
		while ((stop == 0 || stop == -1) && lem->input[++i])
			if (lem->input[i] == '#')
				while (lem->input[i] && lem->input[i] != '\n')
					i++;
			else if (lem->input[i] == '\n')
			{
				if (stop == -1)
					stop = 0;
				else if (is_room(lem->input, i - 1))
					count++;
				else
					stop = 1;				
			}
	}
printf("\t/LOOP1\n");
	if (rd_size < 0)
{printf("\t->SORTIE (erreur lecture)\n");
		return (0);
}
printf("\t2/2\n");
	return (count); // returns -1 si y a des fourmis mais 0 salles (ou parametres fourmis non valide), renvoie 0 si le nombre de salle est zero ou si read a rencontré une erreur, renvoie le nombre de salles sinon
}