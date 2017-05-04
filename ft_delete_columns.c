#include "ft_db.h"

void		ft_delete_columns(char *buffer)
{
	t_table		tab;
	char		**args;
	int			argcount;
	int			*cols;
	int			i;
	int			j;
	int			index;

	if(!ft_parse_function(buffer, &tab, &args))
		return ;
	cols = ft_get_field_indices(args, &argcount, tab);
	i = -1;
	//will need to consider reallocing fields and rows.  first going to move them around then worry about that.
	while (++i < argcount)
	{
		index = cols[i];
		j = -1;
		if (index != 0)
		{
			while (++j < tab.row_count)
			{
			//this gonna have memory leaks.  as it stands now, just gonna free the t_data in the row, then delete the field;
				if (tab.rows[j][index])
					free(tab.rows[j][index]);
				if (index != tab.col_count - 1)
				{
					tab.rows[j][index] = tab.rows[j][tab.col_count - 1];
					if (tab.rows[j][tab.col_count - 1])
						free(tab.rows[j][tab.col_count - 1])
				}
				tab.rows[j] = (t_data**)realloc(tab.rows[j], sizeof(t_data*) * (tab.col_count - 1));
			}
			if (tab.fields[index])
				free(tab.fields[index]);
			tab.fields[index] = tab.fields[tab.col_count - 1];
			tab.fields = (t_field*)realloc(tab.fields, sizeof(t_field) * (tab.col_count - 1));
			tab.col_count -= 1;
		}
		else
			ft_printf("Primary column %s can't be deleted.", tab.fields[0].name)
	}
}
