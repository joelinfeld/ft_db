/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_column.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <jinfeld@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 16:29:33 by jinfeld           #+#    #+#             */
/*   Updated: 2017/05/02 18:25:19 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_db.h"

void	ft_insert_cols(char *buffer)
{
	t_table		tab;
	char		**fld_args;
	char		**split;
	int			new_col_cnt;
	int			i;
	int			j;


	if (ft_parse_function(buffer, &tab, &fld_args) < 0)
		return ;
	new_col_cnt = ft_arrlen2(fld_args);
	tab.col_cnt += new_col_cnt;
	tab.flds = (t_field*)realloc(tab.flds, sizeof(t_field) * tab.col_cnt);
	i = -1;


	while (++i < new_col_cnt)
	{
		split = ft_strsplit(fld_args[i], ' ');
		if(ft_validate_type(split[1]))
		{
			tab.flds[tab.col_cnt - new_col_cnt + i].name = ft_strdup(split[0]);
			tab.flds[tab.col_cnt - new_col_cnt + i].type = ft_strdup(split[1]);
		}
		else
			return ;
	}
	i = -1;
	while (++i < tab.row_cnt)
	{
		tab.rows[i] = (t_data**)realloc(tab.rows[i], sizeof(t_data*) * tab.col_cnt);
		j = -1;
		while (++j < new_col_cnt)
			tab.rows[i][tab.col_cnt - new_col_cnt + j] = NULL;
	}
	ft_serialize_tab(tab);
}