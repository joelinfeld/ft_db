#include "ft_db.h"

void		ft_delete_rows(char *buffer)
{
	t_table		tab;
	char		**args;
	int			*row_inds;
	int			i;
	int			j;
	int			del_row_cnt;
	int			index;

	if (ft_parse_function(buffer, &tab, &args) > 0)
		return ;
	ft_arrdel2(args);
	if (!(row_inds = ft_where(buffer, &del_row_cnt, tab)))
		return ;
	i = del_row_cnt;
	while (--i >= 0)
	{
		index = row_inds[i];
		j = -1;
		while(++j < tab.col_cnt)
		{
		//for this and del column, should we set pointers to NULL after freeing, before the realloc?
		//and in the case of deleting rows, do we free the double pointers before realloc?
			if (tab.rows[index][j])
				free(tab.rows[index][j]);
			if (index != tab.row_cnt - 1)
				tab.rows[index][j] = tab.rows[tab.row_cnt - 1][j];
		}
		tab.row_cnt -= 1;
	}
	tab.rows = (t_data***)realloc(tab.rows, sizeof(t_data**) * tab.row_cnt);
	ft_serialize_tab(tab);
}
