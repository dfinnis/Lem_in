/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_select.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaskeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 18:30:43 by svaskeli          #+#    #+#             */
/*   Updated: 2019/01/19 15:28:31 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	ft_compare_path(t_paths *path, t_paths *moving)
{
	t_path	*highway;
	t_path	*moving_high;

	highway = path->highway;
	moving_high = moving->highway;
	while (highway && moving_high)
	{
		if (highway->room != moving_high->room)
			return (0);
		highway = highway->next;
		moving_high = moving_high->next;
	}
	if (!highway && !moving_high)
		return (1);
	else
		return (0);
}

static void	ft_remove_path(t_lem_in *lem_in, t_paths **path)
{
	t_paths	*remove;
	t_path	*tmp;

	remove = lem_in->paths;
	while (remove && remove->next != *path)
		remove = remove->next;
	remove->next = remove->next->next;
	while (*path && (*path)->highway)
	{
		tmp = (*path)->highway;
		(*path)->highway = (*path)->highway->next;
		free(tmp);
		tmp = NULL;
	}
	free(*path);
	*path = NULL;
}

void		ft_remove_duplicates(t_lem_in *lem_in)
{
	t_paths	*path;
	t_paths	*moving_path;

	path = lem_in->paths;
	while (path && path->next)
	{
		moving_path = path->next;
		while (moving_path)
		{
			if (ft_compare_path(path, moving_path))
			{
				ft_remove_path(lem_in, &moving_path);
				moving_path = path->next;
			}
			if (moving_path)
				moving_path = moving_path->next;
		}
		path = path->next;
	}
}

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
