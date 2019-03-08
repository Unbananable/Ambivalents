/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_rooms_and_fill_input.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 10:42:17 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/08 12:14:25 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		count_rooms_and_fill_input(t_lem *lem)
{
	int		i;
	int		count;
	int		stop;
	int		size;
	char	buff[BUFF_SIZE];

	i = -1;
	stop = 0;
	size = 0;
	count = -1;
	lem->input = NULL;
	while ((size = read(0, buff, BUFF_SIZE)) > 0)
	{
		buff[size - 1] = '\0';
		while (buff[++i])
		{
			if (buff[i] == '#')
				while (buff[++i] != '\n')
					;
			else
			{
				count += (buff[i] == '\n' || !stop) ? 1 : 0;
				stop = (buff[i] == '-') ? 1 : 0;
				stop = (buff[i] == ' ' && stop) ? 0 : 1;
			}
		}
		if (!(lem->input = ft_char_realloc(lem->input, sizeof(char) * (ft_strlen(lem->input) + size)))) // Pas besoin de +1 je penses mais je laisse ça là en cas de segfault hein (y)
			return (0);
		lem->input = ft_strncat(lem->input, buff, size); //strncat est plus lourd que strcat.. a-t-on vraiment besoin de la "sécurité" de strncat ? a retirer en cas de manque de perfs, et voir.
	}
	if (size < 0)
		return (0);
	return (count); // returns -1 si y a des fourmis mais 0 salles (ou parametres fourmis non valide), renvoie 0 si le nombre de salle est zero ou si read a rencontré une erreur, renvoie le nombre de salles sinon
}