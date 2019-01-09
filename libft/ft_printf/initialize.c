/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 09:27:39 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/06 15:05:48 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_initialize_print(t_print *all)
{
	all->printed = 0;
	all->len = 0;
	all->form = NULL;
	ft_reinitialize(all);
}

void	ft_reinitialize(t_print *all)
{
	all->type = '0';
	all->hh = 0;
	all->h = 0;
	all->j = 0;
	all->ll = 0;
	all->l = 0;
	all->up_l = 0;
	all->z = 0;
	all->hash = 0;
	all->zero = 0;
	all->minus = 0;
	all->plus = 0;
	all->space = 0;
	all->width = 0;
	all->prec = 0;
	all->prec_set = 0;
	all->sign = 0;
	all->hex_o_zero = 0;
	all->num_zero = 0;
	all->char_zero = 0;
	all->print_negative = 0;
	all->print_plus = 0;
	all->wild_width = 0;
	all->wild_prec = 0;
}
