/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_others.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 14:54:54 by dfinnis           #+#    #+#             */
/*   Updated: 2018/12/17 19:40:13 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	ft_int_len(t_print *all, va_list ap)
{
	intmax_t	num;

	if (all->z)
		num = (intmax_t)va_arg(ap, size_t);
	else if (all->j)
		num = va_arg(ap, intmax_t);
	else if (all->l)
		num = (intmax_t)va_arg(ap, long);
	else if (all->ll)
		num = (intmax_t)va_arg(ap, long long);
	else if (all->h)
		num = (intmax_t)(short)va_arg(ap, int);
	else if (all->hh)
		num = (intmax_t)(signed char)va_arg(ap, int);
	else
		num = va_arg(ap, int);
	return (num);
}

uintmax_t	ft_unsigned_len(t_print *all, va_list ap)
{
	uintmax_t	num;

	if (all->j || all->z)
		num = va_arg(ap, uintmax_t);
	else if (all->l)
		num = (uintmax_t)va_arg(ap, unsigned long);
	else if (all->ll)
		num = (uintmax_t)va_arg(ap, unsigned long long);
	else if (all->h)
		num = (uintmax_t)(unsigned short)va_arg(ap, unsigned int);
	else if (all->hh)
		num = (uintmax_t)(unsigned char)va_arg(ap, unsigned int);
	else
		num = (uintmax_t)va_arg(ap, unsigned int);
	return (num);
}

void		ft_string(t_print *all, va_list ap)
{
	char	*str;

	str = NULL;
	if (!(str = va_arg(ap, char*)))
	{
		if (all->prec_set && !all->prec)
			str = ft_strdup_empty(all->form);
		else
		{
			if (!(str = ft_strdup("(null)")))
				ft_error(NULL, all->form);
		}
	}
	else if (all->prec_set && !all->prec)
		str = ft_strdup_empty(all->form);
	else if (!(str = ft_strdup(str)))
		ft_error(NULL, all->form);
	ft_justify(str, all);
}

void		ft_char(t_print *all, va_list ap)
{
	char	c;
	char	*str;

	if (all->type == '%')
		c = '%';
	else
		c = (char)va_arg(ap, int);
	if (!(str = malloc(sizeof(char) * 2)))
		ft_error(NULL, all->form);
	if (c == '\0')
		all->char_zero = 1;
	str[0] = c;
	str[1] = '\0';
	ft_justify(str, all);
}

void		ft_pointer(t_print *all, va_list ap)
{
	uintmax_t	num;
	char		*num_str;

	num = (uintmax_t)va_arg(ap, void*);
	if (all->type == 'p' && all->prec_set && !all->prec && num == 0)
		num_str = ft_strdup_empty(all->form);
	else
	{
		if (!(num_str = ft_itoa_base(num, 16, 'x')))
			ft_error(NULL, all->form);
	}
	if (num == 0)
		all->num_zero = 1;
	if (!all->prec || all->num_zero)
		num_str = ft_strjoinfree_s2_error("0x", num_str, all->form);
	ft_justify(num_str, all);
}
