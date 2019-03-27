/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 10:53:45 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/27 18:47:04 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	nb_links_from(t_lem *lem, int **matrix, int index)
{
	int		res;
	int		i;

	res = 0;
	i = -1;
	while (++i < lem->nb_rooms * 2)
		if (!lem->split_rooms[i])
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

//static int c;
//int c2;
//c++;
//c2 = c;
//printf("\t\t\t/// IN BFS_RECURSIVE (%dth recursive)\n", c);
//printf("\t\t\t1/9\n");
//int a = -1;
//printf("\t\t\t x current_w_list(id) = [");
//while (current_w_list[++a] != -1)
//printf(" %d(%.1s)", current_w_list[a], lem->rooms[current_w_list[a] / 2].id);
//printf(" ]\n");
	/* On initialise la nouvelle liste de rooms auquelles on met un poids */
	i = -1;
	nb_links = 0;
	while (current_w_list[++i] != -1)
		nb_links += nb_links_from(lem, matrix, current_w_list[i]);
//printf("\t\t\t2/9\n");
//printf("\t\t\t x nb_links = %d\n", nb_links);
	next_w_list = NULL;
	if (nb_links != 0) // Si il y a encore des rooms disponibles
	{
//printf("\t\t\t3/9\n");
		if (!(next_w_list = (int *)malloc(sizeof(int) * (nb_links + 1))))
		{
			free(current_w_list);
			delete_matrix(lem, &matrix);
			error(lem);
		}
//printf("\t\t\t4/9\n");
		count = -1;
		i = -1;
		while (current_w_list[++i] != -1)
		{
//printf("\t\t\tLOOP1\n");
			j = -1;
			while (++j < lem->nb_rooms * 2)
//{printf("\t\t\t L1: LOOP2\n");
				if (matrix[current_w_list[i]][j] == 1 && !lem->split_rooms[j])
				{
					/* Condition d'arret : la room est liee a START : on reset le poids des rooms que l'on a assigne durant cette occurence, on free e tableau, et on retourne l'index de la room dans current_w_list qui est en lien avec le plus petit chemin */
					if (j == 2 * START)
					{
						matrix[current_w_list[i]][2 * START] = 0;
						matrix[2 * START][current_w_list[i]] = 1;
//printf("\t\t\t      L2: x next_w_list(w) = [");
						while (count >= 0)
//{printf(" %d(%d->0)", next_w_list[count], lem->split_rooms[next_w_list[count]]);
							lem->split_rooms[next_w_list[count--]] = 0;
//}printf(" ]\n");
						count = -1;
//printf("\t\t\t      L2: x current_w_list(w) = [");
						while (current_w_list[++count] != -1)
//{printf(" %d(%d", current_w_list[count], lem->split_rooms[current_w_list[count]]);
							if (count != i)
//{printf("->0");
								lem->split_rooms[current_w_list[count]] = 0;
//}printf(")");
//}printf(" ]\n");
						free(next_w_list);
//printf("\t\t\t/// HARD END %dth RECURSIVE ///\n", c2);
						return (current_w_list[i]);
					}
					/* Sinon on set le poids et on rajoute la room a la liste */
					lem->split_rooms[j] = current_w;
					next_w_list[++count] = j;
				}
//printf("\t\t\t L1: /LOOP2\n");}
//printf("\t\t\t/LOOP1\n");
		}
//printf("\t\t\t5/9\n");
		next_w_list[++count] = -1;
		j = bfs_recursive(lem, matrix, next_w_list, current_w + 1);
//printf("\t\t\t6/9\n");
	}
	else // Si il n'y a plus de rooms dispo : il n'y a pas de chemin supplementaire entre start et end
		j = -1;
//printf("\t\t\t7/9\n");
//printf("\t\t\t x j = %d\n", j);
	if (j != -1)
	{
		i = -1;
		while (++i != -1 && current_w_list[i] != -1)
			if (matrix[current_w_list[i]][j])
			{
				matrix[current_w_list[i]][j] = 0;
				matrix[j][current_w_list[i]] = 1;
				j = current_w_list[i];
				i = -1;
			}
	}
//printf("\t\t\t x new j = %d\n", j);
//printf("\t\t\t x current_w_list(w) = [");
	i = -1;
	while (current_w_list[++i] != -1)
//{printf(" %d(%d", current_w_list[i], lem->split_rooms[current_w_list[i]]);
		if (current_w_list[i] != j)
//{printf("->0");
			lem->split_rooms[current_w_list[i]] = 0;
//}
//printf(")");
//}
//printf(" ]\n");
//printf("\t\t\t8/9\n");
	free(next_w_list);
//printf("\t\t\t9/9\n");
//printf("\t\t\t/// SOFT END %dth RECURSIVE ///\n", c2);
	return (j);
}

