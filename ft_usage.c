/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 19:36:52 by biremong          #+#    #+#             */
/*   Updated: 2017/05/05 20:37:46 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	ft_usage(void)
{
	ft_printf("\x1b[38;2;115;190;255mUsage:\n");
	ft_printf("  CREATE TABLE table_name(field1 type1, field2 type2, ...)\n");
	ft_printf("  DELETE TABLE table_name()\n");
	ft_printf("  INSERT ROWS  table_name(field1, field2, ...)\n");
	ft_printf("  DELETE ROWS  table_name() WHERE (cond1, ...)\n");
	ft_printf("  INSERT COLS  table_name(field1 type1, field2 type2,...)\n");
	ft_printf("  DELETE COLS  table_name(field1, field2, ...)\n");
	ft_printf("  UPDATE       table_name(field1, field2, ...) WHERE (cond1, ...)\n");
	ft_printf("  SELECT       table_name(field1, field2, ...) WHERE (cond1, ...) ORDER BY (field1 asc/dsc)\n");
	ft_printf("  SORT         table_name(field1 asc/dsc)\n");
	ft_printf("  QUIT/EXIT\n");
	ft_printf("  HELP/USAGE\n");
	ft_printf("\x1b[0m");
}
