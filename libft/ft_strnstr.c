/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 13:26:00 by biremong          #+#    #+#             */
/*   Updated: 2016/12/02 15:14:15 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t j;

	if (!little[0])
		return ((char*)big);
	i = 0;
	j = 0;
	while (big[i] && i < len)
	{
		while (big[i + j] && (i + j) < len && little[j] == big[i + j])
			j++;
		if (!little[j])
			return ((char*)big + i);
		i++;
		j = 0;
	}
	return (NULL);
}
