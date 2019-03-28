/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:04:24 by anleclab          #+#    #+#             */
/*   Updated: 2019/03/28 15:42:16 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void add_option(int *options, char c)
{
    if (c < 'a' || c > 'z')
        return ;
    *options += (*options & (1 << (c - 'a'))) ? 0 : 1 << (c - 'a');
}

int         get_options(int *ac, char ***av)
{
    int     options;

    options = 0;
    (*ac)--;
    (*av)++;
    while (*ac)
    {
        if (!ft_strnequ(**av, "--", 2))
            return (-1);
        else
        {
            (**av) += 2;
            if (ft_strequ(**av, "silent"))
                add_option(&options, 's');
            else if (ft_strequ(**av, "show-paths"))
                add_option(&options, 'p');
            else if (ft_strequ(**av, "line-count"))
                add_option(&options, 'l');
            else if (ft_strequ(**av, "ant-number"))
                add_option(&options, 'a');
            else if (ft_strequ(**av, "ants-per-room"))
                add_option(&options, 'r');
            else if (ft_strequ(**av, "full-info"))
            {
                add_option(&options, 'p');
                add_option(&options, 'l');
                add_option(&options, 'a');
                add_option(&options, 'r');
            }
            else
                return (-1);
        }
        (*ac)--;
        (*av)++;
    }
    return (options);
}

void    print_line_count(t_lem lem)
{
    int     i;
    int     count;

    count = 0;
    i = -1;
    while (lem.instr[++i])
        if (lem.instr[i] == '\n')
            count++;
    ft_putstr("line count: ");
    ft_putnbr(count);
    ft_putchar('\n');
}

void    print_paths(t_lem lem)
{
    int     i;

    ft_putstr("paths:");
    i = -1;
    while (++i < lem.nb_rooms)
        if (lem.links[START][i] && lem.split_rooms[2 * i + 1])
        {
            ft_putchar(' ');
            ft_putstr(lem.rooms[i].id);
            ft_putstr(" (");
            ft_putnbr(lem.split_rooms[2 * i + 1] / 2 + 1);
            ft_putstr(")");
        }
    ft_putchar('\n');
}

void    print_ant_nb(t_lem lem)
{
    ft_putstr("ant number: ");
    ft_putnbr(lem.nb_ants);
    ft_putchar('\n');
}

void    print_ants_per_room(t_lem lem)
{
    int     i;

    i = -1;
    ft_putstr("ants per room:");
    while (lem.paths[++i].index_first != -1)
    {
        ft_putchar(' ');
        ft_putnbr(lem.paths[i].nb_ants);
    }
    ft_putchar('\n');
}