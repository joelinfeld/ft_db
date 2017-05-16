/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 11:04:01 by biremong          #+#    #+#             */
/*   Updated: 2016/12/02 15:00:30 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	long myn;

	myn = (long)n;
	if (myn < 0)
	{
		write(1, "-", 1);
		myn = -myn;
	}
	if (myn < 10)
		ft_putchar('0' + myn);
	if (myn >= 10)
	{
		ft_putnbr(myn / 10);
		ft_putnbr(myn % 10);
	}
}
