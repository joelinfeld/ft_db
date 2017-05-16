/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 15:15:14 by biremong          #+#    #+#             */
/*   Updated: 2017/02/18 20:26:51 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_set_n_val(va_list ap, int mod, int cc)
{
	if (mod == 1)
		*va_arg(ap, char*) = (char)cc;
	else if (mod == 2)
		*va_arg(ap, short*) = (short)cc;
	else if (mod == 3)
		*va_arg(ap, long*) = cc;
	else if (mod == 4)
		*va_arg(ap, long long*) = cc;
	else if (mod == 5)
		*va_arg(ap, intmax_t*) = cc;
	else if (mod == 6)
		*va_arg(ap, size_t*) = cc;
	else
		*va_arg(ap, int*) = cc;
}

void	ft_get_di_str(t_spec *spec, va_list ap, char c, int mod)
{
	if (mod == 3 || c == 'D')
		spec->str = ft_itoa(va_arg(ap, long));
	else if (mod == 4)
		spec->str = ft_itoa(va_arg(ap, long long));
	else if (mod == 1)
		spec->str = ft_itoa((char)va_arg(ap, int));
	else if (mod == 2)
		spec->str = ft_itoa((short)va_arg(ap, int));
	else if (mod == 5)
		spec->str = ft_itoa(va_arg(ap, intmax_t));
	else if (mod == 6)
		spec->str = ft_itoa(ft_get_signed_size_t(ap));
	else
		spec->str = ft_itoa(va_arg(ap, int));
}

void	ft_get_ouxb_str(t_spec *spec, va_list ap, char c, int mod)
{
	uintmax_t int_arg;

	if (mod == 3 || c == 'O' || c == 'U')
		int_arg = va_arg(ap, unsigned long);
	else if (mod == 4)
		int_arg = va_arg(ap, unsigned long long);
	else if (mod == 1)
		int_arg = (unsigned char)va_arg(ap, int);
	else if (mod == 2)
		int_arg = (unsigned short)va_arg(ap, int);
	else if (mod == 5)
		int_arg = va_arg(ap, uintmax_t);
	else if (mod == 6)
		int_arg = va_arg(ap, size_t);
	else
		int_arg = va_arg(ap, unsigned int);
	if (ft_tolower(c) == 'u')
		spec->str = ft_itoa_base(int_arg, 10, 0);
	else if (ft_tolower(c) == 'o')
		spec->str = ft_itoa_base(int_arg, 8, 0);
	else if (spec->c == 'b')
		spec->str = ft_itoa_base(int_arg, 2, 0);
	else
		spec->str = ft_itoa_base(int_arg, 16, (c == 'X'));
}

void	ft_get_c_str(t_spec *spec, va_list ap, char c, int mod)
{
	wchar_t	*temp_wc_str;

	if ((mod >= 3 || c == 'C') && MB_CUR_MAX > 1)
	{
		if (!(temp_wc_str = (wchar_t *)malloc(sizeof(wchar_t) * 2)))
			ft_crash();
		temp_wc_str[0] = va_arg(ap, wchar_t);
		temp_wc_str[1] = 0;
		spec->str = ft_to_multibyte(temp_wc_str, spec->precision);
		free(temp_wc_str);
	}
	else
		spec->str = ft_memset(ft_strnew(1), (unsigned char)va_arg(ap, int), 1);
}

void	ft_get_s_str(t_spec *spec, va_list ap, char c, int mod)
{
	if (mod >= 3 || c == 'S')
		spec->str = ft_to_multibyte(va_arg(ap, wchar_t*), spec->precision);
	else
		spec->str = ft_strdup(va_arg(ap, char*));
	if (!spec->str)
		spec->str = ft_strdup("(null)");
}
