/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 06:48:18 by dfinnis           #+#    #+#             */
/*   Updated: 2018/11/06 06:48:21 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*ptr_dst;
	unsigned char	*ptr_src;
	size_t			i;

	ptr_dst = (unsigned char*)dst;
	ptr_src = (unsigned char*)src;
	i = 0;
	while (i < n)
	{
		*ptr_dst = *ptr_src;
		if (*ptr_dst == (unsigned char)c)
		{
			ptr_dst++;
			return (ptr_dst);
		}
		ptr_dst++;
		ptr_src++;
		i++;
	}
	return (NULL);
}
