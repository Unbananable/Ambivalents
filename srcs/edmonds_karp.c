/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 10:53:45 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/02 15:26:11 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	nb_links_from(t_lem *lem, int index)
{
	int		res;
	int		i;

	res = 0;
	i = -1;
	while (++i < lem->nb_rooms * 2)
		res += lem->d_links[index][i];
	return (res);
}

static int	bfs_recursive(t_lem *lem, int *current_w_list, int current_w)
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
		nb_links += nb_links_from(lem, current_w_list[i]);
//printf("\t\t\t2/9\n");
//printf("\t\t\t x nb_links = %d\n", nb_links);
	next_w_list = NULL;
	if (nb_links != 0) // Si il y a encore des rooms disponibles
	{
//printf("\t\t\t3/9\n");
		if (!(next_w_list = (int *)malloc(sizeof(int) * (nb_links + 1))))
		{
			free(current_w_list);
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
				if (lem->d_links[current_w_list[i]][j] == 1)
				{
					/* Condition d'arret : la room est liee a START : on reset le poids des rooms que l'on a assigne durant cette occurence, on free e tableau, et on retourne l'index de la room dans current_w_list qui est en lien avec le plus petit chemin */
					if (j == 2 * START)
					{
						lem->d_links[current_w_list[i]][2 * START] = 0;
						lem->d_links[2 * START][current_w_list[i]] = 1;
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
		j = bfs_recursive(lem, next_w_list, current_w + 1);
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
			if (lem->d_links[current_w_list[i]][j])
			{
				lem->d_links[current_w_list[i]][j] = 0;
				lem->d_links[j][current_w_list[i]] = 1;
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

static int	bfs(t_lem *lem)
{
	int		*start_list;
	int 	count;
	int		i;
	int		path_index;

//static int iter;
//iter++;
//printf("\t\t/// IN BFS %d ///\n", iter);
//printf("\t\t1/6\n");
//int nb_links = nb_links_from(lem, lem->d_links, 2 * END + 1);
//printf("\t\t x nb_links = %d\n", nb_links);
	/* On fait la premiere iteration pour set les poids des rooms liees a START a 1 et faire une liste de leurs indices */
	// - il est probablement possible de le faire en une seule fonction recursive avec une condition si la liste est NULL pour le debut
	if (!(start_list = (int *)malloc(sizeof(int) * (nb_links_from(lem, 2 * END + 1) + 1))))
		error(lem);
//printf("\t\t2/6\n");
	count = -1;
	i = 1;
	while (++i < lem->nb_rooms * 2)
	{
		if (lem->d_links[2 * END + 1][i] == 1)
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
	/* bfs_recursive retourne l'index dans la liste du chemin choisi */
	path_index = bfs_recursive(lem, start_list, 2);
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
//a=-1;
//while(++a < path_index)
//printf("lem->d_links[3][a]: %d\n", lem->d_links[2 * END + 1][a]);
	if (path_index != -1)
	{
		lem->d_links[2 * END + 1][path_index] = 0;
		lem->d_links[path_index][2 * END + 1] = 1;
	}
//printf("\t\t5/6\n");
	free(start_list);
//printf("\t\t6/6\n");
	return (path_index);
//iter++;
}

static int		get_weight(t_lem *lem, int current_index)
{
	int		next_index;

	if (current_index == END)
		return (0);
	next_index = -1;
	while (++next_index < lem->nb_rooms)
		if (lem->d_links[2 * current_index][2 * next_index + 1])
			return (1 + get_weight(lem, next_index));
	return (-1);
}

static t_path	*set_path_len_list(t_lem *lem)
{
	int		nb_paths;
	int		i;
	int		j;
	t_path	*paths;
	t_path	tmp;

//printf("\t\t/// IN GET_PATH_LEN_LIST ///\n");
//printf("\t\t1/6\n");
	nb_paths = 0;
	i = 1;
	while (++i < lem->nb_rooms)
		if (lem->d_links[2 * START][2 * i + 1])
			nb_paths++;
//printf("\t\t x nb_paths = %d\n", nb_paths);
//printf("\t\t2/6\n");
	if (!(paths = (t_path *)malloc(sizeof(t_path) * (nb_paths + 1))))
		return (NULL);
	j = -1;
	i = 1;
//printf("\t\t3/6\n");
	while (++i < lem->nb_rooms)
		if (lem->d_links[2 * START][2 * i + 1])
		{
//printf("\t\t => setting path starting at %s: index %d, w = %d\n", lem->rooms[i].id, i, lem->split_rooms[2 * i + 1]/ 2);
			paths[++j].id_first = lem->rooms[i].id;
			paths[j].index_first = i;
			paths[j].w = get_weight(lem, i);
		}
//printf("\t\t4/6\n");
	paths[nb_paths].id_first = NULL;
	paths[nb_paths].index_first = -1;
	paths[nb_paths].w = 0;
//printf("\t\t5/6\n");
//int a = -1;
//printf("\t\tx res (pre sort) = [");
//while (res[++a])
//printf(" %d", res[a]);
//printf(" ]\n");
	i = -1;
	while (++i < nb_paths)
	{
		j = -1;
		while (paths[++j + 1].index_first != -1)
			if (paths[j].w > paths[j + 1].w)
			{
				tmp = paths[j + 1];
				paths[j + 1] = paths[j];
				paths[j] = tmp;
			}
	}
//a = -1;
//printf("\t\tx res (post sort) = [");
//while (res[++a])
//printf(" %d", res[a]);
//printf(" ]\n");
//printf("\t\t6/6\n");
	return (paths);
}

void    edmonds_karp(t_lem *lem)
{
	int		stop;
	t_path	*current_paths;

//printf("\t/// IN EDMONDS_KARP ///\n");
	current_paths = NULL;
	stop = 0;
//printf("\t1/4\n");

	/* INITIALISER D_LINKS ET SPLIT_ROOMS */
	make_d_links(lem);
//printf("\t2/4\n");
//printf("\t3/4\n");

	/* TANT QUE CELA AMELIORE LE NOMBRE D'INSTRUCTIONS, TROUVER DE NOUVEAUX CHEMINS AVEC UN BFS */
//display_d_weights(*lem);
//display_d_links(*lem, lem->d_links);
	while (!stop)
	{
//printf("\tLOOP1\n");
//printf("\t L1: 1/5\n");
		if (bfs(lem) == -1) // Ajouter un nouveau chemin le plus court
			stop = 1;
		else
		{
//printf("\t L1: 2/5\n");
//display_d_links(*lem, lem->d_links);
//display_d_weights(*lem);
			if (!(current_paths = set_path_len_list(lem)))
				error(lem); // Faire la liste des indices des premieres rooms des chemins, trie par longueur
//printf("\t L1: 3/5\n");
			set_ants_per_room(lem, current_paths); // Calculer le nouveau nombre d'instructions necessaires
//printf("\t L1: 4/5\n");
//display_paths(current_paths);
			if (!lem->paths || current_paths[0].nb_ants + current_paths[0].w < lem->paths[0].nb_ants + lem->paths[0].w) // Si le nouveau nombre d'instruction et plus petit, on update la matrice et on recommence
			{
//printf("\t  => updating lem->d_links\n");
				free(lem->paths);
				lem->paths = current_paths;
				current_paths = NULL;
			}
			else // Sinon on arrete le processus
//{
//printf("\t  =>stop\n");
				stop = 1;
//}
		}
//printf("\t L1: 5/5\n");
//printf("\t/LOOP1\n");
	}
//printf("\t4/4\n");
}