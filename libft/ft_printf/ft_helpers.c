/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 15:15:14 by biremong          #+#    #+#             */
/*   Updated: 2017/02/18 20:26:45 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_handle_overrides(t_spec *spec, char c)
{
	if ((spec->precision >= 0 && ft_is_diouxb(c)) || spec->minus)
		spec->zero = 0;
	if (ft_tolower(c) != 'd' && c != 'i')
	{
		spec->space = 0;
		spec->plus = 0;
		spec->comma = (ft_tolower(c) == 'u' ? spec->comma : 0);
	}
	if (spec->plus)
		spec->space = 0;
	if (c == 'p')
		spec->octo = 1;
	if ((ft_tolower(c) != 'o' && ft_tolower(c) != 'x' && c != 'p' && c != 'b')
			|| (ft_strequ(spec->str, "0") && (ft_tolower(c) == 'x'
			|| (ft_tolower(c) == 'o' && !(spec->precision == 0)))))
		spec->octo = 0;
	if (ft_tolower(c) == 'o' && spec->precision > (int)ft_strlen(spec->str))
		spec->octo = 0;
	if (ft_tolower(c) == 's' && spec->precision >= 0 &&
			(int)ft_strlen(spec->str) > spec->precision)
		spec->str[spec->precision] = 0;
	if (ft_tolower(c) == 'c' || ft_tolower(c) == 's' || c == '%')
		spec->precision = -1;
	if (spec->precision == 0 && ft_atoi(spec->str) == 0 && *spec->str == '0')
		spec->str[0] = 0;
}

int			ft_is_diouxb(char c)
{
	if (ft_tolower(c) == 'd')
		return (1);
	else if (c == 'i')
		return (1);
	else if (ft_tolower(c) == 'o')
		return (1);
	else if (ft_tolower(c) == 'u')
		return (1);
	else if (ft_tolower(c) == 'x')
		return (1);
	else if (c == 'b')
		return (1);
	else
		return (0);
}

int			ft_is_modifier(char c)
{
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z')
		return (1);
	return (0);
}

int			ft_is_conversion(char c)
{
	if (\
			c == '%' ||
			c == 'p' ||
			c == 'i' ||
			c == 'b' ||
			c == 'n' ||
			ft_tolower(c) == 'd' ||
			ft_tolower(c) == 'o' ||
			ft_tolower(c) == 'u' ||
			ft_tolower(c) == 'x' ||
			ft_tolower(c) == 's' ||
			ft_tolower(c) == 'c')
		return (1);
	return (0);
}

intmax_t	ft_get_signed_size_t(va_list ap)
{
	if (sizeof(size_t) == sizeof(char))
		return ((char)va_arg(ap, int));
	else if (sizeof(size_t) == sizeof(short))
		return ((short)va_arg(ap, int));
	else if (sizeof(size_t) == sizeof(int))
		return (va_arg(ap, int));
	else if (sizeof(size_t) == sizeof(long))
		return (va_arg(ap, long));
	else if (sizeof(size_t) == sizeof(long long))
		return (va_arg(ap, long long));
	else
		return (va_arg(ap, intmax_t));
}
