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
	t_path_room *new;

	if (*path)
	{
		new = (t_path_room *)malloc(sizeof(t_path_room));
		new->room = room;
		new->next = NULL;
		(*path)->last->next = new;
		(*path)->last = new;
//		ft_printf("!!!!\n");
	}
	else
	{
		(*path) = (t_path *)malloc(sizeof(t_path));
		(*path)->next = NULL;
		(*path)->length = 0;
		(*path)->path = (t_path_room *)malloc(sizeof(t_path_room));
		(*path)->path->room = room;
		(*path)->path->next = NULL;
		(*path)->last = (*path)->path;
//		ft_printf("???\n");
	}
}

void	ft_recover_path(t_path **path, t_lem_in *lem_in)
{
	int i;

	ft_add_to_path(path, lem_in->end);
	while ((*path)->last->room != lem_in->start)
	{
		i = 0;
		while ((*path)->last->room->links[i] && (*path)->last->room->links[i]->flow == 0 && (*path)->last->room->links[i]->lvl != (*path)->last->room->lvl - 1)
			i++;
		ft_add_to_path(path, (*path)->last->room->links[i]);
	}
}

void	ft_print_paths(t_path *path)
{
	int i = 0;
	t_path *roads;

	roads = path;
	while (roads)
	{
		while (roads->path)
		{
			ft_printf("road %i - %s\n", i, roads->path->room->name);
			roads->path = roads->path->next;
		}
		i++;
		roads = roads->next;
	}
}

int	ft_bfs(t_lem_in *lem_in)
{
	int		i;
	t_path	*path;
	t_queue	*queue;

	path = lem_in->paths;
	while (path)
		path = path->next;
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
	ft_recover_path(&path, lem_in);
	lem_in->paths = path;
	if (lem_in->end->visited == 1)
		return (1);
	else
		return (0);
} 

int	ft_ford_fulkerson(t_lem_in *lem_in)
{
	t_path_room	*road;

	while (ft_bfs(lem_in))
	{
		road = lem_in->paths->path;
		while (road)
		{
			if (road->room != lem_in->start && road->room != lem_in->end)
				road->room->flow = 1;
			road = road->next;
		}
		if (lem_in->paths)
			ft_print_paths(lem_in->paths);
	}
//	ft_bfs(lem_in);
//	ft_print_paths(lem_in->paths);
	return (0);
}
