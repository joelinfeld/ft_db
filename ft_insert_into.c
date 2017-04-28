#include "ft_db.h"

void	ft_insert_into(void)
{
	char *buffer;
	t_table tab;
	t_field *fields;
	int j;

	ft_printf("TABLE: ");
	ft_gnl(0, &buffer);
	if (access(buffer, F_OK) != -1)
	{
		tab = ft_deserialize_table(buffer);
		fields = tab.fields;
		tab.row_count++;
		tab.rows = (t_cell**)realloc(tab.rows, sizeof(t_cell*) * (tab.row_count));
		tab.rows[tab.row_count - 1] = (t_cell*)ft_malloc(sizeof(t_cell) * tab.col_count);
		j = 0;
		while (j < tab.col_count)
		{

			ft_printf("%s: ", fields[j].name);
			ft_gnl(0, &buffer);

			tab.rows[tab.row_count - 1][j].field = ft_strdup(fields[j].name);

			tab.rows[tab.row_count - 1][j].type = ft_strdup(fields[j].type);

			if (*tab.rows[tab.row_count - 1][j].type == 'i')
				tab.rows[tab.row_count - 1][j].value.i = ft_atoi(buffer);
			else if (*tab.rows[tab.row_count - 1][j].type == 's')
				tab.rows[tab.row_count - 1][j].value.str = ft_strdup(buffer);

			free(buffer);
			j++;
		}

		ft_serialize_table(tab);
	}
	else
		ft_printf("Table Does Not Exist\n");
}


