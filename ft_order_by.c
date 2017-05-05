#include "ft_db.h"

void	ft_order_tab(char **args, t_table *tab)
{
	char	**split;
	int		fld_ind;
	int		thunk;

	if (ft_arrlen2(args) != 1)
	{
		ft_printf("Format Error\n");
		return ;
	}
	split = ft_strsplit(args[0], ' ');
	if (ft_arrlen2(split) > 2)
	{
		ft_printf("Format Error\n");
		return ;
	}
	if ((fld_ind = ft_get_fld_ind(split[0], *tab)) < 0)
		return ;
	ft_str_tolower(&split[1]);
	if (!split[1] || ft_strequ(split[1], "asc"))
		thunk = fld_ind + 1;
	else if (ft_strequ(split[1], "dsc"))
		thunk = -(fld_ind + 1);
	else 
	{
		ft_printf("Format Error\n");
		return ;
	}
	if (ft_strequ(tab->flds[fld_ind].type, "str"))
		qsort_r(tab->rows, tab->row_cnt, sizeof(t_data**), &thunk, ft_row_str_cmp);
	else if (ft_strequ(tab->flds[fld_ind].type, "int"))
		qsort_r(tab->rows, tab->row_cnt, sizeof(t_data**), &thunk, ft_row_int_cmp);
}



int	ft_order_by(char *buffer, t_table *tab)
{
	char	*bracket_pnt;
	char	*trimmed;
	char	**args;

	bracket_pnt = ft_strchr(buffer, ')') + 1;
	if (ft_strstr(bracket_pnt, "WHERE"))
		bracket_pnt = ft_strchr(buffer, ')') + 1;
	trimmed = ft_strtrim(bracket_pnt);
	if (ft_strlen(trimmed) == 0)
		return (0);
	if (!ft_check_str_begin(trimmed, "ORDER BY"))
		return (-1);
	args = ft_get_args(trimmed);
	if (!args)
		return (-1);
	ft_order_tab(args, tab);
	return (0);
}
	


	

