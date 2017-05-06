/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_cols.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 16:36:45 by jinfeld           #+#    #+#             */
/*   Updated: 2017/05/05 17:29:42 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	ft_delete_cols(char *buffer)
{
	t_table		tab;
	char		**args;
	int			*fld_inds;
	int			arg_cnt, i;

	if (ft_parse_function(buffer, &tab, &args) > 0)
		return ;
	fld_inds = ft_get_fld_inds(args, &arg_cnt, tab);
	if (!fld_inds)
		return ;
	qsort(fld_inds, arg_cnt, sizeof(int), ft_int_cmp);
	i = -1;
	while (++i < arg_cnt)
	{
		if (fld_inds[i] != 0)
			ft_delete_column(fld_inds[i], &tab);
		else
			ft_db_error(4, tab.flds[0].name);
	}
	ft_serialize_tab(tab);
	ft_free_tab(tab);
	ft_arrdel2(args);
	free(fld_inds);
}

void	ft_delete_column(int fld_ind, t_table *tab)
{
	int j;

	j = -1;
	while (++j < tab->row_cnt)
	{
		if (tab->rows[j][fld_ind])
			free(tab->rows[j][fld_ind]);
		if (fld_ind != tab->col_cnt - 1)
			tab->rows[j][fld_ind] = tab->rows[j][tab->col_cnt - 1];
		tab->rows[j] = (t_data**)realloc(
				tab->rows[j], sizeof(t_data*) * (tab->col_cnt - 1));
	}
	tab->flds[fld_ind] = tab->flds[tab->col_cnt - 1];
	tab->flds = (t_field*)realloc(tab->flds, sizeof(t_field) * (tab->col_cnt - 1));
	tab->col_cnt--;
}

int		ft_int_cmp(const void *a, const void *b)
{
	return (*(int*)b - *(int*)a);
}
