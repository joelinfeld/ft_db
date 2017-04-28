/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 11:38:37 by biremong          #+#    #+#             */
/*   Updated: 2016/11/29 13:44:19 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int len;

	len = ft_strlen(str);
	while (len + 1)
	{
		if (str[len] == (char)c)
			return ((char*)str + len);
		len--;
	}
	return (NULL);
}
