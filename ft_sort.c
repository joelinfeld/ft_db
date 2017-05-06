/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 17:11:39 by biremong          #+#    #+#             */
/*   Updated: 2017/05/05 18:28:57 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		ft_row_str_cmp(void *thunk, const void *row1, const void *row2)
{
	t_data	*val1, *val2;
	int		fld_ind, asc_dsc;

	asc_dsc = (*(int*)thunk > 0 ? 1 : -1);
	fld_ind = (*(int*)thunk) * asc_dsc - 1;

	val1 = (*(t_data***)row1)[fld_ind];
	val2 = (*(t_data***)row2)[fld_ind];
	if (!val2)
		return (-1);
	else if (!val1)
		return (1);
	return(asc_dsc * ft_strcmp(val1->str, val2->str));
}

int		ft_row_int_cmp(void *thunk, const void *row1, const void *row2)
{
	t_data	*val1, *val2;
	int		fld_ind, asc_dsc;

	asc_dsc = (*(int*)thunk > 0 ? 1 : -1);
	fld_ind = (*(int*)thunk) * asc_dsc - 1;

	val1 = (*(t_data***)row1)[fld_ind];
	val2 = (*(t_data***)row2)[fld_ind];
	if (!val2)
		return (-1);
	else if (!val1)
		return (1);
	return(asc_dsc * (val1->i - val2->i));
}

int		ft_row_flt_cmp(void *thunk, const void *row1, const void *row2)
{
	t_data	*val1, *val2;
	int		fld_ind, asc_dsc;

	asc_dsc = (*(int*)thunk > 0 ? 1 : -1);
	fld_ind = (*(int*)thunk) * asc_dsc - 1;

	val1 = (*(t_data***)row1)[fld_ind];
	val2 = (*(t_data***)row2)[fld_ind];
	if (!val2)
		return (-1);
	else if (!val1)
		return (1);
	return(asc_dsc * (val1->f - val2->f));
}

int		ft_sort(char *buffer)
{
	t_table tab;
	char	**args;

	tab.name = ft_get_outer_str(buffer);
	if (!tab.name)
		return (ft_db_error(2, ""));
	if (ft_deserialize_tab(tab.name, &tab))
		return(-1);
	args = ft_get_args(buffer);
	if (!args || *(args[0]) == '\0')
		return (ft_db_error(2, ""));
	ft_order_tab(args, &tab);
	ft_serialize_tab(tab);
	ft_free_tab(tab);
	ft_arrdel2(args);
	return (0);
}
