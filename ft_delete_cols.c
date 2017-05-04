#include "ft_db.h"

void		ft_delete_cols(char *buffer)
{
	t_table		tab;
	char		**args;
	int			arg_cnt;
	int			*fld_inds;
	int			i;
	int			j;
	int			index;

	if (ft_parse_function(buffer, &tab, &args) < 0)
		return ;
	fld_inds = ft_get_fld_inds(args, &arg_cnt, tab);
	ft_arrdel2(args);
	i = -1;
	//will need to consider reallocing fields and rows.  first going to move them around then worry about that.
	while (++i < arg_cnt)
	{
		index = fld_inds[i];
		if (index != 0)
		{
			j = -1;
			while (++j < tab.row_cnt)
			{
			//this gonna have memory leaks.  as it stands now, just gonna free the t_data in the row, then delete the field;
				if (tab.rows[j][index])
					free(tab.rows[j][index]);
				if (index != tab.col_cnt - 1)
					tab.rows[j][index] = tab.rows[j][tab.col_cnt - 1];
				tab.rows[j] = (t_data**)realloc(tab.rows[j], sizeof(t_data*) * (tab.col_cnt - 1));
			}
		//	if (tab.flds[index])
		//		free(tab.flds[index]);
			tab.flds[index] = tab.flds[tab.col_cnt - 1];
			tab.flds = (t_field*)realloc(tab.flds, sizeof(t_field) * (tab.col_cnt - 1));
			tab.col_cnt -= 1;
		}
		else
			ft_printf("Primary column %s can't be deleted\n", tab.flds[0].name);
	}
	ft_serialize_tab(tab);
}
