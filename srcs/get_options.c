/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:04:24 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/19 11:07:14 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_help(void)
{
	ft_putstr("usage: ./lem-in [options] [< file]\n");
	ft_putstr("available options:\n");
	ft_putstr("\t--silent: do not print the regular output of the program\n");
	ft_putstr("\t--show-paths: prints the name of the rooms in the paths the ");
	ft_putstr("ants follow\n");
	ft_putstr("\t--line-count: prints the number of lines of instructions ");
	ft_putstr("necessary for all the ants to get to the end room\n");
	ft_putstr("\t--ant-number: prints the number of ants\n");
	ft_putstr("\t--ants-per-room: prints how many ants are sent in each path\n");
	ft_putstr("\t--full-info: activates --line-count --ants-per-room ");
	ft_putstr("--ant-number\n");
	ft_putstr("\t--help: you are here\n");
	exit(0);
}

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
	else if (ft_strequ(av, "help"))
		print_help();
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
