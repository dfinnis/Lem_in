/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 16:30:37 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/20 16:30:38 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_free_rooms(t_room *room)
{
	t_room *tmp;

	while (room)
	{
		tmp = room;
		room = room->next;
		if (tmp->name)
			free(tmp->name);
		tmp->name = NULL;
		if (tmp->links)
			free(tmp->links);
		tmp->links = NULL;
		free(tmp);
		tmp = NULL;
	}
}

static void	ft_free_links(t_link *link)
{
	t_link *tmp;

	while (link)
	{
		tmp = link;
		link = link->next;
		free(tmp);
		tmp = NULL;
	}
}

static void	ft_free_paths(t_paths *paths)
{
	t_paths *tmp;
	t_path	*high;

	while (paths)
	{
		tmp = paths;
		paths = paths->next;
		while (tmp->highway)
		{
			high = tmp->highway;
			tmp->highway = tmp->highway->next;
			free(high);
			high = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
}

static void	ft_free_groups(t_groups *groups)
{
	t_groups	*tmp;
	t_group		*tmp_g;

	while (groups)
	{
		tmp = groups;
		groups = groups->next;
		while (tmp->group)
		{
			tmp_g = tmp->group;
			tmp->group = tmp->group->next;
			free(tmp_g);
			tmp_g = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
}

void		ft_lem_in_free(t_lem_in *lem_in)
{
	if (lem_in->line)
		free(lem_in->line);
	lem_in->line = NULL;
	if (lem_in->room)
		ft_free_rooms(lem_in->room);
	if (lem_in->link)
		ft_free_links(lem_in->link);
	if (lem_in->queue)
		ft_free_queue(lem_in->queue);
	if (lem_in->paths)
		ft_free_paths(lem_in->paths);
	if (lem_in->groups)
		ft_free_groups(lem_in->groups);
	if (lem_in->array)
		ft_free_ants(lem_in->array);
}
