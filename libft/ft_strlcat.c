/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:26:03 by dfinnis           #+#    #+#             */
/*   Updated: 2018/11/05 15:26:05 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	while (dst[i] && i < size)
		i++;
	while (src[j])
		j++;
	len = i + j;
	j = 0;
	while (size != 0 && i < (size - 1) && src[j])
		dst[i++] = src[j++];
	while (i < size)
		dst[i++] = 0;
	return (len);
}
