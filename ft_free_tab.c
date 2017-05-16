/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 15:03:09 by biremong          #+#    #+#             */
/*   Updated: 2017/05/05 16:00:57 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	ft_free_tab(t_table tab)
{
	int i, j;

	free(tab.name);
	i = -1;
	while (++i < tab.row_cnt)
	{
		j = -1;
		while (++j < tab.col_cnt)
			if (tab.rows[i][j])
			{
				if (ft_strequ(tab.flds[j].type, "str"))
					free(tab.rows[i][j]->str);
				free(tab.rows[i][j]);
			}
		free(tab.rows[i]);
	}
	i = -1;
	while (++i < tab.col_cnt)
	{
		free(tab.flds[i].name);
		free(tab.flds[i].type);
	}
	free(tab.flds);
}
