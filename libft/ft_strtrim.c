/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 09:15:10 by dfinnis           #+#    #+#             */
/*   Updated: 2018/11/06 09:15:12 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*fresh;
	size_t	sta;
	size_t	end;

	if (!s)
		return (0);
	sta = 0;
	end = ft_strlen(s) - 1;
	while (s[sta] && (s[sta] == ' ' || s[sta] == '\n' || s[sta] == '\t'))
		sta++;
	while (sta < end && (s[end] == ' ' || s[end] == '\n' || s[end] == '\t'))
		end--;
	fresh = ft_strsub(s, sta, (end - sta + 1));
	return (fresh);
}
