/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_realloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:22:18 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/03/07 17:17:47 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_char_realloc(char *ptr, size_t size)
{
	char	*p;
	int		i;

	i = -1;
	if (ptr && !size)
	{
		if (!(p = malloc(1)))
			return (NULL);
		ft_strdel(ptr);
		return (p);
	}
	p = ft_strnew(size);
	if (ptr && p)
	{
		p = ft_strcpy(p, ptr);
		ft_strdel(&ptr);
	}
	return (p);
}
