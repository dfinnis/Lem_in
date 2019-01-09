/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 07:25:33 by dfinnis           #+#    #+#             */
/*   Updated: 2018/11/06 07:25:36 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*fresh;

	if (!(fresh = (char*)malloc((size + 1) * sizeof(char))))
		return (NULL);
	ft_bzero(fresh, size + 1);
	return (fresh);
}
