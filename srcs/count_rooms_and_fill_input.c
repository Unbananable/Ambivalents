/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_rooms_and_fill_input.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:56:17 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/10 19:03:01 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	add_buffer(t_lem *lem, char *buff, int rd_size)
{
	if (!(lem->input = ft_char_realloc(lem->input, sizeof(char)
					* (ft_strlen(lem->input) + rd_size))))
		error(lem);
	lem->input = ft_strncat(lem->input, buff, rd_size);
}

/*
** Checks if the line preceding the '\n' in the input is a room with its
** coordinates by checking each character from the end to the start.
*/

static int	is_room(char *str, int i)
{
	if (str[i] < '0' || str[i] > '9')
		return (0);
	while (i >= 0 && str[i] >= '0' && str[i] <= '9')
		i--;
	if (i >= 0 && str[i] == '-')
		i--;
	if (i < 0 || str[i--] != ' ')
		return (0);
	if (i < 0 || str[i] < '0' || str[i] > '9')
		return (0);
	while (i >= 0 && str[i] >= '0' && str[i] <= '9')
		i--;
	if (i >= 0 && str[i] == '-')
		i--;
	if (i < 0 || str[i--] != ' ')
		return (0);
	if (i < 0)
		return (0);
	return (1);
}

/*
** Stores the input in a string and counts the number of rooms.
*/

int			count_rooms_and_fill_input(t_lem *lem)
{
	int		i;
	int		count;
	int		stop;
	int		rd_size;
	char	buff[BUFF_SIZE + 1];

	rd_size = 0;
	count = 0;
	stop = -1;
	lem->input = NULL;
	while ((rd_size = read(0, buff, BUFF_SIZE)) > 0)
	{
		buff[rd_size] = 0;
		i = ft_strlen(lem->input) - 1;
		add_buffer(lem, buff, rd_size);
		while (stop < 1 && lem->input[++i])
			if (lem->input[i] == '#')
				while (lem->input[i] && lem->input[i] != '\n')
					i++;
			else if (lem->input[i] == '\n')
			{
				if (stop == -1) // Skip the line containing the number of ants
					stop = 0;
				else if (is_room(lem->input, i - 1))
					count++;
				else
					stop = 1;
			}
	}
	if (rd_size < 0)
		return (0);
	return (count);
}
