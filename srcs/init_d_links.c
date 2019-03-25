#include "lem_in.h"

/* Premiere conditions dans les if: le cas in>>out */

void	make_d_links(t_lem *lem)
{
	int		i;
	int		j;

	i = 1;
	while (++i < lem->nb_rooms)
	{
		j = i - 1;
/* ****************** */
/* FOR DEBUG USE ONLY */
/* ****************** */
		lem->d_links[(i - 2) * 2][(j - 1) * 2] = -2;
		lem->d_links[(i - 2) * 2][(j - 1) * 2 + 1] = -2;
		lem->d_links[(i - 2) * 2 + 1][(j - 1) * 2] = -2;
		lem->d_links[(i - 2) * 2 + 1][(j - 1) * 2 + 1] = -2;
/* ****************** */
/* ****************** */
		lem->d_links[(i - 2) * 2][(j - 1) * 2] = 0; // X_in >> X_in
		lem->d_links[(i - 2) * 2 + 1][(j - 1) * 2 + 1] = 0; // X_out >> X_out
		while (++j < lem->nb_rooms)
		{
			lem->d_links[(i - 2) * 2][(j - 2) * 2 + 1] = 1; // X_in >> X_out
			lem->d_links[(i - 2) * 2 + 1][(j - 2) * 2] = 0; // X_out >> X_in
			if (links[i][j] == 1 && lem->rooms[i].w < lem->rooms[j].w)
			{
				lem->d_links[(j - 2) * 2 + 1][(i - 2) * 2] = 1; // j_out >> i_in
				lem->d_links[(i - 2) * 2 + 1][(j - 2) * 2] = 0; // i_out >> j_in
			}
			else if (links[i][j] == 1 && lem->rooms[i].w < lem->rooms[j])
			{
				lem->d_links[(i - 2) * 2 + 1][(j - 2) * 2] = 1; // i_out >> j_in
				lem->d_links[(j - 2) * 2 + 1][(i - 2) * 2] = 0; // j_out >> i_in
			}
			else if (links[i][j] == 0)
			{
				lem->d_links[(i - 2) * 2 + 1][(j - 2) * 2] = 0; // i_out >> j_in
				lem->d_links[(j - 2) * 2 + 1][(i - 2) * 2] = 0; // j_out >> i_in
			}
		}
	}
}
