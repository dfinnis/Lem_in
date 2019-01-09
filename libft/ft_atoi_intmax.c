/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_intmax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 17:15:52 by dfinnis           #+#    #+#             */
/*   Updated: 2018/12/26 17:15:53 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

intmax_t	ft_atoi_intmax(const char *str)
{
	intmax_t	a;
	int			i;
	int			n;

	a = 0;
	i = 0;
	n = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'\
	|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n = -1;
		i++;
	}
	if (str[i] < '0' || str[i] > '9')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		a = (a * 10) + (str[i++] - '0');
	return (a * n);
}
