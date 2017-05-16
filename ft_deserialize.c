/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deserialize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 16:54:30 by jinfeld           #+#    #+#             */
/*   Updated: 2017/05/05 18:18:58 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		ft_deserialize_tab(char *tab_name, t_table *tab)
{
	int	fd;
	
	if(access(tab_name, F_OK) == -1)
		return (ft_db_error(7, tab_name));
	fd = ft_open(tab_name);
	*tab = ft_deserialize_tab_data(fd);
	tab->rows = ft_deserialize_rows(fd, *tab);
	ft_close(fd);
	return (0);
}

t_table	ft_deserialize_tab_data(int	fd)
{
	t_table tab;
	char 	*buffer;
	char 	**split;

	ft_gnl(fd, &buffer);
	split = ft_strsplit(buffer, ',');
	tab.name = ft_get_tab_name(split[0]);
	tab.col_cnt = ft_atoi(split[1]);
	tab.flds = ft_get_tab_flds(split[2], tab.col_cnt);
	tab.row_cnt = ft_atoi(split[3]);
	ft_arrdel2(split);
	free(buffer);
	return (tab);
}

char	*ft_get_tab_name(char *name_data)
{
	int len;

	len = ft_atoi(name_data);
	name_data = ft_strchr(name_data, '\"') + 1;
	return (ft_strndup(name_data, len));
}

t_field	*ft_get_tab_flds(char *fld_data, int col_cnt)
{
	t_field *flds;
	int 	len;
	int 	i;
	
	flds = (t_field*)ft_malloc(sizeof(t_field) * col_cnt);
	i = -1;
	while (++i < col_cnt)
	{
		fld_data++;
		len = ft_atoi(fld_data);
		fld_data = ft_strchr(fld_data, '\"') + 1;
		flds[i].name = ft_strndup(fld_data, len);
		fld_data = ft_strchr(fld_data, '\"') + 2;
		flds[i].type = ft_strndup(fld_data, 3);
		fld_data += 3;
	}
	return (flds);
}

t_data	***ft_deserialize_rows(int fd, t_table tab)
{
	t_data	***rows;
	char 	*buffer;
	char 	**split;
	int 	i, j;

	rows = (t_data***)ft_malloc(sizeof(t_data**) * tab.row_cnt);
	i = -1;
	while (++i < tab.row_cnt)
	{
		rows[i] = (t_data**)ft_malloc(sizeof(t_data*) * tab.col_cnt);
		ft_gnl(fd, &buffer);
		split = ft_strsplit(buffer, ',');
		j = -1;
		while (++j < tab.col_cnt)
			rows[i][j] = ft_get_value(tab.flds[j].type, split[j]);
		free(buffer);
		ft_arrdel2(split);
	}
	return (rows);
}

t_data	*ft_get_value(char *type, char *cell_str)
{
	t_data	*value;
	int 	len;

	if (*cell_str == '~')
		return (NULL);
	value = (t_data*)ft_malloc(sizeof(t_data));
	if (ft_strequ(type, "int"))
		value->i = ft_atoi(cell_str);
	else if (ft_strequ(type, "flt"))
		value->f = ft_atof(cell_str);
	else if (ft_strequ(type, "str"))
	{
		len = ft_atoi(cell_str);
		cell_str = ft_strchr(cell_str, '\"') + 1;
		value->str = ft_strndup(cell_str, len);
	}
	return (value);
}
