/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 11:01:30 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/07 11:01:33 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find_len(uintmax_t n, int b)
{
	int			len;

	len = 1;
	while ((n /= b) > 0)
		len++;
	return (len);
}

static char	*ft_strdup_base(char *base, char type)
{
	if (type == 'X')
	{
		if (!(base = ft_strdup("0123456789ABCDEF")))
			return (NULL);
	}
	else
	{
		if (!(base = ft_strdup("0123456789abcdef")))
			return (NULL);
	}
	return (base);
}

char		*ft_itoa_base(uintmax_t n, int b, char type)
{
	char	*base;
	char	*fresh;
	int		len;

	base = NULL;
	if (n == 0)
		return (ft_strdup("0"));
	if (!(base = ft_strdup_base(base, type)))
		return (NULL);
	len = ft_find_len(n, b);
	if (!(fresh = ft_strnew(len + 1)))
		return (NULL);
	fresh[len + 1] = '\0';
	while (n > 0)
	{
		fresh[--len] = base[n % b];
		n = n / b;
	}
	free(base);
	base = NULL;
	return (fresh);
}
