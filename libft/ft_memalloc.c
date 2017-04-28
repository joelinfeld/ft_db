/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 19:19:20 by biremong          #+#    #+#             */
/*   Updated: 2016/12/03 12:25:54 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*fresh;
	size_t	i;

	if (!size)
		return (NULL);
	fresh = malloc(size);
	if (!fresh)
		return (NULL);
	i = 0;
	while (i < size)
	{
		((unsigned char*)fresh)[i] = 0;
		i++;
	}
	return (fresh);
}
