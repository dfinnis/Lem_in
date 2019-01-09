/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 13:57:46 by dfinnis           #+#    #+#             */
/*   Updated: 2018/12/18 18:14:44 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_parse(t_print *all, va_list ap)
{
	while (all->form[all->len] &&
		ft_strchr("+- #0123456789.hlLjz*", all->form[all->len]))
	{
		ft_parse_flags(all);
		ft_parse_width(all, ap);
		ft_parse_precision(all, ap);
		ft_parse_length(all);
	}
	ft_parse_type(all);
	ft_update_conflicts(all);
}

void	ft_read(t_print *all, va_list ap)
{
	if (all->type == 'i' || all->type == 'd' || all->type == 'u' ||
			all->type == 'o' || all->type == 'x' || all->type == 'X')
		ft_number(all, ap);
	else if (all->type == 's')
		ft_string(all, ap);
	else if (all->type == 'c')
		ft_char(all, ap);
	else if (all->type == '%')
		ft_char(all, ap);
	else if (all->type == 'p')
		ft_pointer(all, ap);
	else if (all->type == 'f')
		ft_float_type(all, ap);
	else if (all->type == 'b')
		ft_binary(all, ap);
}

void	ft_justify(char *num_str, t_print *all)
{
	if (all->prec)
		num_str = ft_precision(num_str, all);
	if ((!all->minus && (all->plus || all->hash || all->space) && (!all->zero
		|| all->type == 'o' || ((all->type == 'x' || all->type == 'X') &&
		(!all->zero) && !all->width)) && all->type != 'c') || (all->type == 'x'
		&& all->hash && all->prec_set && all->width && !all->num_zero))
		num_str = ft_build_prefix(num_str, all);
	if (all->type == 'c' && all->char_zero == 1)
		all->width--;
	if (all->width && !all->zero)
		num_str = ft_fill_width(num_str, all, ' ');
	else if (all->width && all->zero)
		num_str = ft_fill_width(num_str, all, '0');
	if ((all->minus || all->zero || all->prec_set || all->prec) &&
		(!all->width || all->zero))
		num_str = ft_negative(num_str, all);
	if ((all->minus && (all->plus || all->hash || all->space)) ||
		(all->zero && all->type != 'o'))
		num_str = ft_build_prefix(num_str, all);
	if (all->sign && !all->print_negative)
		num_str = ft_negative(num_str, all);
	ft_print(num_str, all);
	free(num_str);
}

void	ft_print(char *num_str, t_print *all)
{
	if (all->type == 'c' && all->char_zero == 1)
	{
		if (all->minus)
		{
			ft_putchar('\0');
			ft_putstr(num_str);
		}
		else
		{
			ft_putstr(num_str);
			ft_putchar('\0');
		}
		all->printed++;
	}
	else
		ft_putstr(num_str);
	all->printed = all->printed + ft_strlen(num_str);
}

int		ft_printf(char const *format, ...)
{
	va_list			ap;
	t_print			all;

	va_start(ap, format);
	ft_initialize_print(&all);
	if (!(all.form = ft_strdup(format)))
		ft_error(NULL, all.form);
	while (all.form[all.len] != '\0')
	{
		if (all.form[all.len] == '%')
		{
			all.len++;
			ft_parse(&all, ap);
			ft_read(&all, ap);
			ft_reinitialize(&all);
		}
		else
		{
			ft_putchar(all.form[all.len++]);
			all.printed++;
		}
	}
	free(all.form);
	va_end(ap);
	return (all.printed);
}
