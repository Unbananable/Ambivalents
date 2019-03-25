#include "lem_in.h"

int		number_of_instr(t_lem *lem, int	*plen_list)
{
	int			i;
	int			ants_left;
	int			res;

	ants_left = lem->nb_ants;
	while (ants_left)
	{
		i = -1;
		while (ants_left && plen_list[++i] && (i == 0
			|| ants_left >= plen_list[i] - plen_list[0] + i))
			ants_left--;
		res++;
	}
	res += plen_list[0];
	return (res);
}
