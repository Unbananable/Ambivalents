/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:22:18 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/03/07 15:04:51 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*p;
	int		i;

	i = -1;
	if (ptr && !size)
	{
		if (!(p = malloc(1)))
			return (NULL);
		free(ptr);
		return (p);
	}
	p = malloc(size);
	if (ptr && p)
	{
		while (++i < size)
		{
			if (ptr[i])
				p[i] = ptr[i];
			else
				p[i] = '\0';
		}
		free(ptr);
		ptr = NULL;
	}
	return (p);
}
