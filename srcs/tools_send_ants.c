/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_send_ants.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:23:23 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/18 16:50:59 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_nbr_str(t_lem *lem, int nb, unsigned long *start)
{
	int		pow;

	pow = 1;
	while (nb / pow >= 10)
		pow *= 10;
	while (pow)
	{
		lem->instr[++(*start)] = nb / pow + '0';
		nb %= pow;
		pow /= 10;
	}
}
