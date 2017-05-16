/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_serialize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 16:57:37 by biremong          #+#    #+#             */
/*   Updated: 2017/05/05 18:24:17 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	ft_serialize_tab(t_table tab)
{
	FILE *fp;

	fp = fopen(tab.name, "w");
	ft_serialize_tab_data(fp, tab);
	ft_serialize_rows(fp, tab);
	fclose(fp);
}

void	ft_serialize_tab_data(FILE *fp, t_table tab)
{
	int i;
	
	fprintf(fp, "%lu:\"%s\",", strlen(tab.name), tab.name);
	fprintf(fp, "%d,{", tab.col_cnt);
	i = -1;
	while (++i < tab.col_cnt)
	{
		fprintf(fp, "%lu:\"%s\"|", strlen(tab.flds[i].name), tab.flds[i].name);
		fprintf(fp, "%s;", tab.flds[i].type);
	}
	fprintf(fp, "},");
	fprintf(fp, "%d\n", tab.row_cnt);
}

void	ft_serialize_rows(FILE *fp, t_table tab)
{
	int	i, k;

	i = -1;
	while (++i < tab.row_cnt)
	{
		k = -1;
		while (++k < tab.col_cnt)
			ft_typrint(tab.flds[k].type, tab.rows[i][k], fp);
		fprintf(fp, "\n");
	}
}

void	ft_typrint(char *type, t_data *value, FILE *fp)
{
	if (!value)
		fprintf(fp, "%c,", '~');
	else if (ft_strequ(type, "int"))
		fprintf(fp, "%d,", value->i);
	else if (ft_strequ(type, "flt"))
		fprintf(fp, "%f,", value->f);
	else if (ft_strequ(type, "str"))
		fprintf(fp, "%lu:\"%s\",", strlen(value->str), value->str);
}
