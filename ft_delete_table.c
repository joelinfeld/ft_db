/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 21:19:03 by jinfeld           #+#    #+#             */
/*   Updated: 2017/05/05 16:09:35 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		ft_delete_table(char *buffer)
{
	char	*file_name;

	file_name = ft_get_outer_str(buffer);
	if (!file_name)
		return (ft_db_error(2, ""));
	if(access(file_name, F_OK) == -1)
		return(ft_db_error(7, file_name));
	else
		remove(file_name);
	free(file_name);
	return (0);
}
