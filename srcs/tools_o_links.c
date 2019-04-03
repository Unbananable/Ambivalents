/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_o_links.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:42:54 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/03 10:50:17 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Returns the index of the 'in' subroom of the room with the index in parameter.
*/
int     in(int index)
{
    return (2 * index);
}

/*
** Returns the index of the 'out' subroom of the room with the index in parameter.
*/
int     out(int index)
{
    return (2 * index + 1);
}