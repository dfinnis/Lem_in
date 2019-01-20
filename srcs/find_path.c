/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaskeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 17:57:02 by svaskeli          #+#    #+#             */
/*   Updated: 2019/01/19 15:23:30 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_add_to_queue(t_lem_in *lem_in, t_room *room)
{
	t_queue *new;

	if (!(new = (t_queue *)malloc(sizeof(t_queue))))
		ft_lem_in_error(lem_in, "malloc fail in ft_add_to_queue");
	new->room = room;
	new->next = NULL;
	if (lem_in->queue)
	{
		lem_in->last_queue->next = new;
		lem_in->last_queue = new;
	}
	else
	{
		lem_in->queue = new;
		lem_in->last_queue = new;
	}
}

void	ft_pop_queue(t_lem_in *lem_in)
{
	t_queue *tmp;

	tmp = lem_in->queue;
	if (lem_in->queue)
		lem_in->queue = lem_in->queue->next;
	if (tmp)
		free(tmp);
	tmp = NULL;
}

void	ft_reset_visited(t_lem_in *lem_in)
{
	t_room *room;

	room = lem_in->room;
	while (room)
	{
		room->visited = 0;
		room->lvl = 0;
		room = room->next;
	}
}

t_paths	*ft_add_path(t_lem_in *lem_in)
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

void	ft_add_to_path(t_paths *path, t_room *room, t_lem_in *lem_in)
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

void	ft_recover_path(t_lem_in *lem_in)
{
	int 		i;
	t_paths		*path;

	path = ft_add_path(lem_in);
	ft_add_to_path(path, lem_in->start, lem_in);
	while (path->last->room != lem_in->end)
	{
		i = 0;
		while ((path->last->room->links[i]
			&& path->last->room->links[i]->lvl != (path->last->room->lvl - 1))
			|| (path->last->room->links[i]->lvl == 0
			&& path->last->room->links[i] != lem_in->end)
			|| path->last->room->links[i] == lem_in->start
			|| !path->last->room->links[i]->visited)
			i++;
		ft_add_to_path(path, path->last->room->links[i], lem_in);
	}
}

// int ft_bfs_no_flow(t_lem_in *lem_in)
// {
// 	if (top_room == lem_in->end && top_room->links[i] == lem_in->start)
// 		i++;
// 	if (top_room->links[i] && top_room->links[i]->visited == 0 
// 			&& top_room->links[i]->flow == 0)
// 	{
// 		ft_add_to_queue(lem_in, top_room->links[i]);
// 		top_room->links[i]->lvl = top_room->lvl + 1;
// 		top_room->links[i]->visited = 1;
// 		add++;
// 	}
// 	if (top_room->links[i])
// 		i++;
// }

int	ft_bfs(t_lem_in *lem_in)
{
	int		i;
	int		add;
	t_room	*top_room;
	t_queue	*tmp;

	ft_reset_visited(lem_in);
	ft_add_to_queue(lem_in, lem_in->end);
	lem_in->end->visited = 1;
	while (lem_in->queue)
	{
		top_room = lem_in->queue->room;
		ft_pop_queue(lem_in);
		i = 0;
		add = 0;
		while (top_room->links[i])
		{
			if (top_room == lem_in->end && top_room->links[i] == lem_in->start)
				i++;
			if (top_room->links[i] && top_room->links[i]->visited == 0 
					&& top_room->links[i]->flow == 0)
			{
				ft_add_to_queue(lem_in, top_room->links[i]);
				top_room->links[i]->lvl = top_room->lvl + 1;
				top_room->links[i]->visited = 1;
				add++;
			}
			if (top_room->links[i])
				i++;
		}
		i = 0;
		while (top_room->links[i] && !add)
		{
			if (top_room == lem_in->end && top_room->links[i] == lem_in->start)
				i++;
			if (top_room->links[i] && top_room->links[i]->visited == 0
				&& top_room->links[i]->flow == 1)
			{
				ft_add_to_queue(lem_in, top_room->links[i]);
				top_room->links[i]->lvl = top_room->lvl + 1;
				top_room->links[i]->visited = 1;
			}
			if (top_room->links[i])
				i++;
		}
	}
	while (lem_in->queue)
	{
		tmp = lem_in->queue;
		lem_in->queue  = lem_in->queue->next;
		free(tmp);
		tmp = NULL;
	}
	lem_in->queue = NULL;
	if (lem_in->start->visited == 1)
		return (1);
	else
		return (0);
} 

void	ft_update_length(t_paths *path)
{
	t_path *highway;
	int			i;

	i = 0;
	highway = path->highway;
	while (highway)
	{
		highway = highway->next;
		i++;
	}
	path->length = i;
}

void	add_direct_path(t_lem_in *lem_in)
{
	t_paths		*path;

	path = ft_add_path(lem_in);
	ft_add_to_path(path, lem_in->start, lem_in);
	ft_add_to_path(path, lem_in->end, lem_in);
}

void	ft_bfs_loop(t_lem_in *lem_in)
{
	t_paths	*road;
	t_path	*highway;

	ft_recover_path(lem_in);
	road = lem_in->paths;
	while (road->next)
		road = road->next;
	ft_update_length(road);
	highway = road->highway;
	while (highway)
	{
		if (highway->room != lem_in->start && highway->room != lem_in->end)
			highway->room->flow++;
		highway = highway->next;
	}
}

void	ft_edmonds_karp(t_lem_in *lem_in)
{
	int		i;

	i = 0;
	while (lem_in->start->links[i])
	{
		if (lem_in->start->links[i] == lem_in->end)
			add_direct_path(lem_in);
		i++;
	}
	while (ft_bfs(lem_in))
		ft_bfs_loop(lem_in);
	if (!lem_in->paths)
		ft_lem_in_error(lem_in, "no path");
	else
	{
		ft_remove_dublicates(lem_in);
		ft_group_paths(lem_in);
	}
}
