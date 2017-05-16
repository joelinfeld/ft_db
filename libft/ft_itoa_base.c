/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 09:04:09 by exam              #+#    #+#             */
/*   Updated: 2017/01/31 15:32:57 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_digits(uintmax_t n, int base)
{
	int	digits;

	digits = 1;
	while (n /= base)
		digits++;
	return (digits);
}

char		*ft_itoa_base(uintmax_t n, int base, int upper_flag)
{
	char	*array;
	int		digits;
	char	symbols[16];
	int		i;

	i = -1;
	while (++i < 16)
	{
		if (i < 10)
			symbols[i] = '0' + i;
		else
			symbols[i] = (upper_flag ? 'A' + i - 10 : 'a' + i - 10);
	}
	digits = get_digits(n, base);
	if (!(array = (char*)ft_memalloc(sizeof(char) * (digits + 1))))
		ft_crash();
	if (n == 0)
		array[0] = '0';
	while (n)
	{
		array[digits - 1] = symbols[n % base];
		n /= base;
		digits--;
	}
	return (array);
}
