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

void		ft_add_to_queue(t_lem_in *lem_in, t_room *room)
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

void		ft_pop_queue(t_lem_in *lem_in)
{
	t_queue *tmp;

	tmp = lem_in->queue;
	if (lem_in->queue)
		lem_in->queue = lem_in->queue->next;
	if (tmp)
		free(tmp);
	tmp = NULL;
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
