/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 09:27:21 by dfinnis           #+#    #+#             */
/*   Updated: 2018/11/06 09:27:22 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wcount(const char *s, char c)
{
	int	i;
	int	wcount;

	i = 0;
	wcount = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		wcount++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (wcount);
}

static int	ft_wlen(const char *s, char c, int wref)
{
	int	i;
	int	wlen;
	int	count;

	i = 0;
	count = -1;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		wlen = 0;
		while (s[i] && s[i] != c)
		{
			i++;
			wlen++;
		}
		count++;
		if (count == wref)
			break ;
		while (s[i] && s[i] == c)
			i++;
	}
	return (wlen);
}

static int	ft_start(const char *s, char c, int wref)
{
	int	i;
	int	start;
	int	ref;

	i = 0;
	ref = 0;
	while (s[i] && s[i] == c)
		i++;
	start = i;
	while (ref < wref)
	{
		while (s[i] && s[i] != c)
			i++;
		while (s[i] && s[i] == c)
			i++;
		start = i;
		ref++;
	}
	return (start);
}

char		**ft_strsplit(char const *s, char c)
{
	int				wcount;
	int				wref;
	int				wlen;
	char			**strings;
	unsigned int	start;

	if (!s)
		return (NULL);
	wcount = ft_wcount(s, c);
	if (!(strings = (char **)malloc(sizeof(char *) * (wcount + 1))))
		return (NULL);
	wref = 0;
	while (wref < wcount)
	{
		start = ft_start(s, c, wref);
		wlen = ft_wlen(s, c, wref);
		if (!(strings[wref] = ft_strsub(s, start, wlen)))
			return (NULL);
		wref++;
	}
	strings[wref] = NULL;
	return (strings);
}
