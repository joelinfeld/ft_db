/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 20:58:00 by biremong          #+#    #+#             */
/*   Updated: 2016/12/02 15:15:53 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strtrim(char const *s)
{
	char	*fresh;
	size_t	total;
	size_t	front;
	size_t	back;

	if (!s)
		return (NULL);
	total = ft_strlen(s);
	front = 0;
	while (s[front] == ' ' || s[front] == '\t' || s[front] == '\n')
		front++;
	if (front == total)
		back = 0;
	else
	{
		back = total - 1;
		while (s[back] == ' ' || s[back] == '\t' || s[back] == '\n')
			back--;
		back = total - 1 - back;
	}
	if (!(fresh = (char*)malloc(sizeof(char) * (total - front - back + 1))))
		return (NULL);
	ft_strncpy(fresh, s + front, total - front - back);
	fresh[total - front - back] = '\0';
	return (fresh);
}
