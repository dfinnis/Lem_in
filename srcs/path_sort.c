/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 12:54:47 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/22 12:54:48 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_groups	*ft_sort_paths(t_groups *group)
{
	t_group	*tmp;
	t_paths	*swap;

	tmp = group->group;
	while (tmp && tmp->next)
	{
		if (tmp->path->length > tmp->next->path->length)
		{
			swap = tmp->path;
			tmp->path = tmp->next->path;
			tmp->next->path = swap;
			tmp = group->group;
		}
		tmp = tmp->next;
	}
	return (group);
}

t_groups	*ft_update_size(t_groups *group)
{
	t_group *tmp;
	int		i;

	i = 0;
	tmp = group->group;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	group->size = i;
	return (group);
}
