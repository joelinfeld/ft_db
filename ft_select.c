#include "ft_db.h"







void	ft_select(void)
{
	t_table tab;
	char *buffer;
	int	selected_count;
	int *cols;
	char **selected_fields;

	ft_printf("FROM: ");
	ft_gnl(0, &buffer);
	if (access(buffer, F_OK) != -1)
	{

		tab = ft_deserialize_table(buffer);
		free(buffer);

		ft_printf("FIELDS: ");
		ft_gnl(0, &buffer);
		selected_fields = ft_strsplit(buffer, ',');
		selected_count = ft_arrlen2(selected_fields);
	//	cols = ft_get_field_indices(selected_fields, selected_count, tab);
		if (!cols)
			return ;
		free(buffer);
		ft_arrdel2(selected_fields);

		int i;
		int j;
		t_cell *row;

		i = 0;

		while (i < tab.row_count)
		{


			row = tab.rows[i];
			j = 0;
			while (j < selected_count)
			{
				if (*row[cols[j]].type == 'i')
					ft_printf("%d ", row[cols[j]].value->i);
				else if (*row[cols[j]].type == 's')
					ft_printf("%s ", row[cols[j]].value->str);
				j++;
			}
			ft_printf("\n");
			i++;
		}
		free(cols);
	}
	else
		ft_printf("Table Does Not Exist\n");
}


