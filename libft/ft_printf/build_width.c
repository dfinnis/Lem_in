/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 15:20:13 by dfinnis           #+#    #+#             */
/*   Updated: 2018/12/18 11:03:09 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_is_unsigned(t_print *all)
{
	return (all->type == 'u' || all->type == 'U' || all->type == 'x' ||
		all->type == 'X' || all->type == 'o');
}

int			ft_is_unsigned_wo(t_print *all)
{
	return (all->type == 'u' || all->type == 'U' ||
		(all->type == 'o' && all->zero && all->num_zero) ||
		(all->type == 'x' && all->plus));
}

void		ft_calc_width(t_print *all)
{
	if ((all->sign || (((all->hash && !ft_is_unsigned_wo(all)) ||
		((all->plus || all->space) && (!ft_is_unsigned(all)))) &&
		(all->minus || all->zero)) || all->type == '%') && all->type != 's')
	{
		if (all->hash && all->type != '%' &&
			!(all->type == 'o' || all->type == 'd' || all->type == 'i'))
			all->width--;
		all->width--;
	}
	else if (all->type == 'o' &&
		all->minus && all->width && all->prec && all->num_zero)
		all->width--;
	if ((all->type == 'x' || all->type == 'X') && all->zero && all->width
		&& all->hash && (all->h || all->prec_set || all->num_zero))
		all->width += 2;
	if ((all->type == 'o' && all->hash && all->width && all->prec_set &&
		!all->num_zero && all->zero) || (all->type == '%' && all->width))
		all->width++;
}

char		*ft_build_width(t_print *all, char c)
{
	char	*str;
	int		i;

	i = 0;
	if ((all->type == 'u' || all->type == 'o' || all->type == 'x' ||
		all->type == 'X') && all->prec_set && all->width)
		c = ' ';
	if (!(str = (char*)malloc(sizeof(char) * (all->width + 1))))
		ft_error(NULL, all->form);
	while (i < all->width)
		str[i++] = c;
	str[i] = '\0';
	return (str);
}

char		*ft_fill_width(char *num_str, t_print *all, char c)
{
	int		i;
	char	*str;

	str = NULL;
	if ((i = ft_strlen(num_str)) < all->width)
	{
		if (all->sign && !all->minus && !all->zero)
			num_str = ft_negative(num_str, all);
		ft_calc_width(all);
		all->width = all->width - i;
		str = ft_build_width(all, c);
		if (all->minus || (all->type == 'p' && all->zero))
			num_str = ft_strjoinfree_error(num_str, str, all->form);
		else
			num_str = ft_strjoinfree_error(str, num_str, all->form);
	}
	else if (all->type == 'f')
		num_str = ft_negative(num_str, all);
	return (num_str);
}
