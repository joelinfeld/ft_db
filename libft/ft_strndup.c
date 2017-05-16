/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 12:12:48 by biremong          #+#    #+#             */
/*   Updated: 2016/12/08 12:16:16 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*sofresh;

	if (!(sofresh = (char*)malloc(len + 1)))
		return (NULL);
	i = 0;
	slen = ft_strlen(str);
	while (i < len)
	{
		if (i < slen)
			sofresh[i] = str[i];
		else
			sofresh[i] = '\0';
		i++;
	}
	sofresh[i] = '\0';
	return (sofresh);
}
