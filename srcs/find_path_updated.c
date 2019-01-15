/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaskeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 17:57:02 by svaskeli          #+#    #+#             */
/*   Updated: 2019/01/15 17:26:32 by svaskeli         ###   ########.fr       */
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

void	ft_add_to_path(t_path **path, t_room *room)
{
	t_path *new;

	if (*path)
	{
		new = (t_path *)malloc(sizeof(t_path));
		new->room = room;
		new->next = NULL;
		(*path)->next = new;
		(*path) = new;
	}
	else
	{
//		(*path) = (t_path *)malloc(sizeof(t_path));
//		(*path)->next = NULL;
//		(*path)->length = 0;
		(*path) = (t_path *)malloc(sizeof(t_path));
		(*path)->room = room;
		(*path)->next = NULL;
//		(*path)->last = (*path)->highway;
	}
}

void	ft_recover_path(t_lem_in *lem_in, int i)
{
	int		j;
	t_path	*path;

	path = lem_in->path[i];
	ft_add_to_path(&path, lem_in->end);
	while (path->room != lem_in->start)
	{
		j = 0;
		while (path->room->links[j] && path->room->links[j]->flow == 0 && 
				path->room->links[j]->lvl != path->room->lvl - 1)
			j++;
		ft_add_to_path(&path, path->room->links[j]);
	}
}

void	ft_print_paths(t_path *path)
{
	int i = 0;
	int	j = 0;
	t_path *paths;

	paths = path;
	while (paths)
	{
		while (*paths[i])
		{
			ft_printf("%i road -> %s\n", j, paths[i]->room->name);
			paths[i] = paths[i]->next;
			i++;
		}
		j++;
		paths = paths->next;
	}
}

int	ft_bfs(t_lem_in *lem_in/*, t_path **path*/)
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

/*void	ft_extend_path(t_path **path)
{
	int i;
	t_path	**new_path;

	i = 0;
	while(path[i])
		i++;
	new_path = (t_path **)malloc(sizeof(t_path) * (i + 2));
	i = -1;
	while (path[++i])
		new_path[i] = path[i];
	new_path[i] = NULL;
	new_path[++i] = NULL;
	if (path[i])
		free(path[i]);
	path[i] = new_path[i];
}*/

void	ft_add_path(t_lem_in *lem_in)
{
/*	if (paht)
		ft_extend_path(path);
	else
	{*/
		t_path **new;
		new = (t_path **)malloc(sizeof(t_path *) * 1000);
		*new = NULL;
//		path[1] = NULL;
//		path->room = NULL;
//		path->next = NULL;
//		path = NULL;
/*	}*/
		lem_in->path = new;
}

int		ft_edmonds_karp(t_lem_in *lem_in)
{
	int		i;
	t_path	*road;
//	t_path	*path;

//	path = lem_in->paths;
//	lem_in->last_path = lem_in->paths;
	i = 0;
	while (ft_bfs(lem_in/*, &path*/))
	{
		ft_add_path(lem_in); //might not work
		ft_recover_path(lem_in, i);
		road = lem_in->path[i++];
		while (road)
		{
			if (road->room != lem_in->start && road->room != lem_in->end)
				road->room->flow = 1;
			road = road->next;
		}
//		if (/*lem_in->*/lem_in->last_path)
//			ft_print_paths(/*lem_in->*/lem_in->last_path);
//		while (path)
//			path = path->next;
	}
	if (lem_in->path)
		ft_print_paths(lem_in->path);
	else
		ft_lem_in_error("no paths");
	return (i);
}
