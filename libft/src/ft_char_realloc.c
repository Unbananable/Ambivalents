/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_realloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:22:18 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/03/08 12:03:18 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_char_realloc(char *ptr, size_t size)
{
	char	*p;
	int		i;

	if (!ptr)
		return (NULL);
	i = -1;
	if (ptr && size == 0)
	{
		if (!(p = (char *)malloc(sizeof(char))))
			return (NULL);
		ft_strdel(&ptr);
		return (p);
	}
	if (!(p = ft_strnew(size)))
		return (NULL);
	p = ft_strncpy(p, ptr, size);
	ft_strdel(&ptr);
	return (p);
}
