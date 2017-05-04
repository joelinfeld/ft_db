#include "ft_db.h" //all rows just return NULL and be same as none

int	*ft_where(char *buffer, int *match_cnt, t_table tab)
{
	char	*trimmed;
	char	**args;
	int		arg_cnt;

	trimmed = ft_strtrim(ft_strchr(buffer, ')') + 1);//do all check here
	if (ft_strlen(trimmed) == 0)
		return (ft_all_row_inds(tab.row_cnt, match_cnt));
	if (!ft_check_str_begin(trimmed, "WHERE"))
		return (NULL);
	args = ft_get_args(trimmed + 5);
	if (!args)
		return (NULL);
	arg_cnt = ft_arrlen2(args);
	if (arg_cnt == 1 && ft_strequ(args[0], "*"))
		return (ft_all_row_inds(tab.row_cnt, match_cnt));
	return (ft_get_matches(tab, args, arg_cnt,  match_cnt)); //free args, trimmed
}



int	*ft_get_matches(t_table tab, char **args, int arg_cnt, int *match_cnt)
{
	int		*row_inds;
	char	**split;
	int		fld_i;
	int 	i;
	int 	j;

	row_inds = NULL;
	*match_cnt = 0;
	i = -1;
	while (++i < tab.row_cnt)
	{
		j = -1;
		while (++j < arg_cnt)
		{
			split = ft_strsplit(args[j],  ' ');
			if (ft_arrlen2(split) != 3)
				return (NULL);
			fld_i = ft_get_fld_ind(split[0], tab);
			if (fld_i < 0)
				return (NULL);
			if (!ft_is_match(tab.rows[i][fld_i], tab.flds[fld_i].type, split[1], split[2]))
				break ;
		}
		if (j == arg_cnt)
		{
			(*match_cnt)++;
			row_inds = (int*)realloc(row_inds, sizeof(int) * *match_cnt);
			row_inds[*match_cnt - 1] = i;
		}
	}
	return (row_inds);
}


			






int ft_is_match(t_data *row_val, char *type, char *op, char *cmp_val)
{
	int	result;

	if (ft_strequ(cmp_val, "NULL") && !row_val)
		return (ft_strequ(op, "="));
	else if (ft_strequ(cmp_val, "NULL"))
		return (ft_strequ(op, "!="));
	else if (!row_val)
		return (0);
	else if (ft_strequ(type, "int"))
		result = row_val->i - ft_atoi(cmp_val);
	else
		result = ft_strcmp(row_val->str, cmp_val);
	if (ft_strequ(op, "=") && result == 0)
		return (1);
	else if (ft_strequ(op, "!=") && result != 0)
		return (1);
	else if (ft_strequ(op, ">=") && result >= 0)
		return (1);
	else if (ft_strequ(op, "<=") && result <= 0)
		return (1);
	else if (ft_strequ(op, ">") && result > 0)
		return (1);
	else if (ft_strequ(op, "<") && result < 0)
		return (1);
	else 
		return (0);
}



int	*ft_all_row_inds(int row_cnt, int *match_cnt)
{
	int *row_inds;
	int i;

	*match_cnt = row_cnt;
	row_inds = (int*)ft_malloc(sizeof(int) * row_cnt);
	i = -1;
	while (++i < row_cnt)
		row_inds[i] = i;
	return (row_inds);
}
