/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 14:01:19 by biremong          #+#    #+#             */
/*   Updated: 2016/12/03 12:23:58 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *new_link;

	if (!(new_link = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		new_link->content = NULL;
		new_link->content_size = 0;
	}
	else
	{
		if (!(new_link->content = (void*)malloc(content_size)))
			return (NULL);
		ft_memcpy(new_link->content, content, content_size);
		new_link->content_size = content_size;
	}
	new_link->next = NULL;
	return (new_link);
}
