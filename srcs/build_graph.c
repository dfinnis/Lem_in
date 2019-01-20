/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaskeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 11:15:09 by svaskeli          #+#    #+#             */
/*   Updated: 2019/01/17 11:15:11 by svaskeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_linkjoin(t_room *room, t_room *link, t_lem_in *lem_in)
{
	int		i;
	t_room	**new_links;

	i = 0;
	while (room->links[i])
		i++;
	if (!(new_links = (t_room **)malloc(sizeof(t_room *) * (i + 2))))
		ft_lem_in_error(lem_in, "malloc tube fail");
	i = -1;
	while (room->links[++i])
		new_links[i] = room->links[i];
	new_links[i] = link;
	new_links[++i] = NULL;
	if (room->links)
		free(room->links);
	room->links = new_links;
}

static void	ft_add_tubes(t_room *room, t_room *link, t_lem_in *lem_in)
{
	if (room->links)
		ft_linkjoin(room, link, lem_in);
	else
	{
		if (!(room->links = (t_room **)malloc(sizeof(t_room *) * 2)))
			ft_lem_in_error(lem_in, "malloc first tube fail");
		room->links[0] = link;
		room->links[1] = NULL;
	}
}

void		ft_build_graph(t_lem_in *lem_in)
{
	t_link	*link;
	t_room	*room;

	room = lem_in->room;
	while (room)
	{
		link = lem_in->link;
		while (link)
		{
			if (link->from == room)
			{
				ft_add_tubes(link->to, room, lem_in);
				ft_add_tubes(room, link->to, lem_in);
			}
			link = link->next;
		}
		room = room->next;
	}
	if (!lem_in->start->links)
		ft_lem_in_error(lem_in, "start has no links");
	if (!lem_in->end->links)
		ft_lem_in_error(lem_in, "end has no links");
}
