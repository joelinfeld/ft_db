/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 21:19:03 by jinfeld           #+#    #+#             */
/*   Updated: 2017/05/04 21:30:05 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		ft_delete_table(char *buffer)
{
	char	*filename;

	filename = ft_get_outer_str(buffer);
	if(access(filename, F_OK) == -1)
		return(ft_db_error(7, filename));
	else
		remove(filename);
	return (0);
}
