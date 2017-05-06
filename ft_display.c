/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 16:54:40 by jinfeld           #+#    #+#             */
/*   Updated: 2017/05/05 17:35:11 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		*ft_get_col_widths(int *fld_inds, int fld_cnt, int *row_inds, int row_cnt, t_table tab)
{
	int		*col_widths;
	t_data	*value;
	char	*type;
	int		len, i, j;

	col_widths = (int*)ft_malloc(sizeof(int) * fld_cnt);
	i = -1;
	while (++i < fld_cnt)
	{
		col_widths[i] = ft_strlen(tab.flds[fld_inds[i]].name);
		type = tab.flds[fld_inds[i]].type;
		j = -1;
		while (++j < row_cnt)
		{
			value = tab.rows[row_inds[j]][fld_inds[i]];
			if (!value)
				len = 4;
			else if (ft_strequ(type, "int"))
				len = ft_strlen(ft_itoa(value->i));
			else if (ft_strequ(type, "str"))
				len = ft_strlen(value->str);
			if (len > col_widths[i])
				col_widths[i] = len;
		}
	}
	return (col_widths);
}

void	ft_display_hor_line(int *col_widths, int fld_cnt)
{
	int total;
	int i;

	total = fld_cnt + 1;
	i = -1;
	while (++i < fld_cnt)
		total += 4 + col_widths[i];
	i = -1;
	while (++i < total)
		printf("=");
	printf("\n");
}

void	ft_display_table_header(int *fld_inds, int fld_cnt, int *col_widths, t_table tab)
{
	int	pad;
	int	l_pad;
	int	len;
	int i;

	ft_display_hor_line(col_widths, fld_cnt);
	i = -1;
	while (++i < fld_cnt)
	{
		len = ft_strlen(tab.flds[fld_inds[i]].name);
		pad = col_widths[i] + 4 - len;
		l_pad = pad / 2;
		if (pad % 2)
			l_pad++;
		printf("|%*s%*s", l_pad + len, tab.flds[fld_inds[i]].name, pad / 2, ""); 
	}
	printf("|\n");
	ft_display_hor_line(col_widths, fld_cnt);
}

void	ft_display_rows(int *fld_inds, int fld_cnt, int *row_inds, int row_cnt, t_table tab)
{
	t_data	**row;
	int		*col_widths;
	int		i, j;

	col_widths = ft_get_col_widths(fld_inds, fld_cnt, row_inds, row_cnt, tab);
	i = -1;
	ft_display_table_header(fld_inds, fld_cnt, col_widths, tab);
	while (++i < row_cnt)
	{
		row = tab.rows[row_inds[i]];
		j = -1;
		while (++j < fld_cnt)
		{
			if (!row[fld_inds[j]])
				printf("|   %*s ", col_widths[j], "NULL");
			else if (ft_strequ(tab.flds[fld_inds[j]].type, "int"))
				printf("|   %*d ", col_widths[j], row[fld_inds[j]]->i);
			else if (ft_strequ(tab.flds[fld_inds[j]].type, "str"))
				printf("|   %*s ", col_widths[j], row[fld_inds[j]]->str);
		}
		printf("|\n");
	}
	ft_display_hor_line(col_widths, fld_cnt);
	free(col_widths);
}
