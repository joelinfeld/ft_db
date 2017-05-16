/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 15:15:14 by biremong          #+#    #+#             */
/*   Updated: 2017/02/18 20:26:33 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_handle_modifier(t_spec *spec, char **format)
{
	if (**format == 'h' && *(*format + 1) == 'h' && spec->mod < 1)
		spec->mod = 1;
	else if (**format == 'l' && *(*format + 1) == 'l' && spec->mod < 4)
		spec->mod = 4;
	else if (**format == 'h' && spec->mod < 2)
		spec->mod = 2;
	else if (**format == 'l' && spec->mod < 3)
		spec->mod = 3;
	else if (**format == 'j' && spec->mod < 5)
		spec->mod = 5;
	else if (**format == 'z')
		spec->mod = 6;
	*format += (spec->mod == 1 || spec->mod == 4 ? 2 : 1);
}

void	ft_handle_precision(t_spec *spec, char **format, va_list ap)
{
	long wildcard;

	(*format)++;
	spec->precision = 0;
	if (**format == '*')
	{
		wildcard = va_arg(ap, int);
		spec->precision = (wildcard < 0 ? -1 : wildcard);
		(*format)++;
		return ;
	}
	while (ft_isdigit(**format))
	{
		spec->precision *= 10;
		spec->precision += **format - '0';
		(*format)++;
	}
}

void	ft_handle_min_width(t_spec *spec, char **format, va_list ap)
{
	long wildcard;

	spec->min_width = 0;
	while (ft_isdigit(**format) || **format == '*')
	{
		spec->min_width *= 10;
		spec->min_width += **format - '0';
		if (**format == '*')
		{
			wildcard = va_arg(ap, int);
			if (wildcard < 0)
				spec->minus = 1;
			spec->min_width = (wildcard < 0 ? -wildcard : wildcard);
			if (ft_isdigit(*(*format + 1)))
				spec->min_width = 0;
		}
		(*format)++;
	}
}

void	ft_handle_flags(t_spec *spec, char **format)
{
	while (1)
	{
		if (**format == '+')
			spec->plus = 1;
		else if (**format == '-')
			spec->minus = 1;
		else if (**format == '#')
			spec->octo = 1;
		else if (**format == ' ')
			spec->space = 1;
		else if (**format == '0')
			spec->zero = 1;
		else if (**format == '\'')
			spec->comma = 1;
		else
			return ;
		(*format)++;
	}
}

int		ft_is_flag(char c)
{
	if (c == '+' || c == '-' || c == '#' || c == ' ' || c == '0' || c == '\'')
		return (1);
	return (0);
}
