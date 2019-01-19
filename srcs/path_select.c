/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_select.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaskeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 18:30:43 by svaskeli          #+#    #+#             */
/*   Updated: 2019/01/17 11:25:56 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_compare_path(t_paths *path, t_paths *moving)
{
	t_path	*highway;
	t_path	*moving_high;

	highway = path->highway;
	moving_high = moving->highway;
	while(highway && moving_high)
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

void	ft_remove_path(t_lem_in *lem_in, t_paths **path)
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
	}
	free(*path);
	*path = NULL;
}

void	ft_remove_dublicates(t_lem_in *lem_in)
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

t_groups	*ft_add_group(t_lem_in *lem_in)
{
	t_groups	*new_group;
	t_groups	*group;

	new_group = (t_groups *)malloc(sizeof(t_groups));
	ft_bzero(new_group, sizeof(*new_group));
	if (!lem_in->groups)
	{
		lem_in->groups = new_group;
		return (lem_in->groups);
	}
	else
	{
		group = lem_in->groups;
		while (group && group->next)
			group = group->next;
		group->next = new_group;
		return (group->next);
	}
}

void	ft_add_to_group(t_groups *group, t_paths *path)
{
	t_group *new;

	new = (t_group *)malloc(sizeof(t_group));
	new->path = path;
	new->next = NULL;
	if (!group->group)
		group->group = new;
	if (group->last)
		group->last->next = new;
	group->last = new;
}

int		ft_compare_rooms(t_paths *path, t_paths *moving)
{
	t_path *room;
	t_path *move;

	room = path->highway->next;
	while (room && room->next)
	{
		move = moving->highway->next;
		while (move && move->next)
		{
			if (room->room == move->room)
				return (0);
			move = move->next;
		}
		room = room->next;
	}
	return (1);
}

void	ft_group_paths(t_lem_in *lem_in)
{
	t_paths		*path;
	t_paths		*moving;
	t_groups	*group;

	path = lem_in->paths;
	while (path)
	{
		group = ft_add_group(lem_in);
		ft_add_to_group(group, path);
		moving = lem_in->paths;
		while (moving)
		{
			if (ft_compare_rooms(path, moving))
				ft_add_to_group(group, moving);
			moving = moving->next;
		}
		path = path->next;
	}
}
