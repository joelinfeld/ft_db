/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_where.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 17:06:26 by biremong          #+#    #+#             */
/*   Updated: 2017/05/05 18:46:40 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		*ft_where(char *buffer, int *match_cnt, t_table tab)
{
	char	*trimmed, *trimmed2;
	char	**args;
	int		arg_cnt;

	trimmed = ft_strtrim(ft_strchr(buffer, ')') + 1);
	if (ft_strlen(trimmed) == 0 || ft_check_str_begin(trimmed, "ORDER BY"))
		return (ft_all_row_inds(tab.row_cnt, match_cnt));
	if (!ft_check_str_begin(trimmed, "WHERE"))
		return (NULL);
	trimmed2 = ft_strtrim(trimmed + 5);
	free(trimmed);
	if (trimmed2[0] != '(')
		return (NULL);
	args = ft_get_args(trimmed2);
	free(trimmed2);
	if (!args)
		return (NULL);
	arg_cnt = ft_arrlen2(args);
	if (arg_cnt == 1 && ft_strequ(args[0], "*"))
	{
		ft_arrdel2(args);
		return (ft_all_row_inds(tab.row_cnt, match_cnt));
	}
	return (ft_get_matches(tab, args, arg_cnt,  match_cnt));
}

int		*ft_get_matches(t_table tab, char **args, int arg_cnt, int *match_cnt)
{
	int		*row_inds;
	char	**split;
	int		fld_ind, i, j;

	row_inds = NULL;
	*match_cnt = 0;
	i = -1;
	while (++i < tab.row_cnt)
	{
		j = -1;
		while (++j < arg_cnt)
		{
			split = ft_strsplit(args[j],  ' ');
			if (ft_arrlen2(split) != 3)
				return (NULL);
			fld_ind = ft_get_fld_ind(split[0], tab);
			if (fld_ind < 0)
				return (NULL);
			if (!ft_is_match(tab.rows[i][fld_ind], tab.flds[fld_ind].type, split[1], split[2]))
				break ;
		}
		if (j == arg_cnt)
		{
			(*match_cnt)++;
			row_inds = (int*)realloc(row_inds, sizeof(int) * *match_cnt);
			row_inds[*match_cnt - 1] = i;
		}
	}
	ft_arrdel2(args);
	return (row_inds);
}

int 	ft_is_match(t_data *row_val, char *type, char *op, char *cmp_val)
{
	int	result;

	if (ft_strequ(cmp_val, "NULL") && !row_val)
		return (ft_strequ(op, "="));
	else if (ft_strequ(cmp_val, "NULL"))
		return (ft_strequ(op, "!="));
	else if (!row_val)
		return (0);
	else if (ft_strequ(type, "int"))
		result = row_val->i - ft_atoi(cmp_val);
	else if (ft_strequ(type, "flt"))
		result = row_val->f - ft_atof(cmp_val);
	else
		result = ft_strcmp(row_val->str, cmp_val);
	if (ft_strequ(op, "=") && result == 0)
		return (1);
	else if (ft_strequ(op, "!=") && result != 0)
		return (1);
	else if (ft_strequ(op, ">=") && result >= 0)
		return (1);
	else if (ft_strequ(op, "<=") && result <= 0)
		return (1);
	else if (ft_strequ(op, ">") && result > 0)
		return (1);
	else if (ft_strequ(op, "<") && result < 0)
		return (1);
	else 
		return (0);
}

int		*ft_all_row_inds(int row_cnt, int *match_cnt)
{
	int *row_inds;
	int i;

	*match_cnt = row_cnt;
	row_inds = (int*)ft_malloc(sizeof(int) * row_cnt);
	i = -1;
	while (++i < row_cnt)
		row_inds[i] = i;
	return (row_inds);
}
