/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fld_inds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 16:55:15 by jinfeld           #+#    #+#             */
/*   Updated: 2017/05/05 16:52:43 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		*ft_get_fld_inds(char **fld_args, int *arg_cnt, t_table tab)
{
	int 	*fld_inds;
	int 	i, j;

	*arg_cnt = ft_arrlen2(fld_args);
	if (*arg_cnt == 1 && ft_strequ(fld_args[0], "*"))
		fld_inds = ft_all_fld_inds(tab.col_cnt, arg_cnt);
	else
	{
		fld_inds = (int*)ft_malloc(sizeof(int) * *arg_cnt);
		i = -1;
		while (++i < *arg_cnt)
		{
			j = -1;
			while (++j < tab.col_cnt)
				if (ft_strequ(fld_args[i], tab.flds[j].name))
				{
					fld_inds[i] = j;
					break ;
				}
			if (j == tab.col_cnt)
			{
				free(fld_inds);
				return (ft_no_fld_match(fld_inds, fld_args[i]));
			}
		}
	}
	return (fld_inds);
}

int		ft_get_fld_ind(char *fld, t_table tab)
{
	int i;

	i = -1;
	while (++i < tab.col_cnt)
		if (ft_strequ(tab.flds[i].name, fld))
			return (i);
	ft_db_error(5, fld);
	return (-1);
}

int		*ft_all_fld_inds(int col_cnt, int *fld_cnt)
{
	int *fld_inds;
	int i;

	fld_inds = (int*)ft_malloc(sizeof(int) * col_cnt);
	i = -1;
	while (++i < col_cnt)
		fld_inds[i] = i;
	*fld_cnt = col_cnt;
	return (fld_inds);
}

void	*ft_no_fld_match(int *inds, char *fld_name)
{
	ft_db_error(5, fld_name);
	free(inds);
	return (NULL);
}
