#include "ft_db.h"

int	*ft_get_fld_inds(char **fld_args, int *arg_cnt, t_table tab)
{
	int *fld_inds;
	int i;
	int j;

	*arg_cnt = ft_arrlen2(fld_args);
	if (*arg_cnt == 1 && ft_strequ(fld_args[0], "*"))
		fld_inds = ft_all_fld_inds(tab.col_cnt, arg_cnt);
	else
	{
		fld_inds = (int*)ft_malloc(sizeof(int) * *arg_cnt);
		i = -1;
		while (++i < *arg_cnt)
		{
			j = -1;
			while (++j < tab.col_cnt)
			{//
				if (ft_strequ(fld_args[i], tab.flds[j].name))
				{
					fld_inds[i] = j;
					break ;
				}
			}//
			if (j == tab.col_cnt)
				return (ft_no_fld_match(fld_inds, fld_args[i], tab.name));
		}
	}
	return (fld_inds);
}

int	ft_get_fld_ind(char *fld, t_table tab)
{
	int i;

	i = -1;
	while (++i < tab.col_cnt)
		if (ft_strequ(tab.flds[i].name, fld))
			return (i);
	ft_printf("Error: No field \"%s\" in Table \"%s\"\n", fld, tab.name);
	return (-1);
}


int	*ft_all_fld_inds(int col_cnt, int *fld_cnt)
{
	int *cols;
	int i;

	cols = (int*)ft_malloc(sizeof(int) * col_cnt);
	i = -1;
	while (++i < col_cnt)
		cols[i] = i;
	*fld_cnt = col_cnt;
	return (cols);
}



void	*ft_no_fld_match(int *inds, char *fld_name, char *tab_name)
{
	ft_printf("Error: No Field \"%s\" in Table \"%s\"\n", fld_name, tab_name);
	free(inds);
	return (NULL);
}



