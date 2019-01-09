/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 15:20:24 by dfinnis           #+#    #+#             */
/*   Updated: 2018/12/17 18:36:59 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_prec_a(char *num_str, t_print *all, int i)
{
	char *str;

	str = NULL;
	if (!(str = (char*)malloc(sizeof(char) * (all->prec + 1))))
		ft_error(NULL, all->form);
	all->prec = all->prec - i;
	i = 0;
	while (i < all->prec)
		str[i++] = '0';
	str[i] = '\0';
	num_str = ft_strjoinfree_error(str, num_str, all->form);
	return (num_str);
}

char		*ft_prec_b(char *num_str, t_print *all, int i)
{
	char *str;

	str = NULL;
	if (!(str = (char*)malloc(sizeof(char) * (all->prec + 1))))
		ft_error(NULL, all->form);
	i = 0;
	while (i < all->prec - 1)
		str[i++] = '0';
	str[i] = '\0';
	num_str = ft_strjoinfree_error(num_str, str, all->form);
	return (num_str);
}

char		*ft_prec_c(char *num_str, t_print *all, int i)
{
	int		len;
	char	*str;

	str = NULL;
	if ((size_t)all->prec > ft_strlen(num_str))
	{
		len = ft_strlen(num_str);
		if (!(str = (char*)malloc(sizeof(char) *
			(all->prec - (len + 1)))))
			ft_error(NULL, all->form);
		i = 0;
		while (i < all->prec - len)
			str[i++] = '0';
		str[i] = '\0';
		num_str = ft_strjoinfree_error(str, num_str, all->form);
	}
	num_str = ft_strjoinfree_s2_error("0x", num_str, all->form);
	return (num_str);
}

char		*ft_precision(char *num_str, t_print *all)
{
	int		i;

	if ((i = ft_strlen(num_str)) < all->prec &&
		all->type != 's' && all->type != 'p' && all->type != 'f')
		num_str = ft_prec_a(num_str, all, i);
	else if (all->type == 's' && all->prec)
		num_str[all->prec] = '\0';
	else if (all->type == 'p' && all->prec && all->num_zero)
		num_str = ft_prec_b(num_str, all, i);
	else if (all->type == 'p' && all->prec && !all->num_zero)
		num_str = ft_prec_c(num_str, all, i);
	return (num_str);
}
