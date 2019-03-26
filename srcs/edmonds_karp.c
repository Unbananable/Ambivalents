/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 10:53:45 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/26 17:08:21 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

static int	bfs_recursive(t_lem *lem, int **matrix, int *current_w_list, int current_w)
{
	int		*next_w_list;
	int		i;
	int		j;
	int		count;
	int		nb_links;

	/* On initialise la nouvelle liste de rooms auquelles on met un poids */
	i = -1;
	nb_links = 0;
	while (current_w_list[++i] != -1)
		nb_links += nb_links_from(lem, matrix, current_w_list[i]);
	if (nb_links != 0) // Si il y a encore des rooms disponibles
	{
		if (!(next_w_list = (int *)malloc(sizeof(int) * (nb_links + 1))))
		{
			free(current_w_list);
			delete_matrix(lem, &matrix);
			error(lem);
		}
		count = -1;
		i = -1;
		while (current_w_list[++i] != -1)
		{
			j = 0;
			while (++j < lem->nb_rooms * 2 - 2)
				if (matrix[current_w_list[i]][j] == 1 && !lem->split_rooms[j].w)
				{
					/* Condition d'arret : la room est liee a END : on reset le poids des rooms que l'on a assigne durant cette occurence, on free e tableau, et on retourne l'index de la room dans current_w_list qui est en lien avec le plus petit chemin */
					if (j == END)
					{
						while (count >= 0)
							lem->split_rooms[next_w_list[count--]].w = 0;
						free(next_w_list);
						return (i);
					}
					/* Sinon on set le poids et on rajoute la room a la liste */
					lem->split_rooms[j].w = current_w;
					next_w_list[++count] = j;
				}
		}
		next_w_list[++count] = -1;
		j = bfs_recursive(lem, matrix, next_w_list, current_w + 1);
	}
	else // Si il n'y a plus de rooms dispo : il n'y a pas de chemin supplementaire entre start et end
		j = -1;
	i = -1;
	while (current_w_list[++i] != -1)
		if (i != j)
			lem->split_rooms[current_w_list[i]].w = 0;
	j = (j == -1) ? -1 : current_w_list[j];
	free(current_w_list);
	return (j);
}

static void	bfs(t_lem *lem, int **tmp_flow)
{
	int		*start_list;
	int 	count;
	int		i;
	int		path_index;

	/* On fait la premiere iteration pour set les poids des rooms liees a START a 1 et faire une liste de leurs indices */
	// - il est probablement possible de le faire en une seule fonction recursive avec une condition si la liste est NULL pour le debut
	if (!(start_list = (int *)malloc(sizeof(int) * (nb_links_from(lem, tmp_flow, START) + 1))))
	{
		delete_matrix(lem, &tmp_flow);
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
	/* bfs_recursive retourne l'index dans la liste du chemin choisi : on lui laisse son poids et on reset les autres a 0 */
	path_index = bfs_recursive(lem, tmp_flow, start_list, 2);
	i = -1;
	while (start_list[++i] != -1)
		if (i != path_index)
			lem->split_rooms[start_list[i]].w = 0;
	free(start_list);
}

static int	*get_path_len_list(t_lem *lem, int **matrix)
{
	int		*res;
	int		nb_paths;
	int		i;
	int		j;
	int		tmp;

	nb_paths = 0;
	i = -1;
	while (++i < lem->nb_rooms * 2)
		if (lem->split_rooms[i].w)
			nb_paths++;
	if (!(res = (int *)malloc(sizeof(int) * (nb_paths + 1)))
	{
		delete_matrix(lem, &matrix);
		error(lem);		
	}
	j = -1;
	i = 2;
	while (++i < lem->rooms * 2)
		if (lem->split_rooms[i].w)
			res[++j] = i;
	res[++j] = 0;
	i = -1;
	while (++i < nb_paths)
	{
		j = -1;
		while (res[++j + 1])
			if (res[j] > res[j + 1])
			{
				tmp = res[j];
				res[j + 1] = res[j];
				res[j] = tmp;
			}
	}	
	return (res);
}

void    edmonds_karp(t_lem *lem)
{
    int     prev_nb_instr;
	int		current_nb_instr;
	int		stop;
	int		*paths_len;
	int		**tmp_flow;

	prev_nb_instr = 2147483647;
	stop = 0;
	tmp_flow = copy_matrix(lem, lem->d_links); // On opere sur une copie de la matrice pour pouvoir revenir en arriere si le nombre d'instructions n'est pas ameliore

	/* INITIALISER D_LINKS ET SPLIT_ROOMS */
	// - verifier que tous les poids dans split_rooms sont à 0
	// - verifier qu'on a bien le meme principe d'une matrice de taille (nb_rooms * 2 - 2) ** 2
	// - verifier qu'on a bien considere les links orientes dans le meme sens

	/* TANT QUE CELA AMELIORE LE NOMBRE D'INSTRUCTIONS, TROUVER DE NOUVEAUX CHEMINS AVEC UN BFS */
	while (!stop)
	{
		bfs(lem, tmp_flow); // Ajouter un nouveau chemin le plus court
		paths_len = get_path_len_list(lem, tmp_flow); // FONCTION MANQUANTE : Faire la liste des indices des premieres rooms des chemins, trie par longueur
		current_nb_instr = number_of_instr(lem, paths_len); // Calculer le nouveau nombre d'instructions necessaires
		free(paths_len);
		if (current_nb_instr <= prev_nb_instr) // Si le nouveau nombre d'instruction et plus petit, on update la matrice et on recommence
		{
			delete_matrix(lem, &(lem->d_links));
			lem->d_links = copy_matrix(lem, tmp_flow);
			prev_nb_instr = current_nb_instr;
		}
		else // Sinon on arrete le processus
		{
			delete_matrix(lem, &tmp_flow);
			stop = 1;
		}
	}
}
