#include "lem_in.h"

static int	count_links(t_lem *lem)
{
	int		i;
	int		j;
	int		res;

	i = -1;
	res = 0;
	while (++i < lem->nb_rooms)
	{
		j = -1;
		while (++j < lem->nb_rooms)
			res += lem->links[i][j];
	}
	return (res);
}

static int	bfs(t_lem *lem, int **current_w_list, int **next_w_list, int weight)
{
	int		i;
	int		j;
	int		k;
	int		*tmp;

	if (!(*current_w_list)[0])
		return (0);
	i = -1;
	k = -1;
	while ((*current_w_list)[++i])
	{
		j = 0;
		while (++j < lem->nb_rooms)
			if (lem->links[(*current_w_list)[i]][j] == 1 && !lem->rooms[j].w)
			{
				lem->rooms[j].w = weight;
				(*next_w_list)[++k] = j;
			}
	}
	(*next_w_list)[++k] = 0;
	tmp = *current_w_list;
	*current_w_list = *next_w_list;
	*next_w_list = tmp;
	return (1);
}

static void set_weights(t_lem *lem)
{
	int		i;
	int		j;
	int		weight;
	int		*current_w_list;
	int		*next_w_list;

	i = count_links(lem);
	if (!(current_w_list = (int *)malloc(sizeof(int) * i)))
		error(lem);
	if (!(next_w_list = (int *)malloc(sizeof(int) * i)))
		error(lem);
	ft_bzero(next_w_list, sizeof(int) * i);
	ft_bzero(current_w_list, sizeof(int) * i);
	i = -1;
	j = -1;
	while (++i < lem->nb_rooms)
		if (lem->links[START][i] == 1 && !lem->rooms[i].w)
		{
			lem->rooms[i].w = 1;
			current_w_list[++j] = i;
		}
	weight = 1;
	while (bfs(lem, &current_w_list, &next_w_list, ++weight))
		;
	free(current_w_list);
	free(next_w_list);
}

void	make_d_links(t_lem *lem)
{
	int		i;
	int		j;

	set_weights(lem);
	i = -1;
	while (++i < lem->nb_rooms)
	{
		j = i - 1;
		lem->d_links[2 * i][2 * i + 1] = 1; // X_in >> X_out

		while (++j < lem->nb_rooms)
		{
			if (lem->links[i][j] == 1 && lem->rooms[i].w > lem->rooms[j].w && j != END)
			{
				lem->d_links[j * 2 + 1][i * 2] = 1; // j_out >> i_in
			}
			else if (lem->links[i][j] == 1 && i != END)
			{
				lem->d_links[i * 2 + 1][j * 2] = 1; // i_out >> j_in
			}
		}
	}
}
