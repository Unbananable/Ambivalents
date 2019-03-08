/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_steps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 10:38:30 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/08 11:42:01 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
				|| str[i + 1] != '\n')
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
	if (!(lem->rooms[count].id = ft_strnew(j)))
		return (-1);
	i = -1;
	j = -1;
	while (str[++i] && str[++i] != ' ')
		lem->rooms[count].id[++j] = str[i++];
	lem->rooms[count].id[++j] = '\n';
	lem->rooms[count].is_full = 0;
	if (++count == lem->nb_rooms)
		return (2);
	return (1);
/* A la fin, on check si on a atteint la derniere room ou pas, pour savoir si on peut passer à l'étape des links(2) ou continuer avec les rooms(1). */
}

static void init_links(t_link *link1, t_link *link2)
{
    link1->st = -1;
    link1->nd = -1;
    link2->st = -1;
    link2->nd = -1;
}

int         fill_adjacency_matrix(t_lem *lem, char *str)
{
    int     i;
    int     j;
    int     k;
    t_link  link;
    t_link  search;

    init_links(&link, &search);
    i = 0;
    search.st = -1;
    search.nd = -1;
    while (str[i] && str[i] != '\n')
    {
        if (str[i] == '-')
        {
            j = i;
            while (str[j] && str[j] != '\n')
                j++;
            k = -1;
            while (++k < lem->nb_rooms)
            {
                if (ft_strnequ(str, lem->rooms[k].id, i - 1))
                    search.st = k;
                if (ft_strnequ(str + i + 1, lem->rooms[k].id, j - i - 1))
                    search.nd = k;
            }
            if (search.st != -1 && search.nd != -1)
            {
                if (link.st != -1)
                    return (-1);
                link.st = search.st;
                link.nd = search.nd;
            }
        }
        i++;
    }
    lem->links[link.st][link.nd] = 1;
    lem->links[link.nd][link.st] = 1;
    return(2);
}