/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 15:47:46 by dfinnis           #+#    #+#             */
/*   Updated: 2018/08/29 15:48:04 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char *str)
{
	int	i;
	int	count;
	int	word;

	i = 0;
	count = 0;
	word = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] && !ft_isblank(str[i]))
		{
			i++;
			word = 1;
		}
		while (str[i] && ft_isblank(str[i]))
			i++;
		if (word == 1)
			count++;
		word = 0;
	}
	return (count);
}

static int	ft_word_len(char *str, int i)
{
	int	count;

	count = 1;
	while (str[i] && !ft_isblank(str[i]))
	{
		count++;
		i++;
	}
	return (count);
}

char		**ft_split_whitespaces(char *str)
{
	int		i;
	int		j;
	int		k;
	char	**res;

	i = 0;
	j = 0;
	if (!(res = (char **)malloc(sizeof(char *) * (ft_count_words(str) + 1))))
		return (NULL);
	while (str[i])
	{
		k = 0;
		while (str[i] && ft_isblank(str[i]))
			i++;
		if (!str[i])
			break ;
		if (!(res[j] = (char *)malloc(sizeof(char) * (ft_word_len(str, i)))))
			return (NULL);
		while (str[i] && !ft_isblank(str[i]))
			res[j][k++] = str[i++];
		res[j][k] = '\0';
		j++;
	}
	res[j] = NULL;
	return (res);
}
