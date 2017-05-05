/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <jinfeld@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 19:40:03 by jinfeld           #+#    #+#             */
/*   Updated: 2017/05/04 21:39:21 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_db.h"

void		ft_update(char	*buffer)
{
	t_table		tab;
	char		**fld_args;
	char		**val_args;
	int			i;
	int			fld_i;
	int			row_i;
	int			*fld_inds;
	char		*input;
	int			fld_cnt;
	int			j;
	int			*row_inds;
	int			row_cnt;
	
	if (ft_parse_function(buffer, &tab, &fld_args) > 0)
		return ;
	fld_inds = ft_get_fld_inds(fld_args, &fld_cnt, tab);
   	if (!fld_inds)
		return ;	
	row_inds = ft_where(buffer, &row_cnt, tab);
	if (!row_inds)
		return ;
	i = 0;
	while (i < row_cnt)
	{
		row_i = row_inds[i];
		ft_printf("Update for %s: %d >> ", tab.flds[0].name, tab.rows[row_i][0]->i); 
		ft_gnl(0, &input);
		val_args = ft_get_args(input); //free?
		if (!val_args)
		{
			ft_db_error(2, "");
			continue ;
		}
		j = -1;
		while (++j < fld_cnt)
		{
			fld_i = fld_inds[j];
			if (!tab.rows[row_i][fld_i])
				tab.rows[row_i][fld_i] = (t_data*)ft_malloc(sizeof(t_data));
			if (ft_strequ(val_args[j], "NULL"))
			{
				free(tab.rows[row_i][fld_i]);
				tab.rows[row_i][fld_i] = NULL;
			}
			else if (ft_strequ(tab.flds[fld_i].type, "int"))
				tab.rows[row_i][fld_i]->i = ft_atoi(val_args[j]);
			else if (ft_strequ(tab.flds[fld_i].type, "str"))
				tab.rows[row_i][fld_i]->str = ft_strdup(val_args[j]);
		}
		i++;
	}
	ft_serialize_tab(tab);
}
