/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 12:56:30 by biremong          #+#    #+#             */
/*   Updated: 2016/12/02 15:00:15 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int i;
	int j;

	if (!little[0])
		return ((char*)big);
	i = 0;
	j = 0;
	while (big[i])
	{
		while (big[i + j] && little[j] && little[j] == big[i + j])
			j++;
		if (little[j] == '\0')
			return ((char*)big + i);
		i++;
		j = 0;
	}
	return (NULL);
}
