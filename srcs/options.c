/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:04:24 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/28 15:01:39 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	add_option(int *options, char c)
{
	if (c < 'a' || c > 'z')
		return ;
	*options += (*options & (1 << (c - 'a'))) ? 0 : 1 << (c - 'a');
}

static int	apply_option(char ****av, int *options)
{
	(***av) += 2;
	if (ft_strequ(***av, "silent"))
		add_option(options, 's');
	else if (ft_strequ(***av, "show-paths"))
		add_option(options, 'p');
	else if (ft_strequ(***av, "line-count"))
		add_option(options, 'l');
	else if (ft_strequ(***av, "ant-number"))
		add_option(options, 'a');
	else if (ft_strequ(***av, "full-info"))
	{
		add_option(options, 'p');
		add_option(options, 'l');
		add_option(options, 'a');
	}
	else
		return (-1);
	return (0);
}

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
			if (apply_option(&av, &options))
				return (-1);
		}
		(*ac)--;
		(*av)++;
	}
	return (options);
}
