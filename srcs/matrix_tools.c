/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 17:34:14 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/28 15:05:26 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
static void	free_res(t_lem *lem, int i, int **res)
{
	while (--i >= 0)
		free(res[i]);
	free(res);
	error(lem);
}

int			**copy_matrix(t_lem *lem, int **matrix)
{
	int		i;
	int		**res;

	if (!(res = (int **)malloc(sizeof(int *) * (lem->nb_rooms * 2))))
		error(lem);
	i = -1;
	while (++i < lem->nb_rooms * 2)
	{
		if (!(res[i] = (int *)malloc(sizeof(int) * (lem->nb_rooms * 2))))
			free_res(lem, i, res);
		if (!(res[i] = ft_memcpy(res[i], matrix[i], sizeof(int)
						* lem->nb_rooms * 2)))
			free_res(lem, i, res);
	}
	return (res);
}

void		delete_matrix(t_lem *lem, int ***matrix)
{
	int		i;

	i = -1;
	while (++i < lem->nb_rooms * 2)
		free((*matrix)[i]);
	free(*matrix);
	*matrix = NULL;
}
