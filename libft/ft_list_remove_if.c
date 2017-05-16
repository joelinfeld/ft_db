/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_foreach.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 20:31:59 by biremong          #+#    #+#             */
/*   Updated: 2016/12/07 18:13:32 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list *list_pointer;
	t_list *post_pointer;
	t_list *pre_pointer;

	list_pointer = *begin_list;
	while (list_pointer && cmp(list_pointer->content, data_ref) == 0)
	{
		post_pointer = list_pointer->next;
		free(list_pointer);
		list_pointer = post_pointer;
	}
	*begin_list = list_pointer;
	pre_pointer = 0;
	while (list_pointer)
	{
		post_pointer = list_pointer->next;
		if (cmp(list_pointer->content, data_ref) == 0)
		{
			free(list_pointer);
			pre_pointer->next = post_pointer;
		}
		else
			pre_pointer = list_pointer;
		list_pointer = post_pointer;
	}
}
