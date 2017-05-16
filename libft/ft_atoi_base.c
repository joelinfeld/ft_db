/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:13:31 by biremong          #+#    #+#             */
/*   Updated: 2017/01/27 15:47:58 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_valid_digit(int base, char c)
{
	if (base >= 2 && base <= 10)
	{
		if (c >= '0' && c <= '0' + base - 1)
			return (1);
	}
	else if (base >= 11 && base <= 16)
	{
		if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'a' + base - 11)
			|| (c >= 'A' && c <= 'A' + base - 11))
			return (1);
	}
	return (0);
}

static int	get_value(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else
		return (c - 'A' + 10);
}

int			ft_atoi_base(int base, char *str)
{
	int i;
	int result;
	int sign;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	sign = 1;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	result = 0;
	while (is_valid_digit(base, str[i]))
	{
		result *= base;
		result += get_value(str[i]);
		i++;
	}
	return (result * sign);
}
