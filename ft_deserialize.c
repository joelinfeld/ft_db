//I WANT TO USE FT_GNL INSTEADS OF FGETS, BUT NEED AN FD INSTEAD OF FP, BUT FPRINTF TAKES FP
#include "ft_db.h"

char *ft_get_table_name(char *name_data)
{
	int len;

	len = ft_atoi(name_data);
	name_data = ft_strchr(name_data, '\"') + 1;
	return (ft_strndup(name_data, len));
}

t_field *ft_get_table_fields(char *field_data, int col_count)
{
	t_field *fields;
	int len;
	int i;
	
	fields = (t_field*)ft_malloc(sizeof(t_field) * col_count);
	i = 0;
	while (i < col_count)
	{
		field_data++;
		len = ft_atoi(field_data);

		field_data = ft_strchr(field_data, '\"') + 1;
		fields[i].name = ft_strndup(field_data, len);
		field_data = ft_strchr(field_data, '\"') + 2;
		fields[i].type = ft_strndup(field_data, 3);
		field_data += 3;
		i++;
	}
	return (fields);
}

t_table	ft_deserialize_table_data(FILE *fp)
{
	t_table tab;
	char line[255];
	char **split;

	fgets(line, 255, fp);
	split = ft_strsplit(line, ',');
	tab.name = ft_get_table_name(split[0]);
	tab.col_count = ft_atoi(split[1]);
	tab.fields = ft_get_table_fields(split[2], tab.col_count);
	tab.row_count = ft_atoi(split[3]);
	return (tab);
}

void	ft_get_value(FILE *fp, char *type, char *cell_str, t_data **value)
{
	int 	len;

	if (*cell_str == '~')
	{
		*value = NULL;
		return ;
	}
	*value = (t_data*)ft_malloc(sizeof(t_data));

	if (ft_strequ(type, "int"))
		(*value)->i = ft_atoi(cell_str);


	else if (ft_strequ(type, "str"))
	{


		len = ft_atoi(cell_str);


		cell_str = ft_strchr(cell_str, '\"') + 1;



		(*value)->str = ft_strndup(cell_str, len);
	}


}




t_data	***ft_deserialize_rows(FILE *fp, t_table tab)
{
	t_data ***rows;
	char line[255];
	char **split;
	int i;
	int j;

	rows = (t_data***)ft_malloc(sizeof(t_data**) * tab.row_count);
	i = -1;
	while (++i < tab.row_count)
	{
		rows[i] = (t_data**)ft_malloc(sizeof(t_data*) * tab.col_count);
		fgets(line, 255, fp);
		split = ft_strsplit(line, ',');
		j = -1;

		while (++j < tab.col_count)
			ft_get_value(fp, tab.fields[j].type, split[j], &(rows[i][j]));



	}
	return (rows);
}





t_table	ft_deserialize_table(char *table_name)
{
	FILE *fp;
	t_table tab;

	fp = fopen(table_name, "r");

	tab = ft_deserialize_table_data(fp);


	tab.rows = ft_deserialize_rows(fp, tab);


	fclose(fp);
	return (tab);
}
