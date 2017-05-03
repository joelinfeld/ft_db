/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <jinfeld@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 19:40:03 by jinfeld           #+#    #+#             */
/*   Updated: 2017/05/02 22:15:58 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_db.h"

void		ft_update(char	*buffer)
{
	t_table		tab;
	char		**field_args;
	char		**values;
	int			i;
	int			colindex;
	int			rowindex;
	int			*cols;
	char		*input;
	int			count;
	int			j;
	int			*row_indices;
	int			rows;
	
	tab.name = ft_get_outer_str(buffer);
	if (!tab.name)
		return ;
	tab = ft_deserialize_table(tab.name);
	field_args = ft_get_args(buffer);
	if (!field_args)
		return ;
	cols = ft_get_field_indices(field_args, &count, tab); 
	row_indices = ft_where(buffer, &rows, tab);
	if (!row_indices)
		return ;
	i = -1;
	while (++i < rows)
	{
		rowindex = row_indices[i];
		ft_printf("Update for %s, %d:", tab.fields[0].name, tab.rows[rowindex][0]->i); 
		ft_gnl(0, &input);
		values = ft_get_args(input); //free?
		j = -1;
		while (++j < count)
		{
			colindex = cols[j];
			if (!tab.rows[rowindex][colindex])
				tab.rows[rowindex][colindex] = (t_data*)malloc(sizeof(t_data));
			if (ft_strequ(values[j], "NULL"))
			{
				free(tab.rows[rowindex][colindex]);
				tab.rows[rowindex][colindex] = NULL;
			}
			else if (ft_strequ(tab.fields[colindex].type, "int"))
				tab.rows[rowindex][colindex]->i = ft_atoi(values[j]);
			else if (ft_strequ(tab.fields[colindex].type, "str"))
				tab.rows[rowindex][colindex]->str = ft_strdup(values[j]);
		}	
	}
	ft_serialize_table(tab);
}
