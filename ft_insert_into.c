#include "ft_db.h"
/*
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
		ft_printf("Table \"%s\" Does Not Exist\n", buffer);
}
*/





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





t_cell	*ft_new_row(t_table tab)
{
	t_cell	*row;
	int 	i;

	row = (t_cell*)ft_malloc(sizeof(t_cell) * tab.col_count);
	i = 0;
	while (i < tab.col_count)
	{
		row[i].field = ft_strdup(tab.fields[i].name);
		row[i].type = ft_strdup(tab.fields[i].type);
		row[i].value = NULL;
		i++;
	}
	return (row);
}



/*
int	ft_get_insert_table(char *buffer, t_table *tab)
{
	char *table_name;

	if (ft_parse_table_name(buffer, &table_name) < 0)
		return (-1);
	if (access(table_name, F_OK) == -1)
	{
		ft_printf("Table \"%s\" Does Not Exist\n", table_name);
		return (-1);
	}
	*tab = ft_deserialize_table(table_name);
	return (0);
}
*/

/*
int	ft_get_args(char *buffer,char ***field_args)
{
	char	*arg_str;
	int		arg_count;
	char	*trimmed;
	int		i;

	arg_str = ft_strchr(buffer, '(') + 1;
	if (!ft_strchr(arg_str, ')'))
	{
		ft_printf("Format Error\n");
		return (-1);
	}
	*ft_strchr(arg_str, ')') = '\0';
	*field_args = ft_strsplit(arg_str, ',');
	arg_count = ft_arrlen2(*field_args);
	i = -1;
	while (++i < arg_count)
	{
		trimmed = ft_strtrim((*field_args)[i]);
		free((*field_args)[i]);
		(*field_args)[i] = trimmed;
	}
	return (0);
}
*/



int	ft_no_field_match(int *indices, char *field, char *table)
{
	ft_printf("Error: No Field \"%s\" in Table \"%s\"\n", field, table);
	free(indices);
	return (-1);
}




int	ft_get_field_indices(char **field_args, int **field_indices, int *field_count, t_table tab)
{
	int i;
	int j;

	*field_count = ft_arrlen2(field_args);
	if (*field_count == 1 && ft_strequ(field_args[0], "*"))
		*field_indices = ft_all_field_indices(tab, field_count);
	else
	{
		*field_indices = (int*)ft_malloc(sizeof(int) * *field_count);
		i = -1;
		while (++i < *field_count)
		{
			j = -1;
			while (++j < tab.col_count)
				if (ft_strequ(field_args[i], tab.fields[j].name))
				{
					(*field_indices)[i] = j;
					break ;
				}
			if (j == tab.col_count)
				return (ft_no_field_match(*field_indices, field_args[i], tab.name));
		}
	}
	return (0);
}





void	ft_add_row_to_table(char **value_args, int *field_indices, t_table *tab)
{
	int 	value_count;
	char 	*trimmed;
	t_cell	*row;
	int 	i;
	int 	j;

	tab->row_count++;
	tab->rows = (t_cell**)realloc(tab->rows, sizeof(t_cell*) * (tab->row_count));
	tab->rows[tab->row_count - 1] = ft_new_row(*tab);
	row = tab->rows[tab->row_count - 1];
	value_count = ft_arrlen2(value_args);
	i = 0;
	while (i < value_count)
	{
		j = field_indices[i];
		row[j].field = ft_strdup(tab->fields[j].name);
		row[j].type = ft_strdup(tab->fields[j].type);
		row[j].value = (t_data*)ft_malloc(sizeof(t_data));
		trimmed = ft_strtrim(value_args[i]);
		if (ft_strequ(tab->fields[j].type, "int"))
			row[j].value->i = ft_atoi(trimmed);
		else if (ft_strequ(tab->fields[j].type, "str"))
			row[j].value->str = ft_strdup(trimmed);
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

		
	






void	ft_insert_into(char *buffer)
{
	t_table tab;
	char	**field_args;
	int		*field_indices;
	int		field_count;

	tab.name = ft_get_outer_str(buffer);
	if (!tab.name)
		return ; //free name?
	tab = ft_deserialize_table(tab.name);
	field_args = ft_get_args(buffer);
	if (!field_args)
		return ;
	if (ft_get_field_indices(field_args, &field_indices, &field_count, tab) < 0)
		return ;
//	ft_arrdel2(field_args);//need to be freed, but having a problem
	ft_get_values(field_indices, field_count, &tab);
	ft_serialize_table(tab);
}












