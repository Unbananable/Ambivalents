/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nb_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 16:51:30 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/03/07 20:48:27 by dtrigalo         ###   ########.fr       */
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

int		set_nb_ants(t_lem *lem, char *str)
{
	/* Ici j'ai fait un while qui break dès qu'on a un non-digit
	 * Du coup,
	 * - Si jamais on a un caractère non valide (espace non compris)
	 *   avant ou dans le nombre, ça break, et atoi==0 donc return -1
	 * - Si on a que des char invalides, c'est pareil
	 * - Si on a des invalides apres le nombre, on rentre
	 *   dans le if a cause de str[i+1] != '\n'
	 * - Si on a que des espaces avant ou apres le nombre, c 'est pareil,
	 *   à la difference près que atoi ne rendra pas forcement 0, mais
	 *   set_nb_ants return -1 à cause de str[i+1] != '\n'
	 * - Si on a "" ou "0", on rentre dans le if, avec respectivement
	 *   i == 0 et (i==1 && str[0] == 0), donc return -1
	 * - Si on a un nombre valide, on break a la toute fin en atteignant '\n',
	 *   on rentre pas dans le if, on return 1 et on a set nb_ants via atoi
	 *
	 *   Je crois que j'ai fait le tour, dis moi si tu vois autre chose ;) */
	int		i;

	i = -1;
	while (str[++i] && str[i] != '\n')
		if (!ft_isdigit(str[i]))
			break ;
	if ((lem->nb_ants = ft_atoi(str)) == 0 || (i == 1
				&& str[0] == 0) || i == 0 || str[i] == '\n'
				|| str[i + 1] != '\n')
		return (-1);
	return (1);
}

int		set_rooms(t_lem *lem, char *str)
{
	static int	count = 0;
	int		i;
	int		j;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
		{
			j = i;
			while (ft_isdigit(str[++i]))
				;
			if (str[i] == ' ')
			{
				while (ft_isdigit(str[++i]))
					;
				if (str[i] != '\n')
					return (-1);
			}
			else
				return (-1);
		}
		else
			return (-1);
	}
/* Dans le while précédent, j'ai voulu tester le format de la ligne de room, (j'ai au passage trouvé la len du nom), si le format est incorrect, on return -1, sinon on continue dans la partie ci-dessous, qui set le nom dans l'id adequat. */
	if (!(lem->rooms[count]->id = ft_strnew(j)))
		return (-1);
	i = -1;
	j = -1;
	while (str[++i] && str[++i] != ' ')
		lem->rooms[count]->id[++j] = str[i++];
	lem->rooms[count]->id[++j] = '\n';
	lem->rooms[count]->is_full = 0;
	if (++count == lem->nb_rooms)
		return (2);
	return (1);
/* A la fin, on check si on a atteint la derniere room ou pas, pour savoir si on peut passer à l'étape des links(2) ou continuer avec les rooms(1). */
}
