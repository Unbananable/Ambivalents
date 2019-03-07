/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nb_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 16:51:30 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/03/07 17:48:24 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"
#include <unistd.h>

/* Ajouter realloc dans libft */

int		count_room_and_fill_input(t_lem *lem)
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
				count += (buff[i] == '\n' || !stop) ? 1 : 0;
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

void	set_ant_number(t_lem *lem)
{
	int		i;

	i = -1;
	while (lem->input[++i])
		if (lem->input[i] < 48 || lem->input[i] > 57)
			break ;
	if ((i == 1 && lem->input[0] == 0) || lem->input[i] != '\n')
		return (NULL);
	lem->nb_ants = ft_atoi(lem->input);
}

void	set_rooms(t_lem *lem) // on considere que l'input est valide
{
	int		i;

	i = -1;
	while (lem->input[++i] != '\n')
		;
	if (
}
