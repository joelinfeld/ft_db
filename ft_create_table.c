#include "ft_db.h"

/*
//these functions allow for user input to create a new table, crating rows not yet functional.
void	ft_create_table(void)
{
	t_table	tab;
	char	*buffer;
	int 	i;

	ft_printf("TABLE NAME: ");
	ft_gnl(0, &tab.table_data.name);
	ft_printf("# OF FIELDS: ", 13);
	ft_gnl(0,  &buffer);
	tab.table_data.col_count = ft_atoi(buffer);
	free(buffer);

	tab.table_data.fields = (t_field*)ft_malloc(sizeof(t_field) * tab.table_data.col_count);
	i = 0;
	while(i < tab.table_data.col_count)
	{
		ft_printf("FIELD: ");
		ft_gnl(0, &tab.table_data.fields[i].field_name);
		ft_printf("TYPE (i/s): ");
		ft_gnl(0, &tab.table_data.fields[i].type);
		i++;
	}
	tab.table_data.row_count = 0;
	ft_serialize_table(tab);
}
*/


int	ft_parse_table_name(char *buffer, char **name)
{	
	int	name_len;

	if (!ft_strchr(buffer, '('))
		return (-1);
	if (!(name_len = ft_strchr(buffer, '(') - buffer))
		return (-1);
	*name = ft_strndup(buffer, name_len);
	return (0);
}

char 	*ft_tolower_str(char *str)
{
	char 	*lower_str;
	int		i;

	lower_str = ft_strnew(ft_strlen(str));
	i = 0;
	while (str[i])
	{
		lower_str[i] = ft_tolower(str[i]);
		i++;
	}
	return (lower_str);
}

int		ft_validate_type(char *type)
{
	char *lower_type;
	int valid;

	valid = -1;
	lower_type = ft_tolower_str(type);
	if (ft_strequ(lower_type, "int"))
		valid = 1;
	else if (ft_strequ(lower_type, "str"))
		valid = 1;
	else if (ft_strequ(lower_type, "dbl"))
		valid = 1;
	free(lower_type);
	return (valid);
}

int	ft_get_field(char *arg, t_field *field)
{
	char	**split;

	split = ft_strsplit(arg, ' ');

	if (ft_arrlen2(split) != 2)
		return (-1);
	if (ft_validate_type(split[1]) < 0)
		return (-1);
	field->name = ft_strdup(split[0]);
	field->type = ft_strdup(split[1]);

	ft_arrdel2(split);
	return (0);
}





int	ft_parse_table_fields(char *buffer, t_field **fields, int *col_count)
{
	char 		*arg_str;
	char		**arg_arr;
	int			i;

	arg_str = ft_strchr(buffer, '(') + 1;
	arg_arr = ft_strsplit(arg_str, ',');
	*col_count = ft_arrlen2(arg_arr);
	*fields = (t_field*)ft_malloc(sizeof(t_field) * *col_count);
	i = 0;
	while (i < *col_count)
	{

		if (i == *col_count - 1)
			arg_arr[i][ft_strlen(arg_arr[i]) - 1] = '\0';
		if (ft_get_field(arg_arr[i], *fields + i) < 0)
			return (-1);

		i++;

	}


	ft_arrdel2(arg_arr);
	return (0);
}

		






void	ft_create_table(void)
{
	t_table	tab;
	char	*buffer;

	ft_printf(">> ");
	ft_gnl(0, &buffer);
	if (ft_parse_table_name(buffer, &tab.name) < 0)
	{
		ft_printf("Format Error\n");
		return ;
	}


	if (ft_parse_table_fields(buffer, &tab.fields, &tab.col_count) < 0)
	{
		ft_printf("Format Error\n");
		return ;
	}
printf("yy %s %s\n", tab.fields[0].name, tab.fields[1].name);

	free(buffer);
	tab.row_count = 0;


	ft_serialize_table(tab);



}
