#include "ft_db.h"

int	ft_row_str_cmp(void *thunk, const void *row1, const void *row2)
{
	t_data	*val1;
	t_data	*val2;
	int		fld_ind;
	int		asc_dsc;

	asc_dsc = (*(int*)thunk > 0 ? 1 : -1);
	fld_ind = (*(int*)thunk) * asc_dsc - 1;

	val1 = (*(t_data***)row1)[fld_ind];
	val2 = (*(t_data***)row2)[fld_ind];
	if (!val2)
		return (-1);
	else if (!val1)
		return (1);
	return(asc_dsc * ft_strcmp(val1->str, val2->str));
}


int	ft_row_int_cmp(void *thunk, const void *row1, const void *row2)
{
	t_data	*val1;
	t_data	*val2;
	int		fld_ind;
	int		asc_dsc;

	asc_dsc = (*(int*)thunk > 0 ? 1 : -1);
	fld_ind = (*(int*)thunk) * asc_dsc - 1;

	val1 = (*(t_data***)row1)[fld_ind];
	val2 = (*(t_data***)row2)[fld_ind];
	if (!val2)
		return (-1);
	else if (!val1)
		return (1);
	return(asc_dsc * (val1->i - val2->i));
}




void	ft_sort(char *buffer)
{
	t_table tab;
	char	**args;
	char	**split;
	int		fld_ind;
	int		thunk;


	if (ft_parse_function(buffer, &tab, &args) < 0)
		return ;
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
	if ((fld_ind = ft_get_fld_ind(split[0], tab)) < 0)
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
	if (ft_strequ(tab.flds[fld_ind].type, "str"))
		qsort_r(tab.rows, tab.row_cnt, sizeof(t_data**), &thunk, ft_row_str_cmp);
	else if (ft_strequ(tab.flds[fld_ind].type, "int"))
		qsort_r(tab.rows, tab.row_cnt, sizeof(t_data**), &thunk, ft_row_int_cmp);
	ft_serialize_tab(tab);
}




