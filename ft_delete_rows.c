#include "ft_db.h"

void		ft_delete_rows(char *buffer)
{
	t_table		tab;
	char		**args;
	int			*rows;
	int			i;
	int			j;
	int			rowcount;
	int			index;

	if(!ft_parse_function(buffer, &tab, &args))
		return ;
	rows = ft_where(buffer, &rowcount, tab);
	if (!rows)
		return ;
	i = -1;
	while (++i < rowcount)
	{
		index = rows[i]
		j = -1;
		while(++j < tab.col_count)
		{
		//for this and del column, should we set pointers to NULL after freeing, before the realloc?
		//and in the case of deleting rows, do we free the double pointers before realloc?
			if (tab.rows[index][j])
				free(tab.rows[index][j];
			if (index != tab.row_count - 1)
				tab.rows[index][j] = tab.rows[tab.row_count - 1][j];
			if (tab.rows[tab.row_count - 1][j])
				free(tab.rows[tab.row_count - 1][j]);
		}
		tab.row_count -= 1;
	}
	tab.rows = (t_data***)realloc(tab.rows, sizeof(t_data**) * row_count);
}
