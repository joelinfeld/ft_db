/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 14:36:14 by biremong          #+#    #+#             */
/*   Updated: 2016/12/03 12:07:08 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*current_link;
	t_list	*temp;

	if (!alst || !del)
		return ;
	current_link = *alst;
	while (current_link)
	{
		del(current_link->content, current_link->content_size);
		temp = current_link->next;
		free(current_link);
		current_link = temp;
	}
	*alst = NULL;
}
