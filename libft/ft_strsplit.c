/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 21:28:48 by biremong          #+#    #+#             */
/*   Updated: 2016/12/02 11:57:08 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_wc(char const *s, char c)
{
	int		searching;
	size_t	count;
	size_t	i;

	searching = 1;
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			searching = 1;
		else if (searching == 1)
		{
			count++;
			searching = 0;
		}
		i++;
	}
	return (count);
}

static size_t	ft_get_next_cc(char const **s, char c)
{
	size_t	cc;

	while (**s == c)
		(*s)++;
	cc = 0;
	while (**s != c && **s != '\0')
	{
		(*s)++;
		cc++;
	}
	return (cc);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**array;
	size_t	wc;
	size_t	cc;
	size_t	i;

	if (!s)
		return (NULL);
	wc = ft_get_wc(s, c);
	array = (char**)malloc(sizeof(char*) * (wc + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (i < wc)
	{
		cc = ft_get_next_cc(&s, c);
		array[i] = (char*)malloc(sizeof(char) * (cc + 1));
		if (!array[i])
			return (NULL);
		ft_strncpy(array[i], s - cc, cc);
		array[i][cc] = '\0';
		i++;
	}
	array[i] = 0;
	return (array);
}
