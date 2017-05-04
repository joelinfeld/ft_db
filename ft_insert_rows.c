#include "ft_db.h"

void	ft_insert_rows(char *buffer)
{
	t_table tab;
	char	**fld_args;
	int		*fld_inds;
	int		fld_cnt;

	if (ft_parse_function(buffer, &tab, &fld_args) < 0)
		return ;
	fld_inds = ft_get_fld_inds(fld_args, &fld_cnt, tab);
	if (!fld_inds)
		return ;
//	ft_arrdel2(field_args);//need to be freed, but having a prob?
	ft_populate_new_rows(fld_inds, fld_cnt, &tab);
	ft_serialize_tab(tab);
}






void	ft_populate_new_rows(int *fld_inds, int fld_cnt, t_table *tab)
{
	char 	*buffer;
	int 	i;
	int		row_cnt;
	char	**val_args;
	
	row_cnt = ft_get_insert_cnt();
	i = 0;
	while (i < row_cnt)
	{
		ft_printf("INSERTION #%d >> ", i + 1);
		ft_gnl(0, &buffer);
		val_args = ft_get_args(buffer);
		if (!val_args)
		{
			free(buffer);
			continue ;
		}
		if (ft_wrong_arg_cnt(val_args, fld_cnt, buffer))
			continue ;
		ft_add_row_to_tab(val_args, fld_inds, tab);
		free(buffer);
		ft_arrdel2(val_args);
		i++;
	}
}


int	ft_get_insert_cnt(void)
{
	char 	*buffer;
	int		row_count;

	ft_printf("# OF ROWS TO INSERT >> ");
	ft_gnl(0, &buffer);
	row_count = ft_atoi(buffer);
	free(buffer);
	return (row_count);
}


	
void	ft_add_row_to_tab(char **val_args, int *fld_inds, t_table *tab)
{
	int 	val_cnt;
	char 	*trimmed;
	t_data	**row;
	int 	i;
	int 	j;

	tab->row_cnt++;
	tab->rows = (t_data***)realloc(tab->rows, sizeof(t_data**) * (tab->row_cnt));
	tab->rows[tab->row_cnt - 1] = ft_new_row(*tab);
	row = tab->rows[tab->row_cnt - 1];
	val_cnt = ft_arrlen2(val_args);
	i = -1;
	while (++i < val_cnt)
	{
		j = fld_inds[i];
		trimmed = ft_strtrim(val_args[i]);
		if (ft_strequ(trimmed, "NULL"))
			row[j] = NULL;
		else
		{
			row[j] = (t_data*)ft_malloc(sizeof(t_data));
			if (ft_strequ(tab->flds[j].type, "int"))
				row[j]->i = ft_atoi(trimmed);
			else if (ft_strequ(tab->flds[j].type, "str"))
				row[j]->str = ft_strdup(trimmed);
		}
		free(trimmed);
	}
}




t_data	**ft_new_row(t_table tab)
{
	t_data	**row;
	int 	i;

	row = (t_data**)ft_malloc(sizeof(t_data*) * tab.col_cnt);
	i = -1;
	while (++i < tab.col_cnt)
		row[i] = NULL;
	return (row);
}




int	ft_wrong_arg_cnt(char **val_args, int fld_cnt, char *buffer)
{
	if (ft_arrlen2(val_args) != fld_cnt)
	{
		free(buffer);
		ft_arrdel2(val_args);
		ft_printf("Error: Expecting %d Values\n", fld_cnt);
		return (1);
	}
	return (0);
}

	











