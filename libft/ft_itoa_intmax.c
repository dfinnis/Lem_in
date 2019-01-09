/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_intmax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 17:06:40 by dfinnis           #+#    #+#             */
/*   Updated: 2018/12/17 17:06:45 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find_len(intmax_t n)
{
	int			neg;
	int			len;

	neg = 0;
	len = 1;
	if (n < 0)
	{
		neg = 1;
		n *= -1;
	}
	while ((n /= 10) > 0)
		len++;
	return ((neg) ? len + 1 : len);
}

char		*ft_itoa_intmax(intmax_t n)
{
	char	*fresh;
	int		len;

	len = ft_find_len(n);
	if (n < -9223372036854775807)
		return (ft_strdup("9223372036854775808"));
	else if (n > 9223372036854775806)
		return (ft_strdup("9223372036854775807"));
	if (!(fresh = ft_strnew(len + 1)))
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
