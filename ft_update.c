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

void		ft_update(char	*buffer)
{
	t_table		*tab;
	char		**field_args;
	char		**values;
	int			i;
	int			index;
	int			*cols;
	char		*input;
	int			count;
	int			j;
	
	tab.name = ft_get_outer_str(buffer);
	if (!tab.name)
		return ;
	tab = ft_deserialize(tab.name);
	field_args = ft_get_args(buffer);
	if (!field_args)
		return ;
	cols = ft_get_field_indices(field_args, &count, tab); 
	i = -1;
	while (++i < tab.row_count)
	{
		ft_gnl(0, &input)
		values = ft_get_args(input); //free?
		j = -1;
		while (++j < count)
		{
			index = cols[j];
			if (tab.fields[index].type = "int")
				tab.rows[i][index]->i = ft_atoi(values[j]);
			if (tab.fields[index].type = "str")
				tab.rows[i][index]->str = ft_strdup(values[j]);
		}	
	}
	ft_serialize(tab);
}
