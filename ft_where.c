#include "ft_db.h"











int	ft_get_field_index(char *field, t_table tab)
{
	int i;

	i = -1;
	while (++i < tab.col_count)
		if (ft_strequ(tab.fields[i].name, field))
			return (i);
	ft_printf("Error: No field \"%s\" in Table \"%s\"\n", field, tab.name);
	return (-1);
}





int ft_where_match(t_data *row_val, char *type, char *op, char *cmp_val)
{
	int	result;

	if (ft_strequ(type, "int"))
	{
		result = row_val->i - ft_atoi(cmp_val);
		if (ft_strequ(op, "==") && result == 0)
			return (1);
		else if (ft_strequ(op, ">=") && result >= 0)
			return (1);
		else if (ft_strequ(op, "<=") && result <= 0)
			return (1);
		else if (ft_strequ(op, ">") && result > 0)
			return (1);
		else if (ft_strequ(op, ">") && result > 0)
			return (1);
		else 
			return (0);
	}
	else 
	{
		result = ft_strcmp(row_val->str, cmp_val);
			if (ft_strequ(op, "==") && result == 0)
			return (1);
		else if (ft_strequ(op, ">=") && result >= 0)
			return (1);
		else if (ft_strequ(op, "<=") && result <= 0)
			return (1);
		else if (ft_strequ(op, ">") && result > 0)
			return (1);
		else if (ft_strequ(op, ">") && result > 0)
			return (1);
		else 
			return (0);
	}
}









int	*ft_where(char *buffer, int *row_count, t_table tab)
{
	int		*row_indices;
	char	*trimmed;
	char	**args;
	int		arg_count;

	trimmed = ft_strtrim(ft_strchr(buffer, ')') + 1);
	if (!ft_check_str_begin(trimmed, "WHERE"))
		return (NULL);
	args = ft_get_args(trimmed + 5);
	if (!args)
		return (NULL);
//	arg_count = ft_arrlen2(args);
	

	char	**split;
	int		field_i;
//	int i;
	int j;

	row_indices = NULL;
	*row_count = 0;
//	i = -1;
//	while (++i < arg_count)
//	{
		split = ft_strsplit(args[0],  ' ');
		if (ft_arrlen2(split) != 3)
			return (NULL);
		field_i = ft_get_field_index(split[0], tab);
		if (field_i < 0)
			return (NULL);
		j = -1;
		while (++j < tab.row_count)
		{
			if (ft_where_match(tab.rows[j][field_i], tab.fields[field_i].type, split[1], split[2]))
			{
				(*row_count)++;
				row_indices = (int*)realloc(row_indices, sizeof(int) * *row_count);
				row_indices[*row_count - 1] = j;
			}
		}
//	}
	return (row_indices);
}



	


