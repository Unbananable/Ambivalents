/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 10:53:45 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/22 10:27:22 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	nb_links_from(t_lem *lem, int **matrix, int index)
{
	int		res;
	int		i;

	res = 0;
	i = -1;
	while (++i < lem->nb_rooms * 2 - 2)
		if (!lem->split_rooms[i].w)
			res += matrix[index][i];
	return (res);
}


/* Suppose la creation de lem->split_rooms, qui est pareil que lem->rooms mais en
splitant in et out, et en mettant tous les .w a 0 */
static int	bfs_recursive(t_lem *lem, int **matrix, int *current_w_list, int current_w)
{
	int		*next_w_list;
	int		i;
	int		j;
	int		count;
	int		nb_links;

	i = -1;
	nb_links = 0;
	while (current_w_list[++i] != -1)
		nb_links += nb_links_from(lem, matrix, current_w_list[i]);
	if (!(next_w_list = (int *)malloc(sizeof(int) * nb_links)))
	{
		free(current_w_list);
		delete_matrix(&matrix);
		error(lem);
	}
	count = -1;
	i = -1;
	while (current_w_list[++i] != -1)
	{
		j = -1;
		while (++j < lem->nb_rooms * 2 - 2)
			if (matrix[current_w_list[i]][j] == 1 && !lem->split_rooms[j])
			{
				lem->split_rooms[j].w = current_w;
				next_w_list[++count] = j;
			}
	}
	next_w_list[++count] = -1;
	j = bfs_recursive(lem, matrix, next_w_list, current_w + 1);
	i = -1;
	while (current_w_list[++i] != -1)
		if (i != j)
			lem->split_rooms[current_w_list[i]].w = 0;
	j = current_w_list[j];
	free(current_w_list);
	return (j);
}

static void	bfs(t_lem *lem, int **tmp_flow)
{
	int		*start_list;
	int 	count;
	int		i;
	int		path_index;
	
	if (!(start_list = (int *)malloc(sizeof(int) * (nb_links_from(lem, tmp_flow, START) + 1))))
	{
		delete_matrix(tmp_flow);
		error(lem);
	}
	count = -1;
	i = 1;
	while (++i < lem->nb_rooms * 2 - 2)
	{
		if (tmp_flow[START][i] == 1)
		{
			start_list[++count] = i;
			lem->split_rooms[i].w = 1;
		}
	}
	start_list[++count] = -1; 
	path_index = bfs_recursive(lem, tmp_flow, start_list, 2);
	i = -1;
	while (start_list[++i] != -1)
		if (i != path_index)
			lem->split_rooms[start_list[i]].w = 0;
	free(start_list);
}

static int	**copy_matrix(t_lem *lem, int **matrix)
{
	int		i;
	int		**res;

	if (!(res = (int **)malloc(sizeof(int *) * (lem->nb_rooms * 2 - 2))))
		error(lem);
	i = -1;
	while (++i < lem->nb_rooms * 2 - 2)
	{
		if (!(res[i] = (int *)malloc(sizeof(int) * (lem->nb_rooms * 2 - 2))))
		{
			while (--i >= 0)
				free(res[i]);
			free(res);
			error(lem);
		}
		if (!(res[i] = ft_memcpy(res[i], matrix[i], sizeof(int) * lem->nb_rooms * 2 - 2)))
		{
			while (--i >= 0)
				free(res[i]);
			free(res);
			error(lem);
		}
	}
	return (res);
}

static void	delete_matrix(t_lem *lem, int ***matrix)
{
	int		i;

	i = -1;
	while (++i < lem->nb_rooms * 2 - 2)
		free((*matrix)[i]);
	free(*matrix);
	*matrix = NULL;
}

void    edmonds_karp(t_lem *lem)
{
    int     prev_nb_instr;
	int		current_nb_instr;
	int		stop;
	int		*paths_len;
	int		**tmp_flow;

	prev_nb_instr = MAX_INT;
	stop = 0;
	tmp_flow = copy_matrix(lem, lem->flow);

	/* CREATING THE FLOW MATRIX AND THE INITIAL ORIENTATION OF TUNNELS */

	/* IN LOOP FIND NEW PATHS AS LONG AS IT INCREASES EFFICIENCY */
	while (!stop)
	{
		bfs(lem, tmp_flow_matrix);
		paths_len = get_path_len_list(tmp_flow);
		current_nb_instr = number_of_instr(lem, paths_len);
		if (current_nb_instr <= prev_nb_instr)
		{
			delete_matrix(lem, &(lem->flow));
			lem->flow = copy_matrix(lem, tmp_flow);
		}
		else
		{
			delete_matrix(lem, &tmp_flow);
			stop = 1;
		}
	}
}
