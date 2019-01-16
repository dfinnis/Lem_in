/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaskeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 17:57:02 by svaskeli          #+#    #+#             */
/*   Updated: 2019/01/16 11:48:44 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_add_to_queue(t_lem_in *lem_in, t_room *room)
{
	t_queue *new;

	new = (t_queue *)malloc(sizeof(t_queue));
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
	free(tmp);
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

t_path	*ft_add_path(t_lem_in *lem_in)
{
	t_path	*new_path;
	t_path	*path;

	new_path = (t_path *)malloc(sizeof(t_path));
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

void	ft_add_to_path(t_path *path, t_room *room)
{
	t_path_room *new;

	new = (t_path_room *)malloc(sizeof(t_path_room));
	new->room = room;
	new->next = NULL;
	if (!path->highway)
		path->highway = new;
	if (path->last)
		path->last->next = new;
	path->last = new;
}

void	ft_recover_path(t_lem_in *lem_in)
{
	int i;
	t_path		*path;

	path = ft_add_path(lem_in);
	ft_add_to_path(path, lem_in->end);
	while (path->last->room != lem_in->start)
	{
		i = 0;
		while ((path->last->room->links[i] && path->last->room->links[i]->lvl != (path->last->room->lvl - 1))
				|| (path->last->room->links[i]->lvl == 0 && path->last->room->links[i] != lem_in->start)
				|| path->last->room->links[i] == lem_in->end || !path->last->room->links[i]->visited)
			i++;
		ft_add_to_path(path, path->last->room->links[i]);
	}
}

void	ft_print_paths(t_path *path)
{
	int i = 0;
	t_path *roads;

	roads = path;
	while (roads)
	{
		ft_printf("\n-NEW PATH-\n");
		while (roads->highway)
		{
			ft_printf("road %i - %s\n", i, roads->highway->room->name);
			roads->highway = roads->highway->next;
		}
		i++;
		roads = roads->next;
	}
}

int	ft_bfs(t_lem_in *lem_in)
{
	int		i;
	t_room	*top_room;
	t_queue	*tmp;

	ft_reset_visited(lem_in);
	ft_add_to_queue(lem_in, lem_in->start);
	lem_in->start->visited = 1;

	// Standard BFS Loop 
	while (lem_in->queue && lem_in->queue->room != lem_in->end)
	{
		top_room = lem_in->queue->room;
		ft_pop_queue(lem_in);
		i = 0;
		while (top_room->links[i])
		{
			if (top_room->links[i]->visited == 0 
					&& top_room->links[i]->flow == 0)
			{
				ft_add_to_queue(lem_in, top_room->links[i]);
				top_room->links[i]->lvl = top_room->lvl + 1;
				top_room->links[i]->visited = 1;
			}
			i++;
		}
	}
	if (lem_in->queue)
	{
		while (lem_in->queue)
		{
			tmp = lem_in->queue;
			lem_in->queue  = lem_in->queue->next;
			free(tmp);
		}
		lem_in->queue = NULL;
	}
	if (lem_in->end->visited == 1)
		return (1);
	else
		return (0);
} 

int	ft_edmonds_karp(t_lem_in *lem_in)
{
	t_path		*road;
	t_path_room	*highway;

	while (ft_bfs(lem_in))
	{
		ft_recover_path(lem_in);
		road = lem_in->paths;
		while (road->next)
			road = road->next;
		highway = road->highway;
		while (highway)
		{
			if (highway->room != lem_in->start && highway->room != lem_in->end)
				highway->room->flow = 1;
			highway = highway->next;
		}
	}
	if (lem_in->paths)
		ft_print_paths(lem_in->paths);
	return (0);
}
