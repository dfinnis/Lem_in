/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaskeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 17:57:02 by svaskeli          #+#    #+#             */
/*   Updated: 2019/01/15 23:18:13 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_add_to_queue(t_lem_in *lem_in, t_queue **queue, t_room *room)
{
	t_queue *new;

	new = (t_queue *)malloc(sizeof(t_queue));
	if (*queue)
	{
		new->room = room;
		new->next = NULL;
		lem_in->last_queue->next = new;
		lem_in->last_queue = new;
	}
	else
	{
		new->room = room;
		new->next = NULL;
		*queue = new;
		lem_in->last_queue = new;
	}
}

void	ft_pop_queue(t_queue **queue)
{
	t_queue *tmp;

	tmp = *queue;
	if (*queue)
		*queue = (*queue)->next;
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
//	new_path->next = NULL;
//	new_path->length = 0;
//	new_path->last = NULL;
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
		while (path->last->room->links[i]
				&& path->last->room->links[i]->flow == 0
				&& path->last->room->links[i]->lvl != path->last->room->lvl - 1)
		{
			ft_printf("room %s links[i] - %s\n", path->last->room->name, path->last->room->links[i]->name);
			i++;
		}
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
	t_queue	*queue;

	queue = lem_in->queue;
	ft_reset_visited(lem_in);
	ft_add_to_queue(lem_in, &queue, lem_in->start);
	lem_in->start->visited = 1;

	// Standard BFS Loop 
	while (queue && queue->room != lem_in->end)
	{
		t_room *top_room;

		top_room = queue->room;
		ft_pop_queue(&queue);
		i = 0;
		while (top_room->links[i])
		{
			if (top_room->links[i]->visited == 0 && top_room->links[i]->flow == 0)
			{
				ft_add_to_queue(lem_in, &queue, top_room->links[i]);
				top_room->links[i]->lvl = top_room->lvl + 1;
				top_room->links[i]->visited = 1;
			}
			i++;
		}
	}
	if (lem_in->end->visited == 1)
		return (1);
	else
		return (0);
} 

int	ft_edmonds_karp(t_lem_in *lem_in)
{
	t_path_room	*road;

	while (ft_bfs(lem_in))
	{
		ft_recover_path(lem_in);
		road = lem_in->paths->highway;
		while (road)
		{
			if (road->room != lem_in->start && road->room != lem_in->end)
				road->room->flow = 1;
			road = road->next;
		}
		if (lem_in->paths)
			ft_print_paths(lem_in->paths);
	}
	return (0);
}
