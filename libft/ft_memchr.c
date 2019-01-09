/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 06:56:33 by dfinnis           #+#    #+#             */
/*   Updated: 2018/11/06 06:56:35 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char*)s;
	while (i < n)
	{
		if (*ptr == (char)c)
			return (ptr);
		else
		{
			ptr++;
			i++;
		}
	}
	return (NULL);
}
