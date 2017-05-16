/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <jinfeld@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 19:40:03 by jinfeld           #+#    #+#             */
/*   Updated: 2017/05/05 18:25:31 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		ft_update(char	*buffer)
{
	t_table	tab;
	char	**fld_args;
	int		*fld_inds, *row_inds;
	int		fld_cnt, row_cnt;
	
	if (ft_parse_function(buffer, &tab, &fld_args) > 0)
		return (0);
	fld_inds = ft_get_fld_inds(fld_args, &fld_cnt, tab);
   	if (!fld_inds)
		return (0);	
	row_inds = ft_where(buffer, &row_cnt, tab);
	if (!row_inds)
		return (ft_db_error(2, ""));
	ft_update_rows(&tab, fld_inds, fld_cnt, row_inds, row_cnt);
	ft_serialize_tab(tab);
	ft_free_tab(tab);
	ft_arrdel2(fld_args);
	free(fld_inds);
	free(row_inds);
	return (0);
}

void	ft_update_rows(t_table *tab, int *fld_inds, int fld_cnt, int *row_inds, int row_cnt)
{
	char	**val_args;
	int		i, j;

	i = 0;
	while (i < row_cnt)
	{
		val_args = ft_get_update_vals(row_inds[i], i, row_cnt, fld_cnt, *tab);
		if (!val_args)
			continue ;
		j = -1;
		while (++j < fld_cnt)
		{
			if (!tab->rows[row_inds[i]][fld_inds[j]])
				tab->rows[row_inds[i]][fld_inds[j]] = (t_data*)ft_malloc(sizeof(t_data));
			if (ft_strequ(val_args[j], "NULL"))
			{
				free(tab->rows[row_inds[i]][fld_inds[j]]);
				tab->rows[row_inds[i]][fld_inds[j]] = NULL;
			}
			else if (ft_strequ(tab->flds[fld_inds[j]].type, "int"))
				tab->rows[row_inds[i]][fld_inds[j]]->i = ft_atoi(val_args[j]);
			else if (ft_strequ(tab->flds[fld_inds[j]].type, "flt"))
				tab->rows[row_inds[i]][fld_inds[j]]->f = ft_atof(val_args[j]);
			else if (ft_strequ(tab->flds[fld_inds[j]].type, "str"))
				tab->rows[row_inds[i]][fld_inds[j]]->str = ft_strdup(val_args[j]);
		}
		i++;
		ft_arrdel2(val_args);
	}
}

char	**ft_get_update_vals(int row_ind, int i, int row_cnt, int fld_cnt, t_table tab)
{
	char	**val_args;
	char	*buffer;

	if (!tab.rows[row_ind][0])
		ft_printf("\x1b[38;2;115;190;255mUpdate (%d of %d) for \"%s\" : (null) >> \x1b[0m",
				i + 1, row_cnt, tab.flds[0].name);
	else if (ft_strequ(tab.flds[0].type, "str"))
		ft_printf("\x1b[38;2;115;190;255mUpdate (%d of %d) for \"%s\" : %s >> \x1b[0m",
				i + 1, row_cnt, tab.flds[0].name, tab.rows[row_ind][0]->str);
	else if (ft_strequ(tab.flds[0].type, "int"))
		ft_printf("\x1b[38;2;115;190;255mUpdate (%d of %d) for \"%s\" : %d >> \x1b[0m",
				i + 1, row_cnt, tab.flds[0].name, tab.rows[row_ind][0]->i);
	else if (ft_strequ(tab.flds[0].type, "flt"))
		ft_printf("\x1b[38;2;115;190;255mUpdate (%d of %d) for \"%s\" : %f >> \x1b[0m",
				i + 1, row_cnt, tab.flds[0].name, tab.rows[row_ind][0]->f);
	ft_gnl(0, &buffer);
	val_args = ft_get_args(buffer);
	if (!val_args || *(val_args[0]) == '\0')
	{
		ft_db_error(2, "");
		return (NULL);
	}
	if (ft_wrong_arg_cnt(val_args, fld_cnt, buffer))
		return (NULL);
	free(buffer);
	return (val_args);
}
