/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 09:48:05 by biremong          #+#    #+#             */
/*   Updated: 2016/12/02 14:57:11 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (i < len)
	{
		dst[i] = src[j];
		if (src[j])
			j++;
		i++;
	}
	return (dst);
}
