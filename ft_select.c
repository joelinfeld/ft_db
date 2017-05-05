#include "ft_db.h"



void	ft_select(char *buffer)
{
	t_table tab;
	char	**args;
	int		*fld_inds;
	int		*row_inds;
	int		fld_cnt;
	int		row_cnt;

	if (ft_parse_function(buffer, &tab, &args) < 0)
		return ;
	fld_inds = ft_get_fld_inds(args, &fld_cnt, tab);
	if (!fld_inds)
		return ;
	row_inds = ft_where(buffer, &row_cnt, tab);
	if (!row_inds)
	{
		ft_printf("WHERE Clause Format Error\n");
		return ;
	}
	if (ft_order_by(buffer, &tab) < 0)
	{
		ft_printf("Format Error");
		return ;
	}
	ft_display_rows(fld_inds, fld_cnt, row_inds, row_cnt, tab);
	free(fld_inds);
	free(row_inds);
	ft_arrdel2(args);
}


