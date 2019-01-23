/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 15:58:03 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/20 15:58:04 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_paths	*ft_add_path(t_lem_in *lem_in)
{
	t_paths	*new_path;
	t_paths	*path;

	if (!(new_path = (t_paths *)malloc(sizeof(t_paths))))
		ft_lem_in_error(lem_in, "malloc fail in ft_add_path");
	ft_bzero(new_path, sizeof(*new_path));
	if (!lem_in->paths)
	{
		lem_in->paths = new_path;
		return (lem_in->paths);
	}
	else
	{
		path = lem_in->paths;
		while (path && path->next)
			path = path->next;
		path->next = new_path;
		return (path->next);
	}
}

static void		ft_add_to_path(t_paths *path, t_room *room, t_lem_in *lem_in)
{
	t_path *new;

	if (!(new = (t_path *)malloc(sizeof(t_path))))
		ft_lem_in_error(lem_in, "malloc fail in ft_add_to_path");
	new->room = room;
	new->next = NULL;
	if (!path->highway)
		path->highway = new;
	if (path->last)
	{
		path->last->next = new;
	}
	path->last = new;
}

void			ft_update_length(t_paths *path)
{
	t_path	*highway;
	int		i;

	i = 0;
	highway = path->highway;
	while (highway)
	{
		highway = highway->next;
		i++;
	}
	path->length = i;
}

void			ft_add_direct_path(t_lem_in *lem_in)
{
	t_paths		*path;

	path = ft_add_path(lem_in);
	ft_add_to_path(path, lem_in->start, lem_in);
	ft_add_to_path(path, lem_in->end, lem_in);
}

void			ft_recover_path(t_lem_in *lem_in)
{
	t_paths		*path;
	t_queue		*queue;

	queue = lem_in->queue;
	while (queue && queue->room != lem_in->start)
		queue = queue->next;
	path = ft_add_path(lem_in);
	ft_add_to_path(path, lem_in->start, lem_in);
	if (queue->room == lem_in->start)
		queue = queue->parent;
	while (queue)
	{
		ft_add_to_path(path, queue->room, lem_in);
		queue = queue->parent;
	}
}