static void	bfs(t_lem *lem, int **tmp_flow)
{
	int		*start_list;
	int 	count;
	int		i;
	int		path_index;

//printf("\t\t/// IN BFS ///\n");
//printf("\t\t1/6\n");
//int nb_links = nb_links_from(lem, tmp_flow, 2 * END + 1);
//printf("\t\t x nb_links = %d\n", nb_links);
	/* On fait la premiere iteration pour set les poids des rooms liees a START a 1 et faire une liste de leurs indices */
	// - il est probablement possible de le faire en une seule fonction recursive avec une condition si la liste est NULL pour le debut
	if (!(start_list = (int *)malloc(sizeof(int) * (nb_links_from(lem, tmp_flow, 2 * END + 1) + 1))))
	{
		delete_matrix(lem, &tmp_flow);
		error(lem);
	}
//printf("\t\t2/6\n");
	count = -1;
	i = 1;
	while (++i < lem->nb_rooms * 2)
	{
		if (tmp_flow[2 * END + 1][i] == 1)
		{
			start_list[++count] = i;
			lem->split_rooms[i] = 1;
		}
	}
	start_list[++count] = -1;
//printf("\t\t x start_list(id) = [");
//int a = -1;
//while (start_list[++a] != -1)
//printf(" %d(%.1s)", start_list[a], lem->rooms[start_list[a] / 2].id);
//printf(" ]\n");
//printf("\t\t3/6\n");
	/* bfs_recursive retourne l'index dans la liste du chemin choisi : NOT WORKING : on lui laisse son poids et on reset les autres a 0 + NOT DONE : on inverse le sens des liens */
	path_index = bfs_recursive(lem, tmp_flow, start_list, 2);
//printf("\t\t x path_index = %d\n", path_index);
//printf("\t\t4/6\n");
	i = -1;
//printf("\t\t x start_list(w) = [");
	while (start_list[++i] != -1)
//{printf(" %d(%d", start_list[i], lem->split_rooms[start_list[i]]);
		if (start_list[i] != path_index)
//{printf("->0");
			lem->split_rooms[start_list[i]] = 0;
//}
//printf(")");
//}
//printf(" ]\n");
//printf("path_index: %d\n", path_index);
//int a=-1;
//while(++a < path_index)
//	printf("tmp_flow[3][a]: %d\n", tmp_flow[2 * END + 1][a]);
	if (path_index != -1)
	{
		tmp_flow[2 * END + 1][path_index] = 0;
		tmp_flow[path_index][2 * END + 1] = 1;
	}
//printf("\t\t5/6\n");
	free(start_list);
//printf("\t\t6/6\n");
}

static int	*get_path_len_list(t_lem *lem, int **matrix)
{
	int		*res;
	int		nb_paths;
	int		i;
	int		j;
	int		tmp;

//printf("\t\t/// IN GET_PATH_LEN_LIST ///\n");
//printf("\t\t1/6\n");
	nb_paths = 0;
	i = 1;
	while (++i < lem->nb_rooms)
		if (lem->links[i][START] && lem->split_rooms[2 * i + 1])
			nb_paths++;
//printf("\t\t x nb_paths = %d\n", nb_paths);
//printf("\t\t2/6\n");
	if (!(res = (int *)malloc(sizeof(int) * (nb_paths + 1))))
	{
		delete_matrix(lem, &matrix);
		error(lem);		
	}
	j = -1;
	i = 2;
//printf("\t\t3/6\n");
	while (++i < lem->nb_rooms)
		if (lem->links[i][START] && lem->split_rooms[2 * i + 1])
			res[++j] = lem->split_rooms[2 * i + 1] / 2;
//printf("\t\t4/6\n");
	res[nb_paths] = 0;
//printf("\t\t5/6\n");
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
//printf("\t\t6/6\n");
	return (res);
}

void    edmonds_karp(t_lem *lem)
{
    int     prev_nb_instr;
	int		current_nb_instr;
	int		stop;
	int		*paths_len;
	int		**tmp_flow;

//printf("\t/// IN EDMONDS_KARP ///\n");
	prev_nb_instr = 2147483647;
	stop = 0;
//printf("\t1/4\n");

	/* INITIALISER D_LINKS ET SPLIT_ROOMS */
	// - verifier qu'on a bien considere les links orientes dans le meme sens
	make_d_links(lem);
//printf("\t2/4\n");
	tmp_flow = copy_matrix(lem, lem->d_links); // On opere sur une copie de la matrice pour pouvoir revenir en arriere si le nombre d'instructions n'est pas ameliore
//printf("\t3/4\n");

	/* TANT QUE CELA AMELIORE LE NOMBRE D'INSTRUCTIONS, TROUVER DE NOUVEAUX CHEMINS AVEC UN BFS */
//display_d_links(*lem, tmp_flow);
//display_d_weights(*lem);
	while (stop >= 0)
	{
//printf("\tLOOP1\n");
//printf("\t L1: 1/5\n");
		bfs(lem, tmp_flow); // Ajouter un nouveau chemin le plus court
//printf("\t L1: 2/5\n");
//display_d_links(*lem, tmp_flow);
//display_d_weights(*lem);
		paths_len = get_path_len_list(lem, tmp_flow); // Faire la liste des indices des premieres rooms des chemins, trie par longueur
//printf("\t L1: 3/5\n");
//printf("\t  x paths_len = [");
//int a = -1;
//while (paths_len[++a])
//printf(" %d", paths_len[a]);
//printf(" ]\n");
		current_nb_instr = number_of_instr(lem, paths_len); // Calculer le nouveau nombre d'instructions necessaires
		free(paths_len);
//printf("\t L1: 4/5\n");
		if (stop < 6 && current_nb_instr <= prev_nb_instr) // Si le nouveau nombre d'instruction et plus petit, on update la matrice et on recommence
		{
			delete_matrix(lem, &(lem->d_links));
			lem->d_links = copy_matrix(lem, tmp_flow);
			prev_nb_instr = current_nb_instr;
			stop++;
		}
		else // Sinon on arrete le processus
		{
			delete_matrix(lem, &tmp_flow);
			stop = -1;
		}
//printf("\t L1: 5/5\n");
//printf("\t/LOOP1\n");
	}
//printf("\t4/4\n");
}
