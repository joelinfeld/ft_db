#include "ft_db.h"


int		ft_handle_command(char *command)
{
	if (ft_strequ(command, "CREATE TABLE"))
		ft_create_table();
	else if (ft_strequ(command, "INSERT INTO"))
		ft_insert_into();
	else if (ft_strequ(command, "SELECT"))
		ft_select();
	else
		ft_printf("Invalid Command\n");
	return (0);
}


int main(void)
{

	char *command;

	while (1)
	{
		ft_printf("> ");
		ft_gnl(0, &command);
		ft_handle_command(command);
	}
	return (0);
}
