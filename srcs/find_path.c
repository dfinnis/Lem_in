#include "lem_in.h"

void	ft_add_to_queue(t_lem_in *lem_in, t_room *room)
{
	t_queue *new;

	new = (t_queue *)malloc(sizeof(t_queue));
	if (lem_in->queue)
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
		lem_in->queue = new;
		lem_in->last_queue = new;
	}
}

void	ft_pop_queue(t_lem_in *lem_in)
{
	t_queue *tmp;

	tmp = NULL;
	if (lem_in->queue)
		lem_in->queue = lem_in->queue->next;
	free(lem_in->queue);
	lem_in->queue = tmp;
}

void	ft_reset_visited(t_lem_in *lem_in)
{
	t_room *room;

	room = lem_in->room;
	while (room)
	{
		room->visited = 0;
		room = room->next;
	}
}

int	ft_bfs(t_lem_in *lem_in)
{
	int		i;

	ft_reset_visited(lem_in);
	ft_add_to_queue(lem_in, lem_in->start);
	lem_in->start->visited = 1;
//	ft_add_to_path(lem_in, lem_in->start);

	// Standard BFS Loop 
	while (lem_in->queue && lem_in->queue->room != lem_in->end)
	{
		t_room *top_room;

		top_room = lem_in->queue->room;
		ft_pop_queue(lem_in);
		i = -1;
		while (top_room->links[++i])
		{
			if (top_room->links[i]->visited == 0)
			{
				ft_add_to_queue(lem_in, top_room->links[i]);
//				ft_add_to_path(lem_in, top_room->links[i]);
				ft_printf("adding to queue - %s\n", top_room->links[i]->name);
				top_room->links[i]->visited = 1;
			}
		}
	} 
	if (lem_in->end->visited == 1)
		return (1);
	else
		return (0);
} 

int	ft_ford_fulkerson(t_lem_in *lem_in)
{ 
//	t_path	*paths;
//	paths = lem_in->paths;

	ft_bfs(lem_in);
//	while (ft_bfs(lem_in))
//	{ 
//		int i;

//		i = 0;
/*		while (paths->path[i])
			i++;
		paths->length = i; //adding the path length to the structure
		paths = paths->next;*/

/*		for (v=t; v != s; v=parent[v])
		{ 
			u = parent[v]; 
			rGraph[u][v] -= path_flow; 
			rGraph[v][u] += path_flow; 
		} */
//	}
/*	paths = NULL; // terminating the paths list
	int		i;
	t_path	*tmp;

	i = 0;
	tmp = lem_in->paths;
	while (tmp->next)
	{
		i++;
		tmp = tmp->next;
	}
	return (i); //the number of paths*/
	return (0);
}
