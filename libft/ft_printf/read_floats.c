/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_floats.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 18:56:11 by dfinnis           #+#    #+#             */
/*   Updated: 2018/12/18 18:09:52 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_double(t_print *all, va_list ap)
{
	long double	num;
	char		*num_str;

	num = (long double)va_arg(ap, double);
	num_str = ft_itoa_double(num, all);
	num_str = ft_precision_float(num_str, all);
	ft_justify(num_str, all);
}

void		ft_long_double(t_print *all, va_list ap)
{
	long double	num;
	char		*num_str;

	num = va_arg(ap, long double);
	num_str = ft_itoa_double(num, all);
	num_str = ft_precision_float(num_str, all);
	ft_justify(num_str, all);
}

void		ft_float_type(t_print *all, va_list ap)
{
	if (all->up_l)
		ft_long_double(all, ap);
	else
		ft_double(all, ap);
}
