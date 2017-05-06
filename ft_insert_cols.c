/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_cols.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <jinfeld@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 16:29:33 by jinfeld           #+#    #+#             */
/*   Updated: 2017/05/05 17:37:04 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		ft_insert_cols(char *buffer)
{
	t_table		tab;
	char		**fld_args;
	int			new_col_cnt, i, j;

	if (ft_parse_function(buffer, &tab, &fld_args) > 0)
		return (-1);
	new_col_cnt = ft_arrlen2(fld_args);
	tab.col_cnt += new_col_cnt;
	tab.flds = (t_field*)realloc(tab.flds, sizeof(t_field) * tab.col_cnt);
	i = -1;
	while (++i < new_col_cnt)
		if (ft_insert_fld(fld_args[i], new_col_cnt, i, &tab) > 0)
			return (-1);
	i = -1;
	while (++i < tab.row_cnt)
	{
		tab.rows[i] = (t_data**)realloc(tab.rows[i], sizeof(t_data*) * tab.col_cnt);
		j = -1;
		while (++j < new_col_cnt)
			tab.rows[i][tab.col_cnt - new_col_cnt + j] = NULL;
	}
	ft_serialize_tab(tab);
	ft_free_tab(tab);
	ft_arrdel2(fld_args);
	return (0);
}

int		ft_insert_fld(char *fld_arg, int new_col_cnt, int i, t_table *tab)
{
	char **split;

	split = ft_strsplit(fld_arg, ' ');
	if (ft_arrlen2(split) != 2)
		return (ft_db_error(2, ""));
	if (ft_repeated_field(split[0], tab->col_cnt - new_col_cnt + i, tab->flds))
		return (ft_db_error(9, split[0]));
	if (ft_strchr(split[0], '\t'))
		return (ft_db_error(2, ""));
	if(ft_validate_type(split[1]))
	{
		tab->flds[tab->col_cnt - new_col_cnt + i].name = ft_strdup(split[0]);
		tab->flds[tab->col_cnt - new_col_cnt + i].type = ft_strdup(split[1]);
	}
	else
		return(ft_db_error(3, split[1]));
	ft_arrdel2(split);
	return (0);
}
