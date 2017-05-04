#include "ft_db.h"
//fix memory leaks handle errors add dbls sort format display matchnmatch

int		ft_handle_command(char *buffer)
{
	if (ft_check_str_begin(buffer, "CREATE TABLE "))
		ft_create_table(buffer + ft_strlen("CREATE TABLE "));
	else if (ft_check_str_begin(buffer, "INSERT ROWS "))
		ft_insert_rows(buffer + ft_strlen("INSERT ROWS "));
//	else if (ft_check_str_begin(buffer, "INSERT COLUMNS "))
//		ft_insert_column(buffer + ft_strlen("INSERT COLUMNS "));
	else if (ft_check_str_begin(buffer, "SELECT "))
		ft_select(buffer + ft_strlen("SELECT "));
//	else if (ft_check_str_begin(buffer, "UPDATE "))
//		ft_update(buffer + ft_strlen("UPDATE "));
	else if (ft_check_str_begin(buffer, "SORT "))
		ft_sort(buffer + ft_strlen("SORT "));
	else
		ft_printf("Invalid Command\n");
	return (0);
}


int main(void)
{
	char *buffer;

	while (1)
	{
		ft_printf(">> ");
		ft_gnl(0, &buffer);
		ft_handle_command(buffer);
		free(buffer);
	}
	return (0);
}
