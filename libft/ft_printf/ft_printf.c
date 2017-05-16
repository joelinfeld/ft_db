/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 15:15:14 by biremong          #+#    #+#             */
/*   Updated: 2017/02/18 20:24:05 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	t_spec	spec;
	int		char_count;

	va_start(ap, format);
	char_count = 0;
	while (*format)
	{
		while (*format && *format != '%')
		{
			write(1, format++, 1);
			char_count++;
		}
		if (!*format)
			break ;
		ft_parse_spec(&spec, (char **)&format, ap, char_count);
		if (spec.c == 'n')
			continue ;
		char_count += ft_print_spec(&spec);
		free(spec.str);
	}
	va_end(ap);
	return (char_count);
}

void	ft_parse_spec(t_spec *spec, char **format, va_list ap, int cc)
{
	*spec = (t_spec){0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0};
	(*format)++;
	while (1)
	{
		if (ft_is_flag(**format))
			ft_handle_flags(spec, format);
		else if (ft_isdigit(**format) || **format == '*')
			ft_handle_min_width(spec, format, ap);
		else if (**format == '.')
			ft_handle_precision(spec, format, ap);
		else if (ft_is_modifier(**format))
			ft_handle_modifier(spec, format);
		else
		{
			spec->c = **format;
			if (**format)
				(*format)++;
			ft_get_arg_str(spec, ap, cc);
			ft_handle_overrides(spec, spec->c);
			break ;
		}
	}
}

void	ft_get_arg_str(t_spec *spec, va_list ap, int cc)
{
	char	c;
	int		mod;

	c = spec->c;
	mod = spec->mod;
	if (ft_tolower(c) == 'd' || c == 'i')
		ft_get_di_str(spec, ap, c, mod);
	else if (ft_is_diouxb(c))
		ft_get_ouxb_str(spec, ap, c, mod);
	else if (ft_tolower(c) == 'c')
		ft_get_c_str(spec, ap, c, mod);
	else if (ft_tolower(c) == 's')
		ft_get_s_str(spec, ap, c, mod);
	else if (c == 'p')
		spec->str = ft_itoa_base((uintmax_t)va_arg(ap, void*), 16, 0);
	else if (c == '%')
		spec->str = ft_strdup("%");
	else if (c == 'n')
		ft_set_n_val(ap, mod, cc);
	else
		spec->str = ft_memset(ft_strnew(1), spec->c, 1);
}

int		ft_print_spec(t_spec *spec)
{
	int		pad_len;
	int		prec_len;
	int		comma_count;
	int		total;
	int		is_neg;

	total = ft_get_lens(spec, &pad_len, &prec_len, &comma_count);
	if (spec->zero)
		ft_print_prefix(spec, &is_neg);
	while (!spec->minus && pad_len--)
		write(1, (spec->zero ? "0" : " "), 1);
	if (!spec->zero)
		ft_print_prefix(spec, &is_neg);
	while (!spec->comma && prec_len--)
		write(1, "0", 1);
	if (spec->comma)
		ft_put_comma_str(spec->str + is_neg, prec_len, comma_count);
	else
		ft_putstr(spec->str + is_neg);
	if (ft_tolower(spec->c) == 'c' && !(*spec->str))
		write(1, spec->str, 1);
	while (pad_len-- > 0)
		write(1, " ", 1);
	return (total);
}
