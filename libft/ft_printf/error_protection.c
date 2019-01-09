/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_protection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:17:32 by dfinnis           #+#    #+#             */
/*   Updated: 2018/12/18 14:17:33 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_error(char *s1, char *s2)
{
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2)
	{
		free(s2);
		s2 = NULL;
	}
	exit(1);
}

char		*ft_strdup_empty(char *form)
{
	char	*num_str;

	num_str = NULL;
	if (!(num_str = ft_strdup("")))
		ft_error(form, NULL);
	return (num_str);
}

char		*ft_strjoinfree_error(char *s1, char *s2, char *form)
{
	char	*num_str;

	num_str = NULL;
	if (!(num_str = ft_strjoinfree(s1, s2)))
	{
		if (form)
		{
			free(form);
			form = NULL;
		}
		ft_error(s1, s2);
	}
	return (num_str);
}

char		*ft_strjoinfree_s1_error(char *s1, char *s2, char *form)
{
	char	*num_str;

	num_str = NULL;
	if (!(num_str = ft_strjoinfree_s1(s1, s2)))
		ft_error(s1, form);
	return (num_str);
}

char		*ft_strjoinfree_s2_error(char *s1, char *s2, char *form)
{
	char	*num_str;

	num_str = NULL;
	if (!(num_str = ft_strjoinfree_s2(s1, s2)))
		ft_error(s2, form);
	return (num_str);
}
