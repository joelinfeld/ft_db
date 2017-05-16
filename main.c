/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 17:11:59 by biremong          #+#    #+#             */
/*   Updated: 2017/05/05 20:32:12 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		ft_handle_command(char *buffer)
{	
	if (ft_strequ(buffer, ""))
		return (0);
	else if (ft_strequ(buffer, "EXIT") || ft_strequ(buffer, "QUIT"))
		exit(0);
	else if (ft_strequ(buffer, "HELP") || ft_strequ(buffer, "USAGE"))
		ft_usage();
	else if (ft_check_str_begin(buffer, "CREATE TABLE "))
		ft_create_table(buffer + ft_strlen("CREATE TABLE "));
	else if (ft_check_str_begin(buffer, "DELETE TABLE "))
		ft_delete_table(buffer + ft_strlen("DELETE TABLE "));
	else if (ft_check_str_begin(buffer, "INSERT ROWS "))
		ft_insert_rows(buffer + ft_strlen("INSERT ROWS "));
	else if (ft_check_str_begin(buffer, "DELETE ROWS "))
		ft_delete_rows(buffer + ft_strlen("DELETE ROWS "));
	else if (ft_check_str_begin(buffer, "INSERT COLS "))
		ft_insert_cols(buffer + ft_strlen("INSERT COLS "));
	else if (ft_check_str_begin(buffer, "DELETE COLS "))
		ft_delete_cols(buffer + ft_strlen("DELETE COLS "));
	else if (ft_check_str_begin(buffer, "SELECT "))
		ft_select(buffer + ft_strlen("SELECT "));
	else if (ft_check_str_begin(buffer, "UPDATE "))
		ft_update(buffer + ft_strlen("UPDATE "));
	else if (ft_check_str_begin(buffer, "SORT "))
		ft_sort(buffer + ft_strlen("SORT "));
	else
		ft_db_error(8, "");
	return (0);
}


int main(void)
{
	char *buffer;

	while (1)
	{
		ft_printf("\x1b[38;2;115;190;255m>> \x1b[0m");
		ft_gnl(0, &buffer);
		ft_handle_command(buffer);
		free(buffer);
	}
	return (0);
}
