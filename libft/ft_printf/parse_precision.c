/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 14:01:02 by dfinnis           #+#    #+#             */
/*   Updated: 2018/12/17 14:01:04 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_wild_prec(t_print *all, va_list ap)
{
	all->prec = va_arg(ap, int);
	all->wild_prec = 1;
	all->len++;
}

void	ft_read_prec(t_print *all, unsigned int n)
{
	unsigned int	multi;

	multi = 1;
	while (n-- > all->len)
	{
		all->prec = all->prec + (all->form[n] - 48) * multi;
		multi *= 10;
	}
}

void	ft_parse_precision(t_print *all, va_list ap)
{
	unsigned int	n;
	unsigned int	count;

	if (all->form[all->len] == '.')
	{
		all->len++;
		all->prec_set = 1;
		all->prec = 0;
	}
	else
		return ;
	n = all->len;
	while (ft_isdigit(all->form[n]))
		n++;
	count = n - all->len;
	if (all->form[n] == '*')
		ft_wild_prec(all, ap);
	if (!all->wild_prec)
		ft_read_prec(all, n);
	all->len += count;
}
