#include "ft_db.h"


int	*ft_all_field_indices(t_table tab, int *field_count)
{
	int *cols;
	int i;

	cols = (int*)ft_malloc(sizeof(int) * tab.col_count);
	i = -1;
	while (++i < tab.col_count)
		cols[i] = i;
	*field_count = tab.col_count;
	return (cols);
}





t_data	**ft_new_row(t_table tab)
{
	t_data	**row;
	int 	i;

	row = (t_data**)ft_malloc(sizeof(t_data*) * tab.col_count);
	i = -1;
	while (++i < tab.col_count)
		row[i] = NULL;
	return (row);
}



void	*ft_no_field_match(int *indices, char *field, char *table)
{
	ft_printf("Error: No Field \"%s\" in Table \"%s\"\n", field, table);
	free(indices);
	return (NULL);
}




int	*ft_get_field_indices(char **field_args, int *arg_count, t_table tab)
{
	int *field_indices;
	int i;
	int j;

	*arg_count = ft_arrlen2(field_args);
	if (*arg_count == 1 && ft_strequ(field_args[0], "*"))
		field_indices = ft_all_field_indices(tab, arg_count);
	else
	{
		field_indices = (int*)ft_malloc(sizeof(int) * *arg_count);
		i = -1;
		while (++i < *arg_count)
		{
			j = -1;
			while (++j < tab.col_count)
				if (ft_strequ(field_args[i], tab.fields[j].name))
				{
					(field_indices)[i] = j;
					break ;
				}
			if (j == tab.col_count)
				return (ft_no_field_match(field_indices, field_args[i], tab.name));
		}
	}
	return (field_indices);
}





void	ft_add_row_to_table(char **value_args, int *field_indices, t_table *tab)
{
	int 	value_count;
	char 	*trimmed;
	t_data	**row;
	int 	i;
	int 	j;

	tab->row_count++;
	tab->rows = (t_data***)realloc(tab->rows, sizeof(t_data**) * (tab->row_count));
	tab->rows[tab->row_count - 1] = ft_new_row(*tab);
	row = tab->rows[tab->row_count - 1];
	value_count = ft_arrlen2(value_args);
	i = 0;
	while (i < value_count)
	{
		j = field_indices[i];
		row[j] = (t_data*)ft_malloc(sizeof(t_data));
		trimmed = ft_strtrim(value_args[i]);
		if (ft_strequ(tab->fields[j].type, "int"))
			row[j]->i = ft_atoi(trimmed);
		else if (ft_strequ(tab->fields[j].type, "str"))
			row[j]->str = ft_strdup(trimmed);
		free(trimmed);
		i++;
	}
}




int	ft_get_insertion_count(void)
{
	char 	*buffer;
	int		row_count;

	ft_printf("# OF ROWS TO INSERT: ");
	ft_gnl(0, &buffer);
	row_count = ft_atoi(buffer);
	free(buffer);
	return (row_count);
}




int	ft_wrong_arg_count(char **value_args, int field_count, char *buffer)
{
	if (ft_arrlen2(value_args) != field_count)
	{
		free(buffer);
		ft_arrdel2(value_args);
		ft_printf("Incorrect Number of Values\n");
		return (1);
	}
	return (0);
}



void	ft_get_values(int *field_indices, int field_count, t_table *tab)
{
	char 	*buffer;
	int 	i;
	int		row_count;
	char	**value_args;
	
	row_count = ft_get_insertion_count();
	i = 0;
	while (i < row_count)
	{
		ft_printf("INSERTION %d: ", i + 1);
		ft_gnl(0, &buffer);
		value_args = ft_get_args(buffer);
		if (!value_args)
		{
			free(buffer);
			continue ;
		}
		if (ft_wrong_arg_count(value_args, field_count, buffer))
			continue ;
		ft_add_row_to_table(value_args, field_indices, tab);
		free(buffer);
		ft_arrdel2(value_args);
		i++;
	}
}

		
	






void	ft_insert_rows(char *buffer)
{
	t_table tab;
	char	**field_args;
	int		*field_indices;
	int		arg_count;

	tab.name = ft_get_outer_str(buffer);
	if (!tab.name)
		return ; //free name?
	tab = ft_deserialize_table(tab.name);
	field_args = ft_get_args(buffer);
	if (!field_args)
		return ;
	field_indices = ft_get_field_indices(field_args, &arg_count, tab);
	if (!field_indices)
		return ;
//	ft_arrdel2(field_args);//need to be freed, but having a problem
	ft_get_values(field_indices, arg_count, &tab);
	ft_serialize_table(tab);
}












