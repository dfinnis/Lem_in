/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:22:30 by dfinnis           #+#    #+#             */
/*   Updated: 2018/11/05 15:22:31 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*ptr_dst;
	const char	*ptr_src;

	ptr_dst = (char*)dst;
	ptr_src = (char*)src;
	while (n)
	{
		*ptr_dst++ = *ptr_src++;
		n--;
	}
	return (dst);
}
