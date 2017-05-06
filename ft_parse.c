/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 17:11:10 by biremong          #+#    #+#             */
/*   Updated: 2017/05/05 17:11:12 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

char	*ft_get_outer_str(char *buffer)
{
	char	*bracket_pnt;
	char	*outer_str;

	bracket_pnt = ft_strchr(buffer, '(');
	if (!bracket_pnt)
		return (NULL);
	bracket_pnt[0] = '\0';
	outer_str = ft_strtrim(buffer);
	if (!*outer_str || ft_strchr(outer_str, ' ') || ft_strchr(outer_str, '\t'))
		return (NULL);
	bracket_pnt[0] = '(';
	return (outer_str);
}

char	**ft_get_args(char *buffer)
{
	char	*arg_str, *trimmed, *bracket_pnt;
	char	**split_args;
	int		i;

	if (!ft_strchr(buffer, '('))
		return (NULL);
	arg_str = ft_strchr(buffer, '(') + 1;
	bracket_pnt = ft_strchr(arg_str, ')');
	if (!bracket_pnt)
		return (NULL);
	bracket_pnt[0] = '\0';
	split_args = ft_strsplit(arg_str, ',');
	if (!split_args[0])
	{
		split_args = (char**)realloc(split_args, sizeof(char*) * 2);
		split_args[0] = ft_strnew(0);
		split_args[1] = NULL;
	}
	i = -1;
	while (split_args[++i])
	{
		trimmed = ft_strtrim(split_args[i]);
		free(split_args[i]);
		split_args[i] = trimmed;
	}
	bracket_pnt[0] = ')';
	return (split_args);
}

int		ft_parse_function(char *buffer, t_table *tab, char ***args)
{
	char	*table_name;

	table_name = ft_get_outer_str(buffer);
	if (!table_name)
		return (ft_db_error(2, ""));
	if(ft_deserialize_tab(table_name, tab))
		return (1);
	*args = ft_get_args(buffer);
	if (!*args)
		return (ft_db_error(2, ""));
	free(table_name);
	return (0);
}

int		ft_check_str_begin(char *buffer, char *str)
{
	if (ft_strnequ(buffer, str, ft_strlen(str)))
		return (1);
	else
		return (0);
}
