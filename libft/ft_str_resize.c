/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 14:23:07 by biremong          #+#    #+#             */
/*   Updated: 2017/01/16 19:25:38 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_resize(char *str, size_t len)
{
	char *sofresh;

	if (!(sofresh = (char*)malloc(len + 1)))
		return (NULL);
	ft_strncpy(sofresh, str, len);
	sofresh[len] = '\0';
	free(str);
	str = NULL;
	return (sofresh);
}
