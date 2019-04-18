/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:04:24 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/18 17:09:23 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	add_option(int *options, char c)
{
	if (c < 'a' || c > 'z')
		return ;
	*options += (*options & (1 << (c - 'a'))) ? 0 : 1 << (c - 'a');
}

static int	apply_option(char *av, int *options)
{
	if (ft_strequ(av, "silent"))
		add_option(options, 's');
	else if (ft_strequ(av, "show-paths"))
		add_option(options, 'p');
	else if (ft_strequ(av, "line-count"))
		add_option(options, 'l');
	else if (ft_strequ(av, "ant-number"))
		add_option(options, 'a');
	else if (ft_strequ(av, "ants-per-room"))
		add_option(options, 'r');
	else if (ft_strequ(av, "full-info"))
	{
		add_option(options, 'l');
		add_option(options, 'a');
		add_option(options, 'r');
	}
	else
		return (ERROR);
	return (0);
}

/*
** Checks program parameters againts a number of available commands. The
** different options are stored as an activated bit in an int.
*/

int			get_options(int *ac, char ***av)
{
	int		options;

	options = 0;
	(*ac)--;
	(*av)++;
	while (*ac)
	{
		if (!ft_strnequ(**av, "--", 2))
			return (-1);
		else
		{
			**av += 2;
			if (apply_option(**av, &options))
				return (ERROR);
		}
		(*ac)--;
		(*av)++;
	}
	return (options);
}
