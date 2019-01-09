/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 10:02:28 by dfinnis           #+#    #+#             */
/*   Updated: 2018/11/06 10:02:30 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find_len(int nb)
{
	int		neg;
	int		len;
	long	n;

	neg = 0;
	len = 1;
	n = nb;
	if (n < 0)
	{
		neg = 1;
		n *= -1;
	}
	while ((n /= 10) > 0)
		len++;
	return ((neg) ? len + 1 : len);
}

char		*ft_itoa(int n)
{
	char	*fresh;
	int		len;

	len = ft_find_len(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (!(fresh = ft_strnew(len)))
		return (NULL);
	if (n < 0)
	{
		fresh[0] = '-';
		n *= -1;
	}
	if (n == 0)
		fresh[0] = '0';
	fresh[len + 1] = '\0';
	while (n > 0)
	{
		fresh[--len] = (n % 10) + '0';
		n = n / 10;
	}
	return (fresh);
}
