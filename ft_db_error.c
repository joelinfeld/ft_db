/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 16:10:12 by jinfeld           #+#    #+#             */
/*   Updated: 2017/05/05 17:52:11 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		ft_db_error(int code, char *str)
{
	ft_printf("\x1b[38;2;255;64;64mError: ");
	if (code == 1)
		ft_printf("Table \"%s\" Already Exists\n", str);
	else if (code == 2)
		ft_printf("Invalid Format\n");
	else if (code == 3)
		ft_printf("Unsupported Type: %s\n", str);
	else if (code == 4)
		ft_printf("Primary Column \"%s\" Can't Be Deleted\n", str);
	else if (code == 5)
		ft_printf("Field \"%s\" Does Not Exist\n", str);
	else if (code == 6)
		ft_printf("Incorrect Amount of Values\n");
	else if (code == 7)
		ft_printf("Table \"%s\" Does Not Exist\n", str);
	else if (code == 8)
		ft_printf("Invalid Command\n", str);
	else if (code == 9)
		ft_printf("Duplicate Field \"%s\"\n", str);
	ft_printf("\x1b[0m");
	return (code);
}
