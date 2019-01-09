/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags_width.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 14:00:50 by dfinnis           #+#    #+#             */
/*   Updated: 2018/12/17 14:00:52 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_isflag(char c)
{
	if (c == '+' || c == '-' || c == ' ' || c == '0' || c == '#')
		return (1);
	return (0);
}

void	ft_parse_flags(t_print *all)
{
	while (ft_isflag(all->form[all->len]))
	{
		if (all->form[all->len] == '+')
			all->plus = 1;
		if (all->form[all->len] == '-')
			all->minus = 1;
		if (all->form[all->len] == ' ')
			all->space = 1;
		if (all->form[all->len] == '0')
			all->zero = 1;
		if (all->form[all->len] == '#')
			all->hash = 1;
		all->len++;
	}
}

void	ft_wild_width(t_print *all, va_list ap)
{
	all->width = va_arg(ap, int);
	if (all->width < 0)
	{
		all->width *= -1;
		all->minus = 1;
	}
	if (all->width)
		all->wild_width = 1;
	all->len++;
}

void	ft_parse_width(t_print *all, va_list ap)
{
	unsigned int	n;
	unsigned int	count;
	unsigned int	multi;

	multi = 1;
	n = all->len;
	while (ft_isdigit(all->form[n]))
		n++;
	count = n - all->len;
	if (all->form[n] == '*')
		ft_wild_width(all, ap);
	else
	{
		if (all->wild_width)
			all->width = 0;
		while (n-- > all->len)
		{
			all->width = all->width + (all->form[n] - 48) * multi;
			multi *= 10;
		}
	}
	all->len += count;
}
