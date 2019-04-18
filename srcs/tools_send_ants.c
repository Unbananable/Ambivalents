/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_send_ants.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:23:23 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/18 14:26:44 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	write_number_str(t_lem *lem, int nb, int *start)
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
