/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 15:58:19 by dfinnis           #+#    #+#             */
/*   Updated: 2019/01/20 15:58:23 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_queue		*ft_add_to_queue(t_lem_in *lem_in, t_room *room, t_queue *parent)
{
	t_queue *new;
	t_queue *tmp;

	if (!(new = (t_queue *)malloc(sizeof(t_queue))))
		ft_lem_in_error(lem_in, "malloc fail in ft_add_to_queue");
	new->room = room;
	new->next = NULL;
	new->parent = parent;
	tmp = parent;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new;
	else
	{
		parent = new;
		lem_in->queue = parent;
	}
	return (parent);
}

t_queue		*ft_pop_queue(t_queue *queue)
{
	if (queue)
		queue = queue->next;
	return (queue);
}

void		ft_reset_visited(t_lem_in *lem_in)
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

void		ft_sort_group(t_lem_in *lem_in)
{
	t_group	*tmp;
	t_paths	*swap;
	int		count;

	count = 0;
	tmp = lem_in->shortest->group;
	while (tmp && tmp->next && count++ < lem_in->depth)
	{
		if (tmp->path->length > tmp->next->path->length)
		{
			swap = tmp->path;
			tmp->path = tmp->next->path;
			tmp->next->path = swap;
			tmp = lem_in->shortest->group;
		}
		tmp = tmp->next;
	}
}
