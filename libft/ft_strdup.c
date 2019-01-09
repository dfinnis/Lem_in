/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:23:59 by dfinnis           #+#    #+#             */
/*   Updated: 2018/11/05 15:24:02 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*str;

	i = ft_strlen(s1);
	if (!(str = malloc(sizeof(*s1) * (i + 1))))
		return (NULL);
	while (i >= 0)
	{
		str[i] = s1[i];
		i--;
	}
	return (str);
}
