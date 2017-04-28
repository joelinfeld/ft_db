/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:14:39 by biremong          #+#    #+#             */
/*   Updated: 2016/12/03 12:56:53 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t i;

	if (n == 0)
		return (0);
	i = 0;
	while (((unsigned char*)s1)[i] == ((unsigned char*)s2)[i] && i < (n - 1))
		i++;
	return (((unsigned char*)s1)[i] - ((unsigned char*)s2)[i]);
}
