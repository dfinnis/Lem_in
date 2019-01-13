#include "lem_in.h"

void	ft_add_to_queue(t_lem_in *lem_in, t_room *room)
{
	t_queue *new;
	t_queue	*tmp;

	new = NULL;
	tmp = lem_in->first_in_queue;
	if (lem_in->first_in_queue)
	{
		new = (t_queue *)malloc(sizeof(t_queue));
		new->room = room;
		new->next = NULL;
		while (tmp)
			tmp = tmp->next;
		tmp = new;
//		lem_in->last_in_queue->next = new;
//		lem_in->last_in_queue = new;
	}
	else
	{
		lem_in->first_in_queue = (t_queue *)malloc(sizeof(t_queue));
		lem_in->first_in_queue->room = room;
		lem_in->first_in_queue->next = NULL;
//		lem_in->last_in_queue = lem_in->first_in_queue;
	}
}

/*static void	ft_linkjoin(t_room *room, t_room *link)
{
	int		i;
	t_room	**new_links;

	i = 0;
	while (room->links[i])
		i++;
	if (!(new_links = (t_room **)malloc(sizeof(t_room *) * (i + 2))))
		ft_lem_in_error("ERROR");
	i = -1;
	while (room->links[++i])
		new_links[i] = room->links[i];
	new_links[i] = link;
	new_links[++i] = NULL;
	if (room->links)
		free(room->links);
	room->links = new_links;
}

void	ft_add_to_path(t_lem_in *lem_in, t_room *room)
{
	if (lem_in->path)
		ft_linkjoin(room, link);
	else
	{
		if (!(room->links = (t_room **)malloc(sizeof(t_room *) * 2)))
			ft_lem_in_error("ERROR");
		room->links[0] = link;
		room->links[1] = NULL;
	}
}*/

void	ft_pop_queue(t_lem_in *lem_in)
{
	t_queue *tmp;

	tmp = lem_in->first_in_queue;
	if (lem_in->first_in_queue)
		lem_in->first_in_queue = lem_in->first_in_queue->next;
	if (tmp)
	{
		tmp->room = NULL;
		tmp->next = NULL;
			free(tmp);
		tmp = NULL;
	}
}

/*int		ft_generate_key(t_room *room)
{
	int i;
	int sum;

	i = -1;
	sum = 0;
	while (room->name[++i])
		sum = sum + (int)room->name[i];
	return (sum % 1000);
}*/

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

/* Returns true if there is a path from source 's' to sink 't' in 
   residual graph. Also fills parent[] to store the path */
int	ft_bfs(t_lem_in *lem_in)//int rGraph[V][V], int s, int t, int parent[])
{
	// Create a visited array and mark all vertices as not visited 
	//	bool visited[V];
	//	memset(visited, 0, sizeof(visited));

	// Create a queue, enqueue source vertex and mark source vertex
	// as visited

	t_queue	*queue;
	t_room	*room;

	ft_reset_visited(lem_in);
	room = lem_in->start;
	ft_add_to_queue(lem_in, room);
	if (lem_in->first_in_queue)
		ft_printf("%s\n", lem_in->first_in_queue->room->name);
	queue = lem_in->first_in_queue;
	room->visited = 1;
//	ft_add_to_path(lem_in, room);


	//	queue <int> q;
	//	q.push(s);
	//	visited[s] = true; 
	//	parent[s] = -1; 

	// Standard BFS Loop 
	while (queue && queue->room != lem_in->end)//!q.empty())
	{
		t_room *top_room;
		int		i;

		i = -1;
		top_room = queue->room;
		ft_pop_queue(lem_in);

		//		int u = q.front(); 
		//		q.pop(); 

		while (top_room->links[++i])
		{
			if (!top_room->links[i]->visited)
			{
				ft_add_to_queue(lem_in, top_room->links[i]);
				if (lem_in->first_in_queue)
					ft_printf("%s\n", lem_in->first_in_queue->room->name);
//				ft_add_to_path(lem_in, top_room->links[i]);
				top_room->links[i]->visited = 1;
			}
			ft_printf("%i\n", i);
		}

		//		for (int v=0; v<V; v++) 
		//		{ 
		//			if (visited[v]==false && rGraph[u][v] > 0) 
		//			{ 
		///				q.push(v); 
		//				parent[v] = u; 
		//				visited[v] = true; 
		//			} 
		//		} 
	} 
	// If we reached sink in BFS starting from source, then return 
	// true, else false

	if (lem_in->end->visited == 1)
		return (1);
	else
		return (0);
} 

// Returns the maximum flow from s to t in the given graph 
int	ft_ford_fulkerson(t_lem_in *lem_in)//int graph[V][V], int s, int t)
{ 
	//	int u, v;

	// Create a residual graph and fill the residual graph with 
	// given capacities in the original graph as residual capacities 
	// in residual graph 
	//	ft_copy_residual(lem_in);
	//	int rGraph[V][V]; // Residual graph where rGraph[i][j] indicates  
	// residual capacity of edge from i to j (if there 
	// is an edge. If rGraph[i][j] is 0, then there is not)   
	//	for (u = 0; u < V; u++) 
	//		for (v = 0; v < V; v++) 
	//			rGraph[u][v] = graph[u][v]; 

//	t_path	*paths;
//	paths = lem_in->paths;

//	int parent[V];  // This array is filled by BFS and to store path 

	//	int max_flow = 0;  // There is no flow initially 

	// Augment the flow while tere is path from source to sink 
	while (ft_bfs(lem_in))
	{ 
		// Find minimum residual capacity of the edges along the 
		// path filled by BFS. Or we can say find the maximum flow 
		// through the path found. 
		//		int path_flow = INT_MAX; 
		//		for (v=t; v!=s; v=parent[v]) 
		//		{ 
		//			u = parent[v]; 
		//			path_flow = min(path_flow, rGraph[u][v]); 
		//		} 

		// update residual capacities of the edges and reverse edges 
		// along the path 

/*		int i;

		i = 0;
		while (paths->path[i])
			i++;
		paths->length = i; //adding the path length to the structure
		paths = paths->next;*/

		//////////////////////////////////////
/*		for (v=t; v != s; v=parent[v])
		{ 
			u = parent[v]; 
			rGraph[u][v] -= path_flow; 
			rGraph[v][u] += path_flow; 
		} */

		// Add path flow to overall flow 
//		max_flow += path_flow; 
		/////////////////////////////////////
	}
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
	return (i); //the number of paths
	// Return the overall flow 
	//	return max_flow; */
	return (0);
}
