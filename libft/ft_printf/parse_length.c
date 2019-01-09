/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_length.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 14:01:14 by dfinnis           #+#    #+#             */
/*   Updated: 2018/12/17 14:01:16 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_islength(char c)
{
	return (c == 'h' || c == 'j' || c == 'l' || c == 'L' || c == 'z');
}

void	ft_hh(t_print *all)
{
	all->hh = 1;
	all->len++;
}

void	ft_ll(t_print *all)
{
	all->ll = 1;
	all->len++;
}

void	ft_parse_length(t_print *all)
{
	if (ft_islength(all->form[all->len]))
	{
		if (all->form[all->len] == 'h')
		{
			if (all->form[all->len + 1] == 'h')
				ft_hh(all);
			else
				all->h = 1;
		}
		if (all->form[all->len] == 'j')
			all->j = 1;
		if (all->form[all->len] == 'l')
		{
			if (all->form[all->len + 1] == 'l')
				ft_ll(all);
			else
				all->l = 1;
		}
		if (all->form[all->len] == 'L')
			all->up_l = 1;
		if (all->form[all->len] == 'z')
			all->z = 1;
		all->len++;
	}
}
