/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 22:08:00 by biremong          #+#    #+#             */
/*   Updated: 2017/02/13 22:11:09 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_power(int base, unsigned int exp)
{
	long long	result;

	result = 1;
	while (exp)
	{
		result *= base;
		exp--;
	}
	return (result);
}
