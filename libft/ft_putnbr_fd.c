/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 11:24:46 by biremong          #+#    #+#             */
/*   Updated: 2016/12/01 15:18:24 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	myn;

	myn = (long)n;
	if (myn < 0)
	{
		write(fd, "-", 1);
		myn = -myn;
	}
	if (myn < 10)
		ft_putchar_fd('0' + myn, fd);
	if (myn >= 10)
	{
		ft_putnbr_fd(myn / 10, fd);
		ft_putnbr_fd(myn % 10, fd);
	}
}
