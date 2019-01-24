/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 16:14:17 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/20 16:14:21 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	ft_bfs_no_flow(t_lem_in *lem_in, t_room *room, int i, t_queue *queue, int *add)
{
	if (room == lem_in->end && room->links[i] == lem_in->start)
		i++;
	if ((room->links[i] && !room->links[i]->visited && !room->links[i]->flow)
		|| (room->links[i] && room->links[i] == lem_in->start))
	{
		queue = ft_add_to_queue(lem_in, room->links[i], queue);
		room->links[i]->visited = 1;
		*add = 1;
	}
	if (room->links[i])
		i++;
	return (i);
}

// static int	ft_bfs_flow(t_lem_in *lem_in, t_room *room, int i, t_queue *queue)
// {
// 	if (room == lem_in->end && room->links[i] == lem_in->start)
// 		i++;
// 	if ((room->links[i] && !room->links[i]->visited && room->links[i]->flow == 1)
// 		|| (room->links[i] && room->links[i] == lem_in->start))
// 	{
// 		ft_add_to_queue(lem_in, room->links[i], queue);
// 		room->links[i]->visited = 1;
// 	}
// 	if (room->links[i])
// 		i++;
// 	return (i);
// }

static int	ft_bfs(t_lem_in *lem_in)
{
	int		i;
	t_queue	*queue;
	int		add;

	ft_reset_visited(lem_in);
	queue = ft_add_to_queue(lem_in, lem_in->end, NULL);
	queue->room->visited = 1;
	while (queue)
	{
		i = 0;
		add = 0;
		if (lem_in->start->visited)
			return (1);
		while (queue->room->links[i])
			i = ft_bfs_no_flow(lem_in, queue->room, i, queue, &add);
		// i = 0;
		// if (!add)
		// 	while (queue->room->links[i])
		// 		i = ft_bfs_flow(lem_in, queue->room, i, queue);
		queue = queue->next;
	}
	return (0);
}

static void	ft_bfs_loop(t_lem_in *lem_in)
{
	t_paths	*road;
	t_path	*highway;

	ft_recover_path(lem_in);
	ft_free_queue(lem_in->queue);
	lem_in->queue = NULL;
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

void		ft_solve_algo(t_lem_in *lem_in)
{
	int		i;

	i = 0;
	while (lem_in->start->links[i])
	{
		if (lem_in->start->links[i] == lem_in->end)
			ft_add_direct_path(lem_in);
		i++;
	}
	while (ft_bfs(lem_in))
		ft_bfs_loop(lem_in);
	if (!lem_in->paths)
		ft_lem_in_error(lem_in, "no path");
	else
	{
		ft_remove_duplicates(lem_in);
		ft_group_paths(lem_in);
	}
}
