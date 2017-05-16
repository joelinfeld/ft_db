/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_multibyte.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 15:28:40 by biremong          #+#    #+#             */
/*   Updated: 2017/02/16 01:23:18 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_to_multibyte(wchar_t *wc_str, int prec)
{
	char	*mb_str;
	int		byte_count;
	int		byte_total;
	int		i;
	int		j;

	if (!wc_str)
		return (NULL);
	byte_total = 0;
	i = -1;
	while (wc_str[++i])
	{
		byte_count = ft_get_mb_len(wc_str[i]);
		if (prec == -1 || byte_total + byte_count <= prec)
			byte_total += ft_get_mb_len(wc_str[i]);
	}
	if (!(mb_str = (char*)malloc(byte_total + 1)))
		ft_crash();
	ft_memset(mb_str, 128, byte_total);
	mb_str[byte_total] = 0;
	i = -1;
	j = 0;
	while (wc_str[++i] && j != byte_total)
		ft_encode_wc(wc_str[i], mb_str, &j);
	return (mb_str);
}

void	ft_encode_wc(wchar_t wc, char *mb_str, int *j)
{
	int byte_count;

	byte_count = ft_get_mb_len(wc);
	if (byte_count == 1)
	{
		mb_str[*j] = (unsigned char)wc;
		(*j)++;
		return ;
	}
	else if (byte_count == 2)
		mb_str[*j] = 192;
	else if (byte_count == 3)
		mb_str[*j] = 224;
	else if (byte_count == 4)
		mb_str[*j] = 240;
	else if (byte_count == 5)
		mb_str[*j] = 248;
	else
		mb_str[*j] = 252;
	while (byte_count--)
	{
		mb_str[*j] |= (unsigned char)((wc >> byte_count * 6) & 63);
		(*j)++;
	}
}

int		ft_get_mb_len(wchar_t wc)
{
	if (wc < 0x00000080)
		return (1);
	else if (wc < 0x00000800)
		return (2);
	else if (wc < 0x00010000)
		return (3);
	else if (wc < 0x00200000)
		return (4);
	else if (wc < 0x04000000)
		return (5);
	else
		return (6);
}
