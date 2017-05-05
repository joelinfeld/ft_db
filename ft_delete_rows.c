#include "ft_db.h"

int	ft_delete_rows(char *buffer)
{
	t_table		tab;
	char		**args;
	int			*row_inds;
	int			del_row_cnt, i, j;

	if (ft_parse_function(buffer, &tab, &args) > 0)
		return (0);
	if (ft_arrlen2(args) != 1 || *(args[0]) != '\0')
		return (ft_db_error(2, ""));
	ft_arrdel2(args);
	if (!(row_inds = ft_where(buffer, &del_row_cnt, tab)))
		return (ft_db_error(2, ""));
	i = del_row_cnt;
	while (--i >= 0)
	{
		j = -1;
		while(++j < tab.col_cnt)
		{
			if (tab.rows[row_inds[i]][j])
				free(tab.rows[row_inds[i]][j]);
			if (row_inds[i] != tab.row_cnt - 1)
				tab.rows[row_inds[i]][j] = tab.rows[tab.row_cnt - 1][j];
		}
		tab.row_cnt -= 1;
	}
	tab.rows = (t_data***)realloc(tab.rows, sizeof(t_data**) * tab.row_cnt);
	ft_serialize_tab(tab);
	return (0);
}
