/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 16:10:12 by jinfeld           #+#    #+#             */
/*   Updated: 2017/05/04 17:44:29 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_db_error(int code, char *str)
{
	ft_printf("Error: ");
	if (code == 1)
		ft_printf("Table \"%s\" Already Exists\n", str);
	else if (code == 2)
		ft_printf("Format\n");
	else if (code == 3)
		ft_printf("Unsupported Type: %s\n", str);
	else if (code == 4)
		ft_printf("Primary Column \"%s\" Can't Be Deleted\n", str);
	else if (code == 5)
		ft_printf("Field \"%s\" Does Not Exist", str);
	else if (code = 6)
		ft_printf("Incorrect amount of values\n");
	return (code);
}
