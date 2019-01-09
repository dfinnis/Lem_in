/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_prefix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:08:40 by dfinnis           #+#    #+#             */
/*   Updated: 2018/12/17 16:08:46 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_negative(char *num_str, t_print *all)
{
	if (all->sign && !all->print_negative)
		num_str = ft_strjoinfree_s2_error("-", num_str, all->form);
	all->print_negative = 1;
	return (num_str);
}

int			ft_0x_condition(t_print *all)
{
	return (!all->print_plus && all->hash &&
		((!all->hex_o_zero && !all->num_zero) ||
		(all->width && all->prec_set && !all->prec && !all->num_zero)));
}

int			ft_o_condition(t_print *all)
{
	return (!all->print_plus && all->hash && (((!all->hex_o_zero &&
		!all->num_zero) || (all->width && all->prec)) ||
		(!all->prec && all->prec_set && !all->num_zero)));
}

char		*ft_build_prefix(char *num_str, t_print *all)
{
	if ((all->type == 'i' || all->type == 'd') &&
		!all->print_plus && !all->sign)
	{
		if (all->plus)
			num_str = ft_strjoinfree_s2_error("+", num_str, all->form);
		else if (all->space && !all->plus)
			num_str = ft_strjoinfree_s2_error(" ", num_str, all->form);
	}
	else if (all->type == 'x' && ft_0x_condition(all))
		num_str = ft_strjoinfree_s2_error("0x", num_str, all->form);
	else if (all->type == 'X' && ft_0x_condition(all))
		num_str = ft_strjoinfree_s2_error("0X", num_str, all->form);
	else if (all->type == 'o' && ft_o_condition(all))
		num_str = ft_strjoinfree_s2_error("0", num_str, all->form);
	all->print_plus = 1;
	return (num_str);
}
