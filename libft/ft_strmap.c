/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 19:41:45 by biremong          #+#    #+#             */
/*   Updated: 2016/12/02 11:59:02 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	unsigned int	len;
	unsigned int	i;
	char			*fresh;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	fresh = (char*)malloc(sizeof(char) * (len + 1));
	if (!fresh)
		return (NULL);
	i = 0;
	while (i < len)
	{
		fresh[i] = f(s[i]);
		i++;
	}
	fresh[i] = '\0';
	return (fresh);
}
