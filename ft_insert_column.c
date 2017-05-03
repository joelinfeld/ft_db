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

void	ft_insert_column(char *buffer)
{
	t_table		*tab;
	char		**field_args;
	char		**split;
	int			newcol;
	int			colcount;
	int			i;
	int			j;

	tab.name = ft_get_outer_str(buffer);
	if (!tab.name)
		return ; //free name?
	tab = ft_deserialize(tab.name);
	field_args = ft_get_args(buffer);
	if (!field_args)
		return ;
	newcol = ft_arrlen2(field_args);
	colcount = newcol + tab.col_count; 
	tab.col_count = colcount;
	tab.fields = (t_field*)realloc(sizeof(t_field) * colcount);
	i = -1;
	while (++i < newcol)
	{
		split = ft_strsplit(field_args[i]);
		if(ft_validate_type(split[1]))
		{
			fields[colcount - newcol - 1 + i].name = ft_strdup(split[0]);
			fields[colcount - newcol - 1 + i].type = ft_strdup(split[1]);
		}
		return ;
	}
	i = -1;
	while (++i < tab.row_count)
	{
		tab.rows[i] = (t_data**)realloc(sizeof(t_data*) * colcount);
		j = -1;
		while (++j < newcol)
			tab.rows[i][colcount - newcol - 1 + j] = NULL;
	}
	ft_serialize(tab);
}
