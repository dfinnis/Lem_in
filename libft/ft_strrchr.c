/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:27:50 by dfinnis           #+#    #+#             */
/*   Updated: 2018/11/05 15:27:52 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*needle;

	needle = NULL;
	while (*s)
	{
		if (*s == c)
			needle = (char*)s;
		s++;
	}
	if (*s == c)
		needle = (char*)s;
	return (needle);
}
