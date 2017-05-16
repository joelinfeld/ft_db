/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 10:30:12 by biremong          #+#    #+#             */
/*   Updated: 2017/01/31 14:49:53 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_digits(uintmax_t myn)
{
	int digits;

	digits = 1;
	while (myn /= 10)
		digits++;
	return (digits);
}

char		*ft_itoa(intmax_t n)
{
	char		*array;
	int			digits;
	int			is_neg;
	uintmax_t	myn;

	is_neg = n < 0 ? 1 : 0;
	myn = n < 0 ? -n : n;
	digits = ft_get_digits(myn);
	array = (char*)malloc(sizeof(char) * (digits + is_neg + 1));
	if (!array)
		return (NULL);
	array[digits + is_neg] = '\0';
	while (digits)
	{
		array[digits + is_neg - 1] = '0' + (myn % 10);
		myn /= 10;
		digits--;
	}
	if (is_neg)
		array[0] = '-';
	return (array);
}
