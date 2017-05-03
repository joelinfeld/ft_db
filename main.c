#include "ft_db.h"


int		ft_handle_command(char *buffer)
{
	if (ft_check_str_begin(buffer, "CREATE TABLE "))
		ft_create_table(buffer + ft_strlen("CREATE TABLE "));
	else if (ft_check_str_begin(buffer, "INSERT ROWS "))
		ft_insert_rows(buffer + ft_strlen("INSERT ROWS "));
	else if (ft_check_str_begin(buffer, "INSERT COLUMNS "))
		ft_insert_column(buffer + ft_strlen("INSERT COLUMNS "));
	else if (ft_check_str_begin(buffer, "SELECT "))
		ft_select(buffer + ft_strlen("SELECT "));
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
