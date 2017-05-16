/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_specifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 20:54:23 by biremong          #+#    #+#             */
/*   Updated: 2017/02/18 20:26:35 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_prefix(t_spec *spec, int *is_neg)
{
	if (*spec->str == '-')
	{
		write(1, "-", 1);
		*is_neg = 1;
		return ;
	}
	*is_neg = 0;
	if (spec->plus)
		write(1, "+", 1);
	else if (spec->space)
		write(1, " ", 1);
	if (spec->octo && ft_tolower(spec->c) == 'o')
		write(1, "0", 1);
	else if (spec->octo && spec->c == 'b')
		write(1, "0b", 2);
	else if (spec->octo && spec->c == 'X')
		write(1, "0X", 2);
	else if (spec->octo)
		write(1, "0x", 2);
}

int		ft_get_lens(t_spec *spec, int *pad_len, int *prec_len, int *comma_cnt)
{
	int len;

	len = ft_strlen(spec->str);
	if (ft_tolower(spec->c) == 'c' && *spec->str == '\0')
		len++;
	if (spec->precision - len + (*spec->str == '-') > 0)
		*prec_len = spec->precision - len + (*spec->str == '-');
	else
		*prec_len = 0;
	len += *prec_len;
	*comma_cnt = spec->comma ? (len - 1 - (*spec->str == '-')) / 3 : 0;
	len += *comma_cnt;
	if (ft_tolower(spec->c) == 'o' && spec->octo)
		len++;
	else if (spec->octo)
		len += 2;
	if ((spec->space || spec->plus) && ft_isdigit(*spec->str))
		len++;
	*pad_len = (spec->min_width > len ? spec->min_width - len : 0);
	return ((spec->min_width > len ? spec->min_width : len));
}

void	ft_put_comma_str(char *str, int prec_len, int comma_cnt)
{
	int len;
	int	front_digits;
	int other_digits;

	len = ft_strlen(str) + prec_len;
	front_digits = (len % 3 ? len % 3 : 3);
	other_digits = (comma_cnt * 3) + comma_cnt;
	while (front_digits--)
	{
		if (prec_len && prec_len--)
			write(1, "0", 1);
		else
			write(1, str++, 1);
	}
	while (other_digits)
	{
		if (other_digits % 4 == 0)
			write(1, ",", 1);
		else if (prec_len && prec_len--)
			write(1, "0", 1);
		else
			write(1, str++, 1);
		other_digits--;
	}
}
