/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:04:11 by biremong          #+#    #+#             */
/*   Updated: 2016/12/03 13:42:11 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_listcpy(t_list *lst)
{
	t_list	*new_begin;
	t_list	*new_link;
	t_list	*prev_link;
	int		i;

	new_begin = NULL;
	prev_link = NULL;
	i = 1;
	while (lst)
	{
		if (!(new_link = (t_list*)malloc(sizeof(t_list))))
			return (NULL);
		*new_link = *lst;
		new_link->next = NULL;
		if (i)
		{
			new_begin = new_link;
			i = 0;
		}
		if (prev_link)
			prev_link->next = new_link;
		prev_link = new_link;
		lst = lst->next;
	}
	return (new_begin);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_begin;
	t_list	*current_link;
	t_list	*pre_temp;
	t_list	*post_temp;

	if (!f)
		return (NULL);
	pre_temp = NULL;
	new_begin = ft_listcpy(lst);
	current_link = new_begin;
	while (current_link)
	{
		post_temp = current_link->next;
		current_link = f(current_link);
		if (pre_temp)
			pre_temp->next = current_link;
		else
			new_begin = current_link;
		current_link->next = post_temp;
		pre_temp = current_link;
		current_link = current_link->next;
	}
	return (new_begin);
}
