#include "ft_db.h"



void	ft_display_rows(int *field_indices, int field_count, int *row_indices, int row_count, t_table tab)
{
	t_data	**row;
	int		i;
	int		j;

	i = -1;
	while (++i < row_count)
	{
		row = tab.rows[row_indices[i]];
		j = -1;
		while (++j < field_count)
		{
			if (!row[field_indices[j]])
				ft_printf("(null) ");
			else if (ft_strequ(tab.fields[field_indices[j]].type, "int"))
				ft_printf("%d ", row[field_indices[j]]->i);
			else if (ft_strequ(tab.fields[field_indices[j]].type, "str"))
				ft_printf("%s ", row[field_indices[j]]->str);
		}
		ft_printf("\n");
	}
}
				




void	ft_select(char *buffer)
{
	t_table tab;
	char	**args;
	int		*field_indices;
	int		*row_indices;
	int		field_count;
	int		row_count;

	tab.name = ft_get_outer_str(buffer);


	if (!tab.name)
		return ;

	tab = ft_deserialize_table(tab.name);

	args = ft_get_args(buffer);
	if (!args)
		return ;

	field_indices = ft_get_field_indices(args, &field_count, tab);
	if (!field_indices)
		return ;

	
	row_indices = ft_where(buffer, &row_count, tab);
	if (!row_indices)
		return ;

	ft_display_rows(field_indices, field_count, row_indices, row_count, tab);
	free(field_indices);
	free(row_indices);
	ft_arrdel2(args);
}





