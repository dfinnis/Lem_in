/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree_s2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 13:22:00 by dfinnis           #+#    #+#             */
/*   Updated: 2018/12/16 13:22:02 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree_s2(char *s1, char *s2)
{
	char	*fresh;

	if (!s1 || !s2)
		return (0);
	if (!(fresh = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	ft_strcpy(fresh, s1);
	ft_strcat(fresh, s2);
	if (s2)
	{
		free(s2);
		s2 = NULL;
	}
	return (fresh);
}
