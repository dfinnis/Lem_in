/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_group.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 16:25:49 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/20 16:25:50 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_groups	*ft_add_group(t_lem_in *lem_in)
{
	t_groups	*new_group;
	t_groups	*group;

	if (!(new_group = (t_groups *)malloc(sizeof(t_groups))))
		ft_lem_in_error(lem_in, "malloc fail in ft_add_group");
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

t_groups	*ft_add_to_group(t_groups *group, t_paths *path, t_lem_in *lem_in)
{
	t_group *new;

	if (!(new = (t_group *)malloc(sizeof(t_group))))
		ft_lem_in_error(lem_in, "malloc fail in ft_add_to_group");
	new->path = path;
	new->next = NULL;
	new->times = 0;
	if (!group->group)
		group->group = new;
	if (group->last)
		group->last->next = new;
	group->last = new;
	return (group);
}

static int	ft_compare_rooms(t_paths *path, t_paths *moving)
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

static int	ft_interate_cmp(t_groups *new_group, t_paths *second_path)
{
	t_group		*tmp_group;
	int			dup;

	dup = 0;
	tmp_group = new_group->group;
	while (tmp_group)
	{
		if (!ft_compare_rooms(tmp_group->path, second_path)
			|| tmp_group->path == second_path)
			dup++;
		tmp_group = tmp_group->next;
	}
	return (dup);
}

void		ft_group_paths(t_lem_in *lem_in)
{
	t_paths		*first_path;
	t_paths		*second_path;
	t_groups	*new_group;
	int			dup;

	first_path = lem_in->paths;
	while (first_path)
	{
		new_group = ft_add_group(lem_in);
		new_group = ft_add_to_group(new_group, first_path, lem_in);
		second_path = lem_in->paths;
		while (second_path)
		{
			dup = ft_interate_cmp(new_group, second_path);
			if (!dup)
				new_group = ft_add_to_group(new_group, second_path, lem_in);
			second_path = second_path->next;
		}
		new_group = ft_sort_paths(new_group);
		new_group = ft_update_size(new_group);
		new_group = ft_sort_paths(new_group);
		first_path = first_path->next;
	}
}
