/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_numbers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 14:54:39 by dfinnis           #+#    #+#             */
/*   Updated: 2018/12/17 14:54:45 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_int(t_print *all, va_list ap)
{
	intmax_t	num;
	char		*num_str;

	num = ft_int_len(all, ap);
	if (num < -9223372036854775807)
		all->sign = 1;
	else if (num < 0)
	{
		all->sign = 1;
		num = -num;
	}
	if ((all->type == 'd' || all->type == 'i')
		&& !all->prec && all->prec_set && num == 0)
		num_str = ft_strdup_empty(all->form);
	else
	{
		if (!(num_str = ft_itoa_intmax(num)))
			ft_error(NULL, all->form);
	}
	ft_justify(num_str, all);
}

void		ft_unsigned(t_print *all, va_list ap)
{
	uintmax_t	num;
	char		*num_str;

	num = ft_unsigned_len(all, ap);
	if (num == 0)
		all->num_zero = 1;
	if (all->type == 'u' && !all->prec && all->prec_set && num == 0)
		num_str = ft_strdup_empty(all->form);
	else
	{
		if (!(num_str = ft_itoa_unsigned(num)))
			ft_error(NULL, all->form);
	}
	ft_justify(num_str, all);
}

void		ft_int_octal(t_print *all, va_list ap)
{
	uintmax_t	num;
	char		*num_str;

	num = ft_unsigned_len(all, ap);
	if (num == 0)
		all->num_zero = 1;
	if (!all->hex_o_zero || all->hash || !all->num_zero)
	{
		if (!(num_str = ft_itoa_base(num, 8, all->type)))
			ft_error(NULL, all->form);
	}
	else
		num_str = ft_strdup_empty(all->form);
	if (all->hash && all->prec && (!all->num_zero || all->width))
		all->prec--;
	ft_justify(num_str, all);
}

void		ft_int_hex(t_print *all, va_list ap)
{
	uintmax_t	num;
	char		*num_str;

	num = ft_unsigned_len(all, ap);
	if (num == 0)
		all->num_zero = 1;
	if (!all->hex_o_zero || !all->num_zero)
	{
		if (!(num_str = ft_itoa_base(num, 16, all->type)))
			ft_error(NULL, all->form);
	}
	else
		num_str = ft_strdup_empty(all->form);
	ft_justify(num_str, all);
}

void		ft_number(t_print *all, va_list ap)
{
	if (all->type == 'i' || all->type == 'd')
		ft_int(all, ap);
	else if (all->type == 'u')
		ft_unsigned(all, ap);
	else if (all->type == 'o')
		ft_int_octal(all, ap);
	else if (all->type == 'x' || all->type == 'X')
		ft_int_hex(all, ap);
}
